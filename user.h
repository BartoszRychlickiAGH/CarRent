#ifndef USER_HPP_
#define USER_HPP_
#include "including.h"
#include "vehicle.h"
#include "reservation.h"

class User : public Vehicle{
	private:
		string name{""}, surname{""}, login{""}, password{""},Key{"0"};
		int age{ 0 }, ban{0};
	public: 
		vector<Reservation>reservationsHistory{}; // history of reservations
		//konstruktor
		User(string p_name = "Didn't set", string p_surname = "Didn't set", string p_login = "Didn't set",string p_password="Didn't set",int p_age=0,int p_ban=0):
			name(p_name), surname(p_surname), login(p_login), password(p_password), age(p_age),ban(p_ban) {
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
		void History(Reservation& booking) {
			reservationsHistory.push_back(booking);
		}
		

		//gettery pól
		string getName(void){
			return name;
		}
		string getSurname(void) const{
			return surname;
		}
		string getLogin(void) const{
			return login;
		}
		string getPassword(void) const{
			return password;
		}
		int getAge(void) const{
			return age;
		}
		int getBan(void) const{ 
			return ban;
		}
		string getKey(void) const{
			return Key;
		}
		
		virtual void Print() {
			cout << "1. Name: " << getName() << "\n2. Surname: " << getSurname() << "\n3. Login: " << getLogin() << "\n4. Age : " << getAge() << endl;
		}
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
			string n_string{ "" }; int n{}; // indicators which point an action chosen by user
			string strDay{}, strMonth{}, dueDay{}, dueMonth{}; // variables which will store admin input
			string k_in{};
			
			int k{ 1 };
			int sD{}, sM{ }, dD{ }, dM{ }; // variables which will be changing date of reservation
			bool validation{};//variable which will be checking if admin entered correct input

			while (true)
			{
				cout << "\nChoose action: " << endl; 
				cout << "1.User info\n2.New reservation\n3.CurrentReservations\n4.Cancel Reservation\n5.Vehicles available\n6.Log out" << endl;
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
							PrintVehicles(), cout << endl << "Chosen number of vehicle: ", cin >> k_in; cout << endl;
							if (!regex_match(k_in, regex("[0-90-9]+"))) { validation = false; cout << "Entered incorrect input! Enter number between 1-20" << endl << endl; }
							else if (stoi(k_in) > 20 || stoi(k_in) < 1) { validation = false; cout << "Entered wrong number of vehicle!" << endl << endl; }
							else { validation = true; }
						} while (!validation);
						k = stoi(k_in);
						--k;
						
						do {
							cout << "Enter starting month: ", cin >> strMonth;
							if (!regex_match(strMonth, regex("[1-91-9]+"))) {
								cout << "Entered invalid input!\nEnter only numbers" << endl;
								validation = false;
							}
							else {
								sM = stoi(strMonth);
								if (sM < 1 || sM>12) {
									validation = false;
									cout << "Entered incorrect inout value! Mind to enter number between 1-12!" << endl << endl;
								}
								else {
									validation = true;
								}
							}
							
						} while (!validation);
						do {
							cout << "Enter starting day: ", cin >> strDay;
							if (!regex_match(strDay, regex("[1-90-1]+"))) {
								cout << "Entered invalid input!\nEnter only numbers" << endl;
								validation = false;
							}
							else {
								sD = stoi(strDay);
								if (sD < 32) {
									if (sM == 2 && sD < 29) {
										validation = true;
									}
									else if ((sM == 4 || sM == 6 || sM == 9 || sM == 11) && sD < 31) {
										validation = true;
									}
									else if ((sM == 1 || sM == 3 || sM == 5 || sM == 7 || sM == 8 || sM == 10 || sM == 12)&&sD<32) {
										validation = true;
									}
									else {
										cout << "Entered incorrect number of day in given month!" << endl;
										validation = false;
									}
								}
								else {
									cout << "Entered bad input value! Mind to enter number between 1-31" << endl;
									validation = false;
								}
							}
						} while (!validation);

						do {
							cout << "Enter ending month: ", cin >> dueMonth;
							if (!regex_match(dueMonth, regex("[1-91-9]+"))) {
								cout << "Entered invalid input!\nEnter only numbers" << endl;
								validation = false;
							}
							else {
								dM = stoi(dueMonth);
								if (dM >= sM) {
									if (dM < 1 || dM>12) {
										validation = false;
										cout << "Entered incorrect input value! Mind to enter number between 1-12!" << endl << endl;
									}
									else {
										validation = true;
									}
								}
								else {
									cout << "Number of chosen ending month is fewer than number of starting month! Try again!" << endl;
									validation = false;
								}
							}
							
						} while (!validation);
						do {
							cout << "Enter ending day: ", cin >> dueDay;
							if (!regex_match(dueDay, regex("[0-90-9]+"))) {
								cout << "Entered invalid input!\nEnter only numbers!" << endl;
								validation = false;
							}
							else {
								dD = stoi(dueDay);
								if (dM == sM && dD < sD) {
									validation = false;
									cout << "Given number of ending day is fewer than number of starting month!\n\n";
								}
								else {
									if (dD < 32 && dD>0) {
										if (dM == 2 && dD < 29) {
											validation = true;
										}
										else if ((dM == 4 || dM == 6 || dM == 9 || dM == 11) && dD < 31) {
											validation = true;
										}
										else if ((dM == 1 || dM == 3 || dM == 5 || dM == 7 || dM == 8 || dM == 10 || dM == 12)) {
											validation = true;
										}
										else {
											cout << "Entered incorrect number of day in given month!" << endl;
											validation = false;
										}

									}
									else {
										cout << "Entered bad inout value! Mind to enter number between 1-31" << endl;
										validation = false;
									}
								}
							}
							
						} while (!validation); // variables which will store admin input
						sM--; dD--; sD--; dM--; // decrementing variables to match with index of array
						if (Vehicles[k].isReserved(sM, sD, dM, dD)) {
							Reservation reserv(sM, sD, dM, dD, k); // wrzuciæ metody i konstruktor klasy reservation aby user przechowywa³ wektor rezerwacji
							reservationsHistory.push_back(reserv);
							cout << endl << "Reservation made! Thank you!" << endl;
						}
						else {
							cout << "\nChosen vehicle is actually reserved or under maintace given data!\n" << endl;
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

						}
						else {
							int j{ 1 };
							do{
								
								cout << "Choose reservatiion to cancel: " << endl;
								for (auto i = reservationsHistory.begin(); i != reservationsHistory.end(); ++i) {
									cout << "----------------------------------------" << endl << j << ":" << endl;
									i->Print(); cout << endl;
									j++;
								}
								cin >> j;
								j--;
							}while (j >= reservationsHistory.size());

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
		Admin(string p_name, string p_surname, string p_login, string p_password, int p_age, string p_key) :User(p_name, p_surname, p_login, p_password, p_age), Key(p_key) { setBan(0); }
		
		void ChangeUserData(int k) {
			int n{}, j{}; string s{}; // n - variable to store age and indicator of action on user's data
			while (true) {
				cout << "Choose data to change: " << endl;
				Users[k].Print(), cout << "5. Exit" << endl , cin >> n;
				
				if (n == 1) {//change name
					do {
						cout << "Enter name: ", cin >> s; cout << endl;
						if (regex_match(s, regex("^$"))) {
							cout << "You have to enter any name!" << endl;
						}
					} while (regex_match(s, regex("^$")));
					Users[k].setName(s);
				}
				else if (n == 2) {//change surname
					do {
						cout << "Enter surname: ", cin >> s;
						if (regex_match(s, regex("^$"))) {
							cout << "You have to enter any surname!" << endl;
						}
					} while (regex_match(s, regex("^$")));
					Users[k].setSurname(s);
				}
				else if (n == 3) {//change login
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
				}
				else if (n == 4) {//change age
					do {
						cout << endl << "Enter age: ", cin >> s;
						if (regex_match(s, regex("[0-90-9]+"))) {
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
				}
				else if (n == 5) {
					cout << "Exiting..." << endl;
					break;
				}
				else {
					cout << "Entered bad value! Mind to enter between 1-6!" << endl;
					continue;
					break;
				}
				
			}
		}
		void InterfaceAdmin() {
			while (true) {
				int n{ 0 }, k{ 0 }, b{ 1 }; string decision{},input; // n - variable to choose sepcified module, k - variable to point exact user or vehicle, which admin wants to manage
				do{//cout << "Admin interface terminated!"<<endl<<"Under constructions!" << endl;
					cout << "\nChoose action!" << endl;
					cout << "1. Admin's info" << endl;
					cout << "2. Manage user" << endl;
					cout << "3. Manage vehicle" << endl;
					cout << "4. Log out" << endl;
					cin >> input;
					if (!regex_match(input, regex("[1-4]+"))) { cout << "\nEntered incorrect input value! Enter only number between 1-4!\n\n"; }
				} while (!regex_match(input,regex("[1-4]+")));
				
				n = stoi(input);
				
				if (n == 1) {
					 //1. Admin info -> Print()
					 Print();
				}
				else if (n == 2) {	//2. Manage user 
					 do {
						 cout << "Choose user: " << endl; ;//choose user to manage
						 cout << "-------------------------------------------" << endl;
						 for (auto i = Users.begin(); i != Users.end(); ++i) {
							 cout << b << ": " << endl; b++;
							 i->Print();
							 cout << "-------------------------------------------" << endl;
						 }cout << endl;
					 
						cin >> k; cout << endl; k--;
						if (k > Users.size() - 1) { cout << "Entered too high number!\n" << endl; }
					 } while (k>Users.size()-1);
					 cout << "\nChoose Action on User: " << endl << "1. Print or change data\n2. Manage user's reservations\n3. Ban user\n4. Unban user\n5. Delete user" << endl
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
						
						decision = "Yes"; // decision variable which will be used to manage reservations
						while (regex_match(decision,regex("[Yy]es"))) {
							if (Users[k].reservationsHistory.size() > 0) {
								int j = 0;
								do {

									cout << "Choose reservation to manage: " << endl;
									j = 0;
									for (auto i = Users[k].reservationsHistory.begin(); i != Users[k].reservationsHistory.end(); ++i) {

										cout << "--------------------------------" << endl;
										j++; cout << j << ": " << endl;//print reservations

										i->Print(), cout << endl;
									}cout << "--------------------------------" << endl;
									cin >> j; j--;
									if (j > Users[k].reservationsHistory.size() - 1) { cout << "Entered wrong numnber! Try again!\n\n"; }
								} while (j > Users[k].reservationsHistory.size() - 1);

								Users[k].reservationsHistory[j].Manage(k, j);

								int g = Users[k].reservationsHistory[j].getMDecision(); // g is a variable which will store admin's decision of if he deleted reservation

								if (g == 3) {
									Users[k].reservationsHistory[j].~Reservation();
									Users[k].reservationsHistory.erase(Users[k].reservationsHistory.begin() + j);
								}
								cout << endl << "Do you want to manage another reservation?" << endl;
								cin >> decision;
								cout << endl;
							}
							else {
								cout << "\nThere's no reservations to manage!\n\n";
								break;
							}
						};
						break;
					 case 3:	//3. Block user's access
						 Users[k].setBan(1);
						 cout << "\nAccount banned!\n" << endl;
						 break;
					 case 4:	//4. Unblock user's access
						 Users[k].setBan(0);
						 cout << "\nAccount unbanned!\n" << endl;
						 break;
					 case 5://5. Delete user
						 //deleting user data from file
						 
						 Users[k].~User();
						 Users.erase(Users.begin() + k);
						 cout << "\nAccount deleted!\n" << endl;
						 break;
					 default:
						 cout << "Entered bad input value! Remember to enter number between 1-5!" << endl;
						 break;
					 }
				}
				else if (n == 3) {
					 //cout << "Under construction" << endl;//3. Manage vehicle's -> Choose vehicle ->
					 int n{}; string n_in, k_in; bool validation{ true };
					 do { 
						 PrintVehicles();
						 cout << endl;
						 cin >> k_in;
						 if (!regex_match(k_in, regex("[0-90-9]+"))) { cout << "Entered type of input! Enter only numbers!" << endl << endl; validation = false; }
						 else if (stoi(k_in) < 1 || stoi(k_in) > 20) { cout << "\nEntered wrong number of vehicle! Enter number between 1-20!\n\n"; validation = false; }
						 else { validation = true; }
					 } while (!validation);
					 
					 n = stoi(k_in);
					 n--;
					 while (true) {
						 do {
							 cout << "\nChoose action: " << endl;
							 cout << "1. Change vehicle info!" << endl;
							 cout << "2. Turn status to 'in maintance'!" << endl;
							 cout << "3. Turn status to 'available" << endl;
							 cout << "4. Delete vehicle" << endl;
							 cout << "5. Exit" << endl;
							 cin >> n_in; cout << endl << endl;
							 if (!regex_match(n_in, regex("[1-5]+"))) { cout << "Entered wrong input value! Mind to enter number between 1-5\n" << endl; }
						 } while (!regex_match(n_in, regex("[1-5]+")));
						 
						 if (n_in == "4") { // 4. Delete vehicle
							 Vehicles.erase(Vehicles.begin() + n);
							 break;
						 }
						 else if (n_in == "5") {//5. Exit
							 cout << "\nExiting...\n";
							 break;
						 }
						 else {
							 Vehicles[n].Manage(n_in);
						 }
						 

					 }
				}
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

