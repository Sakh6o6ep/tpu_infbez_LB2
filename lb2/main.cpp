#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <iomanip>
#include "Security.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	int user, file;
	cout << "User = ";
	cin >> user;
	cout << "File = ";
	cin >> file;
	user++;
	file++;

	Security matrix1;

	matrix1.matrix_creation(user, file);
	matrix1.filling_operations(user, file);
	matrix1.matrix_output();
	matrix1.matrix_security(user, file);
	matrix1.matrix_output();

	system("pause");
	return 0;
}