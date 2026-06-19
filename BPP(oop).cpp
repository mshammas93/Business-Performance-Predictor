#include <iostream>  // For input and output operations
#include <fstream>   // For file handling (reading and writing files)
#include <string>    // For string operations
#include <map>       // For storing users and passwords in a key-value pair format
#include <iomanip>   // For formatted output
#include <limits>    // For clearing input buffer
using namespace std;

// Structure to hold business data
struct BusinessData {
    float sales[12], expenses[12], inventory[12]; // Arrays to store monthly data
    int customers[12], employees[12];             // Arrays for customer footfall and employee count
    float customerSatisfaction[12];               // Ratings from 1 to 5 for customer satisfaction
};

// Global map to store users and passwords
map<string, string> users = {{"admin", "admin123"}}; // Default admin user

// Function prototypes
void adminLogin();
void createUser();
void changePassword();
void enterData(BusinessData& data);
void saveToFile(BusinessData& data);
void loadFromFile(BusinessData& data);
void appendToFile(BusinessData& data);
void analyzePerformance(BusinessData& data);
void predictPerformance(BusinessData& data); // New function for prediction
void resetData(BusinessData& data);
void menu(BusinessData& data);

int main() {
    BusinessData data; // Create an instance of the structure to hold business data
    resetData(data);   // Initialize data to default values
    adminLogin();      // Authenticate the admin before proceeding
    menu(data);        // Display the main menu
    return 0;          // Exit the program
}

// Function to authenticate admin
void adminLogin() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.find(username) != users.end() && users[username] == password) {
        cout << "Access granted.\n";
        if (username == "admin") {
            int choice;
            cout << "1. Create User\n2. Change Password\n3. Continue\nEnter your choice: ";
            cin >> choice;
            if (choice == 1) {
                createUser();
            } else if (choice == 2) {
                changePassword();
            }
        }
    } else {
        cout << "Access denied.\n";
        exit(0);
    }
}

// Function to create a new user
void createUser() {
    string username, password;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> password;
    users[username] = password;
    cout << "User created successfully.\n";
}

