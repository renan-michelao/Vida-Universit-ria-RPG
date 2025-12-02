#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <algorithm>
#include <map> // Adicionado para flags genéricas
#include "Evento.h"

enum class Arquetipo { INDEFINIDO, HERDEIRO, REBELDE, MASCOTE, NERDOLA };

/// @brief Classe que representa o estado completo do jogador.
class Player {
private:
    int mente, social, saude, notas, faltas;
    int semestre;

    Arquetipo arquetipo;
    std::string nomeNamorada;
    std::string statusRelacionamento;
    std::string projetoExtensao;
    std::string emprego;
    
    // Rastreamento academico
    std::vector<std::string> dps; 
    std::vector<std::string> aprovadas;
    
    // Flags de narrativa (Ex: "FoiNaTusca", "BeijouAlice", "EstagioApple")
    std::map<std::string, bool> storyFlags; 

public:
    Player() { reset(); }

    void reset() {
        mente = 50; social = 50; saude = 50; notas = 50; faltas = 0;
        semestre = 0; 
        arquetipo = Arquetipo::INDEFINIDO;
        nomeNamorada = ""; statusRelacionamento = "Solteiro";
        projetoExtensao = "Nenhum"; emprego = "Desempregado";
        dps.clear(); aprovadas.clear(); storyFlags.clear();
    }

    // --- Gestão de Flags (C++20 style) ---
    void setFlag(const std::string& key, bool val) { storyFlags[key] = val; }
    bool getFlag(const std::string& key) const {
        return storyFlags.contains(key) ? storyFlags.at(key) : false;
    }

    // --- Gestão Acadêmica ---
    void adicionarDP(std::string materia) { dps.push_back(materia); }
    
    void removerDP(std::string materia) {
        std::erase(dps, materia); // C++20 std::erase para vector
    }

    void adicionarAprovacao(std::string materia) {
        aprovadas.push_back(materia);
        removerDP(materia); 
    }

    bool temDP(std::string materia) const {
        return std::ranges::find(dps, materia) != dps.end(); // C++20 ranges
    }

    bool passouEm(std::string materia) const {
        return std::ranges::find(aprovadas, materia) != aprovadas.end(); // C++20 ranges
    }

    // Mantendo setters/getters originais e lógica de arquetipo...
    void setArquetipo(Arquetipo tipo) {
        arquetipo = tipo;
        switch (tipo) {
            case Arquetipo::HERDEIRO: mente=25; social=55; saude=85; faltas=0; notas=55; break; 
            case Arquetipo::REBELDE:  mente=85; social=55; saude=25; faltas=0; notas=55; break; 
            case Arquetipo::MASCOTE:  mente=25; social=85; saude=55; faltas=0; notas=25; break; 
            case Arquetipo::NERDOLA:  mente=85; social=25; saude=25; faltas=0; notas=85; break; 
            default: break;
        }
    }

    void aplicarImpacto(const struct ImpactoStats& impacto); // Forward declaration para manter compatibilidade
    
    // Getters simples
    int getMente() const { return mente; }
    int getSocial() const { return social; }
    int getSaude() const { return saude; }
    int getNotas() const { return notas; }
    int getFaltas() const { return faltas; }
    int getSemestre() const { return semestre; }
    std::string getNomeNamorada() const { return nomeNamorada; }
    std::string getStatusRelacionamento() const { return statusRelacionamento; }
    std::string getProjeto() const { return projetoExtensao; }
    std::string getEmprego() const { return emprego; }
    
    void setNamorada(std::string n, std::string s) { nomeNamorada = n; statusRelacionamento = s; }
    void setProjeto(std::string p) { projetoExtensao = p; }
    void setEmprego(std::string e) { emprego = e; }

    // Helpers de lógica
    void limitStats() {
        mente = std::clamp(mente, 0, 100);
        social = std::clamp(social, 0, 100);
        saude = std::clamp(saude, 0, 100);
        notas = std::clamp(notas, 0, 100);
        faltas = std::clamp(faltas, 0, 100);
    }

    void avancarSemestre() {
        semestre++;
        mente += 10; saude += 10; faltas = 0; notas = 50; 
        limitStats();
    }

    bool isSobrecarregado() const {
        return (emprego != "Desempregado" && emprego != "Procurando") && (projetoExtensao != "Nenhum");
    }

    bool isGameOver() const {
        if (mente <= 0 || saude <= 0) return true;
        if (dps.size() >= 4) return true; // Jubilamento [cite: 15]
        return false;
    }

    std::string getGameOverReason() const {
        if (mente <= 0) return "Burnout Total. Voce trancou o curso.";
        if (saude <= 0) return "Colapso fisico. Internacao necessaria.";
        if (dps.size() >= 4) return "JUBILADO! Voce atingiu o limite critico de reprovacoes.";
        return "Fim de Jogo.";
    }
};

// Implementação inline para resolver dependência circular simples

inline void Player::aplicarImpacto(const ImpactoStats& impacto) {
    mente += impacto.deltaMente;
    social += impacto.deltaSocial;
    saude += impacto.deltaSaude;
    notas += impacto.deltaNotas;
    faltas += impacto.deltaFaltas;
    if (isSobrecarregado()) { mente -= 5; saude -= 5; }
    limitStats();
}

#endif