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
    bool isEmptyTime = true;
    int new_stMin = 0;
    new_stMin = appointment.getStartHour() * 60 + appointment.getStartMin();
    int new_endMin = 0;
    new_endMin = appointment.getEndHour() * 60 + appointment.getEndMin();
    int stMin = 0;
    int endMin = 0;
    for(int i = 0; i<this->size; i++)
    {
        if(this->appointments[i].getYear() == appointment.getYear() &&
           this->appointments[i].getMonth() == appointment.getMonth() &&
           this->appointments[i].getDate() == appointment.getDate())
        {
            
            stMin = this->appointments[i].getStartHour() * 60 + this->appointments[i].getStartMin();
            endMin = this->appointments[i].getEndHour() * 60 + this->appointments[i].getEndMin();

            if(new_stMin >= stMin && new_stMin <endMin){
                isEmptyTime = false;
            }else if(new_endMin >= stMin && new_endMin <endMin){
                isEmptyTime = false;
            }
            }
        
    }

    if(isEmptyTime == true){
        if (this->size == this->capacity)
        {
            this->resize();
        }
    this->appointments[this->size] = appointment;
    ++this->size;
    }
    return *this;
    
}




Calander& Calander::operator -=(const char* name){
    for(int i = 0; i<this->size; i++){
        if(strcmp(name, this->appointments[i].getName()) == 0){
            this->appointments[i] = this->appointments[this->size - 1];
            --this->size;
        }
    }
    return *this;
}

Calander& Calander::operator -=(const Appointment& appointment)
{
    for(int i = 0; i<this->size; i++){
        if(this->appointments[i].getStartHour() == appointment.getStartHour() &&
           this->appointments[i].getStartMin() == appointment.getStartMin() &&
           this->appointments[i].getDate() == appointment.getDate() &&
           this->appointments[i].getMonth() == appointment.getMonth() &&
           this->appointments[i].getYear() == appointment.getYear())
        {
            this->appointments[i] = this->appointments[this->size - 1];
             --this->size;
        }
    }
    return *this;
}

Calander::~Calander()
{
    this->reallocate();
}

std::ostream& operator <<(std::ostream& out, const Calander &object)
{
    for (int i = 0; i < object.size; ++i)
    {
        out << object.appointments[i] << '\n';
    }

    return out;
}

std::istream& operator >>(std::istream& in, Calander &object)
{
    int curSize;
    in >> curSize;
    for (int i = 0; i < curSize; ++i)
    {
        Appointment temp;
        in >> temp;
        object += temp;
    }

    return in;
}

void Calander::chronologicalSortByHour()
{
    for (int i = 0; i<size; i++){
        for(int j = i + 1; j <size; j++){
            if(this->appointments[j].getStartHour()<this->appointments[i].getStartHour()){
                std::swap(this->appointments[j], this->appointments[i]);
            }else if(this->appointments[j].getStartHour()==this->appointments[i].getStartHour() && (this->appointments[j].getStartMin()<this->appointments[i].getStartMin())){
                std::swap(this->appointments[j], this->appointments[i]);
            }
        }
    }
    
}

void Calander::filterByDay(const int date, const int month, const int year)
{
    std::ofstream appointmentsByDay("appointmentsByDay.txt");
    if (!appointmentsByDay.is_open())
    {
        std::cout << "Problem while opening the file - appointmentsByDay!";
        return;
    }
    appointmentsByDay <<"Appointments for "<<date<<"."<<month<<"."<<year<<std::endl;
    for(int i = 0; i<this->size; i++){
        if(this->appointments[i].getDate() == date && this->appointments[i].getMonth() == month && this->appointments[i].getYear()){
            appointmentsByDay << this->appointments[i]<< '\n';
        }
    }
    appointmentsByDay.close();
}

