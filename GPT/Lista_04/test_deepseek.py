# ia_services.py - CORRIGIDO
from openai import OpenAI
import os
from dotenv import load_dotenv

load_dotenv()

class IAService:
    def __init__(self):
        self.groq_key = os.environ.get("GROQ_API_KEY")
        self.deepseek_key = os.environ.get("DEEPSEEK_API_KEY")
        
    def dev_chat(self, messages):
        """IA para desenvolvedor (Groq - Gratuita)"""
        return self._groq_chat(messages, "llama-3.1-8b-instant")
    
    def user_chat(self, messages):
        """IA para usuário (Groq - Gratuita)""" 
        return self._groq_chat(messages, "llama-3.1-8b-instant")
    
    def _groq_chat(self, messages, model):
        try:
            client = OpenAI(
                api_key=self.groq_key,
                base_url="https://api.groq.com/openai/v1"
            )
            
            # Sistema message baseada no tipo
            if any("código" in msg.get("content", "").lower() for msg in messages if msg.get("role") == "user"):
                system_content = "Você é um expert em programação. Analise códigos, sugere melhorias, explica conceitos técnicos. Responda em português de forma detalhada."
            else:
                system_content = "Você é um assistente útil. Responda em português de forma clara e objetiva."
            
            system_msg = {"role": "system", "content": system_content}
            full_messages = [system_msg] + messages
            
            response = client.chat.completions.create(
                model=model,
                messages=full_messages,
                temperature=0.7,
                max_tokens=13107
            )
            return response.choices[0].message.content
            
        except Exception as e:
            return f"❌ Erro na IA: {str(e)}"

# Teste rápido CORRIGIDO
if __name__ == "__main__":
    service = IAService()
    
    # Teste Dev
    print("🧪 Testando IA Dev...")
    dev_result = service.dev_chat([
        {"role": "user", "content": "Analise este código Python: def soma(a,b): return a+b"}
    ])
    print("🔧 IA Dev:", dev_result)
    print("\n" + "="*50 + "\n")
    
    # Teste User
    print("🧪 Testando IA User...")
    user_result = service.user_chat([
        {"role": "user", "content": "Como faço para criar uma nova página no sistema?"}
    ])
    print("🤖 IA User:", user_result)