from Config.config import names
from sound_functions import listen, say
import volodya_functions.volodya_functions as vf
import logging

logger = logging.getLogger(__name__)

# Список команд
commands = {'открой ютуб': vf.open_youtube,
            'открой диск': vf.open_discord,
            'открой телеграмм': vf.open_tg,
            'стоп': vf.terminate_program,
            'прими игру': vf.game_accept}

logger.info('Ассистент запущен')


# Бесконечный цикл, ожидающий команд
while True:
    text = listen()
    if text:
        logger.info(text)
    if any(name in text for name in names):
        for command, function in commands.items():
            if command in text:
                say('Выполняю')
                try:
                    function()
                except Exception as e:
                    logger.error(f'Произошла ошибка - {e} '
                                 'при выполнении функции {function}')
