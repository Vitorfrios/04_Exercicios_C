class DevWidget {
    constructor() {
        this.isOpen = false;
        this.isAuthenticated = false;
        this.currentSessionId = null;
        this.sessions = [];
        this.token = localStorage.getItem('dev_token');
        this.user = JSON.parse(localStorage.getItem('dev_user') || 'null');
        this.responseHandler = new ResponseHandler();
        this.analysisTools = new AnalysisTools();
        this.conversationHistory = []; // ✅ NOVO: Histórico da conversa
        
        this.init();
    }
    
    init() {
        this.createWidget();
        this.bindEvents();
        
        if (this.token && this.user) {
            this.checkAuthentication();
        }
        
        console.log('✅ Widget Dev carregado com melhorias técnicas');
    }
    
    createWidget() {
        const widgetBtn = document.createElement('button');
        widgetBtn.id = 'devWidgetBtn';
        widgetBtn.className = 'widget-btn';
        widgetBtn.innerHTML = '🔧';
        widgetBtn.title = 'Dev Assistant';
        
        const widgetWindow = document.createElement('div');
        widgetWindow.id = 'devWidgetWindow';
        widgetWindow.className = 'widget-window widget-hidden';
        
        widgetWindow.innerHTML = `
            <div class="dev-container">
                <div class="dev-sidebar">
                    <div class="dev-sessions" id="devSessions"></div>
                    <button class="new-session-btn" id="newSessionBtn">+ Novo</button>
                </div>
                <div class="dev-main">
                    <div class="dev-header">
                        <h3>Assistente Dev</h3>
                        <button class="close-btn">&times;</button>
                    </div>
                    <div class="dev-content" id="devContent"></div>
                </div>
            </div>
        `;
        
        document.body.appendChild(widgetBtn);
        document.body.appendChild(widgetWindow);
        
        this.elements = {
            btn: widgetBtn,
            window: widgetWindow,
            sidebar: document.getElementById('devSessions'),
            content: document.getElementById('devContent'),
            closeBtn: widgetWindow.querySelector('.close-btn'),
            newSessionBtn: document.getElementById('newSessionBtn')
        };
        
        this.showAuthScreen();
    }
    
    bindEvents() {
        this.elements.btn.addEventListener('click', () => this.toggleWidget());
        this.elements.closeBtn.addEventListener('click', () => this.closeWidget());
        this.elements.newSessionBtn.addEventListener('click', () => this.createNewSession());
    }
    
    async checkAuthentication() {
        try {
            const response = await fetch('/api/dev/sessions', {
                headers: {
                    'Authorization': `Bearer ${this.token}`
                }
            });
            
            if (response.ok) {
                this.isAuthenticated = true;
                this.loadSessions();
            } else {
                this.logout();
            }
        } catch (error) {
            console.error('Erro verificação auth:', error);
            this.logout();
        }
    }
    
    showAuthScreen() {
        this.elements.content.innerHTML = `
            <div class="dev-auth">
                <h3 style="text-align: center; margin-bottom: 16px; color: var(--text-color);">Login Dev</h3>
                <input type="text" id="devUsername" class="auth-input" placeholder="Usuário" value="admin">
                <input type="password" id="devPassword" class="auth-input" placeholder="Senha" value="admin123">
                <button id="devLoginBtn" class="auth-btn">Entrar</button>
                <div style="font-size: 12px; color: var(--secondary-color); text-align: center; margin-top: 12px;">
                    Credenciais padrão: admin / admin123
                </div>
                <div id="authMessage"></div>
            </div>
        `;
        
        document.getElementById('devLoginBtn').addEventListener('click', () => this.login());
        document.getElementById('devPassword').addEventListener('keypress', (e) => {
            if (e.key === 'Enter') this.login();
        });
    }
    
    async login() {
        const username = document.getElementById('devUsername').value;
        const password = document.getElementById('devPassword').value;
        const authMessage = document.getElementById('authMessage');
        
        if (!username || !password) {
            this.showMessage(authMessage, 'Preencha todos os campos', 'error');
            return;
        }
        
        try {
            const response = await fetch('/api/dev/login', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({ username, password })
            });
            
            const data = await response.json();
            
            if (response.ok) {
                this.token = data.token;
                this.user = data.user;
                this.isAuthenticated = true;
                
                localStorage.setItem('dev_token', this.token);
                localStorage.setItem('dev_user', JSON.stringify(this.user));
                
                this.showMessage(authMessage, 'Login realizado!', 'success');
                setTimeout(() => {
                    this.loadSessions();
                }, 1000);
                
            } else {
                this.showMessage(authMessage, data.detail || 'Erro no login', 'error');
            }
            
        } catch (error) {
            this.showMessage(authMessage, 'Erro de conexão', 'error');
            console.error('Erro login:', error);
        }
    }
    
    logout() {
        this.isAuthenticated = false;
        this.token = null;
        this.user = null;
        this.sessions = [];
        this.currentSessionId = null;
        
        localStorage.removeItem('dev_token');
        localStorage.removeItem('dev_user');
        
        this.showAuthScreen();
    }
    
    async loadSessions() {
        try {
            const response = await fetch('/api/dev/sessions', {
                headers: {
                    'Authorization': `Bearer ${this.token}`
                }
            });
            
            if (response.ok) {
                const data = await response.json();
                this.sessions = data.sessions;
                this.renderSessions();
                
                if (this.sessions.length > 0 && !this.currentSessionId) {
                    this.selectSession(this.sessions[0].id);
                } else if (this.sessions.length === 0) {
                    this.showEmptyState();
                }
            } else {
                this.logout();
            }
        } catch (error) {
            console.error('Erro carregar sessões:', error);
        }
    }
    
    renderSessions() {
        this.elements.sidebar.innerHTML = '';
        
        this.sessions.forEach(session => {
            const sessionEl = document.createElement('div');
            sessionEl.className = `session-item ${session.id === this.currentSessionId ? 'session-active' : ''}`;
            sessionEl.innerHTML = `
                <div class="session-content">
                    <div class="session-title">${session.title}</div>
                    <div class="session-date">${new Date(session.last_interaction).toLocaleDateString()}</div>
                </div>
                <button class="delete-session-btn" data-session-id="${session.id}" title="Deletar chat">
                    🗑️
                </button>
            `;
            
            // Clique para selecionar sessão
            sessionEl.querySelector('.session-content').addEventListener('click', () => this.selectSession(session.id));
            
            // Clique para deletar sessão
            sessionEl.querySelector('.delete-session-btn').addEventListener('click', (e) => {
                e.stopPropagation(); // Impede que clique no botão selecione a sessão
                this.deleteSession(session.id, session.title);
            });
            
            this.elements.sidebar.appendChild(sessionEl);
        });
        
        // Adiciona botão para deletar todas as sessões
        if (this.sessions.length > 0) {
            const deleteAllBtn = document.createElement('button');
            deleteAllBtn.className = 'delete-all-btn';
            deleteAllBtn.innerHTML = '🗑️ Deletar Todos';
            deleteAllBtn.addEventListener('click', () => this.deleteAllSessions());
            this.elements.sidebar.appendChild(deleteAllBtn);
        }
    }
    
    async deleteSession(sessionId, sessionTitle) {
        if (!confirm(`Tem certeza que deseja deletar o chat "${sessionTitle}"?`)) {
            return;
        }
        
        try {
            const response = await fetch(`/api/dev/sessions/${sessionId}`, {
                method: 'DELETE',
                headers: {
                    'Authorization': `Bearer ${this.token}`
                }
            });
            
            if (response.ok) {
                const data = await response.json();
                console.log('✅ Sessão deletada:', data.message);
                
                // Recarrega a lista de sessões
                await this.loadSessions();
                
                // Se era a sessão atual, mostra estado vazio
                if (this.currentSessionId === sessionId) {
                    this.currentSessionId = null;
                    this.showEmptyState();
                }
            } else {
                throw new Error('Erro ao deletar sessão');
            }
        } catch (error) {
            console.error('❌ Erro ao deletar sessão:', error);
            alert('Erro ao deletar sessão. Tente novamente.');
        }
    }
    
    async deleteAllSessions() {
        if (!confirm('Tem certeza que deseja deletar TODOS os chats? Esta ação não pode ser desfeita.')) {
            return;
        }
        
        try {
            const response = await fetch('/api/dev/sessions', {
                method: 'DELETE',
                headers: {
                    'Authorization': `Bearer ${this.token}`
                }
            });
            
            if (response.ok) {
                const data = await response.json();
                console.log('✅ Todas as sessões deletadas:', data.message);
                
                // Limpa estado atual
                this.sessions = [];
                this.currentSessionId = null;
                
                // Recarrega a interface
                this.renderSessions();
                this.showEmptyState();
            } else {
                throw new Error('Erro ao deletar sessões');
            }
        } catch (error) {
            console.error('❌ Erro ao deletar sessões:', error);
            alert('Erro ao deletar sessões. Tente novamente.');
        }
    }

    
    async selectSession(sessionId) {
        this.currentSessionId = sessionId;
        this.renderSessions();
        await this.loadSessionMessages(sessionId);
    }
    
    async loadSessionMessages(sessionId) {
        try {
            const response = await fetch(`/api/dev/sessions/${sessionId}/messages`, {
                headers: {
                    'Authorization': `Bearer ${this.token}`
                }
            });
            
            if (response.ok) {
                const data = await response.json();
                this.showChatInterface(data.messages);
            }
        } catch (error) {
            console.error('Erro carregar mensagens:', error);
        }
    }
    
    addMessage(role, content) {
        if (!this.elements.devMessages) {
            console.error('devMessages não está definido');
            return;
        }
        
        const messageDiv = document.createElement('div');
        messageDiv.className = `message ${role === 'dev' ? 'user-message' : 'ia-message'}`;
        
        // Processa o conteúdo para manter formatação
        const processedContent = this.responseHandler.cleanResponse(content);
        messageDiv.innerHTML = processedContent;
        
        this.elements.devMessages.appendChild(messageDiv);
        this.scrollToBottom();
        this.checkScrollable();
    }
    
    async analyzeCode() {
        try {
            this.addMessage('dev', '🔍 Analisando código do projeto...');
            
            const response = await fetch('/api/dev/analyze-code', {
                headers: {
                    'Authorization': `Bearer ${this.token}`
                }
            });
            
            if (response.ok) {
                const data = await response.json();
                
                if (data.issues) {
                    data.issues.forEach(issue => {
                        this.addMessage('ia', issue);
                    });
                    
                    // Adiciona botões de ação após análise
                    this.addActionTools();
                } else if (data.error) {
                    this.addMessage('ia', `❌ ${data.error}`);
                }
            }
        } catch (error) {
            this.addMessage('ia', '❌ Erro na análise de código');
        }
    }
    
    addActionTools() {
        const toolsContainer = document.createElement('div');
        toolsContainer.className = 'action-tools';
        toolsContainer.style.cssText = `
            display: flex;
            gap: 8px;
            margin: 12px 0;
            flex-wrap: wrap;
            justify-content: center;
        `;
        
        const tools = [
            { label: '📊 Análise Detalhada', action: 'detailed_analysis' },
            { label: '🐛 Debug', action: 'debug' },
            { label: '📝 Exemplo Prático', action: 'practical_example' },
            { label: '🔍 Performance', action: 'performance' }
        ];
        
        tools.forEach(tool => {
            const button = document.createElement('button');
            button.className = 'tech-tool-btn';
            button.textContent = tool.label;
            button.onclick = () => this.handleTechnicalTool(tool.action);
            toolsContainer.appendChild(button);
        });
        
        this.elements.devMessages.appendChild(toolsContainer);
    }

    showChatInterface(messages = []) {
        this.elements.content.innerHTML = `
            <div class="dev-messages" id="devMessages">
                ${messages.map(msg => `
                    <div class="message ${msg.role === 'dev' ? 'user-message' : 'ia-message'}">
                        ${this.escapeHtml(msg.content)}
                    </div>
                `).join('')}
            </div>
            <div class="dev-input-area">
                <div class="dev-toolbar">
                    <button class="tool-btn analyze" onclick="devWidget.analyzeCode()">
                        🔍 Analisar Código
                    </button>
                    <button class="tool-btn delete" onclick="devWidget.deleteCurrentSession()">
                        🗑️ Deletar Este Chat
                    </button>
                </div>
                <div class="dev-input-group">
                    <textarea 
                        id="devMessageInput" 
                        placeholder="Ex: Como corrigir funções duplicadas?"
                        rows="1"
                    ></textarea>
                    <button id="devSendBtn">Enviar</button>
                </div>
            </div>
        `;
        
        this.bindChatEvents();
        this.scrollToBottom();
        
        // Adiciona botões de ação se já houver mensagens
        if (messages.length > 0) {
            setTimeout(() => this.addActionTools(), 100);
        }
    }

    async deleteCurrentSession() {
        if (!this.currentSessionId) return;
        
        const currentSession = this.sessions.find(s => s.id === this.currentSessionId);
        if (currentSession) {
            await this.deleteSession(this.currentSessionId, currentSession.title);
        }
    }

    checkScrollable() {
        if (this.elements.devMessages) {
            const messages = this.elements.devMessages;
            const isScrollable = messages.scrollHeight > messages.clientHeight;
            
            if (isScrollable) {
                messages.classList.add('scrollable');
            } else {
                messages.classList.remove('scrollable');
            }
        }
    }

    escapeHtml(unsafe) {
        return unsafe
            .replace(/&/g, "&amp;")
            .replace(/</g, "&lt;")
            .replace(/>/g, "&gt;")
            .replace(/"/g, "&quot;")
            .replace(/'/g, "&#039;");
    }

    bindChatEvents() {
        const input = document.getElementById('devMessageInput');
        const sendBtn = document.getElementById('devSendBtn');
        const messagesContainer = document.getElementById('devMessages');
        
        input.addEventListener('input', function() {
            this.style.height = 'auto';
            this.style.height = Math.min(this.scrollHeight, 120) + 'px';
            sendBtn.disabled = !this.value.trim();
        });
        
        sendBtn.addEventListener('click', () => this.sendDevMessage());
        
        input.addEventListener('keydown', (e) => {
            if (e.key === 'Enter' && !e.shiftKey) {
                e.preventDefault();
                if (!sendBtn.disabled) {
                    this.sendDevMessage();
                }
            }
        });
        
        this.elements.devMessages = messagesContainer;
        this.elements.devInput = input;
        this.elements.devSendBtn = sendBtn;
    }
    
    async sendDevMessage() {
        const message = this.elements.devInput.value.trim();
        if (!message || !this.currentSessionId) return;
        
        await this.sendSmartMessage(message);
        
        // Limpa input
        this.elements.devInput.value = '';
        this.elements.devInput.style.height = 'auto';
        this.elements.devSendBtn.disabled = true;
    }
    
    handleTechnicalTool(action) {
        // ✅ Mensagens mais conversacionais
        const actionMessages = {
            'detailed_analysis': '🔍 Vamos fazer uma análise técnica detalhada. Em que aspecto específico você gostaria de se aprofundar?',
            'debug': '🐛 Vamos examinar o código em busca de problemas. Tem alguma área específica em mente?',
            'practical_example': '📝 Vamos criar um exemplo prático juntos. Qual funcionalidade você gostaria de ver implementada?',
            'performance': '⚡ Vamos analisar a performance do sistema. Qual métrica ou componente te preocupa mais?'
        };
        
        const message = actionMessages[action] || 'Vamos explorar isso juntos. Por onde quer começar?';
        this.sendSmartMessage(message, action);
    }

    async sendSmartMessage(message, actionType = null) {
        if (!this.currentSessionId) return;
        
        this.addMessage('dev', message);
        this.showDevTypingIndicator();
        
        try {
            const payload = {
                session_id: this.currentSessionId,
                content: message
            };
            
            if (actionType) {
                payload.action_type = actionType;
            }
            
            const response = await fetch('/api/dev/send-message', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${this.token}`
                },
                body: JSON.stringify(payload)
            });
            
            if (response.ok) {
                const data = await response.json();
                this.hideDevTypingIndicator();
                this.addMessage('ia', data.response);
                
                // ✅ ADICIONADO: Botão de continuidade após resposta
                this.addContinuationPrompt(data.response, actionType);
                
            } else {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            
        } catch (error) {
            this.hideDevTypingIndicator();
            this.addMessage('ia', '❌ Erro de conexão');
            console.error('Erro sendSmartMessage:', error);
        }
    }

    addContinuationPrompt(aiResponse, actionType) {
        // ✅ NOVO: Adiciona prompts de continuidade baseados no contexto
        const continuationPrompts = {
            'detailed_analysis': [
                '📊 Quer analisar outro componente?',
                '🔍 Focar em segurança ou performance?',
                '📈 Explorar métricas específicas?'
            ],
            'debug': [
                '🐛 Verificar outro arquivo?',
                '🔧 Testar uma solução diferente?',
                '📝 Implementar os fixes sugeridos?'
            ],
            'practical_example': [
                '🚀 Evoluir este exemplo?',
                '💡 Ver uma abordagem alternativa?',
                '🔍 Adicionar mais funcionalidades?'
            ],
            'performance': [
                '⚡ Otimizar outro aspecto?',
                '📊 Medir impacto das mudanças?',
                '🔍 Analisar consumo de recursos?'
            ]
        };

        // Só adiciona se a resposta não já tiver engajamento
        if (!aiResponse.includes('?') && !aiResponse.includes('Quer') && !aiResponse.includes('Vamos')) {
            const prompts = continuationPrompts[actionType] || [
                '💭 Como posso ajudar ainda mais?',
                '🚀 Quer explorar outro aspecto?',
                '🔍 Tem alguma dúvida específica?'
            ];
            
            // Adiciona após um delay
            setTimeout(() => {
                const promptContainer = document.createElement('div');
                promptContainer.className = 'continuation-prompt';
                promptContainer.innerHTML = `
                    <div class="prompt-text">${prompts[0]}</div>
                    <div class="prompt-buttons">
                        <button class="prompt-btn" onclick="devWidget.quickResponse('${prompts[0]}')">Sim</button>
                        <button class="prompt-btn" onclick="this.parentElement.parentElement.remove()">Agora não</button>
                    </div>
                `;
                this.elements.devMessages.appendChild(promptContainer);
                this.scrollToBottom();
            }, 1000);
        }
    }

    quickResponse(prompt) {
        // ✅ NOVO: Resposta rápida aos prompts de continuidade
        this.sendSmartMessage(prompt);
        
        // Remove o prompt
        const promptElement = this.elements.devMessages.querySelector('.continuation-prompt');
        if (promptElement) {
            promptElement.remove();
        }
    }
    
    updateConversationHistory(userMessage, aiResponse) {
        // ✅ Mantém um histórico limpo da conversa
        this.conversationHistory.push(
            { role: 'user', content: userMessage },
            { role: 'assistant', content: aiResponse }
        );
        
        // Limita o histórico para não ficar muito grande
        if (this.conversationHistory.length > 20) {
            this.conversationHistory = this.conversationHistory.slice(-20);
        }
    }
    
    getConversationContext() {
        // ✅ Retorna o histórico formatado para contexto
        if (this.conversationHistory.length === 0) {
            return [];
        }
        
        // Pega apenas as últimas 6 mensagens para contexto
        return this.conversationHistory.slice(-6);
    }



    getCurrentContext() {
        const mensagens = this.elements.devMessages?.querySelectorAll('.message') || [];
        const ultimasMensagens = Array.from(mensagens).slice(-4); // Últimas 4 mensagens
        
        if (ultimasMensagens.length === 0) return "o sistema atual";
        
        const contexto = ultimasMensagens.map(msg => {
            const isUser = msg.classList.contains('user-message');
            const texto = msg.textContent.substring(0, 80);
            return `${isUser ? 'Pergunta' : 'Resposta'}: ${texto}${texto.length === 80 ? '...' : ''}`;
        }).join(' | ');
        
        return contexto;
    }
    
    showDevTypingIndicator() {
        const typingDiv = document.createElement('div');
        typingDiv.id = 'devTypingIndicator';
        typingDiv.className = 'typing-indicator';
        typingDiv.innerHTML = `
            IA analisando...
            <div class="typing-dot"></div>
            <div class="typing-dot"></div>
            <div class="typing-dot"></div>
        `;
        
        this.elements.devMessages.appendChild(typingDiv);
        this.scrollToBottom();
    }
    
    hideDevTypingIndicator() {
        const typingIndicator = document.getElementById('devTypingIndicator');
        if (typingIndicator) {
            typingIndicator.remove();
        }
    }
    
    async createNewSession() {
        try {
            const response = await fetch('/api/dev/sessions', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${this.token}`
                },
                body: JSON.stringify({
                    title: `Chat ${new Date().toLocaleTimeString()}`,
                    session_type: 'code_analysis'
                })
            });
            
            if (response.ok) {
                const data = await response.json();
                await this.loadSessions();
                this.selectSession(data.session.id);
            }
        } catch (error) {
            console.error('Erro criar sessão:', error);
        }
    }
    
    showEmptyState() {
        this.elements.content.innerHTML = `
            <div class="empty-state">
                <div style="font-size: 48px; margin-bottom: 16px;">💬</div>
                <h3>Nenhum chat ainda</h3>
                <p style="margin: 8px 0 16px 0;">Comece uma nova conversa técnica</p>
                <button class="auth-btn" onclick="devWidget.createNewSession()">Criar Primeiro Chat</button>
            </div>
        `;
    }
    
    showMessage(element, message, type) {
        element.innerHTML = `<div class="${type}-message">${message}</div>`;
    }
    
    scrollToBottom() {
        if (this.elements.devMessages) {
            setTimeout(() => {
                this.elements.devMessages.scrollTop = this.elements.devMessages.scrollHeight;
            }, 50);
        }
    }
    
    toggleWidget() {
        this.isOpen = !this.isOpen;
        
        if (this.isOpen) {
            this.elements.window.classList.remove('widget-hidden');
            this.elements.window.classList.add('widget-visible');
            
            if (this.isAuthenticated && this.elements.devInput) {
                this.elements.devInput.focus();
            }
        } else {
            this.closeWidget();
        }
    }
    
    closeWidget() {
        this.isOpen = false;
        this.elements.window.classList.remove('widget-visible');
        this.elements.window.classList.add('widget-hidden');
    }
}

// Instância global
let devWidget;

// Inicializa quando a página carregar
document.addEventListener('DOMContentLoaded', () => {
    devWidget = new DevWidget();
});