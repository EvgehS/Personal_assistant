#include <map>
#include <string>
#include <vector>
#include <functional>

class Assistant
{
public:
    // Functions/Assistant.cpp
    Assistant();
    void start();

private:
    // variables
    std::string name;
    std::string mode;
    std::string default_model; //TODO: заменить стандартную модель
    std::string last_phrase;
    bool is_running = false;

    std::vector<std::pair<std::vector<std::string>, std::function<void()>>> command_list =
        {
            {{"привет", "здравствуй", "здарова", "приветствую"}, [this]()
             {
                 speak("Здравствуй, меня зовут " + name + ", чем могу помочь?");
             }},
            {{"как дела", "как ты", "как жизнь"}, [this]()
             {
                 speak("У меня все хорошо, спасибо!");
             }},
            {{"что ты умеешь", "что ты можешь", "расскажи о себе"}, [this]()
             {
                 speak("Я могу выполнять различные команды и отвечать на вопросы.");
             }},
            {{"спасибо", "благодарю"}, [this]()
             {
                 speak("Пожалуйста!");
             }},
            {{"начать диалог", "давай поговорим", "начать разговор"}, [this]()
             {
                 start_dialog();
             }},
            {{"переключить режим", "сменить режим", "изменить режим"}, [this]()
             {
                 change_mode();
             }},
            {{"задать вопрос", "спросить", "узнать"}, [this]()
             { 
                ask_question(); 
            }},
            {{"повтори", "не услышал", "скажи ещё раз"}, [this]()
             {
                 repeat();
             }},
            {{"скажи заряд", "сколько процентов", "заряд батареи"}, [this]()
             {
                speak(battery_level());
            }},
            {{"пока", "до свидания", "выключись"}, [this]()
             {
                 stop();
             }}}; //TODO: время, погода

    // Functions/Assistant.cpp
    std::string read_from_config(const std::string &variable);
    void stop();
    void do_command(std::string &command);
    void change_mode();
    void repeat();
    std::string battery_level();

    // Functions/Sounds/sound_functions.cpp
    std::string listen();
    void speak(const std::string &text);

    // Functions/LLM/llm_functions.cpp
    void start_dialog();
    void ask_question();

    bool is_lm_studio_running();
    bool is_server_running();
    bool is_model_loaded(const std::string &model_name);
    void start_server_and_load_model(const std::string &model_name);
    void start_lm_studio();
    std::string get_answer(const std::string &question, const std::string &model_name, std::vector<std::pair<std::string, std::string>> history);
    std::string clean_for_shell(const std::string &input);
};
