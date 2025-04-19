#include <boost/python.hpp>
#include <string>

std::string listen() {
    try {
        // Инициализация Python
        static bool initialized = false;
        if (!initialized) {
            Py_Initialize();
            boost::python::object sys = boost::python::import("sys");
            sys.attr("path").attr("insert")(0, "/home/evgen/programs/Personal_assistant/venv/lib/python3.10/site-packages");
            sys.attr("path").attr("insert")(0, "/home/evgen/programs/Personal_assistant");

            initialized = true;
        }

        // Импорт модуля и вызов функции
        boost::python::object result = boost::python::import("Sounds.sound_functions").attr("listen");
        
        // Извлечение строки из результата Python
        return boost::python::extract<std::string>(result());
    } catch (boost::python::error_already_set&) {
        PyErr_Print();
        return "error";
    }
}

