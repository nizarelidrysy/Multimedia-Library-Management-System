#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cctype>

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

// Function Declarations
// Initial Menu
string initialMenu();
int initialMenu_userChoiceID();
int initialMenu_cases();
// Client Menu
// Main Menu
string clientMenu();
int clientMenu_userChoiceID();
void clientMenu_cases();
// Consulting
string clientMenu_consulting();
int clientMenu_consulting_userChoiceID();
void adminMenu_cases();
void clientMenu_consulting_cases();
void clientMenu_consultingBooks();
void clientMenu_consultingAudios();
void clientMenu_consultingAll();
void clientMenu_consultingVideos();
void clientMenu_searchingInBooks();
void clientMenu_searchingInAudios();
void clientMenu_searchingInVideos();
void clientMenu_searchingInAll();
void clientMenu_searchingFormat_cases();
void clientMode_initialMenu_cases();
// Main
int main();

// Functions
// Other
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
// Login
void loginSystem()
{
    string inputEmail, inputPass, fEmail, fPass;
    int threshold=0;
    bool emailExists = false;
    bool passwordCorrect = false;
    
    cout << "\n"
         << bold << underline << highlightCyan << "Login Portal" << ansiReset << "\n"
         << endl;
    emailExists = false;
    passwordCorrect = false;
    cout << "Email >> ";
    cin >> inputEmail;
    cout << "\n";
    retype:
    cout << "Password >> ";
    cin >> inputPass;

    ifstream userFile("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/users.txt");
    if (!userFile.is_open())
    {
        ofstream create("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/users.txt");
        create.close();
        userFile.open("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/users.txt");
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
        cout << endl
             << highlightGreen << bold << "Access Granted" << ansiReset << endl;
             clientMenu_cases();
    }
    else if (emailExists)
    {
        cout << endl
             << highlightRed << bold << "Access Denied. Wrong password x"  << threshold+1 << ansiReset << "\n"
             << endl;
             threshold++;
        if(threshold!=3){
            goto retype;
        }else{
            cout << endl
             << highlightRed << bold << "Access Denied. Too many password attempts" << ansiReset << "\n"
             << endl;
             threshold=0;
             clientMode_initialMenu_cases();
        }
        
    }
    else
    {
        cout << endl
             << highlightRed << bold << "Warning, user does not exist" << ansiReset
             << endl;
        clientMode_initialMenu_cases();
    }
}
// Signup
void registerySystem()
{
    string email, pass;
    string fEmail, fPass;
    bool emailExists = false;

    cout << "\n"
         << bold << underline << highlightCyan << "Registration Portal" << ansiReset << "\n" << endl;
    cout << "Enter New email >> ";
    cin >> email;
    cout << "\n";
    cout << "Enter New password >> ";
    cin >> pass;

    ifstream userFileRead("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/users.txt");
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
        cerr << "\n"
             << highlightRed << bold << "Error, user with this email already exists!" << ansiReset << endl;
    }
    else
    {
        ofstream userFileWrite("/Users/nizar/Desktop/Multimedia-Library-Management-System/Users/users.txt", ios::app);
        if (userFileWrite.is_open())
        {
            userFileWrite << endl
                          << email << " " << pass;
            userFileWrite.close();
            cout << "\n"
                 << highlightGreen << bold << "Successfully Registered !" << ansiReset << endl;
        }
        else
        {
            cerr << "\n"
                 << highlightRed << bold << "Error, could not access database!" << ansiReset << endl;
        }
    }
    userFileRead.close();
}
// Initial Menu
string initialMenu()
{
    string userChoice;
    cout << bold << "\nAre you accessing the system as a Library " << underline << "Client" << ansiReset bold << " or a Staff " << underline << "Administrator" << ansiReset << " ?" << ansiReset << endl;
    cout << bold << "\n >> " << ansiReset;
    cin >> userChoice;
    return userChoice;
}
int initialMenu_userChoiceID()
{
    string userChoice = initialMenu();
    int userChoiceID = -1;
    if (strcasecmp(userChoice.c_str(), "client") == 0)
        userChoiceID = 1;
    else if (strcasecmp(userChoice.c_str(), "administrator") == 0)
        userChoiceID = 2;
    else if (strcasecmp(userChoice.c_str(), "exit") == 0)
        userChoiceID = 0;
    return userChoiceID;
}
int initialMenu_cases()
{
retype:
    int userChoice = initialMenu_userChoiceID();
    switch (userChoice)
    {
    case 0:
        cout << "\n";
        cout << bold highlightYellow;
        cout << "Program Terminated" << ansiReset << endl;
        cout << "\n";
        return 0;
        break;
    case 1:
        cout << "\n";
        cout << bold highlightCyan;
        cout << "Client Mode Entered" << ansiReset << endl;
        clientMode_initialMenu_cases();
        goto retype;
        break;
    case 2:
        cout << "\n";
        cout << bold highlightCyan;
        cout << "Admin Mode Entered" << ansiReset << endl;
        adminMenu_cases();
        goto retype;
        break;
    default:
        cout << "\n";
        cout << bold highlightRed;
        cout << "Wrong choice. Re-type";
        cout << ansiReset << "\n";
        goto retype;
    }
}
// Client Menu
// Initial Menu
string clientMode_initialMenu()
{
    string userChoice;
    cout << "\n";
    cout << bold underline colorCyan;
    cout << "Select your desired task :" << ansiReset << endl;
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
        cout << "\n";
        cout << bold highlightYellow;
        cout << "Client Mode Terminated" << ansiReset << endl;
        break;
    case 1:
        cout << "\n";
        cout << bold highlightCyan;
        cout << "Client Mode Sign-in Entered" << ansiReset << endl;
        loginSystem();
        break;
    case 2:
        cout << "\n";
        cout << bold highlightCyan;
        cout << "Client Mode Sign-up Entered" << ansiReset << endl;
        registerySystem();
        goto retype;
        break;
    default:
        cout << "\n";
        cout << bold highlightRed;
        cout << "Wrong choice. Re-type";
        cout << ansiReset << "\n";
        goto retype;
    }
}
// Main Menu
string clientMenu(){
    string userChoice;
    cout << "\n";
    cout << bold underline colorCyan;
    cout << "Select your desired task :" << ansiReset << endl;
    cout << "\n";
    cout << bold;
    cout << "1. Consult Library" << endl;
    cout << "2. Search Media" << endl;
    cout << "3. Return Media" << endl;
    cout << "4. Basket Status" << endl;
    cout << "0. Exit\n" << endl << " >> ";
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
        cout << "\n"
             << bold << highlightYellow << "Client Mode Terminated" << ansiReset << endl;
             clientMode_initialMenu_cases();
        break;
    case 1:
        cout << "\n"
             << bold << highlightCyan << "Consulting Mode Entered" << ansiReset << endl;
        clientMenu_consulting_cases();
        goto retype;
        break;
    case 2:
        cout << "\n"
             << bold << highlightCyan << "Searching Mode Entered" << ansiReset << endl;
        clientMenu_searchingFormat_cases();
        goto retype;
        break;
    default:
        cout << "\n";
        cout << bold highlightRed;
        cout << "Wrong choice. Re-type";
        cout << ansiReset << "\n";
        goto retype;
    }
}
// Consulting
string clientMenu_consulting()
{
    string userChoice;
    cout << "\n";
    cout << bold underline colorCyan;
    cout << "Select your media format :" << ansiReset << endl;
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
        cout << "\n"
             << bold << highlightYellow << "Consulting Mode Terminated" << ansiReset << endl;
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
        cout << bold highlightRed;
        cout << "Wrong choice. Re-type";
        cout << ansiReset << "\n";
        goto retype;
    }
}
// Books
void clientMenu_consultingBooks()
{
    ifstream media_books("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/books/media_books.txt");
    if (!media_books.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent !" << ansiReset << endl;
    }
    else
    {
        cout << "\n"
             << bold << highlightYellow << "Consulting Books Mode Entered" << ansiReset << endl;
        cout << "\n";
        string line;
        while (getline(media_books, line))
        {
            cout << line << endl;
        }
        cout << "\n"
             << bold << highlightYellow << "Consulting Books Mode Terminated" << ansiReset << endl;
    }
    media_books.close();
}
// Videos
void clientMenu_consultingVideos()
{
    ifstream media_videos("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/videos/trailers/media_videos.txt");
    if (!media_videos.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent !" << ansiReset << endl;
    }
    else
    {

        cout << "\n"
             << bold << highlightYellow << "Consulting Videos Mode Entered" << ansiReset << endl;
        cout << "\n";
        string line;
        while (getline(media_videos, line))
        {
            cout << line << endl;
        }
        cout << "\n"
             << bold << highlightYellow << "Consulting Videos Mode Terminated" << ansiReset << endl;
    }
    media_videos.close();
}
// Audios
void clientMenu_consultingAudios()
{
    ifstream media_audios("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/audios/media_audios.txt");
    if (!media_audios.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent !" << ansiReset << endl;
    }
    else
    {
        cout << "\n"
             << bold << highlightYellow << "Consulting Audios Mode Entered" << ansiReset << endl;
        cout << "\n";
        string line;
        while (getline(media_audios, line))
        {
            cout << line << endl;
        }
        cout << "\n"
             << bold << highlightYellow << "Consulting Audios Mode Terminated" << ansiReset << endl;
    }
    media_audios.close();
}
// All
void clientMenu_consultingAll()
{
    ifstream media_books("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/books/media_books.txt");
    if (!media_books.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent !" << ansiReset << endl;
    }
    else
    {
        cout << "\n"
             << bold << highlightYellow << "Consulting Books Mode Entered" << ansiReset << endl;
        cout << "\n";
        string line;
        while (getline(media_books, line))
        {
            cout << line << endl;
        }
        cout << "\n"
             << bold << highlightYellow << "Consulting Books Mode Terminated" << ansiReset << endl;
    }
    media_books.close();
    ifstream media_audios("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/audios/media_audios.txt");
    if (!media_audios.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent !" << ansiReset << endl;
    }
    else
    {
        cout << "\n"
             << bold << highlightYellow << "Consulting Audios Mode Entered" << ansiReset << endl;
        cout << "\n";
        string line;
        while (getline(media_audios, line))
        {
            cout << line << endl;
        }
        cout << "\n"
             << bold << highlightYellow << "Consulting Audios Mode Terminated" << ansiReset << endl;
    }
    media_audios.close();
    ifstream media_videos("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/videos/trailers/media_videos.txt");
    if (!media_videos.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent !" << ansiReset << endl;
    }
    else
    {

        cout << "\n"
             << bold << highlightYellow << "Consulting Videos Mode Entered" << ansiReset << endl;
        cout << "\n";
        string line;
        while (getline(media_videos, line))
        {
            cout << line << endl;
        }
        cout << "\n"
             << bold << highlightYellow << "Consulting Videos Mode Terminated" << ansiReset << endl;
    }
    media_videos.close();
}
// Searching
string clientMenu_searchingFormat()
{
    string userChoice;
    cout << "\n";
    cout << bold underline colorCyan;
    cout << "Select your media format :" << ansiReset << endl;
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
        cout << "\n"
             << bold << highlightYellow << "Searching Mode Terminated" << ansiReset << endl;
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
        cout << bold highlightRed;
        cout << "Wrong choice. Re-type";
        cout << ansiReset << "\n";
        goto retype;
    }
}
// Books
void clientMenu_searchingInBooks()
{
    string userChoice;
    cout << "\n";
    cout << bold;
    cout << "Please specify your media name >> " << ansiReset;
    cin.ignore();
    getline(cin, userChoice);
    bool found = false;
    string line;
    ifstream media_books("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/books/media_books.txt");
    if (!media_books.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent !" << ansiReset << endl;
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
        cout << "\n"
             << highlightGreen << bold << userChoice << " is available !" << ansiReset << endl;
    }
    else
    {
        cout << "\n"
             << highlightRed << bold << userChoice << " is not available !" << ansiReset << endl;
    }
    media_books.close();
}
// Audios
void clientMenu_searchingInAudios()
{
    string userChoice;
    cout << "\n";
    cout << bold;
    cout << "Please specify your media name >> " << ansiReset;
    cin.ignore();
    getline(cin, userChoice);
    bool found = false;
    string line;
    ifstream media_audios("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/audios/media_audios.txt");
    if (!media_audios.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent !" << ansiReset << endl;
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
        cout << "\n"
             << highlightGreen << bold << userChoice << " is available !" << ansiReset << endl;
    }
    else
    {
        cout << "\n"
             << highlightRed << bold << userChoice << " is not available !" << ansiReset << endl;
    }
    media_audios.close();
}
// Videos
void clientMenu_searchingInVideos()
{
    string userChoice;
    cout << "\n";
    cout << bold;
    cout << "Please specify your media name >> " << ansiReset;
    cin.ignore();
    getline(cin, userChoice);
    bool found = false;
    string line;
    ifstream media_videos("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/videos/trailers/media_videos.txt");
    if (!media_videos.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent !" << ansiReset << endl;
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
        cout << "\n"
             << highlightGreen << bold << userChoice << " is available !" << ansiReset << endl;
    }
    else
    {
        cout << "\n"
             << highlightRed << bold << userChoice << " is not available !" << ansiReset << endl;
    }
    media_videos.close();
}
// All
void clientMenu_searchingInAll()
{
    string userChoice;
    cout << "\n";
    cout << bold;
    cout << "Please specify your media name >> " << ansiReset;
    cin.ignore();
    getline(cin, userChoice);
    bool found = false;
    string line;
    ifstream media_books("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/books/media_books.txt");
    if (!media_books.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent !" << ansiReset << endl;
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
        cout << "\n"
             << highlightGreen << bold << userChoice << " is available in books !" << ansiReset << endl;
    }
    else
    {
        cout << "\n"
             << highlightRed << bold << userChoice << " is not available in books !" << ansiReset << endl;
    }
    media_books.close();
    found = false;
    ifstream media_audios("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/audios/media_audios.txt");
    if (!media_audios.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent !" << ansiReset << endl;
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
        cout << "\n"
             << highlightGreen << bold << userChoice << " is available in audios !" << ansiReset << endl;
    }
    else
    {
        cout << "\n"
             << highlightRed << bold << userChoice << " is not available in audios !" << ansiReset << endl;
    }
    media_audios.close();
    found = false;
    ifstream media_videos("/Users/nizar/Desktop/Multimedia-Library-Management-System/Media/videos/trailers/media_videos.txt");
    if (!media_videos.is_open())
    {
        cout << "\n";
        cerr << bold highlightRed << "File could not be opened / inexistent !" << ansiReset << endl;
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
        cout << "\n"
             << highlightGreen << bold << userChoice << " is available in videos !" << ansiReset << endl;
    }
    else
    {
        cout << "\n"
             << highlightRed << bold << userChoice << " is not available in videos !" << ansiReset << endl;
    }
    media_videos.close();
}
// Admin Menu
string adminMenu()
{
    string userChoice;
    cout << "\n";
    cout << bold underline colorCyan;
    cout << "Select your desired task :" << ansiReset << endl;
    cout << "\n";
    cout << bold;
    cout << "1. Delete Users" << endl;
    cout << "2. Add Media" << endl;
    cout << "3. Client Mode" << endl;
    cout << "4. Basket Status" << endl;
    cout << "0. Exit\n"
         << endl
         << " >> ";
    cout << ansiReset;
    cin >> userChoice;
    return userChoice;
}
int adminMenu_userChoiceID()
{
    string userChoice = adminMenu();
    int userChoiceID = -1;
    if (strcasecmp(userChoice.c_str(), "delete") == 0)
        userChoiceID = 1;
    else if (strcasecmp(userChoice.c_str(), "add") == 0)
        userChoiceID = 2;
    else if (strcasecmp(userChoice.c_str(), "client") == 0)
        userChoiceID = 3;
    else if (strcasecmp(userChoice.c_str(), "basket") == 0)
        userChoiceID = 4;
    else if (strcasecmp(userChoice.c_str(), "exit") == 0)
        userChoiceID = 0;
    return userChoiceID;
}
void adminMenu_cases()
{
retype:
    int userCaseID = adminMenu_userChoiceID();
    switch (userCaseID)
    {
    case 0:
        cout << "\n"
             << bold << highlightYellow << "Admin Mode Terminated" << ansiReset << endl;
        break;
    case 1:
        cout << "\n"
             << bold << highlightCyan << "Consulting Mode Entered" << ansiReset << endl;
        clientMenu_consulting_cases();
        goto retype;
        break;
    case 2:
        cout << "\n"
             << bold << highlightCyan << "Searching Mode Entered" << ansiReset << endl;
        clientMenu_searchingFormat_cases();
        goto retype;
        break;
    default:
        cout << "\n";
        cout << bold highlightRed;
        cout << "Wrong choice. Re-type";
        cout << ansiReset << "\n";
        goto retype;
    }
}
// Main
int main()
{
    cout << "\n";
    cout << bold underline colorGreen;
    cout << "Welcome to MediaForge !" << " Your personal Media library" << endl;
    cout << ansiReset;
    initialMenu_cases();
    return 0;
}