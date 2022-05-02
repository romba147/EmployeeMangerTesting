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
/*    auto* steve  = new EmployeeManager();
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
    free (highestEarnerInEachCompany);
    free (employeesBySalary);
    delete (steve);*/
    ////////////////////// test 2
/*    auto* em = new EmployeeManager();
    int** employees = new int*;
    int employeeId =0;
    int employeesNum =0;
    int numMatching =0;
    int numVeryMatching =0;
    int value =0;
    int companyId =0;
    int salary =0;
    int grade =0;
    em->AddCompany(11,5000);
    em->AddCompany(22,40000);
    em->AddEmployee(1,11,5000,5);
    em->AddEmployee(2,11,6000,4);
    em->AddEmployee(3,11,4000,3);
    em->AddEmployee(4,11,3000,4);
    em->AddEmployee(5,11,8000,1);
    em->AddEmployee(11,22,5500,5);
    em->AddEmployee(12,22,6500,4);
    em->AddEmployee(13,22,4500,3);
    em->AddEmployee(14,22,3500,4);
    em->AddEmployee(15,22,8500,1);
    em->GetHighestEarnerInEachCompany(2,employees);
    cout << "exp 5 15 ==";
    printArray(employees,2);
    free(employees);
    employees = new int*;
    em->GetHighestEarner(-1 , &employeeId);
    cout << "exp 15 " << employeeId << endl;
    em->PromoteEmployee(1,5000,2);
    em->GetHighestEarner(-1 , &employeeId);
    cout << "exp 1 " << employeeId << endl;
    em->GetAllEmployeesBySalary(-5 ,employees,&employeesNum);
    cout << "exp 1 15 5 12 2 11 13 3 14 4 == ";
    printArray(employees,employeesNum);
    free(employees);
    em->GetNumEmployeesMatching(-1 , 3,13,5000 , 3,&numMatching , &numVeryMatching);
    cout << "exp 6 " << numMatching << " exp 2 " << numVeryMatching << endl;
    if (em->AddEmployee(1,11,4000,5) != FAILURE)
    {
        cout << "NOT OK" << endl;
    }
    if (em->AddCompany(11,5000) != FAILURE)
    {
        cout << "NOT OK" << endl;
    }
    if (em->AcquireCompany(22,11,1.4) != FAILURE)
    {
        cout<<"NOT OK " << endl;
    }
    em->IncreaseCompanyValue(22,10000);
    if (em->AcquireCompany(22,11,1.5) != SUCCESS)
    {
        cout<<"NOT OK " << endl;
    }

    employees = new int*;
    em->GetAllEmployeesBySalary(22 ,employees,&employeesNum);
    cout << "exp 1 15 5 12 2 11 13 3 14 4 == ";
    printArray(employees,employeesNum);
    if (em->GetCompanyInfo(11,&value,&employeesNum) !=FAILURE)
    {
        cout<<"NOT OK " << endl;
    }
    em->AddCompany(33,5000);
    em->AddCompany(44,7000);
    em->AddCompany(55 , 8000);
    em->AddEmployee(21,33,8000 , 5);
    em->AddEmployee(22,44,9000,5);
    em->AddEmployee(23,55,8000,5);
    em->GetHighestEarnerInEachCompany(3,employees);
    cout << "exp 1 21 22 ==";
    printArray(employees,3);
    free (employees);
    employees = new int*;
    em->HireEmployee(21,44);
    em->GetHighestEarnerInEachCompany(3,employees);
    cout << "exp 1 22 23 ==";
    printArray(employees,3);
    em->RemoveEmployee(1);
    free (employees);
    employees = new int*;
    em->GetHighestEarnerInEachCompany(3,employees);
    cout << "exp 15 22 23 ==";
    printArray(employees,3);
    em->GetEmployeeInfo(5,&companyId,&salary,&grade);
    cout << "exp 22 " << companyId << " exp 8000 " << salary << " exp 1 "<<grade << endl;

    delete em;*/
//////////test 3
    auto *em = new EmployeeManager();
    int highestEarner=0;
    int** highestEarnerInEach = new int*;
    int** employeesBySalary = new int*;
    int employeesNum=0;
    int numMatching =0;
    int numVeryMatching =0;
    int value =0;
    int companyid=0;
    int sat=0;
    em->AddCompany (1 ,50);
    em->AddCompany (2,500);
    em->AddCompany (3,5000);
    em->AddEmployee (11, 1 ,60 ,70);
    em->AddEmployee (12 ,2 ,600 ,700);
    em->AddEmployee (13 ,3 ,6000 ,7000);
    em->AcquireCompany (3 ,2 ,1.63);
    em->IncreaseCompanyValue (1 ,100);
    em->PromoteEmployee (13 ,10 ,1);
    em->GetHighestEarner (12,&highestEarner);
    em->GetAllEmployeesBySalary (3,employeesBySalary,&employeesNum);
    em->GetHighestEarnerInEachCompany (2,highestEarnerInEach);
    em->GetNumEmployeesMatching (-1, 0 ,20 ,100 ,10,&numMatching,&numVeryMatching);
    em->HireEmployee (12, 1);
    em->GetCompanyInfo (1,&value,&employeesNum);
    em->GetCompanyInfo (2,&value,&employeesNum);
    em->GetCompanyInfo (3,&value,&employeesNum);
    em->GetEmployeeInfo (11,&companyid,&sat,&sat);
    em->GetEmployeeInfo (12,&companyid,&sat,&sat);
    em->GetEmployeeInfo (13,&companyid,&sat,&sat);
    em->RemoveEmployee (13);
    em->RemoveCompany (3);
    em->AddEmployee (11 ,1 ,70, 25);
    em->GetCompanyInfo (-14,&value,&employeesNum);
    em->GetCompanyInfo (1,&value,&employeesNum);
    em->IncreaseCompanyValue (1 ,39);
    em->IncreaseCompanyValue (1 ,15);
    em->GetHighestEarner (1,&highestEarner);
    em->GetNumEmployeesMatching (1 ,1, 52 ,54 ,65,&numMatching,&numVeryMatching);
    em->GetHighestEarnerInEachCompany (1,highestEarnerInEach);
    delete em;

}
