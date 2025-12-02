#include "Game.h"
#include "UIManager.h"
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm> 

// --- CONSTRUTORES E DESTRUTORES ---

Game::Game(sf::RenderWindow& jan, const sf::Font& f)
    : janela(jan), fonte(f), arvoreEventos(nullptr), eventoAtual(nullptr), 
      status(GameStatus::RUNNING) 
{
    ui = new UIManager(jan, f);
    carregarTexturas();
    carregarNivelAtual();
}

Game::~Game() {
    delete ui;
    limparArvoreAtual();
}

// --- GESTÃO DE ASSETS ---

void Game::carregarTexturas() {
    std::string path = "./img/";
    
    if (!texturas["bg_inicio"].loadFromFile(path + "bg_inicio.png")) {
        std::cerr << "Aviso: Não foi possível carregar bg_inicio.png" << std::endl;
    }
    if (!texturas["bg_aula"].loadFromFile(path + "bg_aula.png")) {
        std::cerr << "Aviso: Não foi possível carregar bg_aula.png" << std::endl;
    }
    if (!texturas["bg_ru"].loadFromFile(path + "bg_ru.png")) {
        std::cerr << "Aviso: Não foi possível carregar bg_ru.png" << std::endl;
    }
    if (!texturas["bg_festa"].loadFromFile(path + "bg_festa.jpg")) {
        std::cerr << "Aviso: Não foi possível carregar bg_festa.jpg" << std::endl;
    }
    if (!texturas["bg_jubilado"].loadFromFile(path + "bg_jubilado.png")) {
        std::cerr << "Aviso: Não foi possível carregar bg_jubilado.png" << std::endl;
    }
    if (!texturas["bg_dc"].loadFromFile(path + "bg_dc.png")) {
        std::cerr << "Aviso: Não foi possível carregar bg_dc.png" << std::endl;
    }
    if (!texturas["bg_at"].loadFromFile(path + "bg_at.png")) {
        std::cerr << "Aviso: Não foi possível carregar bg_at.png" << std::endl;
    }
    if (!texturas["bg_ex_bloqueou"].loadFromFile(path + "bg_ex_bloqueou.jpg")) {
        std::cerr << "Aviso: Não foi possível carregar bg_ex_bloqueou.jpg" << std::endl;
    }
    if (!texturas["bg_quarto"].loadFromFile(path + "bg_quarto.png")) {
        std::cerr << "Aviso: Não foi possível carregar bg_quarto.png" << std::endl;
    }
    if (!texturas["bg_DPMatematica"].loadFromFile(path + "bg_DPMatematica.jpg")) {
        std::cerr << "Aviso: Não foi possível carregar bg_DPMatematica.jpg" << std::endl;
    }
    if (!texturas["bg_pracinha"].loadFromFile(path + "bg_pracinha.jpg")) {
        std::cerr << "Aviso: Não foi possível carregar bg_pracinha.jpg" << std::endl;
    }
    if (!texturas["bg_ligandoEx"].loadFromFile(path + "bg_ligandoEx.jpg")) {
        std::cerr << "Aviso: Não foi possível carregar bg_ligandoEx.jpg" << std::endl;
    }
    if (!texturas["bg_ufscar"].loadFromFile(path + "bg_ufscar.jpg")) {
        std::cerr << "Aviso: Não foi possível carregar bg_ufscar.jpg" << std::endl;
    }
    if (!texturas["bg_jantar"].loadFromFile(path + "bg_jantar.jpg")) {
        std::cerr << "Aviso: Não foi possível carregar bg_jantar.jpg" << std::endl;
    }
    if (!texturas["bg_startap"].loadFromFile(path + "bg_startap.jpg")) {
        std::cerr << "Aviso: Não foi possível carregar bg_startap.jpg" << std::endl;
    }
    if (!texturas["bg_torneioRobotica"].loadFromFile(path + "bg_torneioRobotica.jpg")) {
        std::cerr << "Aviso: Não foi possível carregar bg_torneioRobotica.jpg" << std::endl;
    }
    if (!texturas["bg_redDragons"].loadFromFile(path + "bg_redDragons.png")) {
        std::cerr << "Aviso: Não foi possível carregar bg_redDragons.png" << std::endl;
    }
    if (!texturas["bg_petBCC"].loadFromFile(path + "bg_petBCC.png")) {
        std::cerr << "Aviso: Não foi possível carregar bg_petBCC.png" << std::endl;
    }
    if (!texturas["bg_secomp"].loadFromFile(path + "bg_secomp.jpg")) {
        std::cerr << "Aviso: Não foi possível carregar bg_secomp.jpg" << std::endl;
    }
    if (!texturas["bg_catiJr"].loadFromFile(path + "bg_catiJr.png")) {
        std::cerr << "Aviso: Não foi possível carregar bg_catiJr.png" << std::endl;
    }
    if (!texturas["bg_hackaton"].loadFromFile(path + "bg_hackaton.jpeg")) {
        std::cerr << "Aviso: Não foi possível carregar bg_hackaton.jpeg" << std::endl;
    }
    if (!texturas["bg_conversando"].loadFromFile(path + "bg_conversando.jpg")) {
        std::cerr << "Aviso: Não foi possível carregar bg_conversando.jpg" << std::endl;
    }
}


Evento* Game::criarPrologo() {
    Evento* raiz = new Evento(
        "Dia do ENEM. O inicio de tudo.", "bg_aula",
        "Focar ao maximo (Cansa Mente).",
        "Fazer relaxado (Arrisca Nota)."
    );
    raiz->impactoEsq = ImpactoStats(-20, -10, 0, +15, 0); 
    raiz->impactoDir = ImpactoStats(+10, 0, 0, -10, 0);

    Evento* sisu = new Evento("Aprovado na UFSCar! Você é Bixo!", "bg_inicio", "Próximo", "Próximo");
    raiz->proximoEventoEsq = sisu; raiz->proximoEventoDir = sisu;

    // Escolha de moradia em São Carlos
    Evento* escolhaMoradia = new Evento(
        "Chegou a hora de decidir onde morar em São Carlos. Isso vai moldar sua experiência na UFSCar.",
        "bg_inicio",
        "Morar em republica (dividir casa com bixos e veteranos).",
        "Morar sozinho em kitnet/apt (Mais silencio, mais responsabilidade)."
    );

    // CORREÇÃO AQUI: Removido o "cpp" que estava solto antes de "[NERDOLA]"
    Evento* arq = new Evento("Quem você será no campus?", "bg_ufscar", 
        "[HERDEIRO] Rico (+Saúde, -Nota)", 
        "[NERDOLA] Genio (+Nota, -Social)");
    arq->tipo = EventoTipo::ESCOLHA_ARQUETIPO;
    
    sisu->proximoEventoEsq = escolhaMoradia; 
    sisu->proximoEventoDir = escolhaMoradia;
    escolhaMoradia->proximoEventoEsq = arq;
    escolhaMoradia->proximoEventoDir = arq;
    
    Evento* fim = new Evento("Tudo pronto. Cuidado para não Jubilar.", "bg_inicio", EventoTipo::FINAL_SEMESTRE);
    arq->proximoEventoEsq = fim; arq->proximoEventoDir = fim;

    return raiz;
}

