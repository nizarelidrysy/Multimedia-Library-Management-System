#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <set>
#include <thread>
#include <chrono>
#include <filesystem>
#include <functional>

using namespace std;
namespace fs = std::filesystem;

// ==========================================
// UI & ANSI Definitions
// ==========================================
#define ansiReset "\033[0m\033[40m"
#define bold "\033[1m"
#define underline "\033[4m"
#define colorGray "\033[1;30m"
#define colorBlack "\033[30m"
#define colorRed "\033[31m"
#define colorGreen "\033[32m"
#define colorYellow "\033[33m"
#define colorCyan "\033[36m"
#define colorWhite "\033[37m"
#define highlightBlue "\033[44m"
#define highlightBlueGreenBold "\033[44;38;5;82;1m"
#define highlightCyan "\033[46m" 
#define highlightBlack "\033[40m" 

class UI {
public:
    static void slowPrint(string text, int speedMs) {
        for (size_t i = 0; i < text.length(); ++i) {
            if (i + 2 < text.length() && text.substr(i, 3) == "...") {
                cout << "." << flush; this_thread::sleep_for(chrono::milliseconds(200));
                cout << "." << flush; this_thread::sleep_for(chrono::milliseconds(200));
                cout << "." << flush; this_thread::sleep_for(chrono::milliseconds(200));
                i += 2;
            } else {
                cout << text[i] << flush;
                this_thread::sleep_for(chrono::milliseconds(speedMs));
            }
        }
    }
    
    // Mimic the backup code loading dots effect
    static void loadingDots(int repeats = 3) {
         for(int k=0; k<repeats; ++k) {
             cout << "." << flush; 
             this_thread::sleep_for(chrono::milliseconds(300));
             cout << "." << flush; 
             this_thread::sleep_for(chrono::milliseconds(300));
             cout << "." << flush; 
             this_thread::sleep_for(chrono::milliseconds(300));
             cout << "\b\b\b   \b\b\b" << flush; // Clear dots
             this_thread::sleep_for(chrono::milliseconds(200));
         }
    }

    static void drawFrame() {
        cout << ansiReset;
        system("clear");
        string frame =
            string(highlightBlack) + 
            "    _______________________________________________\n"
            "   /" + string(colorGray) + "* * * * * * * * * * * * * * * * * * * * * * * /" + ansiReset + highlightBlack + "\\\n"
            "  |    _________________________________________" + string(colorGray) + " /" + ansiReset + highlightBlack + " " + string(colorGray) + "*" + ansiReset + highlightBlack + "|\n" +
            "  |   |" + highlightBlue + "                                         " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"\n"+highlightBlack
            "  |   |" + highlightBlue + "                                         " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"\n"+highlightBlack
            "  |   |" + highlightBlue + "                                         " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"\n"+highlightBlack
            "  |   |" + highlightBlue + "                                         " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"\n"+highlightBlack
            "  |   |" + highlightBlue + "                                         " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"\n"+highlightBlack
            "  |   |" + highlightBlue + "                                         " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"\n"+highlightBlack
            "  |   |" + highlightBlue + "                                         " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"\n"+highlightBlack
            "  |   |" + highlightBlue + "                                         " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|\n"
            "  |   |" + highlightBlue + "                                         " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|\n"
            "  |   |" + highlightBlue + "                                         " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|\n"
            "  |   |" + highlightBlue + "                                         " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|\n"
            "  |   |" + highlightBlue + "_________________________________________" + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|\n"
            "  |                 " + string(bold) + "§ MEDIAFORGE §" + ansiReset + highlightBlack + "           " + string(colorGray) + "." + ansiReset + highlightBlack + "" + string(colorRed) + "." + ansiReset + highlightBlack + "    " + string(colorGray) + "*" + ansiReset + highlightBlack + "|\n"
            "   \\_______________________________________________/\n"
            "          / _)           " + string(colorYellow) + "t" + string(colorGreen) + "t" + string(colorRed) + "t" + string(colorWhite) + "t" + string(colorCyan) + "t" + ansiReset + highlightBlack + "          (_ \\\n"
            " ________/ /______________________________\\ \\_________\n"
            "/                                                     \\\n"
            "/    000000000000000000    .0.     0000====0x==       \\\n"
            "/  ==000000000000000000==.0.     000=xxx0===xx000     \\\n"
            "/_==____==========_______==_==________________________\\\n";
        cout << frame << endl; 
        cout << ansiReset; 
    }

