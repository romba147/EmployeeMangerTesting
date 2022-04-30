#include "EmployeeManager.h"
using namespace std;
int main()
{
    auto* steve  = new EmployeeManager();
    steve->AddCompany(10,5000);
    int value = 0;
    int employeesNum =0;
    steve->GetCompanyInfo(10,&value,&employeesNum);
    cout << "exp 5000 " << value << " exp 0 " << employeesNum << endl;


    steve->AddEmployee(1,10,1000,1);
    steve->GetCompanyInfo(10,&value,&employeesNum);
    cout << "exp 5000 " << value << " exp 1 " << employeesNum << endl;
    steve->AddCompany(20,7000);
    steve->RemoveEmployee(1);
    steve->GetCompanyInfo(10,&value,&employeesNum);
    cout << "exp 5000 " << value << " exp 0 " << employeesNum << endl;
    steve->RemoveCompany(10);
    if (steve->GetCompanyInfo(10,&value,&employeesNum) != FAILURE)
    {
        cout << "fail" << endl;
    }
    ////////////////
    steve->AddCompany(11,3000);
    steve->GetCompanyInfo(11,&value,&employeesNum);
    cout << "exp 3000 " << value << " exp 0 " << employeesNum << endl;
    steve->AddEmployee(1,11,2000,1);
    steve->AddEmployee(2,11,2500,1);
    steve->AddEmployee(3,11,2700,1);
    steve->AddEmployee(4,11,2900,1);
    steve->AddEmployee(5,11,2800,1);
    steve->IncreaseCompanyValue(11,123);
    steve->GetCompanyInfo(11,&value,&employeesNum);
    cout << "exp 3123 " << value << " exp 5 " << employeesNum << endl;
    int highestEarner = 0;
    steve->GetHighestEarner(11, &highestEarner);
    cout << "exp 4 " << highestEarner << endl;
    steve->PromoteEmployee(3,3000 , 2);
    steve->GetHighestEarner(11, &highestEarner);
    cout << "exp 3 " << highestEarner << endl;



}
