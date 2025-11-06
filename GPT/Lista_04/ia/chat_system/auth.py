# auth.py
import hashlib
import secrets
from datetime import datetime, timedelta
import database

class AuthService:
    def __init__(self):
        self.token_expire_hours = 24
    
    def hash_password(self, password: str) -> str:
        """Hash seguro da senha"""
        return hashlib.sha256(password.encode()).hexdigest()
    
    def verify_password(self, plain_password: str, hashed_password: str) -> bool:
        """Verifica se a senha corresponde ao hash"""
        return self.hash_password(plain_password) == hashed_password
    
    def create_session_token(self, dev_user_id: int) -> str:
        """Cria um token de sessão seguro"""
        token = secrets.token_urlsafe(32)
        expires_at = datetime.now() + timedelta(hours=self.token_expire_hours)
        
        conn = database.db.get_connection()
        cursor = conn.cursor()
        
        cursor.execute('''
            INSERT INTO dev_session_token (token, dev_user_id, expires_at)
            VALUES (?, ?, ?)
        ''', (token, dev_user_id, expires_at))
        
        conn.commit()
        conn.close()
        
        return token
    
    def verify_token(self, token: str) -> dict:
        """Verifica se o token é válido e retorna dados do usuário"""
        conn = database.db.get_connection()
        cursor = conn.cursor()
        
        cursor.execute('''
            SELECT st.dev_user_id, st.expires_at, du.username, du.email
            FROM dev_session_token st
            JOIN dev_user du ON st.dev_user_id = du.id
            WHERE st.token = ? AND st.is_active = TRUE
        ''', (token,))
        
        result = cursor.fetchone()
        conn.close()
        
        if not result:
            return None
        
        dev_user_id, expires_at, username, email = result
        
        # Verifica se o token expirou
        if datetime.now() > datetime.fromisoformat(expires_at):
            return None
        
        return {
            "dev_user_id": dev_user_id,
            "username": username,
            "email": email
        }
    
    def login_dev(self, username: str, password: str) -> dict:
        """Login do desenvolvedor"""
        conn = database.db.get_connection()
        cursor = conn.cursor()
        
        cursor.execute('''
            SELECT id, username, email, password_hash
            FROM dev_user
            WHERE username = ? OR email = ?
        ''', (username, username))
        
        user = cursor.fetchone()
        conn.close()
        
        if not user:
            return {"success": False, "error": "Credenciais inválidas"}
        
        user_id, username, email, password_hash = user
        
        if not self.verify_password(password, password_hash):
            return {"success": False, "error": "Credenciais inválidas"}
        
        token = self.create_session_token(user_id)
        
        return {
            "success": True,
            "token": token,
            "user": {
                "id": user_id,
                "username": username,
                "email": email
            }
        }

# Instância global
auth_service = AuthService()