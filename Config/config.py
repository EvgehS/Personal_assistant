import logging


# Инициализация и настройка логгера
logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG,
                    format='[{asctime}] #{levelname:8} {filename}:'
                    '{lineno} - {name} - {message}',
                    style='{')
# Имена ассистента
names = ['ассистент']

# Личные ссылки до файлов
paths = {
    'discord': "C:\\Users\\sidze\\AppData"
    "\\Local\\Discord\\app-1.0.9151\\Discord.exe",
    'chrome': "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe",
    'telegram': "C:\\Users\\sidze\\AppData"
    "\\Roaming\\Telegram Desktop\\Telegram.exe"
}
