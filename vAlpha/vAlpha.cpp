#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <thread>
#include <chrono>
#include <cctype>

// Golbal Definitions
// ANSI Escape Codes
#define ansiReset "\033[0m"
#define bold "\033[1m"
#define underline "\033[4m"
#define colorGold "\033[33m"
#define colorBlack "\033[30m"
#define colorRed "\033[31m"
#define colorOrange "\033[38;5;208m"
#define colorGreen "\033[32m"
#define colorYellow "\033[33m"
#define colorCyan "\033[36m"
#define colorWhite "\033[37m"
#define highlightBlack "\033[40m"
#define highlightRed "\033[41m"
#define highlightOrange "\033[48;5;208m"
#define highlightGreen "\033[42m"
#define highlightYellow "\033[43m"
#define highlightCyan "\033[46m"
#define highlightWhite "\033[47m"

using namespace std;

// Functions Declarations
// Complementary
void capitalizePhrase(string &);
string drawBox(string color, string title);
void slowPrint(string text, int speedMs);
void loadingDots(string message, int cycles);
void displaySystemArt();
// Initial Menu
string initialMenu();
int initialMenu_userChoiceID();
int initialMenu_cases();

// Client Mode Functions
// Login & Registery System
void clientLoginSystem();
void clientRegisterySystem();
// Login Portal
string clientMode_initialMenu();
int clientMode_initialMenu_userChoiceID();
void clientMode_initialMenu_cases();
// Main Menu
string clientMenu();
int clientMenu_userChoiceID();
void clientMenu_cases();
// Consulting Menu
string clientMenu_consulting();
int clientMenu_consulting_userChoiceID();
void clientMenu_consulting_cases();
// Consulting - Books
void clientMenu_consultingBooks();
// Consulting - Videos
void clientMenu_consultingVideos();
// Consulting - Audios
void clientMenu_consultingAudios();
// Consulting - All Media
void clientMenu_consultingAll();
// Searching Menu
string clientMenu_searchingFormat();
int clientMenu_searchingFormat_userChoiceID();
void clientMenu_searchingFormat_cases();
// Searching - Books
void clientMenu_searchingInBooks();
// Searching - Audios
void clientMenu_searchingInAudios();
// Searching - Videos
void clientMenu_searchingInVideos();
// Searching - All Media
void clientMenu_searchingInAll();
// Admin Functions
// Login & Registery System
void adminLoginSystem();
void adminRegisterySystem();
// Login Portal
string adminMode_initialMenu();
int adminMode_initialMenu_userChoiceID();
void adminMode_initialMenu_cases();
// Main Menu
string adminMode();
int adminMode_userChoiceID();
void adminMode_cases();
// Main
int main();

// Global Variables
bool actuallyAdmin = false;
bool insideScreen = false;

