# check_reality.py - CORRIGIDO
import os
import ast

def analisar_funcoes_reais():
    """Analisa as funções que REALMENTE existem no código"""
    # AGORA procura na pasta correta
    project_root = os.path.dirname(__file__)  # Já está em chat_system/
    
    funcoes_por_arquivo = {}
    
    arquivos = ['auth.py', 'chat_services.py', 'ia_services.py', 'routes.py', 'database.py', 'config.py', 'app.py']
    
    for arquivo in arquivos:
        caminho = os.path.join(project_root, arquivo)  # CORRIGIDO: não precisa de chat_system/
        if os.path.exists(caminho):
            try:
                with open(caminho, 'r', encoding='utf-8') as f:
                    conteudo = f.read()
                
                tree = ast.parse(conteudo)
                funcoes = []
                
                for node in ast.walk(tree):
                    if isinstance(node, ast.FunctionDef):
                        funcoes.append({
                            'nome': node.name,
                            'args': [arg.arg for arg in node.args.args],
                            'linha': node.lineno
                        })
                
                funcoes_por_arquivo[arquivo] = funcoes
                print(f"✅ {arquivo}: {[f['nome'] for f in funcoes]}")
                
            except Exception as e:
                print(f"⚠️  {arquivo}: Erro de análise - {e}")
        else:
            print(f"❌ {arquivo}: Arquivo não encontrado")
    
    return funcoes_por_arquivo

def encontrar_duplicatas_reais():
    """Encontra duplicatas REAIS baseado nos arquivos existentes"""
    funcoes_por_arquivo = analisar_funcoes_reais()
    todas_funcoes = {}
    duplicatas = []
    
    for arquivo, funcoes in funcoes_por_arquivo.items():
        for funcao in funcoes:
            nome = funcao['nome']
            if nome in todas_funcoes:
                duplicatas.append({
                    'funcao': nome,
                    'arquivo1': todas_funcoes[nome],
                    'arquivo2': arquivo,
                    'linha': funcao['linha']
                })
            else:
                todas_funcoes[nome] = arquivo
    
    print(f"\n🔍 DUPLICATAS ENCONTRADAS: {len(duplicatas)}")
    for dup in duplicatas:
        print(f"   🚨 {dup['funcao']}: {dup['arquivo1']} ↔ {dup['arquivo2']}")
    
    return duplicatas

if __name__ == "__main__":
    print("🔍 ANALISANDO REALIDADE DO CÓDIGO:")
    print("=" * 50)
    duplicatas = encontrar_duplicatas_reais()