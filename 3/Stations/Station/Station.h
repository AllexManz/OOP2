#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <vector>
#include <string>


struct LinesPairs{
    std::string line;
    std::string station;
};



// InterfaceClass
class Station{
private:
    std::string station_name;
    std::string line_name;
public:
    virtual ~Station() = default;

    [[nodiscard]] virtual std::string get_station() const {return station_name;}
    [[nodiscard]] virtual std::string get_line() const {return line_name;}

    void set_station(std::string& new_name) {station_name = new_name;}
    void set_line(std::string& new_name) {line_name = new_name;}

    virtual std::ostream& print(std::ostream &s) = 0;
    virtual std::vector<LinesPairs> get_interchange() = 0;
    [[nodiscard]] virtual std::string get_type() const {return "OrdinaryStation";}
};


#endif



/*
TODO:
    1. не копировать при возврате


TODO:
    Теория:
        1. Чисто виртуальный метод
            Чисто виртуальная функция (pure virtual function) – виртуальная функция,
            не имеющая определения в базовом классе.
            Для страховки от неправильного вызова ее часто объявляют равной нулю
        2. Что такое абстрактный класс
            Абстрактные классы - это классы, которые содержат или наследуют без
            переопределения хотя бы одну чистую виртуальную функцию. Абстрактный класс
            определяет интерфейс для переопределения производными классами.
*/