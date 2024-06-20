from sound_functions import listen, say
from jarvis_functions import open_discord, open_tg, open_youtube


# Список команд
commands = {'открой ютуб': open_youtube,
            'открой дис': open_discord,
            'открой телеграмм': open_tg}

names = ['володя', 'вован', 'вовчик', 'вова']

# Бесконечный цикл, ожидающий команд
while True:
    text = listen()
    print(text)
    if any(name in text for name in names):
        if 'стоп' in text:
            say('До свидания')
            break
        for command, function in commands.items():
            if command in text:
                say('Выполняю')
                function()
