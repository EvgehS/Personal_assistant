CONFIG := .config.txt
LIBS := $(shell awk -F " = " '/^compile_libs/ {print $$2}' $(CONFIG))
CC := g++
FLAGS := -Wall -Wextra -std=c++11

Jarvis: Jarvis.cpp Functions/Assistant.o Functions/Sounds/sound_functions.o Functions/LLM/llm_functions.o Assistant.h
	@echo "Компиляция Jarvis..."
	$(CC) $(FLAGS) Jarvis.cpp Functions/Sounds/sound_functions.o Functions/Assistant.o Functions/LLM/llm_functions.o $(LIBS) -o Jarvis

Functions/Assistant.o: Functions/Assistant.cpp Assistant.h
	@echo "Компиляция базовых функций"
	$(CC) $(FLAGS) -c Functions/Assistant.cpp -o Functions/Assistant.o

Functions/Sounds/sound_functions.o: Functions/Sounds/sound_functions.cpp .config.txt
	@echo "Компиляция звуковых функций"
	$(CC) $(FLAGS) $(LIBS) -c Functions/Sounds/sound_functions.cpp -o Functions/Sounds/sound_functions.o

Functions/LLM/llm_functions.o: Functions/LLM/llm_functions.cpp
	@echo "Компиляция функций для работы с нейросетями"
	$(CC) $(FLAGS) -c Functions/LLM/llm_functions.cpp -o Functions/LLM/llm_functions.o
test: Jarvis
	@echo "Запуск Jarvis..."
	./Jarvis

clean:
	rm -f Jarvis Functions/*.o Functions/Sounds/*.o Functions/LLM/*.o
