#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Evento.h"
#include <sstream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm> 

// --- SISTEMA DE PARTÍCULAS SIMPLES ---
struct Particle {
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Color color;
    float life;
};

// --- BARRAS DE STATUS ---
class StatBar {
public:
    sf::RectangleShape fundo;
    sf::RectangleShape valor;
    sf::Text rotulo;
    
    void setup(sf::Font& fonte, std::string nome, float x, float y, sf::Color cor) {
        fundo.setSize(sf::Vector2f(200, 20)); 
        fundo.setPosition(x, y);
        fundo.setFillColor(sf::Color(20, 20, 20, 200)); 
        fundo.setOutlineColor(sf::Color(100, 100, 100));
        fundo.setOutlineThickness(2);
        
        valor.setSize(sf::Vector2f(200, 20));
        valor.setPosition(x, y);
        valor.setFillColor(cor);
        
        rotulo.setFont(fonte);
        rotulo.setString(sf::String::fromUtf8(nome.begin(), nome.end()));
        rotulo.setCharacterSize(16);
        rotulo.setOutlineColor(sf::Color::Black);
        rotulo.setOutlineThickness(1);
        rotulo.setPosition(x + 210, y - 2);
        rotulo.setFillColor(sf::Color::White);
    }
    
    void update(int val) {
        float perc = std::clamp(val, 0, 100) / 100.0f;
        valor.setSize(sf::Vector2f(perc * 200.0f, 20));
    }
    
    void draw(sf::RenderWindow& janela) {
        janela.draw(fundo);
        janela.draw(valor);
        janela.draw(rotulo);
    }
};

class UIManager {
private:
    sf::RenderWindow& janela;
    const sf::Font& fonte;
    sf::Sprite spriteFundo;
    sf::RectangleShape caixaTextoFundo;
    sf::Text textoDescricao;
    sf::RectangleShape botaoEsq, botaoDir, botaoProximo;
    sf::Text textoBotaoEsq, textoBotaoDir, textoBotaoProximo;
    
    StatBar barraMente, barraSocial, barraSaude, barraNotas, barraFaltas;
    sf::Text textoInfoExtra;
    EventoTipo tipoEventoAtual;

    // --- EFEITOS VISUAIS ---
    std::vector<Particle> particles;
    sf::Shader shaderDrunk;
    bool shaderAtivo = false;
    sf::Clock clockShader;

public:
    UIManager(sf::RenderWindow& jan, const sf::Font& f) : janela(jan), fonte(f) {
        // Inicializa Shaders
        const std::string fragShader = \
            "uniform float time;" \
            "uniform sampler2D texture;" \
            "void main() {" \
            "   vec2 coord = gl_TexCoord[0].xy;" \
            "   coord.x += sin(time * 3.0 + coord.y * 10.0) * 0.02;" \
            "   coord.y += cos(time * 5.0 + coord.x * 10.0) * 0.02;" \
            "   gl_FragColor = texture2D(texture, coord);" \
            "}";
        
        if (!shaderDrunk.loadFromMemory(fragShader, sf::Shader::Fragment)) {
            // Ignora falha de shader
        }
        shaderDrunk.setUniform("texture", sf::Shader::CurrentTexture);

        setupUI();
    }

