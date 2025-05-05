import vosk
import queue
import json
import sounddevice as sd

# Загрузка модели Vosk
vosk_model = vosk.Model('vosk-model-small-ru-0.22')

# Параметры записи
samplerate = 48000
device = 2  # TODO: через config.txt

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
        print(f'Произошла ошибка: {e}')
        return None
