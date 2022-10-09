#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

ifstream sPrice("SeatPrices.dat");
ifstream sAvialable("SeatAvailability.dat");
ofstream sResult("SeatResult.dat");

struct seatStructure{
	double cost;
	char sold;
};

class TicketManager{
	public:
		seatStructure theater[15][30];
		int sTotal;
		double pTotal;
		TicketManager();
		~TicketManager();
};

//Constructor
TicketManager::TicketManager(){
    sTotal = 0;
    pTotal = 0;
    double price;
    for(int row = 0; row < 15; row++){
        sPrice >> price;
        for(int column = 0; column < 30; column++){
            theater[row][column].cost = price;
            sAvialable >> theater[row][column].sold;
        }
    }
}

//Destructor
TicketManager::~TicketManager(){
    for (int row = 0; row < 15; row++){
		sResult << "Row " << left << setw(8) << row + 1;
		for (int column = 0; column < 30; column++){
			sResult << theater[row][column].sold;
		}
		sResult << endl;
	}
	sResult << "\nThe number of seats sold is: " << sTotal << endl;
	sResult << "The number of seats available is: " << (15 * 30) - sTotal << endl;
	sResult << "The amound of money collected today is: $" << pTotal << endl;
	sResult.close();
}

int menu();
TicketManager seatInfo(TicketManager);
void seatChart(TicketManager);
char seatOrder(int, int, int, char, TicketManager);
TicketManager seatUpdate(int, int, int, TicketManager);
void report(TicketManager);

int main(){
	TicketManager theater;
	int choice = 0;
	while(choice != 4){
		choice = menu();
		switch(choice){
			case 1:
				seatChart(theater);
				break;

			case 2:
				theater = seatInfo(theater);
				break;

			case 3:
				report(theater);
				break;

			case 4:
				cout << "\nHave a great day and enjoy the Theater!" << endl;
				break;
		}
	}
	sPrice.close();
	sAvialable.close();
}

void report(TicketManager movie){
	for(int row = 0; row < 15; row++){
		for(int column = 0; column < 30; column++){
			if(movie.theater[row][column].sold == '*'){
				movie.sTotal++;
				movie.pTotal += movie.theater[row][column].cost;
			}
		}
	}
	int left = 15 * 30 - movie.sTotal;
	cout << "Seats Sold: " << movie.sTotal << "\nSeats Left: " << left
		<< "\nTotal Money: $" << movie.pTotal << endl << endl;
}

void seatChart(TicketManager movie){
	for(int row = 0; row < 15; row++){
		cout << "Row " << left << setw(8) << row + 1;
	for (int column = 0; column < 30; column++)
		{
			cout << movie.theater[row][column].sold;
		}
		cout << endl;
	}
	cout << endl;
}

TicketManager seatInfo(TicketManager theater){
	int numSeats, numRow, startSeat;
	char bought;
	cout << "How many seats: ";
	cin >> numSeats;
	cout << "Which row do you want to be in: ";
	cin >> numRow;
	cout << "Which seat did you want to start with: ";
	cin >> startSeat;
	bought = seatOrder(numSeats, numRow, startSeat, bought, theater);
	if(bought == 'Y' || bought == 'y'){
		cout << "\nOrder Confirmed." << endl << endl;
		theater = seatUpdate(numSeats, numRow, startSeat, theater);
	}
	else{
		cout << "\nOrder did not go through." << endl << endl;
	}
	return theater;
}

TicketManager seatUpdate(int numSeats, int numRow, int startSeat, TicketManager movie){
	for(int x = 0; x < numSeats; x++){
		movie.theater[numRow - 1][startSeat+x - 1].sold = '*';
	}
	return movie;
}

char seatOrder(int numSeats, int numRow, int startSeat, char bought, TicketManager movie){
    for(int x = 0; x < numSeats; x++){
        if(movie.theater[numRow - 1][(startSeat+x) - 1].sold == '*'){
            cout << "\nThe seats are not available." << endl;
            return 'N';
        }
    }
    cout << "Number of seats: " << numSeats << "\nPrice of each seat: $" << movie.theater[numRow][0].cost
         << "\nTotal cost for these seats: $" << movie.theater[numRow][0].cost * numSeats
         << "\n\nDo you want to purchase these seats? (Y/N) ";
    cin >> bought;
    return bought;
}

int menu(){
	int choice;
	cout << "Welcome to the Theater!\nEnter number for options:" << "\n1 for seating chart"
		<< "\n2 to request tickets" << "\n3 to print sells report" << "\n4 to exit menu: ";
	cin >> choice;
	cout << endl;
	if(choice < 1 || choice > 4){
		cout << "\nInvalid Input." << endl;
		choice = menu();
	}
	return choice;
}
