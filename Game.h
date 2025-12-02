#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <map>
#include <set>
#include <string>
#include "Player.h"
#include "Evento.h"

class UIManager; 

class Game {
public:
    enum class GameStatus { RUNNING, VICTORY, GAME_OVER_GENERICO };

private:
    sf::RenderWindow& janela;
    sf::Font fonte;
    Player player;
    UIManager* ui;

    Evento* arvoreEventos; 
    Evento* eventoAtual;   
    GameStatus status; 
    std::map<std::string, sf::Texture> texturas;

    // --- EFEITOS ---
    float shakeIntensity = 0.0f; // Intensidade do tremor

    // --- SISTEMA DE DESCANSO ---
    Evento* eventoDescansoAtual = nullptr; // Evento de descanso temporário
    Evento* proximoEventoAposDescanso = nullptr; // Próximo evento após descanso

    void carregarNivelAtual();
    Evento* criarPrologo();
    Evento* criarSemestre1();
    Evento* criarSemestre2();
    Evento* criarSemestre3();
    Evento* criarSemestre4();
    Evento* criarSemestre5();
    Evento* criarSemestre6();
    Evento* criarSemestre7();
    Evento* criarSemestre8();

    void limparArvoreAtual(); 
    void deletarNosRecursivo(Evento* no, std::set<Evento*>& visitados);

    void carregarTexturas(); 
    void aplicarEscolha(int escolha); 
    void processarLogicaEspecial(Evento* eventoAnterior, int escolhaFeita);
    void verificarFimDeSemestre(Evento* eventoFim);
    
    bool verificarAtributosBaixos() const;
    Evento* criarEventoDescanso(Evento* proximoEventoOriginal);
    Evento* criarEventoFinalPersonalizado();

public:
    Game(sf::RenderWindow& jan, const sf::Font& f);
    ~Game();

    void processarEvento(sf::Event evento);
    void atualizar();
    void desenhar();

    GameStatus getStatus() const { return status; }
    std::string getFinalMessage() const;
};

#endif