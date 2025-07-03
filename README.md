# Hospital-Patient-and-Pharmacy-Management-System 
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

// ===== Color Helper Function =====
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Max sizes
const int MAX_PATIENTS = 100;
const int MAX_MEDICINES = 100;
const int MAX_APPOINTMENTS = 100;
const int MAX_SALES = 100;

// File names
const string PATIENT_FILE = "patients.txt";
const string MEDICINE_FILE = "medicines.txt";
const string APPOINTMENT_FILE = "appointments.txt";
const string SALE_FILE = "sales.txt";

// Structs
struct Patient {
    string id;
    string name;
    int age;
    string issue;
    float fee;
};

struct Medicine {
    string name;
    float price;
    string expiryDate;
    int stock;
};

struct Appointment {
    string patientId;
    string doctorName;
    string date;
};

struct MedicineSale {
    string patientId;
    string medicineName;
    int quantity;
    string date;
};

// Global Arrays
Patient patients[MAX_PATIENTS];
Medicine medicines[MAX_MEDICINES];
Appointment appointments[MAX_APPOINTMENTS];
MedicineSale sales[MAX_SALES];

// Global Counters
int patientCount = 0;
int medicineCount = 0;
int appointmentCount = 0;
int saleCount = 0;

// Function Prototypes
bool idExists(string filename, string searchID);
void loadPatients();
void savePatients();
void loadMedicines();
void saveMedicines();
void loadAppointments();
void saveAppointments();
void loadSales();
void saveSales();
void adminMenu();
void receptionistMenu();
void addPatient();
void viewAllPatients();
void sortPatientsByAge();
void sortPatientsByFee();
void updatePatient();
void deletePatient();
void addMedicine();
void viewMedicines();
void sortMedicinesByPrice();
void sortMedicinesByExpiry();
void updateMedicine();
void deleteMedicine();
void searchPatient();
void viewMedicineSalesHistory();
void bookAppointment();
void recommendDepartment();
void viewAppointmentHistory();
void sellMedicine();
void viewPatientHistory();

