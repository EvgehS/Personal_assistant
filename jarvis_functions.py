import os
import webbrowser
from sound_functions import say

# Функции джарвиса


def open_discord():
    os.startfile(
        r'C:\Users\sidze\AppData\Local\Discord\app-1.0.9149\Discord.exe')
    say('Диск запущен')


def open_youtube():
    webbrowser.open_new('https://www.youtube.com/')
    say('Youtube открыт')


def open_tg():
    os.startfile(
        r'C:\Users\sidze\AppData\Roaming\Telegram Desktop\Telegram.exe')
    say('Телеграм запущен')
