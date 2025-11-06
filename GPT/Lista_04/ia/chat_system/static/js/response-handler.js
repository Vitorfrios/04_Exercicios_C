// response-handler.js
class ResponseHandler {
    constructor() {
        this.typingSpeed = 30;
        this.thinkingTime = 800;
    }

    async processResponse(response, messageType = 'user') {
        let processedResponse = this.cleanResponse(response);
        const contentType = this.detectContentType(processedResponse);
        processedResponse = this.formatByContentType(processedResponse, contentType);
        processedResponse = this.addContextualEmojis(processedResponse, contentType);
        return processedResponse;
    }

    cleanResponse(text) {
        if (!text) return 'Desculpe, não consegui processar a resposta.';
        
        return text
            .replace(/\*\*(.*?)\*\*/g, '<strong>$1</strong>')
            .replace(/\*(.*?)\*/g, '<em>$1</em>')
            .replace(/`(.*?)`/g, '<code>$1</code>')
            .replace(/\n{3,}/g, '\n\n')
            .replace(/\s+\./g, '.')
            .trim();
    }

    detectContentType(text) {
        const lowerText = text.toLowerCase();
        
        if (lowerText.includes('erro') || lowerText.includes('error') || 
            lowerText.includes('não funciona') || lowerText.includes('problema')) {
            return 'error';
        }
        
        if (lowerText.includes('código') || lowerText.includes('code') || 
            lowerText.match(/function|class|const|let|var|def |import |export /)) {
            return 'code';
        }
        
        if (lowerText.includes('```') || lowerText.includes('python') || 
            lowerText.includes('javascript') || lowerText.includes('html')) {
            return 'code_block';
        }
        
        if (lowerText.includes('exemplo') || lowerText.includes('exemplo:') || 
            lowerText.includes('por exemplo')) {
            return 'example';
        }
        
        if (lowerText.includes('dica') || lowerText.includes('sugestão') || 
            lowerText.includes('recomendação')) {
            return 'tip';
        }
        
        if (lowerText.match(/passo a passo|como fazer|tutorial/)) {
            return 'tutorial';
        }
        
        return 'general';
    }

    formatByContentType(text, contentType) {
        switch (contentType) {
            case 'code':
                return this.formatCodeResponse(text);
            case 'code_block':
                return this.formatCodeBlock(text);
            case 'error':
                return this.formatErrorResponse(text);
            case 'tip':
                return this.formatTipResponse(text);
            case 'tutorial':
                return this.formatTutorialResponse(text);
            case 'example':
                return this.formatExampleResponse(text);
            default:
                return this.formatGeneralResponse(text);
        }
    }

    formatCodeResponse(text) {
        return text.replace(/```(\w+)?\n([\s\S]*?)```/g, 
            '<div class="code-block"><div class="code-header">$1</div><pre><code>$2</code></pre></div>');
    }

    formatCodeBlock(text) {
        return `<div class="code-container">${text}</div>`;
    }

    formatErrorResponse(text) {
        return `🚨 <strong>Problema Detectado:</strong>\n\n${text}\n\n💡 <strong>Sugestão de Solução:</strong>`;
    }

    formatTipResponse(text) {
        return `💡 <strong>Dica Profissional:</strong>\n\n${text}`;
    }

    formatTutorialResponse(text) {
        const steps = text.split(/\d+\./).filter(step => step.trim());
        let formatted = `📚 <strong>Passo a Passo:</strong>\n\n`;
        
        steps.forEach((step, index) => {
            formatted += `${index + 1}. ${step.trim()}\n\n`;
        });
        
        return formatted;
    }

    formatExampleResponse(text) {
        return `📋 <strong>Exemplo Prático:</strong>\n\n${text}`;
    }

    formatGeneralResponse(text) {
        const paragraphs = text.split('\n\n');
        return paragraphs.map(p => {
            if (p.startsWith('- ') || p.startsWith('• ')) {
                return `• ${p.substring(2)}`;
            }
            return p;
        }).join('\n\n');
    }

    addContextualEmojis(text, contentType) {
        const emojis = {
            'error': '🚨',
            'code': '💻',
            'code_block': '📝',
            'tip': '💡',
            'tutorial': '📚',
            'example': '📋',
            'general': '🤖'
        };
        
        const emoji = emojis[contentType] || '💬';
        return `${emoji} ${text}`;
    }

    async typeMessage(element, message, speed = this.typingSpeed) {
        element.innerHTML = '';
        await this.delay(this.thinkingTime);
        
        for (let i = 0; i < message.length; i++) {
            element.innerHTML += message[i];
            element.parentElement.scrollTop = element.parentElement.scrollHeight;
            
            const currentChar = message[i];
            const nextChar = message[i + 1];
            let charSpeed = speed;
            
            if (currentChar.match(/[.,;!?]/)) {
                charSpeed = speed * 3;
            } else if (nextChar && nextChar.match(/[.,;!?]/)) {
                charSpeed = speed * 1.5;
            }
            
            await this.delay(charSpeed);
        }
    }

    delay(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
}