bool idExists(string filename, string searchID) {
    ifstream file(filename);
    if (!file) return false;

    string line;
    while (getline(file, line)) {
        string idInFile = line.substr(0, line.find(','));
        if (idInFile == searchID) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void loadPatients() {
    ifstream file(PATIENT_FILE);
    if (!file) return;

    string line;
    patientCount = 0;
    while (getline(file, line) && patientCount < MAX_PATIENTS) {
        stringstream ss(line);
        string temp;
        getline(ss, patients[patientCount].id, ',');
        getline(ss, patients[patientCount].name, ',');
        getline(ss, temp, ',');
        patients[patientCount].age = stoi(temp);
        getline(ss, patients[patientCount].issue, ',');
        getline(ss, temp);
        patients[patientCount].fee = stof(temp);
        patientCount++;
    }
    file.close();
}

void savePatients() {
    ofstream file(PATIENT_FILE);
    for (int i = 0; i < patientCount; i++) {
        file << patients[i].id << "," 
             << patients[i].name << "," 
             << patients[i].age << "," 
             << patients[i].issue << "," 
             << patients[i].fee << "\n";
    }
    file.close();
}

void loadMedicines() {
    ifstream file(MEDICINE_FILE);
    if (!file) return;

    string line;
    medicineCount = 0;
    while (getline(file, line) && medicineCount < MAX_MEDICINES) {
        stringstream ss(line);
        string temp;
        getline(ss, medicines[medicineCount].name, ',');
        getline(ss, temp, ',');
        medicines[medicineCount].price = stof(temp);
        getline(ss, medicines[medicineCount].expiryDate, ',');
        getline(ss, temp);
        medicines[medicineCount].stock = stoi(temp);
        medicineCount++;
    }
    file.close();
}

void saveMedicines() {
    ofstream file(MEDICINE_FILE);
    for (int i = 0; i < medicineCount; i++) {
        file << medicines[i].name << "," 
             << medicines[i].price << "," 
             << medicines[i].expiryDate << "," 
             << medicines[i].stock << "\n";
    }
    file.close();
}

void loadAppointments() {
    ifstream file(APPOINTMENT_FILE);
    if (!file) return;

    string line;
    appointmentCount = 0;
    while (getline(file, line) && appointmentCount < MAX_APPOINTMENTS) {
        stringstream ss(line);
        getline(ss, appointments[appointmentCount].patientId, ',');
        getline(ss, appointments[appointmentCount].doctorName, ',');
        getline(ss, appointments[appointmentCount].date);
        appointmentCount++;
    }
    file.close();
}

void saveAppointments() {
    ofstream file(APPOINTMENT_FILE);
    for (int i = 0; i < appointmentCount; i++) {
        file << appointments[i].patientId << "," 
             << appointments[i].doctorName << "," 
             << appointments[i].date << "\n";
    }
    file.close();
}

void loadSales() {
    ifstream file(SALE_FILE);
    if (!file) return;

    string line;
    saleCount = 0;
    while (getline(file, line) && saleCount < MAX_SALES) {
        stringstream ss(line);
        string temp;
        getline(ss, sales[saleCount].patientId, ',');
        getline(ss, sales[saleCount].medicineName, ',');
        getline(ss, temp, ',');
        sales[saleCount].quantity = stoi(temp);
        getline(ss, sales[saleCount].date);
        saleCount++;
    }
    file.close();
}

void saveSales() {
    ofstream file(SALE_FILE);
    for (int i = 0; i < saleCount; i++) {
        file << sales[i].patientId << "," 
             << sales[i].medicineName << "," 
             << sales[i].quantity << "," 
             << sales[i].date << "\n";
    }
    file.close();
}

int main() {
    // Load data from files at startup
    loadPatients();
    loadMedicines();
    loadAppointments();
    loadSales();

    int choice;
    system("cls");

    // Colorful welcome message
    setColor(12);
    cout << "******************************************\n";
    cout << "*                                        *\n";
    cout << "*                                        *\n";
    cout << "*                                        *\n";
    cout << "*                                        *\n";
    cout << "*     WELCOME TO HOSPITAL SYSTEM         *\n";
    cout << "*                                        *\n";
    cout << "*                                        *\n";
    cout << "*                                        *\n";
    cout << "*                                        *\n";
    cout << "******************************************\n";

    setColor(14);
    cout << "\nLoading, please wait...\n";
    Sleep(2000);
    system("cls");

    do {
        setColor(11);
        cout << "\n#*#*#* Hospital Patient & Pharmacy System #*#*#*\n";
        setColor(3);
        cout << "1. Login\n";
        cout << "2. Exit\n";
        setColor(7);
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                system("cls");
                int loginChoice;
                setColor(13);
                cout << "\n#*#*#* Login to the System #*#*#*\n";
                setColor(3);
                cout << "1. Admin\n";
                cout << "2. Receptionist / Doctor\n";
                setColor(7);
                cout << "Enter choice: ";
                cin >> loginChoice;

                if (loginChoice == 1) {
                    adminMenu();
                } else if (loginChoice == 2) {
                    receptionistMenu();
                } else {
                    setColor(12);
                    cout << "Invalid choice.\n";
                    setColor(7);
                }
                break;
            }
            case 2:
                savePatients();
                saveMedicines();
                saveAppointments();
                saveSales();
                setColor(10);
                cout << "Thank you for using the system.\n";
                setColor(7);
                break;
            default:
                setColor(12);
                cout << "Invalid choice. Try again.\n";
                setColor(7);
        }
    } while (choice != 2);

    return 0;
}

