#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Security {
    string S = "rwmg";
    vector<vector<string>> BAZA;
public:
    void matrix_creation(int user, int file);
    void matrix_output();
    void filling_operations(int user, int file);
    void matrix_security(int user, int file);
};