// Function to change password
void changePassword() {
    string username, oldPassword, newPassword;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter old password: ";
    cin >> oldPassword;

    if (users.find(username) != users.end() && users[username] == oldPassword) {
        cout << "Enter new password: ";
        cin >> newPassword;
        users[username] = newPassword;
        cout << "Password changed successfully.\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

// Function to reset business data
void resetData(BusinessData& data) {
    for (int i = 0; i < 12; i++) {
        data.sales[i] = 0;
        data.expenses[i] = 0;
        data.customers[i] = 0;
        data.inventory[i] = 0;
        data.employees[i] = 0;
        data.customerSatisfaction[i] = 0;
    }
    cout << "All data has been reset.\n";
}

// Function to enter data for specific months
void enterData(BusinessData& data) {
    int month;
    char choice;
    cout << "\n--- Enter Monthly Data ---\n";
    do {
        cout << "Enter the month number (1 for January, 2 for February, ..., 12 for December): ";
        cin >> month;

        if (month < 1 || month > 12) {
            cout << "Invalid month. Please enter a number between 1 and 12.\n";
            continue;
        }

        cout << "Month: " << month << "\n";
        cout << "  Sales: ";
        cin >> data.sales[month - 1];
        cout << "  Expenses: ";
        cin >> data.expenses[month - 1];
        cout << "  Customer Footfall: ";
        cin >> data.customers[month - 1];
        cout << "  Inventory Level: ";
        cin >> data.inventory[month - 1];
        cout << "  Number of Employees: ";
        cin >> data.employees[month - 1];
        cout << "  Customer Satisfaction (1 to 5): ";
        cin >> data.customerSatisfaction[month - 1];

        cout << "Do you want to enter data for another month? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

// Function to save data to a file
void saveToFile(BusinessData& data) {
    string filePath;
    cout << "Enter the full path and name of the file to save (e.g., D:\\Data\\business_data.txt): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, filePath);

    ofstream outFile(filePath);
    if (!outFile) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }

    outFile << "Month Sales Expenses Customers Inventory Employees CustomerSatisfaction\n";
    for (int i = 0; i < 12; i++) {
        if (data.sales[i] != 0 || data.expenses[i] != 0 || data.customers[i] != 0 || data.inventory[i] != 0 || data.employees[i] != 0 || data.customerSatisfaction[i] != 0) {
            string monthName;
            switch (i + 1) {
                case 1: monthName = "January"; break;
                case 2: monthName = "February"; break;
                case 3: monthName = "March"; break;
                case 4: monthName = "April"; break;
                case 5: monthName = "May"; break;
                case 6: monthName = "June"; break;
                case 7: monthName = "July"; break;
                case 8: monthName = "August"; break;
                case 9: monthName = "September"; break;
                case 10: monthName = "October"; break;
                case 11: monthName = "November"; break;
                case 12: monthName = "December"; break;
            }

            outFile << monthName << " " << data.sales[i] << " " << data.expenses[i] << " " << data.customers[i] << " "
                    << data.inventory[i] << " " << data.employees[i] << " " << data.customerSatisfaction[i] << endl;
        }
    }
    outFile.close();
    cout << "Data saved to file successfully.\n";
    resetData(data); // Reset data after saving
}

// Function to load data from a file
void loadFromFile(BusinessData& data) {
    string filePath;
    cout << "Enter the full path and name of the file to load (e.g., D:\\Data\\business_data.txt): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, filePath);

    ifstream inFile(filePath);
    if (!inFile) {
        cout << "Error: Could not open file for reading.\n";
        return;
    }

    string header;
    getline(inFile, header); // Skip the header line

    string monthName;
    for (int i = 0; i < 12; i++) {
        if (inFile >> monthName >> data.sales[i] >> data.expenses[i] >> data.customers[i] 
                   >> data.inventory[i] >> data.employees[i] >> data.customerSatisfaction[i]) {
            // Successfully read data for a month
        } else {
            // If data is missing or file ends prematurely, reset remaining months
            for (int j = i; j < 12; j++) {
                data.sales[j] = 0;
                data.expenses[j] = 0;
                data.customers[j] = 0;
                data.inventory[j] = 0;
                data.employees[j] = 0;
                data.customerSatisfaction[j] = 0;
            }
            break;
        }
    }

    inFile.close();
    cout << "Data loaded from file successfully.\n";
}

// Function to append data to a file
void appendToFile(BusinessData& data) {
    string filePath;
    cout << "Enter the full path and name of the file to append to (e.g., D:\\Data\\business_data.txt): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, filePath);

    ofstream outFile(filePath, ios::app);
    if (!outFile) {
        cout << "Error: Could not open file for appending.\n";
        return;
    }

    // Check if the file is empty
    ifstream inFile(filePath);
    inFile.seekg(0, ios::end);
    if (inFile.tellg() == 0) {
        outFile << "Month Sales Expenses Customers Inventory Employees CustomerSatisfaction\n";
    }
    inFile.close();

    for (int i = 0; i < 12; i++) {
        if (data.sales[i] != 0 || data.expenses[i] != 0 || data.customers[i] != 0 || data.inventory[i] != 0 || data.employees[i] != 0 || data.customerSatisfaction[i] != 0) {
            string monthName;
            switch (i + 1) {
                case 1: monthName = "January"; break;
                case 2: monthName = "February"; break;
                case 3: monthName = "March"; break;
                case 4: monthName = "April"; break;
                case 5: monthName = "May"; break;
                case 6: monthName = "June"; break;
                case 7: monthName = "July"; break;
                case 8: monthName = "August"; break;
                case 9: monthName = "September"; break;
                case 10: monthName = "October"; break;
                case 11: monthName = "November"; break;
                case 12: monthName = "December"; break;
            }

            outFile << monthName << " " << data.sales[i] << " " << data.expenses[i] << " " << data.customers[i] << " "
                    << data.inventory[i] << " " << data.employees[i] << " " << data.customerSatisfaction[i] << endl;
        }
    }
    outFile.close();
    cout << "Data appended to file successfully.\n";
    resetData(data); // Reset data after appending
}

// Function to analyze performance
void analyzePerformance(BusinessData& data) {
    cout << "\n--- Performance Analysis ---\n";
    float totalProfit = 0;
    int lossMonths = 0;

    for (int i = 0; i < 12; i++) {
        float profit = data.sales[i] - data.expenses[i];
        totalProfit += profit;
        if (profit < 0) lossMonths++;
        cout << "Month " << i + 1 << ": Profit = " << profit << endl;
    }

    if (lossMonths >= 3) {
        cout << "Alert: Loss in 3 consecutive months!\n";
    }
    cout << "Average Profit: " << totalProfit / 12 << endl;
}

// Function to predict future performance
void predictPerformance(BusinessData& data) {
    cout << "\n--- Business Performance Prediction ---\n";

    // Variables to store total and average values
    float totalSales = 0, totalExpenses = 0, totalCustomers = 0, totalInventory = 0, totalEmployees = 0, totalSatisfaction = 0;
    int monthsWithData = 0;

    // Calculate totals and count months with data
    for (int i = 0; i < 12; i++) {
        if (data.sales[i] != 0 || data.expenses[i] != 0 || data.customers[i] != 0 || data.inventory[i] != 0 || data.employees[i] != 0 || data.customerSatisfaction[i] != 0) {
            totalSales += data.sales[i];
            totalExpenses += data.expenses[i];
            totalCustomers += data.customers[i];
            totalInventory += data.inventory[i];
            totalEmployees += data.employees[i];
            totalSatisfaction += data.customerSatisfaction[i];
            monthsWithData++;
        }
    }

    // Check if there is enough data to make predictions
    if (monthsWithData == 0) {
        cout << "Not enough data to make predictions.\n";
        return;
    }

    // Calculate averages
    float avgSales = totalSales / monthsWithData;
    float avgExpenses = totalExpenses / monthsWithData;
    float avgCustomers = totalCustomers / monthsWithData;
    float avgInventory = totalInventory / monthsWithData;
    float avgEmployees = totalEmployees / monthsWithData;
    float avgSatisfaction = totalSatisfaction / monthsWithData;

    // Predict values for the next 3 months
    cout << "\nPredicted Values for the Next 3 Months:\n";
    for (int i = 1; i <= 3; i++) {
        cout << "Month " << monthsWithData + i << ":\n";
        cout << "  Predicted Sales: " << avgSales << "\n";
        cout << "  Predicted Expenses: " << avgExpenses << "\n";
        cout << "  Predicted Customers: " << avgCustomers << "\n";
        cout << "  Predicted Inventory: " << avgInventory << "\n";
        cout << "  Predicted Employees: " << avgEmployees << "\n";
        cout << "  Predicted Customer Satisfaction: " << avgSatisfaction << "\n";
    }
}

// Function to display the menu
void menu(BusinessData& data) {
    int choice;
    do {
        cout << "\n--- Business Performance Predictor ---\n";
        cout << "1. Enter Data\n";
        cout << "2. Analyze Performance\n";
        cout << "3. Load Data from File\n";
        cout << "4. Save Data to File\n";
        cout << "5. Append Data to File\n";
        cout << "6. Reset Data\n";
        cout << "7. Predict Performance\n"; // New option for predictions
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: enterData(data); break;
            case 2: analyzePerformance(data); break;
            case 3: loadFromFile(data); break;
            case 4: saveToFile(data); break;
            case 5: appendToFile(data); break;
            case 6: resetData(data); break;
            case 7: predictPerformance(data); break; // Call the prediction function
            case 8: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);
}