void adminMenu() {
    int choice;
    do {
        setColor(13);
        cout << "\n#*#*#* Admin Menu #*#*#*\n";
        setColor(9);
        cout << "1. Add New Patient\n";
        cout << "2. View All Patients (Sorted)\n";
        cout << "3. Update Patient Info\n";
        cout << "4. Delete Patient\n";
        cout << "5. Add New Medicine\n";
        cout << "6. View Medicines (Sorted)\n";
        cout << "7. Update Medicine Info\n";
        cout << "8. Delete Medicine\n";
        cout << "9. Search Patient\n";
        cout << "10. View Medicine Sales History\n";
        cout << "11. Back to Main Menu\n";
        setColor(7);
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewAllPatients(); break;
            case 3: updatePatient(); break;
            case 4: deletePatient(); break;
            case 5: addMedicine(); break;
            case 6: viewMedicines(); break;
            case 7: updateMedicine(); break;
            case 8: deleteMedicine(); break;
            case 9: searchPatient(); break;
            case 10: viewMedicineSalesHistory(); break;
            case 11:
                setColor(10);
                cout << "Returning to Main Menu...\n";
                setColor(7);
                break;
            default:
                setColor(12);
                cout << "Invalid option.\n";
                setColor(7);
        }
    } while (choice != 11);
}

void receptionistMenu() {
    int choice;
    do {
        setColor(13);
        cout << "\n#*#*#* Receptionist/Doctor Menu #*#*#*\n";
        setColor(9);
        cout << "1. Book Appointment\n";
        cout << "2. Recommend Department\n";
        cout << "3. View Appointment History\n";
        cout << "4. Sell Medicine\n";
        cout << "5. View Patient History\n";
        cout << "6. View All Patients\n";
        cout << "7. View All Medicines\n";
        cout << "8. Back to Main Menu\n";
        setColor(7);
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bookAppointment(); break;
            case 2: recommendDepartment(); break;
            case 3: viewAppointmentHistory(); break;
            case 4: sellMedicine(); break;
            case 5: viewPatientHistory(); break;
            case 6: viewAllPatients(); break;
            case 7: viewMedicines(); break;
            case 8:
                setColor(10);
                cout << "Returning to Main Menu...\n";
                setColor(7);
                break;
            default:
                setColor(12);
                cout << "Invalid option.\n";
                setColor(7);
        }
    } while (choice != 8);
}

void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        setColor(12);
        cout << "Patient limit reached!\n";
        setColor(7);
        return;
    }

    ofstream outFile(PATIENT_FILE, ios::app);
    if (!outFile) {
        setColor(12);
        cout << "Error opening file!\n";
        setColor(7);
        return;
    }

    setColor(13);
    cout << "\n#*#*#* Add New Patient #*#*#*\n";
    setColor(3);
    cout << "Enter Patient ID: ";
    setColor(7);
    cin >> patients[patientCount].id;

    if (idExists(PATIENT_FILE, patients[patientCount].id)) {
        setColor(12);
        cout << "This Patient ID already exists. Please use a different ID.\n";
        setColor(7);
        outFile.close();
        return;
    }

    cin.ignore();
    setColor(3);
    cout << "Enter Name: ";
    setColor(7);
    getline(cin, patients[patientCount].name);

    do {
        setColor(3);
        cout << "Enter Age (must be > 0): ";
        setColor(7);
        cin >> patients[patientCount].age;
        if (patients[patientCount].age <= 0) {
            setColor(12);
            cout << "Invalid age. Try again.\n";
            setColor(7);
        }
    } while (patients[patientCount].age <= 0);

    cin.ignore();
    setColor(3);
    cout << "Enter Issue: ";
    setColor(7);
    getline(cin, patients[patientCount].issue);

    setColor(3);
    cout << "Enter Consultation Fee: ";
    setColor(7);
    cin >> patients[patientCount].fee;

    outFile << patients[patientCount].id << "," 
            << patients[patientCount].name << "," 
            << patients[patientCount].age << "," 
            << patients[patientCount].issue << "," 
            << patients[patientCount].fee << "\n";
    outFile.close();

    patientCount++;
    setColor(10);
    cout << "Patient added successfully!\n";
    setColor(7);
}

