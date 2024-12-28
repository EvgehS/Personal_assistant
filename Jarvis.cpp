#include <boost/python.hpp>
#include <iostream>

int main()
{
    Py_Initialize();

    boost::python::object sys = boost::python::import("sys");
    sys.attr("path").attr("insert")(1, "Sounds/");

    boost::python::object recognize_speech = boost::python::import("sound_functions").attr("listen");
    while(true)
    {
        std::string command = boost::python::extract<std::string>(recognize_speech());

        std::cout << "Распознанная команда: " << command << std::endl;
    }

    Py_Finalize();
    return 0;
}
