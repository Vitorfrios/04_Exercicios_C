# ia_services.py - CORRIGIDO
import os
import re
from openai import OpenAI
from dotenv import load_dotenv

load_dotenv()

class IAService:
    def __init__(self):
        self.groq_key = os.environ.get("GROQ_API_KEY")
        self.use_real_ia = bool(self.groq_key)
        self.conversation_threads = {}  # ✅ Threads de conversação por usuário
        
        if self.use_real_ia:
            self.client = OpenAI(
                api_key=self.groq_key,
                base_url="https://api.groq.com/openai/v1"
            )
            print("✅ IA Groq - Conversação Contínua Ativa")
        else:
            print("⚠️  Modo MOCK - Conversação Contínua")

    def dev_chat(self, messages, user_id="dev", action_type=None):
        """Chat Dev com conversação contínua - MELHORADO"""
        # ✅ Mantém thread de conversação
        thread_id = f"dev_{user_id}"
        if thread_id not in self.conversation_threads:
            self.conversation_threads[thread_id] = []
        
        # Adiciona nova mensagem ao thread
        if messages:
            self.conversation_threads[thread_id].extend(messages[-2:])  # Mantém últimas 2
        
        # Limita o tamanho do thread
        if len(self.conversation_threads[thread_id]) > 20:
            self.conversation_threads[thread_id] = self.conversation_threads[thread_id][-20:]
        
        # Busca análise REAL do código
        from code_analyzer import code_analyzer
        analise_real = code_analyzer.analyze_project()
        
        # Prepara contexto inteligente
        contexto_acao = self._get_continuous_context(action_type, messages, analise_real, thread_id)
        
        system_context = f"""
        VOCÊ É UM ENGENHEIRO ESPECIALISTA EM CONVERSAÇÕES TÉCNICAS CONTÍNUAS.

        CONTEXTO DO SISTEMA:
        {self._format_real_analysis(analise_real)}

        {contexto_acao}

        SEU ESTILO DE CONVERSA:
        - Mantenha a conversa fluida e contínua
        - Não "feche" os tópicos - sempre permita continuação
        - Use perguntas retóricas para engajar
        - Ofereça aprofundamento natural
        - Seja técnico mas acessível

        EXEMPLOS DE RESPOSTAS CONTÍNUAS:
        "Analisando esse aspecto mais a fundo..." 
        "Quer que eu detalhe alguma parte específica?"
        "Vamos explorar isso melhor..."
        "Algum ponto em particular você gostaria de expandir?"

        EVITE:
        - "Passo 1, 2, 3..." (muito robótico)
        - Encerrar tópicos abruptamente
        - Listas muito longas sem engajamento
        """

        # Usa o thread completo para contexto
        full_messages = self.conversation_threads[thread_id].copy()
        
        return self._continuous_groq_chat(full_messages, system_context, action_type)

    def _get_continuous_context(self, action_type, messages, analise_real, thread_id):
        """Contexto para conversação contínua - MELHORADO"""
        if not action_type:
            return "Continue a conversa naturalmente, permitindo aprofundamento nos tópicos."
        
        # Verifica se é continuação de ação anterior
        last_action = getattr(self, f'_last_action_{thread_id}', None)
        setattr(self, f'_last_action_{thread_id}', action_type)

        
        action_contexts = {
            "detailed_analysis": f"""
            CONTINUAÇÃO DA ANÁLISE DETALHADA:
            {f'Continuação do tópico anterior: {last_action}' if last_action == 'detailed_analysis' else 'Iniciando análise detalhada...'}
            
            Mantenha a análise fluida e aprofundável. 
            Convide para explorar aspectos específicos.
            Ofereça diferentes ângulos de análise.
            """,
            
            "debug": f"""
            CONTINUAÇÃO DO DEBUG:
            {f'Continuando debug do problema anterior' if last_action == 'debug' else 'Iniciando análise de debug...'}
            
            Explore os problemas de forma conversacional.
            Peça mais contexto se necessário.
            Sugira próximos passos naturalmente.
            """,
            
            "practical_example": f"""
            CONTINUAÇÃO DO EXEMPLO PRÁTICO:
            {f'Expandindo o exemplo anterior' if last_action == 'practical_example' else 'Criando exemplo prático...'}
            
            Desenvolva o exemplo de forma incremental.
            Peça feedback sobre a implementação.
            Ofereça variações do exemplo.
            """,
            
            "performance": f"""
            CONTINUAÇÃO DA ANÁLISE DE PERFORMANCE:
            {f'Aprofundando análise de performance' if last_action == 'performance' else 'Iniciando análise de performance...'}
            
            Explore métricas de forma conversacional.
            Compare diferentes abordagens.
            Peça contexto sobre casos de uso específicos.
            """
        }
        
        return action_contexts.get(action_type, "Continue a conversa técnica de forma natural.")

    def _continuous_groq_chat(self, messages, system_context, action_type):
        """Chat com foco em continuidade - NOVO"""
        if not self.use_real_ia:
            return self._continuous_mock_response(messages, system_context, action_type)
        
        try:
            system_msg = {"role": "system", "content": system_context}
            full_messages = [system_msg] + messages
            
            response = self.client.chat.completions.create(
                model="llama-3.1-8b-instant",
                messages=full_messages,
                temperature=0.7,  # Mais criativo para conversação
                max_tokens=600,
                timeout=15
            )
            
            content = response.choices[0].message.content
            return self._format_continuous_response(content, action_type)
            
        except Exception as e:
            print(f"❌ Erro Groq: {e}")
            return self._continuous_mock_response(messages, system_context, action_type)

    def _format_continuous_response(self, text, action_type):
        """Formata resposta para incentivar continuidade - NOVO"""
        if not text:
            return "Gostaria de explorar mais algum aspecto específico?"
        
        # Remove fechamentos muito definitivos
        text = re.sub(r'(em conclusão|finalmente|para resumir|em suma)[^.!?]*[.!?]', '', text, flags=re.IGNORECASE)
        
        # Adiciona engajamento se a resposta for muito "fechada"
        if not any(word in text.lower() for word in ['?', 'quer', 'gostaria', 'vamos', 'explorar', 'detalhar']):
            engagement_phrases = [
                "\n\nO que achou dessa abordagem?",
                "\n\nQuer que eu detalhe algum ponto específico?",
                "\n\nVamos explorar isso mais a fundo?",
                "\n\nAlguma parte em particular te interessa mais?"
            ]
            
            import random
            text += random.choice(engagement_phrases)
        
        # Limpa HTML
        text = re.sub(r'</?strong>', '**', text)
        text = re.sub(r'</?code>', '`', text)
        text = re.sub(r'<[^>]+>', '', text)
        
        return text

    def _continuous_mock_response(self, messages, system_context, action_type):
        """Mock responses que incentivam continuidade - MELHORADO"""
        last_msg = messages[-1]['content'].lower() if messages else ""
        
        if "dev" in system_context.lower():
            continuous_responses = {
                "detailed_analysis": [
                    "🔍 **Análise em Andamento:** Identifiquei alguns padrões interessantes na arquitetura. Quer que eu foque em algum componente específico como o sistema de autenticação ou a estrutura do banco?",
                    
                    "📊 **Profundizando Análise:** Analisando o tratamento de erros, vejo oportunidades em auth.py. Como você lida atualmente com falhas de autenticação? Podemos explorar isso.",
                    
                    "🔄 **Continuação da Análise:** Vamos olhar para a performance das queries SQLite? Ou prefere focar na escalabilidade da API? Me diga qual aspecto te interessa mais."
                ],
                
                "debug": [
                    "🐛 **Debug Contínuo:** Encontrei alguns pontos de melhoria no tratamento de exceções. Quer que eu mostre como implementar logs mais detalhados?",
                    
                    "🔧 **Aprofundando Debug:** Analisando o fluxo de autenticação, há oportunidades para melhorar a validação. Como você monitora tentativas de login atualmente?",
                    
                    "⚡ **Debug em Progresso:** Vamos examinar o consumo de memória do sistema? Ou prefere focar em otimização de consultas? Me oriente sobre sua prioridade."
                ],
                
                "practical_example": [
                    "📝 **Exemplo Expandido:** Aqui está uma implementação básica. Quer que eu adicione tratamento de erros ou prefere ver uma versão com cache?",
                    
                    "🚀 **Desenvolvendo Exemplo:** Vamos evoluir esse código juntos? Posso mostrar como adicionar logging, métricas ou testes unitários. O que te interessa?",
                    
                    "💡 **Exemplo em Camadas:** Esta é a versão simples. Quer ver como escalar para produção com rate limiting e monitoramento?"
                ],
                
                "performance": [
                    "⚡ **Análise de Performance Contínua:** Identifiquei oportunidades em consultas SQL. Quer que eu mostre como adicionar índices ou prefere otimização de conexões?",
                    
                    "📈 **Métricas em Foco:** Vamos explorar métricas específicas? Posso ajudar com monitoramento de tempo de resposta, throughput ou uso de recursos. Qual sua necessidade?",
                    
                    "🔍 **Performance Profunda:** Analisando o sistema, vejo potencial em cache. Quer implementar cache em memória ou prefere focar em otimização de algoritmos?"
                ]
            }
            
            import random
            responses = continuous_responses.get(action_type, [
                "💭 Interessante! Como posso ajudar você a explorar isso mais a fundo?",
                "🔍 Vamos continuar essa análise? Em que aspecto específico você gostaria de se aprofundar?",
                "🚀 Ótimo ponto! Quer que eu detalhe alguma parte específica ou explore uma abordagem diferente?"
            ])
            
            return random.choice(responses)
        else:
            # Respostas contínuas para usuário
            return "🤖 Como posso continuar ajudando você? Tem alguma dúvida específica ou quer explorar outra funcionalidade?"
    def user_chat(self, messages, user_id="user"):
        """Chat Usuário Inteligente - CORRIGIDO"""
        system_context = """
        VOCÊ É UM ASSISTENTE DO CHAT SYSTEM.

        SOBRE ESTE SISTEMA:
        - Site de chat com IA gratuita
        - Dois widgets: 💬 (ajuda geral) e 🔧 (análise técnica)
        - Desenvolvido com FastAPI, SQLite e JavaScript
        - IA integrada com Groq API

        SUAS FUNÇÕES:
        - Explicar como o sistema funciona
        - Ajudar a usar os recursos disponíveis
        - Responder perguntas técnicas básicas
        - Direcionar para análise técnica quando necessário

        CREDENCIAIS DEV: admin / admin123

        ESTILO:
        - Respostas úteis e diretas (100-200 palavras)
        - Tom amigável e profissional
        - Use emojis moderadamente
        - Ofereça ajuda adicional
        """

        return self._smart_groq_chat(messages, system_context)

    def _get_smart_action_context(self, action_type, messages, analise_real):
        """Gera contexto inteligente para ações - CORRIGIDO"""
        if not action_type:
            return "Forneça ajuda técnica geral baseada na conversa."
        
        # Pega a última mensagem do usuário para contexto
        ultima_user_msg = ""
        for msg in reversed(messages):
            if msg['role'] == 'user':
                ultima_user_msg = msg['content']
                break
        
        action_contexts = {
            "detailed_analysis": f"""
            O usuário solicitou uma ANÁLISE DETALHADA.
            
            Contexto da conversa: {ultima_user_msg[:200] if ultima_user_msg else "Conversa geral"}
            
            Forneça uma análise técnica aprofundada incluindo:
            - Arquitetura e estrutura do código
            - Problemas identificados na análise real
            - Recomendações de melhoria
            - Impacto nas funcionalidades
            """,
            
            "debug": f"""
            O usuário solicitou DEBUG técnico.
            
            Contexto: {ultima_user_msg[:200] if ultima_user_msg else "Sistema geral"}
            
            Foque em:
            - Identificar e explicar possíveis bugs
            - Sugerir correções específicas
            - Melhorar tratamento de erros
            - Logs e monitoramento
            """,
            
            "practical_example": f"""
            O usuário solicitou um EXEMPLO PRÁTICO.
            
            Contexto: {ultima_user_msg[:200] if ultima_user_msg else "Implementação geral"}
            
            Forneça:
            - Código implementável e testável
            - Exemplo concreto relacionado ao contexto
            - Explicação passo a passo
            - Boas práticas aplicadas
            """,
            
            "performance": f"""
            O usuário solicitou análise de PERFORMANCE.
            
            Contexto: {ultima_user_msg[:200] if ultima_user_msg else "Otimização geral"}
            
            Analise:
            - Possíveis gargalos de performance
            - Otimizações específicas
            - Melhorias de consulta e cache
            - Métricas e monitoramento
            """
        }
        
        return action_contexts.get(action_type, "Forneça ajuda técnica geral.")

    def _format_real_analysis(self, analise):
        """Formata a análise real para contexto"""
        partes = []
        
        if analise['duplicate_functions']:
            for dup in analise['duplicate_functions'][:2]:
                if dup['function'] != '__init__':  # Ignora __init__
                    partes.append(f"🚨 {dup['function']} em {dup['file1']} e {dup['file2']}")
        
        if analise['error_handling']:
            for err in analise['error_handling'][:2]:
                partes.append(f"⚠️ {err['file']}: {err['issue']}")
        
        if analise['security_issues']:
            for sec in analise['security_issues'][:2]:
                partes.append(f"🔒 {sec['file']}: {sec['issue']}")
        
        return "\n".join(partes) if partes else "✅ Código estável"

    def _smart_groq_chat(self, messages, system_context):
        """Chat inteligente com fallback elegante - CORRIGIDO"""
        if not self.use_real_ia:
            return self._smart_mock_response(messages, system_context)
        
        try:
            system_msg = {"role": "system", "content": system_context}
            full_messages = [system_msg] + messages
            
            response = self.client.chat.completions.create(
                model="llama-3.1-8b-instant",
                messages=full_messages,
                temperature=0.3,
                max_tokens=800,
                timeout=15
            )
            
            content = response.choices[0].message.content
            return self._clean_response(content)
            
        except Exception as e:
            print(f"❌ Erro Groq: {e}")
            return self._smart_mock_response(messages, system_context)

    def _smart_mock_response(self, messages, system_context):
        """Resposta mock inteligente - CORRIGIDO"""
        ultima_msg = messages[-1]['content'].lower() if messages else ""
        
        if "dev" in system_context.lower():
            # Respostas mock melhoradas baseadas no contexto
            if "análise detalhada" in ultima_msg or "detailed_analysis" in str(messages):
                return "🔍 **Análise Detalhada:** O sistema mostra boa arquitetura. Melhore o tratamento de erros em auth.py. Configure GROQ_API_KEY para análise completa."
            
            elif "debug" in ultima_msg:
                return "🐛 **Debug:** Verifique funções sem tratamento de erro em auth.py. Logs ajudariam no monitoramento. Configure GROQ_API_KEY para debug detalhado."
            
            elif "exemplo prático" in ultima_msg or "practical_example" in str(messages):
                return "📝 **Exemplo Prático:** ```python\n# Melhoria em auth.py\ntry:\n    user = get_user(username)\nexcept Exception as e:\n    logger.error(f'Auth error: {e}')\n    return None\n```"
            
            elif "performance" in ultima_msg:
                return "⚡ **Performance:** SQLite é adequado para testes. Para produção, considere PostgreSQL. Otimize consultas frequentes."
            
            else:
                return "💡 Configure GROQ_API_KEY no .env para respostas técnicas completas e contextualizadas."
        else:
            # Respostas para usuário
            if "funcion" in ultima_msg or "como" in ultima_msg:
                return "🤖 Este é um sistema de chat com IA gratuita. Use 💬 para ajuda geral ou 🔧 para análise técnica (login: admin/admin123)."
            elif "ajuda" in ultima_msg or "help" in ultima_msg:
                return "💬 Posso ajudar! Este sistema permite conversar com IA. Para questões técnicas, use o widget 🔧."
            else:
                return "Olá! Sou o assistente deste sistema de chat. Como posso ajudar?"

    def _clean_response(self, text):
        """Limpa resposta mantendo qualidade"""
        if not text: 
            return "Resposta não disponível."
        
        # Remove HTML mas mantém formatação
        text = re.sub(r'</?strong>', '**', text)
        text = re.sub(r'</?code>', '`', text)
        text = re.sub(r'<[^>]+>', '', text)
        
        # Limita tamanho mas preserva estrutura
        if len(text) > 1000:
            paragraphs = text.split('\n\n')
            if len(paragraphs) > 3:
                text = '\n\n'.join(paragraphs[:3]) + "\n\n..."
        
        return text.strip()

# Instância global
ia_service = IAService()