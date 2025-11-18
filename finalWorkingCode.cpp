#include <iostream>
#include <string>
#include <vector>

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

class Media
{
private:
    int year_of_publication;
    int unique_id;
    int rating; // 1-5 stars
    int copies_available;
    string title;
    string artist_or_author;
    string genre;

public:
    // Base Class Constructor
    Media(string t, string a, int y, int uid, string g, int r, int ca)
        : title(t), artist_or_author(a), year_of_publication(y), unique_id(uid), genre(g), rating(r), copies_available(ca) {}

    // Virtual Destructor (Essential for proper cleanup in base/derived classes)
    virtual ~Media() = default;

    // Getters
    int get_unique_id() const { return unique_id; }
    string get_title() const { return title; }
    int get_copies_available() const { return copies_available; }

    // Setters
    void set_copies_available(int ca) { copies_available = ca; }

    // Virtual function for polymorphism
    virtual void display_details() const
    {
        cout << "--- Media Item ---" << endl;
        cout << "ID: " << unique_id << ", Title: " << title << endl;
        cout << "Creator: " << artist_or_author << ", Year: " << year_of_publication << endl;
        cout << "Genre: " << genre << ", Copies Available: " << copies_available << endl;
    }
};

class Book : public Media
{
private:
    int pages;
    string isbn; // International Standard Book Number
    string publisher;

public:
    // Derived Class Constructor
    Book(string t, string a, int y, int uid, string g, int r, int ca, string is, int nop, string pub)
        : Media(t, a, y, uid, g, r, ca), isbn(is), pages(nop), publisher(pub) {}

    // Overridden display method
    void display_details() const override
    {
        Media::display_details();
        cout << "Type: Book, ISBN: " << isbn << ", Pages: " << pages << endl;
        cout << "Publisher: " << publisher << endl;
    }
};

class Audio : public Media
{
private:
    double duration_seconds;
    string file_format;
    string album_name;

public:
    // Derived Class Constructor
    Audio(string t, string a, int y, int uid, string g, int r, int ca, double ds, string ff, string an)
        : Media(t, a, y, uid, g, r, ca), duration_seconds(ds), file_format(ff), album_name(an) {}

    // Overridden display method
    void display_details() const override
    {
        Media::display_details(); // Call base class method
        cout << "Type: Audio, Duration: " << duration_seconds << "s, Format: " << file_format << endl;
        cout << "Album: " << album_name << endl;
    }
};

class Video : public Media
{
private:
    double runtime_minutes;
    string resolution;

public:
    // Derived Class Constructor
    Video(string t, string a, int y, int uid, string g, int r, int ca,
          double rm, string res)
        : Media(t, a, y, uid, g, r, ca), runtime_minutes(rm), resolution(res) {}

    // Overridden display method
    void display_details() const override
    {
        Media::display_details();
        cout << "Type: Video, Runtime: " << runtime_minutes << endl;
        cout << "Resolution: " << resolution << endl;
    }
};

class Person
{
private:
    int person_id;
    string first_name;
    string last_name;
    string email;
    string password_hash;

public:
    // Base Class Constructor
    Person(string fn, string ln, int pid, string em, string ph)
        : first_name(fn), last_name(ln), person_id(pid), email(em), password_hash(ph) {}

    virtual ~Person() = default;

    // Getters
    int get_person_id() const { return person_id; }
    string get_full_name() const { return first_name + " " + last_name; }

    // Virtual function
    virtual void display_info() const
    {
        cout << "--- Person Info ---" << endl;
        cout << "ID: " << person_id << ", Name: " << get_full_name() << endl;
        cout << "Email: " << email << endl;
    }
};

class Client : public Person
{
private:
    vector<int> checked_out_media_ids;
    int fine_balance_cents;
    int max_checkout_limit;

public:
    // Derived Class Constructor
    Client(string fn, string ln, int pid, string em, string ph,
           int fbc = 0, int mcl = 5) // Set default values for fines and limit
        : Person(fn, ln, pid, em, ph), fine_balance_cents(fbc), max_checkout_limit(mcl)
    {
    }

    // Core Client Methods
    void checkout_media(int media_id)
    {
        if (checked_out_media_ids.size() < max_checkout_limit)
        {
            checked_out_media_ids.push_back(media_id);
            cout << "Client " << get_full_name() << " checked out media ID: " << media_id << endl;
        }
        else
        {
            cout << "Checkout failed: Limit reached." << endl;
        }
    }

    // Overridden display method
    void display_info() const override
    {
        Person::display_info();
        cout << "Role: Client, Items Checked Out: " << checked_out_media_ids.size() << endl;
        cout << "Fines: $" << (double)fine_balance_cents / 100.0 << endl;
    }
};

