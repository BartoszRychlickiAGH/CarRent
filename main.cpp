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

void Register() {
    
    string in1{ "" }, in2{ "" }, name{ "" }, input{ "" }, surname{ "" }, s{}, ageIn{}; int age{}; bool contains{}, j{};
    string ;
    //brak wyœwietlania komunikatów o pustym inpucie podczas wprowadzania danych
    do {
        cout << "Enter name: ", cin >> name;
        if (name == s) { 
            cout << "You have to enter any name!" << endl;
        }
    } while (name==s);

    do {
        cout << "Enter surname: ", cin >> surname;
        if (surname == s) { 
            cout << "You have to enter any surname!" << endl;
        }
    } while (surname==s);

    do {
        do {
            
            cout << "Enter login: ",cin >> in1;
            if (in1 == s) { cout << "You have to enter any login!" << endl; }
        } while (in1 == s);
        if (Users.size() > 0) {
            for (int i = 0; i <= Users.size() - 1; i++) {

                if (Users[i].getLogin() == in1) {
                    contains = true;
                    cout << "Login already exist!" << endl;
                    cout << "Enter different login" << endl;
                }
                else {
                    contains = false;
                }
            }
        }
        do {
            cout << "Enter password: ", cin >> in2; cout << endl;
            if (regex_match(in2,regex("[ \t]"))){ //nie dzia³a wypisywanie na ekran
                cout << "You have to enter any password!" << endl; 
            }
        } while (regex_match(in2, regex("[ \t]")));
        
    } while (contains == true);
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
        
        
    } while (age < 18 || age > 100 || (j == 1));
    cout << "Registered!" << endl;

    User client(name, surname, in1, in2, age);
    Users.push_back(client);

}
int findUserInColl(string p_login) {
    int l{ 0 };
    for (int i = 0; i <= Users.size()-1; ++i) {
        if (Users[i].getLogin() == p_login) {
            l = i;
        }
    }
    return l;
}

int main(){
    Admin Ad1("Bartosz", "Rychlicki", "Admin1", "Admin1", 20, "key");
    Users.push_back(Ad1);
    string path{ "dataVehicle.txt" };
    fstream fileVehicles{path};
    
    //fileVehicles.open(path, ios::out);
    if (!fileVehicles.is_open()) {
        cout << "Something went wrong while terminating loading data!\nPlease restart!" << endl;
        return -1;
    }
    else {
        string s{ "" }, x{ "" }; vector<string>words{"NULL","NULL" ,"NULL" ,"NULL" ,"NULL" ,"NULL" ,"NULL" };
        int n{};
        for (int j = 1; j <= 20;j++) {
            if (!fileVehicles.eof()) {
                getline(fileVehicles, s,';');
                n = 0;
                for (int i = 0; i <= s.size()-1; ++i) {
                    if (s[i] == ',') {
                        words[n]=x;
                        x = {""};
                        n++;
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
    }

  
    string input{ "" }, input1{ "" };

    while (true) {
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
        int n = stoi(input);
        switch (n) { // logging in module
        case 1:
            if (Users.size() == 0) {
                cout << "The are no accounts!" << endl;
                break;
            }
            do {
                cout << "Enter login: ", cin >> input, cout << endl << "Enter password: ", cin >> input1, cout << endl;
                if (input == "" || input1 == "") { cout << "You have to enter login and password!" << endl; }
            } while (input == "" || input1 == "");

            if (Login(input, input1)) {
                cout << "Logged in" << endl;
                int k{ findUserInColl(input) };

                //przekierowanie do interfejsu admina
                Users[k].Interface();
            }
            else {
                cout << "Entered wrong login or password!" << endl;
            }
            cout << endl;

            break;
        case 2: // registering module
            Register();
            cout << endl;
            break;
        case 3: // exit module
            cout << "Exiting..." << endl;
            return 0;
            break;
        default: // module which launch when user enter unexpected input value 
            cout << "Entered wrong action!\nChoose correct action!" << endl;
            continue;
            break;
        }
};
    fileVehicles.close();
    return 0;
}
