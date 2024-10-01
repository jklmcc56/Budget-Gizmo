#include "savings.hh"

extern State state;

const string SavingsFile = "savings.txt";

string SavingsAcc = "0.00";
string CheckingAcc = "0.00";
string SavingsTot = "0.00";

string SavingsAccLabel = "Savings Account ($): ";
string CheckingAccLabel = "Checking Account ($): ";
string SavingsTotLabel = "Total Savings ($): ";

void Savings(void) {

    ifstream infile(SavingsFile);
    if (!infile.good()) {
        CreateSavingsReport();
        this_thread::sleep_for(chrono::seconds(LDELAY));
        ClearTerminal();
    }

    cout << "Savings Menu" << endl;
	cout << "Check Accounts (1)" << endl;
	cout << "Add to Savings (2)" << endl;
	cout << "Add to Checking (3)" << endl;
    cout << "Withdraw from Savings (4)" << endl;
    cout << "Withdraw from Checking (5)" << endl;
    cout << "Transfer Money (6)" << endl;
	cout << "Return to Menu (7)" << endl;

    int sel = ValidOption(7);
    switch (sel) {
		case 1:
			CheckAccounts();
			break;
		case 2:
			AddMoney(SavingsAccLabel);
			break;
		case 3:
			AddMoney(CheckingAccLabel);
			break;
        case 4:
            //WithdrawMoney(SavingsAccLabel);
            break;
        case 5:
            //WithdrawMoney(CheckingAccLabel);
            break;
		case 6:
			//TransferMoney();
			break;
        case 7:
            state = MenuState;
            break;
	}

    infile.close();
}

void CreateSavingsReport(void) {
    cout << "No Savings Report Detected" << endl;
    ofstream outfile("savings.txt");
    if (outfile.is_open()) {
        cout << "Blank Savings Report Created" << endl;
        outfile << SavingsAccLabel << SavingsAcc << endl;
        outfile << CheckingAccLabel << CheckingAcc << endl;
        outfile << SavingsTotLabel << SavingsTot << endl;
        cout << "Populated Savings Report with Blank Values" << endl;
        outfile.close();
    }
    else {
        cerr << "ERROR: Could Not Create Savings Report" << endl;
        exit(0);
    }
}

void CheckAccounts(void) {
    ifstream infile(SavingsFile);
    if (!infile) {
        cerr << "ERROR: Failed to Open Savings File in CheckAccounts()" << endl;
        exit(0);
    }

    cout << "Accounts" << endl;
    string line;
    while (getline(infile, line)) {
        cout << line << endl;
    }
    infile.close();

    ReturnOption(SavingsState);
}

void AddMoney(string DesiredAcc) {
    ifstream infile(SavingsFile);
    if (!infile) {
        cerr << "ERROR: Failed to Open Savings File in AddMoney()" << endl;
        exit(0);
    }

    stringstream buffer;
    buffer << infile.rdbuf();
    string FileContents = buffer.str();
    infile.close();

    size_t pos = FileContents.find(DesiredAcc);
    if (pos != string::npos) {
        size_t LineEnd = FileContents.find('\n', pos);
        string line = FileContents.substr(pos, LineEnd - pos);
        cout << line << endl;
        string MoneyAcc = line.substr(DesiredAcc.length());
        double DMoneyAcc = stod(MoneyAcc);

        string AccountName = DesiredAcc.substr(0, DesiredAcc.length() - 6);
        cout << "How Much Money Would You Like to Add to Your Account?" << endl;
        cout << "Please Omit the Dollar Sign!" << endl;
        string MoneyAdd = ValidAddMoney();
        double DMoneyAdd = stod(MoneyAdd);
        double DNewMoneyAcc = DMoneyAcc + DMoneyAdd;
        stringstream SNewMoneyAcc;
        SNewMoneyAcc << fixed << setprecision(2) << DNewMoneyAcc;
        string NewMoneyAcc = SNewMoneyAcc.str();

        FileContents.replace(pos + DesiredAcc.length(), MoneyAcc.length(), NewMoneyAcc);
        ofstream outfile(SavingsFile);
        if (!outfile) {
            cerr << "ERROR: Failed to Open Savings File in AddMoney()" << endl;
            exit(0);
        }

        outfile << FileContents;
        outfile.close();
        cout << "Succesfully Updated Balance in " << AccountName << endl;
        cout << "Money Added ($): " << MoneyAdd << endl;
        cout << "Updated Amount in " << AccountName << " ($): " << NewMoneyAcc << endl;

        ReturnOption(SavingsState);
    }
    else {
        cerr << "ERROR: Account Not Present in Savings File in AddMoney()" << endl;
        exit(0);
    }
}