// Functions
// Complementary
void capitalizePhrase(string &phrase)
{
    for (int i = 0; i < phrase.length(); i++)
    {
        if (i == 0 || phrase[i - 1] == ' ')
        {
            phrase[i] = toupper(phrase[i]);
        }
        else
        {
            phrase[i] = tolower(phrase[i]);
        }
    }
}
string drawBox(string color, string title)
{
    int width = title.length() + 4;

    string line = "";
    for (int i = 0; i < width; i++)
    {
        line += "═";
    }

    string top = "╔" + line + "╗\n";
    string middle = "║  " + title + "  ║\n";
    string bottom = "╚" + line + "╝";
    cout << "\n";
    return string(color) + bold + top + middle + bottom + ansiReset;
}
void slowPrint(string text, int speedMs)
{
    for (size_t i = 0; i < text.length(); ++i)
    {
        if (i + 2 < text.length() && text.substr(i, 3) == "...")
        {
            loadingDots("", 3);
            i += 2;
        }
        else
        {
            cout << text[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(speedMs));
        }
    }
}
void loadingDots(string message, int cycles)
{
    cout << message << flush;
    for (int i = 0; i < cycles; ++i)
    {
        for (int dots = 1; dots <= 3; ++dots)
        {
            cout << "." << flush;
            this_thread::sleep_for(chrono::milliseconds(200));
            if (dots == 3)
            {
                cout << "\b\b\b   \b\b\b" << flush;
            }
        }
    }
    cout << "" << flush;
}
void displaySystemArt()
{
    string frame =
        "   _________________________________________________\n"
        "  | * * * * * * * * * * * * * * * * * * * * * * * * |\n"
        "  |    _________________________________________   *|\n"
        "  |   |                                         |  *|\n"
        "  |   |                                         |  *|\n"
        "  |   |                                         |  *|\n"
        "  |   |                                         |  *|\n"
        "  |   |                                         |  *|\n"
        "  |   |                                         |  *|\n"
        "  |   |                                         |  *|\n"
        "  |   |                                         |  *|\n"
        "  |   |                                         |  *|\n"
        "  |   |                                         |  *|\n"
        "  |   |_________________________________________|  *|\n"
        "  |                  "+string(bold)+"§ MEDIAFORGE §"+ansiReset +"                *|\n"
        "  \\_________________________________________________/\n"
        "          / _)                          (_ \\\n"
        " ________/ /______________________________\\ \\_________\n"
        "/                                                     /\n"
        "/    000000000000000000    .0.     0000====0x==       /\n"
        "/  ==000000000000000000==.0.     000=xxx0===xx000     /\n"
        "/_==____==========_______==_==________________________/\n";

    // Clear screen so the PC starts at the top
    system("clear");
    slowPrint(frame, 1);
    // The frame is 19 lines tall. Moving up 15 lines hits the top of the inner screen.
    cout << "\033[18A" << "\033[7C" << flush;
    slowPrint(" Initializing database...", 15);
    // We move down 1 line (\033[1B) and back to the left (\r) then right (\033[8C)
    cout << "\033[2B" << "\r" << "\033[8C" << flush;
    slowPrint(string(bold) + colorGreen + "Connection established!" + ansiReset, 15);
    cout << "\033[2B" << "\r" << "\033[8C" << flush;
    slowPrint(string(bold) + string(colorOrange) + "Identity scanning" + ansiReset + colorOrange + "...", 15);
    cout << "\033[2B" << "\r" << "\033[8C" << flush;
    slowPrint(string(bold) + string(colorOrange) + "Are you a Library Client or a", 15);
    cout << "\033[1B" << "\r" << "\033[8C" << flush;
    slowPrint(string(bold) + string(colorOrange) + "System Admin? >> ", 15);
} 
// Initial Menu
string initialMenu()
{
    string userChoice;
    cin >> userChoice;
    return userChoice;
}
int initialMenu_userChoiceID()
{
    string userChoice = initialMenu();
    int userChoiceID = -1;
    if (strcasecmp(userChoice.c_str(), "client") == 0)
        userChoiceID = 1;
    else if (strcasecmp(userChoice.c_str(), "admin") == 0)
    {
        userChoiceID = 2;
        actuallyAdmin = true;
    }
    else if (strcasecmp(userChoice.c_str(), "exit") == 0)
        userChoiceID = 0;
    return userChoiceID;
}
int initialMenu_cases()
{
    retype:
    if(!insideScreen){
        cout << "\n";
        slowPrint(string(bold) + string(colorOrange) + "Are you a Library Client or a System Admin? >> " , 15);
    }
    int userChoice = initialMenu_userChoiceID();
    switch (userChoice)
    {
    case 0:
        if(insideScreen){
            cout << "\033[9B" << "\r" << endl;
            insideScreen=false;
        }
        cout << "\n";
        slowPrint(string(bold) + colorBlack + highlightYellow + "Program Terminated" + ansiReset + "\n", 15);
        cout << "\n";
        slowPrint(string(bold) + string(colorCyan) + string(underline) + "Credits" + ansiReset + string(colorCyan) + " :" + string(ansiReset) + "\n", 15);
        slowPrint(drawBox(colorCyan, "Nizar EL IDRYSY | Hajar CHABLI | Nizar BTIRA"), 2);
        slowPrint((drawBox(colorGreen, "3IIR-G3 | EMSI-T") + string(colorGreen) + "[ ^ u ^ ]" + ansiReset), 2);
        slowPrint(drawBox(colorCyan, "MEDIAFORGE SYSTEM, vAlpha"), 2);
        cout << "\n\n";
        return 0;
        break;
    case 1:
    if(insideScreen){
        cout << "\033[9B" << "\r" << endl;
        insideScreen=false;
    }
        clientMode_initialMenu_cases();
        goto retype;
        break;
    case 2:
    if(insideScreen){
        cout << "\033[9B" << "\r" << endl;
        insideScreen=false;
    }
        adminMode_initialMenu_cases();
        goto retype;
        break;
    default:
    if(insideScreen){
        cout << "\033[9B" << "\r" << endl;
        insideScreen=false;
    }
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "Wrong choice. Re-type:" + ansiReset + "\n", 10);
        goto retype;
    }
}

