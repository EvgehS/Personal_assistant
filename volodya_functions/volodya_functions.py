import os
from sound_functions import say
import sys
import keyboard
import psutil
import subprocess

# Функции джарвиса


def open_discord(backgropn):
    os.startfile(
        r'C:\Users\sidze\AppData\Local\Discord\app-1.0.9149\Discord.exe')
    say('Диск запущен')


def open_youtube(backgropn):
    chrome_path = "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe"
    # Открываем приложение в фоновом режиме
    subprocess.Popen([chrome_path, 'https://www.youtube.com/'],
                     stdout=[None, subprocess.DEVNULL][backgropn])
    say('Youtube открыт')


def open_tg(backgropn):
    if not (backgropn):
        os.startfile(
            r'C:\Users\sidze\AppData\Roaming\Telegram Desktop\Telegram.exe')


def terminate_program(backgropn):
    say('До свидания')
    sys.exit()


def game_accept(backgropn):
    keyboard.press_and_release('enter')
    say('Приятной игры!')


def is_dota2_running():
    # Проверяем все запущенные процессы
    for process in psutil.process_iter(['pid', 'name']):
        if process.info['name'] and "dota2" in process.info['name'].lower():
            return True
    return False
