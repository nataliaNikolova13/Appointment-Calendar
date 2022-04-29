#include <iostream>

#include "appointment.hpp"

#include <cassert>

Appointment::Appointment(){
        this->date = 0;
        this->startHour = 0;
        this->startMin = 0;
        this->endHour = 0;
        this->endMin = 0;
        this->month = 0;
        this->year = 0;
        this->name = nullptr;
    }