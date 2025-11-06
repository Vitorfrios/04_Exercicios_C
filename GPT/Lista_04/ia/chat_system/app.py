# app.py - CORRIGIR importações e inicialização
from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse, JSONResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
import uvicorn
import os
import sys

# Adiciona o diretório atual ao path para importações
current_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.append(current_dir)

app = FastAPI(title="Chat System", version="1.0.0")

# ✅ Configuração ABSOLUTA de templates
templates_dir = os.path.join(current_dir, "templates")
print(f"📁 Templates path: {templates_dir}")

# Verifica se a pasta templates existe
if not os.path.exists(templates_dir):
    print("❌ PASTA TEMPLATES NÃO ENCONTRADA!")
    os.makedirs(templates_dir, exist_ok=True)
    print("✅ Pasta templates criada")

templates = Jinja2Templates(directory=templates_dir)

# Arquivos estáticos
static_dir = os.path.join(current_dir, "static")
app.mount("/static", StaticFiles(directory=static_dir), name="static")

# ✅ Inicialização ROBUSTA dos serviços
try:
    import database
    print("✅ Database carregado")
except Exception as e:
    print(f"❌ Erro database: {e}")

try:
    import auth
    print("✅ Auth carregado")
except Exception as e:
    print(f"❌ Erro auth: {e}")

try:
    import chat_services
    print("✅ Chat services carregado")
except Exception as e:
    print(f"❌ Erro chat_services: {e}")

try:
    import routes
    app.include_router(routes.router)
    print("✅ Rotas carregadas")
except Exception as e:
    print(f"❌ Erro routes: {e}")

# ✅ Rota principal FALLBACK garantida
@app.get("/")
async def root():
    """Rota principal garantida"""
    html_content = """
    <!DOCTYPE html>
    <html>
    <head>
        <title>Chat System - IA Gratuita</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <style>
            body {
                font-family: Arial, sans-serif;
                margin: 0;
                padding: 40px;
                background: linear-gradient(135deg, #667eea, #764ba2);
                color: white;
                text-align: center;
                min-height: 100vh;
                display: flex;
                align-items: center;
                justify-content: center;
            }
            .container {
                max-width: 800px;
                background: rgba(255,255,255,0.1);
                padding: 40px;
                border-radius: 20px;
                backdrop-filter: blur(10px);
                box-shadow: 0 8px 32px rgba(0,0,0,0.1);
            }
            h1 {
                margin-bottom: 20px;
                font-size: 2.5em;
            }
            .status {
                background: rgba(0,255,0,0.2);
                padding: 10px;
                border-radius: 10px;
                margin: 20px 0;
            }
            .credential-box {
                background: rgba(0,0,0,0.3);
                padding: 20px;
                border-radius: 10px;
                margin: 20px 0;
            }
            .widgets-info {
                display: flex;
                gap: 20px;
                justify-content: center;
                margin: 30px 0;
            }
            .widget-card {
                background: rgba(255,255,255,0.1);
                padding: 20px;
                border-radius: 10px;
                flex: 1;
            }
        </style>
    </head>
    <body>
        <div class="container">
            <h1>🚀 Chat System - IA Gratuita</h1>
            <div class="status">
                ✅ Sistema Online - FastAPI + SQLite
            </div>
            
            <div class="widgets-info">
                <div class="widget-card">
                    <h3>💬 Widget Usuário</h3>
                    <p>Canto inferior direito</p>
                    <p>Chat geral de suporte</p>
                </div>
                <div class="widget-card">
                    <h3>🔧 Widget Dev</h3>
                    <p>Canto inferior esquerdo</p>
                    <p>Análise técnica e debug</p>
                </div>
            </div>
            
            <div class="credential-box">
                <h3>🔐 Credenciais Desenvolvedor</h3>
                <p><strong>Usuário:</strong> admin</p>
                <p><strong>Senha:</strong> admin123</p>
            </div>
            
            <div style="margin-top: 30px;">
                <p><strong>📊 Status:</strong> Sistema carregado com sucesso</p>
                <p><strong>🔧 API:</strong> <a href="/docs" style="color: #fff;">/docs</a> | <a href="/health" style="color: #fff;">/health</a></p>
            </div>
        </div>
        
        <!-- Widgets -->
        <script src="/static/js/response-handler.js"></script>
        <script src="/static/js/user-widget.js"></script>
        <script src="/static/js/dev-widget.js"></script>
        
        <script>
            console.log('✅ Chat System carregado com sucesso!');
            // Inicializa widgets após carregamento
            setTimeout(() => {
                if (typeof userWidget !== 'undefined') {
                    console.log('✅ User Widget pronto');
                }
                if (typeof devWidget !== 'undefined') {
                    console.log('✅ Dev Widget pronto');
                }
            }, 1000);
        </script>
    </body>
    </html>
    """
    return HTMLResponse(content=html_content)

# ✅ Rota de health check
@app.get("/health")
async def health():
    return {
        "status": "healthy", 
        "service": "Chat System",
        "version": "1.0.0",
        "endpoints": ["/", "/health", "/docs", "/api/health"]
    }

@app.get("/api/health")
async def api_health():
    return {
        "status": "online",
        "timestamp": "now",
        "features": ["fastapi", "sqlite", "ia_gratuita", "widgets"]
    }

if __name__ == "__main__":
    print("🚀 Chat System - Iniciando Servidor")
    print("📍 URLs:")
    print("   • Principal: http://localhost:8000")
    print("   • API Docs: http://localhost:8000/docs") 
    print("   • Health: http://localhost:8000/health")
    print("🔐 Credenciais: admin / admin123")
    uvicorn.run(app, host="0.0.0.0", port=8000, log_level="info")