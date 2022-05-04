#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

#include "calander.hpp"

const std::size_t INITIAL_CAPACITY = 2;
const std::size_t INCREASE_STEP = 2;

void Calander::reallocate()
{
    delete[] this->appointments;
    
}

void Calander::copy(const Calander& other)
{
    this->appointments = new (std::nothrow) Appointment[other.capacity];
    if (!this->appointments)
        {
            std::cout << "Memory problem with copy constructor" << std::endl;
            return;
        }
    for (std::size_t i = 0; i < other.size; ++i)
        {
            this->appointments[i] = other.appointments[i];
        }

        this->size = other.size;
        this->capacity = other.capacity;    
}

void Calander::resize()
{
    Appointment* newAppointment = new (std::nothrow) Appointment[this->capacity * INCREASE_STEP];
        if (!newAppointment)
        {
            std::cout << "Memory problem with resize" << std::endl;
            return;
        }

        for (std::size_t i = 0; i < this->size; ++i)
        {
            newAppointment[i] = this->appointments[i];
        }

        this->reallocate();
        this->appointments = newAppointment;
        this->capacity *= INCREASE_STEP;
}

Calander::Calander()
{
    this->appointments = new (std::nothrow) Appointment[INITIAL_CAPACITY];
        if (!this->appointments)
        {
            std::cout << "Memory problem with constructor" << std::endl;
            return;
        }

        this->capacity = INITIAL_CAPACITY;
        this->size = 0;
}

Calander::Calander(const Calander& other)
{
    this->copy(other);
}

Calander& Calander::operator = (const Calander& other)
{
    if (this != &other)
        {
            this->reallocate();
            this->copy(other);
        }

        return *this;
}

Calander& Calander::operator +=(const Appointment& appointment)
{
    if (this->size == this->capacity)
        {
            this->resize();
        }
    this->appointments[this->size] = appointment;
    ++this->size;
    return *this;
}

Calander::~Calander()
{
    this->reallocate();
}

std::ostream& operator <<(std::ostream& out, const Calander &obj)
{
    //out << obj.size << '\n';

    for (int i = 0; i < obj.size; ++i)
    {
        out << obj.appointments[i] << '\n';
    }

    return out;
}

std::istream& operator >>(std::istream& in, Calander &obj)
{
    int curSize;
    in >> curSize;
    for (int i = 0; i < curSize; ++i)
    {
        Appointment temp;
        in >> temp;
        obj += temp;
    }

    return in;
}