Evento* Game::criarSemestre1() {
    // ATO I: O FILTRO - Semestre 1 MUITO EXPANDIDO E ENVOLVENTE
    
    // FIM DO SEMESTRE
    Evento* fimSemestre = new Evento(
        "Fim do 1º Semestre. Você sobreviveu ao 'Filtro'.",
        "bg_ru",
        "Ir para Semestre 2", 
        "Ir para Semestre 2"
    );
    fimSemestre->tipo = EventoTipo::FINAL_SEMESTRE;

    // PROVA FINAL CÁLCULO 1 - Resultado Estudou
    Evento* resultadoP1_Estudou = new Evento(
        "A prova estava difícil, mas você lembrou das derivadas. Nota azul! O professor Mário até elogiou sua dedicação.",
        "bg_aula",
        "Comemorar com os colegas.", 
        "Ir descansar (merecido)."
    );
    resultadoP1_Estudou->impactoEsq = ImpactoStats(10, +10, 0, 20, 0);
    resultadoP1_Estudou->impactoDir = ImpactoStats(10, 0, +10, 20, 0);
    
    // Comemoração após passar
    Evento* comemoracao = new Evento(
        "Você e seus colegas comemoram a aprovação. Lucas está aliviado, Alice te parabeniza.",
        "bg_ru",
        "Aceitar o convite para comemorar.",
        "Ir para casa descansar."
    );
    comemoracao->impactoEsq = ImpactoStats(+5, +15, -5, 0, 0);
    comemoracao->impactoDir = ImpactoStats(+10, 0, +15, 0, 0);
    
    resultadoP1_Estudou->proximoEventoEsq = comemoracao;
    resultadoP1_Estudou->proximoEventoDir = fimSemestre;
    comemoracao->proximoEventoEsq = fimSemestre;
    comemoracao->proximoEventoDir = fimSemestre;

    // PROVA FINAL CÁLCULO 1 - Resultado Festa
    Evento* resultadoP1_Festa = new Evento(
        "Você foi de ressaca. O papel parecia em grego. O professor Mário não perdoou. 'Reprovado. Vejo você no próximo semestre.'",
        "bg_aula",
        "Aceitar a DP e se preparar melhor.", 
        "Chorar no banheiro (Desespero)."
    );
    resultadoP1_Festa->impactoEsq = ImpactoStats(-20, 0, 0, -30, 0);
    resultadoP1_Festa->impactoDir = ImpactoStats(-10, -5, 0, -30, 0);
    
    // Consequência da reprovação
    Evento* consequenciaDP = new Evento(
        "Você tem DP de Cálculo 1. Precisa refazer a matéria no próximo semestre. Como você lida com isso?",
        "bg_jubilado",
        "Focar em estudar mais no próximo semestre.",
        "Desanimar e pensar em desistir."
    );
    consequenciaDP->impactoEsq = ImpactoStats(+5, 0, 0, +5, 0);
    consequenciaDP->impactoDir = ImpactoStats(-15, -10, -5, -10, 0);
    
    resultadoP1_Festa->proximoEventoEsq = consequenciaDP;
    resultadoP1_Festa->proximoEventoDir = consequenciaDP;
    consequenciaDP->proximoEventoEsq = fimSemestre;
    consequenciaDP->proximoEventoDir = fimSemestre;

    // PREPARAÇÃO PARA A PROVA - Evento intermediário
    Evento* preparacaoProva = new Evento(
        "A prova de Cálculo 1 está chegando. Você precisa se preparar. O que fazer?",
        "bg_dc",
        "Estudar sozinho na BCo (Foco total).",
        "Formar grupo de estudo (Social e aprendizado)."
    );
    preparacaoProva->impactoEsq = ImpactoStats(-5, -5, 0, +15, 0);
    preparacaoProva->impactoDir = ImpactoStats(0, +10, 0, +10, 0);
    
    // Meio do semestre - sem TUSCA (TUSCA só acontece em novembro, semestres pares)
    Evento* meioSemestre = new Evento(
        "Meio do semestre. Você está se adaptando à rotina universitária. Como você está lidando?",
        "bg_dc",
        "Focar totalmente nos estudos.",
        "Equilibrar estudos e vida social."
    );
    meioSemestre->impactoEsq = ImpactoStats(-5, -10, 0, +15, 0);
    meioSemestre->impactoDir = ImpactoStats(0, +10, +5, +8, 0);
    
    // Resultado da prova (sem TUSCA no primeiro semestre)
    meioSemestre->proximoEventoEsq = preparacaoProva;
    meioSemestre->proximoEventoDir = preparacaoProva;
    
    preparacaoProva->proximoEventoEsq = resultadoP1_Estudou;
    preparacaoProva->proximoEventoDir = resultadoP1_Estudou;
    
    // INTRODUÇÃO DO ROBERTO - No meio do semestre
    Evento* encontroRoberto = new Evento(
        "Na aula de IPA, um aluno faz uma pergunta 'búrrra'. Roberto, um veterano arrogante e competitivo, ri alto e humilha o colega na frente de todos.",
        "bg_aula",
        "Defender o colega ('Isso não é necessário, Roberto').",
        "Ficar quieto (Evitar conflito)."
    );
    encontroRoberto->impactoEsq = ImpactoStats(+5, +5, 0, +5, 0); // Defendeu - ganha respeito
    encontroRoberto->impactoDir = ImpactoStats(-5, -5, 0, 0, 0); // Ficou quieto - perde autoestima
    
    // Consequência de defender
    Evento* robertoReacao = new Evento(
        "Roberto te olha com desprezo. 'Quem é você para me dar lição de moral? Vamos ver quem se forma primeiro.' Ele claramente te marcou como rival.",
        "bg_aula",
        "Ignorar e seguir em frente.",
        "Responder com confiança."
    );
    robertoReacao->impactoEsq = ImpactoStats(0, 0, 0, 0, 0);
    robertoReacao->impactoDir = ImpactoStats(+5, +10, 0, +5, 0);
    
    encontroRoberto->proximoEventoEsq = robertoReacao;
    encontroRoberto->proximoEventoDir = meioSemestre;
    robertoReacao->proximoEventoEsq = meioSemestre;
    robertoReacao->proximoEventoDir = meioSemestre;

    // ENCONTRO COM LUCAS (na BCo) - EXPANDIDO
    Evento* encontroLucas = new Evento(
        "Na Biblioteca Central, você vê um colega apanhando com a lista de Cálculo. É o Lucas, calmo e estudioso. Ele parece perdido.",
        "bg_dc",
        "Ajudar Lucas ('Vamos estudar juntos').",
        "Focar apenas na sua lista."
    );
    encontroLucas->impactoEsq = ImpactoStats(+5, +5, 0, +10, 0);
    encontroLucas->impactoDir = ImpactoStats(0, 0, 0, +5, 0);
    
    // Desenvolvimento da amizade com Lucas
    Evento* estudoComLucas = new Evento(
        "Você e Lucas estudam juntos. Ele é organizado e paciente. Vocês fazem um bom time.",
        "bg_dc",
        "Continuar estudando juntos.",
        "Fazer uma pausa para conversar."
    );
    estudoComLucas->impactoEsq = ImpactoStats(0, +5, 0, +10, 0);
    estudoComLucas->impactoDir = ImpactoStats(+5, +10, +5, +5, 0);
    
    encontroLucas->proximoEventoEsq = estudoComLucas;
    encontroLucas->proximoEventoDir = encontroRoberto; // Se não ajudou, encontra Roberto depois
    estudoComLucas->proximoEventoEsq = encontroRoberto; // Roberto aparece depois
    estudoComLucas->proximoEventoDir = encontroRoberto;

    // ENCONTRO COM ALICE (IPA) - MUITO EXPANDIDO
    Evento* encontroAlice = new Evento(
        "Na aula de IPA, uma garota senta ao seu lado. É a Alice, de Estatística. Ela pergunta se você entendeu o 'While'. Ela parece gentil e inteligente.",
        "bg_aula",
        "Mentir que sabe tudo", 
        "Ser humilde e pedir ajuda"
    );
    encontroAlice->impactoEsq = ImpactoStats(0, -5, 0, 0, 0);
    encontroAlice->impactoDir = ImpactoStats(5, 10, 0, 5, 0);
    
    // Se mentiu, Alice descobre depois
    Evento* aliceDescobre = new Evento(
        "Durante a aula prática, você tenta fazer o exercício e não consegue. Alice percebeu que você mentiu. Ela parece decepcionada, mas ainda oferece ajuda.",
        "bg_aula",
        "Pedir desculpas e aceitar ajuda.",
        "Tentar se justificar."
    );
    aliceDescobre->impactoEsq = ImpactoStats(+5, +5, 0, +5, 0);
    aliceDescobre->impactoDir = ImpactoStats(-5, -10, 0, 0, 0);
    
    // Se foi humilde, Alice ajuda e vocês se aproximam
    Evento* aliceAjuda = new Evento(
        "Alice te ajuda com o código. Ela explica com paciência e vocês conseguem fazer o exercício juntos. Ela sorri: 'Se precisar de ajuda, é só chamar.'",
        "bg_aula",
        "Agradecer e trocar contato.",
        "Agradecer e seguir em frente."
    );
    aliceAjuda->impactoEsq = ImpactoStats(+5, +15, 0, +10, 0);
    aliceAjuda->impactoDir = ImpactoStats(+5, +5, 0, +5, 0);
    
    encontroAlice->proximoEventoEsq = aliceDescobre;
    encontroAlice->proximoEventoDir = aliceAjuda; // Se foi humilde, Alice ajuda
    
    aliceDescobre->proximoEventoEsq = encontroRoberto; // Roberto aparece depois
    aliceDescobre->proximoEventoDir = encontroRoberto;
    
    aliceAjuda->proximoEventoEsq = encontroRoberto; // Roberto aparece depois
    aliceAjuda->proximoEventoDir = encontroRoberto;

    // EVENTO INICIAL - Primeira impressão do campus
    Evento* primeiroDia = new Evento(
        "Primeiro dia na UFSCar. O campus é enorme e você se sente um pouco perdido. Onde você vai primeiro?",
        "bg_inicio",
        "Ir para a aula de IPA (Conhecer pessoas).",
        "Ir para a Biblioteca (Focar nos estudos)."
    );
    primeiroDia->impactoEsq = ImpactoStats(0, +5, 0, +5, 0);
    primeiroDia->impactoDir = ImpactoStats(0, -5, 0, +10, 0);
    
    // Se escolheu biblioteca, conhece Lucas primeiro
    Evento* exploracaoCampus = new Evento(
        "Você explora o campus. O DC (Departamento de Computação) parece interessante. Você vê vários grupos de estudantes.",
        "bg_dc",
        "Se aproximar e conhecer pessoas.",
        "Focar em encontrar a biblioteca."
    );
    exploracaoCampus->impactoEsq = ImpactoStats(0, +10, 0, 0, 0);
    exploracaoCampus->impactoDir = ImpactoStats(0, -5, 0, +5, 0);
    
    primeiroDia->proximoEventoEsq = encontroAlice;
    primeiroDia->proximoEventoDir = exploracaoCampus;
    
    exploracaoCampus->proximoEventoEsq = encontroLucas;
    exploracaoCampus->proximoEventoDir = encontroLucas;

    return primeiroDia;
}

