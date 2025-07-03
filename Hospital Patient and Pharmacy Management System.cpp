// ===== Muhammad Taha 2025(S)CS-153=====
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

// ===== Color Function =====
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

// Global Arrays for Patients
string patientIds[MAX_PATIENTS];
string patientNames[MAX_PATIENTS];
int patientAges[MAX_PATIENTS];
string patientIssues[MAX_PATIENTS];
float patientFees[MAX_PATIENTS];

// Global Arrays for Medicines
string medicineNames[MAX_MEDICINES];
float medicinePrices[MAX_MEDICINES];
string medicineExpiryDates[MAX_MEDICINES];
int medicineStocks[MAX_MEDICINES];

// Global Arrays for Appointments
string appointmentPatientIds[MAX_APPOINTMENTS];
string appointmentDoctorNames[MAX_APPOINTMENTS];
string appointmentDates[MAX_APPOINTMENTS];

// Global Arrays for Sales
string salePatientIds[MAX_SALES];
string saleMedicineNames[MAX_SALES];
int saleQuantities[MAX_SALES];
string saleDates[MAX_SALES];

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
        getline(ss, patientIds[patientCount], ',');
        getline(ss, patientNames[patientCount], ',');
        getline(ss, temp, ',');
        patientAges[patientCount] = stoi(temp);
        getline(ss, patientIssues[patientCount], ',');
        getline(ss, temp);
        patientFees[patientCount] = stof(temp);
        patientCount++;
    }
    file.close();
}

void savePatients() {
    ofstream file(PATIENT_FILE);
    for (int i = 0; i < patientCount; i++) {
        file << patientIds[i] << "," 
             << patientNames[i] << "," 
             << patientAges[i] << "," 
             << patientIssues[i] << "," 
             << patientFees[i] << "\n";
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
        getline(ss, medicineNames[medicineCount], ',');
        getline(ss, temp, ',');
        medicinePrices[medicineCount] = stof(temp);
        getline(ss, medicineExpiryDates[medicineCount], ',');
        getline(ss, temp);
        medicineStocks[medicineCount] = stoi(temp);
        medicineCount++;
    }
    file.close();
}

void saveMedicines() {
    ofstream file(MEDICINE_FILE);
    for (int i = 0; i < medicineCount; i++) {
        file << medicineNames[i] << "," 
             << medicinePrices[i] << "," 
             << medicineExpiryDates[i] << "," 
             << medicineStocks[i] << "\n";
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
        getline(ss, appointmentPatientIds[appointmentCount], ',');
        getline(ss, appointmentDoctorNames[appointmentCount], ',');
        getline(ss, appointmentDates[appointmentCount]);
        appointmentCount++;
    }
    file.close();
}

void saveAppointments() {
    ofstream file(APPOINTMENT_FILE);
    for (int i = 0; i < appointmentCount; i++) {
        file << appointmentPatientIds[i] << "," 
             << appointmentDoctorNames[i] << "," 
             << appointmentDates[i] << "\n";
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
        getline(ss, salePatientIds[saleCount], ',');
        getline(ss, saleMedicineNames[saleCount], ',');
        getline(ss, temp, ',');
        saleQuantities[saleCount] = stoi(temp);
        getline(ss, saleDates[saleCount]);
        saleCount++;
    }
    file.close();
}