void Calander::searchApointment(const char* search){
    std::ofstream appointmentsSearchResult("appointmentsSearchResult.txt");
    if (!appointmentsSearchResult.is_open())
    {
        std::cout << "Problem while opening the file - appointmentsSearchResult!";
        return;
    }
    appointmentsSearchResult <<"Search result for "<<search<<std::endl;
    bool foundMatch = false;
    for(int i = 0; i<this->size; i++)
    {
        if(strstr(this->appointments[i].getName(),search)){
            appointmentsSearchResult<<this->appointments[i]<< '\n';
            foundMatch = true;
        }
        else if(strstr(this->appointments[i].getMessage(),search)){
            appointmentsSearchResult<<this->appointments[i]<< '\n';
            foundMatch = true;
        }
    }
    if(foundMatch == false){
        appointmentsSearchResult <<"Keyword not found"<<std::endl;
    }

    appointmentsSearchResult.close();
}

void Calander::findLoad(const int startdate, const int enddate, const int year, const int month)
{   
    int count = 0;
    int t = 0;
    int tempArr[31][2];
    for(int i = startdate; i <=enddate;i++)
    {
        for(int j = 0; j<this->size;j++){
            if(this->appointments[j].getDate() == i && this->appointments[j].getMonth() == month 
            && this->appointments[j].getYear()){
                count++;
        }}
        
        tempArr[t][1] = count;
        tempArr[t][0] = i;
        t++;
        count = 0;
    }

    for(int j = 0; j<enddate - startdate+1;j++){
        for(int m = j + 1; m <enddate - startdate+1; m++){
            if(tempArr[m][1] > tempArr[j][1]){
                std::swap(tempArr[m][0],tempArr[j][0]);
                std::swap(tempArr[m][1],tempArr[j][1]);
        }
    }}
    
    std::ofstream stats("stats.txt");
    if (!stats.is_open())
    {
        std::cout << "Problem while opening the file - stats!";
        return;
    }
    stats <<"Statistics for the period "<<startdate<<"."<<month<<"."<<year<<" - "<<enddate<<"."<<month<<"."<<year<<std::endl;
    for(int i = 0; i<enddate - startdate+1; i++){
        stats <<"For the date "<<tempArr[i][0]<<" there are "<<tempArr[i][1]<<" appointments"<< '\n';
        
    }
    stats.close();
    
}

    bool Calander::findAvailability(const int startPeriod, const int endPeriod,const int year, const int month, const int startHourInterval,const int endHourInterval, const int startMinInterval,const int endMinInterval, const int duration)
    {
        int startTime = startHourInterval*60 + startMinInterval;

        int endTime = endHourInterval * 60 + endMinInterval;
        bool dayIsEmpty = true;

        for(int j = 0; j<endPeriod-startPeriod+1;j++){
            for(int i = 0; i<this->size; i++){
                if(this->appointments[i].getDate() == startPeriod+j && this->appointments[i].getMonth() == month && this->appointments[i].getYear()){
                dayIsEmpty = false;
                }}
            if(dayIsEmpty == true){
                std::cout<<"There is an empty space on "<<startPeriod+j<<"."<<month<<"."<<year<<" at "<<startHourInterval<<":"<<startMinInterval<<std::endl;
                return true;;
                
        }
        dayIsEmpty = true; 
    }

    for (int i = 0; i<size; i++){
        for(int j = i + 1; j <size; j++){
            if(this->appointments[j].getStartHour()<this->appointments[i].getStartHour()){
                std::swap(this->appointments[j], this->appointments[i]);
            }else if(this->appointments[j].getStartHour()==this->appointments[i].getStartHour() && (this->appointments[j].getStartMin()<this->appointments[i].getStartMin())){
                std::swap(this->appointments[j], this->appointments[i]);
            }
        }
    }
        
        for(int j = 0; j<endPeriod-startPeriod+1;j++)
        {
            for(int i = 0; i<this->size; i++)
            {
                if(this->appointments[i].getDate() == startPeriod+j && this->appointments[i].getMonth() == month && this->appointments[i].getYear())
                {
                    if(startTime + duration < (this->appointments[i].getStartHour()*60 + this->appointments[i].getStartMin()))
                    {
                        std::cout<<"There is an empty space on "<<startPeriod+j<<"."<<month<<"."<<year<<" at "<<startTime/60<<":"<<startTime%60<<std::endl;
                        return true;
                    }
                    startTime = this->appointments[i].getEndHour()*60 + this->appointments[i].getEndMin();
                }

            }
            startTime = startHourInterval*60 + startMinInterval;
    }

    std::cout<<"There is no empty space in this period"<<std::endl;
    return false;
    }


