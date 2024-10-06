#include <iostream>
#include <fstream>
#include <iomanip>
#include <thread> // For sleep functionality
#include <chrono> // For cross-platform sleep
using namespace std;

void menu(); // main menu function prototype

class ManageMenu {
protected:
    string userName; // hide admin name

public:
    ManageMenu() {
#ifdef _WIN32
        system("color 0A"); // Change terminal color on Windows
#endif
        cout << "\n\n\n\n\n\n\n\n\n\t  Enter Your Name to Continue as an Admin: ";
        cin >> userName;
        system("CLS"); // Clear screen
        menu(); // Call to main function to load after executing the constructor
    }

    ~ManageMenu() {} // Destructor
};

class Customer {
public:
    string name, gender, address;
    int age, mobileNo, menuBack;
    static int cusID;
    char all[999];

    void getDetails() {
        ofstream out("old-customers.txt", ios::app); // Open file using append mode to write customer details
        {
            cout << "\nEnter Customer ID: ";
            cin >> cusID;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Mobile Number: ";
            cin >> mobileNo;
            cout << "Address: ";
            cin >> address;
            cout << "Gender: ";
            cin >> gender;
        }
        out << "\nCustomer ID: " << cusID << "\nName: " << name << "\nAge: " << age << "\nMobile Number: " << mobileNo
            << "\nAddress: " << address << "\nGender: " << gender << endl;
        out.close();
        cout << "\nSaved \nNOTE: We save your details record for future purposes.\n" << endl;
    }

    void showDetails() { // Function to show old customer records
        ifstream in("old-customers.txt");
        {
            if (!in) {
                cout << "File Error!" << endl;
            }
            while (!(in.eof())) {
                in.getline(all, 999);
                cout << all << endl;
            }
            in.close();
        }
    }
};

int Customer::cusID;

class Cabs {
public:
    int cabChoice;
    int kilometers;
    float cabCost;
    static float lastCabCost;

    void cabDetails() {
        cout << "We collaborated with fastest, safest, and smartest cab service around the country" << endl;
        cout << "-----------ABC Cabs-----------\n" << endl;
        cout << "1. Rent a Standard Cab - Rs.15 for 1KM" << endl;
        cout << "2. Rent a Luxury Cab - Rs.25 per 1KM" << endl;

        cout << "\nEnter another key to go back or," << endl;
        cout << "\nTo calculate the cost for your journey.." << endl;
        cout << "Enter which kind of cab you need: ";
        cin >> cabChoice;
        cout << "Enter Kilometers you have to travel: ";
        cin >> kilometers;

        int hireCab;

        if (cabChoice == 1) {
            cabCost = kilometers * 15;
            cout << "\nYour tour will cost " << cabCost << " rupees for a standard cab" << endl;
            cout << "Press 1 to hire this cab or Press 2 to select another cab: ";
            cin >> hireCab;
            system("CLS");
            if (hireCab == 1) {
                lastCabCost = cabCost;
                cout << "\nYou have successfully hired a standard cab" << endl;
                cout << "Go to Menu to take the receipt" << endl;
            } else if (hireCab == 2) {
                cabDetails();
            } else {
                cout << "Invalid Input! Redirecting to Previous Menu \nPlease Wait!" << endl;
                this_thread::sleep_for(chrono::milliseconds(1100)); // Replaced Sleep with cross-platform solution
                system("CLS");
                cabDetails();
            }
        } else if (cabChoice == 2) {
            cabCost = kilometers * 25;
            cout << "\nYour tour will cost " << cabCost << " rupees for a luxury cab" << endl;
            cout << "Press 1 to hire this cab or Press 2 to select another cab: ";
            cin >> hireCab;
            system("CLS");
            if (hireCab == 1) {
                lastCabCost = cabCost;
                cout << "\nYou have successfully hired a luxury cab" << endl;
                cout << "Go to Menu to take the receipt" << endl;
            } else if (hireCab == 2) {
                cabDetails();
            } else {
                cout << "Invalid Input! Redirecting to Previous Menu \nPlease Wait!" << endl;
                this_thread::sleep_for(chrono::milliseconds(1100)); // Replaced Sleep with cross-platform solution
                system("CLS");
                cabDetails();
            }
        } else {
            cout << "Invalid Input! Redirecting to Previous Menu \nPlease Wait!" << endl;
            this_thread::sleep_for(chrono::milliseconds(1100)); // Replaced Sleep with cross-platform solution
            system("CLS");
            cabDetails();
        }
    }
};

