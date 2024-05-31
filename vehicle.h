#ifndef VEHICLE_HPP_
#define VEHICLE_HPP_
#include "including.h"



class Vehicle{
private:
	string brand{ "" };//marka
	string model{ "" };//model
	string gearbox{ "" };//skrzynia biegów
	string engine{ "" };//silnik
	string condition{ "" };//stan 
	string type{ "" };// typ pojazdu
	string category{ "" };// klasa pojazdu
	float price{ 0.0 };//cena za wynajem [per day]
	vector <vector<bool>>Cal;
	int DaysTotal{};
	

public:
	float getprice()const { return price; }
	void setPrice(float p_price = 0.0) {
		price = p_price;
	}
	

	Vehicle(string p_brand = "Didn't set", string p_model = "Didn't set", string p_gearbox = "Didn't set",
		string p_engine = "Didn't set", string p_condition = "Didn't set", string p_type = "Didn't set", 
		string p_category = "Didn't set") :brand(p_brand), model(p_model), gearbox(p_gearbox), engine(p_engine), condition(p_condition),
		type (p_type), category(p_category)
	{
		

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

	virtual void Print()const {
		cout << "Brand: " << brand << endl;
		cout << "Model: " << model << endl;
		cout << "Class: " << category << endl;
		cout << "Engine: " << engine << endl;
		cout << "Gearbox: " << gearbox << endl;
		cout << "Type: " << type << endl;
		cout << "Price [per day]: " << price << endl;
	}// void Print
	void setCondition(string p_condition) { condition = p_condition; }// setStan
	string getCondition(void) {
		return condition;
	}// getStan

	bool isReserved(int strMonth, int strDay, int dueMonth, int dueDay) {
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
	int reservingCalendar(int strMonth, int strDay, int dueMonth, int dueDay) {
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
	void deleteReservationCal(int strMonth, int strDay, int dueMonth, int dueDay) {// metoda na zakoñczenie rezerwacji -> zmiana wska¿nika dostênosci z 1 -> 0
		if (strMonth < dueMonth) {
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
			cout << "Entered wrong start month or due month" << endl;
		}
		DaysTotal = 0;
	}
	int getDaysTotal(void) const { return DaysTotal; }
	
};



vector<Vehicle>Vehicles;// collection of vehicles
void PrintVehicles() {
	int j{ 1 };
	cout << "--------------------------------------------------------------------------------" << endl;
	for (int i = 0;i <= Vehicles.size()-1; ++i) {
		cout <<endl<< j << ":" << endl, j++;
		Vehicles[i].Print(), cout << "\n--------------------------------------------------------------------------------";
	}
}
#endif