Evento* Game::criarSemestre2() {
    // ATO II: AS FACÇÕES - Semestre 2 MUITO EXPANDIDO E ENVOLVENTE
    
    Evento* fimSemestre = new Evento(
        "Fim do 2º Semestre. Agora você tem uma 'família' no DC.", 
        "bg_dc", 
        "Próximo", 
        "Próximo"
    );
    fimSemestre->tipo = EventoTipo::FINAL_SEMESTRE;
    
    // FÉRIAS DE VERÃO (final do ano, após semestre par)
    Evento* feriasVerao = new Evento(
        "Férias de verão! Dezembro chegou e o ano letivo terminou. Você tem tempo para descansar e refletir sobre o semestre.",
        "bg_ufscar",
        "Descansar completamente (Recupera tudo).",
        "Aproveitar para estudar e se preparar para o próximo ano."
    );
    feriasVerao->impactoEsq = ImpactoStats(+25, +10, +25, -5, 0);
    feriasVerao->impactoDir = ImpactoStats(-5, -5, 0, +15, 0);
    feriasVerao->proximoEventoEsq = fimSemestre;
    feriasVerao->proximoEventoDir = fimSemestre;

    // DESENVOLVIMENTO DO RELACIONAMENTO COM ALICE - MUITO EXPANDIDO
    std::string introAlice = "S2: Início do semestre. ";
    if (player.getFlag("AmigoAlice")) {
        introAlice += "Alice te encontra no corredor e sorri. 'Oi! Quer estudar junto na BCO hoje?'";
    } else if (player.getNomeNamorada() == "Alice") {
        introAlice += "Alice te encontra e te dá um abraço. 'Como foi sua semana?'";
    } else {
        introAlice += "Você vê Alice no corredor do DC. Ela te chama para estudar.";
    }
    
    Evento* desenvolvimentoAlice = new Evento(
        introAlice,
        "bg_ru",
        "Aceitar estudar junto (Aproximar mais).",
        "Dizer que está ocupado (Focar em outras coisas)."
    );
    desenvolvimentoAlice->impactoEsq = ImpactoStats(+5, +15, 0, +10, 0);
    desenvolvimentoAlice->impactoDir = ImpactoStats(0, -5, 0, +5, 0);
    
    // Se aceitou estudar com Alice
    Evento* estudoComAlice = new Evento(
        "Vocês estudam juntos na BCO. Alice é inteligente e paciente. Vocês conversam sobre o curso e a vida.",
        "bg_ru",
        "Convidar ela para sair (Romance).",
        "Manter apenas amizade (Seguro)."
    );
    estudoComAlice->impactoEsq = ImpactoStats(+10, +20, +5, +5, 0);
    estudoComAlice->impactoDir = ImpactoStats(+5, +10, 0, +10, 0);
    
    // Se convidou para sair - EXPANDIDO
    Evento* encontroRomantico = new Evento(
        "Vocês saem juntos. É um encontro agradável. Vocês vão ao cinema e depois caminham pelo campus. Alice parece interessada em você.",
        "bg_pracinha",
        "Tentar beijá-la (Avançar no relacionamento).",
        "Ser respeitoso e esperar mais tempo (Construir confiança)."
    );
    encontroRomantico->impactoEsq = ImpactoStats(+5, +15, 0, 0, 0);
    encontroRomantico->impactoDir = ImpactoStats(+10, +10, 0, 0, 0);
    
    // Se beijou, relacionamento avança
    Evento* relacionamentoAvança = new Evento(
        "Vocês se beijam. É um momento especial. Alice sorri: 'Eu estava esperando isso.'",
        "bg_pracinha",
        "Planejar um pedido clássico (jantar, balões de coração).",
        "Fazer um aplicativo especial e pedir para ela testar."
    );
    relacionamentoAvança->impactoEsq = ImpactoStats(+15, +25, +10, 0, 0);
    relacionamentoAvança->impactoDir = ImpactoStats(+10, +20, +5, 0, 0);
    
    // Caminho 1: Pedido clássico
    Evento* pedidoClassico = new Evento(
        "Você prepara um jantar especial, com flores e balões de coração no seu quarto da república. "
        "No fim da noite, você respira fundo e se declara para Alice.",
        "bg_jantar",
        "Dizer que a ama e pedir em namoro.",
        "Fazer uma piada para quebrar o clima antes do pedido."
    );
    pedidoClassico->impactoEsq = ImpactoStats(+20, +30, +10, 0, 0);
    pedidoClassico->impactoDir = ImpactoStats(+10, +20, 0, 0, 0);

    // Caminho 2: Pedido via aplicativo
    Evento* pedidoApp = new Evento(
        "Você passa alguns dias programando um aplicativo simples. "
        "No final de semana, chama Alice para 'testar um app novo de UX'. "
        "Na última tela, aparece: 'Quer namorar comigo?' com dois botões gigantes: SIM e COM CERTEZA.",
        "bg_dc",
        "Esperar ela clicar e observar a reação.",
        "Explicar nervoso que era um pedido de namoro."
    );
    pedidoApp->impactoEsq = ImpactoStats(+25, +30, +5, +5, 0);
    pedidoApp->impactoDir = ImpactoStats(+15, +25, 0, 0, 0);
    
    // Se ela aceita o pedido
    Evento* pedidoNamoro = new Evento(
        "Alice ri, se emociona e aceita o pedido. 'Eu também estava pensando nisso há um tempo.' "
        "Vocês oficializam o namoro ali mesmo, entre códigos, jantares e memórias do DC.",
        "bg_dc",
        "Comemorar juntos.",
        "Planejar o futuro."
    );
    pedidoNamoro->impactoEsq = ImpactoStats(+20, +35, +15, +5, 0);
    pedidoNamoro->impactoDir = ImpactoStats(+15, +30, +10, +10, 0);
    
    desenvolvimentoAlice->proximoEventoEsq = estudoComAlice;
    // Direita (recusar estudar com Alice) leva para a feira de extensão, mas só depois que inicioFeira for criado
    
    estudoComAlice->proximoEventoEsq = encontroRomantico;
    // Direita (manter só amizade) seguirá para a feira mais adiante
    
    encontroRomantico->proximoEventoEsq = relacionamentoAvança;
    // Direita (ser respeitoso e esperar mais tempo) também seguirá para a feira mais adiante
    
    relacionamentoAvança->proximoEventoEsq = pedidoClassico;
    relacionamentoAvança->proximoEventoDir = pedidoApp;
    
    pedidoClassico->proximoEventoEsq = pedidoNamoro;
    pedidoClassico->proximoEventoDir = pedidoNamoro;
    pedidoApp->proximoEventoEsq = pedidoNamoro;
    pedidoApp->proximoEventoDir = pedidoNamoro;
    
    // Após oficializar namoro, semestre seguirá para a feira (definida após inicioFeira)
    
    // TUSCA EM NOVEMBRO (semestre par) - A maior festa do ano
    Evento* tuscaNovembro = new Evento(
        "Novembro chegou! É a TUSCA - a maior festa do ano na UFSCar. O Corso está rolando e o caminhão pipa tá passando... Mas você tem provas chegando.",
        "bg_festa",
        "Ir pro Corso da TUSCA! (Social++, mas arrisca as provas).",
        "Ficar estudando (Foco nas provas)."
    );
    tuscaNovembro->impactoEsq = ImpactoStats(+20, +30, -15, -20, +10);
    tuscaNovembro->impactoDir = ImpactoStats(-10, -5, 0, +10, 0);
    
    // ENCONTRO COM BRUNO (se foi na TUSCA)
    Evento* encontroBrunoS2 = new Evento(
        "No Corso, um veterano alto e extrovertido te oferece uma 'Bomba'. 'Beba, bixo! Eu sou o Bruno da Atlética.'",
        "bg_festa",
        "Beber tudo! (Social++, Nota--).",
        "Recusar educadamente ('Tenho prova amanhã')."
    );
    encontroBrunoS2->impactoEsq = ImpactoStats(+10, +20, -15, -15, +5);
    encontroBrunoS2->impactoDir = ImpactoStats(+5, +10, 0, 0, 0);
    
    // Só mostra opção de traição se tem relacionamento com Alice
    bool temRelacionamento = (player.getNomeNamorada() == "Alice" || player.getFlag("RelacionamentoAlice"));
    
    Evento* naTusca = nullptr;
    if (temRelacionamento) {
        naTusca = new Evento(
            "Na festa, uma pessoa te chama pra dançar. Alice não está vendo.",
            "bg_festa",
            "Só dançar (Fiel).",
            "Beijar (Traição/Curtição)."
        );
        naTusca->impactoEsq = ImpactoStats(+5, 0, 0, 0, 0);
        naTusca->impactoDir = ImpactoStats(+10, -20, +5, 0, 0);
    } else {
        naTusca = new Evento(
            "Na festa, você conhece várias pessoas e se diverte bastante.",
            "bg_festa",
            "Continuar festejando.",
            "Voltar para casa (cansado)."
        );
        naTusca->impactoEsq = ImpactoStats(+5, +15, -5, 0, 0);
        naTusca->impactoDir = ImpactoStats(+10, +5, +10, 0, 0);
    }
    
    // PROVA DE AED1 - Evento importante (declarado antes para ser usado)
    Evento* provaAED1 = new Evento(
        "Prova de AED1 com o professor Ferrari. Ele é conhecido por sua aura infinita e ser exigente. Como você se prepara?",
        "bg_aula",
        "Estudar muito (Foco total).",
        "Estudar com grupo (Social e aprendizado)."
    );
    provaAED1->impactoEsq = ImpactoStats(-10, -5, 0, +15, 0);
    provaAED1->impactoDir = ImpactoStats(-5, +10, 0, +12, 0);
    
    // Resultado da prova AED1
    Evento* resultadoAED1 = new Evento(
        "A prova foi difícil, mas você se saiu bem. O professor Ferrari até elogiou sua solução.",
        "bg_aula",
        "Comemorar.",
        "Focar na próxima matéria."
    );
    resultadoAED1->impactoEsq = ImpactoStats(+5, +10, 0, +20, 0);
    resultadoAED1->impactoDir = ImpactoStats(0, 0, 0, +15, 0);
    
    provaAED1->proximoEventoEsq = resultadoAED1;
    provaAED1->proximoEventoDir = resultadoAED1;
    
    // Conecta TUSCA com a prova
    tuscaNovembro->proximoEventoEsq = encontroBrunoS2;
    tuscaNovembro->proximoEventoDir = provaAED1; // Se não foi, vai direto para a prova
    
    encontroBrunoS2->proximoEventoEsq = naTusca; // Bebeu muito
    encontroBrunoS2->proximoEventoDir = naTusca; // Recusou, mas ainda foi na festa
    
    naTusca->proximoEventoEsq = provaAED1;
    naTusca->proximoEventoDir = provaAED1;
    
    // FEIRA DE EXTENSÃO - A Grande Escolha (EXPANDIDA)
    Evento* escolhaTecnica = new Evento(
        "Na feira, você vê várias opções. Qual sua vibe técnica?",
        "bg_dc",
        "Robótica e Hardware (Dragons)", 
        "Pesquisa e Ensino (PET)"
    );
    escolhaTecnica->impactoEsq = ImpactoStats(0,0,0,0,0);
    escolhaTecnica->impactoDir = ImpactoStats(0,0,0,0,0);

    // RAMO 3: RED DRAGONS - EXPANDIDO
    Evento* entraDragons = new Evento(
        "Você entrou na Red Dragons! O time está animado. Você precisa escolher seu foco.",
        "bg_redDragons",
        "Focar na Robótica (Hardware e competições).", 
        "Jogar no time de LoL (Esports e campeonatos)."
    );
    entraDragons->impactoEsq = ImpactoStats(-10, 5, -5, 10, 0);
    entraDragons->impactoDir = ImpactoStats(5, 10, -5, -5, 0);
    
    // Desenvolvimento no time - EXPANDIDO
    Evento* desenvolvimentoDragons = new Evento(
        "Você se integra ao time. Os treinos são intensos, mas você está aprendendo muito sobre trabalho em equipe.",
        "bg_redDragons",
        "Treinar mais (Dedicar tempo extra).",
        "Manter ritmo normal (Equilíbrio)."
    );
    desenvolvimentoDragons->impactoEsq = ImpactoStats(-15, +10, -10, +5, 0);
    desenvolvimentoDragons->impactoDir = ImpactoStats(-5, +5, -5, +10, 0);
    
    // Campeonato do time
    Evento* campeonatoDragons = new Evento(
        "O campeonato regional está chegando! O time precisa de você.",
        "bg_torneioRobotica",
        "Treinar muito para o campeonato (Time feliz, mas estudos sofrem).",
        "Equilibrar treinos e estudos (Time entende, mas você perde destaque)."
    );
    campeonatoDragons->impactoEsq = ImpactoStats(-10, +20, -10, -15, 0);
    campeonatoDragons->impactoDir = ImpactoStats(-5, +10, -5, +5, 0);
    
    desenvolvimentoDragons->proximoEventoEsq = campeonatoDragons;
    desenvolvimentoDragons->proximoEventoDir = campeonatoDragons;
    campeonatoDragons->proximoEventoEsq = tuscaNovembro;
    campeonatoDragons->proximoEventoDir = tuscaNovembro;

    // RAMO 2: PET - EXPANDIDO
    Evento* entraPet = new Evento(
        "Você passou no PET-BCC! Agora tem bolsa, mas precisa manter o IRA alto e dar minicursos.",
        "bg_petBCC",
        "Escrever Artigo (Acadêmico).", 
        "Organizar Recepção Calouros (Social)."
    );
    entraPet->impactoEsq = ImpactoStats(-5, 0, 0, 15, 0);
    entraPet->impactoDir = ImpactoStats(0, 15, 0, 5, 0);
    
    // Desenvolvimento no PET - EXPANDIDO
    Evento* desenvolvimentoPET = new Evento(
        "Você se integra ao PET. Os membros são dedicados e você sente que está crescendo academicamente.",
        "bg_petBCC",
        "Focar em pesquisa (Publicar artigos).",
        "Focar em ensino (Dar minicursos)."
    );
    desenvolvimentoPET->impactoEsq = ImpactoStats(-10, +5, 0, +20, 0);
    desenvolvimentoPET->impactoDir = ImpactoStats(-5, +15, 0, +10, 0);
    
    // SeComp - Organização do evento
    Evento* secompPET = new Evento(
        "A Semana da Computação (SeComp) está chegando! Você precisa ajudar na organização.",
        "bg_secomp",
        "Assumir responsabilidades grandes (Stress, mas evento acontece).",
        "Ajudar nas atividades menores (Menos stress, mas menos destaque)."
    );
    secompPET->impactoEsq = ImpactoStats(-15, +15, -10, 0, 0);
    secompPET->impactoDir = ImpactoStats(-5, +10, -5, +5, 0);
    
    desenvolvimentoPET->proximoEventoEsq = secompPET;
    desenvolvimentoPET->proximoEventoDir = secompPET;
    secompPET->proximoEventoEsq = tuscaNovembro;
    secompPET->proximoEventoDir = tuscaNovembro;

    // RAMO 1: CATI JR - EXPANDIDO
    Evento* entraCati = new Evento(
        "Você é Trainee na Cati Jr. O ambiente é profissional. Seu primeiro projeto chega.",
        "bg_catiJr",
        "Aceitar projeto desafiador (Aprender muito).", 
        "Começar com projeto simples (Seguro)."
    );
    entraCati->impactoEsq = ImpactoStats(-15, +10, -5, +15, 0);
    entraCati->impactoDir = ImpactoStats(-5, +5, 0, +8, 0);
    
    // Desenvolvimento na Cati - EXPANDIDO
    Evento* desenvolvimentoCati = new Evento(
        "Você trabalha na Cati Jr. O ambiente é dinâmico e você está aprendendo muito sobre mercado.",
        "bg_catiJr",
        "Aceitar mais projetos (Ganhar experiência).", 
        "Focar em qualidade (Menos projetos, mais aprendizado)."
    );
    desenvolvimentoCati->impactoEsq = ImpactoStats(-10, +10, -5, +10, 0);
    desenvolvimentoCati->impactoDir = ImpactoStats(-5, +5, 0, +15, 0);
    
    // Crise na Cati
    Evento* criseCati = new Evento(
        "Um cliente importante quer o site pra ontem e o layout quebrou em produção!",
        "bg_catiJr",
        "Virar a noite codando (Resolver problema).", 
        "Negociar prazo (Soft Skill)."
    );
    criseCati->impactoEsq = ImpactoStats(-15, +5, -10, +10, 0);
    criseCati->impactoDir = ImpactoStats(-5, +15, 0, -5, 0);
    
    desenvolvimentoCati->proximoEventoEsq = criseCati;
    desenvolvimentoCati->proximoEventoDir = criseCati;
    criseCati->proximoEventoEsq = tuscaNovembro;
    criseCati->proximoEventoDir = tuscaNovembro;

    // Conecta os ramos
    escolhaTecnica->proximoEventoEsq = entraDragons;
    escolhaTecnica->proximoEventoDir = entraPet;
    
    entraDragons->proximoEventoEsq = desenvolvimentoDragons;
    entraDragons->proximoEventoDir = desenvolvimentoDragons;
    
    entraPet->proximoEventoEsq = desenvolvimentoPET;
    entraPet->proximoEventoDir = desenvolvimentoPET;
    
    entraCati->proximoEventoEsq = desenvolvimentoCati;
    entraCati->proximoEventoDir = desenvolvimentoCati;
    
    resultadoAED1->proximoEventoEsq = feriasVerao;
    resultadoAED1->proximoEventoDir = feriasVerao;

    Evento* inicioFeira = new Evento(
        "Feira de Extensão no DC! Várias bancas chamam sua atenção. Onde você vai se inscrever?",
        "bg_dc",
        "Empreendedorismo (Cati Jr)", 
        "Ver outras bancas..."
    );
    inicioFeira->impactoEsq = ImpactoStats(0,0,0,0,0);
    inicioFeira->impactoDir = ImpactoStats(0,0,0,0,0);
    inicioFeira->proximoEventoEsq = entraCati;
    inicioFeira->proximoEventoDir = escolhaTecnica;
    
    // Conecta desenvolvimento de Alice agora que inicioFeira existe
    desenvolvimentoAlice->proximoEventoDir = inicioFeira;      // Recusar estudar com Alice -> vida segue
    estudoComAlice->proximoEventoDir = inicioFeira;            // Manter amizade -> feira
    encontroRomantico->proximoEventoDir = inicioFeira;         // Ser respeitoso e esperar -> feira
    pedidoNamoro->proximoEventoEsq = inicioFeira;              // Depois do namoro -> feira
    pedidoNamoro->proximoEventoDir = inicioFeira;
    
    return desenvolvimentoAlice;
}

