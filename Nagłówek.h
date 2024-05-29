#ifndef VEHICLE_HPP_
#define VEHICLE_HPP_

class Vehicle {
private:
	string brand{ "" },;//marka
	string model{ "" };//model
	string gearbox{ "" };//skrzynia biegów
	string engine{ "" };//silnik
	string condition{ "" };//stan 
	string type{ "" };// typ pojazdu
	string category{""}// klasa pojazdu
	//wskaznik rezerwacji
	float price{ 0.0 };//cena za wynajem [per day]
public:
	Vehicle(string p_brand="Didn't set", string p_model="Didn't set",string p_gearbox="Didn't set",string p_engine="Didn't set",string p_condition="Didn't set",string p_type="Didn't set",string p_category="Didn't set",float p_price=0.0) {
		brand = p_brand, model = p_model, gearbox = p_gearbox, engine = p_engine, condition = p_condition, type = p_type, category = p_category;
	}//konstruktor

	void Print()const {
		cout << "Brand: " << brand << endl;
		cout << "Model: " << model << endl;
		cout << "Class: " << category<< endl;
		cout << "Engine: " << engine<< endl;
		cout << "gearbox: " << gearbox << endl;
		cout << "Type: " << type<< endl;
		cout << "Price [per day]: " << price << endl;
	}// void Print
	void setCondition(string p_condition) { condition = p_codnition; }// setStan
	string getCondition(void) {
		return condition;
	}// getStan
	
	// setPrzebieg
	// set_Cena_Za_Wynajem
	//destuktor
}; 

#endif