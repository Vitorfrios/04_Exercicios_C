# ia_services.py - IA COM RESPOSTAS PRECISAS E INTELIGENTES
import os
from openai import OpenAI
from dotenv import load_dotenv

load_dotenv()

class IAService:
    def __init__(self):
        self.groq_key = os.environ.get("GROQ_API_KEY")
        self.use_real_ia = bool(self.groq_key)

        if self.use_real_ia:
            self.client = OpenAI(
                base_url="https://api.groq.com/openai/v1",
                api_key=self.groq_key,
            )
            print("✅ IA Groq - Respostas Inteligentes Ativas")
        else:
            self.client = None
            print("❌ GROQ_API_KEY não configurada")

    def dev_chat(self, messages, action_type=None):
        """IA que analisa código real e responde com precisão"""
        if not self.use_real_ia:
            return self._get_smart_fallback_response(messages)
        
        try:
            # Análise em tempo real do código
            real_context = self._get_real_time_context()
            user_message = self._get_last_user_message(messages)
            
            # Sistema que entende o código profundamente
            system_prompt = self._create_deep_system_prompt(real_context)
            
            response = self.client.chat.completions.create(
                model="llama-3.1-8b-instant",
                messages=[
                    {"role": "system", "content": system_prompt},
                    {"role": "user", "content": user_message}
                ],
                temperature=0.4,
                max_tokens=1200,
                timeout=25,
            )
            
            return response.choices[0].message.content

        except Exception as e:
            print(f"❌ Erro IA inteligente: {e}")
            return self._analyze_and_respond_offline(messages)

    def _get_real_time_context(self):
        """Obtém contexto REAL em tempo real do sistema"""
        try:
            from code_analyzer import code_analyzer
            
            analysis = code_analyzer.analyze_project()
            current_issues = self._extract_current_issues(analysis)
            project_structure = self._get_project_structure()
            
            return {
                'current_issues': current_issues,
                'structure': project_structure,
                'analysis_data': analysis
            }
            
        except Exception as e:
            return {
                'current_issues': ['Erro na análise: ' + str(e)],
                'structure': {},
                'analysis_data': {}
            }

    def _extract_current_issues(self, analysis):
        """Extrai problemas atuais do código"""
        issues = []
        
        # Duplicatas REAIS
        duplicates = [d for d in analysis.get('duplicate_functions', []) 
                     if d.get('function') != '__init__']
        for dup in duplicates[:3]:
            issues.append(f"DUPLICATA: {dup.get('function')} em {dup.get('file1')} e {dup.get('file2')}")
        
        # Erros de tratamento
        if analysis.get('error_handling'):
            for err in analysis['error_handling'][:2]:
                issues.append(f"ERRO: {err.get('file')} - {err.get('issue')}")
        
        return issues

    def _get_project_structure(self):
        """Estrutura real do projeto"""
        return {
            'backend': 'FastAPI + SQLite',
            'frontend': 'JavaScript Vanilla + Widgets',
            'core_files': [
                'app.py', 'auth.py', 'chat_services.py', 'database.py', 
                'routes.py', 'ia_services.py', 'code_analyzer.py'
            ],
            'widgets': ['user-widget.js', 'dev-widget.js', 'response-handler.js']
        }

    def _create_deep_system_prompt(self, context):
        """Cria prompt inteligente que entende o código profundamente"""
        
        issues_text = "\n".join(context['current_issues']) if context['current_issues'] else "Nenhum problema crítico"
        
        return f"""
Você é um engenheiro sênior analisando este sistema específico.

SISTEMA ANALISADO:
- FastAPI + SQLite + JavaScript vanilla
- Arquivos principais: {', '.join(context['structure']['core_files'])}
- Widgets: {', '.join(context['structure']['widgets'])}

PROBLEMAS ATUAIS IDENTIFICADOS:
{issues_text}

VOCÊ TEM ACESSO COMPLETO AO CÓDIGO E PODE:
- Analisar funções específicas
- Verificar erros em tempo real  
- Sugerir correções baseadas no código real
- Explicar como o sistema funciona
- Diagnosticar problemas técnicos

SEJA DIRETO E PRECISO:
- Não invente arquivos ou funções
- Baseie-se apenas no código existente
- Dê exemplos reais quando possível
- Foque na pergunta específica do usuário

O usuário está interagindo com o sistema AGORA e precisa de ajuda real.
"""

    def _get_last_user_message(self, messages):
        """Pega a última mensagem do usuário com contexto"""
        user_messages = [msg for msg in messages if msg["role"] == "user"]
        return user_messages[-1]["content"] if user_messages else "Analisar o sistema"

    def _analyze_and_respond_offline(self, messages):
        """Análise offline inteligente quando IA não está disponível"""
        try:
            from code_analyzer import code_analyzer
            analysis = code_analyzer.analyze_project()
            
            user_message = self._get_last_user_message(messages).lower()
            
            # Respostas contextuais baseadas na análise real
            if 'duplicad' in user_message or 'duplicat' in user_message:
                return self._format_duplicates_response(analysis)
            elif 'erro' in user_message or 'error' in user_message:
                return self._format_errors_response(analysis)
            elif 'sessão' in user_message or 'session' in user_message:
                return self._format_session_response()
            else:
                return self._format_general_analysis(analysis)
                
        except Exception as e:
            return "🔧 Estou analisando seu sistema FastAPI + SQLite. Para respostas detalhadas, configure a GROQ_API_KEY."

    def _format_duplicates_response(self, analysis):
        """Resposta inteligente sobre duplicatas"""
        duplicates = [d for d in analysis.get('duplicate_functions', []) 
                     if d.get('function') != '__init__']
        
        if not duplicates:
            return "✅ Não encontrei funções duplicadas significativas no código."
        
        response = ["🔍 **FUNÇÕES DUPLICADAS ENCONTRADAS:**"]
        
        for dup in duplicates[:3]:
            func_name = dup.get('function', 'N/A')
            file1 = dup.get('file1', 'N/A')
            file2 = dup.get('file2', 'N/A')
            response.append(f"• `{func_name}` - presente em `{file1}` e `{file2}`")
        
        response.append("\n💡 **SOLUÇÃO:** Unifique em `database.py` e remova de `chat_services.py`")
        return "\n".join(response)

    def _format_errors_response(self, analysis):
        """Resposta inteligente sobre erros"""
        error_issues = analysis.get('error_handling', [])
        
        if not error_issues:
            return "✅ O tratamento de erros parece adequado."
        
        response = ["⚠️ **FALTA TRATAMENTO DE ERROS:**"]
        
        for err in error_issues[:3]:
            response.append(f"• `{err.get('file')}`: {err.get('issue')}")
        
        response.append("\n💡 **SOLUÇÃO:** Adicione try/except nas funções principais")
        return "\n".join(response)

    def _format_session_response(self):
        """Resposta sobre problemas de sessão"""
        return """
🔧 **ERRO DE SESSÃO DETECTADO:**

O erro 500 ao deletar sessão indica um problema no backend.

**CAUSA PROVÁVEL:**
- Função `delete_dev_session` duplicada entre `chat_services.py` e `database.py`
- Falta de tratamento de erro na rota DELETE

**SOLUÇÃO IMEDIATA:**
1. Use apenas `database.db.delete_dev_session()` 
2. Remova a função duplicada de `chat_services.py`
3. Adicione try/except na rota em `routes.py`

**CÓDIGO CORRETO:**
```python
# routes.py - usar assim:
success = database.db.delete_dev_session(session_id, user_id)
"""