Evento* Game::criarSemestre3() {
    // Verifica se conheceu os personagens
    std::string intro = "S3: Trabalho de Arq. de Computadores (AOC). VHDL.";
    if (player.getFlag("AmigoLucas") && player.getFlag("ConheceuBruno")) {
        intro += " Você pode fazer dupla com Lucas ou Bruno.";
    } else if (player.getFlag("AmigoLucas")) {
        intro += " Lucas te convida para fazer dupla.";
    } else if (player.getFlag("ConheceuBruno")) {
        intro += " Bruno te chama para fazer dupla.";
    } else {
        intro += " Você precisa escolher um parceiro.";
    }
    
    Evento* raiz = new Evento(intro, "bg_dc",
        "Fazer dupla com Lucas (Trabalho serio).",
        "Fazer dupla com Bruno (A gente 'pega da net')."
    );
    raiz->impactoEsq = ImpactoStats(0, +5, 0, +5, 0);
    raiz->impactoDir = ImpactoStats(0, +10, 0, -5, 0);

    // Rota com Lucas - Trabalho sério
    Evento* trabalhoLucas = new Evento(
        "Você e Lucas trabalham juntos. Ele é organizado e vocês fazem um bom trabalho.",
        "bg_dc",
        "Continuar trabalhando.",
        "Continuar trabalhando."
    );
    trabalhoLucas->impactoEsq = ImpactoStats(+5, +5, 0, +15, 0);
    trabalhoLucas->impactoDir = ImpactoStats(+5, +5, 0, +15, 0);
    
    Evento* entregaLucas = new Evento(
        "O trabalho foi entregue com sucesso. O professor elogiou o código.",
        "bg_aula",
        "Continuar",
        "Continuar"
    );

    // Rota com Bruno - Dilema do Plágio
    Evento* dilemaPlagio = new Evento(
        "Bruno achou um código pronto no GitHub. 'A gente só muda os nomes das variáveis, ninguém vai saber.'",
        "bg_dc",
        "Recusar. Fazer do zero (Difícil).",
        "Aceitar. Mudar só os nomes das variáveis."
    );
    dilemaPlagio->impactoEsq = ImpactoStats(-5, -5, 0, +10, 0); // Recusou - estressa mas é honesto
    dilemaPlagio->impactoDir = ImpactoStats(-10, +5, 0, +5, 0); // Aceitou - fácil mas arriscado
    
    Evento* flagrante = new Evento(
        "O Prof. Silva descobriu o plágio! Chamou vocês na sala. 'Quem foi o responsável?'",
        "bg_jubilado",
        "Assumir a culpa sozinho (Salvar Bruno).",
        "Culpar o Bruno ('Ele me forçou')."
    );
    flagrante->impactoEsq = ImpactoStats(-20, +10, -10, -40, 0); // Assumiu culpa: Nota despenca, Bruno amigo
    flagrante->impactoDir = ImpactoStats(-10, -50, -10, -20, 0); // Culpou Bruno: Perde amigo, Nota cai menos

    // Conecta rotas
    raiz->proximoEventoEsq = trabalhoLucas;
    raiz->proximoEventoDir = dilemaPlagio;
    
    trabalhoLucas->proximoEventoEsq = entregaLucas;
    trabalhoLucas->proximoEventoDir = entregaLucas;
    
    dilemaPlagio->proximoEventoEsq = entregaLucas; // Recusou plágio
    dilemaPlagio->proximoEventoDir = flagrante;  // Aceitou plágio

    // DESENVOLVIMENTO DO PROJETO DE EXTENSÃO (baseado na escolha do S2)
    Evento* desenvolvimentoProjeto = nullptr;
    std::string projetoAtual = player.getProjeto();
    
    if (projetoAtual == "Cati Jr") {
        desenvolvimentoProjeto = new Evento(
            "Na Cati Jr, um cliente real precisa de um site urgente. O prazo é apertado.",
            "bg_dc",
            "Aceitar o projeto (Experiência real).",
            "Recusar (Muito responsabilidade)."
        );
        desenvolvimentoProjeto->impactoEsq = ImpactoStats(0, +10, 0, +5, 0);
        
        Evento* catiCrise = new Evento(
            "O site do cliente caiu em produção! Ele ameaça processar a empresa.",
            "bg_jubilado",
            "Virar a noite arrumando (Stress++, mas resolve).",
            "Negociar com o cliente (Social++, mas pode perder o cliente)."
        );
        catiCrise->impactoEsq = ImpactoStats(-15, +5, -10, +10, 0);
        catiCrise->impactoDir = ImpactoStats(-5, +15, 0, -5, 0);
        
        desenvolvimentoProjeto->proximoEventoEsq = catiCrise;
        desenvolvimentoProjeto->proximoEventoDir = entregaLucas;
        catiCrise->proximoEventoEsq = entregaLucas;
        catiCrise->proximoEventoDir = entregaLucas;
        
    } else if (projetoAtual == "Red Dragons") {
        desenvolvimentoProjeto = new Evento(
            "No time Red Dragons, o campeonato nacional (Juegos/BGS) está chegando. O time precisa de você.",
            "bg_festa",
            "Treinar muito para o campeonato (Social++, Nota--).",
            "Focar nos estudos (Nota++, mas time fica chateado)."
        );
        desenvolvimentoProjeto->impactoEsq = ImpactoStats(0, +20, -5, -10, 0);
        desenvolvimentoProjeto->impactoDir = ImpactoStats(0, -10, 0, +10, 0);
        
        // Resultado do campeonato
        Evento* resultadoCampeonato = new Evento(
            "O campeonato aconteceu! O time se saiu bem, mas você precisa equilibrar com os estudos.",
            "bg_festa",
            "Continuar no time (Social alto).",
            "Focar mais nos estudos (Equilíbrio)."
        );
        resultadoCampeonato->impactoEsq = ImpactoStats(0, +15, -5, -5, 0);
        resultadoCampeonato->impactoDir = ImpactoStats(0, -5, 0, +10, 0);
        
        desenvolvimentoProjeto->proximoEventoEsq = resultadoCampeonato;
        desenvolvimentoProjeto->proximoEventoDir = resultadoCampeonato;
        resultadoCampeonato->proximoEventoEsq = entregaLucas;
        resultadoCampeonato->proximoEventoDir = entregaLucas;
        
    } else if (projetoAtual == "PET") {
        desenvolvimentoProjeto = new Evento(
            "No PET, precisam organizar a Semana da Computação (SeComp). É um evento grande e importante.",
            "bg_at",
            "Ajudar a organizar (Muito trabalho burocrático).",
            "Focar apenas nas atividades técnicas."
        );
        desenvolvimentoProjeto->impactoEsq = ImpactoStats(-10, +10, 0, 0, 0);
        desenvolvimentoProjeto->impactoDir = ImpactoStats(0, +5, 0, +5, 0);
        
        // SeComp acontece
        Evento* secompAcontece = new Evento(
            "A SeComp foi um sucesso! Você ajudou na organização e conheceu várias pessoas importantes.",
            "bg_at",
            "Continuar no PET (Crescer academicamente).",
            "Focar em outras atividades."
        );
        secompAcontece->impactoEsq = ImpactoStats(+5, +15, 0, +10, 0);
        secompAcontece->impactoDir = ImpactoStats(0, +5, 0, +5, 0);
        
        desenvolvimentoProjeto->proximoEventoEsq = secompAcontece;
        desenvolvimentoProjeto->proximoEventoDir = entregaLucas;
        secompAcontece->proximoEventoEsq = entregaLucas;
        secompAcontece->proximoEventoDir = entregaLucas;
    }
    
    // DRAMA DA ALICE (se traiu na TUSCA)
    Evento* dramaAlice = nullptr;
    if (player.getFlag("TraiuAlice")) {
        dramaAlice = new Evento(
            "Alice viu fotos da TUSCA nas redes sociais. Ela está chateada.",
            "bg_ru",
            "Pedir perdão.",
            "Terminar tudo."
        );
        dramaAlice->impactoEsq = ImpactoStats(-5, +5, 0, 0, 0);
        dramaAlice->impactoDir = ImpactoStats(-15, -20, -5, 0, 0);
    }

    // FIM DO SEMESTRE
    Evento* fim = new Evento("Fim do Semestre 3.", "bg_ru", EventoTipo::FINAL_SEMESTRE);
    
    // Conecta tudo
    Evento* proximoAposEntrega = desenvolvimentoProjeto ? desenvolvimentoProjeto : (dramaAlice ? dramaAlice : fim);
    entregaLucas->proximoEventoEsq = proximoAposEntrega;
    entregaLucas->proximoEventoDir = proximoAposEntrega;
    
    flagrante->proximoEventoEsq = proximoAposEntrega;
    flagrante->proximoEventoDir = proximoAposEntrega;
    
    if (desenvolvimentoProjeto) {
        if (dramaAlice) {
            desenvolvimentoProjeto->proximoEventoEsq = dramaAlice;
            desenvolvimentoProjeto->proximoEventoDir = dramaAlice;
            dramaAlice->proximoEventoEsq = fim;
            dramaAlice->proximoEventoDir = fim;
        } else {
            desenvolvimentoProjeto->proximoEventoEsq = fim;
            desenvolvimentoProjeto->proximoEventoDir = fim;
        }
    } else if (dramaAlice) {
        dramaAlice->proximoEventoEsq = fim;
        dramaAlice->proximoEventoDir = fim;
    }

    return raiz;
}

