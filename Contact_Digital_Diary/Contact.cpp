//-------------Contact Digital Diary in C++-----------------
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct ContactDetails
{
    int id;
    char name[20];
    char fatherName[20];
    char motherName[20];
    char mobile[15];
    char email[40];
    char address[40];
    char dateOfBirth[15];
    char qualification[20];
} C;

// Function declarations
void addDetails();
void showDetails();
void searchDetails();
void modifyDetails();
void deleteDetails();
bool passCheck();

int main()
{
    if (passCheck())
    {
        int choice;
        while (true)
        {
            system("cls");
            cout << "----------- Contact Digital Diary --------------------\n";
            cout << "\t1. Add Details\n";
            cout << "\t2. Show Details\n";
            cout << "\t3. Search Details\n";
            cout << "\t4. Modify Details\n";
            cout << "\t5. Delete Details\n";
            cout << "\t6. Exit\n";
            cout << "\nEnter your choice: ";
            cin >> choice;

            system("cls");
            switch (choice)
            {
            case 1:
                addDetails();
                break;
            case 2:
                showDetails();
                break;
            case 3:
                searchDetails();
                break;
            case 4:
                modifyDetails();
                break;
            case 5:
                deleteDetails();
                break;
            case 6:
                exit(0);
            default:
                cout << "Wrong choice!\n";
            }

            cout << "\n";
            system("pause");
        }
    }
    else
    {
        cout << "\nInvalid password!\n";
    }
    return 0;
}

// Function definitions
void addDetails()
{
    ofstream file("contact.data", ios::app | ios::binary);
    if (!file)
    {
        cerr << "Error opening file!\n";
        return;
    }

    cout << "\nEnter the details of the person:\n";
    cout << "ID: ";
    cin >> C.id;
    cin.ignore();
    cout << "Name: ";
    cin.getline(C.name, 20);
    cout << "Father's Name: ";
    cin.getline(C.fatherName, 20);
    cout << "Mother's Name: ";
    cin.getline(C.motherName, 20);
    cout << "Mobile: ";
    cin.getline(C.mobile, 15);
    cout << "Email: ";
    cin.getline(C.email, 40);
    cout << "Address: ";
    cin.getline(C.address, 40);
    cout << "Date of Birth: ";
    cin.getline(C.dateOfBirth, 15);
    cout << "Qualification: ";
    cin.getline(C.qualification, 20);

    file.write(reinterpret_cast<char *>(&C), sizeof(C));
    file.close();
    cout << "Details added successfully!\n";
}

void showDetails()
{
    ifstream file("contact.data", ios::in | ios::binary);
    if (!file)
    {
        cerr << "Error opening file!\n";
        return;
    }

    cout << "\nContact List:\n";
    while (file.read(reinterpret_cast<char *>(&C), sizeof(C)))
    {
        cout << "\n------------------------------------\n";
        cout << "ID: " << C.id << "\n";
        cout << "Name: " << C.name << "\n";
        cout << "Father's Name: " << C.fatherName << "\n";
        cout << "Mother's Name: " << C.motherName << "\n";
        cout << "Mobile: " << C.mobile << "\n";
        cout << "Email: " << C.email << "\n";
        cout << "Address: " << C.address << "\n";
        cout << "Date of Birth: " << C.dateOfBirth << "\n";
        cout << "Qualification: " << C.qualification << "\n";
    }

    file.close();
}

void searchDetails()
{
    ifstream file("contact.data", ios::in | ios::binary);
    if (!file)
    {
        cerr << "Error opening file!\n";
        return;
    }

    int searchId;
    bool found = false;
    cout << "\nEnter the ID to search: ";
    cin >> searchId;

    while (file.read(reinterpret_cast<char *>(&C), sizeof(C)))
    {
        if (C.id == searchId)
        {
            cout << "\nDetails Found:\n";
            cout << "ID: " << C.id << "\n";
            cout << "Name: " << C.name << "\n";
            cout << "Father's Name: " << C.fatherName << "\n";
            cout << "Mother's Name: " << C.motherName << "\n";
            cout << "Mobile: " << C.mobile << "\n";
            cout << "Email: " << C.email << "\n";
            cout << "Address: " << C.address << "\n";
            cout << "Date of Birth: " << C.dateOfBirth << "\n";
            cout << "Qualification: " << C.qualification << "\n";
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nNo record found!\n";
    }

    file.close();
}

void modifyDetails()
{
    fstream file("contact.data", ios::in | ios::out | ios::binary);
    if (!file)
    {
        cerr << "Error opening file!\n";
        return;
    }

    int searchId;
    bool found = false;
    cout << "\nEnter the ID to modify: ";
    cin >> searchId;

    while (file.read(reinterpret_cast<char *>(&C), sizeof(C)))
    {
        if (C.id == searchId)
        {
            file.seekp(-static_cast<int>(sizeof(C)), ios::cur);

            cout << "\nEnter new details:\n";
            cout << "ID: ";
            cin >> C.id;
            cin.ignore();
            cout << "Name: ";
            cin.getline(C.name, 20);
            cout << "Father's Name: ";
            cin.getline(C.fatherName, 20);
            cout << "Mother's Name: ";
            cin.getline(C.motherName, 20);
            cout << "Mobile: ";
            cin.getline(C.mobile, 15);
            cout << "Email: ";
            cin.getline(C.email, 40);
            cout << "Address: ";
            cin.getline(C.address, 40);
            cout << "Date of Birth: ";
            cin.getline(C.dateOfBirth, 15);
            cout << "Qualification: ";
            cin.getline(C.qualification, 20);

            file.write(reinterpret_cast<char *>(&C), sizeof(C));
            found = true;
            cout << "\nRecord updated successfully!\n";
            break;
        }
    }

    if (!found)
    {
        cout << "\nNo record found!\n";
    }

    file.close();
}

void deleteDetails()
{
    ifstream file("contact.data", ios::in | ios::binary);
    ofstream tempFile("temp.data", ios::out | ios::binary);

    if (!file || !tempFile)
    {
        cerr << "Error opening file!\n";
        return;
    }

    int deleteId;
    bool found = false;
    cout << "\nEnter the ID to delete: ";
    cin >> deleteId;

    while (file.read(reinterpret_cast<char *>(&C), sizeof(C)))
    {
        if (C.id != deleteId)
        {
            tempFile.write(reinterpret_cast<char *>(&C), sizeof(C));
        }
        else
        {
            found = true;
        }
    }

    if (found)
    {
        cout << "\nRecord deleted successfully!\n";
    }
    else
    {
        cout << "\nNo record found!\n";
    }

    file.close();
    tempFile.close();

    remove("contact.data");
    rename("temp.data", "contact.data");
}

bool passCheck()
{
    string password;
    cout << "\nEnter your password: ";
    cin >> password;
    return password == "contact1001";
}