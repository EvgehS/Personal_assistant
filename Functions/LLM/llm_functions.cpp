#include <thread>
#include <chrono>
#include "cstring"
#include "../../Assistant.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
using json = nlohmann::json;

bool Assistant::is_lm_studio_running()
{
    FILE *fp = popen("pgrep -f lmstudio", "r");

    char buffer[128];
    if (fgets(buffer, sizeof(buffer), fp) != nullptr)
    {
        pclose(fp);
        return true;
    }

    pclose(fp);
    return false;
}

void Assistant::start_lm_studio()
{
    if (!is_lm_studio_running())
    {
        system("nohup lmstudio > /dev/null 2>&1 &");
        speak("Запускаю LM-Studio");
        std::this_thread::sleep_for(std::chrono::seconds(5));
        system("hyprctl dispatch movetoworkspacesilent 9");
    }
}

bool Assistant::is_server_running()
{
    FILE *fp = popen("lms server status 2>&1", "r");

    char buffer[100];
    while (fgets(buffer, 100, fp) != nullptr)
    {
        if (strstr(buffer, "The server is not running.") != nullptr)
        {
            pclose(fp);
            return true;
        }
    }

    pclose(fp);
    return false;
}

bool Assistant::is_model_loaded(const std::string &model_name)
{
    char buffer[128];
    std::string command = "lms ps 2>&1 | grep " + model_name;
    FILE *fp = popen(command.c_str(), "r");

    if (fgets(buffer, sizeof(buffer), fp) != nullptr)
    {
        pclose(fp);
        return true;
    }

    pclose(fp);
    return false;
}

void Assistant::start_server_and_load_model(const std::string &model_name)
{
    start_lm_studio();

    if (is_server_running())
    {
        speak("Запускаю сервер");
        system("lms server start");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (!is_model_loaded(model_name))
    {
        speak("Загружаю модель " + model_name);
        std::string command = "lms load " + model_name;
        std::cout << command << std::endl;
        system(command.c_str());
        speak("Модель " + model_name + " загружена");
    }
}

void Assistant::start_dialog()
{
    start_server_and_load_model(default_model);
    speak("Принял, переключаюсь в режим диалога. Для окончания дайте команду '" + this->name + " стоп' или '" + this->name + " хватит'");
    speak("Так о чем вы хотите поговорить?");
    std::string question;
    std::string answer;
    std::vector<std::pair<std::string, std::string>> history;
    while (is_running)
    {
        if (mode == "текст")
        {
            std::cout << "  -";
            std::getline(std::cin, question);
            std::cout << "  -";
        }
        else
        {
            question = listen();
        }
        if (question.find(this->name + " стоп") != std::string::npos || question.find(this->name + " хватит") != std::string::npos)
        {
            speak("Хорошо, заканчиваю диалог");
            break;
        }
        else if(question.find(this->name + " повтори") != std::string::npos || question.find(this->name + " не услышал") != std::string::npos || question.find(this->name + " скажи ещё раз") != std::string::npos)
        {
            repeat();
            continue;
        }
        else
        {
            answer = get_answer(question, default_model, history);
            history.push_back({"user", question});
            history.push_back({"assistant", answer}); 
            speak(answer);
        }
        
    }
}

void Assistant::ask_question()
{
    start_server_and_load_model(default_model);
    std::string question;
    if (mode == "текст")
    {
        std::cout << "Введите вопрос: ";
        std::getline(std::cin, question);
        std::cout << "Ответ: ";
    }
    else
    {
        speak("Скажите ваш вопрос");
        question = listen();
    }
    speak(get_answer(question, default_model, {}));
}

std::string Assistant::get_answer(const std::string &question, const std::string &model_name, std::vector<std::pair<std::string, std::string>> history)
{
    std::string command = "curl -s -X POST http://127.0.0.1:1234/api/v0/chat/completions -H \"Content-Type: application/json\" -d '{ \"model\": \"" + model_name + "\", \"messages\": [{\"role\": \"system\",\"content\": \"Ты краткий, точный и дружелюбный помощник. Отвечай сжато, слов 15-20 и ТОЛЬКО НА РУССКОМ\"}";
    for(std::pair<std::string, std::string> &item : history)
    {
        command += ",{\"role\": \"" + item.first + "\", \"content\": \"" + item.second + "\"}";
    }
    command += ", {\"role\":\"user\", \"content\":\"" + question + ".Ответь кратко и только на русском\"}]}\'";
    std::string result = "";
    char buffer[4096];
    FILE *fp = popen(command.c_str(), "r");
    while (fgets(buffer, sizeof(buffer), fp) != nullptr)
    {
        result += buffer;
    }
    pclose(fp);
    auto answer = json::parse(result);
    result = answer["choices"][0]["message"]["content"];
    return clean_for_shell(result);
}