    void setupUI() {
        float w = janela.getSize().x;
        float h = janela.getSize().y;

        // Caixa estilo RPG
        caixaTextoFundo.setSize(sf::Vector2f(w - 100, 250));
        caixaTextoFundo.setOrigin((w - 100)/2, 0);
        caixaTextoFundo.setPosition(w/2, h - 280);
        caixaTextoFundo.setFillColor(sf::Color(0, 0, 0, 220));
        caixaTextoFundo.setOutlineColor(sf::Color(255, 215, 0));
        caixaTextoFundo.setOutlineThickness(3);

        textoDescricao.setFont(fonte);
        textoDescricao.setCharacterSize(24);
        textoDescricao.setFillColor(sf::Color::White);
        textoDescricao.setPosition(70, h - 260);

        // Botões
        sf::Vector2f tamBotao(400, 90);
        
        botaoEsq.setSize(tamBotao);
        botaoEsq.setFillColor(sf::Color(0, 100, 200));
        botaoEsq.setOutlineThickness(2);
        botaoEsq.setPosition(w/2 - 420, h - 110);

        botaoDir.setSize(tamBotao);
        botaoDir.setFillColor(sf::Color(200, 50, 50));
        botaoDir.setOutlineThickness(2);
        botaoDir.setPosition(w/2 + 20, h - 110);

        botaoProximo.setSize(sf::Vector2f(840, 90));
        botaoProximo.setFillColor(sf::Color(50, 150, 50));
        botaoProximo.setPosition(w/2 - 420, h - 110);

        textoBotaoEsq.setFont(fonte); textoBotaoEsq.setCharacterSize(20);
        textoBotaoDir.setFont(fonte); textoBotaoDir.setCharacterSize(20);
        textoBotaoProximo.setFont(fonte); textoBotaoProximo.setCharacterSize(22);

        // Barras
        float startY = 20; float gap = 30;
        barraMente.setup(const_cast<sf::Font&>(fonte), "Mente", 20, startY, sf::Color::Cyan);
        barraSocial.setup(const_cast<sf::Font&>(fonte), "Social", 20, startY + gap, sf::Color::Magenta);
        barraSaude.setup(const_cast<sf::Font&>(fonte), "Saude", 20, startY + gap*2, sf::Color::Green);
        barraNotas.setup(const_cast<sf::Font&>(fonte), "Notas", 20, startY + gap*3, sf::Color::Yellow);
        barraFaltas.setup(const_cast<sf::Font&>(fonte), "Faltas", 20, startY + gap*4, sf::Color::Red);

        // Info Extra
        textoInfoExtra.setFont(fonte);
        textoInfoExtra.setCharacterSize(18);
        textoInfoExtra.setPosition(w - 300, 20);
    }

    void fixBackgroundScale(const sf::Texture& tex) {
        sf::Vector2u texSize = tex.getSize();
        sf::Vector2u winSize = janela.getSize();
        
        float scaleX = (float)winSize.x / texSize.x;
        float scaleY = (float)winSize.y / texSize.y;
        float scale = std::max(scaleX, scaleY);
        
        spriteFundo.setTexture(tex, true);
        spriteFundo.setScale(scale, scale);
        spriteFundo.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
        spriteFundo.setPosition(winSize.x / 2.0f, winSize.y / 2.0f);
    }

    void setShaderDrunk(bool active) { shaderAtivo = active; }

    // Efeito simples de partículas (confete); pode ser disparado pelo Game
    void spawnConfetti() {
        for (int i = 0; i < 80; ++i) {
            Particle p;
            p.pos = sf::Vector2f(
                static_cast<float>(std::rand() % janela.getSize().x),
                static_cast<float>(std::rand() % (janela.getSize().y / 2))
            );
            p.vel = sf::Vector2f(
                static_cast<float>((std::rand() % 200) - 100) / 100.0f,
                static_cast<float>((std::rand() % 200) + 50) / 50.0f
            );
            p.life = 255.0f;
            p.color = sf::Color(
                static_cast<sf::Uint8>(std::rand() % 255),
                static_cast<sf::Uint8>(std::rand() % 255),
                static_cast<sf::Uint8>(std::rand() % 255)
            );
            particles.push_back(p);
        }
    }

