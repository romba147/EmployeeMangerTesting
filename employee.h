
#ifndef HW1_WET_EMPLOYEE_H
#define HW1_WET_EMPLOYEE_H
#include <iostream>
#include "AVLtree.h"
#include <memory>
class Company;

class Employee {
    int id;
    int salary;
    int grade;
public:
    Employee (int id, int salary , int grade) : id(id) , salary(salary) ,grade(grade){};

    bool operator == (const Employee& emp1) const {
        return this->id==emp1.id;
    }

    int getId () const {
        return this->id;
    }

    int getSalary () const
    {
        return salary;
    }

    int getGrade () const
    {
        return grade;
    }

    Employee BumpGrade(int num){
        if (num> 0){
            this->grade = this->grade +1;
        }
        return *this;
    }

    Employee IncreaseSalary(int num) {
        this->salary = this->salary + num;
        return *this;
    }


    virtual bool operator < (const Employee& emp1) const{
        if (this->salary == emp1.salary){
            return this->id > emp1.id;
        }
        return this->salary < emp1.salary;
    }

    virtual bool operator > (const Employee& emp1) const{
        if (this->salary == emp1.salary){
            return this->id < emp1.id;
        }
        return this->salary > emp1.salary;
    }
};


class EmployeeById : public Employee {

    Company* empCompany;

public:
    EmployeeById(int id, int salary , int grade) : Employee(id,salary,grade){
        empCompany = nullptr;
    }

    EmployeeById changeCompany(Company* new_company){
        this->empCompany = new_company;
        return *this;
    }

    Company* getEmployeeCompany () const
    {
        return this->empCompany;
    }

    bool operator < (const Employee& emp1) const override{
        return this->getId() < emp1.getId();
    }
    bool operator > (const Employee& emp1) const override{
        return this->getId() > emp1.getId();
    }

};



#endif //HW1_WET_EMPLOYEE_H
