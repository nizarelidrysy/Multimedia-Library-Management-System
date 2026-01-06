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
#include <memory>

using namespace std;
namespace fs = std::filesystem;

// UI & ANSI Definitions

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
#define highlightGray "\033[100m" 
#define highlightGreen "\033[42m"
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
    
    static string drawBox(string color, string text) {
         string top = "╔";
         string bot = "╚";
         for(size_t i=0; i<text.length()+2; ++i) {
             top += "═";
             bot += "═";
         }
         top += "╗\n";
         bot += "╝\n";
         string indent = "\033[8C";
         string res = indent + string(highlightBlack) + top + 
                      indent + string(highlightBlack) + "║ " + color + text + ansiReset + string(highlightBlack) + " ║\n" + 
                      indent + string(highlightBlack) + bot + ansiReset;
         return res;
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

    static void drawFrame(bool forceClear = true) {
        cout << ansiReset;
        if(forceClear) system("clear");
        else cout << "\033[1;1H"; // Move to Top-Left
        
        string frame =
            string(highlightBlack) + 
            "    __________________________________________________________      _____________\n"
            "   /" + string(colorGray) + "* * * * * * * * * * * * * * * * * * * * * * * * * * * * */" + ansiReset + highlightBlack + "\\    /  " + string(highlightBlack) + "_________" + ansiReset + highlightBlack + " "+ string(colorGray) + "*" + ansiReset + highlightBlack +"\\\n"
            "  |    ____________________________________________________" + string(colorGray) + " /" + ansiReset + highlightBlack + " " + string(colorGray) + "*" + ansiReset + highlightBlack + "|  |  " + string(highlightBlack) + "|         |" + ansiReset + highlightBlack + " "+ string(colorGray) + "*" + ansiReset + highlightBlack +"|\n" +
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|         |"+ansiReset+highlightBlack+" "+ string(colorGray) + "*" + ansiReset + highlightBlack +"|\n"+highlightBlack
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|         |"+ansiReset+highlightBlack+" "+ string(colorGray) + "*" + ansiReset + highlightBlack +"|\n"+highlightBlack
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|         |"+ansiReset+highlightBlack+" "+ string(colorGray) + "*" + ansiReset + highlightBlack +"|\n"+highlightBlack
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|         | "+ string(colorGray) + "*" + ansiReset + highlightBlack +""+ansiReset+highlightBlack+"|\n"
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|         | "+ string(colorGray) + "*" + ansiReset + highlightBlack +""+ansiReset+highlightBlack+"|\n"
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|         | "+ string(colorGray) + "*" + ansiReset + highlightBlack +""+ansiReset+highlightBlack+"|\n"
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|         | "+ string(colorGray) + "*" + ansiReset + highlightBlack +""+ansiReset+highlightBlack+"|\n"
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|         | "+ string(colorGray) + "*" + ansiReset + highlightBlack +""+ansiReset+highlightBlack+"|\n"
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|         | "+ string(colorGray) + "*" + ansiReset + highlightBlack +""+ansiReset+highlightBlack+"|\n"
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|         | "+ string(colorGray) + "*" + ansiReset + highlightBlack +""+ansiReset+highlightBlack+"|\n"
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|         | "+ string(colorGray) + "*" + ansiReset + highlightBlack +""+ansiReset+highlightBlack+"|\n"
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|         | "+ string(colorGray) + "*" + ansiReset + highlightBlack +""+ansiReset+highlightBlack+"|\n"
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|    " + string(colorGray) + "_" + ansiReset + highlightBlack + "    | "+ string(colorGray) + "*" + ansiReset + highlightBlack +""+ansiReset+highlightBlack+"|\n"
            "  |   |" + highlightBlue + "                                                    " + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|"+highlightBlack+"  |  "+string(highlightBlack)+"|   " + string(colorGray) + "(_)" + ansiReset + highlightBlack + "   | "+ string(colorGray) + "*" + ansiReset + highlightBlack +""+ansiReset+highlightBlack+"|\n"
            "  |   |" + highlightBlue + "____________________________________________________" + ansiReset + highlightBlack + "|  " + string(colorGray) + "*" + ansiReset + highlightBlack + "|  |  " + string(highlightBlack) + "|         | "+ string(colorGray) + "*" + ansiReset + highlightBlack +"" + ansiReset + highlightBlack + "|\n"
            "  |                      " + string(bold) + "§ MEDIAFORGE §" + ansiReset + highlightBlack + "                 " + string(colorGray) + "." + ansiReset + highlightBlack + "" + string(colorRed) + "." + ansiReset + highlightBlack + "    " + string(colorGray) + "*" + ansiReset + highlightBlack + "|  |  " + string(highlightBlack) + "|   "+ string(colorGray)+"IBM"+ ansiReset + highlightBlack +"   | "+ string(colorGray) + "*" + ansiReset + highlightBlack +"" + ansiReset + highlightBlack + "|\n"
            "   \\__________________________________________________________/    \\ " + string(highlightBlack) + "|         |"+ string(colorGray) + "*" + ansiReset + highlightBlack +"" + ansiReset + highlightBlack + "/\n"
            "          / _)               " + string(colorRed) + "t" + string(colorYellow) + "t" + string(colorGreen) + "t" + string(colorRed) + "t" + string(colorWhite) + "t" + string(colorCyan) + "t" + string(colorGreen) + "t" + ansiReset + highlightBlack + "                  (_ \\    " + string(highlightBlack) + "      \\|_________|" + ansiReset + highlightBlack + "/\n"
            " ________/ /_____________________" + ansiReset + highlightBlack + "_______________________\\ \\__________H_________H__________\n"


            "/  " + string(highlightBlack) + "________________________________________________" + ansiReset + highlightBlack + "" + string(highlightBlack) +"   " + "__________" + ansiReset + highlightBlack + "                          /\n"
            "/  " + string(highlightBlack) + "| " + string(colorCyan) + "[ESC] [F1] [F2] [F3] [F4] [F5] [F6] [F7] [F8] " + ansiReset + highlightBlack + "" + string(highlightBlack) + "|  |" + string(colorGray) + "[7][8][9]" + ansiReset + highlightBlack + "|                         /\n"
            "/   " + string(highlightBlack) + "| " + string(colorGray) + "["+ string(colorGreen) + "." + ansiReset + string(highlightBlack) + string(colorGray) +"UP] [ Q] [ W] [ E] [ R] [ T] [ Y] [ U] [ I]" + ansiReset + highlightBlack + " " + string(highlightBlack) + "|  |" + string(colorGray) + "[4][5][6]" + ansiReset + highlightBlack + "|                        /\n"
            "/    " + string(highlightBlack) + "| " + string(colorGray) + "[CMD] [ A] [ S] [ D] [ F] [ G] [ H] [ J] [ K] " + ansiReset + highlightBlack + "" + string(highlightBlack) + "|  |" + string(colorGray) + "[1][2][3]" + ansiReset + highlightBlack + "|                       /\n"
            "/     " + string(highlightBlack) + "|_________________"+ string(colorGray) +"[ --SPACE-- ]"+ ansiReset + highlightBlack +"_________________|" + ansiReset + highlightBlack + "  |___"+string(colorGray)+"[0]"+ ansiReset + highlightBlack"___|   " + string(highlightBlack) + "" + string(colorGray) + "" + ansiReset + highlightBlack + "   " + string(colorGreen) + "" + ansiReset + highlightBlack + "                /\n"
            "/_____________________________________________________________________________" + string(highlightBlack) + "_________" + ansiReset + highlightBlack + "___/\n";
        cout << frame << endl; 
        cout << ansiReset; 
    }

    static void resetCursorToTop() {
        cout << "\033[26A" << "\033[8C" << flush;
    }

    static void bootScreen() {
        drawFrame(true);
        resetCursorToTop(); 
        for(int i=0; i<8; ++i) { 
            cout << "\033[1A" << "\r\033[8C" << "                                        " << flush;
        }
        cout << "\r\033[8C" << flush << ansiReset;
        
        clearInner();
    }

    static void clearInner() {
        cout << ansiReset;
        drawFrame(false); // Overwrite, don't clear
        cout << ansiReset;
        resetCursorToTop();
        cout << ansiReset;
    }
    
    template<typename T>
    static void input(T& var) {
        cout << ansiReset << string(bold) << string(highlightBlue);
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

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first) return str;
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
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
    string title; 
    string path;  
    float price;  
    bool isBorrowed;
    int durationSeconds; // For Audio/Video/AudioBook

public:
    Media(string t, string p) : title(t), path(p), isBorrowed(false), durationSeconds(0) {
        price = 100.0f; 
    }
    virtual ~Media() = default;

    string getTitle() const { return title; }
    string getPath() const { return path; }
    float getPrice() const { return price; }
    bool getIsBorrowed() const { return isBorrowed; }
    int getDuration() const { return durationSeconds; }

    void setBorrowed(bool status) { isBorrowed = status; }
    void setDuration(int s) { durationSeconds = s; }
    
    virtual void displayCompact() const = 0;
    virtual string getType() const = 0;
    
    virtual void openExternal() const {
        string cmd = "open \"" + path + "\"";
        system(cmd.c_str());
    }

    // Operator Overloading
    bool operator==(const Media& other) const { return this->title == other.title; }
    bool operator<(const Media& other) const { return this->title < other.title; }
};

