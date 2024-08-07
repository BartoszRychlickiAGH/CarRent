//Header file with class Vehicle and methods which are responsible for managing vehicles
#ifndef VEHICLE_HPP_
#define VEHICLE_HPP_
#include "including.h"



class Vehicle{
private:
	string brand{ "" };//marka
	string model{ "" };//model
	string gearbox{ "" };//skrzynia bieg�w
	string engine{ "" };//silnik
	string condition{ "" };//stan 
	string type{ "" };// typ pojazdu
	string category{ "" };// klasa pojazdu
	float price{ 0.0 };//cena za wynajem [per day]
	vector <vector<bool>>Cal; // representing and calendar, vector of 12 vector, where each vector has different size
	int DaysTotal{};
	

public:
	// getters and setters
	void setCondition(string p_condition) { condition = p_condition; }// setStan
	void setPrice(float p_price = 0.0) { price = p_price; }
	void setBrand(string p_brand) { brand = p_brand; }
	void setModel(string p_model) { model = p_model; }
	void setCategory(string p_category) { category = p_category; }
	void setEngine(string p_Engine) { engine = p_Engine; }
	void setGearBox(string p_gearbox) { gearbox = p_gearbox; }
	void setType(string p_type) { type = p_type; }

	string getModel(void)const { return model; }
	string getBrand(void)const { return brand; }
	string getCategory(void)const { return category; }
	string getEngine(void)const { return engine; }
	string getGearBox(void)const { return gearbox; }
	string getType(void)const { return type; }
	string getCondition(void) { return condition; }// getStan
	int getDaysTotal(void) const { return DaysTotal; }
	float getprice()const { return price; }
	//constructor
	Vehicle(string p_brand = "Didn't set", string p_model = "Didn't set", string p_gearbox = "Didn't set",
		string p_engine = "Didn't set", string p_condition = "Didn't set", string p_type = "Didn't set", 
		string p_category = "Didn't set") :brand(p_brand), model(p_model), gearbox(p_gearbox), engine(p_engine), condition(p_condition),
		type (p_type), category(p_category)
	{
		
		//setting correct price base on class of vehicle and his condition
		if (p_category == "Luxury") {
			setPrice(300);
		}
		else if(p_category=="Rare") {
			setPrice(200);
		}
		else {
			setPrice(100);
		}
		if (p_condition == "Good") {
			setPrice(getprice() * 0.75);
		}
		else if (p_condition == "Bad") {
			setPrice(getprice() * 0.5);
		}
		//building calendar
		for (int i = 0; i <= 11; ++i) {
			if (i == 0 || i == 2 || i == 4 || i == 6 || i == 7 || i == 9 || i == 11) {
				vector<bool>Days;
				for (int j = 0; j <= 30; j++) {
					Days.push_back(true);
				}
				Cal.push_back(Days);
			}
			else if (i == 1) {
				vector<bool>Days;
				for (int j = 0; j <= 28; j++) {
					Days.push_back(true);
				}
				Cal.push_back(Days);
			}
			else {
				vector<bool>Days{};
				for (int j = 0; j <= 29; j++) {
					Days.push_back(true);
				}
				Cal.push_back(Days);
			}
		}
	}//konstruktor
	//Printing value of field of object
	virtual void Print()const {
		cout << "Brand: " << brand << endl;
		cout << "Model: " << model << endl;
		cout << "Class: " << category << endl;
		cout << "Engine: " << engine << endl;
		cout << "Gearbox: " << gearbox << endl;
		cout << "Type: " << type << endl;
		cout << "Price [per day]: " << price << endl;
	}// void Print
	

	bool isReserved(int strMonth, int strDay, int dueMonth, int dueDay) { // bool function, which returns if exact vehicle is reservaed in given date
		vector <bool> check;
		if (strMonth <= dueMonth) {
			for (int i = strDay - 1; i <= Cal[strMonth].size() - 1; i++) {//Cal
				/*if (Cal[strMonth][i] == true) {
					return true;
				}*/
				check.push_back(Cal[strMonth][i]);
			}
			for (int i = 0; i <= dueDay - 1; i++) {
				/*if (Cal[dueMonth][i] == true) {
					return true;
				}*/
				check.push_back(Cal[dueMonth][i]);
			}
			if ((dueMonth - strMonth) >= 2) {
				for (int i = dueMonth - strMonth - 1; i <= dueMonth - 1; i++) {
					for (int j = 0; j <= Cal[i].size() - 1; ++j) {
						/*if (Cal[i][j] == true)
							return true;*/
						check.push_back(Cal[i][j]);
					}
				}
			}
		}
		/*return false;*/
		for (int i = 0; i <= check.size() - 1; ++i) {
			if (check[i] == false) {
				return false;
			}
		}
		return true;

	}

