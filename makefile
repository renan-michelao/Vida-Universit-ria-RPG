# Makefile para UFSCar: Vida Universitária

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

TARGET = ufscar_rpg

# CORRIGIDO: Game.cpp com 'G' maiúsculo
SOURCES = main.cpp Game.cpp GameTree.cpp 

OBJECTS = $(SOURCES:.cpp=.o)

# Ajuste conforme sua instalação
SFML_INCLUDE = 
SFML_LIB = 

all: $(TARGET)
	@echo "🎮 Iniciando UFSCar: Vida Universitária..."
	./$(TARGET)

$(TARGET): $(OBJECTS)
	@echo "🔗 Linkando objetos..."
	$(CXX) $(OBJECTS) -o $(TARGET) $(SFML_LIB) $(SFML_FLAGS)
	@echo "✅ Executável $(TARGET) criado!"

%.o: %.cpp
	@echo "📝 Compilando $<..."
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -c $< -o $@

main.o: main.cpp Game.h
# CORRIGIDO: Game.cpp com 'G' maiúsculo
game.o: Game.cpp Game.h Player.h Evento.h UIManager.h

clean:
	@echo "🧹 Limpando arquivos..."
	rm -f $(OBJECTS) $(TARGET)

reinstall: clean all

.PHONY: all clean reinstall