

#include "EmployeeManager.h"

static Company* getCompany (AVLtree<Company>* tree , int Id)
{
    auto* newCompany = new Company(Id , 0);
    auto* checkIfHere = tree->findNode(tree->root , newCompany);
    if (checkIfHere == nullptr)
    {
        delete newCompany;
        delete checkIfHere;
        return nullptr;
    }
    delete newCompany;
    Company* data = checkIfHere->data;
    return data;
}

static Employee* getEmployee (AVLtree<Employee>* tree , int Id, int salary)
{
    auto* newEmployee = new Employee(Id,salary,0);
    auto* checkIfHere = tree->findNode(tree->root , newEmployee);
    if (checkIfHere == nullptr)
    {
        delete newEmployee;
        delete checkIfHere;
        return nullptr;
    }
    delete newEmployee;
    Employee* data = checkIfHere->data;
    return data;
}

static EmployeeById* getEmployeeById (AVLtree<EmployeeById>* tree , int Id )
{
    auto* newEmployee = new EmployeeById(Id,0,0);
    auto* checkIfHere = tree->findNode(tree->root , newEmployee);
    if (checkIfHere == nullptr)
    {
        delete newEmployee;
        delete checkIfHere;
        return nullptr;
    }
    delete newEmployee;
    EmployeeById* data = checkIfHere->data;
    return data;
}
/////////////////////main functions
StatusType EmployeeManager::AddCompany (int companyId , int value)
{
    if (companyId <= 0 || value <= 0)
    {
        return INVALID_INPUT;
    }
    if(getCompany(allCompanies , companyId) != nullptr)
    {
        return FAILURE;
    }
    auto* newCompany = new Company(companyId,value);
    if (!newCompany)
    {
        return ALLOCATION_ERROR;
    }
    this->allCompanies->insert(newCompany);
    return SUCCESS;
}

StatusType EmployeeManager::AddEmployee(int EmployeeId, int CompanyId, int Salary, int Grade)
{
    if (CompanyId <= 0 || Salary <= 0 || EmployeeId <=0 || Grade <0)
    {
        return INVALID_INPUT;
    }
    auto* reqCompany = getCompany(allCompanies,CompanyId);
    if (reqCompany == nullptr)
    {
        return FAILURE;
    }
    if (getEmployeeById(IdEmployees,EmployeeId) != nullptr)
    {
        return FAILURE;
    }
    auto* newEmployee = new Employee (EmployeeId,Salary,Grade);
    if (!newEmployee)
    {
        return ALLOCATION_ERROR;
    }
    auto* newEmployeeById = new EmployeeById (EmployeeId,Salary,Grade);
    if (!newEmployeeById)
    {
        return ALLOCATION_ERROR;
    }
    reqCompany->addEmployee(newEmployeeById,newEmployee);
    salaryEmployees->insert(newEmployee);
    IdEmployees->insert(newEmployeeById);
    highestSalary = salaryEmployees->biggest(salaryEmployees->root)->data;
    if (reqCompany->getEmployeesNum() == 1)
    {
        ///omer 27.4 - edited from: nonEmptyCompanies->insert(nonEmptyCompanies->root,reqCompany);
        nonEmptyCompanies->insert(reqCompany);
    }
    this->highestSalary = salaryEmployees->biggest(salaryEmployees->root)->data;
    return SUCCESS;

}

StatusType EmployeeManager::RemoveEmployee(int EmployeeId)
{
    if (EmployeeId <=0)
    {
        return INVALID_INPUT;
    }
    auto* reqEmployeeById = getEmployeeById(IdEmployees,EmployeeId);
    if (reqEmployeeById == nullptr)
    {
        return FAILURE;
    }
    auto* reqEmployee = getEmployee(salaryEmployees,EmployeeId,reqEmployeeById->getSalary());
    auto* reqCompany = reqEmployeeById->getEmployeeCompany();
    reqCompany->removeEmployee(reqEmployeeById,reqEmployee);
    if (reqCompany->getEmployeesNum() == 0)
    {
        nonEmptyCompanies->deleteNode(nonEmptyCompanies->root,reqCompany);
    }
    if (salaryEmployees->root != nullptr) {
        this->highestSalary = salaryEmployees->biggest(salaryEmployees->root)->data;
    }
    salaryEmployees->deleteNode(salaryEmployees->root , reqEmployee);
    IdEmployees->deleteNode(IdEmployees->root , reqEmployeeById);
    delete reqEmployee;
    return SUCCESS;
}

