from sound_functions import listen, say
from Jarvis_functions import open_discord, open_tg, open_youtube


# Список команд
commands = {'открой ютуб': open_youtube,
            'открой диск': open_discord,
            'открой телеграмм': open_tg}


# Бесконечный цикл, ожидающий команд
while True:
    text = listen()
    print(text)
    if 'джарвис' in text:
        if 'стоп' in text:
            say('До свидания')
            break
        for command, function in commands.items():
            if command in text:
                say('Выполняю')
                function()