void sortPatientsByAge() {
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (patients[j].age > patients[j + 1].age) {
                swap(patients[j], patients[j + 1]);
            }
        }
    }
}

void sortPatientsByFee() {
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (patients[j].fee > patients[j + 1].fee) {
                swap(patients[j], patients[j + 1]);
            }
        }
    }
}

void viewAllPatients() {
    if (patientCount == 0) {
        setColor(12);
        cout << "No patients to display.\n";
        setColor(7);
        return;
    }

    int sortChoice;
    setColor(13);
    cout << "\n#*#*#* View All Patients #*#*#*\n";
    setColor(9);
    cout << "1. Sort by Age\n";
    cout << "2. Sort by Fee\n";
    cout << "3. No Sorting\n";
    setColor(7);
    cout << "Enter choice: ";
    cin >> sortChoice;

    if (sortChoice == 1) {
        sortPatientsByAge();
    } else if (sortChoice == 2) {
        sortPatientsByFee();
    } else if (sortChoice != 3) {
        setColor(12);
        cout << "Invalid sort option. Showing unsorted list.\n";
        setColor(7);
    }

    setColor(11);
    cout << "\n#*#*#* Patient List #*#*#*\n";
    setColor(14);
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(6) << "Age"
         << setw(20) << "Issue" << setw(10) << "Fee" << "\n";
    cout << "-------------------------------------------------------------\n";
    setColor(7);

    for (int i = 0; i < patientCount; i++) {
        cout << left << setw(10) << patients[i].id << setw(20) << patients[i].name
             << setw(6) << patients[i].age << setw(20) << patients[i].issue
             << setw(10) << patients[i].fee << "\n";
    }
}

void updatePatient() {
    ifstream inFile(PATIENT_FILE);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        setColor(12);
        cout << "Error opening file.\n";
        setColor(7);
        return;
    }

    string id;
    setColor(13);
    cout << "\n#*#*#* Update Patient Info #*#*#*\n";
    setColor(3);
    cout << "Enter Patient ID to update: ";
    setColor(7);
    cin >> id;

    bool found = false;
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            found = true;
            setColor(3);
            cout << "Current Name: " << patients[i].name << "\n";
            cout << "Enter New Name: ";
            setColor(7);
            cin.ignore();
            getline(cin, patients[i].name);

            setColor(3);
            cout << "Current Age: " << patients[i].age << "\n";
            cout << "Enter New Age: ";
            setColor(7);
            cin >> patients[i].age;

            setColor(3);
            cout << "Current Issue: " << patients[i].issue << "\n";
            cout << "Enter New Issue: ";
            setColor(7);
            cin.ignore();
            getline(cin, patients[i].issue);

            setColor(3);
            cout << "Current Fee: " << patients[i].fee << "\n";
            cout << "Enter New Fee: ";
            setColor(7);
            cin >> patients[i].fee;
        }
        tempFile << patients[i].id << "," 
                 << patients[i].name << "," 
                 << patients[i].age << "," 
                 << patients[i].issue << "," 
                 << patients[i].fee << "\n";
    }

    inFile.close();
    tempFile.close();
    remove(PATIENT_FILE.c_str());
    rename("temp.txt", PATIENT_FILE.c_str());

    if (found) {
        setColor(10);
        cout << "Patient updated successfully!\n";
    } else {
        setColor(12);
        cout << "Patient with ID " << id << " not found.\n";
    }
    setColor(7);
}

