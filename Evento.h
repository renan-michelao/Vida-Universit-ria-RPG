#ifndef EVENTO_H
#define EVENTO_H

#include <string>

// Estrutura atualizada conforme a imagem dos Arquétipos
// Stats variam de 0 a 20 (baseado na imagem) ou 0 a 100 (vamos usar escala 100 para facilitar matemática)
struct ImpactoStats {
    int deltaMente;   // Saude Mental
    int deltaSocial;  // Carisma/Interação
    int deltaSaude;   // Saude Física
    int deltaNotas;   // Desempenho Acadêmico
    int deltaFaltas;  // Frequência (se chegar a 100% de faltas, reprova)

    // Construtor
    ImpactoStats(int m = 0, int soc = 0, int sau = 0, int n = 0, int f = 0)
        : deltaMente(m), deltaSocial(soc), deltaSaude(sau), deltaNotas(n), deltaFaltas(f) {}
};

// Define o "tipo" de nó para sabermos como o jogo deve reagir
enum class EventoTipo { 
    NARRATIVA,      // Um evento normal da história (2 botões)
    ESCOLHA_ARQUETIPO, // Evento especial para definir status iniciais
    FINAL_SEMESTRE, // Um final de semestre (1 botão "próximo")
    FINAL_JOGO      // Um final definitivo (sem botões)
};

// Esta classe É O NÓ da Árvore Binária
class Evento {
public:
    std::string descricao;
    std::string idBackground;
    std::string textoOpcaoEsq;
    std::string textoOpcaoDir;
    EventoTipo tipo; // Guarda o tipo do evento

    ImpactoStats impactoEsq;
    ImpactoStats impactoDir;

    //  A ÁRVORE BINÁRIA ESTÁ AQUI
    Evento* proximoEventoEsq;    // Ponteiro para o filho da ESQUERDA
    Evento* proximoEventoDir;    // Ponteiro para o filho da DIREITA
    // ----------------------------------

    // Construtor principal (para nós de narrativa)
    Evento(std::string desc, std::string bg, std::string opE, std::string opD)
        : descricao(desc), idBackground(bg), 
          textoOpcaoEsq(opE), textoOpcaoDir(opD),
          tipo(EventoTipo::NARRATIVA),
          proximoEventoEsq(nullptr), proximoEventoDir(nullptr) {}

    // Construtor para FINAIS ou ESPECIAIS
    Evento(std::string descFinal, std::string bg, EventoTipo t)
        : descricao(descFinal), idBackground(bg),
          textoOpcaoEsq(""), textoOpcaoDir(""),
          tipo(t), 
          proximoEventoEsq(nullptr), proximoEventoDir(nullptr) {}

    // Verifica se é um nó folha (um final de qualquer tipo)
    bool isFinal() const {
        return tipo == EventoTipo::FINAL_SEMESTRE || tipo == EventoTipo::FINAL_JOGO;
    }
};

#endif