#ifndef STUDENT_H
#define STUDENT_H

#include<iostream>
#include <fstream>
using namespace std;


struct student{
    int studentID;
    char name[15];
    float grade;
};

    void getrecord(student recors[]);
    void readrecord(student record[]);
 
#endif//ends the conditional block