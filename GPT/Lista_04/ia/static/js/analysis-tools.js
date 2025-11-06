// analysis-tools.js
class AnalysisTools {
    async analyzeQuery(message) {
        return {
            complexity: this.detectComplexity(message),
            intent: this.detectIntent(message),
            urgency: this.detectUrgency(message),
            technicalDepth: this.detectTechnicalDepth(message),
            topics: this.detectTopics(message)
        };
    }
    
    detectComplexity(message) {
        const complexKeywords = ['bug', 'erro', 'otimização', 'performance', 'arquitetura'];
        return complexKeywords.some(keyword => message.toLowerCase().includes(keyword)) ? 'high' : 'medium';
    }
    
    detectIntent(message) {
        if (message.includes('?')) return 'question';
        if (message.includes('ajuda')) return 'help';
        if (message.match(/não funciona|problema|erro/)) return 'debug';
        return 'general';
    }
    
    detectUrgency(message) {
        const urgentWords = ['urgente', 'crítico', 'bloqueador', 'produção'];
        return urgentWords.some(word => message.toLowerCase().includes(word)) ? 'high' : 'normal';
    }
    
    detectTechnicalDepth(message) {
        const techWords = ['api', 'endpoint', 'database', 'query', 'function', 'class'];
        const count = techWords.filter(word => message.toLowerCase().includes(word)).length;
        return count > 2 ? 'deep' : count > 0 ? 'medium' : 'shallow';
    }
    
    detectTopics(message) {
        const topics = {
            'javascript': ['javascript', 'js', 'node', 'react', 'vue'],
            'python': ['python', 'django', 'flask'],
            'html': ['html', 'css', 'frontend'],
            'database': ['sql', 'banco de dados', 'query'],
            'api': ['api', 'rest', 'endpoint']
        };
        
        const detectedTopics = [];
        for (const [topic, keywords] of Object.entries(topics)) {
            if (keywords.some(keyword => message.toLowerCase().includes(keyword))) {
                detectedTopics.push(topic);
            }
        }
        
        return detectedTopics;
    }
}