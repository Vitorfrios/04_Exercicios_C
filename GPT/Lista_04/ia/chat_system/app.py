# app.py - COM CAMINHO ABSOLUTO PARA TEMPLATES
from fastapi import FastAPI
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
import uvicorn
import os

app = FastAPI(title="Chat System", version="1.0.0")

# ✅ CAMINHO ABSOLUTO para templates
current_dir = os.path.dirname(os.path.abspath(__file__))
templates_dir = os.path.join(current_dir, "templates")

print(f"📁 Procurando templates em: {templates_dir}")

# Configura templates com caminho absoluto
templates = Jinja2Templates(directory=templates_dir)

# Cria pastas se não existirem
os.makedirs("static/css", exist_ok=True)
os.makedirs("static/js", exist_ok=True)

# Arquivos estáticos
app.mount("/static", StaticFiles(directory="static"), name="static")

# Inicializa serviços
try:
    import database
    import auth
    import chat_services
    import ia_services
    import system_info
    print("✅ Todos os serviços carregados")
except Exception as e:
    print(f"⚠️  Erro nos serviços: {e}")

# Importa e inclui rotas
try:
    from routes import router
    app.include_router(router)
    print("✅ Rotas carregadas")
except Exception as e:
    print(f"⚠️  Erro nas rotas: {e}")

# ✅ Rota de fallback caso ainda haja problema
@app.get("/fallback")
async def fallback_page():
    html_content = """
    <!DOCTYPE html>
    <html>
    <head>
        <title>Chat System - IA Gratuita</title>
        <link rel="stylesheet" href="/static/css/widgets.css">
        <style>
            body { 
                font-family: Arial, sans-serif; 
                margin: 0; 
                padding: 40px;
                background: linear-gradient(135deg, #667eea, #764ba2);
                color: white;
                text-align: center;
            }
            .container {
                max-width: 800px;
                margin: 0 auto;
                background: rgba(255,255,255,0.1);
                padding: 40px;
                border-radius: 20px;
                backdrop-filter: blur(10px);
            }
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
        </div>
        
        <script src="/static/js/user-widget.js"></script>
        <script src="/static/js/dev-widget.js"></script>
    </body>
    </html>
    """
    return HTMLResponse(content=html_content)

if __name__ == "__main__":
    print("🚀 Chat System - Com Contexto de IA")
    print("📍 Acesse: http://localhost:8000")
    print("📍 Fallback: http://localhost:8000/fallback")
    print("🔐 Credenciais: admin / admin123")
    uvicorn.run(app, host="0.0.0.0", port=8000)