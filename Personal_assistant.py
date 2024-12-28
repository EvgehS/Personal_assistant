from Sounds.sound_functions import listen, say
import logging

logger = logging.getLogger(__name__)

logging.basicConfig(level=logging.INFO)

logger.info('Ассистент запущен')

say("Sounds/Выполняю.mp3")
# Бесконечный цикл, ожидающий команд
while True:
    text = listen()
    if text:
        logger.info(text)