class Admin : public Person
{
private:
    string department;
    int security_level;

public:
    // Derived Class Constructor
    Admin(string fn, string ln, int pid, string em, string ph,
          string dept, int sl)
        : Person(fn, ln, pid, em, ph), department(dept), security_level(sl) {}

    // Admin specific method (example)
    void add_new_media(const Media &new_media)
    {
        cout << "Admin " << get_full_name() << " added new media: " << new_media.get_title() << endl;
    }

    // Overridden display method
    void display_info() const override
    {
        Person::display_info();
        cout << "Role: Admin, Department: " << department << ", Level: " << security_level << endl;
    }
};

void showInitialMenu()
{

    int userChoice;
    cout << bold underline;
    cout << "\nWhat is your role ?" << ansiReset << endl;
    cout << bold << "\n1. Client\n2. Admin\n0. Quit Program\n";
    cout << bold << "\n >> ";
    cout << ansiReset;
}

void showClientMenu()
{

    int userChoice;

    cout << "\n";
    cout << bold highlightCyan;
    cout << "Client Mode" << ansiReset << endl;

    cout << "\n";
    cout << bold underline colorCyan;
    cout << "Select your desired task :" << ansiReset << endl;
    cout << "\n";

    cout << bold;
    cout << "1. Search" << endl;
    cout << "2. Borrow" << endl;
    cout << "3. Return" << endl;
    cout << "0. Quit Mode\n"
         << endl
         << " >> ";
    cout << ansiReset;

reTypeUserChoice:
    cin >> userChoice;

    switch (userChoice)
    {
    case 0:
        cout << "\n";
        cout << bold highlightYellow;
        cout << "Client Mode terminated." << ansiReset << endl;
        break;

    default:
        cout << "\n";
        cout << bold highlightRed;
        cout << "Wrong choice. Re-type";
        cout << ansiReset;
        cout << bold colorRed << " >> ";
        cout << ansiReset;
        goto reTypeUserChoice;
    }
}

void showAdminMenu()
{
    cout << "\n";
    cout << bold highlightCyan;
    cout << "Admin Mode" << ansiReset << endl;

    cout << "\n";
    cout << "Enter password >> ";

    int userChoice;
    int userAdminPassword = 123;

    while (userChoice)
    {
        cin >> userChoice;

        if (userChoice == userAdminPassword)
        {
            cout << "\n";
            cout << bold highlightGreen;
            cout << "Access Granted." << ansiReset << endl;

            cout << "\n";
            cout << bold underline colorCyan;
            cout << "Select your desired task :" << ansiReset << endl;
            cout << "\n";

            cout << bold;
            cout << "1. Add a media" << endl;
            cout << "2. Modify a media" << endl;
            cout << "3. Delete media" << endl;
            cout << "0. Quit Mode\n"
                 << endl
                 << " >> ";
            cout << ansiReset;

        reTypeUserChoice:
            cin >> userChoice;

            switch (userChoice)
            {
            case 0:
                cout << "\n";
                cout << bold highlightYellow;
                cout << "Admin Mode terminated." << ansiReset << endl;
                break;

            default:
                cout << "\n";
                cout << bold highlightRed;
                cout << "Wrong choice. Re-type";
                cout << ansiReset;
                cout << bold colorRed << " >> ";
                cout << ansiReset;
                goto reTypeUserChoice;
            }
            break;
        }

        if (userChoice == 0)
        {
            cout << "\n";
            cout << bold highlightYellow;
            cout << "Admin Mode terminated." << ansiReset << endl;
            break;
        }

        cout << "\n";
        cout << bold highlightRed;
        cout << "Access Denied. Re-type password";
        cout << ansiReset;
        cout << bold colorRed << " >> ";
        cout << ansiReset;
    }
}

int main()
{

    cout << "\n";
    cout << bold underline colorGreen;
    cout << "Welcome to MediaForge!" << " Your personal Media library" << endl;
    cout << ansiReset;

reShowInitialMenu:
    showInitialMenu();

    int userChoice;
    cin >> userChoice;

    switch (userChoice)
    {
    case 0:
        cout << "\n";
        cout << bold highlightYellow;
        cout << "Program terminated." << ansiReset << endl;
        cout << "\n";
        return 0;
        break;

    case 1:
        showClientMenu();
        goto reShowInitialMenu;
        break;

    case 2:
        showAdminMenu();
        goto reShowInitialMenu;
        break;

    default:
        cout << "\n";
        cout << bold highlightRed;
        cout << "Wrong choice. Re-type";
        cout << ansiReset;
        cout << bold colorRed << " >> ";
        cout << ansiReset;
    }
}