    static void resetCursorToTop() {
        cout << "\033[21A" << "\033[8C" << flush;
    }

    static void bootScreen() {
        drawFrame();
        
        resetCursorToTop(); 
        slowPrint(string(bold) + colorCyan + highlightBlue + "<< SYSTEM BOOT: MEDIAFORGE." + ansiReset, 10);
        cout << "\n\033[1B" << "\r" << "\033[8C" << flush;
        slowPrint(string(bold) + colorCyan + highlightBlue + "<< BIOS VERSION... : vFINAL." + ansiReset, 10);
        system("afplay backup/Media/bootup.mp3 > /dev/null 2>&1 &");
        
        cout << "\033[1B" << "\r" << colorCyan;
        cout << "\033[1B" << "\r" << "\033[20C" << highlightBlue << " _|_|_" << ansiReset << highlightBlue << "  " << highlightBlue << "_|_|_" << ansiReset << flush;
        cout << "\033[1B" << "\r" << "\033[20C" << highlightBlue << " _|_|_" << ansiReset << highlightBlue << "  " << highlightBlue << "_|_|_" << ansiReset << flush;
        cout << "\033[1B" << "\r" << "\033[20C" << highlightBlue << "           " << flush;
        cout << "\033[1B" << "\r" << "\033[20C" << highlightBlue << " _|_|_" << ansiReset << highlightBlue << "  " << highlightBlue << "_|_|_" << ansiReset << flush;
        cout << "\033[1B" << "\r" << "\033[20C" << highlightBlue << " _|_|_" << ansiReset << highlightBlue << "  " << highlightBlue << "_|_|_" << ansiReset << flush;
        
        system("sleep 4"); 
        
        for(int i=0; i<8; ++i) { 
            cout << "\033[1A" << "\r\033[8C" << "                                        " << flush;
        }
        cout << "\r\033[8C" << flush << ansiReset;
        
        clearInner();
        slowPrint(string(highlightBlue) + string(bold) + "<< Initializing Database..." + ansiReset, 20);
        cout << ansiReset;
        cout << "\n\033[1B" << "\r" << "\033[8C" << flush;
        system("afplay backup/Media/success.mp3 > /dev/null 2>&1 &"); 
        slowPrint(string(highlightBlueGreenBold) + "<< Connection established!" + ansiReset, 20);
        cout << "\033[2B" << "\r" << "\033[8C" << flush;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    static void clearInner() {
        cout << ansiReset;
        drawFrame();
        cout << ansiReset;
        resetCursorToTop();
        cout << ansiReset;

    }
    
    template<typename T>
    static void input(T& var) {
        cout << ansiReset << string(bold) << string(highlightBlue);
        cout << ansiReset;
        cin >> var;
        cout << ansiReset;
        if(cin.fail()) {
            cout << ansiReset;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    // Robust integer input that prevents crashes
    static void inputInt(int& var) {
        cout << ansiReset << string(bold) << string(colorCyan);
        string line;
        getline(cin, line);
        cout << ansiReset;
        try {
            if(line.empty()) { var = -1; return; }
            var = stoi(line);
        } catch (...) {
            var = -1; // Return error code on invalid input
        }
    }
    
    static void inputLine(string& var) {
        cout << ansiReset << string(bold) << string(colorCyan);
        getline(cin, var);
        cout << ansiReset;
    }
};

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

class Date {
private:
    int day, month, year;
public:
    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
    
    static bool isValid(string dateStr) {
         stringstream ss(dateStr);
        string segment;
        vector<int> parts;
        while(getline(ss, segment, '-')) {
            parts.push_back(stoi(segment));
        }
        if(parts.size() != 3) return false;
        if(parts[1] < 1 || parts[1] > 12) return false;
        if(parts[2] < 1 || parts[2] > 31) return false;
        return true;       
    }
};

// Media Classes

class Media {
protected:
    string title; // Filename without extension
    string path;  // Full path
    float price;  // Defaulted

public:
    Media(string t, string p) : title(t), path(p) {
        price = 100.0f; // Default price
    }
    virtual ~Media() {}

    string getTitle() const { return title; }
    string getPath() const { return path; }
    float getPrice() const { return price; }
    
    virtual void displayCompact() const = 0;
    virtual string getType() const = 0;
    
    virtual void openExternal() const {
        string cmd = "open \"" + path + "\"";
        system(cmd.c_str());
    }
};

class Book : public Media {
public:
    Book(string t, string p) : Media(t, p) {}
    void displayCompact() const override {
        string tDisplay = title.length() > 20 ? title.substr(0,17)+"..." : title;
        cout << string(highlightBlue) << left << setw(22) << tDisplay << " | " << setw(6) << price << " MAD" << ansiReset << endl;
        cout << "\033[8C"; 
    }
    string getType() const override { return "Book"; }
};

class Video : public Media {
public:
    Video(string t, string p) : Media(t, p) {}
    void displayCompact() const override {
        string tDisplay = title.length() > 20 ? title.substr(0,17)+"..." : title;
        cout << string(highlightBlue) << left << setw(22) << tDisplay << " | " << setw(6) << price << " MAD" << ansiReset << endl;
        cout << "\033[8C"; 
    }
    string getType() const override { return "Video"; }
};

class Audio : public Media {
public:
    Audio(string t, string p) : Media(t, p) {}
    void displayCompact() const override {
        string tDisplay = title.length() > 20 ? title.substr(0,17)+"..." : title;
        cout << string(highlightBlue) << left << setw(22) << tDisplay << " | " << setw(6) << price << " MAD" << ansiReset << endl;
        cout << "\033[8C"; 
    }
    string getType() const override { return "Audio"; }
};

// User Classes

class User {
protected:
    string email;
    string password;
    string fullName;
    int age;
    string dateOfBirth;
    string role;
    vector<Media*> basket;
    vector<Media*> ownedMedia;

public:
    User(string e, string p, string fn, int a, string dob, string r) 
        : email(e), password(p), fullName(fn), age(a), dateOfBirth(dob), role(r) {}
    
    virtual ~User() {}

    string getEmail() const { return email; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
    string getFullName() const { return fullName; }
    
    void setEmail(string e) { email = e; }
    void setFullName(string fn) { fullName = fn; }
    void setAge(int a) { age = a; }
    
    // Silent param to fix redundant messaging
    void addToBasket(Media* m, bool silent = false) {
        basket.push_back(m);
        if(!silent) {
            cout << "\n\033[8C" << colorGreen << bold << string(highlightBlue) << "Added to basket." << ansiReset << endl;
            this_thread::sleep_for(chrono::milliseconds(800));
        }
    }
    
    void addToOwned(Media* m) {
        bool alreadyOwned = false;
        for(auto* om : ownedMedia) {
            if(om->getTitle() == m->getTitle()) {
                alreadyOwned = true; 
                break;
            }
        }
        if(!alreadyOwned) ownedMedia.push_back(m);
    }
    
    vector<Media*>& getBasket() { return basket; }
    vector<Media*>& getOwned() { return ownedMedia; }
    
    void clearBasket() { basket.clear(); }
    void clearOwned() { ownedMedia.clear(); }
    
    virtual float getDiscountPercentage() const { return 0.0f; }
    virtual string getDiscountName() const { return ""; }

    void viewBasket(function<void()> refresher) {
        UI::clearInner();
        cout << string(bold) << string(highlightBlue) << "== Your Basket ==" << ansiReset << endl;
        cout << "\n\033[8C";
        if (basket.empty()) {
            cout << "\033[8C" << colorRed << bold << string(highlightBlue) << "Basket is empty." << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << "Press Enter to go back..."<<ansiReset;
            cin.ignore(); cin.get();
            cout << ansiReset;
        } else {
            float total = 0.0f;
            int count = 0;
            for (const auto* m : basket) {
                if(count++ > 5) { cout << string(highlightBlue) << "... more items ..." << ansiReset << endl; cout << "\033[8C"; break; } 
                m->displayCompact();
                total += m->getPrice();
            }
            cout << string(highlightBlue) << "-------------------" << ansiReset << endl;
            cout << "\033[8C";
            cout << string(highlightBlue) << bold << "Subtotal: " << fixed << setprecision(2) << total << " MAD" << ansiReset << endl;
            cout << "\033[8C";
            
            float discount = getDiscountPercentage();
            float finalTotal = total;
            if (discount > 0.0f) {
                float discountAmount = total * discount;
                cout << string(highlightBlue) << colorGreen << "Disc (-" << (discount * 100) << "%): -" << discountAmount << ansiReset << endl;
                cout << "\033[8C";
                finalTotal -= discountAmount;
                cout << string(highlightBlue) << bold << underline << "Total: " << finalTotal << " MAD" << ansiReset << endl;
            } else {
                cout << string(highlightBlue) << bold << underline << "Total: " << total << " MAD" << ansiReset << endl;
            }
            
            cout << string(highlightBlue) << "\033[8C" << "Options: [C]heckout, [X] Clear, [0] Back" << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << ">> ";
            string choiceStr;
            UI::input(choiceStr);
            cout << ansiReset;
            char choice = choiceStr[0];
            
            if(choice == 'C' || choice == 'c') {
                for(auto* m : basket) {
                    addToOwned(m);
                }
                clearBasket();
                
                refresher(); 

                system("afplay backup/Media/success.mp3 > /dev/null 2>&1 &");
                cout << "\033[8C" << colorGreen << "Purchased!" << ansiReset << endl;
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
            else if (choice == 'X' || choice == 'x') {
                clearBasket();
                cout << "\n\033[8C" << highlightBlue << colorRed << bold << "Basket cleared." << ansiReset << endl;
                this_thread::sleep_for(chrono::milliseconds(800));
                refresher();
            }
        }
    }
    
    void viewOwnedMedia() {
        UI::clearInner();
        cout << string(bold) << string(highlightBlue) << "== My Media ==" << ansiReset << endl;
        cout << "\n\033[8C";
        if(ownedMedia.empty()) {
            cout << "\n\033[8C" << colorRed << bold << string(highlightBlue) << "No media owned." << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << "Press Enter to go back..." << ansiReset;
            cin.ignore(); cin.get();
            cout << ansiReset;
            return;
        }
        
        for(size_t i=0; i<ownedMedia.size(); ++i) {
             if(i > 8) { cout << "... (more) ..." << endl; cout<<"\033[8C"; break; }
             string t = ownedMedia[i]->getTitle();
             if(t.length()>20) t = t.substr(0,17)+"..."; // Compact
             cout << string(highlightBlue) << i+1 << ". " << left << setw(22) << t << " [" << ownedMedia[i]->getType() << "]" << ansiReset << endl;
            cout << "\033[8C";
        }
        cout << ansiReset;
        cout << "\n\033[8C" << string(highlightBlue) << ">> ";
        int choice;
        UI::input(choice);
        cout << ansiReset;
        
        if(choice > 0 && choice <= (int)ownedMedia.size()) {
            Media* selected = ownedMedia[choice-1];
            UI::clearInner();
            UI::clearInner();
            cout << string(highlightBlue) << "Opening... " << ansiReset << endl;
            cout << "\033[8C" << highlightBlue << "Launching external viewer..." << ansiReset << endl;
            selected->openExternal();
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    void shopMediaType(vector<Media*>& library, string type, function<void()> refresher) {
        refresher();

        UI::clearInner();
        vector<Media*> filtered;
        for(auto* m : library) if(m->getType() == type) filtered.push_back(m);
        
        cout << string(bold) << string(highlightBlue) << "== Shop " << type << "s ==" << ansiReset << endl;
        cout << "\n" << "\033[8C";
        
        if(filtered.empty()) {
             cout << "\n\033[8C" << colorRed << bold << string(highlightBlue) << "No stock available." << ansiReset << endl;
             this_thread::sleep_for(chrono::seconds(1));
             return;
        }

        for (size_t i = 0; i < filtered.size(); ++i) {
            cout << string(highlightBlue) << (i+1) << ". ";
            filtered[i]->displayCompact();
        }
        cout << string(highlightBlue) << "0. Back" << ansiReset << endl;
        cout << ansiReset;
        cout << "\n\033[8C" << string(highlightBlue) << ">> ";
        int choice;
        UI::input(choice);
        cout << ansiReset;
        
        if(choice > 0 && choice <= (int)filtered.size()) {
             addToBasket(filtered[choice-1], false);
        }
    }

    virtual void displayMenu(vector<Media*>& library, vector<User*>& users, function<void()> refresher) = 0;

    virtual string toString() const {
        return role + "|" + email + "|" + password + "|" + fullName + "|" + to_string(age) + "|" + dateOfBirth;
    }

    string getBasketString() const {
        if(basket.empty()) return "";
        string res = email + "|";
        for(size_t i=0; i<basket.size(); ++i) {
            res += basket[i]->getTitle();
            if(i < basket.size() - 1) res += "|";
        }
        return res;
    }
    
    string getOwnedString() const {
        if(ownedMedia.empty()) return "";
        string res = email + "|";
        for(size_t i=0; i<ownedMedia.size(); ++i) {
             res += ownedMedia[i]->getTitle();
            if(i < ownedMedia.size() - 1) res += "|";
        }
        return res;
    }
};

class Client : public User {
public:
    Client(string e, string p, string fn, int a, string dob) 
        : User(e, p, fn, a, dob, "client") {}

    void displayMenu(vector<Media*>& library, vector<User*>& users, function<void()> refresher) override {
        int choice;
        cout << ansiReset;
        do {
            cout << ansiReset;
            UI::clearInner(); 
            cout << ansiReset;
            cout << ansiReset << string(bold) << string(highlightBlue) << "== Welcome Client: " << fullName << " ==\n" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "1. Shop Books" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "2. Shop Videos" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "3. Shop Audios" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "4. Basket" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "5. My Media" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "0. Log-out" << ansiReset << endl;
            cout << ansiReset;
            cout << "\n\033[8C" << string(highlightBlue) << ">> ";
            UI::input(choice);
            cout << ansiReset;
            switch (choice) {
                case 1: shopMediaType(library, "Book", refresher); break;
                case 2: shopMediaType(library, "Video", refresher); break;
                case 3: shopMediaType(library, "Audio", refresher); break;
                case 4: viewBasket(refresher); break;
                case 5: viewOwnedMedia(); break;
                case 0: break;
                default: 
                    cout << "\n\033[8C" << colorRed << bold << string(highlightBlue) << "Invalid choice." << ansiReset << endl;
                    this_thread::sleep_for(chrono::milliseconds(500));
                    break;
            }
        } while (choice != 0);
    }
};

class Admin : public User {
public:
    Admin(string e, string p, string fn, int a, string dob) 
        : User(e, p, fn, a, dob, "admin") {}

    float getDiscountPercentage() const override { return 0.20f; }
    string getDiscountName() const override { return "Admin Discount"; }
    
    void addUser(vector<User*>& users) { // Simplified
        string e, p, fn, dob, r; int a;
        UI::clearInner(); 
        cout << string(bold) << string(highlightBlue) << "== Create User ==" << ansiReset << endl; 
        cout << "\n\033[8C" << string(highlightBlue) << "E-mail: " << ansiReset; UI::input(e);
        for(auto* u : users) if(u->getEmail() == e) { return; }
        cout << string(highlightBlue) << "\033[8C" << "Password: " << ansiReset; UI::input(p); cin.ignore(); 
        cout << string(highlightBlue) << "\033[8C" << "Full Name: " << ansiReset; UI::inputLine(fn);
        cout << string(highlightBlue) << "\033[8C" << "Age: " << ansiReset; UI::input(a); 
        cout << string(highlightBlue) << "\033[8C" << "Date of Birth: " << ansiReset; UI::input(dob); 
        cout << string(highlightBlue) << "\033[8C" << "Role: " << ansiReset; UI::input(r);
        cout << ansiReset;
        users.push_back((r=="admin")?(User*)new Admin(e,p,fn,a,dob):(User*)new Client(e,p,fn,a,dob));
    }
    void deleteUser(vector<User*>& users) {
         UI::clearInner(); string e; 
         cout << string(bold) << string(highlightBlue) << "== Delete User ==" << ansiReset << endl;
         cout << "\n\033[8C" << string(highlightBlue) << "Delete E-mail: " << ansiReset; UI::input(e); cout << ansiReset;
         for(auto it=users.begin();it!=users.end();++it) { if((*it)->getEmail()==e){ delete *it; users.erase(it); return; } }
    }
    void editUser(vector<User*>& users) {} // Stub
    void searchUser(const vector<User*>& users) {} // Stub
    void showDatabase(const vector<User*>& users) {
        UI::clearInner(); for(auto* u:users) { cout<<string(highlightBlue)<<u->getEmail()<<"|"<<u->getFullName()<<ansiReset<<endl; cout<<"\n\033[8C"; }
        cout << highlightBlue << "Press Enter to go back..." << ansiReset; cin.ignore(); cin.get();
        cout << ansiReset;
    }
    
    void menuUserManagement(vector<User*>& users) {
        int choice;
        do {
            cout << ansiReset;
            UI::clearInner();
            cout << string(bold) << string(colorCyan) << string(highlightBlue) << "== User Management ==" << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << "1. Add   2. Delete" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "3. Show All" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "0. Back" << ansiReset << endl;
            cout << ansiReset;
            cout << "\n\033[8C" << string(highlightBlue) << ">> ";
            UI::input(choice);
            cout << ansiReset;
            
            switch(choice) {
                case 1: addUser(users); break;
                case 2: deleteUser(users); break;
                case 3: showDatabase(users); break;
                case 0: break;

                default: 
                    cout << "\n\033[8C" << colorRed << bold << string(highlightBlue) << "Invalid choice." << ansiReset << endl;
                    this_thread::sleep_for(chrono::milliseconds(500));
                    break;
            }
        } while(choice != 0);
    }

    void openManager(string folder) {
        UI::clearInner();
        cout << colorCyan << string(highlightBlue) << "Opening Finder" << "..." << ansiReset << endl;
        string cmd = "open " + folder;
        system(cmd.c_str());
    }

    void menuMediaManagement() {
        int choice;
        do {
            UI::clearInner();
            cout << string(bold) << string(highlightBlue) << "== Media Management ==" << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << "1. Manage Books" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "2. Manage Videos" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "3. Manage Audios" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "0. Back" << ansiReset << endl;
            cout << ansiReset;
            cout << "\n\033[8C" << string(highlightBlue) << ">> ";
            UI::input(choice);
            cout << ansiReset;
             switch(choice) {
                case 1: openManager("books"); break;
                case 2: openManager("videos"); break;
                case 3: openManager("audios"); break;
                case 0: break;
                default: 
                     cout << "\n\033[8C" << colorRed << bold << string(highlightBlue) << "Invalid choice." << ansiReset << endl;
                     this_thread::sleep_for(chrono::milliseconds(500));
                     break;
            }
        } while(choice != 0);       
    }
    
    void menuPersonal(vector<Media*>& library, function<void()> refresher) {
         int choice;
        do {
            UI::clearInner();
            cout << string(bold) << string(highlightBlue) << "== Browse as a Client ==" << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << "1. Shop Books" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "2. Shop Videos" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "3. Shop Audios" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "4. Basket" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "5. My Media" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "0. Back" << ansiReset << endl;
            cout << ansiReset;
            cout << "\n\033[8C" << string(highlightBlue) << ">> ";
            UI::input(choice);
            cout << ansiReset;
             switch(choice) {
                case 1: shopMediaType(library, "Book", refresher); break;
                case 2: shopMediaType(library, "Video", refresher); break;
                case 3: shopMediaType(library, "Audio", refresher); break;
                case 4: viewBasket(refresher); break;
                case 5: viewOwnedMedia(); break;
                case 0: break;

                default: 
                    cout << "\n\033[8C" << colorRed << bold << string(highlightBlue) << "Invalid choice." << ansiReset << endl;
                    this_thread::sleep_for(chrono::milliseconds(500));
                    break;
            }
        } while(choice != 0); 
    }

    void displayMenu(vector<Media*>& library, vector<User*>& users, function<void()> refresher) override {
        int choice;
        do {
            cout << ansiReset;

            UI::clearInner();
            cout << string(bold) << string(highlightBlue) << "== Welcome Admin: " << fullName << " ==\n" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "1. User Management" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "2. Media Management" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "3. Browse as a Client" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "0. Log-out" << ansiReset;
            cout << ansiReset;
            cout << "\n\n\033[8C" << string(highlightBlue) << ">> " << ansiReset;
            UI::input(choice);
            cout << ansiReset;
            switch (choice) {
                case 1: menuUserManagement(users); break;
                case 2: menuMediaManagement(); break;
                case 3: menuPersonal(library, refresher); break;
                case 0: break;
                default: 
                    cout << "\n\033[8C" << colorRed << bold << string(highlightBlue) << "Invalid choice." << ansiReset << endl;
                    this_thread::sleep_for(chrono::milliseconds(500));
                    break;
            }
        } while (choice != 0);
    }
};

// System

class System {
private:
    vector<User*> users;
    vector<Media*> library;
    string userFile = "users.txt";
    string basketFile = "baskets.txt";
    string ownedFile = "owned.txt";

    void loadUsers() {
        ifstream file(userFile);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            if(line.empty()) continue;
            stringstream ss(line);
            string segment;
            vector<string> parts;
            while(getline(ss, segment, '|')) {
                parts.push_back(segment);
            }
            if (parts.size() >= 6) {
                if (parts[0] == "admin") {
                    users.push_back(new Admin(parts[1], parts[2], parts[3], stoi(parts[4]), parts[5]));
                } else {
                    users.push_back(new Client(parts[1], parts[2], parts[3], stoi(parts[4]), parts[5]));
                }
            }
        }
        file.close();
    }
    
    void saveUsers() { ofstream f(userFile); for(auto* u:users) f<<u->toString()<<endl; f.close(); }
    
    void scanDirectory(string path, string type) {
        if(!fs::exists(path)) fs::create_directory(path);
        for(const auto& entry : fs::directory_iterator(path)) {
            if(entry.is_regular_file()) {
                string fname = entry.path().filename().string();
                if(fname == ".DS_Store") continue;
                string title = entry.path().stem().string(); // Filename no ext
                string fpath = entry.path().string();
                
                bool exists = false;
                for(auto* m : library) if(m->getPath() == fpath) exists = true;
                if(exists) continue;

                if(type == "Book") library.push_back(new Book(title, fpath));
                else if(type == "Video") library.push_back(new Video(title, fpath));
                else if(type == "Audio") library.push_back(new Audio(title, fpath));
            }
        }
    }

    void loadBaskets() {
        ifstream f(basketFile); string l;
        while(getline(f,l)){
             if(l.empty())continue; stringstream ss(l); string s; vector<string> p;
             while(getline(ss,s,'|')) p.push_back(s);
             if(p.size()>=2) {
                 string e=p[0]; User* u=nullptr; for(auto* us:users) if(us->getEmail()==e) u=us;
                 if(u) for(size_t i=1;i<p.size();++i) for(auto* m:library) if(toLower(m->getTitle())==toLower(p[i])) u->addToBasket(m, true); // Silent load!
             }
        }
        f.close();
    }
    void saveBaskets() { ofstream f(basketFile); for(auto* u:users) { string s=u->getBasketString(); if(!s.empty()) f<<s<<endl; } f.close(); }
    
    void loadOwned() {
        ifstream f(ownedFile); string l;
        while(getline(f,l)) {
            if(l.empty())continue; stringstream ss(l); string s; vector<string> p;
            while(getline(ss,s,'|')) p.push_back(s);
            if(p.size()>=2) {
                string e=p[0]; User* u=nullptr; for(auto* us:users) if(us->getEmail()==e) u=us;
                if(u) for(size_t i=1;i<p.size();++i) for(auto* m:library) if(toLower(m->getTitle())==toLower(p[i])) u->addToOwned(m);
            }
        }
        f.close();
    }
    
    void saveOwned() { ofstream f(ownedFile); for(auto* u:users) { string s=u->getOwnedString(); if(!s.empty()) f<<s<<endl; } f.close(); }

public:
    System() {
        loadUsers();
        refreshDatabase(false); // FALSE: Do NOT save existing (empty) state on first load
    }

    ~System() {
        saveBaskets(); saveOwned(); saveUsers();
        for (auto* u : users) delete u;
        for (auto* m : library) delete m;
    }

    void refreshDatabase(bool saveFirst = true) {
        // 0. Save current in-memory state FIRST (Only if requested)
        if(saveFirst) {
            saveBaskets();
            saveOwned();
        }

        // 1. Clean up old library media
        for(auto* m : library) delete m;
        library.clear();
        
        // 2. Rescan directories
        scanDirectory("books", "Book");
        scanDirectory("videos", "Video");
        scanDirectory("audios", "Audio");
        
        // 3. Reset user links
        for(auto* u : users) {
            u->clearBasket();
            u->clearOwned();
        }
        
        // 4. Reload links from files
        loadBaskets();
        loadOwned();
    }

    void run() {
        UI::bootScreen();
        
        while (true) {
            UI::clearInner(); 
            // Save & Reload state on every loop
            refreshDatabase(); 
            cout << ansiReset;
            cout << string(bold) << string(highlightBlue) << "== Login Portal ==" << ansiReset << endl;
            string email, password;
            cout << "\n\033[8C" << string(highlightBlue) << string(bold) << "Enter your E-mail: "<< "\n\033[8C"; UI::input(email);
            if (email == "exit") break; 
            cout << "\n" << string(highlightBlue) << string(bold) << "\033[8C" << "Enter your Password: "<< "\n\033[8C";
            UI::input(password);
            cout << ansiReset;

            User* currentUser = nullptr;
            for (auto* u : users) {
                if (u->getEmail() == email && u->getPassword() == password) {
                    currentUser = u;
                    break;
                }
            }

            if (currentUser) {
                system("afplay backup/Media/success.mp3 > /dev/null 2>&1 &");
                
                // Pass a lambda to allow User classes to trigger System refresh
                currentUser->displayMenu(library, users, [this](){
                    this->refreshDatabase(true); // Save first during runtime
                });
            } else {
                system("afplay backup/Media/error.wav > /dev/null 2>&1 &");
                cout << "\n\033[8C" << colorRed << bold << string(highlightBlue) << "Invalid credentials." << ansiReset << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
        
        UI::clearInner();
        cout << highlightBlue << bold << "Shutting down..." << ansiReset << endl;
    }
};

int main() {
    System app;
    app.run();
    return 0;
}
