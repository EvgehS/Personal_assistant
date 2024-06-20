from sound_functions import listen, say
import jarvis_functions as jf


# Список команд
commands = {'открой ютуб': jf.open_youtube,
            'открой диск': jf.open_discord,
            'открой телеграмм': jf.open_tg,
            'стоп': jf.terminate_program}

names = ['володя', 'вован', 'вовчик', 'вова']

# Бесконечный цикл, ожидающий команд
while True:
    text = listen()
    print(text)
    if any(name in text for name in names):
        for command, function in commands.items():
            if command in text:
                say('Выполняю')
                function()