void saveSales() {
    ofstream file(SALE_FILE);
    for (int i = 0; i < saleCount; i++) {
        file << salePatientIds[i] << "," 
             << saleMedicineNames[i] << "," 
             << saleQuantities[i] << "," 
             << saleDates[i] << "\n";
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

    // Enhanced welcome message
    setColor(11);
    cout << "################## #######################\n";
    cout << "#                                        #\n";
    cout << "#      HOSPITAL MANAGEMENT SYSTEM        #\n";
    cout << "#                                        #\n";
    cout << "##########################################\n";
    cout << "==========================================\n";

    setColor(14);
    cout << "\nInitializing system, please wait...\n";
    Sleep(2000);
    system("cls");

    do {
        setColor(11);
        cout << "\n##########################################\n";
        cout << "#          Main Menu                     #\n";
        cout << "##########################################\n";
        setColor(10);
        cout << "1. Login\n";
        cout << "2. Exit\n";
        setColor(7);
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                system("cls");
                int loginChoice;
                setColor(11);
                cout << "\n##########################################\n";
                cout << "#          Login to the System           #\n";
                cout << "##########################################\n";
                setColor(10);
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
                setColor(15);
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
        setColor(11);
        cout << "\n##########################################\n";
        cout << "#          Admin Menu                    #\n";
        cout << "##########################################\n";
        setColor(10);
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
        cout << "\nEnter choice: ";
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
                setColor(15);
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
        setColor(11);
        cout << "\n##########################################\n";
        cout << "#          Receptionist/Doctor Menu       #\n";
        cout << "##########################################\n";
        setColor(10);
        cout << "1. Book Appointment\n";
        cout << "2. Recommend Department\n";
        cout << "3. View Appointment History\n";
        cout << "4. Sell Medicine\n";
        cout << "5. View Patient History\n";
        cout << "6. View All Patients\n";
        cout << "7. View All Medicines\n";
        cout << "8. Back to Main Menu\n";
        setColor(7);
        cout << "\nEnter your choice: ";
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
                setColor(15);
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

    setColor(11);
    cout << "\n### #######################################\n";
    cout << "#          Add New Patient               #\n";
    cout << "#########################################\n";
    setColor(14);
    cout << "Enter Patient ID: ";
    setColor(7);
    cin >> patientIds[patientCount];

    if (idExists(PATIENT_FILE, patientIds[patientCount])) {
        setColor(12);
        cout << "This Patient ID already exists. Please use a different ID.\n";
        setColor(7);
        outFile.close();
        return;
    }

    cin.ignore();
    setColor(14);
    cout << "Enter Name: ";
    setColor(7);
    getline(cin, patientNames[patientCount]);

    do {
        setColor(14);
        cout << "Enter Age (must be > 0): ";
        setColor(7);
        cin >> patientAges[patientCount];
        if (patientAges[patientCount] <= 0) {
            setColor(12);
            cout << "Invalid age. Try again.\n";
            setColor(7);
        }
    } while (patientAges[patientCount] <= 0);

    cin.ignore();
    setColor(14);
    cout << "Enter Issue: ";
    setColor(7);
    getline(cin, patientIssues[patientCount]);

    setColor(14);
    cout << "Enter Consultation Fee: ";
    setColor(7);
    cin >> patientFees[patientCount];

    outFile << patientIds[patientCount] << "," 
            << patientNames[patientCount] << "," 
            << patientAges[patientCount] << "," 
            << patientIssues[patientCount] << "," 
            << patientFees[patientCount] << "\n";
    outFile.close();

    patientCount++;
    setColor(15);
    cout << "Patient added successfully!\n";
    setColor(7);
}

void sortPatientsByAge() {
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (patientAges[j] > patientAges[j + 1]) {
                swap(patientIds[j], patientIds[j + 1]);
                swap(patientNames[j], patientNames[j + 1]);
                swap(patientAges[j], patientAges[j + 1]);
                swap(patientIssues[j], patientIssues[j + 1]);
                swap(patientFees[j], patientFees[j + 1]);
            }
        }
    }
}