void deletePatient() {
    ifstream inFile(PATIENT_FILE);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        setColor(12);
        cout << "Error opening file.\n";
        setColor(7);
        return;
    }

    string id;
    setColor(13);
    cout << "\n#*#*#* Delete Patient #*#*#*\n";
    setColor(3);
    cout << "Enter Patient ID to delete: ";
    setColor(7);
    cin >> id;

    bool found = false;
    int newCount = 0;
    Patient tempPatients[MAX_PATIENTS];
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id != id) {
            tempPatients[newCount] = patients[i];
            tempFile << patients[i].id << "," 
                     << patients[i].name << "," 
                     << patients[i].age << "," 
                     << patients[i].issue << "," 
                     << patients[i].fee << "\n";
            newCount++;
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();
    remove(PATIENT_FILE.c_str());
    rename("temp.txt", PATIENT_FILE.c_str());

    patientCount = newCount;
    for (int i = 0; i < patientCount; i++) {
        patients[i] = tempPatients[i];
    }

    if (found) {
        setColor(10);
        cout << "Patient deleted successfully!\n";
    } else {
        setColor(12);
        cout << "Patient with ID " << id << " not found.\n";
    }
    setColor(7);
}

void addMedicine() {
    if (medicineCount >= MAX_MEDICINES) {
        setColor(12);
        cout << "Medicine storage full!\n";
        setColor(7);
        return;
    }

    ofstream outFile(MEDICINE_FILE, ios::app);
    if (!outFile) {
        setColor(12);
        cout << "Error opening file!\n";
        setColor(7);
        return;
    }

    setColor(13);
    cout << "\n#*#*#* Add New Medicine #*#*#*\n";
    setColor(3);
    cout << "Enter Medicine Name: ";
    setColor(7);
    cin.ignore();
    getline(cin, medicines[medicineCount].name);

    setColor(3);
    cout << "Enter Price: ";
    setColor(7);
    cin >> medicines[medicineCount].price;

    cin.ignore();
    setColor(3);
    cout << "Enter Expiry Date (DD/MM/YYYY): ";
    setColor(7);
    getline(cin, medicines[medicineCount].expiryDate);

    setColor(3);
    cout << "Enter Stock: ";
    setColor(7);
    cin >> medicines[medicineCount].stock;

    outFile << medicines[medicineCount].name << "," 
            << medicines[medicineCount].price << "," 
            << medicines[medicineCount].expiryDate << "," 
            << medicines[medicineCount].stock << "\n";
    outFile.close();

    medicineCount++;
    setColor(10);
    cout << "Medicine added successfully!\n";
    setColor(7);
}

void sortMedicinesByPrice() {
    for (int i = 0; i < medicineCount - 1; i++) {
        for (int j = 0; j < medicineCount - i - 1; j++) {
            if (medicines[j].price > medicines[j + 1].price) {
                swap(medicines[j],?inines[j + 1]);
            }
        }
    }
}

void sortMedicinesByExpiry() {
    for (int i = 0; i < medicineCount - 1; i++) {
        for (int j = 0; j < medicineCount - i - 1; j++) {
            if (medicines[j].expiryDate > medicines[j + 1].expiryDate) {
                swap(medicines[j], medicines[j + 1]);
            }
        }
    }
}

void viewMedicines() {
    if (medicineCount == 0) {
        setColor(12);
        cout << "No medicines to display.\n";
        setColor(7);
        return;
    }

    int sortChoice;
    setColor(13);
    cout << "\n#*#*#* View All Medicines #*#*#*\n";
    setColor(9);
    cout << "1. Sort by Price\n";
    cout << "2. Sort by Expiry Date\n";
    cout << "3. No Sorting\n";
    setColor(7);
    cout << "Enter choice: ";
    cin >> sortChoice;

    if (sortChoice == 1) {
        sortMedicinesByPrice();
    } else if (sortChoice == 2) {
        sortMedicinesByExpiry();
    } else if (sortChoice != 3) {
        setColor(12);
        cout << "Invalid sort option. Showing unsorted list.\n";
        setColor(7);
    }

    setColor(11);
    cout << "\n#*#*#* Medicine List #*#*#*\n";
    setColor(14);
    cout << left << setw(20) << "Name" << setw(10) << "Price" << setw(15) << "Expiry" << setw(10) << "Stock" << "\n";
    cout << "-------------------------------------------------------------\n";
    setColor(7);

    for (int i = 0; i < medicineCount; i++) {
        cout << left << setw(20) << medicines[i].name << setw(10) << medicines[i].price
             << setw(15) << medicines[i].expiryDate << setw(10) << medicines[i].stock << "\n";
    }
}

