import vosk
import queue
import json
import sounddevice as sd
import pyttsx3


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
        # пизданул
        # переработал
        # пизданул
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