StatusType EmployeeManager::RemoveCompany(int CompanyId)
{
    if (CompanyId <=0)
    {
        return INVALID_INPUT;
    }
    auto* reqCompany = getCompany(allCompanies,CompanyId);
    if (reqCompany->getEmployeesNum() > 0)
    {
        return FAILURE;
    }
    allCompanies->deleteNode(allCompanies->root,reqCompany);
    delete reqCompany;
    return SUCCESS;
}

StatusType EmployeeManager::GetCompanyInfo(int CompanyId, int *Value, int *NumEmployees)
{
    if (CompanyId <=0)
    {
        return INVALID_INPUT;
    }
    auto* reqCompany = getCompany(allCompanies,CompanyId);
    if (reqCompany == nullptr)
    {
        return FAILURE;
    }
    *Value = reqCompany->getValue();
    *NumEmployees = reqCompany->getEmployeesNum();
    return SUCCESS;
}

StatusType EmployeeManager::GetEmployeeInfo(int EmployeeId, int *employerId, int *salary, int *Grade)
{
    if (EmployeeId <=0)
    {
        return INVALID_INPUT;
    }
    auto* reqEmployeeById = getEmployeeById(IdEmployees , EmployeeId);
    if (reqEmployeeById == nullptr)
    {
        return FAILURE;
    }
    *employerId = reqEmployeeById->getEmployeeCompany()->getId();
    *salary = reqEmployeeById->getSalary();
    *Grade = reqEmployeeById->getGrade();
    return SUCCESS;
}

StatusType EmployeeManager::IncreaseCompanyValue(int CompanyID, int valueIncrease)
{
    if (CompanyID <=0 || valueIncrease <=0)
    {
        return INVALID_INPUT;
    }
    auto* reqCompany = getCompany(allCompanies,CompanyID);
    if (reqCompany == nullptr)
    {
        return FAILURE;
    }
    reqCompany->ChangeValue(valueIncrease);
    return SUCCESS;
}

StatusType EmployeeManager::PromoteEmployee(int EmployeeId, int SalaryIncrease, int BumpGrade)
{
    if (EmployeeId <=0 || SalaryIncrease<=0)
    {
        return INVALID_INPUT;
    }
    auto* reqEmployeeById = getEmployeeById(IdEmployees , EmployeeId);
    if (reqEmployeeById == nullptr)
    {
        return FAILURE;
    }
    auto* reqEmployee = getEmployee(salaryEmployees, EmployeeId,reqEmployeeById->getSalary());
    if (reqEmployee == nullptr)
    {
        return FAILURE;
    }
    if (BumpGrade>0) {
        reqEmployee->BumpGrade(BumpGrade);
    }
    reqEmployeeById->BumpGrade(BumpGrade);
    reqEmployeeById->IncreaseSalary(SalaryIncrease);
    reqEmployeeById->BumpGrade(BumpGrade);
    reqEmployee->IncreaseSalary(SalaryIncrease);
    auto* reqCompany = reqEmployeeById->getEmployeeCompany();
    reqCompany->getEmployeesTree()->deleteNode(reqCompany->getEmployeesTree()->root, reqEmployee);
    reqCompany->getEmployeesTree()->insert(reqEmployee);
    reqCompany->setHighestEarner();
    salaryEmployees->deleteNode(salaryEmployees->root,reqEmployee);
    salaryEmployees->insert(reqEmployee);
    highestSalary = salaryEmployees->biggest(salaryEmployees->root)->data;
    return SUCCESS;
}

StatusType EmployeeManager::HireEmployee(int EmployeeId, int NewCompany)
{
    auto* reqCompany = getCompany(allCompanies,NewCompany);
    if (reqCompany == nullptr)
    {
        return FAILURE;
    }
    auto* reqEmployeeById = getEmployeeById(IdEmployees , EmployeeId);
    if (reqEmployeeById == nullptr)
    {
        return FAILURE;
    }
    auto* reqEmployee = getEmployee(salaryEmployees, EmployeeId, reqEmployeeById->getSalary());
    if (reqEmployee == nullptr)
    {
        return FAILURE;
    }

    reqEmployeeById->getEmployeeCompany()->removeEmployee(reqEmployeeById,reqEmployee);
    reqCompany->addEmployee(reqEmployeeById,reqEmployee);
    return  SUCCESS;
}

