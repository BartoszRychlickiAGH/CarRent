#ifndef USER_HPP_
#define USER_HPP_
#include "including.h"
#include "vehicle.h"
#include "reservation.h"

class User /*: public Vehicle*/{
	private:
		string name{""}, surname{""}, login{""}, password{""},Key{"0"};
		int age{ 0 }, ban{0};
	public: 
		vector<Reservation>reservationsHistory{}; // history of reservations
		//konstruktor
		User(string p_name = "Didn't set", string p_surname = "Didn't set", string p_login = "Didn't set",string p_password="Didn't set",int p_age=0):
			name(p_name), surname(p_surname), login(p_login), password(p_password), age(p_age) {
			ban = 0;
		}

		//settery pól
		void setName(string p_name = "Didn't set") {
			name = p_name;
		}
		void setSurname(string p_surname="Didn't set") {
			surname = p_surname;
		}
		void setLogin(string p_login = "Didn't set") {
			login = p_login;
		}
		void setPassword(string p_password = "Didn't set") {
			password = p_password;
		}
		void setAge(int p_age = 0) {
			age = p_age;
		}
		void setBan(int p_ban) {
			ban = p_ban;
		}
		virtual void Print() {
			cout << "Name: " << getName() << "\nSurname: " << getSurname() << "\nLogin: " << getLogin() << "\nAge: " << getAge() << endl;
		}

		//gettery pól
		string getName(void)const {
			return name;
		}
		string getSurname(void)const {
			return surname;
		}
		string getLogin(void)const {
			return login;
		}
		string getPassword(void)const {
			return password;
		}
		int getAge(void) const{
			return age;
		}
		int getBan(void) const { 
			return ban;
		}
		string getKey(void) const{
			return Key;
		}
		void History(Reservation &booking) {
			reservationsHistory.push_back(booking);
		}
		//void Make a reservation

		void deleteHistory() {
			int j{ 0 }; string k{};
			cout << "Choose reservation to cancel: " << endl;
			for (int i = 0; i <= reservationsHistory.size() - 1; i++) {
				cout << "-------------------------------------------------------------" << endl << i + 1 << ":" << endl;
				reservationsHistory[i].Print();
			}
			cout << endl, cin >> k,j=stoi(k),--j, reservationsHistory[j].~Reservation(), reservationsHistory.erase(reservationsHistory.begin()+j);
		}