void sortPatientsByFee() {
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (patientFees[j] > patientFees[j + 1]) {
                swap(patientIds[j], patientIds[j + 1]);
                swap(patientNames[j], patientNames[j + 1]);
                swap(patientAges[j], patientAges[j + 1]);
                swap(patientIssues[j], patientIssues[j + 1]);
                swap(patientFees[j], patientFees[j + 1]);
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
    setColor(11);
    cout << "\n##########################################\n";
    cout << "#          View All Patients             #\n";
    cout << "##########################################\n";
    setColor(10);
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
    cout << "\n##########################################\n";
    cout << "#          Patient List                  #\n";
    cout << "##########################################\n";
    setColor(13);
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(6) << "Age"
         << setw(20) << "Issue" << setw(10) << "Fee" << "\n";
    cout << "-------------------------------------------------------------\n";
    setColor(7);

    for (int i = 0; i < patientCount; i++) {
        cout << left << setw(10) << patientIds[i] << setw(20) << patientNames[i]
             << setw(6) << patientAges[i] << setw(20) << patientIssues[i]
             << setw(10) << patientFees[i] << "\n";
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
    setColor(11);
    cout << "\n##########################################\n";
    cout << "#          Update Patient Info           #\n";
    cout << "##########################################\n";
    setColor(14);
    cout << "Enter Patient ID to update: ";
    setColor(7);
    cin >> id;

    bool found = false;
    for (int i = 0; i < patientCount; i++) {
        if (patientIds[i] == id) {
            found = true;
            setColor(14);
            cout << "Current Name: " << patientNames[i] << "\n";
            cout << "Enter New Name: ";
            setColor(7);
            cin.ignore();
            getline(cin, patientNames[i]);

            setColor(14);
            cout << "Current Age: " << patientAges[i] << "\n";
            cout << "Enter New Age: ";
            setColor(7);
            cin >> patientAges[i];

            setColor(14);
            cout << "Current Issue: " << patientIssues[i] << "\n";
            cout << "Enter New Issue: ";
            setColor(7);
            cin.ignore();
            getline(cin, patientIssues[i]);

            setColor(14);
            cout << "Current Fee: " << patientFees[i] << "\n";
            cout << "Enter New Fee: ";
            setColor(7);
            cin >> patientFees[i];
        }
        tempFile << patientIds[i] << "," 
                 << patientNames[i] << "," 
                 << patientAges[i] << "," 
                 << patientIssues[i] << "," 
                 << patientFees[i] << "\n";
    }

    inFile.close();
    tempFile.close();
    remove(PATIENT_FILE.c_str());
    rename("temp.txt", PATIENT_FILE.c_str());

    if (found) {
        setColor(15);
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
    setColor(11);
    cout << "\n##########################################\n";
    cout << "#          Delete Patient                #\n";
    cout << "##########################################\n";
    setColor(14);
    cout << "Enter Patient ID to delete: ";
    setColor(7);
    cin >> id;

    bool found = false;
    int newCount = 0;
    string tempPatientIds[MAX_PATIENTS];
    string tempPatientNames[MAX_PATIENTS];
    int tempPatientAges[MAX_PATIENTS];
    string tempPatientIssues[MAX_PATIENTS];
    float tempPatientFees[MAX_PATIENTS];

    for (int i = 0; i < patientCount; i++) {
        if (patientIds[i] != id) {
            tempPatientIds[newCount] = patientIds[i];
            tempPatientNames[newCount] = patientNames[i];
            tempPatientAges[newCount] = patientAges[i];
            tempPatientIssues[newCount] = patientIssues[i];
            tempPatientFees[newCount] = patientFees[i];
            tempFile << patientIds[i] << "," 
                     << patientNames[i] << "," 
                     << patientAges[i] << "," 
                     << patientIssues[i] << "," 
                     << patientFees[i] << "\n";
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
        patientIds[i] = tempPatientIds[i];
        patientNames[i] = tempPatientNames[i];
        patientAges[i] = tempPatientAges[i];
        patientIssues[i] = tempPatientIssues[i];
        patientFees[i] = tempPatientFees[i];
    }

    if (found) {
        setColor(15);
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

    setColor(11);
    cout << "\n##########################################\n";
    cout << "#          Add New Medicine              #\n";
    cout << "##########################################\n";
    setColor(14);
    cout << "Enter Medicine Name: ";
    setColor(7);
    cin.ignore();
    getline(cin, medicineNames[medicineCount]);

    setColor(14);
    cout << "Enter Price: ";
    setColor(7);
    cin >> medicinePrices[medicineCount];

    cin.ignore();
    setColor(14);
    cout << "Enter Expiry Date (DD/MM/YYYY): ";
    setColor(7);
    getline(cin, medicineExpiryDates[medicineCount]);

    setColor(14);
    cout << "Enter Stock: ";
    setColor(7);
    cin >> medicineStocks[medicineCount];

    outFile << medicineNames[medicineCount] << "," 
            << medicinePrices[medicineCount] << "," 
            << medicineExpiryDates[medicineCount] << "," 
            << medicineStocks[medicineCount] << "\n";
    outFile.close();

    medicineCount++;
    setColor(15);
    cout << "Medicine added successfully!\n";
    setColor(7);
}

void sortMedicinesByPrice() {
    for (int i = 0; i < medicineCount - 1; i++) {
        for (int j = 0; j < medicineCount - i - 1; j++) {
            if (medicinePrices[j] > medicinePrices[j + 1]) {
                swap(medicineNames[j], medicineNames[j + 1]);
                swap(medicinePrices[j], medicinePrices[j + 1]);
                swap(medicineExpiryDates[j], medicineExpiryDates[j + 1]);
                swap(medicineStocks[j], medicineStocks[j + 1]);
            }
        }
    }
}

void sortMedicinesByExpiry() {
    for (int i = 0; i < medicineCount - 1; i++) {
        for (int j = 0; j < medicineCount - i - 1; j++) {
            if (medicineExpiryDates[j] > medicineExpiryDates[j + 1]) {
                swap(medicineNames[j], medicineNames[j + 1]);
                swap(medicinePrices[j], medicinePrices[j + 1]);
                swap(medicineExpiryDates[j], medicineExpiryDates[j + 1]);
                swap(medicineStocks[j], medicineStocks[j + 1]);
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
    setColor(11);
    cout << "\n##########################################\n";
    cout << "#          View All Medicines            #\n";
    cout << "##########################################\n";
    setColor(10);
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
    cout << "\n##########################################\n";
    cout << "#          Medicine List                 #\n";
    cout << "##########################################\n";
    setColor(13);
    cout << left << setw(20) << "Name" << setw(10) << "Price" << setw(15) << "Expiry" << setw(10) << "Stock" << "\n";
    cout << "-------------------------------------------------------------\n";
    setColor(7);

    for (int i = 0; i < medicineCount; i++) {
        cout << left << setw(20) << medicineNames[i] << setw(10) << medicinePrices[i]
             << setw(15) << medicineExpiryDates[i] << setw(10) << medicineStocks[i] << "\n";
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
    setColor(11);
    cout << "\n##########################################\n";
    cout << "#          Update Medicine               #\n";
    cout << "##########################################\n";
    setColor(14);
    cout << "Enter Medicine Name to update: ";
    setColor(7);
    cin.ignore();
    getline(cin, medName);

    bool found = false;
    for (int i = 0; i < medicineCount; i++) {
        if (medicineNames[i] == medName) {
            found = true;
            setColor(14);
            cout << "Current Price: " << medicinePrices[i] << "\n";
            cout << "Enter New Price: ";
            setColor(7);
            cin >> medicinePrices[i];

            setColor(14);
            cout << "Current Expiry Date: " << medicineExpiryDates[i] << "\n";
            cout << "Enter New Expiry Date (DD/MM/YYYY): ";
            setColor(7);
            cin.ignore();
            getline(cin, medicineExpiryDates[i]);

            setColor(14);
            cout << "Current Stock: " << medicineStocks[i] << "\n";
            cout << "Enter New Stock: ";
            setColor(7);
            cin >> medicineStocks[i];
        }
        tempFile << medicineNames[i] << "," 
                 << medicinePrices[i] << "," 
                 << medicineExpiryDates[i] << "," 
                 << medicineStocks[i] << "\n";
    }

    inFile.close();
    tempFile.close();
    remove(MEDICINE_FILE.c_str());
    rename("temp.txt", MEDICINE_FILE.c_str());

    if (found) {
        setColor(15);
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
    setColor(11);
    cout << "\n##########################################\n";
    cout << "#          Delete Medicine               #\n";
    cout << "##########################################\n";
    setColor(14);
    cout << "Enter Medicine Name to delete: ";
    setColor(7);
    cin.ignore();
    getline(cin, medName);

    bool found = false;
    int newCount = 0;
    string tempMedicineNames[MAX_MEDICINES];
    float tempMedicinePrices[MAX_MEDICINES];
    string tempMedicineExpiryDates[MAX_MEDICINES];
    int tempMedicineStocks[MAX_MEDICINES];

    for (int i = 0; i < medicineCount; i++) {
        if (medicineNames[i] != medName) {
            tempMedicineNames[newCount] = medicineNames[i];
            tempMedicinePrices[newCount] = medicinePrices[i];
            tempMedicineExpiryDates[newCount] = medicineExpiryDates[i];
            tempMedicineStocks[newCount] = medicineStocks[i];
            tempFile << medicineNames[i] << "," 
                     << medicinePrices[i] << "," 
                     << medicineExpiryDates[i] << "," 
                     << medicineStocks[i] << "\n";
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
        medicineNames[i] = tempMedicineNames[i];
        medicinePrices[i] = tempMedicinePrices[i];
        medicineExpiryDates[i] = tempMedicineExpiryDates[i];
        medicineStocks[i] = tempMedicineStocks[i];
    }

    if (found) {
        setColor(15);
        cout << "Medicine deleted successfully!\n";
    } else {
        setColor(12);
        cout << "Medicine not found.\n";
    }
    setColor(7);
}

void searchPatient() {
    setColor(11);
    cout << "\n##########################################\n";
    cout << "#          Search Patient                #\n";
    cout << "##########################################\n";
    setColor(10);
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
        setColor(14);
        cout << "Enter Patient ID: ";
        setColor(7);
        getline(cin, id);
        for (int i = 0; i < patientCount; i++) {
            if (patientIds[i] == id) {
                found = true;
                setColor(11);
                cout << "\n##########################################\n";
                cout << "#          Patient Found                 #\n";
                cout << "##########################################\n";
                setColor(13);
                cout << "ID: " << patientIds[i] << "\nName: " << patientNames[i] 
                     << "\nAge: " << patientAges[i] << "\nIssue: " << patientIssues[i] 
                     << "\nFee: " << patientFees[i] << "\n";
                setColor(7);
                break;
            }
        }
    } else if (choice == 2) {
        string name;
        setColor(14);
        cout << "Enter Patient Name: ";
        setColor(7);
        getline(cin, name);
        for (int i = 0; i < patientCount; i++) {
            if (patientNames[i] == name) {
                found = true;
                setColor(11);
                cout << "\n##########################################\n";
                cout << "#          Patient Found                 #\n";
                cout << "##########################################\n";
                setColor(13);
                cout << "ID: " << patientIds[i] << "\nName: " << patientNames[i] 
                     << "\nAge: " << patientAges[i] << "\nIssue: " << patientIssues[i] 
                     << "\nFee: " << patientFees[i] << "\n";
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
    cout << "\n##########################################\n";
    cout << "#          Medicine Sales History        #\n";
    cout << "##########################################\n";
    setColor(13);
    cout << left << setw(12) << "Patient ID" << setw(20) << "Medicine" << setw(10) << "Qty" << setw(12) << "Date" << "\n";
    cout << "-------------------------------------------------------------\n";
    setColor(7);

    for (int i = 0; i < saleCount; i++) {
        cout << left << setw(12) << salePatientIds[i] << setw(20) << saleMedicineNames[i]
             << setw(10) << saleQuantities[i] << setw(12) << saleDates[i] << "\n";
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

    setColor(11);
    cout << "\n##########################################\n";
    cout << "#          Book Appointment              #\n";
    cout << "##########################################\n";
    setColor(14);
    cout << "Enter Patient ID: ";
    setColor(7);
    cin >> appointmentPatientIds[appointmentCount];

    cin.ignore();
    setColor(14);
    cout << "Enter Doctor Name: ";
    setColor(7);
    getline(cin, appointmentDoctorNames[appointmentCount]);

    setColor(14);
    cout << "Enter Appointment Date (DD/MM/YYYY): ";
    setColor(7);
    getline(cin, appointmentDates[appointmentCount]);

    outFile << appointmentPatientIds[appointmentCount] << "," 
            << appointmentDoctorNames[appointmentCount] << "," 
            << appointmentDates[appointmentCount] << "\n";
    outFile.close();

    appointmentCount++;
    setColor(15);
    cout << "Appointment booked successfully!\n";
    setColor(7);
}

void recommendDepartment() {
    string symptom;
    setColor(11);
    cout << "\n##########################################\n";
    cout << "#          Department Recommendation     #\n";
    cout << "##########################################\n";
    setColor(14);
    cout << "Enter patient's symptom: ";
    setColor(7);
    cin.ignore();
    getline(cin, symptom);

    setColor(13);
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
    cout << "\n##########################################\n";
    cout << "#          Appointment History           #\n";
    cout << "##########################################\n";
    setColor(13);
    cout << left << setw(12) << "Patient ID" << setw(20) << "Doctor" << setw(12) << "Date" << "\n";
    cout << "-------------------------------------------------------------\n";
    setColor(7);

    for (int i = 0; i < appointmentCount; i++) {
        cout << left << setw(12) << appointmentPatientIds[i] << setw(20) << appointmentDoctorNames[i]
             << setw(12) << appointmentDates[i] << "\n";
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
    setColor(11);
    cout << "\n##########################################\n";
    cout << "#          Sell Medicine                 #\n";
    cout << "##########################################\n";
    setColor(14);
    cout << "Enter Patient ID: ";
    setColor(7);
    cin >> salePatientIds[saleCount];

    cin.ignore();
    setColor(14);
    cout << "Enter Medicine Name: ";
    setColor(7);
    getline(cin, medName);

    setColor(14);
    cout << "Enter Quantity: ";
    setColor(7);
    int quantity;
    cin >> quantity;

    bool found = false;
    for (int i = 0; i < medicineCount; i++) {
        if (medicineNames[i] == medName) {
            found = true;
            if (medicineStocks[i] >= quantity) {
                medicineStocks[i] -= quantity;
                saveMedicines();
                saleMedicineNames[saleCount] = medName;
                saleQuantities[saleCount] = quantity;
                setColor(14);
                cout << "Enter Date (DD/MM/YYYY): ";
                setColor(7);
                cin.ignore();
                getline(cin, saleDates[saleCount]);
                outFile << salePatientIds[saleCount] << "," 
                        << saleMedicineNames[saleCount] << "," 
                        << saleQuantities[saleCount] << "," 
                        << saleDates[saleCount] << "\n";
                saleCount++;
                setColor(15);
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
    setColor(11);
    cout << "\n##########################################\n";
    cout << "#          View Patient History          #\n";
    cout << "##########################################\n";
    setColor(14);
    cout << "Enter Patient ID: ";
    setColor(7);
    cin >> id;

    bool found = false;
    setColor(11);
    cout << "\nAppointments:\n";
    setColor(13);
    for (int i = 0; i < appointmentCount; i++) {
        if (appointmentPatientIds[i] == id) {
            found = true;
            cout << "Doctor: " << appointmentDoctorNames[i]
                 << ", Date: " << appointmentDates[i] << "\n";
        }
    }

    cout << "\nMedicine Purchases:\n";
    for (int i = 0; i < saleCount; i++) {
        if (salePatientIds[i] == id) {
            found = true;
            cout << "Medicine: " << saleMedicineNames[i]
                 << ", Quantity: " << saleQuantities[i]
                 << ", Date: " << saleDates[i] << "\n";
        }
    }

    if (!found) {
        setColor(12);
        cout << "No history found for Patient ID " << id << ".\n";
    }
    setColor(7);
}