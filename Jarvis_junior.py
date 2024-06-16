import sounddevice as sd  # type: ignore
import queue
import vosk
import json
import pyttsx3
import webbrowser
import os

# Инициализация модели
vosk_model = vosk.Model('vosk-model-small-ru-0.22')

# Параметры записи
samplerate = 16000
device = 1  # Номер устройства ввода

# Очередь для передачи данных
q = queue.Queue()

# Функция обратного вызова для записи данных


def q_callback(indata, frames, time, status):
    q.put(bytes(indata))

# Функция для прослушивания и распознавания речи


def listen() -> str:
    try:
        with sd.RawInputStream(samplerate=samplerate, blocksize=1000,
                               device=device, dtype='int16', channels=1,
                               callback=q_callback):
            rec = vosk.KaldiRecognizer(vosk_model, samplerate)
            while True:
                data = q.get()
                if rec.AcceptWaveform(data):
                    result = json.loads(rec.Result())
                    text = result.get('text', '')
                    return text
    except Exception as e:
        print("Произошла ошибка:", str(e))


# Инициализация разговорщика
engine = pyttsx3.init()
# Установка настроек
engine.setProperty('voice', 'ru')
engine.setProperty('rate', 200)

# Функция озвучивания слов


def say(words):
    engine.say(words)
    engine.runAndWait()

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


# Список команд
commands = {'открой ютуб': open_youtube,
            'открой диск': open_discord,
            'открой телеграмм': open_tg}
# Бесконечный цикл, ожидающий команд
while True:
    text = listen()
    say(text)
    if 'джарвис' in text:
        if 'стоп' in text:
            break
        for command, function in commands.items():
            if command in text:
                say('Выполняю')
                function()
