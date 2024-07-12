// CarRental.cpp : This file contains the 'main' function. Program execution begins and ends there. The author of this project is Bartosz Rychlicki.
#include "vehicle.h"
#include "user.h"
#include "including.h"


bool Login(string p_Login,string p_Password){
	for (int i = 0; i <= Users.size() - 1; i++) { // iterating through the whole vector of users
		if (p_Login == Users[i].getLogin()) { // checking if inputed login is simmilar to the one got in the exact iteration
			if (p_Password == Users[i].getPassword()) { // similar thing which was checked in the previous  step with login
				return true;
			}
		}
	}

	return false;
}

int findUserInColl(string p_login) { // find position of given user in collection of users
	int l{ 0 }; // variable which will be returned as index of User in vector of users
	for (int i = 0; i <= Users.size()-1; ++i) {
		if (Users[i].getLogin() == p_login) {
			l = i; // if given input is simmilar to the one got in iteration then overwrite variable l 
		}
	}
	return l; // return index of user in vector os users
}
void Register(string name,string surname, string login,string password, int age,int ban); //prototype of registering function

string insertIntoString(string& s,string &result) {
	for (int i = 0; i <= result.size() - 1; ++i) {
		s.push_back(result[i]); // push_back every character from result to the s variable
	}

	return s; // return s which is and sum of previous value of s and result
}
int main() {

	string in1{ "" }, in2{ "" }, input{ "" }, input1{ "" }, s{}, ageIn{}; int age{}, j{}; bool contains{false}; /* name, surname, login, password, age,
	variable which will be checking if login already exist in collection,j - indicator which is used while checking if user didn't enter int value */
	Admin Ad1("Bartosz", "Rychlicki", "Admin", "Admin", 21, "key");
	string path{ "dataVehicle.txt" }; // path to vehicles' data
	ifstream fileVehiclesIn{ path }; // file in which contains a collection of vehicles' data, it will be used to load data of vehicles
	string pathUsers{ "DataUsers.txt" }; // path to users' data
	ifstream fileUsersIn{ pathUsers }; // file which contains data of users, it will be used to load data into vector of users
	Users.push_back(Ad1);

	if (!fileVehiclesIn.is_open() || !fileUsersIn.is_open()){
		return -1;
	}
	else {
		string s{ "" }, x{ "" }; // s - variable where whole line will be stored in reading vehicles' and users' data,
		// x - variable where each character will be stored in reading users' and vehicles' data suc as name, surname and so on

		vector<string>words{ "NULL","NULL" ,"NULL" ,"NULL" ,"NULL" ,"NULL" ,"NULL" }; // collections of each info of vehicle and user
		int n{};//variable where user's input will be stored while choosing action in main interface

		while(!fileVehiclesIn.eof()) {
			if (!fileVehiclesIn.eof()) {
				getline(fileVehiclesIn, s, ';');
				if (s.size() > 0) {
					n = 0; //setting to overwrite data in correct order

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
					Vehicle car(words[0], words[1], words[2], words[3], words[4], words[5], words[6]); //creating an object of vehicles
					Vehicles.push_back(car); // saving object to vector of vehicles
					//Module of Loading data from file and create new object of vehicle 
				}
			}
			else {
				break;
			}
		}
		
	   //Module located below this commment is simmilar to the previous module of loading data of vehicles
		while (true) {
			getline(fileUsersIn, s, ';');
			if (fileUsersIn.eof()) { break; continue; }
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
			User client(words[0], words[1], words[2], words[3], stoi(words[4]),stoi(words[5]));
			Users.push_back(client);
		};
		
	}

	fileUsersIn.close();
	ofstream fileUsersOut{ pathUsers }; // Opening an file to overwrite data in this file, to upload changes made by admin or users
	if (!fileUsersOut.is_open()) {
		cout << "Failed in loading data!\nTry again" << endl; // Checking if file was opened in correct way
		return -1;
	}
	fileVehiclesIn.close();
	ofstream fileVehiclesOut{path}; // Opening an file to overwrite data in this file, to upload changes made by admin or users
	if (!fileVehiclesOut.is_open()) {
		cout << "Failed in loading data!\nTry again" << endl; // Checking if file was opened in correct way
		return -1;
	}
	

	while (true) {

		cout << endl;
		cout << "Choose action: " << endl; // Main interface
		cout << "1.Sign in" << endl;
		cout << "2.Sign up" << endl;
		cout << "3.Exit" << endl;
		do {
			cin >> input; // Selecting action
			if (input != "1" && input != "2" && input != "3") { // checking if user entered wrong number
				cout << "Entered wrong input!" << endl;
			}
		} while (input != "1" && input != "2" && input != "3");
		int n{ stoi(input) }; // input given by user, conversion from string data type to integer
		system("cls"); // cleaning terminal
		 
		if (n == 1){ // logging in module
			do {
				// below we can notice and checking if inputed login and password are blank
				cout << "Enter login: ", cin >> input, cout << endl << "Enter password: ", cin >> input1, cout << endl;
				if (regex_match(input, regex("^$")) || regex_match(input1, regex("^$"))) { cout << "You have to enter login and password!" << endl; }
			} while (regex_match(input, regex("^$")) || regex_match(input1, regex("^$")));

			if (Login(input, input1)) { // checking of there is an inputed login and if yes, then checking if password is correct
				cout << "!Logged in!" << endl;
				int k{ findUserInColl(input) }; // getting an index of user in vector of users
				cout << endl;
				Sleep(500); // freezing for 0.5s to display an communication before cleaning terminal
				//przekierowanie do interfejsu admina
				if (input == "Admin") { // checking if entered login is and admin's login
					Ad1.InterfaceAdmin(); // terminating admin interface
				}
				else {
					Users[k].Interface(); //terminating user interface
				}

			}
			else {
				cout << "Entered wrong login or password!" << endl;
			}
			cout << endl;
		}
		else if (n == 2) { // registering module

				cout << endl << "Do not enter blank input!" << endl << endl;
				//brak wyœwietlania komunikatów o pustym inpucie podczas wprowadzania danych
				do {
					cout << "Enter name: ", cin >> in1;
					if (in1 == "") {
						cout << "You have to enter any name!" << endl;
					}
				} while (regex_match(in1, regex("^$"))); // checking if entered input is blank
				//system("color red");
				do {
					cout << "Enter surname: ", cin >> in2;
					if (regex_match(in2, regex("^$"))) {
						cout << "You have to enter any surname!" << endl;
					}
				} while (regex_match(in2, regex("^$"))); // checking if entered input is blank

				do {
					contains = false;
					cout << "Enter login: ", cin >> input;
					if (regex_match(input, regex("^$"))) { cout << "You have to enter any login!" << endl; }

					if (Users.size() > 1) {
						for (int i = 0; i <= Users.size() - 1; i++) {

							if (Users[i].getLogin() == input) { // checking if an similar login already exists
								contains = true;
								cout << "Login already exist!" << endl;
								cout << "Enter different login!\n" << endl;
								break;
							}

						}
					}

				} while (contains || input == "");
				do {
					cout << "Enter password: ", cin >> input1; cout << endl << endl;;
					if (regex_match(input1, regex("^$"))) { // unfortunately it doesn't work, but it was built to display info in case of entering blank inout
						cout << "You have to enter any password!" << endl;
					}
				} while (regex_match(input1, regex("^$"))); // checking if user enter blank inout
				do {
					// wyj¹tek na string
					cout << "Enter age: ";
					cin >> ageIn;
					if (regex_match(ageIn, regex("[0-90-9]*"))) { // regex checks if user entered an number, if not program displays information and make user to try again
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
				system("cls");
				cout << "Registered!" << endl;
				Sleep(500); // pausing program to display an communication that user just registered new account (because next step is cleaning terminal by system("cls"))
				Register(in1, in2, input, input1, stoi(ageIn),0); // launching registering function

				//fileUsers.write(s.c_str(),s.size()); // cannot save s to fileUsers

				cout << endl;
					
		}
		else if (n == 3) { // exit module
			system("cls"); // cleaning terminal
			cout << endl << "Exiting..." << endl << endl;
			if (Users.size() > 1) { // only write users' data to file
				for (int i = 1; i <= Users.size() - 1; i++) {
					string s{ "" }, text{ "" }, x{ "" };  //s and x are variables which will be uploaded to contain an line of data of user, text is and variable to store different fields of user, for example, name, surname and the rest
					text = Users[i].getName();
					s = insertIntoString(x, text); s.push_back(',');
					x = s;

					text = Users[i].getSurname();
					s = insertIntoString(x, text); s.push_back(',');
					x = s;

					text = Users[i].getLogin();
					s = insertIntoString(x, text); s.push_back(',');
					x = s;

					text = Users[i].getPassword();
					s = insertIntoString(x, text); s.push_back(',');
					x = s;

					text = to_string(Users[i].getAge());
					s = insertIntoString(x, text); s.push_back(',');
					x = s;

					text = to_string(Users[i].getBan());
					s = insertIntoString(x, text); s.push_back(','); s.push_back(';'); //s.push_back('\n');
					x = s;

					//cout << x << endl;
					fileUsersOut << x; // putting line (name,surname,login,password,age,banIndicator,;) into file
				}
			}    //LOADING TO VEHICLES' FILE
			for (int i = 1; i <= Vehicles.size() - 1; i++) {
				
				string s{ "" }, text{ "" }, x{ "" }; //s and x are variables which will be uploaded to contain an line of data of vehicle, text is and variable to store different fields of vehicles, for example, brand name, model name and the rest 
				text = Vehicles[i].getBrand();
				s = insertIntoString(x, text); s.push_back(',');
				x = s;

				text = Vehicles[i].getModel();
				s = insertIntoString(x, text); s.push_back(',');
				x = s;

				text = Vehicles[i].getGearBox();
				s = insertIntoString(x, text); s.push_back(',');
				x = s;

				text = Vehicles[i].getEngine();
				s = insertIntoString(x, text); s.push_back(',');
				x = s;

				text = Vehicles[i].getCondition();
				s = insertIntoString(x, text); s.push_back(',');
				x = s;

				text = Vehicles[i].getType();
				s = insertIntoString(x, text); s.push_back(',');
				x = s;

				text =Vehicles[i].getCategory();
				s = insertIntoString(x, text); s.push_back(','); s.push_back(';');// s.push_back('\n');
				x = s;

				//cout << x << endl;
				fileVehiclesOut << x; // putting data of Vehicle into file
			}
			break;
		}
		else { // module which will launch when user enter unexpected input value 
			cout << "Entered wrong action!\nChoose correct action!" << endl;
			continue;
		}
	};
	
	fileVehiclesOut.close(), fileUsersOut.close(); // closing and overwriting files
	return 0;
}

void Register(string name, string surname, string login, string password, int age,int ban) {
	User client(name, surname, login, password, age,ban); // create an object of user
	Users.push_back(client);    // put new user to vector of users
}