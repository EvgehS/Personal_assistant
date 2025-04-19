#include <iostream>
#include "Sounds/sound_functions.hpp"

int main() {
    std::string command;
    while (true)
    {
        command = listen();
        if (command == "error") {
            std::cerr << "Ошибка распознавания" << std::endl;
            continue;
        }
        
        std::cout << "Распознанная команда: " << command << std::endl;
        if (command == "стоп") {
            std::cout << "Выход из программы." << std::endl;
            break;
        }
    }
    Py_Finalize();
    return 0;
}