#ifndef USER_HPP_
#define USER_HPP_
#include "including.h"
#include "vehicle.h"
#include "reservation.h"

class User : public Vehicle{
	private:
		string name{""}, surname{""}, login{""}, password{""};
		int age{ 0 };  string Key{"0"};
	public: 
		vector<Reservation>reservationsHistory{}; // history of reservations
		//konstruktor
		User(string p_name = "Didn't set", string p_surname = "Didn't set", string p_login = "Didn't set",string p_password="Didn't set",int p_age=0):
		name(p_name),surname(p_surname),login(p_login),password(p_password),age(p_age){}

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
		string getKey(void) const{
			return Key;
		}		void History(Reservation &booking) {
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

		virtual void Interface() {
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
						
					}
				} while (!regex_match(n_string, regex("[1-6]")));
				n = stoi(n_string);
				if (n == 1) {
					Print();
				}
				else if (n == 2) {
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
						Reservation reserv(startingMonth, startingDay, endingMonth, endingDay,k);
						reservationsHistory.push_back(reserv);
						cout << endl << "Reservation made! Thank you!" << endl;
					}
					else {
						cout << "Chosen vehicle is actually reserved in given data!" << endl;
					}
					
				}
				else if (n == 3) {
					if (reservationsHistory.size() == 0) {
						cout << "There's no reservations made!" << endl;
					}
					else {
						for (auto i = reservationsHistory.begin(); i != reservationsHistory.end(); ++i) {
							i->Print(); cout << endl;
						}
					}
				}
				else if (n == 4) {
					if (reservationsHistory.size() == 0) {
						cout << "You haven't made any reservation!" << endl;
					}
					else {
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


class Admin : public User {
	private:
		string Key{""}; // klucz uprawniaj¹cy do wykonywania ró¿nych akcji z poziomu administratora
	public:
		Admin(string p_name, string p_surname, string p_login,string p_password, int p_age,string p_key) :User(p_name,p_surname,p_login,p_password,p_age),Key(p_key) {}
		virtual void Interface() {
			cout << "Admin interface terminated!" << endl;
		}
};

vector<User>Users{}; // collection of users <Login,Password>

#endif 