void updateMedicine() {
    ifstream inFile(MEDICINE_FILE);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        setColor(12);
        cout << "Error opening file.\n";
        setColor(7);
        return;
    }

    string medName;
    setColor(13);
    cout << "\n#*#*#* Update Medicine #*#*#*\n";
    setColor(3);
    cout << "Enter Medicine Name to update: ";
    setColor(7);
    cin.ignore();
    getline(cin, medName);

    bool found = false;
    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].name == medName) {
            found = true;
            setColor(3);
            cout << "Current Price: " << medicines[i].price << "\n";
            cout << "Enter New Price: ";
            setColor(7);
            cin >> medicines[i].price;

            setColor(3);
            cout << "Current Expiry Date: " << medicines[i].expiryDate << "\n";
            cout << "Enter New Expiry Date (DD/MM/YYYY): ";
            setColor(7);
            cin.ignore();
            getline(cin, medicines[i].expiryDate);

            setColor(3);
            cout << "Current Stock: " << medicines[i].stock << "\n";
            cout << "Enter New Stock: ";
            setColor(7);
            cin >> medicines[i].stock;
        }
        tempFile << medicines[i].name << "," 
                 << medicines[i].price << "," 
                 << medicines[i].expiryDate << "," 
                 << medicines[i].stock << "\n";
    }

    inFile.close();
    tempFile.close();
    remove(MEDICINE_FILE.c_str());
    rename("temp.txt", MEDICINE_FILE.c_str());

    if (found) {
        setColor(10);
        cout << "Medicine updated successfully!\n";
    } else {
        setColor(12);
        cout << "Medicine not found.\n";
    }
    setColor(7);
}

void deleteMedicine() {
    ifstream inFile(MEDICINE_FILE);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        setColor(12);
        cout << "Error opening file.\n";
        setColor(7);
        return;
    }

    string medName;
    setColor(13);
    cout << "\n#*#*#* Delete Medicine #*#*#*\n";
    setColor(3);
    cout << "Enter Medicine Name to delete: ";
    setColor(7);
    cin.ignore();
    getline(cin, medName);

    bool found = false;
    int newCount = 0;
    Medicine tempMedicines[MAX_MEDICINES];
    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].name != medName) {
            tempMedicines[newCount] = medicines[i];
            tempFile << medicines[i].name << "," 
                     << medicines[i].price << "," 
                     << medicines[i].expiryDate << "," 
                     << medicines[i].stock << "\n";
            newCount++;
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();
    remove(MEDICINE_FILE.c_str());
    rename("temp.txt", MEDICINE_FILE.c_str());

    medicineCount = newCount;
    for (int i = 0; i < medicineCount; i++) {
        medicines[i] = tempMedicines[i];
    }

    if (found) {
        setColor(10);
        cout << "Medicine deleted successfully!\n";
    } else {
        setColor(12);
        cout << "Medicine not found.\n";
    }
    setColor(7);
}

