#ifndef RESERVATION_HPP_
#define RESERVATION_HPP_

#include <iostream>
#include "including.h"
#include "user.h"
#include "vehicle.h"

class Reservation : public Vehicle{
	private:
		int str_Month{}, str_Day{}, due_Month{}, due_Day{}; 
		Vehicle *object;
	public:
		void setStrMonth(int p_strMonth) { str_Month = p_strMonth; } int getStrMonth()const {return str_Month;}
		void setStrDay(int p_strDay) { str_Day = p_strDay; }		 int getStrDay() const { return str_Day; }
		void setDueMonth(int p_dueMonth) { due_Month = p_dueMonth; } int getDueMonth()const { return due_Month; }
		void setDueDay(int p_dueDay) { due_Day= p_dueDay; }		     int getDueDay()const { return due_Day; }
		void setVehicle(Vehicle &car) { object = &car; }		     Vehicle getVehicle()const { return *object; }

		Reservation(int p_strM, int p_strD, int p_dueM, int p_dueD,int k)://konstruktor: isReserved -> ReservsationCalcendar
		str_Month(p_strM),str_Day(p_strD),due_Month(p_dueM),due_Day(p_dueD){
			--k;
			setVehicle(Vehicles[k]);
			object->reservingCalendar(str_Month, str_Day, due_Month, due_Day);
		}
		void ManageReservation() {
			while (true) {
				//choose action
				//1. Change startMonth
				//2. Change startDay
				//3. Change dueMonth
				//4. Change dueDay
				//5. Change Vehicle
				//6. Exit from module
			}
		}
		virtual void Print() {
			cout << "--------------------------------------------------------------------" << endl;
			cout << "Reservation starts from: " << getStrDay() << "." << getStrMonth() << " and ends in: " << getDueDay() << "." << getDueMonth() << endl;
			cout << "Vehicle of paremetres as below: " << endl;
			object->Print();
			cout << "Total price will be: " << float(object->getprice() * object->getDaysTotal()) << " PLN" << endl;
		}
		~Reservation() {}//destruktor: deleteReservationCal
};


#endif // !RESERVATION_HPP

