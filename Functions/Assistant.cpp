#include "../Assistant.h"
#include <iostream>
#include <fstream>

std::string Assistant::read_from_config(const std::string &variable)
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

Assistant::Assistant()
{
    name = read_from_config("name");
    default_model = read_from_config("default_model");
    mode = read_from_config("assistant_default_mode");
    last_phrase = "";
}

void Assistant::start()
{
    is_running = true;
    while (is_running)
    {
        std::string command = listen();
        if(mode == "текст")
            do_command(command);
        else if(mode == "голос")
        {
            std::cout << "Команда: " << command << std::endl;
            if(command.find(name) != std::string::npos)
                do_command(command);
        }
    }
}

void Assistant::stop()
{
    is_running = false;
    speak("До свидания!");
}

void Assistant::do_command(std::string &command)
{
    bool command_found = false;
    for (std::pair<std::vector<std::string>, std::function<void()>> command_pair : command_list)
    {
        for (std::string command_str : command_pair.first)
        {
            if (command.find(command_str) != std::string::npos)
            {
                command_found = true;
                command_pair.second();
                break;
            }
        }
    }
    if (!command_found)
    {
        speak("Я не знаю такой команды");
    }
}

void Assistant::change_mode()
{
    if (mode == "текст")
    {
        mode = "голос";
        speak("Режим изменен на голосовой");
    }
    else
    {
        mode = "текст";
        speak("Режим изменен на текстовый");
    }
}

void Assistant::repeat()
{
    if(last_phrase != "")
        speak(last_phrase);
    else
        speak("Я ещё ничего не говорил");
}

std::string Assistant::clean_for_shell(const std::string &input)
{
    std::string output;
    for (char c : input) {
        switch (c) {
            case '*':
            case '`':
            case '"':
            case '\'':
            case '$':
            case '&':
            case '|':
            case '<':
            case '>':
            case '\\':
            case '(':
            case ')':
            case ';':
            case '!':
                break;
            case '\n':
                output += ' ';
                break;
            default:
                output += c;
        }
    }
    return output;
}

std::string Assistant::battery_level()
{
    std::ifstream battery_file("/sys/class/power_supply/BATT/capacity");
    std::string battery_level;
    std::getline(battery_file, battery_level);
    battery_file.close();
    return "Уровень заряда батареи: " + battery_level + "%";
}