    void update(const Player& player, Evento* evento, const sf::Texture& texturaFundo) {
        tipoEventoAtual = evento->tipo;
        
        fixBackgroundScale(texturaFundo);

        // Ativa shader de "bêbado" automaticamente em festas/TUSCA
        if (evento->idBackground == "bg_festa") {
            shaderAtivo = true;
        } else {
            shaderAtivo = false;
        }

        std::string desc = wrapText(evento->descricao, caixaTextoFundo.getSize().x - 60, fonte, 24);
        textoDescricao.setString(sf::String::fromUtf8(desc.begin(), desc.end()));

        if (tipoEventoAtual == EventoTipo::NARRATIVA || tipoEventoAtual == EventoTipo::ESCOLHA_ARQUETIPO) {
            setupButtonText(textoBotaoEsq, evento->textoOpcaoEsq, botaoEsq);
            setupButtonText(textoBotaoDir, evento->textoOpcaoDir, botaoDir);
        } else {
            std::string continuarStr = "Continuar >>";
            textoBotaoProximo.setString(sf::String::fromUtf8(continuarStr.begin(), continuarStr.end()));
            sf::FloatRect b = textoBotaoProximo.getLocalBounds();
            textoBotaoProximo.setOrigin(b.left+b.width/2, b.top+b.height/2);
            textoBotaoProximo.setPosition(botaoProximo.getPosition().x + 420, botaoProximo.getPosition().y + 45);
        }

        barraMente.update(player.getMente());
        barraSocial.update(player.getSocial());
        barraSaude.update(player.getSaude());
        barraNotas.update(player.getNotas());
        barraFaltas.update(player.getFaltas());

        std::stringstream ss;
        ss << "Semestre: " << player.getSemestre() << "\n";
        std::string status = player.getStatusRelacionamento();
        if (status == "Solteiro" && player.getNomeNamorada() != "") {
            status = player.getNomeNamorada() + " (" + status + ")";
        }
        ss << "Status: " << status << "\n";
        std::string cargo = player.getEmprego();
        if (cargo == "Desempregado" && player.getProjeto() != "Nenhum") {
            cargo = player.getProjeto();
        } else if (player.getProjeto() != "Nenhum" && cargo != "Desempregado") {
            cargo += " / " + player.getProjeto();
        }
        ss << "Cargo: " << cargo;
        std::string infoStr = ss.str();
        textoInfoExtra.setString(sf::String::fromUtf8(infoStr.begin(), infoStr.end()));
    }

    void draw() {
        if (shaderAtivo) {
            shaderDrunk.setUniform("time", clockShader.getElapsedTime().asSeconds());
            janela.draw(spriteFundo, &shaderDrunk);
        } else {
            janela.draw(spriteFundo);
        }

        if (!particles.empty()) {
            for (auto it = particles.begin(); it != particles.end();) {
                it->pos += it->vel;
                it->life -= 2;
                if (it->life <= 0) {
                    it = particles.erase(it);
                } else {
                    sf::CircleShape c(5);
                    c.setPosition(it->pos);
                    c.setFillColor(sf::Color(it->color.r, it->color.g, it->color.b, (sf::Uint8)it->life));
                    janela.draw(c);
                    ++it;
                }
            }
        }

        janela.draw(caixaTextoFundo);
        janela.draw(textoDescricao);

        if (tipoEventoAtual == EventoTipo::NARRATIVA || tipoEventoAtual == EventoTipo::ESCOLHA_ARQUETIPO) {
            janela.draw(botaoEsq); janela.draw(textoBotaoEsq);
            janela.draw(botaoDir); janela.draw(textoBotaoDir);
        } else {
            janela.draw(botaoProximo); janela.draw(textoBotaoProximo);
        }

        barraMente.draw(janela);
        barraSocial.draw(janela);
        barraSaude.draw(janela);
        barraNotas.draw(janela);
        barraFaltas.draw(janela);
        
        sf::RectangleShape bgInfo(sf::Vector2f(300, 80));
        bgInfo.setPosition(janela.getSize().x - 310, 10);
        bgInfo.setFillColor(sf::Color(0,0,0,150));
        janela.draw(bgInfo);
        janela.draw(textoInfoExtra);
    }

