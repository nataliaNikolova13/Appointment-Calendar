//#include <iostream>

#include "appointment.hpp"

#include <cassert>
#include <cstring>

const unsigned int MONTH_DAYS[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeap(unsigned int year)
{
    return (year % 4 == 0) && ((year % 400 == 0) || (year % 100 != 0));
}
//+крайна дата
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

Appointment::Appointment(const char* name, int startHour, int startMin, int endHour, int endMin, int month, int year, int date){
        this->setStartHour(startHour);
        this->setStartMin(startMin);
        this->setEndHour(endHour);
        this->setEndMin(endMin);
        this->setMonth(month);
        this->setYear(year);
        //this->setDuration(duration);
        this->setName(name);
        this->setDate(date, month, year);
    }

int Appointment::getStartHour() const
{
    return this->startHour;
}

int Appointment::getEndHour() const
{
    return this->endHour;
}

int Appointment::getStartMin() const
{
    return this->startMin;
}

int Appointment::getEndMin() const
{
    return this->endMin;
}

int Appointment::getMonth() const
{
    return this->month;
}

int Appointment::getYear() const
{
    return this->year;
}

int Appointment::getDate() const
{
    return this->date;
}

const char* Appointment::getName() const
{
    return this->name;
}    

void Appointment::setStartHour(const int startHour){
    assert(startHour>=0 && startHour<24);
    this->startHour = startHour;
}
    
void Appointment::setStartMin(const int startMin)
{
    assert(startMin >= 0 && startMin <60);
    this->startMin = startMin;
}

void Appointment::setEndHour(const int endHour)
{
    assert(endHour>=0 && endHour<24);
    this->endHour = endHour;
}

void Appointment::setEndMin(const int endMin)
{
    assert(endMin >= 0 && endMin <60);
    this->endMin = endMin;
}

void Appointment::setMonth(const int month)
{
    assert(month>0 && month <13);
    this->month = month;
}

void Appointment::setYear(const int year)
{
    assert(year>2000);
    this->year = year;
}
    
void Appointment::setDate(const int date, const int month, const int year)
{
    assert(date > 0 && (date <= MONTH_DAYS[month - 1]) + (month == 2 && isLeap(year)));
    this->date = date;
}

void Appointment::setName(const char* name)
{
    this->name = new (std::nothrow) char[strlen(name) + 1];
    if(!this->name){
        std::cout<<"Problem"<<std::endl;
        return;
    }
    strcpy(this->name,name);
}

std::istream& operator>>(std::istream& in, Appointment appointment){
        std::cout<<"Enter name: "<<std::endl;
        char buffer[50];
        //buffer[50]; 
        in>>buffer;
        appointment.name = new (std::nothrow) char[strlen(buffer)];
        strcpy(appointment.name,buffer);
        //strcpy(buffer, appointmentma.name);
        //in >> appointment.name;
        /*
        std::cout << "Enter name: ";
        char arr[1024+1];
        in>> arr;
        //std::cin.getline(arr,1024);
        student.name = new (std::nothrow) char[strlen(arr)];
        strcpy(student.name,arr);
        */
        std::cout<<"Enter the star hour and min: "<<std::endl;
        in >> appointment.startHour >> appointment.startMin;
        std::cout<<"Enter the end hour and min: "<<std::endl;
        in >> appointment.endHour >> appointment.endMin;
        std::cout<<"Enter the date, month and year "<<std::endl;
        in >> appointment.date >> appointment.month >> appointment.year;
        //appointment.duration = (appointment.endHour - appointment.startHour)*60 + appointment.endMin - appointment.startMin;
        return in;
    }
    std::ostream& operator<<(std::ostream& out, Appointment appointment){
        out<<"The name is: "<<appointment.name<<" the time is: "<<appointment.startHour<<":"<<appointment.startMin<<" - "<<appointment.endHour<<":"<<appointment.endMin;
        return out;
    }

    Appointment::~Appointment(){
        delete[] this->name;
    }