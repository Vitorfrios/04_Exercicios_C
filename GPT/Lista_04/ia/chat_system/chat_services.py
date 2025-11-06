# chat_services.py - COMPLETO E CORRIGIDO
from datetime import datetime
import database
from ia_services import ia_service

class ChatService:
    def __init__(self):
        self.max_history_messages = 10
        from code_analyzer import code_analyzer
        self.code_analyzer = code_analyzer
    
    # === SERVIÇOS DE DEV ===
    
    def create_dev_chat_session(self, dev_user_id: int, title: str = None, session_type: str = "general"):
        """Cria nova sessão de chat para dev"""
        if not title:
            title = f"Chat {datetime.now().strftime('%d/%m %H:%M')}"
        
        conn = database.db.get_connection()
        cursor = conn.cursor()
        
        cursor.execute('''
            INSERT INTO dev_chat_session (dev_user_id, title, session_type, last_interaction)
            VALUES (?, ?, ?, ?)
        ''', (dev_user_id, title, session_type, datetime.now()))
        
        session_id = cursor.lastrowid
        
        conn.commit()
        conn.close()
        
        return self.get_dev_session(session_id)
    
    def get_dev_sessions(self, dev_user_id: int):
        """Lista todas as sessões do dev"""
        conn = database.db.get_connection()
        cursor = conn.cursor()
        
        cursor.execute('''
            SELECT id, title, session_type, model_name, created_at, last_interaction
            FROM dev_chat_session
            WHERE dev_user_id = ?
            ORDER BY last_interaction DESC
        ''', (dev_user_id,))
        
        sessions = []
        for row in cursor.fetchall():
            sessions.append({
                "id": row[0],
                "title": row[1],
                "session_type": row[2],
                "model_name": row[3],
                "created_at": row[4],
                "last_interaction": row[5]
            })
        
        conn.close()
        return sessions
    
    def get_dev_session(self, session_id: int):
        """Busca uma sessão específica"""
        conn = database.db.get_connection()
        cursor = conn.cursor()
        
        cursor.execute('''
            SELECT id, dev_user_id, title, session_type, model_name, created_at, last_interaction
            FROM dev_chat_session
            WHERE id = ?
        ''', (session_id,))
        
        row = cursor.fetchone()
        conn.close()
        
        if not row:
            return None
        
        return {
            "id": row[0],
            "dev_user_id": row[1],
            "title": row[2],
            "session_type": row[3],
            "model_name": row[4],
            "created_at": row[5],
            "last_interaction": row[6]
        }
    
    def get_dev_messages(self, session_id: int):
        """Busca mensagens de uma sessão"""
        conn = database.db.get_connection()
        cursor = conn.cursor()
        
        cursor.execute('''
            SELECT role, content, created_at
            FROM dev_chat_message
            WHERE session_id = ?
            ORDER BY created_at ASC
        ''', (session_id,))
        
        messages = []
        for row in cursor.fetchall():
            messages.append({
                "role": row[0],
                "content": row[1],
                "created_at": row[2]
            })
        
        conn.close()
        return messages
    
    def send_dev_message(self, session_id: int, dev_user_id: int, content: str, action_type: str = None):
        """Envia mensagem com histórico inteligente - MELHORADO"""
        # Verifica se a sessão pertence ao dev
        session = self.get_dev_session(session_id)
        if not session or session["dev_user_id"] != dev_user_id:
            return {"error": "Sessão não encontrada ou acesso negado"}
        
        # Salva mensagem do dev
        conn = database.db.get_connection()
        cursor = conn.cursor()
        
        cursor.execute('''
            INSERT INTO dev_chat_message (session_id, role, content)
            VALUES (?, 'dev', ?)
        ''', (session_id, content))
        
        # Atualiza última interação
        cursor.execute('''
            UPDATE dev_chat_session 
            SET last_interaction = ? 
            WHERE id = ?
        ''', (datetime.now(), session_id))
        
        conn.commit()
        
        # Busca MAIS histórico para contexto melhor
        cursor.execute('''
            SELECT role, content
            FROM dev_chat_message
            WHERE session_id = ?
            ORDER BY created_at DESC
            LIMIT ?
        ''', (session_id, 10))  # ✅ Aumentado para 10 mensagens
        
        history = cursor.fetchall()
        history.reverse()
        
        # Prepara mensagens para a IA (AGORA MAIS INTELIGENTE)
        messages = []
        for role, content in history:
            # ✅ Converte roles para o formato OpenAI
            openai_role = "user" if role == "dev" else "assistant"
            messages.append({"role": openai_role, "content": content})
        
        # ✅ Se é uma ação, adiciona contexto natural
        if action_type and messages:
            # Mantém a última mensagem do usuário como contexto
            last_user_msg = None
            for msg in reversed(messages):
                if msg['role'] == 'user':
                    last_user_msg = msg
                    break
            
            # Se encontrou mensagem anterior, usa como contexto
            if last_user_msg:
                # ✅ ADICIONA contexto da ação sem repetir toda a conversa
                action_context_msg = {
                    "role": "user", 
                    "content": f"Ação solicitada: {action_type}. Contexto: {last_user_msg['content'][:100]}..."
                }
                messages.append(action_context_msg)
        
        # Obtém resposta da IA
        ia_response = ia_service.dev_chat(messages, action_type)  
        
        # Salva resposta da IA
        cursor.execute('''
            INSERT INTO dev_chat_message (session_id, role, content)
            VALUES (?, 'ia', ?)
        ''', (session_id, ia_response))
        
        # Atualiza última interação novamente
        cursor.execute('''
            UPDATE dev_chat_session 
            SET last_interaction = ? 
            WHERE id = ?
        ''', (datetime.now(), session_id))
        
        conn.commit()
        conn.close()
        
        return {"response": ia_response}
    
    # === SERVIÇOS DE USUÁRIO ===
    
    def send_user_message(self, content: str, user_identifier: str = "anonymous"):
        """Processa mensagem do usuário comum com contexto inteligente"""
        # Simula histórico básico para contexto
        messages = [{"role": "user", "content": content}]
        ia_response = ia_service.user_chat(messages, user_identifier)
        
        return {"response": ia_response}
    
    def analyze_code_issues(self, dev_user_id: int):
        """Analisa o código - COM LOGS DE DEBUG MELHORADO"""
        print("🔍 Iniciando análise de código...")
        
        try:
            issues = self.code_analyzer.analyze_project()
            print(f"✅ Análise completada: {len(issues['duplicate_functions'])} duplicatas encontradas")
            
            formatted_issues = []
            
            # Duplicatas (ignora __init__ que são normais)
            if issues['duplicate_functions']:
                for dup in issues['duplicate_functions'][:3]:
                    if dup['function'] != '__init__':  # ✅ Filtra __init__
                        formatted_issues.append(f"🚨 {dup['function']} em {dup['file1']} e {dup['file2']}")
            
            # Segurança
            if issues['security_issues']:
                for sec in issues['security_issues'][:2]:
                    formatted_issues.append(f"🔒 {sec['issue']} em {sec['file']}")
            
            # Erros
            if issues['error_handling']:
                for err in issues['error_handling'][:2]:
                    formatted_issues.append(f"⚠️ {err['issue']} em {err['file']}")
            
            if not formatted_issues:
                return {"issues": ["✅ Nenhum problema crítico encontrado"]}
            
            print(f"📋 Retornando {len(formatted_issues)} issues")
            return {"issues": formatted_issues}
            
        except Exception as e:
            print(f"❌ Erro na análise: {e}")
            return {"error": f"Erro na análise: {str(e)}"}
        
    def delete_dev_session(self, session_id: int, dev_user_id: int):
        """Deleta uma sessão específica do dev"""
        try:
            success = database.db.delete_dev_session(session_id, dev_user_id)
            if success:
                return {"success": True, "message": "Sessão deletada com sucesso"}
            else:
                return {"error": "Sessão não encontrada ou acesso negado"}
        except Exception as e:
            return {"error": f"Erro ao deletar sessão: {str(e)}"}
    
    def delete_all_dev_sessions(self, dev_user_id: int):
        """Deleta todas as sessões do dev"""
        try:
            success = database.db.delete_all_dev_sessions(dev_user_id)
            if success:
                return {"success": True, "message": "Todas as sessões foram deletadas"}
            else:
                return {"error": "Erro ao deletar sessões"}
        except Exception as e:
            return {"error": f"Erro ao deletar sessões: {str(e)}"}

# Instância global
chat_service = ChatService()