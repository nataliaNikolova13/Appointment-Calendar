#include <iostream>
#include <fstream>
#include "calander.hpp"

int main(){
    //g++ main.cpp appointment.cpp calander.cpp
    //./a.exe
    Appointment first("Maria", 15, 30, 15, 40, 6, 2022,3,8,"message");
    Appointment second("Boris", 16, 30, 16, 00, 6, 2022,20,7,"message");
    Appointment third("Ivan", 14, 30, 15, 00, 6, 2022, 27,8,"message");
    Appointment five("Alex", 14, 30, 15, 00, 6, 2022, 3,8,"message");
    Appointment six("Niki", 17, 30, 15, 00, 6, 2022, 4,8,"message");
    Appointment seven("Peter", 10, 30, 15, 00, 6, 2022, 3,3,"message");
    Appointment eight("Mira", 13, 30, 15, 00, 6, 2022, 3,8,"message");

    //Appointment four;

    //std::cin >> four;
    //std::cout<< four<<std::endl;

    std::ofstream appointmentList("appointmentList.txt");
    if (!appointmentList.is_open()) 
    {
        std::cout << "Problem while opening the file - appointment" << std::endl;
        return 1;
    } 

    appointmentList << first<< '\n';
    appointmentList << second<< '\n';
    appointmentList << third<< '\n';
    //appointmentList << four<< '\n';
    appointmentList << five<< '\n';
    appointmentList << six<< '\n';
    appointmentList << seven<< '\n';
    appointmentList << eight<< '\n';

    Calander app;

    app += first;
    app += second;
    app += third;
    app += five;
    app += six;
    app += seven;
    app += eight;

    app.chronologicalSortByHour();

    //app -= "Boris";

    //appointmentList << app;
    
    appointmentList.close();
    //first.print();

    std::ofstream calanderList("calanderList.txt");
    if (!calanderList.is_open())
    {
        std::cout << "Problem while opening the file - calander!";
        return 1;
    }
    calanderList << app;
    calanderList.close();

    app.filterByDay(3,6,2022);
    
    return 0;
}