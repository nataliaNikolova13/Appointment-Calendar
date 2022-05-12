#include "appointment.hpp"

#include <cassert>
#include <cstring>

Appointment::Appointment(){
        this->date = 0;
        this->startHour = 0;
        this->startMin = 0;
        this->endHour = 0;
        this->endMin = 0;
        this->month = 0;
        this->year = 0;
        this->name = nullptr;
        this->message = nullptr;
    }

Appointment::Appointment(const char* name, int startHour, int startMin, int endHour, int endMin, int month, int year, int date, const char* message){
        this->setStartHour(startHour);
        this->setStartMin(startMin);
        this->setEndHour(endHour);
        this->setEndMin(endMin);
        this->setMonth(month);
        this->setYear(year);
        this->setName(name);
        this->setDate(date, month, year);
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
    int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if((year % 4 == 0) && ((year % 400 == 0) || (year % 100 != 0)))
    {
        assert(date > 0 && (date <= monthDays[month - 1]) + (month == 2));
    }else{
        assert(date > 0 && (date <= monthDays[month - 1]));
    }

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

void Appointment::changeName(const char* newName)
{
    delete[] this->name;
    this->name = new (std::nothrow) char[strlen(name) + 1];
    if(!this->name){
        std::cout<<"Problem"<<std::endl;
        return;
    }
    strcpy(this->name,newName);
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

void Appointment::changeMessage(const char* newMessage)
{
    delete[] this->message;
    this->message = new (std::nothrow) char[strlen(message) + 1];
    if(!this->message){
        std::cout<<"Problem"<<std::endl;
        return;
    }
    strcpy(this->message,newMessage);
}

void Appointment::changeStartHour(const int newStartHour, const int newStartMin)
{
    this->setStartHour(newStartHour);
    this->setStartMin(newStartMin);
}

void Appointment::changeEndHour(const int newEndHour, const int newEndMin)
{
    this->setEndHour(newEndHour);
    this->setEndMin(newEndMin);
}

void Appointment::changeDate(const int newDate, const int newMonth, const int newYear)
{
    this->setDate(newDate, newMonth, newYear);
    this->setMonth(newMonth);
    this->setYear(newYear);

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
        std::cout<<"Enter the start date, month and year "<<std::endl;
        in >> appointment.date >> appointment.month >> appointment.year;
        std::cout<<"Enter message: "<<std::endl;
        char arr[250] = {'\0',};
        in>>arr;
        appointment.message = new (std::nothrow) char[strlen(arr)+1];
        strcpy(appointment.message,arr);
        return in;
        
    }
    std::ostream& operator<<(std::ostream& out, Appointment appointment){
        out<<"The name is: "<<appointment.name<<", the date: "<<appointment.date<<"."<<appointment.month<<"."<<appointment.year<<" the time is: "<<appointment.startHour<<":"<<appointment.startMin<<" - "<<appointment.endHour<<":"<<appointment.endMin<<" and message: "<<appointment.message;
        return out;
    }

    Appointment::~Appointment(){
        delete[] this->name;
        delete[] this->message;
    }