    // --- CORREÇÃO DEFINITIVA (Padding agressivo + Scale Down) ---
    void setupButtonText(sf::Text& txt, std::string s, sf::RectangleShape& btn) {
        // 1. Aumentamos o padding de 20 para 40 pixels de cada lado (total 80px)
        const float paddingX = 40.0f; 
        const float paddingY = 10.0f;

        float maxWidth  = btn.getSize().x - (2.0f * paddingX);
        float maxHeight = btn.getSize().y - (2.0f * paddingY);

        unsigned int charSize = 22;
        std::string bestFitString = s;

        // Loop: Tenta diminuir a fonte até o texto caber
        while (charSize >= 12) {
            // Força a quebra de linha com a largura reduzida
            std::string wrapped = wrapText(s, maxWidth, fonte, charSize);
            
            txt.setCharacterSize(charSize);
            txt.setString(sf::String::fromUtf8(wrapped.begin(), wrapped.end()));
            
            // Pega os limites reais do texto
        sf::FloatRect b = txt.getLocalBounds();

            // Verifica se cabe na altura e largura
            if (b.width <= maxWidth + 10 && b.height <= maxHeight) { // +10 de tolerância
                bestFitString = wrapped;
                break; // Encontrou! Sai do loop
            }
            
            // Se não coube, guarda como "melhor tentativa" e diminui a fonte
            bestFitString = wrapped;
            charSize -= 2; 
        }

        // Aplica o melhor texto encontrado
        txt.setCharacterSize(charSize);
        txt.setString(sf::String::fromUtf8(bestFitString.begin(), bestFitString.end()));
        
        // --- TRAVA DE SEGURANÇA (SCALE DOWN) ---
        // Se, mesmo depois de tudo, o texto ainda for maior que a largura do botão
        // (acontece com palavras muito longas que não quebram), forçamos o encolhimento.
        sf::FloatRect finalBounds = txt.getLocalBounds();
        float currentWidth = finalBounds.width;
        float maxAllowedWidth = btn.getSize().x - 20.0f; // Margem de segurança final absoluta
        
        txt.setScale(1.0f, 1.0f); // Reseta escala
        if (currentWidth > maxAllowedWidth) {
            float scaleFactor = maxAllowedWidth / currentWidth;
            txt.setScale(scaleFactor, scaleFactor);
        }

        // Centraliza novamente com base na nova escala
        finalBounds = txt.getLocalBounds(); // Recalcula bounds (local bounds não muda com scale)
        // Precisamos usar getGlobalBounds para centralizar corretamente com escala
        sf::FloatRect globalBounds = txt.getGlobalBounds();
        
        txt.setOrigin(finalBounds.left + finalBounds.width / 2.0f, 
                      finalBounds.top + finalBounds.height / 2.0f);
                      
        txt.setPosition(btn.getPosition().x + btn.getSize().x / 2.0f,
                        btn.getPosition().y + btn.getSize().y / 2.0f);
    }

    int handleClick(sf::Vector2f m) {
        if (tipoEventoAtual == EventoTipo::FINAL_SEMESTRE) {
            if (botaoProximo.getGlobalBounds().contains(m)) return 3;
        } else {
            if (botaoEsq.getGlobalBounds().contains(m)) return 1;
            if (botaoDir.getGlobalBounds().contains(m)) return 2;
        }
        return 0;
    }
    
    static std::string wrapText(const std::string& text, float maxWidth, const sf::Font& font, unsigned int charSize) {
        sf::Text tempText; 
        tempText.setFont(font); 
        tempText.setCharacterSize(charSize);
        
        std::string result;
        std::string currentLine;
        std::string word;
        std::stringstream ss(text);
        
        while (ss >> word) {
            std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
            tempText.setString(sf::String::fromUtf8(testLine.begin(), testLine.end()));
            
            // Verifica se a linha ultrapassa a largura máxima
            if (tempText.getLocalBounds().width > maxWidth) {
                if (!currentLine.empty()) {
                    result += currentLine + "\n";
                    currentLine = word;
                } else {
                    // Palavra sozinha já é maior que a largura: coloca ela e quebra linha
                    result += word + "\n";
                    currentLine = "";
                }
            }
            else {
                currentLine = testLine;
            }
        }
        result += currentLine;
        return result;
    }
};

#endif