void searchPatient() {
    setColor(13);
    cout << "\n#*#*#* Search Patient #*#*#*\n";
    setColor(9);
    cout << "1. Search by ID\n";
    cout << "2. Search by Name\n";
    setColor(7);
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    cin.ignore();
    bool found = false;

    if (choice == 1) {
        string id;
        setColor(3);
        cout << "Enter Patient ID: ";
        setColor(7);
        getline(cin, id);
        for (int i = 0; i < patientCount; i++) {
            if (patients[i].id == id) {
                found = true;
                setColor(11);
                cout << "\n#*#*#* Patient Found #*#*#*\n";
                setColor(14);
                cout << "ID: " << patients[i].id << "\nName: " << patients[i].name 
                     << "\nAge: " << patients[i].age << "\nIssue: " << patients[i].issue 
                     << "\nFee: " << patients[i].fee << "\n";
                setColor(7);
                break;
            }
        }
    } else if (choice == 2) {
        string name;
        setColor(3);
        cout << "Enter Patient Name: ";
        setColor(7);
        getline(cin, name);
        for (int i = 0; i < patientCount; i++) {
            if (patients[i].name == name) {
                found = true;
                setColor(11);
                cout << "\n#*#*#* Patient Found #*#*#*\n";
                setColor(14);
                cout << "ID: " << patients[i].id << "\nName: " << patients[i].name 
                     << "\nAge: " << patients[i].age << "\nIssue: " << patients[i].issue 
                     << "\nFee: " << patients[i].fee << "\n";
                setColor(7);
            }
        }
    }

    if (!found) {
        setColor(12);
        cout << "Patient not found.\n";
        setColor(7);
    }
}

void viewMedicineSalesHistory() {
    if (saleCount == 0) {
        setColor(12);
        cout << "No medicine sales recorded.\n";
        setColor(7);
        return;
    }

    setColor(11);
    cout << "\n#*#*#* Medicine Sales History #*#*#*\n";
    setColor(14);
    cout << left << setw(12) << "Patient ID" << setw(20) << "Medicine" << setw(10) << "Qty" << setw(12) << "Date" << "\n";
    cout << "-------------------------------------------------------------\n";
    setColor(7);

    for (int i = 0; i < saleCount; i++) {
        cout << left << setw(12) << sales[i].patientId << setw(20) << sales[i].medicineName
             << setw(10) << sales[i].quantity << setw(12) << sales[i].date << "\n";
    }
}

void bookAppointment() {
    if (appointmentCount >= MAX_APPOINTMENTS) {
        setColor(12);
        cout << "Appointment limit reached!\n";
        setColor(7);
        return;
    }

    ofstream outFile(APPOINTMENT_FILE, ios::app);
    if (!outFile) {
        setColor(12);
        cout << "Error opening file!\n";
        setColor(7);
        return;
    }

    setColor(13);
    cout << "\n#*#*#* Book Appointment #*#*#*\n";
    setColor(3);
    cout << "Enter Patient ID: ";
    setColor(7);
    cin >> appointments[appointmentCount].patientId;

    cin.ignore();
    setColor(3);
    cout << "Enter Doctor Name: ";
    setColor(7);
    getline(cin, appointments[appointmentCount].doctorName);

    setColor(3);
    cout << "Enter Appointment Date (DD/MM/YYYY): ";
    setColor(7);
    getline(cin, appointments[appointmentCount].date);

    outFile << appointments[appointmentCount].patientId << "," 
            << appointments[appointmentCount].doctorName << "," 
            << appointments[appointmentCount].date << "\n";
    outFile.close();

    appointmentCount++;
    setColor(10);
    cout << "Appointment booked successfully!\n";
    setColor(7);
}

void recommendDepartment() {
    string symptom;
    setColor(13);
    cout << "\n#*#*#* Department Recommendation #*#*#*\n";
    setColor(3);
    cout << "Enter patient's symptom: ";
    setColor(7);
    cin.ignore();
    getline(cin, symptom);

    setColor(14);
    if (symptom == "fever" || symptom == "cold" || symptom == "flu")
        cout << "Recommended Department: General Medicine\n";
    else if (symptom == "chest pain")
        cout << "Recommended Department: Cardiology\n";
    else if (symptom == "toothache")
        cout << "Recommended Department: Dentistry\n";
    else if (symptom == "skin rash" || symptom == "acne")
        cout << "Recommended Department: Dermatology\n";
    else if (symptom == "eye pain" || symptom == "blurry vision")
        cout << "Recommended Department: Ophthalmology\n";
    else
        cout << "Symptom not recognized. Refer to General Physician.\n";
    setColor(7);
}