// Client Mode Functions
// Login & Registery System
void clientLoginSystem()
{
    string inputEmail, inputPass, fEmail, fPass;
    int threshold = 0;
    bool emailExists = false;
    bool passwordCorrect = false;
    emailExists = false;
    passwordCorrect = false;
    cout << "\n";
    slowPrint("Email >> ", 15);
    cin >> inputEmail;
    cout << "\n";
retype:
    slowPrint("Password >> ", 15);
    cin >> inputPass;

    ifstream userFile("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/client.txt");
    if (!userFile.is_open())
    {
        ofstream create("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/client.txt");
        create.close();
        userFile.open("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/client.txt");
    }

    while (userFile >> fEmail >> fPass)
    {
        if (inputEmail == fEmail)
        {
            emailExists = true;
            if (inputPass == fPass)
            {
                passwordCorrect = true;
            }
            break;
        }
    }
    userFile.close();

    if (passwordCorrect)
    {
        cout << endl;
        slowPrint(string(highlightGreen) + bold + "Access Granted. Welcome " + inputEmail + ansiReset, 20);
        cout << endl;
        clientMenu_cases();
    }
    else if (emailExists)
    {
        cout << endl;
        slowPrint(string(highlightRed) + bold + "Wrong password x" + to_string(threshold + 1) + ansiReset, 10);
        cout << endl;
        threshold++;
        if (threshold != 3)
        {
            goto retype;
        }
        else
        {
            cout << endl;
            slowPrint(string(highlightRed) + bold + "Access Denied. Too many password attempts" + ansiReset, 10);
            cout << endl;
            threshold = 0;
            clientMode_initialMenu_cases();
        }
    }
    else
    {
        cout << endl;
        slowPrint(string(highlightRed) + bold + "Warning, user does not exist" + ansiReset, 10);
        cout << endl;
        clientMode_initialMenu_cases();
    }
}
void clientRegisterySystem()
{
    string email, pass;
    string fEmail, fPass;
    bool emailExists = false;

    cout << "\n";
    slowPrint(string(bold) + underline + highlightGreen + "Client Registration Portal" + ansiReset, 25);
    cout << endl;
    slowPrint("Enter New email >> ", 15);
    cin >> email;
    cout << "\n";
    slowPrint("Enter New password >> ", 15);
    cin >> pass;

    ifstream userFileRead("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/client.txt");
    if (userFileRead.is_open())
    {
        while (userFileRead >> fEmail >> fPass)
        {
            if (fEmail == email)
            {
                emailExists = true;
                break;
            }
        }
        userFileRead.close();
    }

    if (emailExists)
    {
        cout << "\n";
        slowPrint(string(highlightRed) + bold + "Error, user with this email already exists!" + ansiReset, 10);
        cout << endl;
    }
    else
    {
        ofstream userFileWrite("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/client.txt", ios::app);
        if (userFileWrite.is_open())
        {
            userFileWrite << endl
                          << email << " " << pass;
            userFileWrite.close();
            cout << "\n";
            slowPrint(string(highlightGreen) + bold + "Registration Successful" + ansiReset, 20);
            cout << endl;
        }
        else
        {
            cout << "\n";
            slowPrint(string(highlightRed) + bold + "Error, could not access database!" + ansiReset, 10);
            cout << endl;
        }
    }
    userFileRead.close();
}
// Login Portal
string clientMode_initialMenu()
{
    string userChoice;
    cout << "\n";
    slowPrint(string(bold) + string(colorBlack) + underline + highlightGreen + "Client Login Portal" + ansiReset, 15);
    cout << "\n";
    cout << "\n";
    cout << bold;
    cout << "1. Sign-in" << endl;
    cout << "2. Sign-up" << endl;
    cout << "0. Exit\n"
         << endl
         << " >> ";
    cout << ansiReset;
    cin >> userChoice;
    return userChoice;
}
int clientMode_initialMenu_userChoiceID()
{
    string userChoice = clientMode_initialMenu();
    int userChoiceID = -1;
    if (strcasecmp(userChoice.c_str(), "signin") == 0)
        userChoiceID = 1;
    else if (strcasecmp(userChoice.c_str(), "signup") == 0)
        userChoiceID = 2;
    else if (strcasecmp(userChoice.c_str(), "exit") == 0)
        userChoiceID = 0;
    return userChoiceID;
}
void clientMode_initialMenu_cases()
{
retype:
    int userChoice = clientMode_initialMenu_userChoiceID();
    switch (userChoice)
    {
    case 0:
        break;
    case 1:
        if (actuallyAdmin)
        {
            adminLoginSystem();
        }
        else
        {
            clientLoginSystem();
        }
        break;
    case 2:
        if (actuallyAdmin)
        {
            adminRegisterySystem();
        }
        else
        {
            clientRegisterySystem();
        }

        goto retype;
        break;
    default:
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "Wrong choice. Re-type" + ansiReset + "\n", 10);
        goto retype;
    }
}
// Main Menu
string clientMenu()
{
    string userChoice;
    cout << "\n";
    cout << bold;
    cout << "1. Consult Library" << endl;
    cout << "2. Search Media" << endl;
    cout << "3. Return Media" << endl;
    cout << "4. Basket Status" << endl;
    cout << "0. Exit\n"
         << endl
         << " >> ";
    cout << ansiReset;
    cin >> userChoice;
    return userChoice;
}
int clientMenu_userChoiceID()
{
    string userChoice = clientMenu();
    int userChoiceID = -1;
    if (strcasecmp(userChoice.c_str(), "consult") == 0)
        userChoiceID = 1;
    else if (strcasecmp(userChoice.c_str(), "search") == 0)
        userChoiceID = 2;
    else if (strcasecmp(userChoice.c_str(), "return") == 0)
        userChoiceID = 3;
    else if (strcasecmp(userChoice.c_str(), "status") == 0)
        userChoiceID = 4;
    else if (strcasecmp(userChoice.c_str(), "exit") == 0)
        userChoiceID = 0;
    return userChoiceID;
}
void clientMenu_cases()
{
retype:
    int userCaseID = clientMenu_userChoiceID();
    switch (userCaseID)
    {
    case 0:
        if (actuallyAdmin)
        {
            adminMode_initialMenu_cases();
        }
        else
        {
            clientMode_initialMenu_cases();
        }
        break;
    case 1:
        clientMenu_consulting_cases();
        goto retype;
        break;
    case 2:
        clientMenu_searchingFormat_cases();
        goto retype;
        break;
    default:
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "Wrong choice. Re-type" + ansiReset + "\n", 10);
        goto retype;
    }
}
// Consulting Menu
string clientMenu_consulting()
{
    string userChoice;
    cout << "\n";
    cout << bold;
    cout << "1. Books" << endl;
    cout << "2. Audios" << endl;
    cout << "3. Videos" << endl;
    cout << "4. All" << endl;
    cout << "0. Exit\n"
         << endl
         << " >> ";
    cout << ansiReset;
    cin >> userChoice;
    return userChoice;
}
int clientMenu_consulting_userChoiceID()
{
    string userChoice = clientMenu_consulting();
    int userChoiceID = -1;
    if (strcasecmp(userChoice.c_str(), "books") == 0)
        userChoiceID = 1;
    else if (strcasecmp(userChoice.c_str(), "audios") == 0)
        userChoiceID = 2;
    else if (strcasecmp(userChoice.c_str(), "videos") == 0)
        userChoiceID = 3;
    else if (strcasecmp(userChoice.c_str(), "all") == 0)
        userChoiceID = 4;
    else if (strcasecmp(userChoice.c_str(), "exit") == 0)
        userChoiceID = 0;
    return userChoiceID;
}
void clientMenu_consulting_cases()
{
retype:
    int userCaseID = clientMenu_consulting_userChoiceID();
    switch (userCaseID)
    {
    case 0:
        break;
    case 1:
        clientMenu_consultingBooks();
        goto retype;
        break;
    case 2:
        clientMenu_consultingAudios();
        goto retype;
        break;
    case 3:
        clientMenu_consultingVideos();
        goto retype;
        break;
    case 4:
        clientMenu_consultingAll();
        goto retype;
        break;
    default:
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "Wrong choice. Re-type" + ansiReset + "\n", 10);
        goto retype;
    }
}
// Consulting - Books
void clientMenu_consultingBooks()
{
    ifstream media_books("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/books/media_books.txt");
    if (!media_books.is_open())
    {
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "File could not be opened / inexistent !" + ansiReset, 10);
        cout << endl;
    }
    else
    {
        cout << "\n"
             << bold << highlightYellow << "Consulting Books Mode Entered" << ansiReset << endl;
        cout << "\n";
        string line;
        while (getline(media_books, line))
        {
            slowPrint(line, 5);
            cout << endl;
        }
        cout << "\n"
             << bold << highlightYellow << "Consulting Books Mode Terminated" << ansiReset << endl;
    }
    media_books.close();
}
// Consulting - Videos
void clientMenu_consultingVideos()
{
    ifstream media_videos("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/videos/trailers/media_videos.txt");
    if (!media_videos.is_open())
    {
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "File could not be opened / inexistent !" + ansiReset, 10);
        cout << endl;
    }
    else
    {

        cout << "\n"
             << bold << highlightYellow << "Consulting Videos Mode Entered" << ansiReset << endl;
        cout << "\n";
        string line;
        while (getline(media_videos, line))
        {
            slowPrint(line, 5);
            cout << endl;
        }
        cout << "\n"
             << bold << highlightYellow << "Consulting Videos Mode Terminated" << ansiReset << endl;
    }
    media_videos.close();
}
// Consulting - Audios
void clientMenu_consultingAudios()
{
    ifstream media_audios("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/audios/media_audios.txt");
    if (!media_audios.is_open())
    {
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "File could not be opened / inexistent !" + ansiReset, 10);
        cout << endl;
    }
    else
    {
        cout << "\n"
             << bold << highlightYellow << "Consulting Audios Mode Entered" << ansiReset << endl;
        cout << "\n";
        string line;
        while (getline(media_audios, line))
        {
            slowPrint(line, 5);
            cout << endl;
        }
        cout << "\n"
             << bold << highlightYellow << "Consulting Audios Mode Terminated" << ansiReset << endl;
    }
    media_audios.close();
}
// Consulting - All Media
void clientMenu_consultingAll()
{
    clientMenu_consultingBooks();
    clientMenu_consultingAudios();
    clientMenu_consultingVideos();
}
// Searching Menu
string clientMenu_searchingFormat()
{
    string userChoice;
    cout << "\n";
    cout << bold;
    cout << "1. Books" << endl;
    cout << "2. Audios" << endl;
    cout << "3. Videos" << endl;
    cout << "4. All" << endl;
    cout << "0. Exit\n"
         << endl
         << " >> ";
    cout << ansiReset;
    cin >> userChoice;
    return userChoice;
}
int clientMenu_searchingFormat_userChoiceID()
{
    string userChoice = clientMenu_searchingFormat();
    int userChoiceID = -1;
    if (strcasecmp(userChoice.c_str(), "books") == 0)
        userChoiceID = 1;
    else if (strcasecmp(userChoice.c_str(), "audios") == 0)
        userChoiceID = 2;
    else if (strcasecmp(userChoice.c_str(), "videos") == 0)
        userChoiceID = 3;
    else if (strcasecmp(userChoice.c_str(), "all") == 0)
        userChoiceID = 4;
    else if (strcasecmp(userChoice.c_str(), "exit") == 0)
        userChoiceID = 0;
    return userChoiceID;
}
void clientMenu_searchingFormat_cases()
{
retype:
    int userCaseID = clientMenu_searchingFormat_userChoiceID();
    switch (userCaseID)
    {
    case 0:
        break;
    case 1:
        clientMenu_searchingInBooks();
        goto retype;
        break;
    case 2:
        clientMenu_searchingInAudios();
        goto retype;
        break;
    case 3:
        clientMenu_searchingInVideos();
        goto retype;
        break;
    case 4:
        clientMenu_searchingInAll();
        goto retype;
        break;
    default:
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "Wrong choice. Re-type" + ansiReset + "\n", 10);
        goto retype;
    }
}
// Searching - Books
void clientMenu_searchingInBooks()
{
    string userChoice;
    cout << "\n";
    slowPrint(string(bold) + "Please specify your media name >> " + ansiReset, 15);
    cin.ignore();
    getline(cin, userChoice);
    bool found = false;
    string line;
    ifstream media_books("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/books/media_books.txt");
    if (!media_books.is_open())
    {
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "File could not be opened / inexistent !" + ansiReset, 10);
        cout << endl;
    }
    else
    {
        while (getline(media_books, line))
        {
            if (line.empty())
                continue;
            if (strcasecmp(line.c_str(), userChoice.c_str()) == 0)
            {
                found = true;
                break;
            }
        }
    }
    capitalizePhrase(userChoice);
    if (found)
    {
        cout << "\n";
        slowPrint(string(highlightGreen) + bold + userChoice + " is available" + ansiReset, 20);
        cout << endl;
    }
    else
    {
        cout << "\n";
        slowPrint(string(highlightRed) + bold + userChoice + " is not available" + ansiReset, 15);
        cout << endl;
    }
    media_books.close();
}
// Searching - Audios
void clientMenu_searchingInAudios()
{
    string userChoice;
    cout << "\n";
    slowPrint(string(bold) + "Please specify your media name >> " + ansiReset, 15);
    cin.ignore();
    getline(cin, userChoice);
    bool found = false;
    string line;
    ifstream media_audios("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/audios/media_audios.txt");
    if (!media_audios.is_open())
    {
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "File could not be opened / inexistent !" + ansiReset, 10);
        cout << endl;
    }
    else
    {
        while (getline(media_audios, line))
        {
            if (line.empty())
                continue;
            if (strcasecmp(line.c_str(), userChoice.c_str()) == 0)
            {
                found = true;
                break;
            }
        }
    }
    capitalizePhrase(userChoice);
    if (found)
    {
        cout << "\n";
        slowPrint(string(highlightGreen) + bold + userChoice + " is available" + ansiReset, 20);
        cout << endl;
    }
    else
    {
        cout << "\n";
        slowPrint(string(highlightRed) + bold + userChoice + " is not available" + ansiReset, 15);
        cout << endl;
    }
    media_audios.close();
}
// Searching - Videos
void clientMenu_searchingInVideos()
{
    string userChoice;
    cout << "\n";
    slowPrint(string(bold) + "Please specify your media name >> " + ansiReset, 15);
    cin.ignore();
    getline(cin, userChoice);
    bool found = false;
    string line;
    ifstream media_videos("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/videos/trailers/media_videos.txt");
    if (!media_videos.is_open())
    {
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "File could not be opened / inexistent !" + ansiReset, 10);
        cout << endl;
    }
    else
    {
        while (getline(media_videos, line))
        {
            if (line.empty())
                continue;
            if (strcasecmp(line.c_str(), userChoice.c_str()) == 0)
            {
                found = true;
                break;
            }
        }
    }
    capitalizePhrase(userChoice);
    if (found)
    {
        cout << "\n";
        slowPrint(string(highlightGreen) + bold + userChoice + " is available" + ansiReset, 20);
        cout << endl;
    }
    else
    {
        cout << "\n";
        slowPrint(string(highlightRed) + bold + userChoice + " is not available" + ansiReset, 15);
        cout << endl;
    }
    media_videos.close();
}
// Searching - All Media
void clientMenu_searchingInAll()
{
    string userChoice;
    cout << "\n";
    slowPrint(string(bold) + "Please specify your media name >> " + ansiReset, 15);
    cin.ignore();
    getline(cin, userChoice);
    bool found = false;
    string line;
    ifstream media_books("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/books/media_books.txt");
    if (!media_books.is_open())
    {
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "File could not be opened / inexistent !" + ansiReset, 10);
        cout << endl;
    }
    else
    {
        while (getline(media_books, line))
        {
            if (line.empty())
                continue;
            if (strcasecmp(line.c_str(), userChoice.c_str()) == 0)
            {
                found = true;
                break;
            }
        }
    }
    capitalizePhrase(userChoice);
    if (found)
    {
        cout << "\n";
        slowPrint(string(highlightGreen) + bold + userChoice + " is available in books" + ansiReset, 20);
        cout << endl;
    }
    else
    {
        cout << "\n";
        slowPrint(string(highlightRed) + bold + userChoice + " is not available books" + ansiReset, 15);
        cout << endl;
    }
    media_books.close();
    found = false;
    ifstream media_audios("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/audios/media_audios.txt");
    if (!media_audios.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent" << ansiReset << endl;
    }
    else
    {
        while (getline(media_audios, line))
        {
            if (line.empty())
                continue;
            if (strcasecmp(line.c_str(), userChoice.c_str()) == 0)
            {
                found = true;
                break;
            }
        }
    }
    if (found)
    {
        cout << "\n";
        slowPrint(string(highlightGreen) + bold + userChoice + " is available in audios" + ansiReset, 20);
        cout << endl;
    }
    else
    {
        cout << "\n";
        slowPrint(string(highlightRed) + bold + userChoice + " is not available in audios" + ansiReset, 15);
        cout << endl;
    }
    media_audios.close();
    found = false;
    ifstream media_videos("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/videos/trailers/media_videos.txt");
    if (!media_videos.is_open())
    {
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "File could not be opened / inexistent !" + ansiReset, 10);
        cout << endl;
    }
    else
    {
        while (getline(media_videos, line))
        {
            if (line.empty())
                continue;
            if (strcasecmp(line.c_str(), userChoice.c_str()) == 0)
            {
                found = true;
                break;
            }
        }
    }
    if (found)
    {
        cout << "\n";
        slowPrint(string(highlightGreen) + bold + userChoice + " is available in videos" + ansiReset, 20);
        cout << endl;
    }
    else
    {
        cout << "\n";
        slowPrint(string(highlightRed) + bold + userChoice + " is not available in videos" + ansiReset, 15);
    }
    media_videos.close();
    cout << "\n";
}

