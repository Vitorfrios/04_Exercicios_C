# config.py
import os
from dotenv import load_dotenv

load_dotenv()

class Config:
    # Database
    DATABASE_URL = os.getenv('DATABASE_URL', 'sqlite:///chat_system.db')
    SECRET_KEY = os.getenv('SECRET_KEY', 'dev-secret-key-change-in-production-2024')
    
    # IA Services
    GROQ_API_KEY = os.getenv('GROQ_API_KEY')
    
    # App Settings
    DEBUG = os.getenv('DEBUG', 'True').lower() == 'true'
    TOKEN_EXPIRE_HOURS = 24
    
    # IA Limits
    MAX_TOKENS = 2000
    TEMPERATURE = 0.7
    
    @classmethod
    def validate_config(cls):
        if not cls.GROQ_API_KEY:
            print("⚠️  GROQ_API_KEY não encontrada - O sistema funcionará em modo limitado")
        else:
            print("✅ Configuração carregada com sucesso")

Config.validate_config()