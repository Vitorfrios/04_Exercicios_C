#!/usr/bin/env python3
"""
Script para executar o Chat System com IA Gratuita
"""

import uvicorn
import os
import webbrowser
from datetime import datetime

def main():
    print("🚀 INICIANDO CHAT SYSTEM - IA GRATUITA")
    print("=" * 50)
    
    # Verifica se o .env existe
    if not os.path.exists('chat_system/.env'):
        print("❌ Arquivo .env não encontrado!")
        print("📋 Crie um arquivo .env com:")
        print("""
GROQ_API_KEY=sua_chave_groq_aqui
DATABASE_URL=sqlite:///chat_system.db
SECRET_KEY=sua_chave_secreta
DEBUG=True
        """)
        return
    
    # Verifica dependências
    try:
        import fastapi
        import sqlite3
        import openai
        print("✅ Todas as dependências encontradas")
    except ImportError as e:
        print(f"❌ Dependência faltando: {e}")
        print("📦 Execute: pip install -r requirements.txt")
        return
    
    print("📊 Configuração do sistema:")
    print(f"   • Database: {os.getenv('DATABASE_URL', 'sqlite:///chat_system.db')}")
    print(f"   • IA Service: {'Groq ✅' if os.getenv('GROQ_API_KEY') else 'Mock Mode ⚠️'}")
    print(f"   • Debug: {os.getenv('DEBUG', 'True')}")
    
    print("\n🎯 URLs do sistema:")
    print("   • Frontend: http://localhost:8000")
    print("   • API Docs: http://localhost:8000/docs")
    print("\n📍 Credenciais padrão:")
    print("   • Usuário: admin")
    print("   • Senha: admin123")
    print("\n" + "=" * 50)
    
    # Pergunta se quer abrir o navegador
    try:
        choice = input("Abrir navegador automaticamente? (s/N): ").strip().lower()
        if choice in ['s', 'sim', 'y', 'yes']:
            webbrowser.open('http://localhost:8000')
    except:
        pass
    
    print("⏳ Iniciando servidor... (Ctrl+C para parar)")
    
    # Inicia o servidor
    uvicorn.run(
        "app:app",
        host="0.0.0.0",
        port=8000,
        reload=True,
        log_level="info"
    )

if __name__ == "__main__":
    main()