from Config.config import paths
from Sounds.sound_functions import say
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
    subprocess.Popen(['cmd', '/c', 'start', paths['discord']],
                     stdout=[None, subprocess.DEVNULL][is_dota2_running()])
    say('Sounds/Диск_запущен.mp3')


def open_youtube():
    subprocess.Popen([paths['chrome'], 'https://www.youtube.com/'],
                     stdout=[None, subprocess.DEVNULL][is_dota2_running()])
    say('Sounds/Youtube_открыт.mp3')


def open_tg():
    subprocess.Popen([paths['telegram']],
                     stdout=[None, subprocess.DEVNULL][is_dota2_running()])
    say('Sounds/Telegram_открыт.mp3')


def terminate_program():
    say('Sounds/До_свидания.mp3')
    sys.exit()


def game_accept():
    keyboard.press_and_release('enter')
    say('Sounds/Приятной_игры.mp3')
