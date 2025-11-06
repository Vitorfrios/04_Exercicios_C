# database.py
import sqlite3
import hashlib
import os

class Database:
    def __init__(self):
        self.db_path = "chat_system.db"
    
    def get_connection(self):
        return sqlite3.connect(self.db_path, check_same_thread=False)
    
    def init_db(self):
        """Cria todas as tabelas do sistema"""
        try:
            conn = self.get_connection()
            cursor = conn.cursor()
            
            # Tabela de desenvolvedores
            cursor.execute('''
                CREATE TABLE IF NOT EXISTS dev_user (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT UNIQUE NOT NULL,
                    email TEXT UNIQUE NOT NULL,
                    password_hash TEXT NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            ''')
            
            # Tabela de tokens de sessão
            cursor.execute('''
                CREATE TABLE IF NOT EXISTS dev_session_token (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    token TEXT UNIQUE NOT NULL,
                    dev_user_id INTEGER NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    expires_at TIMESTAMP NOT NULL,
                    is_active BOOLEAN DEFAULT TRUE,
                    FOREIGN KEY (dev_user_id) REFERENCES dev_user (id)
                )
            ''')
            
            # Tabela de sessões de chat do dev
            cursor.execute('''
                CREATE TABLE IF NOT EXISTS dev_chat_session (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    dev_user_id INTEGER NOT NULL,
                    title TEXT NOT NULL,
                    session_type TEXT DEFAULT 'general',
                    model_name TEXT DEFAULT 'groq-llama',
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    last_interaction TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    FOREIGN KEY (dev_user_id) REFERENCES dev_user (id)
                )
            ''')
            
            # Tabela de mensagens do dev
            cursor.execute('''
                CREATE TABLE IF NOT EXISTS dev_chat_message (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    session_id INTEGER NOT NULL,
                    role TEXT NOT NULL,
                    content TEXT NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    FOREIGN KEY (session_id) REFERENCES dev_chat_session (id)
                )
            ''')
            
            # Criar usuário dev padrão
            password_hash = hashlib.sha256("admin123".encode()).hexdigest()
            cursor.execute('''
                INSERT OR IGNORE INTO dev_user (username, email, password_hash) 
                VALUES (?, ?, ?)
            ''', ("admin", "admin@system.com", password_hash))
            
            conn.commit()
            conn.close()
            print("✅ Banco de dados inicializado com sucesso!")
            return True
            
        except Exception as e:
            print(f"❌ Erro no banco de dados: {e}")
            return False
        
    def delete_dev_session(self, session_id: int, dev_user_id: int) -> bool:
        """Deleta uma sessão e todas suas mensagens"""
        try:
            conn = self.get_connection()
            cursor = conn.cursor()
            
            # Verifica se a sessão pertence ao usuário
            cursor.execute('''
                SELECT dev_user_id FROM dev_chat_session WHERE id = ?
            ''', (session_id,))
            
            result = cursor.fetchone()
            if not result or result[0] != dev_user_id:
                conn.close()
                return False
            
            # Deleta todas as mensagens da sessão primeiro
            cursor.execute('DELETE FROM dev_chat_message WHERE session_id = ?', (session_id,))
            
            # Deleta a sessão
            cursor.execute('DELETE FROM dev_chat_session WHERE id = ?', (session_id,))
            
            conn.commit()
            conn.close()
            return True
            
        except Exception as e:
            print(f"❌ Erro ao deletar sessão: {e}")
            return False
    
    def delete_all_dev_sessions(self, dev_user_id: int) -> bool:
        """Deleta todas as sessões de um dev"""
        try:
            conn = self.get_connection()
            cursor = conn.cursor()
            
            # Busca todos os IDs de sessão do usuário
            cursor.execute('SELECT id FROM dev_chat_session WHERE dev_user_id = ?', (dev_user_id,))
            session_ids = [row[0] for row in cursor.fetchall()]
            
            # Deleta mensagens de todas as sessões
            for session_id in session_ids:
                cursor.execute('DELETE FROM dev_chat_message WHERE session_id = ?', (session_id,))
            
            # Deleta todas as sessões
            cursor.execute('DELETE FROM dev_chat_session WHERE dev_user_id = ?', (dev_user_id,))
            
            conn.commit()
            conn.close()
            return True
            
        except Exception as e:
            print(f"❌ Erro ao deletar todas as sessões: {e}")
            return False

# Inicializa o banco
db = Database()
db.init_db()