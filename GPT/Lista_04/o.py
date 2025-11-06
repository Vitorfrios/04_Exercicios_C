import os

# Estrutura do projeto
estrutura = {
    "chat_system": [
        "app.py",
        "config.py",
        "database.py",
        "ia_services.py",
        "auth.py",
        "chat_services.py",
        "routes.py",
        "requirements.txt",
        ".env",
        "static/css/widgets.css",
        "static/js/user-widget.js",
        "static/js/dev-widget.js",
        "templates/base.html",
    ]
}

# Criação das pastas e arquivos
for pasta_raiz, caminhos in estrutura.items():
    for caminho in caminhos:
        caminho_completo = os.path.join(pasta_raiz, caminho)
        os.makedirs(os.path.dirname(caminho_completo), exist_ok=True)
        with open(caminho_completo, "w") as f:
            if caminho.endswith(".py"):
                f.write("# " + os.path.basename(caminho) + "\n")
            elif caminho == "requirements.txt":
                f.write("# dependências do projeto\n")
            elif caminho == ".env":
                f.write("GROQ_API_KEY=\n")
            else:
                f.write("")
print("✅ Estrutura criada com sucesso!")