StatusType EmployeeManager::GetHighestEarner(int CompanyId, int *EmployeeId)
{
    if (CompanyId < 0)
    {
        if (this->highestSalary == nullptr)
        {
            return FAILURE;
        }
        *EmployeeId = highestSalary->getId();
        return SUCCESS;
    }

    auto* reqCompany = getCompany(nonEmptyCompanies, CompanyId);
    if (reqCompany == nullptr)
    {
        return FAILURE;
    }
    *EmployeeId = reqCompany->getHighestEarnerId();
    return SUCCESS;
}

StatusType EmployeeManager::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees)
{
    if (NumOfCompanies <=0)
    {
        return INVALID_INPUT;
    }
    Employees = (int** )malloc(NumOfCompanies*sizeof (int *));
    if(!Employees)
    {
        return ALLOCATION_ERROR;
    }
    auto* array = nonEmptyCompanies->inorderArray(NumOfCompanies);
    for (int i =0 ; i<NumOfCompanies ; i++)
    {
        *(Employees[i]) = array[i]->getHighestEarnerId();
    }
    return SUCCESS;
}

StatusType EmployeeManager::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees)
{
    if (Employees == nullptr || CompanyID == 0)
    {
        return INVALID_INPUT;
    }
    if (CompanyID < 0)
    {
        if (IdEmployees->size == 0) return FAILURE;
        auto* preArray = salaryEmployees->reverseInorderArray(salaryEmployees->size);
        if(!preArray)
        {
            return ALLOCATION_ERROR;
        }
        Employees = (int**)malloc((salaryEmployees->size)*sizeof (int*));
        if(!Employees)
        {
            return ALLOCATION_ERROR;
        }
        for (int i = 0 ; i < salaryEmployees->size ; i++)
        {
            *(Employees[i]) = preArray[i]->getId();
        }
        free(preArray);
        *NumOfEmployees = salaryEmployees->size;
        return SUCCESS;
    }

    auto* reqCompany = getCompany(allCompanies,CompanyID);
    if(reqCompany == nullptr || reqCompany->getEmployeesNum() == 0)
    {
        return FAILURE;
    }
    auto* preArray2 = reqCompany->getEmployeesTree()->reverseInorderArray(reqCompany->getEmployeesNum());
    if(!preArray2)
    {
        return ALLOCATION_ERROR;
    }
    Employees = (int**)malloc((reqCompany->getEmployeesNum())*sizeof (int*));
    if(!Employees)
    {
        return ALLOCATION_ERROR;
    }
    for (int i = 0 ; i < reqCompany->getEmployeesNum() ; i++)
    {
        *(Employees[i]) = preArray2[i]->getId();
    }
    free(preArray2);
    *NumOfEmployees=reqCompany->getEmployeesNum();
    return SUCCESS;
}

StatusType EmployeeManager::GetNumEmployeesMatching(int CompanyID, int MinEmployeeId, int MaxEmployeeId, int MinSalary,
                                                    int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
{
    if (TotalNumOfEmployees == nullptr || MinEmployeeId <0 || MaxEmployeeId <0||
        MinGrade < 0 || MinSalary < 0 || NumOfEmployees == nullptr || CompanyID ==0)
    {
        return INVALID_INPUT;
    }
    auto* maxIdEmployee = new EmployeeById(MaxEmployeeId, 0 ,0);
    auto* minIdEmployee = new EmployeeById(MinEmployeeId, 0 ,0);
    int numMatching =0;
    int numVeryMatching =0;
    if (CompanyID < 0)
    {
        auto* preArray = IdEmployees->smartInorderArray(minIdEmployee,maxIdEmployee,&numMatching);
        *TotalNumOfEmployees = numMatching;
        for (int i = 0 ; i< numMatching; i++)
        {
            if (preArray[i]->getSalary()>=MinSalary && preArray[i]->getGrade() >= MinGrade)
            {
                numVeryMatching ++;
            }
        }
        *NumOfEmployees = numVeryMatching;
        free(preArray);
        return SUCCESS;
    }
    auto* reqCompany = getCompany(allCompanies,CompanyID);
    if (reqCompany == nullptr)
    {
        return FAILURE;
    }
    auto* preArray2 = reqCompany->getEmployeesByIdTree()->smartInorderArray(minIdEmployee,maxIdEmployee,&numMatching);
    *TotalNumOfEmployees = numMatching;
    for (int i = 0 ; i< numMatching; i++)
    {
        if (preArray2[i]->getSalary()>=MinSalary && preArray2[i]->getGrade() >= MinGrade)
        {
            numVeryMatching ++;
        }
    }
    *NumOfEmployees = numVeryMatching;
    free(preArray2);
    return SUCCESS;
}





