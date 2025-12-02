#include "Game.h"
#include "UIManager.h"
#include <set>

// Implementação das operações da árvore de eventos (TAD da narrativa)

void Game::limparArvoreAtual() {
    std::set<Evento*> visitados;
    deletarNosRecursivo(arvoreEventos, visitados);
    arvoreEventos = nullptr;
    eventoAtual = nullptr;
    
    // Limpa eventos temporários
    eventoDescansoAtual = nullptr;
    proximoEventoAposDescanso = nullptr;
}

void Game::deletarNosRecursivo(Evento* no, std::set<Evento*>& visitados) {
    if (no == nullptr || visitados.count(no)) return;
    visitados.insert(no);
    deletarNosRecursivo(no->proximoEventoEsq, visitados);
    deletarNosRecursivo(no->proximoEventoDir, visitados);
    delete no;
}

void Game::carregarNivelAtual() {
    limparArvoreAtual();
    int s = player.getSemestre();

    // Roteamento de Semestres
    switch (s) {
        case 0: arvoreEventos = criarPrologo(); break;
        case 1: arvoreEventos = criarSemestre1(); break;
        case 2: arvoreEventos = criarSemestre2(); break;
        case 3: arvoreEventos = criarSemestre3(); break; // Arco do Plágio
        case 4: arvoreEventos = criarSemestre4(); break; // Crise/TUSCA aftermath
        case 5: arvoreEventos = criarSemestre5(); break;
        case 6: arvoreEventos = criarSemestre6(); break;
        case 7: arvoreEventos = criarSemestre7(); break;
        case 8: arvoreEventos = criarSemestre8(); break;
        default:
            // Após o semestre 8, reutiliza o final personalizado
            arvoreEventos = criarEventoFinalPersonalizado();
            status = GameStatus::VICTORY;
            break;
    }

    eventoAtual = arvoreEventos;
    if (eventoAtual && ui) {
        ui->update(player, eventoAtual, texturas[eventoAtual->idBackground]);
    }
}