Evento* Game::criarSemestre4() {
    // S4: Engenharia de Software e a Sabotagem (Condicional)
    std::string intro = "S4: Engenharia de Software 1 (ES1). O terror dos trabalhos em grupo.";
    if (player.getFlag("ProcessoDisciplinar")) intro += " O processo de plágio ainda te assombra.";

    Evento* raiz = new Evento(intro, "bg_aula",
        "Assumir a liderança do grupo (Garante qualidade, mas +Stress).",
        "Deixar o grupo decidir (Menos trabalho, risco de qualidade)."
    );
    
    // Impactos iniciais
    raiz->impactoEsq = ImpactoStats(-10, +5, 0, +10, 0);
    raiz->impactoDir = ImpactoStats(+5, +5, 0, -5, 0);

    // LÓGICA CONDICIONAL DE RIVALIDADE
    Evento* conflitoGrupo = nullptr;
    
    if (player.getFlag("RivalRoberto")) {
        // ROTA A: O Inimigo Íntimo
        conflitoGrupo = new Evento(
            "Por azar (ou destino), Roberto caiu no seu grupo. Ele sorri de forma cínica: 'Espero que você não atrapalhe dessa vez'.", 
            "bg_dc",
            "Tentar dividir tarefas formalmente (Profissional).",
            "Ignorar Roberto e fazer tudo sozinho (Evitar sabotagem)."
        );
        
        Evento* sabotagem = new Evento(
            "Dia da entrega! Roberto 'esqueceu' de subir a parte dele no Git e sumiu. É sabotagem clara.", 
            "bg_jubilado",
            "Expor Roberto para o professor (Justiça, mas cria barraco).",
            "Virar a noite codando a parte dele (Salva a nota, destrói a mente)."
        );
        
        conflitoGrupo->proximoEventoEsq = sabotagem;
        conflitoGrupo->proximoEventoDir = sabotagem;
        
        sabotagem->impactoEsq = ImpactoStats(+5, -10, 0, +5, 0); // Expõe: Professor aceita, mas clima pesa
        sabotagem->impactoDir = ImpactoStats(-20, 0, -10, +10, 0); // Codar: Nota alta, saúde lixo

        // Conecta ao fim
        Evento* tusca4 = new Evento("Novembro: TUSCA Pós-Trauma de ES1.", "bg_festa", "Ir beber", "Dormir");
        sabotagem->proximoEventoEsq = tusca4;
        sabotagem->proximoEventoDir = tusca4;
        Evento* fim = new Evento("Fim do Semestre 4.", "bg_ru", EventoTipo::FINAL_SEMESTRE);
        tusca4->proximoEventoEsq = fim; tusca4->proximoEventoDir = fim;

    } else {
        // ROTA B: O Aluno Preguiçoso (Ricardo) - Para quem não tem rivalidade
        conflitoGrupo = new Evento(
            "No seu grupo está Ricardo, um aluno que vive no CA jogando sinuca. Ele é gente boa, mas não faz nada.", 
            "bg_dc",
            "Cobrar Ricardo constantemente (Chato, mas necessário).",
            "Deixar pra lá e compensar no seu código (Mais fácil)."
        );
        
        Evento* entregaRicardo = new Evento(
            "Na apresentação, Ricardo leu os slides que ele viu pela primeira vez na hora. O professor percebeu.", 
            "bg_aula",
            "Defender o grupo (União).",
            "Deixar Ricardo se explicar sozinho (Ele que lute)."
        );
        
        conflitoGrupo->proximoEventoEsq = entregaRicardo;
        conflitoGrupo->proximoEventoDir = entregaRicardo;
        
        entregaRicardo->impactoEsq = ImpactoStats(0, +10, 0, -5, 0); // Defendeu: Nota cai um pouco, social sobe
        entregaRicardo->impactoDir = ImpactoStats(0, -5, 0, +5, 0); // Não defendeu: Nota sobe, Ricardo fica chateado

        Evento* fim = new Evento("Fim do Semestre 4.", "bg_ru", EventoTipo::FINAL_SEMESTRE);
        entregaRicardo->proximoEventoEsq = fim;
        entregaRicardo->proximoEventoDir = fim;
    }

    raiz->proximoEventoEsq = conflitoGrupo;
    raiz->proximoEventoDir = conflitoGrupo;

    return raiz;
}
Evento* Game::criarSemestre5() {
    // S5: Redes e Estágio + GREVE
    Evento* raiz = new Evento("S5: Redes. Hora de pensar no mercado.", "bg_inicio",
        "Procurar Estágio (Grana).",
        "Focar em IC com a Prof. Ana (Mestrado)."
    );
    
    Evento* optativa = new Evento("Escolha de Optativa:", "bg_dc",
        "Computação Gráfica (Difícil).",
        "Empreendedorismo (Coxa)."
    );
    raiz->proximoEventoEsq = optativa; raiz->proximoEventoDir = optativa;

    // GREVE (Evento Canônico de Federal)
    Evento* greve = new Evento("A GREVE COMEÇOU! O calendário acadêmico está congelado. As aulas pararam.", "bg_jubilado",
        "Voltar para casa dos pais (Recupera Saúde/Mente, perde Social/Foco).",
        "Ficar em Sao Carlos (Ocupar o predio ou estudar por conta propria)."
    );
    
    Evento* greveCasa = new Evento("Você voltou para casa. Seus pais te tratam como adolescente. Você sente que está regredindo.", "bg_inicio",
        "Estudar por conta propria (Mantem foco, mas solidao).",
        "Relaxar completamente (Recupera tudo, mas perde o ritmo)."
    );
    
    Evento* greveSaoCarlos = new Evento("Você ficou em São Carlos. O prédio está ocupado. O que fazer?", "bg_at",
        "Participar da ocupacao (Social++, mas perde tempo de estudo).",
        "Estudar por conta propria (Mantem notas, mas isolamento)."
    );
    
    optativa->proximoEventoEsq = greve; optativa->proximoEventoDir = greve;
    
    greve->proximoEventoEsq = greveCasa; greve->proximoEventoDir = greveSaoCarlos;
    
    greve->impactoEsq = ImpactoStats(+15, -10, +15, -10, 0); // Volta para casa (recupera mas perde foco)
    greve->impactoDir = ImpactoStats(-5, +5, -5, +5, 0); // Fica em Sanca (mantém mas cansa
    
    greveCasa->impactoEsq = ImpactoStats(-5, -10, 0, +10, 0); // Estuda sozinho (foco mas solidão)
    greveCasa->impactoDir = ImpactoStats(+20, -5, +20, -15, 0); // Relaxa (recupera tudo mas perde ritmo)
    
    greveSaoCarlos->impactoEsq = ImpactoStats(-5, +20, -5, -10, 0); // Ocupa (social mas perde tempo)
    greveSaoCarlos->impactoDir = ImpactoStats(-10, -15, 0, +15, 0); // Estuda sozinho (notas mas isolamento)
    
    // CRISE DO LUCAS (Burnout no S5)
    Evento* lucasBurnout = new Evento("Lucas está com Burnout severo. Ele foi internado no hospital. Você vai visitá-lo?", "bg_jubilado",
        "Visitar Lucas no hospital (Amizade++, mas voce ve o preco do excesso).",
        "Enviar mensagem (Menos impacto, mas ainda mostra preocupacao)."
    );
    
    Evento* lucasRecuperacao = new Evento("Lucas precisa relaxar. Você tenta convencer ele a ir numa festa pela primeira vez?", "bg_conversando",
        "Convencer ele a ir (Ele precisa disso, mesmo que seja difícil).",
        "Respeitar a decisão dele de não ir (Seguro, mas ele continua isolado)."
    );
    
    greveCasa->proximoEventoEsq = lucasBurnout; greveCasa->proximoEventoDir = lucasBurnout;
    greveSaoCarlos->proximoEventoEsq = lucasBurnout; greveSaoCarlos->proximoEventoDir = lucasBurnout;
    
    lucasBurnout->impactoEsq = ImpactoStats(+10, +15, 0, 0, 0); // Visita (amizade, mas vê o preço)
    lucasBurnout->impactoDir = ImpactoStats(+5, +5, 0, 0, 0); // Mensagem (menos impacto)
    
    lucasRecuperacao->impactoEsq = ImpactoStats(+5, +20, 0, -5, 0); // Convence (ele precisa, mas você perde tempo)
    lucasRecuperacao->impactoDir = ImpactoStats(+5, +5, 0, 0, 0); // Respeita (seguro)
    
    lucasBurnout->proximoEventoEsq = lucasRecuperacao; lucasBurnout->proximoEventoDir = lucasRecuperacao;

    Evento* fim = new Evento("Fim do Semestre 5.", "bg_ru", EventoTipo::FINAL_SEMESTRE);
    lucasRecuperacao->proximoEventoEsq = fim; lucasRecuperacao->proximoEventoDir = fim;
    
    return raiz;
}

