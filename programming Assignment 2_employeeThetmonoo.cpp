#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class Employee
class Employee {
protected:
    string empID;
    string name;
    string position;
    string empType;
    string startDate;
    double basicSalary;
    double hourlyWage;
    double workingHours;
    double leaveDays;
    double overtimeHours;

public:
    // Constructor
    Employee(string empID, string name, string position, string empType, string startDate, 
             double basicSalary, double hourlyWage, double workingHours, 
             double leaveDays, double overtimeHours)
        : empID(empID), name(name), position(position), empType(empType), startDate(startDate), 
          basicSalary(basicSalary), hourlyWage(hourlyWage), workingHours(workingHours), 
          leaveDays(leaveDays), overtimeHours(overtimeHours) {}

    // Function to calculate salary
    double calculateSalary() {
        double dailyWage = basicSalary / 30; // Assuming 30 days per month
        double overtimePay = overtimeHours * 2 * dailyWage;
        double bonus = calculateBonus();
        double penalty = 0;

        if (leaveDays > 4 && overtimeHours > 0) {
            penalty = basicSalary * 0.01;
        }

        double grossSalary = basicSalary + overtimePay + bonus - penalty;
        double taxIncome = grossSalary * 0.02;
        double socialSecurityTax = 10;

        return grossSalary - taxIncome - socialSecurityTax;
    }

    // Function to calculate bonus based on leave days
    double calculateBonus() {
        if (leaveDays == 0)
            return 50000;
        else if (leaveDays == 1)
            return 20000;
        else if (leaveDays == 2)
            return 10000;
        else
            return 0;
    }

    // Virtual function for displaying details
    virtual void displayInfo() {
        cout << "Employee ID: " << empID << endl;
        cout << "Name: " << name << endl;
        cout << "Position: " << position << endl;
        cout << "Employee Type: " << empType << endl;
        cout << "Start Date: " << startDate << endl;
        cout << "Basic Salary: $" << basicSalary << endl;
        cout << "Hourly Wage: $" << hourlyWage << endl;
        cout << "Working Hours: " << workingHours << endl;
        cout << "Leave Days: " << leaveDays << endl;
        cout << "Overtime Hours: " << overtimeHours << endl;
        cout << "Net Salary: $" << calculateSalary() << endl;
    }
};

// Derived class Fulltime
class Fulltime : public Employee {
public:
    Fulltime(string empID, string name, string position, string startDate, double basicSalary, 
             double hourlyWage, double workingHours, double leaveDays, double overtimeHours)
        : Employee(empID, name, position, "Full-Time", startDate, basicSalary, hourlyWage, 
                   workingHours, leaveDays, overtimeHours) {}

    void displayInfo() override {
        cout << "Full-Time Employee Details:\n";
        Employee::displayInfo();
    }
};

// Derived class Parttime
class Parttime : public Employee {
public:
    Parttime(string empID, string name, string position, string startDate, double basicSalary, 
             double hourlyWage, double workingHours, double leaveDays, double overtimeHours)
        : Employee(empID, name, position, "Part-Time", startDate, basicSalary, hourlyWage, 
                   workingHours, leaveDays, overtimeHours) {}

    void displayInfo() override {
        cout << "Part-Time Employee Details:\n";
        Employee::displayInfo();
    }
};

int main() {
    vector<Employee*> employees; // Vector to store employees
    int choice;

    do {
        cout << "\nJava Jolt Café Employee Management System" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. View Employees" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string empID, name, position, empType, startDate;
            double hourlyWage, workingHours, leaveDays, overtimeHours, basicSalary;

            cout << "Enter Employee ID: ";
            cin >> empID;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Position: ";
            getline(cin, position);
            cout << "Enter Employee Type (Full-Time/Part-Time): ";
            getline(cin, empType);
            cout << "Enter Start Date (DD/MM/YYYY): ";
            getline(cin, startDate);
            cout << "Enter Basic Salary: ";
            cin >> basicSalary;
            cout << "Enter Hourly Wage: ";
            cin >> hourlyWage;
            cout << "Enter Working Hours: ";
            cin >> workingHours;
            cout << "Enter Leave Days: ";
            cin >> leaveDays;
            cout << "Enter Overtime Hours: ";
            cin >> overtimeHours;

            Employee* newEmployee;
            if (empType == "Full-Time") {
                newEmployee = new Fulltime(empID, name, position, startDate, basicSalary, 
                                           hourlyWage, workingHours, leaveDays, overtimeHours);
            } else {
                newEmployee = new Parttime(empID, name, position, startDate, basicSalary, 
                                           hourlyWage, workingHours, leaveDays, overtimeHours);
            }

            employees.push_back(newEmployee);
            cout << "Employee added successfully!" << endl;

        } else if (choice == 2) {
            for (auto emp : employees) {
                emp->displayInfo();
                cout << "------------------------\n";
            }
        }
    } while (choice != 3);

    // Free allocated memory
    for (auto emp : employees) {
        delete emp;
    }

    return 0;
}
