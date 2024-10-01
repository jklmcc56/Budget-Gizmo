#ifndef MAIN_HH
#define MAIN_HH

#define SDELAY 1
#define DELAY 2
#define LDELAY 3

#include <iostream>
#include <limits>
#include <fstream>
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>

using namespace std;

typedef enum {
    MenuState,
    SavingsState,
    ExpensesState,
    ReportsState,
    ExitState,
} State;

void Menu(void);

int ValidOption(int options);

void ClearTerminal(void);

void ReturnOption(State ReturnState);

string ValidAddMoney(void);

#endif