// Admin Functions
// Login & Registery System
void adminLoginSystem()
{
    string inputEmail, inputPass, fEmail, fPass;
    int threshold = 0;
    bool emailExists = false;
    bool passwordCorrect = false;
    emailExists = false;
    passwordCorrect = false;
    cout << "\n";
    slowPrint("Email >> ", 15);
    cin >> inputEmail;
    cout << "\n";
retype:
    slowPrint("Password >> ", 15);
    cin >> inputPass;

    ifstream userFile("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/admin.txt");
    if (!userFile.is_open())
    {
        ofstream create("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/admin.txt");
        create.close();
        userFile.open("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/admin.txt");
    }

    while (userFile >> fEmail >> fPass)
    {
        if (inputEmail == fEmail)
        {
            emailExists = true;
            if (inputPass == fPass)
            {
                passwordCorrect = true;
            }
            break;
        }
    }
    userFile.close();

    if (passwordCorrect)
    {
        cout << endl;
        slowPrint(string(highlightGreen) + bold + "Access Granted. Welcome " + inputEmail + ansiReset, 20);
        cout << endl;
        adminMode_cases();
    }
    else if (emailExists)
    {
        cout << endl;
        slowPrint(string(highlightRed) + bold + "Wrong password x" + to_string(threshold + 1) + ansiReset, 10);
        cout << endl;
        threshold++;
        if (threshold != 3)
        {
            goto retype;
        }
        else
        {
            actuallyAdmin = false;
            cout << endl;
            slowPrint(string(highlightRed) + bold + "Access Denied. Too many password attempts" + ansiReset, 10);
            cout << endl;
            threshold = 0;
            adminMode_initialMenu_cases();
        }
    }
    else
    {
        actuallyAdmin = false;
        cout << endl;
        slowPrint(string(highlightRed) + bold + "Warning, user does not exist" + ansiReset, 10);
        cout << endl;
        adminMode_initialMenu_cases();
    }
}
void adminRegisterySystem()
{
    string email, pass;
    string fEmail, fPass;
    bool emailExists = false;

    cout << "\n";
    slowPrint(string(bold) + underline + highlightRed + "Admin Registration Portal" + ansiReset, 25);
    cout << endl;
    slowPrint("Enter New email >> ", 15);
    cin >> email;
    cout << "\n";
    slowPrint("Enter New password >> ", 15);
    cin >> pass;

    ifstream userFileRead("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/admin.txt");
    if (userFileRead.is_open())
    {
        while (userFileRead >> fEmail >> fPass)
        {
            if (fEmail == email)
            {
                emailExists = true;
                break;
            }
        }
        userFileRead.close();
    }

    if (emailExists)
    {
        cout << "\n";
        slowPrint(string(highlightRed) + bold + "Error, user with this email already exists!" + ansiReset, 10);
        cout << endl;
    }
    else
    {
        ofstream userFileWrite("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/admin.txt", ios::app);
        if (userFileWrite.is_open())
        {
            userFileWrite << endl
                          << email << " " << pass;
            userFileWrite.close();
            cout << "\n";
            slowPrint(string(highlightGreen) + bold + "Registration Successful" + ansiReset, 20);
            cout << endl;
        }
        else
        {
            cout << "\n";
            slowPrint(string(highlightRed) + bold + "Error, could not access database!" + ansiReset, 10);
            cout << endl;
        }
    }
    userFileRead.close();
}
// Login Portal
string adminMode_initialMenu()
{
    string userChoice;
    cout << "\n";
    slowPrint(string(bold) + underline + highlightRed + "Admin Login Portal" + ansiReset, 25);
    cout << "\n"
         << endl;
    cout << bold;
    cout << "1. Sign-in" << endl;
    cout << "2. Sign-up" << endl;
    cout << "0. Exit\n"
         << endl
         << " >> ";
    cout << ansiReset;
    cin >> userChoice;
    return userChoice;
}
int adminMode_initialMenu_userChoiceID()
{
    string userChoice = adminMode_initialMenu();
    int userChoiceID = -1;
    if (strcasecmp(userChoice.c_str(), "signin") == 0)
        userChoiceID = 1;
    else if (strcasecmp(userChoice.c_str(), "signup") == 0)
        userChoiceID = 2;
    else if (strcasecmp(userChoice.c_str(), "exit") == 0)
    {
        userChoiceID = 0;
        actuallyAdmin = false;
    }
    return userChoiceID;
}
void adminMode_initialMenu_cases()
{
retype:
    int userChoice = adminMode_initialMenu_userChoiceID();
    switch (userChoice)
    {
    case 0:
        break;
    case 1:
        adminLoginSystem();
        break;
    case 2:
        adminRegisterySystem();
        goto retype;
        break;
    default:
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "Wrong choice. Re-type" + ansiReset + "\n", 10);
        goto retype;
    }
}
// Main Menu
string adminMode()
{
    string userChoice;
    cout << bold;
    cout << "\n";
    cout << "1. Manage Users" << endl;
    cout << "2. Manage Media" << endl;
    cout << "3. Generate Reports" << endl;
    cout << "4. Browse as a Client" << endl;
    cout << "0. Exit\n"
         << endl
         << " >> ";
    cout << ansiReset;
    getline(cin >> ws, userChoice);
    return userChoice;
}
int adminMode_userChoiceID()
{
    string userChoice = adminMode();
    int userChoiceID = -1;
    if (strcasecmp(userChoice.c_str(), "manage users") == 0)
        userChoiceID = 1;
    else if (strcasecmp(userChoice.c_str(), "manage media") == 0)
        userChoiceID = 2;
    else if (strcasecmp(userChoice.c_str(), "generate reports") == 0)
        userChoiceID = 3;
    else if (strcasecmp(userChoice.c_str(), "browse as a client") == 0)
        userChoiceID = 4;
    else if (strcasecmp(userChoice.c_str(), "exit") == 0)
        userChoiceID = 0;
    return userChoiceID;
}
void adminMode_cases()
{
retype:
    int userCaseID = adminMode_userChoiceID();
    switch (userCaseID)
    {
    case 0:

        break;
    case 4:
        clientMenu_cases();
        goto retype;
        break;
    default:
        cout << "\n";
        slowPrint(string(bold) + highlightRed + "Wrong choice. Re-type" + ansiReset + "\n", 10);
        goto retype;
    }
}
// Main
int main()
{
    insideScreen=true;
    displaySystemArt();
    initialMenu_cases();
    return 0;
}