		void Interface() {
			string n_string{ "" }; int n{};
			while (true)
			{
				//zabezpieczenie przed nieprzewidzianym inputem
				int k{ 1 }, startingMonth{}, startingDay{}, endingMonth{}, endingDay{};
				

				cout << "Choose action: " << endl; 
				cout << "1.User info\n2.New reservation\n3.CurrentReservations\n4.Cancel Reservation\n5.vehicles available\n6.Log out" << endl;
				do {
					cin >> n_string;
					if (!regex_match(n_string, regex("[1-6]"))) {
						cout << "Entered bad input value! Mind to entered number from 1-6!" << endl;
					}
				} while (!regex_match(n_string, regex("[1-6]")));
				n = stoi(n_string);
				if (n == 1) {
					Print();
				}
				else if (n == 2) {
					if (getBan()==0) {
						cout << "Choose a vehicle: " << endl;

						do {
							PrintVehicles(), cout << endl << "Chosen number of vehicle: ", cin >> k; cout << endl;

							cout << "Enter a number of month you want to start your reservation of chosen car" << endl, cin >> startingMonth, cout << endl;
							cout << "Enter a number of day in chosen month you want to start your reservation of chosen car" << endl, cin >> startingDay, cout << endl;
							cout << "Enter a number of month you want to end your reservation of chosen car" << endl, cin >> endingMonth, cout << endl;
							cout << "Enter a number of day in chosen month you want to start your reservation of chosen car" << endl, cin >> endingDay, cout << endl;

							if (startingMonth < 1 || startingMonth>12) {
								cout << "Entered wrong value of starting month!" << endl;
							}
							if (endingMonth < 1 || endingMonth>12) {
								cout << "Entered wrong value of ending month!" << endl;
							}
							if (startingDay < 1 || startingDay>31) {
								cout << "Entered wrong value of starting day!" << endl;
							}
							if (endingDay < 1 || endingDay>31) {
								cout << "Entered wrong value of ending day!" << endl;
							}
							if (k < 1 || k>20) {
								cout << "Entered wrong number of vehicle!" << endl;
							}

						} while ((startingMonth < 1 || startingMonth>12) || (endingMonth < 1 || endingMonth>12) || (startingDay < 1 || startingDay>31)
							|| (endingDay > 31 || endingDay < 1) || (k > 20 || k < 1));

						if (Vehicles[k - 1].isReserved(startingMonth, startingDay, endingMonth, endingDay)) {
							Reservation reserv(startingMonth, startingDay, endingMonth, endingDay, k); // wrzuciæ metody i konstruktor klasy reservation aby user przechowywa³ wektor rezerwacji
							reservationsHistory.push_back(reserv);
							cout << endl << "Reservation made! Thank you!" << endl;
						}
						else {
							cout << "Chosen vehicle is actually reserved or under maintace given data!" << endl;
						}
					}
					else {
						cout << endl << "!Your account has been banned! For more information contact admin!" << endl << endl;
					}
					
				}
				else if (n == 3) {
					if (getBan() == 0) {
						if (reservationsHistory.size() == 0) {
							cout << "There's no reservations made!" << endl;
						}
						else {
							for (auto i = reservationsHistory.begin(); i != reservationsHistory.end(); ++i) {
								i->Print(); cout << endl;
							}
						}
					}
					else {
						cout << endl << "!Your account has been banned! For more information contact admin!" << endl << endl;
					}
				}
					else if (n == 4) {
						if(getBan() == 0){
							if (reservationsHistory.size() == 0) {
								cout << "You haven't made any reservation!" << endl;

							}else {
								int j{ 1 };
								cout << "Choose reservatiion to cancel: " << endl;
								for (auto i = reservationsHistory.begin(); i != reservationsHistory.end(); ++i) {
									cout << "----------------------------------------" << endl << j << ":" << endl;
									i->Print(); cout << endl;
									j++;
								}
								cin >> j;
								j--;
								string s{};
								cout << "Enter a confition of a vehicle of which reservation you want to end! Enter good, bad or excellent! " << endl;
								cin >> s; reservationsHistory[j].getVehicle().setCondition(s);
								reservationsHistory[j].getVehicle().deleteReservationCal(reservationsHistory[j].getStrMonth(), reservationsHistory[j].getStrDay(), reservationsHistory[j].getDueMonth(), reservationsHistory[j].getDueDay());
								reservationsHistory[j].~Reservation();
								reservationsHistory.erase(reservationsHistory.begin() + j);
							}
						}
						else {
							cout << endl << "!Your account has been banned! For more information contact admin!" << endl << endl;
						}
					}
				else if (n == 5) {
					PrintVehicles();
				}
				else if (n == 6) {
					cout << "Logging out..." << endl;
					
					break;
				}
			}
		}

		~User() { /* destuktor */ }
};
vector<User>Users{}; // collection of users <Login,Password>

class Admin : public User {
	private:
		string Key{""}; // klucz uprawniaj¹cy do wykonywania ró¿nych akcji z poziomu administratora
	public:
		Admin(string p_name, string p_surname, string p_login,string p_password, int p_age,string p_key) :User(p_name,p_surname,p_login,p_password,p_age),Key(p_key) {}
		