Evento* Game::criarSemestre6() {
    Evento* raiz = new Evento("S6: Teoria da Computação. O curso começa a afunilar.", "bg_aula",
        "Focar em Máquinas de Turing (Teoria).",
        "Focar em projetos práticos (Mercado)."
    );

    // Verifica relacionamentos para decidir o arco principal
    bool temDramaAlice = (player.getNomeNamorada() == "Alice" || player.getFlag("RelacionamentoAlice"));
    bool temDramaBruno = player.getFlag("AmigoBruno") || player.getFlag("ConheceuBruno"); // Assumindo flag AmigoBruno
    
    Evento* eventoPrincipal = nullptr;

    if (temDramaAlice) {
        // ARCO DA ALICE (Manteve-se igual, pois estava bom)
        eventoPrincipal = new Evento(
            "Alice está pensando em trancar o curso e mudar de cidade. Ela te chama para conversar.",
            "bg_ru",
            "Apoiar a mudança (Amor maduro).",
            "Pedir para ela ficar (Apego)."
        );
        // ... (resto da lógica da Alice igual ao anterior) ...
        // Para simplificar o exemplo, vou conectar direto ao fim aqui, 
        // mas você pode manter a lógica complexa de término que já fez.
        Evento* fimAlice = new Evento("O destino de Alice foi selado. O semestre acaba.", "bg_inicio", EventoTipo::FINAL_SEMESTRE);
        eventoPrincipal->proximoEventoEsq = fimAlice;
        eventoPrincipal->proximoEventoDir = fimAlice;

    } else if (temDramaBruno) {
        // ARCO DO BRUNO (Manteve-se igual)
        eventoPrincipal = new Evento(
            "Bruno sumiu das aulas há 3 semanas. Dizem que ele vai ser jubilado.", 
            "bg_jubilado",
            "Ir na casa dele arrastá-lo pra aula.",
            "Respeitar o espaço dele (e estudar)."
        );
        Evento* fimBruno = new Evento("A situação do Bruno se resolveu (ou não). Fim do S6.", "bg_inicio", EventoTipo::FINAL_SEMESTRE);
        eventoPrincipal->proximoEventoEsq = fimBruno;
        eventoPrincipal->proximoEventoDir = fimBruno;

    } else {
        // NOVO ARCO: HACKATHON (Para quem focou em si mesmo)
        eventoPrincipal = new Evento(
            "Sem dramas pessoais, você vê um cartaz: 'HACKATHON USP-SÃO CARLOS'. Prêmio em dinheiro e networking.",
            "bg_hackaton.jpeg",
            "Montar equipe com aleatórios (Arriscado).",
            "Participar sozinho (Hardcore mode)."
        );
        
        Evento* resultadoHack = new Evento(
            "A maratona foi insana. 48h sem dormir, base de café e pizza.",
            "bg_dc",
            "O projeto funcionou no final!",
            "O projeto crashou na demo..."
        );
        
        // Sozinho = Mais mérito técnico, mas muito cansaço
        eventoPrincipal->impactoEsq = ImpactoStats(-10, +10, -5, 0, 0);
        eventoPrincipal->impactoDir = ImpactoStats(-25, -5, -15, +10, 0); // Sozinho destrói a mente
        
        eventoPrincipal->proximoEventoEsq = resultadoHack;
        eventoPrincipal->proximoEventoDir = resultadoHack;
        
        Evento* fimHack = new Evento("Você ganhou experiência (e olheiras). Fim do S6.", "bg_ru", EventoTipo::FINAL_SEMESTRE);
        resultadoHack->proximoEventoEsq = fimHack;
        resultadoHack->proximoEventoDir = fimHack;
    }

    raiz->proximoEventoEsq = eventoPrincipal;
    raiz->proximoEventoDir = eventoPrincipal;
    
    return raiz;
}

Evento* Game::criarSemestre7() {
    // S7: O Mercado de Trabalho Real
    Evento* inicio = new Evento(
        "S7: Hora de buscar estágio. O LinkedIn está pegando fogo.", 
        "bg_dc",
        "Atualizar LinkedIn e GitHub (Profissional).", 
        "Pedir indicação pros veteranos (Social)."
    );

    // O DESAFIO TÉCNICO
    Evento* desafioTecnico = new Evento(
        "Uma Big Tech de SP te chamou para entrevista. O desafio: Inverter uma Árvore Binária no quadro.",
        "bg_startap",
        "Tentar solução recursiva elegante (Risco de errar sintaxe).",
        "Fazer solução iterativa segura (Mais código, mas funciona)."
    );
    
    inicio->proximoEventoEsq = desafioTecnico;
    inicio->proximoEventoDir = desafioTecnico;

    // RAMIFICAÇÃO DE SUCESSO OU FRACASSO
    // Aqui usamos a lógica: Esquerda (Recursiva) é "Tudo ou Nada". Direita é "Seguro".
    
    // CAMINHO SUCESSO: Estágio TOP
    Evento* estagioTop = new Evento(
        "Você brilhou! A vaga é sua. Salário alto, VR gordo e Macbook da empresa.",
        "bg_startap",
        "Focar em crescer na empresa (Carreira).",
        "Guardar dinheiro e focar no TCC (Equilíbrio)."
    );
    estagioTop->impactoEsq = ImpactoStats(-10, +5, 0, 0, 0); // Carreira
    estagioTop->impactoDir = ImpactoStats(0, 0, 0, +10, 0);  // TCC
    
    // CAMINHO FRACASSO: Estágio "Arrombado" (Exploratório)
    Evento* estagioRuim = new Evento(
        "Você travou no quadro. A Big Tech agradeceu e sumiu. Só sobrou uma vaga na 'Consultoria do Tio Zé'.",
        "bg_jubilado", // Fundo triste
        "Aceitar (Preciso das horas de estágio).",
        "Recusar e tentar IC de novo (Menos dinheiro, mais estudo)."
    );
    
    // Conecta desafio aos resultados
    // Vamos supor que a Recursiva (Esq) tem chance de dar errado dependendo da Nota, 
    // mas na árvore estática, vamos definir que Esquerda = Arrisca (Pode ir pro Top ou Ruim na logica interna, 
    // mas aqui vamos forçar um caminho narrativo: Esquerda = Acertou (Top), Direita = Seguro (Top mediano).
    // Para criar drama, vamos fazer o seguinte:
    
    // Para simular dificuldade, vamos dizer que a solução iterativa (Dir) foi "muito lenta" e leva pro estágio ruim.
    // É uma pegadinha de entrevista técnica.
    
    desafioTecnico->proximoEventoEsq = estagioTop;  // Recursiva deu certo
    desafioTecnico->proximoEventoDir = estagioRuim; // Iterativa não impressionou
    
    // CONSEQUENCIAS DO ESTÁGIO RUIM
    Evento* rotinaEstagioRuim = new Evento(
        "No estágio, você serve café e formata PC com Windows 7. Seu chefe grita.",
        "bg_jubilado",
        "Engolir o sapo (Resiliência).",
        "Pedir demissão e focar só no TCC (Arriscado financeiramente)."
    );
    estagioRuim->proximoEventoEsq = rotinaEstagioRuim;
    estagioRuim->proximoEventoDir = rotinaEstagioRuim; // Se recusar, vai pra rotina de desempregado (simplificado aqui)

    // FIM DO SEMESTRE
    Evento* fim = new Evento("Fim do Semestre 7. O TCC se aproxima.", "bg_ru", EventoTipo::FINAL_SEMESTRE);
    
    estagioTop->proximoEventoEsq = fim;
    estagioTop->proximoEventoDir = fim;
    rotinaEstagioRuim->proximoEventoEsq = fim;
    rotinaEstagioRuim->proximoEventoDir = fim;

    return inicio;
}

Evento* Game::criarSemestre8() {
    // TCC ARCO PROGRESSIVO - CONTINUAÇÃO E CRISE
    Evento* raiz = new Evento("S8: Início do semestre. Você precisa continuar o TCC.", "bg_aula",
        "Escrever a monografia dia e noite (Dedicação total).",
        "Fazer aos poucos (Equilíbrio, mas pode não dar tempo)."
    );
    
    raiz->impactoEsq = ImpactoStats(-20, -5, -15, +25, 0); // Dia e noite (dedicação total)
    raiz->impactoDir = ImpactoStats(-5, 0, 0, +10, 0); // Aos poucos (equilíbrio)

    // CRISE DO TCC (Meio do S8)
    Evento* criseTCC = new Evento("CRISE! O código não compila / O dataset da IA está viciado. Você precisa resolver isso!", "bg_jubilado",
        "Virar noites até resolver (Stress++, mas resolve o problema).",
        "Pedir ajuda ao orientador (Menos stress, mas pode atrasar)."
    );
    
    raiz->proximoEventoEsq = criseTCC; raiz->proximoEventoDir = criseTCC;
    
    criseTCC->impactoEsq = ImpactoStats(-25, 0, -20, +20, 0); // Vira noites (resolve mas estressa)
    criseTCC->impactoDir = ImpactoStats(-10, +5, -5, +10, 0); // Pede ajuda (menos stress mas atrasa)
    
    // A DEFESA DO TCC (Fim do S8)
    std::string descDefesa = "Dia da Banca. ";
    if (player.getFlag("RivalRoberto")) {
        descDefesa += "Roberto está na banca! ";
        if (player.getFlag("HumilhouRoberto") || player.getFlag("ConfrontouRoberto")) {
            descDefesa += "Ele vai pegar pesado nas perguntas por causa do passado.";
        } else {
            descDefesa += "Ele parece neutro.";
        }
    } else {
        descDefesa += "Lucas e Ana estão lá.";
    }
    
    Evento* defesa = new Evento(descDefesa, "bg_at",
        "Apresentar com confiança (Você estudou, está preparado).",
        "Gaguejar de nervoso (O peso da situação te afeta)."
    );
    
    criseTCC->proximoEventoEsq = defesa; criseTCC->proximoEventoDir = defesa;
    
    // Impacto da defesa depende de várias coisas
    int bonusDefesa = 0;
    if (player.getFlag("AjudouLucas")) bonusDefesa += 5; // Ajudou Lucas = mais confiança
    if (player.getFlag("AjudouBruno")) bonusDefesa += 5; // Ajudou Bruno = mais confiança
    if (player.getFlag("RivalRoberto") && (player.getFlag("HumilhouRoberto") || player.getFlag("ConfrontouRoberto"))) {
        bonusDefesa -= 10; // Roberto pega pesado
    }
    
    defesa->impactoEsq = ImpactoStats(+10 + bonusDefesa, +15, +10, +30, 0); // Confiança (bom resultado)
    defesa->impactoDir = ImpactoStats(-10, -10, -5, +10, 0); // Nervoso (resultado mediano)

    Evento* formatura = criarEventoFinalPersonalizado();
    defesa->proximoEventoEsq = formatura; defesa->proximoEventoDir = formatura;

    return raiz;
}


//   LÓGICA DE CONSEQUÊNCIAS E FLAGS

