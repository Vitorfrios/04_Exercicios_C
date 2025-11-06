# routes.py
from fastapi import APIRouter, HTTPException, Header, Request
from fastapi.responses import HTMLResponse, JSONResponse
from fastapi.templating import Jinja2Templates
from pydantic import BaseModel
import auth
import chat_services
import os

# ✅ Configura templates
templates = Jinja2Templates(directory="templates")

# ✅ Define o router
router = APIRouter()

# Models
class LoginRequest(BaseModel):
    username: str
    password: str

# routes.py - ATUALIZAR ROTAS PARA AÇÕES
class DevMessageRequest(BaseModel):
    session_id: int
    content: str
    action_type: str = None  # NOVO: suporte a ações


class UserMessageRequest(BaseModel):
    content: str
    user_identifier: str = "anonymous"

class CreateSessionRequest(BaseModel):
    title: str = None
    session_type: str = "general"

# === ROTA PRINCIPAL COM HTML ===
@router.get("/", response_class=HTMLResponse)
async def main_page(request: Request):
    """Página principal com interface completa"""
    return templates.TemplateResponse("base.html", {"request": request})

# === ROTAS DE AUTENTICAÇÃO ===
@router.post("/api/dev/login")
async def dev_login(login_data: LoginRequest):
    result = auth.auth_service.login_dev(login_data.username, login_data.password)
    if not result["success"]:
        raise HTTPException(status_code=401, detail=result["error"])
    return result

# === ROTAS DE CHAT ===
@router.get("/api/dev/sessions")
async def get_dev_sessions(authorization: str = Header(None)):
    user_data = _get_user_from_token(authorization)
    sessions = chat_services.chat_service.get_dev_sessions(user_data["dev_user_id"])
    return {"sessions": sessions}

@router.post("/api/dev/sessions")
async def create_dev_session(session_data: CreateSessionRequest, authorization: str = Header(None)):
    user_data = _get_user_from_token(authorization)
    session = chat_services.chat_service.create_dev_chat_session(
        user_data["dev_user_id"], 
        session_data.title,
        session_data.session_type
    )
    return {"session": session}

@router.get("/api/dev/sessions/{session_id}/messages")
async def get_dev_messages(session_id: int, authorization: str = Header(None)):
    user_data = _get_user_from_token(authorization)
    session = chat_services.chat_service.get_dev_session(session_id)
    if not session or session["dev_user_id"] != user_data["dev_user_id"]:
        raise HTTPException(status_code=404, detail="Sessão não encontrada")
    messages = chat_services.chat_service.get_dev_messages(session_id)
    return {"messages": messages}

@router.post("/api/dev/send-message")
async def send_dev_message(message_data: DevMessageRequest, authorization: str = Header(None)):
    user_data = _get_user_from_token(authorization)
    result = chat_services.chat_service.send_dev_message(
        message_data.session_id,
        user_data["dev_user_id"], 
        message_data.content,
        message_data.action_type  # NOVO: passa o tipo de ação
    )
    if "error" in result:
        raise HTTPException(status_code=400, detail=result["error"])
    return {"response": result["response"]}

@router.post("/api/user/send-message")
async def send_user_message(message_data: UserMessageRequest):
    result = chat_services.chat_service.send_user_message(
        message_data.content,
        message_data.user_identifier
    )
    return {"response": result["response"]}

# === ROTAS DE HEALTH ===
@router.get("/health")
async def health():
    return {"status": "healthy", "service": "Chat System"}

@router.get("/api/health")
async def api_health():
    return {
        "status": "online", 
        "version": "1.0.0",
        "features": ["fastapi", "sqlite", "ia_gratuita", "widgets"]
    }
    
@router.get("/api/dev/analyze-code")
async def analyze_code(authorization: str = Header(None)):
    user_data = _get_user_from_token(authorization)
    result = chat_services.chat_service.analyze_code_issues(user_data["dev_user_id"])
    return result


@router.delete("/api/dev/sessions/{session_id}")
async def delete_dev_session(session_id: int, authorization: str = Header(None)):
    user_data = _get_user_from_token(authorization)
    result = chat_services.chat_service.delete_dev_session(session_id, user_data["dev_user_id"])
    if "error" in result:
        raise HTTPException(status_code=400, detail=result["error"])
    return result

@router.delete("/api/dev/sessions")
async def delete_all_dev_sessions(authorization: str = Header(None)):
    user_data = _get_user_from_token(authorization)
    result = chat_services.chat_service.delete_all_dev_sessions(user_data["dev_user_id"])
    if "error" in result:
        raise HTTPException(status_code=400, detail=result["error"])
    return result


# === FUNÇÕES AUXILIARES ===
def _get_user_from_token(authorization: str):
    if not authorization or not authorization.startswith("Bearer "):
        raise HTTPException(status_code=401, detail="Token necessário")
    token = authorization[7:]
    user_data = auth.auth_service.verify_token(token)
    if not user_data:
        raise HTTPException(status_code=401, detail="Token inválido")
    return user_data