	int reservingCalendar(int strMonth, int strDay, int dueMonth, int dueDay) { //  int functon which set an false to reserv vehicle in given date, also return how many days user reserved an vehicle
		if (strMonth < dueMonth) {
			for (int i = strDay - 1; i <= Cal[strMonth].size() - 1; i++) {
				Cal[strMonth][i] = false;
				DaysTotal++;
			}
			for (int i = 0; i <= dueDay - 1; i++) {
				Cal[dueMonth][i] = false;
				DaysTotal++;
			}
			if ((dueMonth - strMonth) >= 2) {
				for (int i = dueMonth - strMonth - 1; i <= dueMonth - 1; i++) {
					for (int j = 0; j <= Cal[i].size() - 1; ++j) {
						Cal[i][j] = false;
						DaysTotal++;
					}
				}
			}
		}
		else if (strMonth == dueMonth) {
			if (strDay <= dueDay) {
				for (int i = strDay; i <= dueDay; ++i) {
					Cal[strMonth][i] = false;
					DaysTotal++;
				}
			}
			else { cout << "Starting number of day can't be bigger than number of ending day"<<endl; }
		}
		else {
			cout << "Number of starting month can't be larger than number of ending month!" << endl;
		}
		return DaysTotal;
	}
	void deleteReservationCal(int strMonth, int strDay, int dueMonth, int dueDay) {// void function which turns false into true in order to cancel reservation in given date
		if (strMonth <= dueMonth) {
			for (int i = strDay - 1; i <= Cal[strMonth].size() - 1; i++) {
				Cal[strMonth][i] = true;
			}
			for (int i = 0; i <= dueDay - 1; i++) {
				Cal[dueMonth][i] = true;
			}
			if ((dueMonth - strMonth) >= 2) {
				for (int i = dueMonth - strMonth - 1; i <= dueMonth - 1; i++) {
					for (int j = 0; j <= Cal[i].size() - 1; ++j) {
						Cal[i][j] = true;
					}
				}
			}
		}
		else {
			cout << "Entered wrong start month or due month!" << endl;
		}
		DaysTotal = 0;
	}
	