		void ChangeUserData(int k) {
			int n{}, j{}; string s{}; // n - variable to store age and indicator of action on user's data
			while (true) {
				cout << "Choose data to change: " << endl;
				Users[k].Print(), cout << endl << "Exit" << endl , cin >> n;
				switch (n)
				{
				case 1://change name
					do {
						cout << "Enter name: ", cin >> s;
						if (regex_match(s, regex("^$"))) {
							cout << "You have to enter any name!" << endl;
						}
					} while (regex_match(s, regex("^$")));
					Users[k].setName(s);
					break;
				case 2://change surname
					do {
						cout << "Enter surname: ", cin >> s;
						if (regex_match(s, regex("^$"))) {
							cout << "You have to enter any surname!" << endl;
						}
					} while (regex_match(s, regex("^$")));
					Users[k].setSurname(s);
					break;
				case 3://change login
					do {
						j = false;
						cout << "Enter login: ", cin >> s;
						if (regex_match(s, regex("^$"))) { cout << "You have to enter any login!" << endl; }

						if (Users.size() > 1) {
							for (int i = 0; i <= Users.size() - 1; i++) {

								if (Users[i].getLogin() == s) {
									j = true;
									cout << "Login already exist!" << endl;
									cout << "Enter different login!\n" << endl;
									break;
								}

							}
						}

					} while (j || s == "");
					setLogin(s);
					break;
				case 4://change password
					do {
						cout << "Enter password: ", cin >> s; cout << endl << endl;;
						if (regex_match(s, regex("^$"))) { //nie dzia³a wypisywanie na ekran
							cout << "You have to enter any password!" << endl;
						}
					} while (regex_match(s, regex("^$")));
					Users[k].setPassword(s);
					break;
				case 5://change age
					do{
						cout << endl << "Enter age";
						cin >> n;
						if (regex_match(s, regex("[0-90-9]*"))) {
							n = stoi(s);
							cout << endl;
							j = 0;
							if (n < 18 || n > 100) {
								cout << "Unnacceptable age!" << endl;
							}
						}
						else {
							cout << "Given input is a string and not a number!" << endl;
							j = 1;
						}

					} while (n < 18 || n > 100 || j == 1);
					Users[k].setAge(n);
					break;
				case 6:
					cout << "Exiting..." << endl;
					break;

				default:
					cout << "Entered bad value! Mind to enter between 1-6!" << endl;
					continue;
						break;
					}
			}
		}
		void InterfaceAdmin() {
			 while (true) {
				 //cout << "Admin interface terminated!"<<endl<<"Under constructions!" << endl;
				 cout << "Choose action!" << endl;
				 cout << "1. Admin's info" << endl;
				 cout << "2. Manage user" << endl;
				 cout << "3. Manage vehicle" << endl;
				 cout << "4. Log out" << endl;
				 int n{ 0 }, k{ 0 }, b{ 1 }; string decision{}; cin >> n; // n - variable to choose sepcified module, k - variable to point exact user or vehicle, which admin wants to manage
						
				 if (n == 1) {
					 //1. Admin info -> Print()
					 Print();
				 }
				 else if (n == 2) {	//2. Manage user's 

					 cout << "Choose user: " << endl; ;//choose user to manage
					 cout << "-------------------------------------------" << endl;
					 for (auto i = Users.begin(); i != Users.end(); ++i) {
						 cout << b << ": " << endl; b++;
						 i->Print();
						 cout << "-------------------------------------------" << endl;
					 }cout << endl;
					 cin >> k; cout << endl; k--;
					 cout << "Choose Action on User: " << endl << "1. Print or change data\n2. Manage user's reservations\n3. Block user\n4. Unblock user\n5. Delete user" << endl
						 , cin >> n;
					 switch (n) {
					 case 1:
						 Users[k].Print(); cout << endl;//1. User's info and if required, changing data

						 do {
							 cout << endl;
							 cout << "Do you want to change data?" << endl, cin >> decision;
							 if (!regex_match(decision, regex("[Yy]es")) && !regex_match(decision, regex("[Nn]o"))) { cout << "Entered bad value! Mind  to enter only yes or no!" << endl << endl; }
						 } while (!regex_match(decision, regex("[Yy]es")) && !regex_match(decision, regex("[Nn]o")));

						 if (regex_match(decision, regex("[Yy]es"))) {
							 ChangeUserData(k);
						 }
						 break;
					 case 2:	//2. Manage user's reservations
						 while (true) {
							 cout << "Choose reservation to manage: " << endl;
							 int j = 0;
							 for (auto i = Users[k].reservationsHistory.begin(); i != Users[k].reservationsHistory.end(); ++i) {
								 cout << "--------------------------------" << endl;
								 j++; cout << j << ": " << endl;//print reservations
								 i->Print(), cout << endl;
							 }cout << "--------------------------------" << endl;
							 cin >> j;


							 // outer function
						 }
						 break;
					 case 3:	//3. Block user's access
						 Users[k].setBan(1);
						 break;
					 case 4:	//4. Unblock user's access
						 Users[k].setBan(0);
						 break;
					 case 5://5. Delete user
						 Users[k].~User();
						 Users.erase(Users.begin() + k);
						 break;
					 default:
						 cout << "Entered bad input value! Remember to enter number between 1-5!" << endl;
						 break;
					 }
				 }
				 else if (n == 3) {
					 cout << "Under construction" << endl;//3. Manage vehicle's -> Choose vehicle ->
										//1. Vehicle's info and if required, changing data
										//2. Turn avability of vehicle to "in maintance"
										//3. Turn avability of vehicle to "available"
				 }						//4. Delete vehicle
				 else if (n == 4) {
					 //4. Log out
					 cout << "Loging out..." << endl;
					 break;
				 }else{
					 cout << endl << "Entered bad input! Mind to choose number between 1-4!" << endl;
				 }
			 }
		 }
};

#endif 

