#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "UIManager.h"
#include <iostream>

const int LARGURA_JANELA = 1024;
const int ALTURA_JANELA = 768;

enum class GameState { MENU, PLAYING, END_SCREEN };

int main() {
    sf::RenderWindow janela(sf::VideoMode(LARGURA_JANELA, ALTURA_JANELA), "UFSCar: Vida Universitária");
    janela.setFramerateLimit(60);

    sf::Font fonte;
    // Tenta carregar a fonte. Certifique-se que o caminho está correto.
    if (!fonte.loadFromFile("./google-carlito-fonts/Carlito-Regular.ttf")) {
        // Fallback: tenta carregar do sistema se não achar na pasta (opcional, mas ajuda testes)
        if (!fonte.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
             std::cerr << "Erro critico: Fonte nao encontrada!" << std::endl;
             return -1;
        }
    }

    GameState estado = GameState::MENU;
    Game* jogo = nullptr;

    // Música de fundo (coloque o arquivo em ./assets/music/bg_music.ogg ou ajuste o caminho)
    // sf::Music bgMusic;
    // if (bgMusic.openFromFile("/home/renan/Faculdade/teste rpg/assets/music/SpotiDown.App - Nothing Else Matters - Instrumental Version - Rock Hero.mp3")) {
    //     bgMusic.setLoop(true);
    //     bgMusic.setVolume(35.f); // volume moderado
    //     bgMusic.play();
    // } else {
    //     std::cerr << "Aviso: nao foi possivel carregar a musica de fundo." << std::endl;
    // }

    // --- TELA INICIAL (MENU) ---
    sf::Texture texturaInicio;
    sf::Sprite spriteInicio;
    if (!texturaInicio.loadFromFile("./img/bg_inicio.png")) {
        std::cerr << "Erro: nao foi possivel carregar bg_inicio.png" << std::endl;
    } else {
        // Ajusta a imagem para caber INTEIRA na janela mantendo proporção (sem cortar)
        float escalaX = LARGURA_JANELA / static_cast<float>(texturaInicio.getSize().x);
        float escalaY = ALTURA_JANELA / static_cast<float>(texturaInicio.getSize().y);
        float escala = std::min(escalaX, escalaY);
        spriteInicio.setTexture(texturaInicio);
        spriteInicio.setScale(escala, escala);
        // Centraliza a imagem
        spriteInicio.setPosition(
            (LARGURA_JANELA - texturaInicio.getSize().x * escala) / 2.0f,
            (ALTURA_JANELA - texturaInicio.getSize().y * escala) / 2.0f
        );
    }

    // Botão "Iniciar Jogo"
    sf::RectangleShape botaoIniciar(sf::Vector2f(300, 80));
    botaoIniciar.setPosition(LARGURA_JANELA / 2.0f - 150, ALTURA_JANELA - 150);
    botaoIniciar.setFillColor(sf::Color(50, 100, 200, 200));
    botaoIniciar.setOutlineColor(sf::Color::White);
    botaoIniciar.setOutlineThickness(3);

    sf::Text textoBotao;
    textoBotao.setFont(fonte);
    std::string textoBotaoStr = "Iniciar Jogo";
    textoBotao.setString(sf::String::fromUtf8(textoBotaoStr.begin(), textoBotaoStr.end()));
    textoBotao.setCharacterSize(36);
    textoBotao.setFillColor(sf::Color::White);
    textoBotao.setOutlineColor(sf::Color::Black);
    textoBotao.setOutlineThickness(2);
    
    // Centraliza o texto no botão
    sf::FloatRect boundsBotao = textoBotao.getLocalBounds();
    textoBotao.setOrigin(boundsBotao.left + boundsBotao.width / 2.0f, 
                         boundsBotao.top + boundsBotao.height / 2.0f);
    textoBotao.setPosition(LARGURA_JANELA / 2.0f, ALTURA_JANELA - 110);

    // Título do jogo (opcional)
    sf::Text titulo;
    titulo.setFont(fonte);
    std::string tituloStr = "UFSCar: Vida Universitária";
    titulo.setString(sf::String::fromUtf8(tituloStr.begin(), tituloStr.end()));
    titulo.setCharacterSize(48);
    titulo.setFillColor(sf::Color::White);
    titulo.setOutlineColor(sf::Color::Black);
    titulo.setOutlineThickness(3);
    boundsBotao = titulo.getLocalBounds();
    titulo.setOrigin(boundsBotao.left + boundsBotao.width / 2.0f, 
                     boundsBotao.top + boundsBotao.height / 2.0f);
    titulo.setPosition(LARGURA_JANELA / 2.0f, 100);
   
    // Texto para tela de Fim de Jogo
    sf::Text fullscreenText;
    fullscreenText.setFont(fonte);
    fullscreenText.setFillColor(sf::Color::White);

    while (janela.isOpen()) {
        
        // --- LOOP DE EVENTOS ---
        sf::Event evento;
        while (janela.pollEvent(evento)) {
            
            if (evento.type == sf::Event::Closed) {
                janela.close();
            }

            if (estado == GameState::MENU) {
                // Detecta clique no botão "Iniciar Jogo"
                if (evento.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(janela);
                    sf::FloatRect botaoRect = botaoIniciar.getGlobalBounds();
                    
                    if (botaoRect.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        // Inicia o jogo
                        try {
                            jogo = new Game(janela, fonte);
                            estado = GameState::PLAYING;
                        } catch (const std::exception& e) {
                            std::cerr << "Erro ao iniciar jogo: " << e.what() << std::endl;
                            return -1;
                        }
                    }
                }
                // Também permite iniciar com Enter
                if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter) {
                    try {
                        jogo = new Game(janela, fonte);
                        estado = GameState::PLAYING;
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao iniciar jogo: " << e.what() << std::endl;
                        return -1;
                    }
                }
            }
            else if (estado == GameState::PLAYING && jogo != nullptr) {
                jogo->processarEvento(evento);
            } 
            else if (estado == GameState::END_SCREEN) {
                // Permite fechar com Clique ou Espaço
                if (evento.type == sf::Event::MouseButtonPressed ||
                    (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Space)) 
                {
                    janela.close();
                }
            }
        }

        // --- LÓGICA DE ESTADOS ---
        if (estado == GameState::PLAYING && jogo != nullptr) {
            
            jogo->atualizar(); 

            // Verifica se o jogo acabou (Vitória ou Derrota)
            // Agora verificamos os NOVOS status definidos no Game.h
            if (jogo->getStatus() == Game::GameStatus::GAME_OVER_GENERICO || 
                jogo->getStatus() == Game::GameStatus::VICTORY) {
                
                estado = GameState::END_SCREEN;
                
                std::string msgFinal = jogo->getFinalMessage();
                
                // Quebra o texto para caber na tela
                std::string wrappedMsg = UIManager::wrapText(msgFinal, LARGURA_JANELA - 100, fonte, 30);
                
                fullscreenText.setCharacterSize(30); 
                fullscreenText.setString(sf::String::fromUtf8(wrappedMsg.begin(), wrappedMsg.end()));
                
                // Centraliza
                sf::FloatRect bounds = fullscreenText.getLocalBounds();
                fullscreenText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
                fullscreenText.setPosition(LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f);
                
                // Muda cor dependendo do resultado
                if (jogo->getStatus() == Game::GameStatus::VICTORY) {
                    fullscreenText.setFillColor(sf::Color::Green);
                } else {
                    fullscreenText.setFillColor(sf::Color::Red);
                }
            }
        }
        
        // --- DESENHO ---
        janela.clear(sf::Color::Black); 

        if (estado == GameState::PLAYING && jogo != nullptr) {
            jogo->desenhar(); 
        } 
        else if (estado == GameState::END_SCREEN) {
            janela.draw(fullscreenText);
        } 
        else if (estado == GameState::MENU) {
            // Desenha a tela inicial
            janela.draw(spriteInicio);
            janela.draw(titulo);
            
            // Efeito hover no botão
            sf::Vector2i mousePos = sf::Mouse::getPosition(janela);
            sf::FloatRect botaoRect = botaoIniciar.getGlobalBounds();
            if (botaoRect.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                botaoIniciar.setFillColor(sf::Color(70, 130, 250, 220));
            } else {
                botaoIniciar.setFillColor(sf::Color(50, 100, 200, 200));
            }
            
            janela.draw(botaoIniciar);
            janela.draw(textoBotao);
        }
        
        janela.display(); 
    }

    delete jogo;
    return 0;
}