def _format_general_analysis(self, analysis):
    """Análise geral inteligente"""
    duplicates = len([d for d in analysis.get('duplicate_functions', []) 
                     if d.get('function') != '__init__'])
    errors = len(analysis.get('error_handling', []))
    
    response = ["📊 **ANÁLISE DO SISTEMA:**"]
    
    if duplicates > 0:
        response.append(f"• {duplicates} função(es) duplicada(s)")
    if errors > 0:
        response.append(f"• {errors} arquivo(s) com pouco tratamento de erro")
    
    if duplicates == 0 and errors == 0:
        response.append("• ✅ Código bem estruturado")
    
    response.append("\n💡 **PRÓXIMOS PASSOS:** Configure GROQ_API_KEY para análise detalhada em tempo real.")
    
    return "\n".join(response)

def _get_smart_fallback_response(self, messages):
    """Resposta fallback inteligente"""
    user_message = self._get_last_user_message(messages).lower()
    
    if 'erro' in user_message or 'error' in user_message:
        return "🔧 Vejo que você tem um erro. Para diagnóstico preciso, configure GROQ_API_KEY. Enquanto isso, verifique se as funções delete_dev_session não estão duplicadas entre chat_services.py e database.py."
    elif 'duplicad' in user_message:
        return "🔍 Para análise de duplicatas, configure GROQ_API_KEY. Verifique funções com mesmo nome em arquivos diferentes."
    else:
        return "💡 Olá! Sou o assistente técnico do seu sistema. Configure GROQ_API_KEY para análises detalhadas em tempo real."

def user_chat(self, messages, user_identifier="user"):
    """Chat natural para usuários comuns"""
    if not self.use_real_ia:
        return "👋 Olá! Como posso ajudar você hoje?"
    
    try:
        response = self.client.chat.completions.create(
            model="llama-3.1-8b-instant",
            messages=[
                {
                    "role": "system", 
                    "content": "Você é um assistente amigável e útil. Seja natural e responda de forma clara e direta."
                },
                {"role": "user", "content": messages[-1]["content"] if messages else "oi"}
            ],
            temperature=0.8,
            max_tokens=300,
            timeout=10,
        )
        return response.choices[0].message.content
        
    except Exception as e:
        return "👋 Olá! Em que posso ajudar?"

ia_service = IAService()
