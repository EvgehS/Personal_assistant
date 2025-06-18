#include <string>
#include <map>
#include <vector>
#include <functional>
#include <array>

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
    std::string default_model;
    std::string last_phrase;
    std::string last_command = "";
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
                 speak("Я могу выполнять различные команды и отвечать на вопросы");
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
            {{"время", "сколько времени"}, [this]()
             { speak(get_time()); }},
            {{"запусти телеграм", "открой тг", "открой телегу", "запусти телегу", "открой телеграм", "запусти телеграм"}, [this]()
             {
                 open_app("телеграм");
             }},
            {{"закрой телеграм", "закрой тг", "закрой телегу"}, [this]()
             {
                 close_app("телеграм");
             }},
            {{"запусти браузер", "открой браузер"}, [this]()
             {
                 open_app("браузер");
             }},
            {{"закрой браузер"}, [this]()
             {
                 close_app("браузер");
             }},
            {{"запусти терминал", "открой терминал"}, [this]()
             {
                 system("nohup kitty > /dev/null 2>&1 &");
                 speak("Терминал запущен");
             }},
            {{"закрой терминал"}, [this]()
             {
                 close_app("терминал");
             }},
            {{"запусти калькулятор", "открой калькулятор"}, [this]()
             {
                 open_app("калькулятор");
             }},
            {{"закрой калькулятор"}, [this]()
             {
                 close_app("калькулятор");
             }},
            {{"запусти редактор", "открой редактор", "запусти код", "открой код"}, [this]()
             {
                 open_app("код");
             }},
            {{"закрой редактор", "закрой код"}, [this]()
             {
                 close_app("код");
             }},
             {{"включи впн", "запусти впн"}, [this]()
             {
                 speak("Запускаю ВПН");
                 system("nohup ~/scripts/VPN.sh > /dev/null 2>&1 &");
             }},
            {{"прибавь громкость", "увеличь громкость"}, [this]()
             {
                 system("nohup wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+ > /dev/null 2>&1 &");
                 speak("Громкость увеличена");
             }},
            {{"убавь громкость", "уменьши громкость"}, [this]()
             {
                 system("nohup wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%- > /dev/null 2>&1 &");
                 speak("Громкость уменьшена");
             }},
            {{"выключи звук", "отключи звук"}, [this]()
             {
                 system("nohup wpctl set-mute @DEFAULT_AUDIO_SINK@ 1 > /dev/null 2>&1 &");
                 speak("Звук отключен");
             }},
            {{"включи звук", "активируй звук"}, [this]()
             {
                 system("nohup wpctl set-mute @DEFAULT_AUDIO_SINK@ 0 > /dev/null 2>&1 &");
                 speak("Звук включен");
             }},
            {{"увеличь яркость", "прибавь яркость"}, [this]()
             {
                 system("nohup brightnessctl -e4 -n2 set 5%+ > /dev/null 2>&1 &");
                 speak("Яркость увеличена");
             }},
            {{"уменьши яркость", "убавь яркость"}, [this]()
             {
                 system("nohup brightnessctl -e4 -n2 set 5%- > /dev/null 2>&1 &");
                 speak("Яркость уменьшена");
             }},
            {{"закрой окно", "закрой текущее окно", "закрой активное окно"}, [this]()
             {
                 system("nohup hyprctl dispatch killactive > /dev/null 2>&1 &");
                 speak("Окно закрыто");
             }},
            {{"перезагрузи компьютер", "перезагрузка компьютера"}, [this]()
             {
                 speak("Перезагружаю компьютер");
                 system("reboot");
             }},
            {{"выключи компьютер", "выключение компьютера"}, [this]()
             {
                 speak("Выключаю компьютер");
                 system("poweroff");
             }},
             {{"передвинь окно на ", "перемести окно на "}, [this]()
             {
                 move_window(last_command);
             }},
             {{"перейти на ", "открой рабочий стол "}, [this]()
            {
                change_workspace(last_command);
            }},
            {{"сделай ещё раз", "выполни ещё раз"}, [this]()
             {
                 if (last_command != "")
                 {
                     do_command(last_command);
                 }
                 else
                 {
                     speak("Я ещё ничего не делал");
                 }
             }},
            {{"до свидания", "выключись"}, [this]()
             {
                 stop();
             }}};

    // Functions/Assistant.cpp
    std::string read_from_config(const std::string &variable);
    void stop();
    void do_command(std::string &command);
    void change_mode();
    void repeat();
    std::string battery_level();
    std::string get_time();

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

    // Fucntions/Apps/apps.cpp
    void open_app(const std::string &app_name);
    void close_app(const std::string &app_name);
    bool get_app_status(const std::string &app_name);
    std::map<std::string, std::array<std::string, 2>> window_class_map = {
        {"телеграм", {"Telegram", "org.telegram.desktop"}},
        {"браузер", {"firefox", "firefox"}},
        {"код", {"code", "Code"}},
        {"терминал", {"kitty", "kitty"}},
        {"калькулятор", {"qalculate-qt", "io.github.Qalculate.qalculate-qt"}}};
    
    void move_window(const std::string &command);
    int get_workspace_number(const std::string &command);
    void change_workspace(const std::string &command);
};
