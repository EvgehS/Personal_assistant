from Config.config import paths
from sound_functions import say
import sys
import keyboard
import psutil
import subprocess

# Функция проверяет, запущена ли дота


def is_dota2_running():
    # Проверяем все запущенные процессы
    for process in psutil.process_iter(['pid', 'name']):
        if process.info['name'] and "dota2" in process.info['name'].lower():
            return 1
    return 0

# Функции ассистента

# TODO: добавь is_dota2_running в функции, создай папку
# Config(обязательно с большой), в ней создай config.py.
# перепиши функции через Popen(пример - функция open_youtube)
# В этот файл внеси массив names и создай словарь paths(пример я тебе отправлю)
# и пропиши там свои пути
# добавь config.py в .gitignore


def open_discord():
    subprocess.Popen(paths['discord'])
    say('Диск запущен')


def open_youtube():
    subprocess.Popen([paths['chrome'], 'https://www.youtube.com/'],
                     stdout=[None, subprocess.DEVNULL][is_dota2_running()])
    say('Youtube открыт')


def open_tg():
    subprocess.Popen([paths['telegram']],
                     stdout=[None, subprocess.DEVNULL][is_dota2_running()])
    say('Telegram открыт')


def terminate_program():
    say('До свидания')
    sys.exit()


def game_accept():
    keyboard.press_and_release('enter')
    say('Приятной игры!')
