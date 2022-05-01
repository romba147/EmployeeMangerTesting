#ifndef HW1_WET_COMPANY_H
#define HW1_WET_COMPANY_H
#include <iostream>
#include "employee.h"


class Company {
    int id;
    int value;
    int employees_num;
    Employee* highest_earner;
    AVLtree<Employee>* employees_tree;
    AVLtree<EmployeeById>* employees_id_tree;
public:
    Company(int id , int value) : id(id) , value(value) {
        employees_num = 0;
        employees_tree = new AVLtree<Employee>();
        employees_id_tree = new AVLtree<EmployeeById>();
        highest_earner = nullptr;
    };


    int getId () const {
        return this->id;
    }

    int getEmployeesNum () const
    {
        return employees_num;
    }

    int getValue () const
    {
        return value;
    }

    Company setHighestEarner()
    {
        highest_earner = employees_tree->biggest(employees_tree->root)->data;
        return *this;
    }

    int getHighestEarnerId () const
    {
        return this->highest_earner->getId();
    }

    AVLtree<Employee>* getEmployeesTree () const {
        return employees_tree;
    }

    AVLtree<EmployeeById>* getEmployeesByIdTree () const {
        return employees_id_tree;
    }

    Company setEmployeesTree(AVLtree<Employee>* newTree)
    {
        employees_tree = newTree;
        return *this;
    }

    Company setEmployeesByIdTree(AVLtree<EmployeeById>* newTree)
    {
        employees_id_tree = newTree;
        return *this;
    }

    Company ChangeValue(int num){
        this->value = this->value + num;
        return *this;
    }

    Company setEmployeesNum(int num)
    {
        employees_num = num;
        return *this;
    }
    Company addEmployee (EmployeeById* employeeId , Employee* employee)
    {
        ///omer 27.4 - edited from: employees_id_tree->insert(employees_id_tree->root,employeeId);
        employees_id_tree->insert(employeeId);
        ///omer 27.4 - edited from: employees_tree->insert(employees_tree->root,employee);
        employees_tree->insert(employee);
        employees_num ++;
        employeeId->changeCompany(this);
        highest_earner = employees_tree->biggest(employees_tree->root)->data;
        return *this;
    }

    Company removeEmployee (EmployeeById* employeeIdRemove , Employee* employeeRemove)
    {
        this->employees_id_tree->deleteNode(employees_id_tree->root,employeeIdRemove);
        this->employees_tree->deleteNode(employees_tree->root, employeeRemove);
        employees_num --;
        if (employees_tree->root == nullptr)
        {
            highest_earner = nullptr;
            return *this;
        }
        employeeIdRemove->changeCompany(nullptr);
        highest_earner =employees_tree->biggest(employees_tree->root)->data;
        return *this;
    }

    bool operator == (const Company& cmp1) const {
        return this->id == cmp1.id;
    }
    bool operator < (const Company& cmp1) const {
        return this->id < cmp1.id;
    }
    bool operator > (const Company& cmp1) const {
        return this->id > cmp1.id;
    }


};


#endif //HW1_WET_COMPANY_H