class Book : virtual public Media {
public:
    Book(string t, string p) : Media(t, p) {}
    void displayCompact() const override {
        string tDisplay = title.length() > 20 ? title.substr(0,17)+"..." : title;
        string status = isBorrowed ? "[BRW]" : "[AVB]";
        string color = isBorrowed ? colorRed : colorGreen;
        cout << string(highlightBlue) << left << setw(22) << tDisplay << " | " << setw(6) << price << " MAD | " << color << status << ansiReset << endl;
        cout << "\033[8C"; 
    }
    string getType() const override { return "Book"; }
};

class Video : virtual public Media {
public:
    Video(string t, string p) : Media(t, p) { 
        durationSeconds = 120 * 60; // Mock duration: 2 hours
    }
    void displayCompact() const override {
        string tDisplay = title.length() > 20 ? title.substr(0,17)+"..." : title;
        string status = isBorrowed ? "[BRW]" : "[AVB]";
        string color = isBorrowed ? colorRed : colorGreen;
        cout << string(highlightBlue) << left << setw(22) << tDisplay << " | " << setw(6) << price << " MAD | " << color << status << ansiReset << endl;
        cout << "\033[8C"; 
    }
    string getType() const override { return "Video"; }
};

class Audio : virtual public Media {
public:
    Audio(string t, string p) : Media(t, p) {
        durationSeconds = 3 * 60; // Mock duration: 3 mins
    }
    void displayCompact() const override {
        string tDisplay = title.length() > 20 ? title.substr(0,17)+"..." : title;
        string status = isBorrowed ? "[BRW]" : "[AVB]";
        string color = isBorrowed ? colorRed : colorGreen;
        cout << string(highlightBlue) << left << setw(22) << tDisplay << " | " << setw(6) << price << " MAD | " << color << status << ansiReset << endl;
        cout << "\033[8C"; 
    }
    string getType() const override { return "Audio"; }
};