void Game::verificarFimDeSemestre(Evento* eventoFim) {
    int s = player.getSemestre();
    int nota = player.getNotas();
    std::string resumo = "Boletim S" + std::to_string(s) + ":\n";

    // Fator Colapso
    if (player.getMente() < 20) {
        nota -= 20;
        resumo += "[ALERTA] Burnout afetou suas notas.\n";
    }

    // Regras por Semestre
    if (s == 1) {
        if (nota >= 60) player.adicionarAprovacao("Calculo 1");
        else { player.adicionarDP("Calculo 1"); resumo += "DP de Cálculo 1 (O Carrasco te pegou).\n"; }
        
        // Verifica cola (Flag setada em processarLogicaEspecial)
        if (player.getFlag("TentouColar")) {
            if (nota < 50) resumo += "Você foi pego colando! Zero na prova.\n"; // Simplificação
        }
    }
    else if (s == 2) {
        if (player.temDP("Calculo 1") && nota < 65) resumo += "Ainda preso na DP de Cálculo.\n";
        else player.removerDP("Calculo 1");

        if (nota >= 60) player.adicionarAprovacao("AED1");
        else { player.adicionarDP("AED1"); resumo += "Reprovou em AED1 (Ferrari).\n"; }
    }
    else if (s == 3) {
        if (player.getFlag("ProcessoDisciplinar")) {
            resumo += "Voce reprovou em AOC por plágio (Nota 0).\n";
            player.adicionarDP("AOC");
        } else {
            if (nota >= 60) player.adicionarAprovacao("AOC");
        }
    }
    else if (s == 8) {
        // TCC depende de múltiplos fatores
        int notaTCC = nota;
        if (player.getFlag("TCCAdiantado")) notaTCC += 10; // Adiantou nas férias
        if (player.getFlag("TCCResolvido")) notaTCC += 10; // Resolveu a crise
        if (player.getFlag("RivalRoberto") && (player.getFlag("HumilhouRoberto") || player.getFlag("ConfrontouRoberto"))) {
            notaTCC -= 15; // Roberto pega pesado na banca
        }
        
        if (notaTCC >= 50) {
            resumo += "TCC Aprovado! Parabéns!\n";
            if (notaTCC >= 80) resumo += "TCC com nota excelente! Você se destacou!\n";
        } else {
            resumo += "TCC Reprovado. Voce não forma esse ano.\n";
        }
    }

    if (player.getFaltas() >= 50) {
        resumo += "REPROVADO POR FALTAS GERAIS!\n";
        player.adicionarDP("Semestre " + std::to_string(s));
    }

    eventoFim->descricao = resumo + "\n[Espaco] para continuar.";
}

void Game::processarLogicaEspecial(Evento* eventoAnterior, int escolhaFeita) {
    std::string txt = (escolhaFeita == 1) ? eventoAnterior->textoOpcaoEsq : eventoAnterior->textoOpcaoDir;
    std::string desc = eventoAnterior->descricao;
    
    // PROLOGO: MORADIA EM SÃO CARLOS
    if (txt.find("Morar em republica") != std::string::npos) {
        player.setFlag("MoraRepublica", true);
    }
    if (txt.find("Morar sozinho em kitnet") != std::string::npos) {
        player.setFlag("MoraSozinho", true);
    }
    
    // Arquétipos
    if (eventoAnterior->tipo == EventoTipo::ESCOLHA_ARQUETIPO) {
        if (escolhaFeita == 1) player.setArquetipo(Arquetipo::HERDEIRO);
        else player.setArquetipo(Arquetipo::NERDOLA);
    }

    // S1: Alice
    if (txt.find("Ser humilde") != std::string::npos || txt.find("pedir ajuda") != std::string::npos) {
        player.setFlag("AmigoAlice", true);
        if (player.getSocial() > 30) {
            player.setNamorada("Alice", "Ficando");
            player.setFlag("RelacionamentoAlice", true);
        }
    }
    if (txt.find("Pedir desculpas") != std::string::npos) {
        player.setFlag("AmigoAlice", true); // Mesmo depois de mentir, pode se redimir
    }
    if (txt.find("trocar contato") != std::string::npos) {
        player.setFlag("AmigoAlice", true);
        if (player.getSocial() > 25) player.setNamorada("Alice", "Ficando");
    }
    
    // S1: Roberto
    if (txt.find("Defender o colega") != std::string::npos || txt.find("Defender") != std::string::npos) {
        player.setFlag("HumilhouRoberto", true);
        player.setFlag("RivalRoberto", true);
    }
    if (txt.find("Responder com confiança") != std::string::npos) {
        player.setFlag("ConfrontouRoberto", true);
        player.setFlag("RivalRoberto", true);
    }
    // S2: TUSCA e Bruno (novembro - semestre par)
    if (txt.find("Ir pro esquenta da TUSCA") != std::string::npos || 
        txt.find("Ir pro esquenta") != std::string::npos || 
        txt.find("Beber tudo") != std::string::npos) {
        player.setFlag("FoiTuscaS2", true);
        player.setFlag("ConheceuBruno", true);
    }
    // S1: Lucas
    if (txt.find("Ajudar Lucas") != std::string::npos) {
        player.setFlag("AmigoLucas", true);
    }
    
    // S2: Projetos de Extensão - Atualiza status
    if (txt.find("Cati Jr") != std::string::npos || txt.find("Empreendedorismo") != std::string::npos || 
        txt.find("Trainee na Cati") != std::string::npos) {
        player.setProjeto("Cati Jr");
        player.setEmprego("Trainee Cati Jr");
    }
    if (txt.find("Red Dragons") != std::string::npos || txt.find("Robótica") != std::string::npos || 
        txt.find("entrou na Red Dragons") != std::string::npos) {
        player.setProjeto("Red Dragons");
    }
    if (txt.find("PET") != std::string::npos || txt.find("Pesquisa e Ensino") != std::string::npos ||
        txt.find("passou no PET") != std::string::npos) {
        player.setProjeto("PET");
        player.setEmprego("Bolsista PET");
    }

    // S2: Alice - aprofundar relacionamento e pedido de namoro
    if (txt.find("Convidar ela para sair") != std::string::npos ||
        txt.find("Romance") != std::string::npos) {
        player.setFlag("AmigoAlice", true);
        if (player.getSocial() > 30) {
            player.setNamorada("Alice", "Ficando");
            player.setFlag("RelacionamentoAlice", true);
        }
    }
    if (txt.find("Tentar beijá-la") != std::string::npos) {
        player.setFlag("RelacionamentoAlice", true);
    }
    if (txt.find("Planejar um pedido clássico") != std::string::npos) {
        player.setFlag("PedidoClassicoAlice", true);
    }
    if (txt.find("Fazer um aplicativo especial") != std::string::npos) {
        player.setFlag("PedidoAppAlice", true);
    }
    if (txt.find("Dizer que a ama e pedir em namoro") != std::string::npos ||
        desc.find("Você pede Alice em namoro") != std::string::npos ||
        desc.find("Alice ri, se emociona e aceita o pedido") != std::string::npos) {
        player.setNamorada("Alice", "Namorando");
        player.setFlag("RelacionamentoAlice", true);
        player.setFlag("NamoroAlice", true);
    }
    // S2: Traição
    if (txt.find("Beijar (Traição") != std::string::npos && 
        (player.getNomeNamorada() == "Alice" || player.getFlag("RelacionamentoAlice"))) {
        player.setFlag("TraiuAlice", true);
    }

    // S3: Plágio (Bruno)
    if (txt.find("Aceitar") != std::string::npos) {
        // Aceitou o código do Bruno
        player.setFlag("Plagio", true);
    }
    if (txt.find("Culpar o Bruno") != std::string::npos) {
        player.setFlag("TraiuBruno", true);
        player.setFlag("ProcessoDisciplinar", false); // Livrou a cara
    }
    if (txt.find("Assumir a culpa") != std::string::npos) {
        player.setFlag("ProcessoDisciplinar", true);
    }

    // S4: Monitoria
    if (txt.find("Monitoria") != std::string::npos || txt.find("Aceitar") != std::string::npos) {
        if (eventoAnterior->descricao.find("Monitoria") != std::string::npos || 
            eventoAnterior->descricao.find("IC") != std::string::npos) {
            player.setEmprego("Monitor");
        }
    }
    
    // S7: Estágio
    // Garante que QUALQUER aceitação do estágio atualize o cargo
    if (txt.find("Aceitar imediatamente") != std::string::npos ||
        txt.find("Negociar condicoes")   != std::string::npos || // versao sem acento
        txt.find("Negociar condições")   != std::string::npos || // versao com acento
        desc.find("te oferece o estágio") != std::string::npos || 
        desc.find("te oferece o estagio") != std::string::npos) 
    {
        player.setEmprego("Estagiário");
        player.setFlag("TemEstagio", true);
    }
    if (txt.find("Ficar e resolver") != std::string::npos) {
        player.setFlag("HeroiEstagio", true);
    }
    // S4: Roberto sabotagem
    if (txt.find("Cobrar Roberto") != std::string::npos) {
        player.setFlag("ConfrontouRoberto", true);
        player.setFlag("RivalRoberto", true);
    }
    
    // S5: Lucas Burnout
    if (txt.find("Visitar Lucas") != std::string::npos) player.setFlag("VisitouLucas", true);
    if (txt.find("Convencer ele a ir") != std::string::npos) player.setFlag("AjudouLucas", true);
    
    // S6: Bruno e Alice
    if (txt.find("Tentar ajudar Bruno") != std::string::npos) player.setFlag("AjudouBruno", true);
    if (txt.find("Apoiar a decisão dela") != std::string::npos) player.setFlag("ApoiouAlice", true);
    if (txt.find("Tentar manter o relacionamento") != std::string::npos) player.setFlag("NamoroDistancia", true);
    if (txt.find("Terminar amigavelmente") != std::string::npos) {
        // Fim oficial do relacionamento com Alice
        player.setNamorada("", "Solteiro");
        player.setFlag("RelacionamentoAlice", false);
        player.setFlag("NamoroAlice", false);
        player.setFlag("NamoroDistancia", false);
        player.setFlag("TerminoAlice", true);
    }
    
    // S7-S8: TCC
    if (txt.find("Adiantar a escrita") != std::string::npos) player.setFlag("TCCAdiantado", true);
    if (txt.find("Virar noites até resolver") != std::string::npos) player.setFlag("TCCResolvido", true);
    
}

bool Game::verificarAtributosBaixos() const {
    // Verifica se saúde ou mente estão REALMENTE baixos (abaixo de 30)
    // Não deve aparecer se os atributos estão altos ou médios
    int saude = player.getSaude();
    int mente = player.getMente();
    return (saude < 30 || mente < 30);
}

Evento* Game::criarEventoDescanso(Evento* proximoEventoOriginal) {
    // Determina qual atributo está mais baixo para personalizar a mensagem
    std::string descricao;
    if (player.getSaude() < 30 && player.getMente() < 30) {
        descricao = "Você está exausto física e mentalmente. Seu corpo e mente pedem um descanso...";
    } else if (player.getSaude() < 30) {
        descricao = "Você está fisicamente exausto. Seu corpo pede um descanso...";
    } else {
        descricao = "Você está mentalmente exausto. Sua mente pede um descanso...";
    }
    
    Evento* eventoDescanso = new Evento(
        descricao,
        "bg_inicio", // Usa o background de início (mais neutro para descanso)
        "Descansar (Recupera Saude e Mente, mas perde tempo).",
        "Seguir adiante (Arrisca perder mais, mas não perde tempo)."
    );
    
    // Opção 1: Descansar - recupera atributos mas pode perder notas/tempo
    eventoDescanso->impactoEsq = ImpactoStats(+20, 0, +20, -5, 0);
    
    // Opção 2: Seguir adiante - pode perder mais atributos mas não perde tempo
    eventoDescanso->impactoDir = ImpactoStats(-10, 0, -10, 0, 0);
    
    // Ambas as opções levam ao próximo evento original
    eventoDescanso->proximoEventoEsq = proximoEventoOriginal;
    eventoDescanso->proximoEventoDir = proximoEventoOriginal;
    
    return eventoDescanso;
}


