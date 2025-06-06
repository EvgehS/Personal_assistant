#include <boost/python.hpp>
#include <iostream>
#include "../../Assistant.h"
#include <string>

std::string Assistant::listen()
{
    if(mode == "текст")
    {
        std::string command;
        std::cout << "Введите команду: ";
        std::getline(std::cin, command);
        return command;
    }

    try
    {
        // Инициализация Python
        static bool initialized = false;
        if (!initialized)
        {
            Py_Initialize();

            // Добавляем текущую директорию в sys.path
            boost::python::object sys = boost::python::import("sys");
            sys.attr("path").attr("insert")(0, ".");

            // Добавляем путь к site-packages с вариативной версией Python
            boost::python::object version_info = sys.attr("version_info");
            std::string major = boost::python::extract<std::string>(boost::python::str(version_info[0]));
            std::string minor = boost::python::extract<std::string>(boost::python::str(version_info[1]));
            std::string site_packages = "./venv/lib/python" + major + "." + minor + "/site-packages";
            sys.attr("path").attr("insert")(0, site_packages);

            initialized = true;
        }

        // Импорт модуля и вызов функции
        boost::python::object result = boost::python::import("Functions.Sounds.sound_functions").attr("listen");

        // Извлечение результата
        return boost::python::extract<std::string>(result());
    }
    catch (boost::python::error_already_set &)
    {
        PyErr_Print();
        return "error";
    }
}

void Assistant::speak(const std::string& text)
{
    last_phrase = text;

    if (mode == "текст")
        std::cout << text << std::endl;
    else
    {
        std::string command = "echo " + text + " | RHVoice-test -p vsevolod -t 95 -r 110 -o ./speak.wav";
        system(command.c_str());
        system("ffplay -autoexit -nodisp -loglevel quiet ./speak.wav > /dev/null 2>&1");
    }
}