#ifndef RESERVATION_HPP_
#define RESERVATION_HPP_

#include <iostream>
#include "including.h"
#include "user.h"
#include "vehicle.h"

class Reservation : public Vehicle{
	private:
		int str_Month{}, str_Day{}, due_Month{}, due_Day{}, daysTotal, manage_Decision;;
		Vehicle *object;
	public:
		void setStrMonth(int p_strMonth) { str_Month = p_strMonth; } int getStrMonth()const {return str_Month;}
		void setStrDay(int p_strDay) { str_Day = p_strDay; }		 int getStrDay() const { return str_Day; }
		void setDueMonth(int p_dueMonth) { due_Month = p_dueMonth; } int getDueMonth()const { return due_Month; }
		void setDueDay(int p_dueDay) { due_Day= p_dueDay; }		     int getDueDay()const { return due_Day; }
		void setVehicle(Vehicle &car) { object = &car; }		     Vehicle getVehicle()const { return *object; }
		void setMDecision(int p_manage_decision) { manage_Decision = p_manage_decision; } int getMDecision(void) const { return manage_Decision; }
		void setDaysTotal(int p_DaysTot) { daysTotal = p_DaysTot; }  int getDaysTotal(void)const { return daysTotal; }
		Reservation(int p_strM, int p_strD, int p_dueM, int p_dueD,int k)://konstruktor: isReserved -> ReservsationCalcendar
		str_Month(p_strM),str_Day(p_strD),due_Month(p_dueM),due_Day(p_dueD){
			--k;
			setVehicle(Vehicles[k]);
			setDaysTotal(object->reservingCalendar(str_Month, str_Day, due_Month, due_Day));
		}
		virtual void Manage(int k,int j) {
			while (true) {
				string n{};//variable which will represents admin's choice of in which way he want to manage exact reservation
				cout << endl << "Choose action on reservation" << endl;
				cout << "1. Reservation details" << endl;
				cout << "2. Change date of reservation" << endl;
				cout << "3. Detele reservation" << endl;
				cout << "4. Exit" << endl;
				do {
					cin >> n;
				} while (!regex_match(n, regex("[1-4]+")));
				setMDecision(stoi(n));
				if (n == "1") {//1. Print
					cout << "-----------------------------------" << endl;
					Print();
					cout << "-----------------------------------" << endl << endl;
				}
				else if (n == "2") {//2. Change date of reservation
					string strDay{}, strMonth{}, dueDay{}, dueMonth{}; // variables which will store admin input

					int sD{ getStrDay() }, sM{ getStrMonth() },
						dD{ getDueDay() }, dM{ getDueMonth() }; // variables which will be changing date of reservation
					int n{ 0 }; // indicator of which vehicle is assigned to reservation
					bool validation{};//variable which will be checking if admin entered correct input

					//Users[k].reservationsHistory[j].getVehicle().deleteReservationCal(sM, sD, dM, dD);

					for (int i = 0; i <= Vehicles.size() - 1; ++i) {
						if (object->getName() == Vehicles[i].getName()) {
							n = i;
						}
					}
					Vehicles[n].deleteReservationCal(sM, sD, dM, dD);
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
									cout << "Entered bad inout value! Mind to enter number between 1-31" << endl;
									validation = false;
								}
							}
						}

					} while (!validation); 
					sM--; dD--; sD--; dM--;
					setStrMonth(sM); setDueMonth(dM); setStrDay(sD); setDueDay(dD);
					//Users[k].reservationsHistory[j].getVehicle().reservingCalendar(sM, sD, dM, dD);
					setDaysTotal(Vehicles[n].reservingCalendar(sM, sD, dM, dD));
					setVehicle(Vehicles[n]);
					cout << "\nReservation changed!\n\n";
				}
				else if (n == "3") {//3. Delete reservation
					cout << "Deleted!" << endl << endl;
					break;
				}
				else if (n == "4") {//4. Exit
					cout << "Exiting..." << endl << endl;
					break;
				}
			}
		}
		virtual void Print() {
			cout << "--------------------------------------------------------------------" << endl;
			cout << "Reservation starts from: " << getStrDay()+1 << "." << getStrMonth()+1 << " and ends in: " << getDueDay()+1 << "." << getDueMonth()+1 << endl;
			cout << "Vehicle of paremetres as below: " << endl;
			object->Print();
			cout << "Total price will be: " << float(object->getprice() * getDaysTotal()) << " PLN" << endl;
		}
		~Reservation() {
			int n{}; // variable to get object position in vector of vehicles to cancel reservation
			for (int i = 0; i <= Vehicles.size() - 1; ++i) {
				if (object->getName() == Vehicles[i].getName()) {
					n = i;
				}
			}
			Vehicles[n].deleteReservationCal(getStrMonth(), getStrDay(), getDueMonth(), getDueDay());
		}//destruktor: deleteReservationCal
};


#endif // !RESERVATION_HPP