class AudioBook : public Book, public Audio {
public:
    AudioBook(string t, string p) : Media(t, p), Book(t, p), Audio(t, p) {
        durationSeconds = 600 * 60; // Mock 10 hours
    }
    void displayCompact() const override {
        string tDisplay = title.length() > 20 ? title.substr(0,17)+"..." : title;
        string status = isBorrowed ? "[BRW]" : "[AVB]";
        string color = isBorrowed ? colorRed : colorGreen;
        cout << string(highlightBlue) << left << setw(22) << tDisplay << " | " << setw(6) << price << " MAD | " << color << status << ansiReset << endl;
        cout << "\033[8C";
    }
    string getType() const override { return "AudioBook"; }
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
    vector<shared_ptr<Media>> basket;
    vector<shared_ptr<Media>> ownedMedia; // Borrowed items
    vector<shared_ptr<Media>> purchasedMedia; // Purchased items

public:
    User(string e, string p, string fn, int a, string dob, string r) 
        : email(e), password(p), fullName(fn), age(a), dateOfBirth(dob), role(r) {}
    
    virtual ~User() {} 

    string getEmail() const { return email; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
    string getFullName() const { return fullName; }
    int getAge() const { return age; }
    string getDateOfBirth() const { return dateOfBirth; }
    
    void setEmail(string e) { email = e; }
    void setFullName(string fn) { fullName = fn; }
    void setAge(int a) { age = a; }
    
    // Silent param to fix redundant messaging
    void addToBasket(shared_ptr<Media> m, bool silent = false) {
        if(m->getIsBorrowed()) {
             if(!silent) {
                cout << "\n\033[8C" << colorRed << bold << string(highlightBlue) << "Item is currently borrowed." << ansiReset << endl;
                this_thread::sleep_for(chrono::milliseconds(800));
             }
             return;
        }
        basket.push_back(m);
        if(!silent) {
            cout << "\n\033[8C" << colorGreen << bold << string(highlightBlue) << "Added to basket." << ansiReset << endl;
            this_thread::sleep_for(chrono::milliseconds(800));
        }
    }
    
    void borrowMedia(shared_ptr<Media> m) {
        bool alreadyHas = false;
        for(auto& om : ownedMedia) {
            if(om->getTitle() == m->getTitle()) {
                alreadyHas = true; 
                break;
            }
        }
        if(alreadyHas) {
             if(!m->getIsBorrowed()) m->setBorrowed(true);
             return;
        }

        if(!m->getIsBorrowed()) {
            ownedMedia.push_back(m);
            m->setBorrowed(true);
        }
    }
    
    void returnMedia(shared_ptr<Media> m) {
        for(auto it = ownedMedia.begin(); it != ownedMedia.end(); ++it) {
            if((*it)->getTitle() == m->getTitle()) {
                (*it)->setBorrowed(false);
                ownedMedia.erase(it);
                break;
            }
        }
    }

    vector<shared_ptr<Media>>& getBasket() { return basket; }
    vector<shared_ptr<Media>>& getOwned() { return ownedMedia; }
    vector<shared_ptr<Media>>& getPurchased() { return purchasedMedia; }
    
    void addToPurchased(shared_ptr<Media> m) {
        bool already = false;
        for(auto& p : purchasedMedia) if(p->getTitle() == m->getTitle()) already = true;
        if(!already) purchasedMedia.push_back(m);
    }
    
    void clearBasket() { basket.clear(); }
    void clearOwned() { 
        for(auto& m : ownedMedia) m->setBorrowed(false);
        ownedMedia.clear(); 
    }
    void clearPurchased() { purchasedMedia.clear(); }
    
    virtual float getDiscountPercentage() const { return 0.0f; }
    virtual string getDiscountName() const { return ""; }

    void viewBasket(function<void()> refresher) {
        UI::clearInner();
        cout << string(bold) << string(highlightBlue) << "== " << underline << fullName << "'s Basket" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl; // Personalized
        cout << "\n\033[8C";
        if (basket.empty()) {
            cout << "\033[8C" << colorRed << bold << string(highlightBlue) << "Basket is empty." << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << "Press Enter to go back..."<<ansiReset;
            cin.ignore(); cin.get();
            cout << ansiReset;
        } else {
            float total = 0.0f;
            int count = 0;
            for (const auto& m : basket) {
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
            
            cout << string(highlightBlue) << "\033[8C" << "Options: [C]onfirm Loan, [X] Clear, [0] Back" << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << ">> ";
            string choiceStr;
            UI::input(choiceStr);
            cout << ansiReset;
            char choice = choiceStr[0];
            
            if(choice == 'C' || choice == 'c') {
                for(auto& m : basket) {
                    if(m->getIsBorrowed()) {
                        cout << "\033[8C" << colorRed << "Some items are not available." << ansiReset << endl;
                        continue;
                    }
                    borrowMedia(m);
                }
                clearBasket();
                
                refresher(); 

                system("afplay backup/Media/success.mp3 > /dev/null 2>&1 &");
                cout << "\033[8C" << highlightBlue << colorGreen << "Borrowed successfully!" << ansiReset << endl;
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
        cout << string(bold) << string(highlightBlue) << "== " << underline << fullName << "'s Borrowed Media" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl; // Personalized
        cout << "\n\033[8C";
        if(ownedMedia.empty()) {
            cout << "\033[8C" << colorRed << bold << string(highlightBlue) << "No media borrowed yet." << ansiReset << endl;
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
        string choiceStr;
        cout << "\n\033[8C" << string(highlightBlue) << ">> ";
        UI::input(choiceStr);
        cout << ansiReset;
        
        // Handle return
        if(choiceStr == "r" || choiceStr == "R") {
             // Return logic if simpler, but maybe select to return?
             // For now just view/open.
        }

        int choice = -1;
        try { choice = stoi(choiceStr); } catch(...) {}
        
        if(choice > 0 && choice <= (int)ownedMedia.size()) {
            auto selected = ownedMedia[choice-1];
            UI::clearInner();
            cout << string(bold) << string(highlightBlue) << "== " << underline << "Manage Item" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << "Price: " << selected->getPrice() << " MAD" << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << "1. Open/Read" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "2. Return to Library" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "3. Buy (Keep it)" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "0. Back" << ansiReset << endl;
            
            cout << "\n\033[8C" << string(highlightBlue) << ">> ";
            int action; UI::input(action);
            
            if(action == 1) {
                cout << "\n\033[8C" << highlightBlue << "Launching external viewer..." << ansiReset << endl;
                selected->openExternal();
                this_thread::sleep_for(chrono::seconds(1));
            } else if (action == 2) {
                returnMedia(selected);
                cout << "\n\033[8C" << highlightBlue << colorGreen << "Item returned." << ansiReset << endl;
                this_thread::sleep_for(chrono::seconds(1));
            } else if (action == 3) {
                 // Buy logic
                 addToPurchased(selected); // Add to purchased list
                 
                 // Remove from ownedMedia vector manually
                 for(auto it = ownedMedia.begin(); it != ownedMedia.end(); ++it) {
                    if((*it)->getTitle() == selected->getTitle()) {
                        ownedMedia.erase(it);
                        break;
                    }
                }
                // NOTE: We do NOT set isBorrowed=false, assuming buying implies taking it out of circulation?
                // Or does it mean "Copy Bought"? If it's digital, others can still borrow.
                // If it's physical, it's gone.
                // Let's assume Digital -> Available for others? 
                // Or Physical -> Gone?
                // The prompt says "buying them when loaning them". 
                // Let's assume for this system, if I buy it, I keep it, and maybe it stays borrowed/unavailable 
                // OR we make it available again? 
                // Let's keep it SIMPLE: Buying = Keeping a copy. availablity irrelevant for digital, 
                // but let's say it makes it available for others since I have my own copy now?
                // "returnMedia" logic sets borrowed=false.
                // Let's set borrowed=false so others can borrow the library copy.
                selected->setBorrowed(false); 
                
                cout << "\n\033[8C" << highlightBlue << colorGreen << "Item purchased for " << selected->getPrice() << " MAD!" << ansiReset << endl;
                cout << "\033[8C" << highlightBlue << "Thank you for your purchase." << ansiReset << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }
        }
    }

    void shopMediaType(vector<shared_ptr<Media>>& library, string type, function<void()> refresher) {
        refresher();

        UI::clearInner();
        vector<shared_ptr<Media>> filtered;
        for(auto& m : library) if(m->getType() == type) filtered.push_back(m);
        
        cout << string(bold) << string(highlightBlue) << "== " << string(underline) << "MediaForge's " << type << "s" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl;
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

    virtual void displayMenu(vector<shared_ptr<Media>>& library, vector<shared_ptr<User>>& users, function<void()> refresher) = 0;

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
    
    string getPurchasedString() const {
        if(purchasedMedia.empty()) return "";
        string res = email + "|";
        for(size_t i=0; i<purchasedMedia.size(); ++i) {
             res += purchasedMedia[i]->getTitle();
            if(i < purchasedMedia.size() - 1) res += "|";
        }
        return res;
    }
    
    void viewPurchasedMedia() {
        UI::clearInner();
        cout << string(bold) << string(highlightBlue) << "== " << underline << fullName << "'s Purchased Media" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl; // Personalized
        cout << "\n\033[8C";
        if(purchasedMedia.empty()) {
            cout << "\033[8C" << colorRed << bold << string(highlightBlue) << "No media purchased yet." << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << "Press Enter to go back..." << ansiReset;
            cin.ignore(); cin.get();
            cout << ansiReset;
            return;
        }
        
        for(size_t i=0; i<purchasedMedia.size(); ++i) {
             string t = purchasedMedia[i]->getTitle();
             cout << string(highlightBlue) << i+1 << ". " << left << setw(22) << t << " [Purchased]" << ansiReset << endl;
            cout << "\033[8C";
        }
        cout << ansiReset;
        cout << "\n\033[8C" << string(highlightBlue) << ">> Make selection to open OR [0] Back: ";
        int choice; UI::input(choice);
        
        if(choice > 0 && choice <= (int)purchasedMedia.size()) {
             cout << "\n\033[8C" << highlightBlue << "Opening..." << ansiReset << endl;
             purchasedMedia[choice-1]->openExternal();
             this_thread::sleep_for(chrono::seconds(1));
        }
    }

    void searchMedia(const vector<shared_ptr<Media>>& library) {
        UI::clearInner();
        cout << string(bold) << string(highlightBlue) << "== " << underline << "Searching Media" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl;
        string query;
        cout << "\n\033[8C" << string(highlightBlue) << "Search query: " << ansiReset;
        UI::inputLine(query);
        string lowerQuery = toLower(query);
        
        vector<shared_ptr<Media>> results;
        for(const auto& m : library) {
            if(toLower(m->getTitle()).find(lowerQuery) != string::npos) {
                results.push_back(m);
            }
        }
        
        cout << "\n\033[8C";
        if(results.empty()) {
             cout << colorRed << bold << string(highlightBlue) << "No matches found." << ansiReset << endl;
        } else {
             cout << string(highlightBlue) << "Found " << results.size() << " match(es):" << ansiReset << endl;
             cout << "\033[8C";
             for(size_t i=0; i<results.size(); ++i) {
                 cout << string(highlightBlue) << (i+1) << ". ";
                 results[i]->displayCompact();
             }
             
             cout << "\n\033[8C" << string(highlightBlue) << ">> [Add to Basket by Index] or [0] Back: " << ansiReset;
             int choice; UI::input(choice);
             if(choice > 0 && choice <= (int)results.size()) {
                 addToBasket(results[choice-1]);
             }
        }
        cout << ansiReset;
        if(results.empty()) {
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
    
    void sortMedia(vector<shared_ptr<Media>>& library) {
         // Sort by Title or Price
         UI::clearInner();
         cout << string(bold) << string(highlightBlue) << "== " << underline << "Sort Library" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl;
         cout << "\n\033[8C" << string(highlightBlue) << "1. By Title (A-Z)" << ansiReset << endl;
         cout << "\033[8C" << string(highlightBlue) << "2. By Price (Low->High)" << ansiReset << endl;
         cout << "\033[8C" << string(highlightBlue) << "0. Back" << ansiReset << endl;
         cout << "\n\033[8C" << string(highlightBlue) << ">> ";
         int choice; UI::input(choice);
         
         if(choice == 1) {
             sort(library.begin(), library.end(), [](const shared_ptr<Media>& a, const shared_ptr<Media>& b){
                 return a->getTitle() < b->getTitle();
             });
             cout << "\n\033[8C" << colorGreen << "Sorted by Title." << ansiReset << endl;
         } else if (choice == 2) {
             sort(library.begin(), library.end(), [](const shared_ptr<Media>& a, const shared_ptr<Media>& b){
                 return a->getPrice() < b->getPrice();
             });
             cout << "\n\033[8C" << colorGreen << "Sorted by Price." << ansiReset << endl;
         }
    }
};

class Client : public User {
public:
    Client(string e, string p, string fn, int a, string dob) 
        : User(e, p, fn, a, dob, "client") {}

    void displayMenu(vector<shared_ptr<Media>>& library, vector<shared_ptr<User>>& users, function<void()> refresher) override {
        int choice;
        cout << ansiReset;
        do {
            cout << ansiReset;
            UI::clearInner(); 
            cout << ansiReset;
            cout << ansiReset << string(bold) << string(highlightBlue) << "== Welcome Client: " << underline << fullName << ansiReset << string(bold) << string(highlightBlue) << " ==\n" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "1. Shop Books" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "2. Shop Videos" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "3. Shop Audios" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "4. Shop AudioBooks" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "5. Search Library" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "6. My Purchased Media" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "7. My Borrowed Media" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "8. View Basket" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "0. Log-out" << ansiReset << endl;
            cout << ansiReset;
            cout << "\n\033[8C" << string(highlightBlue) << ">> ";
            UI::input(choice);
            cout << ansiReset;
            switch (choice) {
                case 1: shopMediaType(library, "Book", refresher); break;
                case 2: shopMediaType(library, "Video", refresher); break;
                case 3: shopMediaType(library, "Audio", refresher); break;
                case 4: shopMediaType(library, "AudioBook", refresher); break;
                case 8: viewBasket(refresher); break;
                case 7: viewOwnedMedia(); break;
                case 5: searchMedia(library); break;
                case 6: viewPurchasedMedia(); break;
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
    
    void addUser(vector<shared_ptr<User>>& users) { // Simplified
        string e, p, fn, dob, r; int a;
        UI::clearInner(); 
        cout << string(bold) << string(highlightBlue) << "== " << underline << "Create User" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl; 
        cout << "\n\033[8C" << string(highlightBlue) << "E-mail: " << ansiReset; UI::input(e);
        for(auto& u : users) if(u->getEmail() == e) { return; }
        cout << string(highlightBlue) << "\033[8C" << "Password: " << ansiReset; UI::input(p); cin.ignore(); 
        cout << string(highlightBlue) << "\033[8C" << "Full Name: " << ansiReset; UI::inputLine(fn);
        cout << string(highlightBlue) << "\033[8C" << "Age: " << ansiReset; UI::input(a); 
        cout << string(highlightBlue) << "\033[8C" << "Date of Birth: " << ansiReset; UI::input(dob); 
        cout << string(highlightBlue) << "\033[8C" << "Role: " << ansiReset; UI::input(r);
        cout << ansiReset;
        
        if(r=="admin") users.push_back(make_shared<Admin>(e,p,fn,a,dob));
        else users.push_back(make_shared<Client>(e,p,fn,a,dob));
    }
    void deleteUser(vector<shared_ptr<User>>& users) {
         UI::clearInner(); string e; 
         cout << string(bold) << string(highlightBlue) << "== " << underline <<  "Delete User" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl;
         cout << "\n\033[8C" << string(highlightBlue) << "Enter User E-mail: " << ansiReset; UI::input(e); cout << ansiReset;
         for(auto it=users.begin();it!=users.end();++it) { if((*it)->getEmail()==e){ users.erase(it); return; } }
    }
    void editUser(vector<shared_ptr<User>>& users) {} // Stub
    void searchUser(const vector<shared_ptr<User>>& users) {} // Stub
    void showDatabase(const vector<shared_ptr<User>>& users) {
        UI::clearInner(); 
        cout << string(bold) << string(highlightBlue) << "== " << underline << "MediaForge's User Database" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl;
        
        cout << "\n\033[8C";
        for(size_t i=0; i<users.size(); ++i) {
             cout << string(highlightBlue) << (i+1) << ". " << users[i]->getFullName() << ansiReset << endl;
             cout << "\033[8C";
        }
        cout << "\n\033[8C" << string(highlightBlue) << "0. Back" << ansiReset << endl;

        cout << "\n\033[8C" << string(highlightBlue) << ">> ";
        int choice; UI::input(choice);
        
        if(choice > 0 && choice <= (int)users.size()) {
             auto target = users[choice-1];
             UI::clearInner();
             cout << string(bold) << string(highlightBlue) << "== " << underline << "MediaForge's User Database" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl;
             cout << "\n\033[8C" << string(highlightBlue) << string(underline) << "Full Name" << string(ansiReset) << string(highlightBlue) << ": " << target->getFullName() << ansiReset << endl;
             cout << "\033[8C" << string(highlightBlue) << string(underline) << "Role" << string(ansiReset) << string(highlightBlue) << ": " << target->getRole() << ansiReset << endl;
             cout << "\033[8C" << string(highlightBlue) << string(underline) << "E-mail" << string(ansiReset) << string(highlightBlue) << ": " << target->getEmail() << ansiReset << endl;
             cout << "\033[8C" << string(highlightBlue) << string(underline) << "Age" << string(ansiReset) << string(highlightBlue) << ": " << target->getAge() << ansiReset << endl;
             cout << "\033[8C" << string(highlightBlue) << string(underline) << "Date of Birth" << string(ansiReset) << string(highlightBlue) << ": " << target->getDateOfBirth() << ansiReset << endl;
             
             cout << "\n\033[8C" << highlightBlue << "Press Enter to go back..." << ansiReset;
             cin.ignore(); cin.get();
        }
        cout << ansiReset;
    }
    
    void menuUserManagement(vector<shared_ptr<User>>& users) {
        int choice;
        do {
            cout << ansiReset;
            UI::clearInner();
            cout << string(bold) << string(colorCyan) << string(highlightBlue) << "== " << underline << "User Management Portal" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << "1. Create User" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "2. Delete User" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "3. Show All Users" << ansiReset << endl;
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

    void showStatistics(const vector<shared_ptr<Media>>& library) {
        UI::clearInner();
        cout << string(bold) << string(highlightBlue) << "== " << underline << "MediaForge's Library Statistics" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl;
        
        int totalMedia = library.size();
        int videoCount = 0;
        int audioCount = 0;
        int bookCount = 0;
        long totalDuration = 0; // seconds
        
        for(const auto& m : library) {
            string type = m->getType();
            if(type == "Video") { videoCount++; totalDuration += m->getDuration(); }
            else if(type == "Audio") { audioCount++; totalDuration += m->getDuration(); }
            else if(type == "Book") { bookCount++; }
            else if(type == "AudioBook") { 
                bookCount++; audioCount++; // AudioBook counts as both? Or separate? 
                // Let's count as AudioBook mainly but check type string returns "AudioBook"
                // Actually getType returns "AudioBook".
                // Let's correct counts.
                bookCount--; audioCount--; // Revert
                // Just count as AudioBook
            }
        }
        
        // Count accurately
        videoCount=0; audioCount=0; bookCount=0; int abCount=0; totalDuration=0;
        for(const auto& m : library) {
            string t = m->getType();
            if(t == "Video") videoCount++;
            else if(t == "Audio") audioCount++;
            else if(t == "Book") bookCount++;
            else if(t == "AudioBook") abCount++;
            
            totalDuration += m->getDuration();
        }
        
        double avgDuration = (videoCount + audioCount + abCount) > 0 ? (double)totalDuration / (videoCount + audioCount + abCount) : 0;
        
        cout << "\n\033[8C" << string(highlightBlue) << "Total Media: " << totalMedia << ansiReset << endl;
        cout << "\033[8C" << string(highlightBlue) << "Books: " << bookCount << ansiReset << endl;
        cout << "\033[8C" << string(highlightBlue) << "Videos: " << videoCount << ansiReset << endl;
        cout << "\033[8C" << string(highlightBlue) << "Audios: " << audioCount << ansiReset << endl;
        cout << "\033[8C" << string(highlightBlue) << "AudioBooks: " << abCount << ansiReset << endl;
        cout << "\033[8C" << string(highlightBlue) << "Avg Duration (AV): " << fixed << setprecision(2) << (avgDuration/60.0) << " mins" << ansiReset << endl;
        
        cout << "\n\033[8C" << highlightBlue << "Press Enter to go back..." << ansiReset;
        cin.ignore(); cin.get();
        cout << ansiReset;
    }
    
    void exportReport(const vector<shared_ptr<Media>>& library, const vector<shared_ptr<User>>& users) {
        ofstream report("report.txt");
        report << "=== MediaForge's System Report ===" << endl;
        report << "Generated at: " << "2026-01-03" << endl << endl; // Mock date or use ctime
        
        report << "-- Library Status --" << endl;
        for(const auto& m : library) {
            report << m->getTitle() << " [" << m->getType() << "] - " << m->getPrice() << " MAD - " << (m->getIsBorrowed() ? "BORROWED" : "AVAILABLE") << endl;
        }
        
        report << "\n-- User Status --" << endl;
        for(const auto& u : users) {
            report << u->getEmail() << " (" << u->getRole() << ") - Borrowed: " << u->getOwned().size() << endl;
        }
        
        report.close();
        
        cout << "\n\033[8C" << highlightBlue << colorGreen << "Report exported to report.txt." << ansiReset << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    void menuMediaManagement(vector<shared_ptr<Media>>& library, const vector<shared_ptr<User>>& users) { // Added params
        int choice;
        do {
            UI::clearInner();
            cout << string(bold) << string(highlightBlue) << "== " << underline << "MediaForge's Media Management" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << "1. Manage Books" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "2. Manage Videos" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "3. Manage Audios" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "4. Manage AudioBooks" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "5. Statistics" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "6. Export Report" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "7. Sort Library" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "0. Back" << ansiReset << endl;
            cout << ansiReset;
            cout << "\n\033[8C" << string(highlightBlue) << ">> ";
            UI::input(choice);
            cout << ansiReset;
             switch(choice) {
                case 1: openManager("books"); break;
                case 2: openManager("videos"); break;
                case 3: openManager("audios"); break;
                case 4: openManager("audiobooks"); break;
                case 5: showStatistics(library); break;
                case 6: exportReport(library, users); break;
                case 7: sortMedia(library); break;
                case 0: break;
                default: 
                     cout << "\n\033[8C" << colorRed << bold << string(highlightBlue) << "Invalid choice." << ansiReset << endl;
                     this_thread::sleep_for(chrono::milliseconds(500));
                     break;
            }
        } while(choice != 0);       
    }
    
    void menuPersonal(vector<shared_ptr<Media>>& library, function<void()> refresher) {
         int choice;
        do {
            UI::clearInner();
            cout << string(bold) << string(highlightBlue) << "== " << underline << "Browsing as a Client" << ansiReset << string(bold) << string(highlightBlue) << " ==" << ansiReset << endl;
            cout << "\n\033[8C" << string(highlightBlue) << "1. Shop Books" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "2. Shop Videos" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "3. Shop Audios" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "4. Shop AudioBooks" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "5. Search Library" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "6. My Purchased Media" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "7. My Borrowed Media" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "8. View Basket" << ansiReset << endl;
            cout << "\033[8C" << string(highlightBlue) << "0. Back" << ansiReset << endl;
            cout << ansiReset;
            cout << "\n\033[8C" << string(highlightBlue) << ">> ";
            UI::input(choice);
             switch(choice) {
                case 1: shopMediaType(library, "Book", refresher); break;
                case 2: shopMediaType(library, "Video", refresher); break;
                case 3: shopMediaType(library, "Audio", refresher); break;
                case 4: shopMediaType(library, "AudioBook", refresher); break;
                case 5: searchMedia(library); break;
                case 6: viewPurchasedMedia(); break;
                case 7: viewOwnedMedia(); break;
                case 8: viewBasket(refresher); break;
                case 0: break;
                default: 
                     cout << "\n\033[8C" << colorRed << bold << string(highlightBlue) << "Invalid choice." << ansiReset << endl;
                     this_thread::sleep_for(chrono::milliseconds(500));
                     break;
            }
        } while(choice != 0); 
    }

    void displayMenu(vector<shared_ptr<Media>>& library, vector<shared_ptr<User>>& users, function<void()> refresher) override {
        int choice;
        do {
            cout << ansiReset;

            UI::clearInner();
            cout << string(bold) << string(highlightBlue) << "== Welcome Admin: " << underline << fullName << ansiReset << string(bold) << string(highlightBlue) << " ==\n" << ansiReset << endl;
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
                case 2: menuMediaManagement(library, users); break;
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
    vector<shared_ptr<User>> users;
    vector<shared_ptr<Media>> library;
    string userFile = "users.txt";
    string basketFile = "baskets.txt";
    string ownedFile = "owned.txt";
    string purchasedFile = "purchased.txt";

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
                    users.push_back(make_shared<Admin>(parts[1], parts[2], parts[3], stoi(parts[4]), parts[5]));
                } else {
                    users.push_back(make_shared<Client>(parts[1], parts[2], parts[3], stoi(parts[4]), parts[5]));
                }
            }
        }
        file.close();
    }
    
    void saveUsers() { ofstream f(userFile); for(const auto& u:users) f<<u->toString()<<endl; f.close(); }
    
    void scanDirectory(string path, string type) {
        if(!fs::exists(path)) fs::create_directory(path);
        for(const auto& entry : fs::directory_iterator(path)) {
            if(entry.is_regular_file()) {
                string fname = entry.path().filename().string();
                if(fname == ".DS_Store" || fname.substr(0, 1) == ".") continue;
                string title = entry.path().stem().string(); // Filename no ext
                string fpath = entry.path().string();
                
                bool exists = false;
                for(auto& m : library) if(m->getPath() == fpath) exists = true;
                if(exists) continue;

                if(type == "Book") library.push_back(make_shared<Book>(title, fpath));
                else if(type == "Video") library.push_back(make_shared<Video>(title, fpath));
                else if(type == "Audio") library.push_back(make_shared<Audio>(title, fpath));
                else if(type == "AudioBook") library.push_back(make_shared<AudioBook>(title, fpath));
            }
        }
    }

    void loadBaskets() {
        ifstream f(basketFile); string l;
        while(getline(f,l)){
             if(l.empty())continue; stringstream ss(l); string s; vector<string> p;
             while(getline(ss,s,'|')) p.push_back(s);
             if(p.size()>=2) {
                 string e=p[0]; shared_ptr<User> u=nullptr; for(auto& us:users) if(us->getEmail()==e) u=us;
                 if(u) for(size_t i=1;i<p.size();++i) for(auto& m:library) if(toLower(m->getTitle())==toLower(p[i])) u->addToBasket(m, true); 
             }
        }
        f.close();
    }
    void saveBaskets() { ofstream f(basketFile); for(auto& u:users) { string s=u->getBasketString(); if(!s.empty()) f<<s<<endl; } f.close(); }
    
    void loadOwned() {
        ifstream f(ownedFile); string l;
        while(getline(f,l)) {
            if(l.empty())continue; stringstream ss(l); string s; vector<string> p;
            while(getline(ss,s,'|')) p.push_back(s);
            if(p.size()>=2) {
                string e=trim(p[0]); shared_ptr<User> u=nullptr; for(auto& us:users) if(us->getEmail()==e) u=us;
                if(u) for(size_t i=1;i<p.size();++i) for(auto& m:library) if(toLower(m->getTitle())==toLower(trim(p[i]))) {
                    u->borrowMedia(m); // Updates status too
                }
            }
        }
        f.close();
    }
    
    void saveOwned() { ofstream f(ownedFile); for(auto& u:users) { string s=u->getOwnedString(); if(!s.empty()) f<<s<<endl; } f.close(); }

    void loadPurchased() {
        ifstream f(purchasedFile); string l;
        while(getline(f,l)) {
            if(l.empty())continue; stringstream ss(l); string s; vector<string> p;
            while(getline(ss,s,'|')) p.push_back(s);
            if(p.size()>=2) {
                string e=p[0]; shared_ptr<User> u=nullptr; for(auto& us:users) if(us->getEmail()==e) u=us;
                if(u) for(size_t i=1;i<p.size();++i) for(auto& m:library) if(toLower(m->getTitle())==toLower(p[i])) u->addToPurchased(m);
            }
        }
        f.close();
    }

    void savePurchased() { ofstream f(purchasedFile); for(auto& u:users) { string s=u->getPurchasedString(); if(!s.empty()) f<<s<<endl; } f.close(); }

public:
    System() {
        loadUsers();
        refreshDatabase(false); 
    }

    ~System() {
        saveBaskets(); saveOwned(); savePurchased(); saveUsers();
        // shared_ptr handles deletion
    }

    void refreshDatabase(bool saveFirst = true) {
        if(saveFirst) {
            saveBaskets();
            saveOwned();
            savePurchased();
        }

        // 1. Clear library
        library.clear();
        
        // 2. Rescan directories
        scanDirectory("books", "Book");
        scanDirectory("videos", "Video");
        scanDirectory("audios", "Audio");
        // AudioBooks might require a specific folder or just reuse others? 
        // For simplicity, let's look for "audiobooks" folder
        scanDirectory("audiobooks", "AudioBook");
        
        // 3. Reset user links
        for(auto& u : users) {
             u->clearBasket();
             u->clearOwned();
             u->clearPurchased();
        }
        
        // 4. Reload links from files
        loadBaskets();
        loadOwned();
        loadPurchased();
    }

    void run() {
        system("clear");
        cout << string(highlightGreen) << "\n\033[8C"  << "Press Enter to start..."<<ansiReset;
        cin.ignore();
        cout << ansiReset;
        system("clear");
        UI::bootScreen();
        
        while (true) {
            UI::clearInner(); 
            // Save & Reload state on every loop
            refreshDatabase(); 
            cout << ansiReset;
            cout << string(bold) << string(highlightBlue) << "== "<<underline<<"Login Portal"<<ansiReset<< string(bold) << string(highlightBlue)<<" ==" << ansiReset << endl;
            string email, password;
            cout << "\n\033[8C" << string(highlightBlue) << string(bold) << "Enter your E-mail: "<< "\n\033[8C" << ">> "; UI::input(email);
            if (email == "exit") break; 
            cout << "\n\033[8C" << string(highlightBlue) << string(bold) << "Enter your Password: "<< "\n\033[8C" << ">> ";
            UI::input(password);
            cout << ansiReset;

            shared_ptr<User> currentUser = nullptr;
            for (auto& u : users) {
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
        UI::slowPrint(string(bold) + string(highlightBlue) +  "<< Program Terminated." + ansiReset + "\n", 27);
        cout << "\n\033[8C";
        UI::slowPrint(string(bold) + string(highlightBlue) + string(underline) + "Credits" +string(ansiReset)+string(highlightBlue)+string(bold)+ " :" + string(ansiReset) + "\n", 15);
        cout << "\n\033[8C";
        UI::slowPrint(string(bold) + string(highlightBlue) + "► "+string(underline)+"Developers"+string(ansiReset)+string(highlightBlue)+string(bold)+" : Nizar EL IDRYSY, Nizar BTIRA"+string("\n\033[8C")+" & Hajar CHABLI."+string(ansiReset), 2);
        cout << "\n\n\033[8C";
        UI::slowPrint(string(bold) + string(highlightBlue) + "► "+string(underline)+"Year"+string(ansiReset)+string(highlightBlue)+string(bold)+" : 3IIRG3 EMSI-T." + string(ansiReset), 2);
        cout << "\n\n\033[8C";
        UI::slowPrint(string(bold) + string(highlightBlue) + "► "+string(underline)+"Project"+string(ansiReset)+string(highlightBlue)+string(bold)+" : MEDIAFORGE SYSTEM, vFinal-C++."+ string(ansiReset), 2);
        cout << "\n\n\033[8C";
        UI::slowPrint(string(bold) + string(highlightBlue) + "► "+string(underline)+"Date"+string(ansiReset)+string(highlightBlue)+string(bold)+" : 04 JAN 2026."+ string(ansiReset), 2);
        cout << "\n\n\033[8C";
        UI::slowPrint(string(bold) + string(highlightBlue) + "► "+string(underline)+"Jury"+string(ansiReset)+string(highlightBlue)+string(bold)+" : Mr. Youssef JDIDOU."+ ansiReset, 2);
        cout << "\033[12B"<< "\033[14C"<< "\n\033";
    }
};

int main() {
    System app;
    app.run();
    return 0;
}
