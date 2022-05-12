#pragma once

#include "appointment.hpp"

class Calander{
private:
    Appointment* appointments;
    std::size_t size;
    std::size_t capacity;

    void reallocate();
    void resize();
    void copy(const Calander& other);

public:
    Calander();
    ~Calander();
    Calander(const Calander& other);
    Calander& operator = (const Calander& other);
    Calander& operator +=(const Appointment& appointment);
    Calander& operator -=(const char* name);
    Calander& operator -=(const Appointment& appointment);
    friend std::ostream& operator <<(std::ostream& out, const Calander &object);
    friend std::istream& operator >>(std::istream& in, Calander &object);
    void filterByDay(const int date, const int month, const int year);
    void chronologicalSortByHour();
    void searchApointment(const char* search);
    void findLoad(const int startdate, const int enddate, const int year, const int month);
    bool findAvailability(const int startPeriod, const int endPeriod,const int year, const int month, const int startHourInterval,const int endHourInterval, const int startMinInterval,const int endMinInterval, const int duration);
};