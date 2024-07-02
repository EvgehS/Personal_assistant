from Config.config import names
from Sounds.sound_functions import listen, say
import assistant_functions.assistant_functions as af
import logging

logger = logging.getLogger(__name__)

# Список команд
commands = {'открой ютуб': af.open_youtube,
            'открой дис': af.open_discord,
            'открой телеграмм': af.open_tg,
            'стоп': af.terminate_program,
            'прими игру': af.game_accept,
            'включи музыку': af.open_vk}

logger.info('Ассистент запущен')


# Бесконечный цикл, ожидающий команд
while True:
    text = listen()
    if text:
        logger.info(text)
    if any(name in text for name in names):
        for command, function in commands.items():
            if command in text:
                say('Sounds/Выполняю.mp3')
                try:
                    function()
                except Exception as e:
                    logger.error(f'Произошла ошибка - {e} '
                                 'при выполнении функции {function}')
