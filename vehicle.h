#ifndef VEHICLE_HPP_
#define VEHICLE_HPP_
#include "including.h"
#include "ReservationCalendar.h"



class Vehicle : public Calendar{
private:
	string brand{ "" };//marka
	string model{ "" };//model
	string gearbox{ "" };//skrzynia biegów
	string engine{ "" };//silnik
	string condition{ "" };//stan 
	string type{ "" };// typ pojazdu
	string category{ "" };// klasa pojazdu
	float price{ 0.0 };//cena za wynajem [per day]
	Calendar *Calc;
	

public:
	float getprice()const { return price; }
	void setPrice(float p_price = 0.0) {
		price = p_price;
	}
	Calendar getCalendar() const { return *Calc; }
	void setCalc(Calendar& cal) { Calc = &cal; }

	Vehicle(string p_brand = "Didn't set", string p_model = "Didn't set", string p_gearbox = "Didn't set",
		string p_engine = "Didn't set", string p_condition = "Didn't set", string p_type = "Didn't set", 
		string p_category = "Didn't set") :brand(p_brand), model(p_model), gearbox(p_gearbox), engine(p_engine), condition(p_condition),
		type (p_type), category(p_category)
	{
		Calendar temporaryCalc,*calendarOfVehicle=&temporaryCalc;
		setCalc(*calendarOfVehicle);
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

	// set_Cena_Za_Wynajem
	
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