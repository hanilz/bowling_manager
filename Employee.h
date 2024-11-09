#pragma once

#define MIN_ID 1
#define MAX_ID 9999

typedef enum {
	eCEO, eManager, eCashier, eKitchen, eMaintenance, eNofEmpTypes
} eEmpType;


static const char* EmpTypeStr[eNofEmpTypes];

typedef struct {
	char* empName;
	int			empID;
	double		salary;
	eEmpType	empType;
} Employee;

int			initEmployee(Employee* pEmployee);
void		initCEOEmployee(Employee* pEmployee);
void		initManagerEmployee(Employee* pEmployee);
eEmpType	getEmpType();
const char* getEmpTypeStr(int type);
int			getEmployeeID();
double		getEmployeeSalary();
void		printEmployee(const Employee* pEmployee);
void		printEmployeeV(void* val);
void		freeEmployee(Employee*);
void		freeEmployeeV(void* ppEmp);
Employee*	findEmployee();  // TODO
int			compareEmployeesByID(int id1, int id2);
int			compareEmployeesBySalary(double salary1, double salary2);
int			compareEmployeesByEmpType(int type1, int type2);
int			saveEmployeeToFile(Employee* pEmployee, FILE* fp);
int			loadEmployeeFromFile(Employee* pEmployee, FILE* fp);
int			changeSalary(Employee*);
int			changeEmpType(Employee*);