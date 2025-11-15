#include<iostream>

using namespace std;

// ANSI Escape Codes
#define ansiReset "\033[0m"
#define bold "\033[1m"
#define underline "\033[4m"
#define colorBlack "\033[30m"
#define colorRed "\033[31m"
#define colorGreen "\033[32m"
#define colorYellow "\033[33m"
#define colorCyan "\033[36m"
#define colorWhite "\033[37m"
#define highlightBlack "\033[40m"
#define highlightRed "\033[41m"
#define highlightGreen "\033[42m"
#define highlightYellow "\033[43m"
#define highlightCyan "\033[46m"
#define highlightWhite "\033[47m"

void showMenu(){
    cout << "\n";
    cout << bold underline colorCyan highlightBlack;
    cout << "Select your desired task :" << ansiReset << endl;
    cout << "\n";

    cout << bold;
    cout << "1. Search" << endl;
    cout << "2. Borrow" << endl;
    cout << "3. Return" << endl;
    cout << "4. Statistics" << endl;
    cout << "5. Admin" << endl;
    cout << "0. Quit\n" << endl << " >> ";
    cout << ansiReset;
}

void showAdmin(){
    cout << "\n";
    cout << bold highlightCyan;
    cout << "Admin Mode" << ansiReset << endl;
    cout << "\n";
    cout << "Enter password (0 to quit) >> ";

    int userChoice;
    int userAdminPassword=123;

    while(userChoice){
        cin >> userChoice;

        if(userChoice==userAdminPassword){
            cout << "\n";
            cout << bold highlightGreen;
            cout << "Access Granted." << ansiReset << endl;
            break;
        }

        if(userChoice==0){
            cout << "\n";
            cout << bold highlightYellow;
            cout << "Admin Mode terminated." << ansiReset << endl;
            break;
        }

        cout << "\n";
        cout << bold highlightRed;
        cout << "Access Denied. Re-type password";
        cout << ansiReset;
        cout << bold colorRed highlightBlack << " >> ";
        cout << ansiReset;
    }
}

int main (){

    cout << "\n";
    cout << bold underline colorGreen;
    cout << "Welcome to MediaForge!" << " Your personal Media library" << endl;
    cout << ansiReset;

    reShowMenu:
    showMenu();

    reShowInput:
    int userChoice;
    cin >> userChoice;

    switch (userChoice){
        case 0 :
            cout << "\n";
            cout << bold highlightYellow;
            cout << "Program terminated." << ansiReset <<  endl;
            cout << "\n";
            return 0;
            break;

        case 5 :
            showAdmin();
            goto reShowMenu;
            break;

        default :
            cout << bold highlightRed;
            cout << "Wrong choice. Re-type";
            cout << ansiReset;
            cout << bold colorRed highlightBlack << " >> ";
            cout << ansiReset;
            goto reShowInput;
        }
}