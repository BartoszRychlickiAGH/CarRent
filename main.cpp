// dopisaæ interfejs admina i clienta -> pliki nag³ówkowe
// napisaæ klasê rezerwacji(karta rezerwacyjna): bêdzie posiadaæ date pocz¹tku i koñca rezerwacji oraz informacje o pojeŸdzie -> bêdzie ona dziedziczona przez klasê User i 

#include "vehicle.h"
#include "user.h"
#include "including.h"


bool Login(string p_Login,string p_Password){
    for (int i = 0; i <= Users.size() - 1; i++) {
        if (p_Login == Users[i].getLogin()) {
            if (p_Password == Users[i].getPassword()) {
                return true;
            }
        }
    }

    return false;
}

int findUserInColl(string p_login) { // find position of given user in collection of users
    int l{ 0 };
    for (int i = 0; i <= Users.size()-1; ++i) {
        if (Users[i].getLogin() == p_login) {
            l = i;
        }
    }
    return l;
}
void Register(string name,string surname, string login,string password, int age); //prototype of registering function
void insertIntoString(string& s,string &result) {
    for (int i=0; i <= s.size()-1; ++i) {
        result.push_back(s[i]);
    }
}
int main() {

    string in1{ "" }, in2{ "" }, input{ "" }, input1{ "" }, s{}, ageIn{}; int age{}, j{}; bool contains{false}; /* name, surname, login, password, age,
    variable which will be checking if login already exist in collection,j - indicator which is used while checking if user didn't enter int value */
    Admin Ad1("Bartosz", "Rychlicki", "Admin1", "Admin1", 21, "key");
    string path{ "dataVehicle.txt" }; // path to vehicles' data
    fstream fileVehicles{ path }; // file in which contains a collection of vehicles' data
    string pathUsers{ "DataUsers.txt" }; // path to users' data
     // file in which contains a collection of users' data
    ifstream fileUsersIn{ pathUsers };
    Users.push_back(Ad1);

    if (!fileVehicles.is_open() || !fileUsersIn.is_open()){
        return -1;
    }
    else {
        string s{ "" }, x{ "" }; // s - variable where whole line will be stored in reading vehicles' data, 
        // string_Users - variable where whole line will be stored in reading users' data, x - variable where each character will be stored in reading vehicles' data
        // y - variable where each character will be stored in reading users' data

        vector<string>words{ "NULL","NULL" ,"NULL" ,"NULL" ,"NULL" ,"NULL" ,"NULL" }; // collections of each info of vehicle and user
        int n{};//variable where user's input will be stored while choosing action in main interface
        //char c{};
         //usun¹æ przecinki i przeczytaæ artyku³na dc + .cpp -> definicje funkcji + usun¹æ z plików nag³ówkowych funkcje itp
        for (int z = 0; z <= 19; z++) {
            if (!fileVehicles.eof()) {
                getline(fileVehicles, s);
                n = 0;

                for (int i = 0; i <= s.size() - 1; ++i) {
                    if (s[i] == ',') {
                        words[n] = x;
                        x = { "" };
                        n++;
                    }
                    else if (s[i] == ';') {
                        break;
                    }
                    else {
                        x.push_back(s[i]);
                    }
                }
                Vehicle car(words[0], words[1], words[2], words[3], words[4], words[5], words[6]);
                Vehicles.push_back(car);
                //Load data from file and create new object of vehicle 
            }
        }
        
         // jakoœ naprawiæ
        while (true) {
            fileUsersIn >> s; //testing...
            if (fileUsersIn.eof()) { break; continue; }
            //getline(fileUsers, s, ';');
            n = 0;x = ""; for (int i = 0; i <= words.size() - 1; ++i) { words[i] = "NULL"; };
            for (int i = 0; i <= s.size() - 1; ++i) {
                if (s[i] == ',') {
                    words[n] = x;
                    x = { "" };
                    n++;
                }
                else if (s[i] == ';') { break; continue; }
                else {
                    x.push_back(s[i]);
                }

            }
            User client(words[0], words[1], words[2], words[3], stoi(words[4]));
            Users.push_back(client);
        };
        
    }

    fileUsersIn.close();
    ofstream fileUsersOut{ pathUsers };
    if (!fileUsersOut.is_open()) {
        cout << "Failed in loading data!\nTry again" << endl;
        return -1;
    }



    while (true) {
        cout << endl;
        cout << "Choose action: " << endl;
        cout << "1.Sign in" << endl;
        cout << "2.Sign up" << endl;
        cout << "3.Exit" << endl;
        do {
            cin >> input;
            if (input != "1" && input != "2" && input != "3") {
                cout << "Entered wrong input!" << endl;
            }
        } while (input != "1" && input != "2" && input != "3");
        int n{ stoi(input) }; // input given by user
        switch (n) { // logging in module
        case 1:
            do {
                cout << "Enter login: ", cin >> input, cout << endl << "Enter password: ", cin >> input1, cout << endl;
                if (regex_match(input, regex("^$")) || regex_match(input1, regex("^$"))) { cout << "You have to enter login and password!" << endl; }
            } while (regex_match(input, regex("^$")) || regex_match(input1, regex("^$")));

            if (Login(input, input1)) {
                cout << "!Logged in!" << endl;
                int k{ findUserInColl(input) };

                //przekierowanie do interfejsu admina
                if (input == "Admin1") {
                    Ad1.InterfaceAdmin();
                }
                
            }
            else {
                cout << "Entered wrong login or password!" << endl;
            }
            cout << endl;

            break;
        case 2: // registering module
            
            cout <<endl<< "Do not enter blank input!" << endl<<endl;
            //brak wyœwietlania komunikatów o pustym inpucie podczas wprowadzania danych
            do {
                cout << "Enter name: ", cin >> in1;
                if (regex_match(in1,regex( "^$"))) {
                    cout << "You have to enter any name!" << endl;
                }
            } while (regex_match(in1,regex("^$")));
            //system("color red");
            do {
                cout << "Enter surname: ", cin >> in2;
                if (regex_match(in2, regex("^$"))) {
                    cout << "You have to enter any surname!" << endl;
                }
            } while (regex_match(in2,regex("^$")));

            do {
                contains = false;
                cout << "Enter login: ", cin >> input;
                if (regex_match(input,regex("^$"))) { cout << "You have to enter any login!" << endl; }
                
                if (Users.size() > 1) {
                    for (int i = 0; i <= Users.size() - 1; i++) {

                        if (Users[i].getLogin() == input) {
                            contains = true;
                            cout << "Login already exist!" << endl;
                            cout << "Enter different login!\n" << endl;
                            break;
                        }
                        
                    }
                }

            }while (contains || input=="");
             do{
                 cout << "Enter password: ", cin >> input1; cout << endl << endl;;
                if (regex_match(input1, regex("^$"))) { //nie dzia³a wypisywanie na ekran
                    cout << "You have to enter any password!" << endl;
                }
             }while (regex_match(input1, regex("^$")));
            do {
                // wyj¹tek na string
                cout << "Enter age: ";
                cin >> ageIn;
                if (regex_match(ageIn, regex("[0-90-9]*"))) {
                    age = stoi(ageIn);
                    cout << endl;
                    j = 0;
                    if (age < 18 || age > 100) {
                        cout << "Unnacceptable age!" << endl;
                    }
                }
                else {
                    cout << "Given input is a string and not a number!" << endl;
                    j = 1;
                }


            } while (age < 18 || age > 100 || j == 1);
            cout << "Registered!" << endl;
            
            Register(in1, in2, input, input1, stoi(ageIn));
            s = "";
            insertIntoString(in1, s), s.push_back(','), insertIntoString(in2, s), s.push_back(','),
            insertIntoString(input, s), s.push_back(','), insertIntoString(input1, s), s.push_back(','), insertIntoString(ageIn, s),
            s.push_back(','), s.push_back(';'),s.push_back('\n');
            fileUsersOut << s;
            //fileUsers.write(s.c_str(),s.size()); // cannot save s to fileUsers
            
            cout << endl;
            break;
        case 3: // exit module
            cout <<endl<< "Exiting..." << endl << endl;
            return 0;
            break;
        default: // module which launch when user enter unexpected input value 
            cout << "Entered wrong action!\nChoose correct action!" << endl;
            //continue;
            break;
        }
    };
    fileVehicles.close(), fileUsersOut.close();
    return 0;
}

void Register(string name, string surname, string login, string password, int age) {
    User client(name, surname, login, password, age);
    Users.push_back(client);    
}