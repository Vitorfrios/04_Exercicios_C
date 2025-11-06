// user-widget.js
class UserWidget {
    constructor() {
        this.isOpen = false;
        this.responseHandler = new ResponseHandler();
        this.init();
    }
    
    init() {
        this.createWidget();
        this.bindEvents();
        console.log('✅ Widget Usuário carregado com melhorias');
    }
    
    createWidget() {
        const widgetBtn = document.createElement('button');
        widgetBtn.id = 'userWidgetBtn';
        widgetBtn.className = 'widget-btn';
        widgetBtn.innerHTML = '💬';
        widgetBtn.title = 'Assistente Virtual';
        
        const widgetWindow = document.createElement('div');
        widgetWindow.id = 'userWidgetWindow';
        widgetWindow.className = 'widget-window widget-hidden';
        
        widgetWindow.innerHTML = `
            <div class="user-header">
                <h3>Assistente Virtual</h3>
                <button class="close-btn">&times;</button>
            </div>
            <div class="user-messages" id="userMessages"></div>
            <div class="user-input-area">
                <div class="user-input-group">
                    <input type="text" id="userMessageInput" placeholder="Digite sua mensagem...">
                    <button id="userSendBtn" disabled>Enviar</button>
                </div>
            </div>
        `;
        
        document.body.appendChild(widgetBtn);
        document.body.appendChild(widgetWindow);
        
        this.elements = {
            btn: widgetBtn,
            window: widgetWindow,
            messages: document.getElementById('userMessages'),
            input: document.getElementById('userMessageInput'),
            sendBtn: document.getElementById('userSendBtn'),
            closeBtn: widgetWindow.querySelector('.close-btn')
        };
    }
    
    bindEvents() {
        this.elements.btn.addEventListener('click', () => this.toggleWidget());
        this.elements.closeBtn.addEventListener('click', () => this.closeWidget());
        this.elements.sendBtn.addEventListener('click', () => this.sendUserMessage());
        
        this.elements.input.addEventListener('input', () => {
            this.elements.sendBtn.disabled = !this.elements.input.value.trim();
        });
        
        this.elements.input.addEventListener('keypress', (e) => {
            if (e.key === 'Enter' && !this.elements.sendBtn.disabled) {
                this.sendUserMessage();
            }
        });
    }
    
    async sendUserMessage() {
        const message = this.elements.input.value.trim();
        if (!message) return;
        
        this.addMessage('user', message);
        this.elements.input.value = '';
        this.elements.sendBtn.disabled = true;
        
        this.showTypingIndicator();
        
        try {
            const response = await this.getAIResponse(message);
            const processedResponse = await this.responseHandler.processResponse(response, 'user');
            
            this.hideTypingIndicator();
            await this.showAIResponse(processedResponse);
            
        } catch (error) {
            this.hideTypingIndicator();
            this.addMessage('ai', this.getErrorMessage(error));
        }
    }
    
    async showAIResponse(response) {
        const messageDiv = document.createElement('div');
        messageDiv.className = 'message ai-message';
        this.elements.messages.appendChild(messageDiv);
        
        await this.responseHandler.typeMessage(messageDiv, response);
        this.addActionButtons(messageDiv, response);
        this.scrollToBottom();
    }
    
    addActionButtons(messageElement, response) {
        const actions = this.detectActions(response);
        
        if (actions.length > 0) {
            const buttonContainer = document.createElement('div');
            buttonContainer.className = 'action-buttons';
            
            actions.forEach(action => {
                const button = document.createElement('button');
                button.className = 'action-btn';
                button.textContent = action.label;
                button.onclick = () => this.handleAction(action);
                buttonContainer.appendChild(button);
            });
            
            messageElement.appendChild(buttonContainer);
        }
    }
    
