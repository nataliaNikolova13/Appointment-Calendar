#include <iostream>
#include <fstream>
#include "calander.hpp"

void testProgramm()
{
    //резервиране на часовя
    Appointment first("Maria", 10, 30, 15, 40, 6, 2022,3,"message");
    Appointment second("Boris", 15, 30, 16, 00, 6, 2022,3,"message");
    Appointment third("Ivan", 14, 30, 15, 00, 6, 2022, 27,"message");
    Appointment five("Alex", 14, 30, 15, 00, 6, 2022, 3,"message");
    Appointment six("Niki", 11, 30, 14, 00, 6, 2022, 4,"message");
    Appointment seven("Peter", 10, 30, 15, 00, 6, 2022, 3,"message");
    Appointment eight("Mira", 16, 00, 16, 30, 6, 2022, 3,"message");

    //Appointment four;

    //std::cin >> four;
    //std::cout<< four<<std::endl;

    std::ofstream appointmentList("appointmentList.txt");
    if (!appointmentList.is_open()) 
    {
        std::cout << "Problem while opening the file - appointment" << std::endl;
        return;
    } 

    appointmentList << first<< '\n';
    appointmentList << second<< '\n';
    appointmentList << third<< '\n';
    //appointmentList << four<< '\n';
    appointmentList << five<< '\n';
    appointmentList << six<< '\n';
    appointmentList << seven<< '\n';
    appointmentList << eight<< '\n';

    first.changeName("New name");
    second.changeMessage("new message");
    third.changeDate(5,3,2022);

    Calander app;

    //резервираните часове се слагат в календара
    //ако въведената дата и час не са свободни, часът не се добавя в календара
    app += first;
    app += second;
    app += third;
    app += five;
    app += six;
    app += seven;
    app += eight;

    app.chronologicalSortByHour();

    //махане на час по въведено име

    //app -= "Boris";

    //appointmentList << app;
    
    appointmentList.close();
    //first.print();

    std::ofstream calanderList("calanderList.txt");
    if (!calanderList.is_open())
    {
        std::cout << "Problem while opening the file - calander!";
        return;
    }
    calanderList << app;
    calanderList.close();

    app.filterByDay(3,6,2022);


    //търсене по ключова дума и извеждане на резултатите във файл
    /*std::cout<<"Enter keyword for search: "<<std::endl;
    char search[100];
    std::cin.getline(search, 100);
    app.searchApointment(search);
    */
    app.searchApointment("message");

    //извеждане на натоварност във файл
    app.findLoad(2, 4, 2022, 6);


    //duration is in min
    app.findAvailability(3, 9, 2022, 6, 10,17,0,0, 60);
}

int main(){
    //g++ main.cpp appointment.cpp calander.cpp
    //./a.exe

    testProgramm();
    return 0;
}