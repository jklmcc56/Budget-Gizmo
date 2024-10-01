#include "main.hh"
#include "savings.hh"

State state;

int main(void) {
	state = MenuState;
	while (1) {
		switch (state) {
			case MenuState:
				Menu();
				break;
			case SavingsState:
				Savings();
				break;
			case ExpensesState:
				
			case ReportsState:
				
			case ExitState:
				return 0;
			
			default:
				cerr << "ERROR: Undefined State" << endl;
				exit(0);
		}
	}
}

void Menu(void) {
	cout << "Welcome To The Budget Gizmo" << endl;
	cout << "Go To Savings (1)" << endl;
	cout << "Go To Expenses (2)" << endl;
	cout << "Go To Reports (3)" << endl;
	cout << "Exit (4)" << endl;

	int sel = ValidOption(4);
	switch (sel) {
		case 1:
			state = SavingsState;
			break;
		case 2:
			state = ExpensesState;
			break;
		case 3:
			state = ReportsState;
			break;
		case 4:
			state = ExitState;
			break;
	}

	return;	
}

int ValidOption(int options) {
	int sel;
	while (1) {
		cin >> sel;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please Select a Valid Option" << endl;
		}
		else if (sel >= 1 && sel <= options) {
			break;
		}
		else {
			cout << "Please Select a Valid Option" << endl;
		}
	}

	ClearTerminal();

	return sel;
}

void ClearTerminal(void) {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif	
}

void ReturnOption(State ReturnState) {
	cout << endl;
	cout << "Return (1)" << endl;
    int sel = ValidOption(1);
	if (sel) {
		ClearTerminal();
		state = ReturnState;
	}
}

string ValidAddMoney(void) {
	string money;
	while (1) {
		cin >> money;
		int DecimalCount = 0;
		for (char c : money) {
			if (isdigit(c)) {
				continue;
			}
			else if (c == '.' && DecimalCount == 0) {
				DecimalCount++;
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid Input. Please Enter a Valid Dollar Amount" << endl;
			}
		}

		size_t DecimalPos = money.find('.');
		if (DecimalPos == string::npos || (money.length() - DecimalPos - 1) > 2) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input. Please Enter a Valid Dollar Amount" << endl;
		}
		else {
			break;
		}
	}

	ClearTerminal();

	return money;
}