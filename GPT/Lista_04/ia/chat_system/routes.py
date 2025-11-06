# routes.py - VERSÃO COMPLETA E CORRIGIDA
from fastapi import APIRouter, HTTPException, Header, Request
from fastapi.responses import HTMLResponse, JSONResponse
from fastapi.templating import Jinja2Templates
from pydantic import BaseModel
import os
import sys

# ✅ Garante importações corretas
current_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.append(current_dir)

try:
    import auth
    import chat_services
    import database
    print("✅ Módulos importados em routes.py")
except Exception as e:
    print(f"❌ Erro importação routes: {e}")

# ✅ Configura templates
templates_dir = os.path.join(current_dir, "templates")
templates = Jinja2Templates(directory=templates_dir)

router = APIRouter()

# Models
class LoginRequest(BaseModel):
    username: str
    password: str

class DevMessageRequest(BaseModel):
    session_id: int
    content: str
    action_type: str = None

class UserMessageRequest(BaseModel):
    content: str
    user_identifier: str = "anonymous"

class CreateSessionRequest(BaseModel):
    title: str = None
    session_type: str = "general"

# === ROTAS PRINCIPAIS ===

@router.get("/", response_class=HTMLResponse)
async def main_page(request: Request):
    """Página principal via templates"""
    try:
        return templates.TemplateResponse("base.html", {"request": request})
    except Exception as e:
        # Fallback se template não existir
        return HTMLResponse(content=f"""
        <!DOCTYPE html>
        <html>
        <head>
            <title>Chat System - Fallback</title>
            <style>
                body {{
                    font-family: Arial, sans-serif;
                    margin: 0;
                    padding: 40px;
                    background: linear-gradient(135deg, #667eea, #764ba2);
                    color: white;
                    text-align: center;
                }}
                .container {{
                    max-width: 800px;
                    margin: 0 auto;
                    background: rgba(255,255,255,0.1);
                    padding: 40px;
                    border-radius: 20px;
                    backdrop-filter: blur(10px);
                }}
            </style>
        </head>
        <body>
            <div class="container">
                <h1>🚀 Chat System - Fallback</h1>
                <p>Template carregado via fallback. Widgets funcionando!</p>
                <div class="credential-box" style="background: rgba(0,0,0,0.3); padding: 20px; border-radius: 10px; margin: 20px 0;">
                    <h3>🔐 Credenciais Dev</h3>
                    <p><strong>Usuário:</strong> admin</p>
                    <p><strong>Senha:</strong> admin123</p>
                </div>
                <p><em>Erro template: {str(e)}</em></p>
            </div>
            
            <script src="/static/js/user-widget.js"></script>
            <script src="/static/js/dev-widget.js"></script>
        </body>
        </html>
        """)

# === ROTAS DE AUTENTICAÇÃO ===

@router.post("/api/dev/login")
async def dev_login(login_data: LoginRequest):
    """Login do desenvolvedor"""
    try:
        result = auth.auth_service.login_dev(login_data.username, login_data.password)
        if not result["success"]:
            raise HTTPException(status_code=401, detail=result["error"])
        return result
    except Exception as e:
        print(f"❌ Erro login: {e}")
        raise HTTPException(status_code=500, detail=f"Erro interno: {str(e)}")

# === ROTAS DE SESSÕES DEV ===

@router.get("/api/dev/sessions")
async def get_dev_sessions(authorization: str = Header(None)):
    """Lista todas as sessões do dev"""
    try:
        user_data = _get_user_from_token(authorization)
        sessions = chat_services.chat_service.get_dev_sessions(user_data["dev_user_id"])
        return {"sessions": sessions}
    except Exception as e:
        print(f"❌ Erro get_dev_sessions: {e}")
        raise HTTPException(status_code=500, detail=f"Erro interno: {str(e)}")

@router.post("/api/dev/sessions")
async def create_dev_session(session_data: CreateSessionRequest, authorization: str = Header(None)):
    """Cria nova sessão de chat para dev"""
    try:
        user_data = _get_user_from_token(authorization)
        session = chat_services.chat_service.create_dev_chat_session(
            user_data["dev_user_id"], 
            session_data.title,
            session_data.session_type
        )
        return {"session": session}
    except Exception as e:
        print(f"❌ Erro create_dev_session: {e}")
        raise HTTPException(status_code=500, detail=f"Erro interno: {str(e)}")

@router.get("/api/dev/sessions/{session_id}/messages")
async def get_dev_messages(session_id: int, authorization: str = Header(None)):
    """Busca mensagens de uma sessão específica"""
    try:
        user_data = _get_user_from_token(authorization)
        session = chat_services.chat_service.get_dev_session(session_id)
        if not session or session["dev_user_id"] != user_data["dev_user_id"]:
            raise HTTPException(status_code=404, detail="Sessão não encontrada")
        messages = chat_services.chat_service.get_dev_messages(session_id)
        return {"messages": messages}
    except HTTPException:
        raise
    except Exception as e:
        print(f"❌ Erro get_dev_messages: {e}")
        raise HTTPException(status_code=500, detail=f"Erro interno: {str(e)}")

