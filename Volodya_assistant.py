from sound_functions import listen, say
import volodya_functions as vf


# Список команд
commands = {'открой ютуб': vf.open_youtube,
            'открой диск': vf.open_discord,
            'открой телеграмм': vf.open_tg,
            'стоп': vf.terminate_program,
            'прими игру': vf.game_accept}

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

