#include "../../Assistant.h"
#include <iostream>
#include <unordered_map>

bool Assistant::get_app_status(const std::string &app_name)
{
    std::string command = "pgrep -f " + window_class_map[app_name][0];
    FILE *fp = popen(command.c_str(), "r");
    char buffer[128];
    if (fgets(buffer, sizeof(buffer), fp) != nullptr)
    {
        pclose(fp);
        return true;
    }
    pclose(fp);
    return false;
}

void Assistant::open_app(const std::string &app_name)
{
    if (get_app_status(app_name))
    {
        speak(app_name + " запущен");
        std::string command = "nohup hyprctl dispatch focuswindow class:" + window_class_map[app_name][1] + " > /dev/null 2>&1 &";
        system(command.c_str());
        return;
    }
    speak("Запускаю " + app_name);
    std::string command = "nohup " + window_class_map[app_name][0] + " > /dev/null 2>&1 &";
    system(command.c_str());
}

void Assistant::close_app(const std::string &app_name)
{
    if (!get_app_status(app_name))
    {
        speak(app_name + " не запущен");
        return;
    }
    speak("Закрываю " + app_name);
    std::string command = "pkill -f " + window_class_map[app_name][0];
    system(command.c_str());
}

int Assistant::get_workspace_number(const std::string &command)
{
    const std::unordered_map<std::string, int> word_to_number = {
        {"первый", 1}, {"второй", 2}, {"третий", 3}, {"четвёртый", 4}, {"четвертый", 4}, {"пятый", 5}, {"шестой", 6}, {"седьмой", 7}, {"восьмой", 8}, {"девятый", 9}, {"десятый", 10}};
    const std::unordered_map<std::string, int> number_to_word = {
        {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10}};
    
    std::string command_lower = command;

    for (std::pair<std::string, int> item : word_to_number)
    {
        if (command.find(item.first) != std::string::npos)
        {
            return item.second;
        }
    }

    for (std::pair<std::string, int> item : number_to_word)
    {
        if (command.find(item.first) != std::string::npos)
        {
            return item.second;
        }
    }
    

    return 0;
}

void Assistant::move_window(const std::string &command)
{
    int workspace_number = get_workspace_number(command);
    if (workspace_number == 0)
    {
        std::cout << "Неверный номер" << std::endl;
        return;
    }

    std::string command_str = "nohup hyprctl dispatch movetoworkspacesilent " + std::to_string(workspace_number) + " > /dev/null 2>&1 &";
    system(command_str.c_str());
    speak("Окно перемещено");
}

void Assistant::change_workspace(const std::string &command)
{
    int workspace_number = get_workspace_number(command);
    if (workspace_number == 0)
    {
        speak("Неверный номер рабочего стола");
        return;
    }

    std::string command_str = "nohup hyprctl dispatch workspace " + std::to_string(workspace_number) + " > /dev/null 2>&1 &";
    system(command_str.c_str());
    speak("Переключаюсь на рабочий стол " + std::to_string(workspace_number));
}