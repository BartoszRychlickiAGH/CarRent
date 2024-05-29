#ifndef RESERVATIONCALENDAR_HPP_
#define RESERVATIONCALENDAR_HPP_
#include "including.h"
#include "vehicle.h"
class Calendar {
	private:
		vector <vector<bool>>Cal;
		int DaysTotal{0};
	public:
		// konstruktor
		Calendar() {
			
			for (int i = 0; i <= 11; ++i) {
				if (i==0||i==2||i==4||i==6||i==7||i==9||i==11) {
					vector<bool>Days;
					for (int j = 0; j <= 30; j++) {
						Days.push_back(true);
					}
					Cal.push_back(Days);
				}
				else if(i==1) {
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
		}
		bool isReserved(int strMonth,int strDay,int dueMonth, int dueDay) {
			vector <bool> check;
			if (strMonth < dueMonth) {
				for (int i = strDay - 1; i <= Cal[strMonth].size() - 1; i++) {
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
			for (int i = 0; i <= check.size()-1; ++i) {
				if (check[i]==false) {
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
						for (int j = 0; j <= Cal[i].size() - 1; ++j){ 
							Cal[i][j] = false;
							DaysTotal++;
						}
					}
				}
			}
			else {
				cout << "Entered wrong start month or due month" << endl;
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

#endif // !RESERVATIONCALENDAR_HPP_
