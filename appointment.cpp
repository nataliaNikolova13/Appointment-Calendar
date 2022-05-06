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
        this->endDate = 0;
        this->startHour = 0;
        this->startMin = 0;
        this->endHour = 0;
        this->endMin = 0;
        this->month = 0;
        this->year = 0;
        this->name = nullptr;
        this->message = nullptr;
    }

Appointment::Appointment(const char* name, int startHour, int startMin, int endHour, int endMin, int month, int year, int date, int endDate, const char* message){
        this->setStartHour(startHour);
        this->setStartMin(startMin);
        this->setEndHour(endHour);
        this->setEndMin(endMin);
        this->setMonth(month);
        this->setYear(year);
        //this->setDuration(duration);
        this->setName(name);
        this->setDate(date, month, year);
        this->setEndDate(endDate, date, month, year);
        this->setMessage(message);
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

int Appointment::getEndDate() const
{
    return this->endDate;
}

const char* Appointment::getName() const
{
    return this->name;
}    

const char* Appointment::getMessage() const
{
    return this->message;
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

void Appointment::setEndDate(const int endDate, const int date, const int month, const int year){
    assert(endDate > 0 && (endDate <= MONTH_DAYS[month - 1]) + (month == 2 && isLeap(year)));
    //assert(endDate>=date);
    this->endDate = endDate;
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

void Appointment::setMessage(const char* message)
{
    this->message = new (std::nothrow) char[strlen(message) + 1];
    if(!this->message){
        std::cout<<"Problem"<<std::endl;
        return;
    }
    strcpy(this->message,message);
}

std::istream& operator>>(std::istream& in, Appointment &appointment){
        std::cout<<"Enter name: "<<std::endl;
        char buffer[50] = {'\0',};
        in>>buffer;
        appointment.name = new (std::nothrow) char[strlen(buffer)+1];
        strcpy(appointment.name,buffer);
        std::cout<<"Enter the star hour and min: "<<std::endl;
        in >> appointment.startHour >> appointment.startMin;
        std::cout<<"Enter the end hour and min: "<<std::endl;
        in >> appointment.endHour >> appointment.endMin;
        std::cout<<"Enter the start date, end date, month and year "<<std::endl;
        in >> appointment.date >> appointment.endDate >> appointment.month >> appointment.year;
        std::cout<<"Enter message: "<<std::endl;
        char arr[250] = {'\0',};
        in>>arr;
        appointment.message = new (std::nothrow) char[strlen(arr)+1];
        strcpy(appointment.message,arr);
        return in;
        
    }
    std::ostream& operator<<(std::ostream& out, Appointment appointment){
        out<<"The name is: "<<appointment.name<<", the date: "<<appointment.date<<" the time is: "<<appointment.startHour<<":"<<appointment.startMin<<" - "<<appointment.endHour<<":"<<appointment.endMin;
        return out;
    }

    Appointment::~Appointment(){
        delete[] this->name;
        delete[] this->message;
    }