void viewAppointmentHistory() {
    if (appointmentCount == 0) {
        setColor(12);
        cout << "No appointments booked yet.\n";
        setColor(7);
        return;
    }

    setColor(11);
    cout << "\n#*#*#* Appointment History #*#*#*\n";
    setColor(14);
    cout << left << setw(12) << "Patient ID" << setw(20) << "Doctor" << setw(12) << "Date" << "\n";
    cout << "-------------------------------------------------------------\n";
    setColor(7);

    for (int i = 0; i < appointmentCount; i++) {
        cout << left << setw(12) << appointments[i].patientId << setw(20) << appointments[i].doctorName
             << setw(12) << appointments[i].date << "\n";
    }
}

void sellMedicine() {
    if (saleCount >= MAX_SALES) {
        setColor(12);
        cout << "Cannot process more sales.\n";
        setColor(7);
        return;
    }

    ofstream outFile(SALE_FILE, ios::app);
    if (!outFile) {
        setColor(12);
        cout << "Error opening file!\n";
        setColor(7);
        return;
    }

    string medName;
    setColor(13);
    cout << "\n#*#*#* Sell Medicine #*#*#*\n";
    setColor(3);
    cout << "Enter Patient ID: ";
    setColor(7);
    cin >> sales[saleCount].patientId;

    cin.ignore();
    setColor(3);
    cout << "Enter Medicine Name: ";
    setColor(7);
    getline(cin, medName);

    setColor(3);
    cout << "Enter Quantity: ";
    setColor(7);
    int quantity;
    cin >> quantity;

    bool found = false;
    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].name == medName) {
            found = true;
            if (medicines[i].stock >= quantity) {
                medicines[i].stock -= quantity;
                saveMedicines();
                sales[saleCount].medicineName = medName;
                sales[saleCount].quantity = quantity;
                setColor(3);
                cout << "Enter Date (DD/MM/YYYY): ";
                setColor(7);
                cin.ignore();
                getline(cin, sales[saleCount].date);
                outFile << sales[saleCount].patientId << "," 
                        << sales[saleCount].medicineName << "," 
                        << sales[saleCount].quantity << "," 
                        << sales[saleCount].date << "\n";
                saleCount++;
                setColor(10);
                cout << "Medicine sold successfully!\n";
            } else {
                setColor(12);
                cout << "Insufficient stock!\n";
            }
            break;
        }
    }

    outFile.close();
    if (!found) {
        setColor(12);
        cout << "Medicine not found.\n";
    }
    setColor(7);
}

void viewPatientHistory() {
    string id;
    setColor(13);
    cout << "\n#*#*#* View Patient History #*#*#*\n";
    setColor(3);
    cout << "Enter Patient ID: ";
    setColor(7);
    cin >> id;

    bool found = false;
    setColor(11);
    cout << "\nAppointments:\n";
    setColor(14);
    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].patientId == id) {
            found = true;
            cout << "Doctor: " << appointments[i].doctorName
                 << ", Date: " << appointments[i].date << "\n";
        }
    }

    cout << "\nMedicine Purchases:\n";
    for (int i = 0; i < saleCount; i++) {
        if (sales[i].patientId == id) {
            found = true;
            cout << "Medicine: " << sales[i].medicineName
                 << ", Quantity: " << sales[i].quantity
                 << ", Date: " << sales[i].date << "\n";
        }
    }

    if (!found) {
        setColor(12);
        cout << "No history found for Patient ID " << id << ".\n";
    }
    setColor(7);
}