    detectActions(response) {
        const actions = [];
        const lowerResponse = response.toLowerCase();
        
        if (lowerResponse.includes('código') || lowerResponse.includes('exemplo')) {
            actions.push({
                label: '📋 Copiar Código',
                type: 'copy_code',
                data: response
            });
        }
        
        if (lowerResponse.includes('explicar') || lowerResponse.includes('detalhes')) {
            actions.push({
                label: '🔍 Mais Detalhes',
                type: 'more_details',
                data: response
            });
        }
        
        return actions;
    }
    
    handleAction(action) {
        switch (action.type) {
            case 'copy_code':
                this.copyCodeToClipboard(action.data);
                break;
            case 'more_details':
                this.requestMoreDetails(action.data);
                break;
        }
    }
    
    copyCodeToClipboard(text) {
        const codeMatch = text.match(/```[\s\S]*?```/);
        if (codeMatch) {
            const code = codeMatch[0].replace(/```\w*\n?/g, '').replace(/```/g, '');
            navigator.clipboard.writeText(code).then(() => {
                this.showTemporaryMessage('✅ Código copiado!');
            });
        }
    }
    
    requestMoreDetails(context) {
        this.addMessage('user', `Poderia dar mais detalhes sobre: "${context.substring(0, 50)}..."`);
        this.sendUserMessage();
    }
    
    showTemporaryMessage(message) {
        const tempMsg = document.createElement('div');
        tempMsg.className = 'temp-message';
        tempMsg.textContent = message;
        tempMsg.style.cssText = `
            position: fixed;
            top: 20px;
            right: 20px;
            background: #10b981;
            color: white;
            padding: 10px 16px;
            border-radius: 8px;
            z-index: 10000;
        `;
        document.body.appendChild(tempMsg);
        
        setTimeout(() => {
            tempMsg.remove();
        }, 3000);
    }
    
    async getAIResponse(message) {
        try {
            const response = await fetch('/api/user/send-message', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({
                    content: message,
                    user_identifier: 'web_user'
                })
            });
            
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            
            const data = await response.json();
            return data.response;
            
        } catch (error) {
            console.error('Erro na chamada da IA:', error);
            throw error;
        }
    }
    
    addMessage(role, content) {
        const messageDiv = document.createElement('div');
        messageDiv.className = `message ${role === 'user' ? 'user-message' : 'ai-message'}`;
        messageDiv.textContent = content;
        this.elements.messages.appendChild(messageDiv);
        this.scrollToBottom();
    }
    
    showTypingIndicator() {
        const typingDiv = document.createElement('div');
        typingDiv.id = 'typingIndicator';
        typingDiv.className = 'typing-indicator';
        typingDiv.innerHTML = `
            IA digitando...
            <div class="typing-dot"></div>
            <div class="typing-dot"></div>
            <div class="typing-dot"></div>
        `;
        this.elements.messages.appendChild(typingDiv);
        this.scrollToBottom();
    }
    
    hideTypingIndicator() {
        const typingIndicator = document.getElementById('typingIndicator');
        if (typingIndicator) {
            typingIndicator.remove();
        }
    }
    
    getErrorMessage(error) {
        console.error('Erro no widget usuário:', error);
        
        const errorMessages = {
            'network': '🔌 Problema de conexão. Verifique sua internet.',
            'timeout': '⏰ A resposta está demorando mais que o normal.',
            'server': '🛠️ Estamos com problemas técnicos.',
            'default': '❌ Ocorreu um erro inesperado.'
        };
        
        if (error.name === 'TimeoutError') return errorMessages.timeout;
        if (error.message.includes('Network')) return errorMessages.network;
        if (error.status === 500) return errorMessages.server;
        
        return errorMessages.default;
    }
    
    scrollToBottom() {
        setTimeout(() => {
            this.elements.messages.scrollTop = this.elements.messages.scrollHeight;
        }, 100);
    }
    
    toggleWidget() {
        this.isOpen = !this.isOpen;
        if (this.isOpen) {
            this.elements.window.classList.remove('widget-hidden');
            this.elements.window.classList.add('widget-visible');
            this.elements.input.focus();
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
let userWidget;
document.addEventListener('DOMContentLoaded', () => {
    userWidget = new UserWidget();
});