	virtual void Manage(string n_in) { // virtual function whic is an subinterface,it's launched when admin wants to change a field of exact vehicle
		system("cls"); // cleaning terminal
		string strMonth{}, strDay{}, dueMonth{}, dueDay{}; bool validation{}; // variables where wille be stored an exact date in order to change reservation date, validation - to store if given condition is true or false
		int sM{}, sD{}, dM{}, dD{}; // variables which will be storing informations about date in which there will be vehicles's mainatnce or end of maitance
			
		if (n_in == "1") { //1. Vehicle's info and if required, changing data
			string input{""}; // variable which will store an number of action hich user chose
			while (true) {
				do {

					cout << "\nChoose action: " << endl;
					cout << "1. Change brand name" << endl;
					cout << "2. Change model name" << endl;
					cout << "3. Change class" << endl;
					cout << "4. Change engine" << endl;
					cout << "5. Change gearbox" << endl;
					cout << "6. Change condition" << endl;
					cout << "7. Change price" << endl;
					cout << "8. Exit" << endl;
					cin >> input;
					cout << endl;
					if (!regex_match(input, regex("[1-8]+"))) { cout << "invalid input! Enter number between 1-8!" << endl; }
				} while (!regex_match(input, regex("[1-8]+")));

				if (input == "1") { // Change brand name
					do {
						cout << "Enter brand name: ", cin >> input, cout << endl;
						if (!regex_match(input, regex("^[A-Za-z]+$"))) { cout << "Entered wrong input value" << endl; }
						// cheking if admin entere brand's name which exist IRL
					} while (!regex_match(input, regex("^[A-Za-z]+$")));
					setBrand(input);
					cout << endl << "Vehicle's brand name changed" << endl;
				}
				else if (input == "2") { // Change model name
					do {
						cout << "Enter model name: ", cin >> input, cout << endl;
						if (!regex_match(input, regex("^[A-Za-z0-9]+$"))) { cout << "Entered wrong input value" << endl; }
					} while (!regex_match(input, regex("^[A-Za-z0-9]+$")));
					setModel(input);
					cout << endl << "Vehicle's model name changed" << endl;
				}
				else if (input == "3") { // Change class
					do {
						validation = true;
						cout << "Enter class name: ";
						cin >> input, cout << endl;
						if (!regex_match(input, regex("^[A-Za-z]+$"))) { cout << "Entered wrong input value" << endl; validation = false; }
						if (input != "Common" && input != "Luxury" && input != "Rare") { validation = false; cout << "Entered wrong input value!\n Enter one of these classes: Common, Rare, Luxury" << endl; }
						// cheking if admin entere brand's name which exist IRL
					} while (!validation);
					setCategory(input);
					cout << endl << "Vehicle's class changed" << endl;
				}
				else if (input == "4") { // Change engine
					do {
						validation = true;
						cout << "Enter engine: ";
						cin >> input; cout << endl;
						if (!regex_match(input, regex("^[A-Za-z.0-9]+$"))) { cout << "Entered wrong input value" << endl; validation = false; }
						// cheking if admin entere brand's name which exist IRL
					} while (!validation);
					setEngine(input);
					cout << endl << "Vehicle's engine changed" << endl;
				}
				else if (input == "5") { // Change gearbox
					do {
						validation = true;
						cout << "Enter gearbox: ";
						cin >> input, cout << endl;
						if (!regex_match(input, regex("^[A-Za-z]+$"))) { cout << "Entered wrong input value" << endl; validation = false; }
						if (input != "Automatic" && input != "Manual") { validation = false; cout << "Entered wrong input value!\n Enter one of these gearboxes: Automatic, Manual" << endl; }
						// cheking if admin entere brand's name which exist IRL
					} while (!validation);
					setGearBox(input);
					cout << endl << "Vehicle's gearbox changed" << endl;
				}
				else if (input == "6") { // Change condition
					do {
						validation = true;
						cout << "Enter condition: ";
						cin >> input, cout << endl;
						if (!regex_match(input, regex("^[A-Za-z]+$"))) { cout << "Entered wrong input value" << endl; validation = false; }
						if (input != "Bad" && input != "Excellent" && input != "Good") { validation = false; cout << "Entered wrong input value!\n Enter one of these conditions: Bad, Good, Excellent" << endl; }
						// cheking if admin entere brand's name which exist IRL
					} while (!validation);
					setCondition(input);
					cout << endl << "Vehicle's condition changed" << endl;
				}
				else if (input == "7") { // Change price
					do {
						cout << "Enter new price: ";
						cin >> input, cout << endl;
						if (!regex_match(input, regex("[0-9]+$"))) { cout << "Entered not a number! Mind to enter only numbers while changing vehicle's price!" << endl; };
					} while (!regex_match(input, regex("[0-9]+$")));
					setPrice(stoi(input));
					cout << endl << "Vehicle's price changed" << endl;
				}
				else if (input == "8") { // Exit
					cout << "Exiting..." << endl;
					break;
				}
			};
		}
		else if (n_in == "2" || n_in == "3") {//2. Turn avability of vehicle to "in maintance" or "available"
			do{
				cout << "Enter date: " << endl;
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
						if (sD < 32 && sD>0) {
							if (sM == 2 && sD < 29) {
								validation = true;
							}
							else if ((sM == 4 || sM == 6 || sM == 9 || sM == 11) && sD < 31) {
								validation = true;
							}
							else if (sM == 1 || sM == 3 || sM == 5 || sM == 7 || sM == 8 || sM == 10 || sM == 12) {
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
								cout << "Entered bad input value! Mind to enter number between 1-31" << endl;
								validation = false;
							}
						}
					}
				} while (!validation);
				if (n_in == "3") {
					if (isReserved(sM, sD, dM, dD)) {
						cout << "There was no mainatnce in given date!" << endl << endl; validation = false;

					}
					else {
						validation = true;
					}
				}
				else if (n_in == "2") {
					if (!isReserved(sM, sD, dM, dD)) {
						validation = false; cout << "Vehicle already in use at this date!\n\n";
					}
					else {
						validation = true;
					}
				}
			}while (!validation);
			if (n_in == "2") {
				reservingCalendar(sM, sD, dM, dD);
				cout << "\nChanged status to 'in maintenance!'" << endl;
			}
			else {
				deleteReservationCal(sM,sD,dM,dD);
				cout << "\nChanged status to 'available!'" << endl;
			}
		}
		else {
			cout << "Entered wrong number! Try again!" << endl;
		}
		
	}
	~Vehicle() {};
	
};



vector<Vehicle>Vehicles;// collection of vehicles
void PrintVehicles() { // function which displays and information of all vehicles in vector of vehicles
	if (Vehicles.size() >= 1) {
		int j{ 1 };
		cout << "--------------------------------------------------------------------------------" << endl;
		for (int i = 0; i <= Vehicles.size() - 1; ++i) {
			cout << endl << j << ":" << endl, j++;
			Vehicles[i].Print(), cout << "\n--------------------------------------------------------------------------------";
		}
	}
	else {
		cout << "There is no vehicles in database!" << endl;
	}
}
#endif