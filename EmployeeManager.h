//
// Created by Eyal on 26/04/2022.
//

#ifndef HW1_WET_EMPLOYEEMANAGER_H
#define HW1_WET_EMPLOYEEMANAGER_H
#include "Company.h"

typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;

class EmployeeManager {
    AVLtree<Company>* allCompanies;
    AVLtree<Company>* nonEmptyCompanies;
    AVLtree<EmployeeById>* IdEmployees;
    Employee* highestSalary;
public:
    AVLtree<Employee>* salaryEmployees;
    EmployeeManager()
    {
        allCompanies = new AVLtree<Company>();
        nonEmptyCompanies = new AVLtree<Company>();
        salaryEmployees = new AVLtree<Employee>();
        IdEmployees = new AVLtree<EmployeeById>();
        highestSalary = nullptr;
    }

    ~EmployeeManager()
    {
        delete allCompanies;
        delete nonEmptyCompanies;
        delete salaryEmployees;
        delete IdEmployees;
    }

    StatusType AddCompany (int companyId , int value);

    StatusType AddEmployee (int EmployeeId , int CompanyId , int Salary , int Grade);

    StatusType RemoveEmployee (int EmployeeId);

    StatusType RemoveCompany (int CompanyId);

    StatusType GetCompanyInfo (int CompanyId , int* Value , int *NumEmployees);

    StatusType GetEmployeeInfo (int EmployeeId , int * employerId , int * salary , int *Grade);

    StatusType IncreaseCompanyValue (int CompanyID , int valueIncrease);

    StatusType PromoteEmployee (int EmployeeId , int SalaryIncrease, int BumpGrade);

    StatusType HireEmployee (int EmployeeId , int NewCompany);

    StatusType AcquireCompany (int AcquirerId , int TargetId , double factor);

    StatusType GetHighestEarner (int CompanyId , int* EmployeeId);

    StatusType GetAllEmployeesBySalary (int CompanyID , int** Employees , int* NumOfEmployees);

    StatusType GetHighestEarnerInEachCompany (int NumOfCompanies , int** Employees);

    StatusType GetNumEmployeesMatching (int CompanyID , int MinEmployeeId , int MaxEmployeeId ,
                                        int MinSalary , int MinGrade , int* TotalNumOfEmployees ,
                                        int* NumOfEmployees);




};


#endif //HW1_WET_EMPLOYEEMANAGER_H
