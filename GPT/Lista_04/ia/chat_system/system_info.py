# system_info.py
import os
import sys
from datetime import datetime

class SystemInfo:
    @staticmethod
    def get_system_context():
        """Retorna informações dinâmicas do sistema"""
        return {
            "system_name": "Chat System - IA Gratuita",
            "version": "1.0.0",
            "backend": "FastAPI + SQLite",
            "frontend": "HTML/CSS/JS Vanilla",
            "ia_provider": "Groq API (Llama 3.1)",
            "widgets": [
                {
                    "name": "Widget Usuário",
                    "icon": "💬",
                    "position": "canto inferior direito",
                    "purpose": "Chat geral de suporte"
                },
                {
                    "name": "Widget Desenvolvedor", 
                    "icon": "🔧",
                    "position": "canto inferior esquerdo",
                    "purpose": "Análise técnica e debug",
                    "login_required": True,
                    "credentials": "admin / admin123"
                }
            ],
            "features": [
                "IA 100% gratuita",
                "Múltiplas sessões de chat",
                "Autenticação segura",
                "Histórico de conversas",
                "Interface responsiva"
            ],
            "current_time": datetime.now().isoformat(),
            "python_version": sys.version,
            "environment": "production" if not os.getenv('DEBUG') else "development"
        }
    
    @staticmethod
    def get_tech_context():
        """Retorna contexto técnico detalhado"""
        return {
            "architecture": {
                "backend": {
                    "framework": "FastAPI",
                    "database": "SQLite",
                    "auth": "Sistema próprio com tokens JWT-like",
                    "api_style": "RESTful"
                },
                "frontend": {
                    "approach": "Vanilla JavaScript",
                    "styling": "CSS customizado",
                    "widgets": "Web Components nativos",
                    "state_management": "LocalStorage + Memória"
                },
                "ia_integration": {
                    "provider": "Groq",
                    "model": "llama-3.1-8b-instant", 
                    "fallback": "Modo Mock quando sem chave"
                }
            },
            "file_structure": """
            chat_system/
            ├── app.py                 # Aplicação principal
            ├── database.py           # Modelos DB
            ├── auth.py               # Autenticação
            ├── chat_services.py      # Lógica de negócio
            ├── ia_services.py        # Integração IA
            ├── routes.py             # Rotas API
            ├── system_info.py        # Informações sistema
            ├── templates/
            │   └── base.html         # HTML principal
            └── static/
                ├── css/
                │   └── widgets.css   # Estilos
                └── js/
                    ├── user-widget.js
                    └── dev-widget.js
            """
        }

# Instância global
system_info = SystemInfo()