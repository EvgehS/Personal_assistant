Jarvis: Jarvis.cpp
	@echo "Компиляция Jarvis..."
	g++ -std=c++20 \
		-I/home/evgen/programs/Personal_assistant/venv/include/python3.13 \
		-L/home/evgen/programs/Personal_assistant/venv/lib/python3.13/site-packages \
		-Wl,-rpath,/home/evgen/programs/Personal_assistant/venv/lib/python3.13/site-packages \
		-lboost_python3 -lpython3.13 \
		Jarvis.cpp -o Jarvis

assist: Jarvis
	@echo "Запуск Jarvis..."
	LD_LIBRARY_PATH=$(HOME)/programs/Personal_assistant/venv/lib/python3.13/site-packages  ./Jarvis

# TODO: через config.txt и вариативный python