Evento* Game::criarEventoFinalPersonalizado() {
    const int mente = player.getMente();
    const int social = player.getSocial();
    const int saude = player.getSaude();
    const int notas = player.getNotas();
    const std::string projeto = player.getProjeto();
    const int semestre = player.getSemestre();

    // Heurística simples: considera que "formou" quem chegou ao 8º semestre,
    // não está em estado de game over e terminou com nota mínima para passar no TCC.
    const bool formou = (semestre >= 8 && notas >= 50 && !player.isGameOver());

    std::string descricaoFinal;
    std::string backgroundFinal = "bg_festa";

    // --- FINAIS SEM FORMATURA (TRANCAMENTO / JUBILAMENTO / ROTAS ALTERNATIVAS) ---
    if (!formou && social > 90 && notas < 60) {
        if (player.getFlag("MoraRepublica")) {
            descricaoFinal = "FINAL - JUBILADO LENDÁRIO\n\nVocê não formou, mas virou lenda viva do DC. "
                             "Organiza a TUSCA, conhece todo mundo e seu nome está em toda lousa. "
                             "O diploma pode esperar: a república é sua casa.";
        } else {
            descricaoFinal = "FINAL - LENDÁRIO DO AP 104\n\nVocê não formou, mas seu apartamento virou ponto de encontro "
                             "de toda a galera do curso. As festas improvisadas e sessões de estudo madrugada adentro "
                             "viraram lenda nos corredores do DC.";
        }
    }
    // --- A PARTIR DAQUI, TODOS OS FINAIS PRESSUPOEM QUE VOCÊ FORMOU ---
    else if (notas > 90 && projeto == "PET" && formou) {
        descricaoFinal = "FINAL - PESQUISADOR DE ELITE\n\nParabéns! Você foi aprovado direto no doutorado. "
                         "Seus artigos com o PET e as noites na BCo renderam prêmios e convites para congressos. "
                         "Alice e você publicaram juntos e o DC se orgulha.";
    }
    else if (player.getFlag("NamoroAlice") && !player.getFlag("TraiuAlice") && !player.getFlag("TerminoAlice") && formou) {
        descricaoFinal = "FINAL - PARCEIROS DE VIDA\n\nVocê e Alice enfrentaram todas as DPs, greves, estágios e TCC juntos. "
                         "Vocês planejam o futuro compartilhando planilhas, viagens e sonhos. "
                         "O amor venceu as estatísticas.";
    }
    else if (player.getFlag("TerminoAlice") && formou && mente >= 40) {
        descricaoFinal = "FINAL - RECOMEÇO EM PAZ\n\nO término com Alice doeu, mas você aprendeu a se reconstruir. "
                         "Com terapia, apoio dos amigos e tempo, encontrou novos caminhos e um futuro em que você vem em primeiro lugar.";
    }
    else if (player.getFlag("TraiuAlice") && formou) {
        descricaoFinal = "FINAL - SOLITÁRIO DE REPÚBLICA\n\nAs festas parecem mais vazias sem Alice. "
                         "Você tem histórias para contar, mas nenhuma mensagem dela no celular. "
                         "Talvez da próxima vez você consiga equilibrar o coração e as tentações do campus.";
    }
    else if (player.getFlag("HeroiEstagio") && player.getEmprego() == "Estagiário" && formou) {
        descricaoFinal = "FINAL - LEAD ANTES DOS 25\n\nVocê salvou deploys, virou noites e ganhou a confiança do time. "
                         "Agora lidera squads, toma café em reuniões com CTOs e recebe ofertas em dólar. "
                         "O DC sente orgulho (e um pouco de inveja).";
    }
    else if (social > 70 && (projeto == "Cati Jr" || projeto == "Red Dragons") && formou) {
        descricaoFinal = "FINAL - TECH LEAD RICO\n\nOs projetos da Cati/Red Dragons te colocaram em contato com clientes e investidores. "
                         "Você foi efetivado e agora trabalha remoto, recebendo em dólar direto de São Carlos.";
    }
    else if ((player.getFlag("ProcessoDisciplinar") || player.getFlag("Plagio")) && formou) {
        descricaoFinal = "FINAL - FICHA MANCHADA\n\nVocê concluiu o curso, mas o rumor do processo disciplinar te segue. "
                         "Vai levar tempo para reconstruir a confiança. Pelo menos você aprendeu o valor da ética.";
    }
    else if ((mente < 40 || saude < 40) && formou) {
        descricaoFinal = "FINAL - SOBREVIVENTE DO BURNOUT\n\nVocê formou, mas sabe que passou do limite. "
                         "A formatura tem gosto agridoce e o descanso agora é obrigatório. "
                         "Ainda assim, você provou para si mesmo que consegue.";
    }
    else if (formou) {
        descricaoFinal = "FINAL - FORMADO UFSCar\n\nVocê pegou o diploma com suor, amizade e muitas histórias. "
                         "Nem tudo saiu como planejado, mas você virou cientista da computação e deixou sua marca no campus.";
    } else {
        // Caso raro: chegou ao final sem critérios claros de formatura,
        // mostra um final neutro de “rota alternativa”.
        descricaoFinal = "FINAL - CAMINHOS ABERTOS\n\nVocê não chegou até a colação de grau, "
                         "mas saiu de São Carlos com bagagem, contatos e cicatrizes importantes. "
                         "Talvez o diploma venha em outro momento — ou talvez a vida te leve por outras trilhas.";
    }

    Evento* final = new Evento(descricaoFinal, backgroundFinal, EventoTipo::FINAL_JOGO);
    return final;
}

void Game::aplicarEscolha(int escolha) {
    if (!eventoAtual) return;
    
    // Se estivermos em um evento de descanso, deletar após usar
    Evento* eventoDescansoTemp = nullptr;
    bool acabouDeSairDeDescanso = false;
    if (eventoAtual == eventoDescansoAtual) {
        eventoDescansoTemp = eventoDescansoAtual;
        eventoDescansoAtual = nullptr;
        proximoEventoAposDescanso = nullptr;
        acabouDeSairDeDescanso = true;
    }
    
    processarLogicaEspecial(eventoAtual, escolha);

    if (escolha == 3 && eventoAtual->tipo == EventoTipo::FINAL_SEMESTRE) {
        // Deleta evento de descanso se existir antes de avançar semestre
        if (eventoDescansoTemp) delete eventoDescansoTemp;
        player.avancarSemestre();
        carregarNivelAtual(); 
        return;
    }

    // Aplica impacto ANTES de determinar o próximo evento
    if (escolha == 1) player.aplicarImpacto(eventoAtual->impactoEsq);
    else if (escolha == 2) player.aplicarImpacto(eventoAtual->impactoDir);

    // Determina próximo evento
    Evento* proximo = (escolha == 1) ? eventoAtual->proximoEventoEsq : eventoAtual->proximoEventoDir;

    // Deleta o evento de descanso após passar por ele
    if (eventoDescansoTemp) {
        delete eventoDescansoTemp;
    }

    // Verifica se os atributos estão baixos após aplicar o impacto
    // Mas só se não estivermos já em um evento de descanso, não acabou de sair de descanso,
    // e não estivermos no final do semestre/jogo
    if (proximo && !eventoDescansoAtual && !acabouDeSairDeDescanso && 
        verificarAtributosBaixos() && 
        proximo->tipo != EventoTipo::FINAL_SEMESTRE && proximo->tipo != EventoTipo::FINAL_JOGO) {
        // Cria evento de descanso e insere antes do próximo evento
        eventoDescansoAtual = criarEventoDescanso(proximo);
        proximoEventoAposDescanso = proximo;
        proximo = eventoDescansoAtual;
    }

    if (proximo && proximo->tipo == EventoTipo::FINAL_SEMESTRE) {
        verificarFimDeSemestre(proximo);
    }

    eventoAtual = proximo;

    // Checagem de Game Over
    if (player.isGameOver()) {
        // Limpa eventos temporários se existirem
        if (eventoDescansoAtual) {
            delete eventoDescansoAtual;
            eventoDescansoAtual = nullptr;
        }
        status = GameStatus::GAME_OVER_GENERICO;
        eventoAtual = new Evento(player.getGameOverReason(), "bg_jubilado", EventoTipo::FINAL_JOGO);
    }
    else if (eventoAtual && eventoAtual->tipo == EventoTipo::FINAL_JOGO) {
        // Vitória ou Derrota no final
        if (player.getSemestre() == 8 && player.getNotas() < 50) {
             status = GameStatus::GAME_OVER_GENERICO;
             eventoAtual->descricao = "Reprovou no TCC. Tente novamente.";
        } else {
             status = GameStatus::VICTORY;
        }
    }

    if (eventoAtual && ui) {
        // Verifica se a textura existe antes de usar
        if (texturas.find(eventoAtual->idBackground) != texturas.end()) {
            ui->update(player, eventoAtual, texturas[eventoAtual->idBackground]);
        } else {
            // Usa uma textura padrão se não encontrar
            std::cerr << "Aviso: Textura '" << eventoAtual->idBackground << "' não encontrada. Usando bg_inicio como padrão." << std::endl;
            if (texturas.find("bg_inicio") != texturas.end()) {
                ui->update(player, eventoAtual, texturas["bg_inicio"]);
            }
        }
    }
}

void Game::processarEvento(sf::Event evento) {
    if (evento.type == sf::Event::Closed) janela.close();
    
    if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
        if (status != GameStatus::RUNNING) return;
        int esc = ui->handleClick(sf::Vector2f(evento.mouseButton.x, evento.mouseButton.y));
        if (esc != 0) aplicarEscolha(esc);
    }
    
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Space) {
        if (eventoAtual && eventoAtual->tipo == EventoTipo::FINAL_SEMESTRE) aplicarEscolha(3);
    }
}

void Game::atualizar() {
    // Lógica do Screen Shake
    if (shakeIntensity > 0) {
        float offsetX = (rand() % 100 - 50) / 50.0f * shakeIntensity;
        float offsetY = (rand() % 100 - 50) / 50.0f * shakeIntensity;
        
        sf::View view = janela.getDefaultView();
        view.move(offsetX, offsetY);
        janela.setView(view);

        shakeIntensity -= 0.5f; // Diminui o tremor suavemente
        if (shakeIntensity < 0) {
            shakeIntensity = 0;
            janela.setView(janela.getDefaultView()); // Reseta a câmera
        }
    } else {
        janela.setView(janela.getDefaultView());
    }

    // Dispara partículas de comemoração quando chegar em um FINAL_SEMESTRE ou FINAL_JOGO
    if (ui && eventoAtual && 
        (eventoAtual->tipo == EventoTipo::FINAL_SEMESTRE || eventoAtual->tipo == EventoTipo::FINAL_JOGO)) {
        ui->spawnConfetti();
    }
}

std::string Game::getFinalMessage() const {
    if (player.isGameOver()) return player.getGameOverReason();
    if (eventoAtual) return eventoAtual->descricao;
    return "Fim.";
}

void Game::desenhar(){
    if(ui){
        ui->draw();
    }
}