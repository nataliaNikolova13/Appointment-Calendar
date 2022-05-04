#include <iostream>
#include <fstream>
#include "calander.hpp"

int main(){
    
    Appointment first("Maria", 14, 30, 15, 40, 4, 2022,3);
    Appointment second("Boris", 14, 30, 16, 00, 6, 2022,20);
    Appointment third("Ivan", 14, 30, 15, 00, 6, 2022, 27);

    //Appointment four;

    //std::cin >> four;

    std::ofstream appointmentList("appointmentList.txt");
    if (!appointmentList.is_open()) 
    {
        std::cout << "Problem while opening the file" << std::endl;
        return 1;
    } 

    appointmentList << first<< '\n';
    appointmentList << second<< '\n';
    appointmentList << third<< '\n';
    //appointmentList << four<< '\n';
    
    appointmentList.close();
    //first.print();
    return 0;
}