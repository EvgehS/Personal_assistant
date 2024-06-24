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


def open_discord():
    subprocess.Popen([paths['discord']],
                     stdout=[None, subprocess.DEVNULL][is_dota2_running()])
    say('Дис запущен')


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
