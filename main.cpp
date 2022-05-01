#include "EmployeeManager.h"
using namespace std;
void printArray (int** array , int num)
{

    for (int i =0 ; i<num ; i++)
    {
        cout << (*array)[i] << " ";
    }
    cout << endl;
}

template <class T>
void printBT(const std::string& prefix, const node<T>* node, bool isLeft)
//void printBT(const std::string& prefix, const node<int>* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        if(node->data)
            std::cout << node->data->getId() << std::endl;
        else
            std::cout << "NULL-data" << std::endl;


        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }

}

template<class T>
///Left branch: ├──
///right branch: └──
void printBT(const node<T>* node)
{
    printBT("", node, false);
}

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
    steve->AddEmployee(4,11,2800,1);
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

    steve->AddCompany(22 , 300000);
    steve->AddEmployee(17 , 22 ,6000 , 5 );
    int grade =0;
    int salary =0;
    int companyId =0;
    steve->GetEmployeeInfo(17 , &companyId, &salary,&grade);
    cout << "exp 22 "<< companyId << " exp 6000 " << salary << " exp 5 " << grade << endl;
    steve->HireEmployee(17,11);
    steve->GetCompanyInfo(22, &value , &employeesNum);
    cout << "exp 0 " << employeesNum << endl;
    steve->GetHighestEarner(11, &highestEarner);
    cout << "exp 17 " << highestEarner << endl;
    steve->GetCompanyInfo(11,&value , &employeesNum);
    cout << "exp 6 " << employeesNum << endl;
    int **employeesBySalary = new int*;
    steve->GetAllEmployeesBySalary(11 ,employeesBySalary,&employeesNum );
    cout << "exp 17 3 4 5 2 1 " << endl;
    printArray(employeesBySalary, employeesNum);
    steve->AddCompany(33, 700);
    steve->AddCompany(44 , 90000);
    steve->AddCompany(55 , 7000);
    steve->AddEmployee(70,33,3000,1);
    steve->AddEmployee(71,44,3000,1);
    steve->AddEmployee(72,55,3000,1);
    int **highestEarnerInEachCompany = new int*;
    steve->GetHighestEarnerInEachCompany(4 , highestEarnerInEachCompany);
    cout << "exp 17 70 71 72 " << endl;
    printArray(highestEarnerInEachCompany,4);
    int numMatching =0 ;
    int numVeryMatching;
    steve->GetNumEmployeesMatching(11 , 2,5 , 2600 ,1 , &numMatching, &numVeryMatching);
    cout << "exp 4 " << numMatching << " exp 3 "<< numVeryMatching <<endl;
    steve->AddCompany(66 , 700000);
    steve->AddEmployee(56 , 66, 4000 , 3);
    steve->AddEmployee(57 , 66, 2400 , 3);
    steve->AddEmployee(58 , 66, 6500 , 3);
    steve->AddEmployee(59 , 66, 1900 , 3);
    steve->GetAllEmployeesBySalary(11, employeesBySalary,&employeesNum);
    steve->GetCompanyInfo(11 , &value ,&employeesNum );

    cout << "acquired company value :" << value << endl;
    printArray(employeesBySalary,employeesNum);
    steve->GetAllEmployeesBySalary(66, employeesBySalary,&employeesNum);
    steve->GetCompanyInfo(66 , &value ,&employeesNum );

    cout << "dest company value:" << value <<  endl;
    printArray(employeesBySalary,employeesNum);
    steve->AcquireCompany(66,11 , 1.4);
    steve->GetAllEmployeesBySalary(66, employeesBySalary,&employeesNum);
    cout << "merged company : " << endl;
    printArray(employeesBySalary,employeesNum);
    steve->GetCompanyInfo(66 , &value ,&employeesNum );
    cout << "exp 984372 " << value << endl;

}