float Cabs::lastCabCost;

class Booking {
public:
    int choiceHotel;
    int packChoice1;
    int gotoMenu;
    static float hotelCost;

    void hotels() {
        cout << "----------- Welcome to ABC Hotels -----------\n" << endl;
        cout << "We provide you the best comfort and affordable prices.\n" << endl;
        cout << "1. Standard Room - Rs.5000/night" << endl;
        cout << "2. Premium Room - Rs.10000/night" << endl;

        cout << "\nPress the number of the room you want to book: ";
        cin >> choiceHotel;

        if (choiceHotel == 1) {
            hotelCost = 5000;
            cout << "You have chosen the Standard Room." << endl;
            cout << "Go to Menu to get your receipt." << endl;
        } else if (choiceHotel == 2) {
            hotelCost = 10000;
            cout << "You have chosen the Premium Room." << endl;
            cout << "Go to Menu to get your receipt." << endl;
        } else {
            cout << "Invalid Input! Redirecting to Previous Menu \nPlease Wait!" << endl;
            this_thread::sleep_for(chrono::milliseconds(1100)); // Cross-platform sleep
            system("CLS");
            hotels();
        }
    }
};

float Booking::hotelCost;

class Charges : public Booking, public Cabs, public Customer {
public:
    void printBill() {
        ofstream outf("receipt.txt");
        {
            outf << "----------ABC Travel Agency Receipt----------" << endl;
            outf << "Customer ID: " << Customer::cusID << endl;
            outf << "Customer Name: " << Customer::name << endl;
            outf << "---------------------------------------------" << endl;
            outf << "Hotel Cost: Rs. " << fixed << setprecision(2) << Booking::hotelCost << endl;
            outf << "Travel (Cab) Cost: Rs. " << fixed << setprecision(2) << Cabs::lastCabCost << endl;
            outf << "---------------------------------------------" << endl;
            outf << "Total Charges: Rs. " << fixed << setprecision(2) << Booking::hotelCost + Cabs::lastCabCost << endl;
            outf << "---------------------------------------------" << endl;
        }
        outf.close();

        cout << "Your receipt has been printed. You can collect it from 'receipt.txt' file." << endl;
    }

    void showBill() {
        ifstream inf("receipt.txt");
        {
            if (!inf) {
                cout << "File Opening Error!" << endl;
            }
            while (!(inf.eof())) {
                inf.getline(all, 999);
                cout << all << endl;
            }
            inf.close();
        }
    }
};

void menu() {
    int mainChoice;
    int inChoice;
    int gotoMenu;
    cout << "---------- ABC Travel Agency ----------\n" << endl;
    cout << "1. Add New Customer" << endl;
    cout << "2. Booking" << endl;
    cout << "3. Cabs" << endl;
    cout << "4. Print Receipt" << endl;
    cout << "5. Exit" << endl;

    cout << "\nEnter Your Choice: ";
    cin >> mainChoice;

    ManageMenu menuObj; // To load the menu

    Customer customerObj; 
    Booking bookingObj;
    Cabs cabObj;
    Charges chargeObj;

    switch (mainChoice) {
        case 1:
            customerObj.getDetails();
            break;
        case 2:
            bookingObj.hotels();
            break;
        case 3:
            cabObj.cabDetails();
            break;
        case 4:
            chargeObj.printBill();
            chargeObj.showBill();
            break;
        case 5:
            cout << "Thank you for using our service!" << endl;
            exit(0);
        default:
            cout << "Invalid Input! Please try again." << endl;
            break;
    }
}

int main() {
    ManageMenu startObj;
    return 0;
}
