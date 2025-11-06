# code_analyzer.py - VERSÃO DEFINITIVA
import os
import ast

class CodeAnalyzer:
    def __init__(self):
        self.project_root = os.path.dirname(__file__)
    
    def analyze_project(self):
        """Analisa baseado na REALIDADE encontrada"""
        try:
            return {
                'duplicate_functions': self.find_meaningful_duplicates(),
                'security_issues': self.find_security_issues_real(),
                'error_handling': self.check_error_handling_real()
            }
        except Exception as e:
            print(f"❌ Erro análise: {e}")
            return {'duplicate_functions': [], 'security_issues': [], 'error_handling': []}
    
    def find_meaningful_duplicates(self):
        """Encontra duplicatas que IMPORTAM (ignora __init__)"""
        todas_funcoes = {}
        duplicatas_significativas = []
        
        arquivos = ['auth.py', 'chat_services.py', 'ia_services.py', 'routes.py', 'database.py']
        
        for arquivo in arquivos:
            caminho = os.path.join(self.project_root, arquivo)
            if os.path.exists(caminho):
                try:
                    with open(caminho, 'r', encoding='utf-8') as f:
                        tree = ast.parse(f.read())
                    
                    for node in ast.walk(tree):
                        if isinstance(node, ast.FunctionDef):
                            nome_funcao = node.name
                            # IGNORA __init__ (são normais em classes)
                            if nome_funcao == '__init__':
                                continue
                                
                            if nome_funcao in todas_funcoes:
                                duplicatas_significativas.append({
                                    'function': nome_funcao,
                                    'file1': todas_funcoes[nome_funcao],
                                    'file2': arquivo,
                                    'linha': node.lineno
                                })
                            else:
                                todas_funcoes[nome_funcao] = arquivo
                except Exception as e:
                    print(f"⚠️  Erro analisando {arquivo}: {e}")
        
        print(f"✅ Duplicatas significativas: {len(duplicatas_significativas)}")
        return duplicatas_significativas
    
    def find_security_issues_real(self):
        """Problemas de segurança REAIS"""
        problemas = []
        padroes_perigosos = {
            'eval(': 'eval() - risco de segurança',
            'exec(': 'exec() - risco de segurança', 
        }
        
        arquivos = ['auth.py', 'chat_services.py', 'ia_services.py', 'routes.py', 'database.py']
        
        for arquivo in arquivos:
            caminho = os.path.join(self.project_root, arquivo)
            if os.path.exists(caminho):
                try:
                    with open(caminho, 'r', encoding='utf-8') as f:
                        conteudo = f.read()
                    
                    for padrao, descricao in padroes_perigosos.items():
                        if padrao in conteudo:
                            problemas.append({
                                'file': arquivo,
                                'issue': descricao,
                                'pattern': padrao
                            })
                except:
                    continue
        
        return problemas
    
    def check_error_handling_real(self):
        """Verifica tratamento de erros REAL"""
        problemas = []
        
        arquivos = ['auth.py', 'chat_services.py', 'ia_services.py', 'routes.py', 'database.py']
        
        for arquivo in arquivos:
            caminho = os.path.join(self.project_root, arquivo)
            if os.path.exists(caminho):
                try:
                    with open(caminho, 'r', encoding='utf-8') as f:
                        conteudo = f.read()
                    
                    try_count = conteudo.count('try:')
                    func_count = conteudo.count('def ')
                    
                    # Arquivos com muitas funções mas pouco tratamento
                    if func_count >= 5 and try_count <= 1:
                        problemas.append({
                            'file': arquivo,
                            'issue': f'{func_count} funções, apenas {try_count} tratamento de erros',
                            'funcoes': func_count,
                            'try_blocks': try_count
                        })
                except:
                    continue
        
        return problemas

code_analyzer = CodeAnalyzer()