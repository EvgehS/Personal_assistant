#include <iostream>
#include <fstream>
#include <map>

class Assistant {
public:
    Assistant();

private:
    std::string name;
    std::string mode;

    std::string read_from_config(const std::string& variable);

    // Functions/Sounds/sound_functions.cpp
    std::string listen();
    void speak(std::string&& text);

};



