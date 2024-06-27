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
    link = 'C:\\Users\\1\\OneDrive\\Рабочий стол\\sounds\\Дис_запущен.mp3'
    say(link)


def open_youtube():
    subprocess.Popen([paths['chrome'], 'https://www.youtube.com/'],
                     stdout=[None, subprocess.DEVNULL][is_dota2_running()])
    link = 'C:\\Users\\1\\OneDrive\\Рабочий стол\\sounds\\Ютуб_открыт.mp3'
    say(link)


def open_tg():
    subprocess.Popen([paths['telegram']],
                     stdout=[None, subprocess.DEVNULL][is_dota2_running()])
    link = 'C:\\Users\\1\\OneDrive\\Рабочий стол\\sounds\\Телеграм_открыт.mp3'
    say(link)


def terminate_program():
    link = 'C:\\Users\\1\\OneDrive\\Рабочий стол\\sounds\\До_свидания.mp3'
    say(link)
    sys.exit()


def game_accept():
    keyboard.press_and_release('enter')
    link = 'C:\\Users\\1\\OneDrive\\Рабочий стол\\sounds\\Приятной_игры.mp3'
    say(link)
