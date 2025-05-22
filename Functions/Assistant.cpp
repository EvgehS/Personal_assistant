#include "../Assistant.h"

Assistant:: Assistant()
    : mode("звук") {name = read_from_config("name");};

std::string Assistant::read_from_config(const std::string& variable)
{
    std::ifstream config_file(".config.txt");
    if (config_file.is_open())
    {
        std::string line;
        while (std::getline(config_file, line))
        {
            if (line.find(variable) != std::string::npos)
            {
                return line.substr(line.find('=') + 2);
            }
        }
        return "";
        config_file.close();
    }
    else
    {
        std::cerr << "Не удалось открыть файл конфигурации." << std::endl;
        return "";
    }
    return "";
}