@router.post("/api/dev/send-message")
async def send_dev_message(message_data: DevMessageRequest, authorization: str = Header(None)):
    """Envia mensagem para sessão dev com ação opcional"""
    try:
        user_data = _get_user_from_token(authorization)
        result = chat_services.chat_service.send_dev_message(
            message_data.session_id,
            user_data["dev_user_id"], 
            message_data.content,
            message_data.action_type
        )
        if "error" in result:
            raise HTTPException(status_code=400, detail=result["error"])
        return {"response": result["response"]}
    except HTTPException:
        raise
    except Exception as e:
        print(f"❌ Erro send_dev_message: {e}")
        raise HTTPException(status_code=500, detail=f"Erro interno: {str(e)}")

@router.get("/api/dev/analyze-code")
async def analyze_code(authorization: str = Header(None)):
    """Analisa código do projeto"""
    try:
        user_data = _get_user_from_token(authorization)
        result = chat_services.chat_service.analyze_code_issues(user_data["dev_user_id"])
        return result
    except Exception as e:
        print(f"❌ Erro analyze_code: {e}")
        raise HTTPException(status_code=500, detail=f"Erro interno: {str(e)}")

@router.delete("/api/dev/sessions/{session_id}")
async def delete_dev_session(session_id: int, authorization: str = Header(None)):
    """Deleta uma sessão específica do dev"""
    try:
        user_data = _get_user_from_token(authorization)
        # ✅ CORREÇÃO: Usar database diretamente (eliminar duplicação)
        success = database.db.delete_dev_session(session_id, user_data["dev_user_id"])
        if success:
            return {"success": True, "message": "Sessão deletada com sucesso"}
        else:
            return {"error": "Sessão não encontrada ou acesso negado"}
    except Exception as e:
        print(f"❌ Erro delete_dev_session: {e}")
        raise HTTPException(status_code=500, detail=f"Erro interno: {str(e)}")

@router.delete("/api/dev/sessions")
async def delete_all_dev_sessions(authorization: str = Header(None)):
    """Deleta todas as sessões do dev"""
    try:
        user_data = _get_user_from_token(authorization)
        # ✅ CORREÇÃO: Usar database diretamente
        success = database.db.delete_all_dev_sessions(user_data["dev_user_id"])
        if success:
            return {"success": True, "message": "Todas as sessões foram deletadas"}
        else:
            return {"error": "Erro ao deletar sessões"}
    except Exception as e:
        print(f"❌ Erro delete_all_dev_sessions: {e}")
        raise HTTPException(status_code=500, detail=f"Erro interno: {str(e)}")

# === ROTAS DE USUÁRIO COMUM ===

@router.post("/api/user/send-message")
async def send_user_message(message_data: UserMessageRequest):
    """Processa mensagem do usuário comum"""
    try:
        result = chat_services.chat_service.send_user_message(
            message_data.content,
            message_data.user_identifier
        )
        return {"response": result["response"]}
    except Exception as e:
        print(f"❌ Erro send_user_message: {e}")
        raise HTTPException(status_code=500, detail=f"Erro interno: {str(e)}")

# === ROTAS DE HEALTH CHECK ===

@router.get("/health")
async def health():
    """Health check básico"""
    return {
        "status": "healthy", 
        "service": "Chat System",
        "version": "1.0.0"
    }

@router.get("/api/health")
async def api_health():
    """Health check detalhado da API"""
    return {
        "status": "online", 
        "version": "1.0.0",
        "features": ["fastapi", "sqlite", "ia_gratuita", "widgets"],
        "endpoints": [
            "/",
            "/health", 
            "/api/health",
            "/api/dev/login",
            "/api/dev/sessions",
            "/api/user/send-message"
        ]
    }

@router.get("/docs")
async def get_docs():
    """Redireciona para documentação interativa"""
    return JSONResponse({
        "message": "Acesse /docs para documentação interativa",
        "url": "/docs"
    })

# === FUNÇÕES AUXILIARES ===

def _get_user_from_token(authorization: str):
    """Verifica token e retorna dados do usuário"""
    try:
        if not authorization or not authorization.startswith("Bearer "):
            raise HTTPException(status_code=401, detail="Token necessário")
        
        token = authorization[7:]
        user_data = auth.auth_service.verify_token(token)
        
        if not user_data:
            raise HTTPException(status_code=401, detail="Token inválido ou expirado")
        
        return user_data
    except HTTPException:
        raise
    except Exception as e:
        print(f"❌ Erro _get_user_from_token: {e}")
        raise HTTPException(status_code=500, detail="Erro na verificação do token")

# === ROTA DE FALLBACK PARA ERROS 404 ===

@router.get("/{full_path:path}")
async def catch_all(full_path: str):
    """Captura todas as rotas não encontradas"""
    raise HTTPException(
        status_code=404, 
        detail=f"Rota não encontrada: /{full_path}. Endpoints disponíveis: /, /health, /api/health, /docs"
    )