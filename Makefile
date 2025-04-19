Jarvis: Jarvis.cpp
	@echo "Компиляция Jarvis..."
	g++ -std=c++20 \
		-I/home/evgen/boost-3.10/include \
		-I/home/evgen/programs/Personal_assistant/venv/include \
		-L/home/evgen/boost-3.10/lib \
		-L/home/evgen/programs/Personal_assistant/venv/lib/python3.10/site-packages \
		-Wl,-rpath,/home/evgen/boost-3.10/lib \
		-Wl,-rpath,/home/evgen/programs/Personal_assistant/venv/lib/python3.10/site-packages \
		-lboost_python310 -lpython3.10 \
		Jarvis.cpp -o Jarvis

assist: Jarvis
	LD_LIBRARY_PATH=$(HOME)/boost-3.10/lib:$(HOME)/programs/Personal_assistant/venv/lib/python3.10/site-packages  ./Jarvis