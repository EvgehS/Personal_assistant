import vosk
import queue
import json
import sounddevice as sd


# Чтение вариативных переменных с конфига
def read_config(value: str) -> str:
    value += " = "
    file = open('.config.txt').readlines()
    for line in file:
        if value in line:
            return line[len(value):].replace('\n', '')
    return ""


# Отключаем логи
vosk.SetLogLevel(-1)
# Загрузка модели Vosk
vosk_model = vosk.Model('vosk-model-small-ru-0.22')

# Параметры записи
samplerate = 48000
device = int(read_config('sound_device'))

q = queue.Queue()


def q_callback(indata, frames, time, status):
    q.put(bytes(indata))


# Функция распознавания речи
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
                    if text:
                        return text
    except Exception as e:
        return f'Произошла ошибка: {e}'
