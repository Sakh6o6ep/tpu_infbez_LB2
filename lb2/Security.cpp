#include "Security.h"

void Security::matrix_creation(int user, int file) {
    // Заполнение матрицы (границы)
    vector<vector<string>> BAZA1(user, vector<string>(file));
    this->BAZA = BAZA1;
    BAZA[0][0] = "";
    BAZA[1][0] = "Admin";
    for (int i = 2; i < user; i++) { // Заполнение Users
        BAZA[i][0] = "User" + to_string(i);
    }
    for (int j = 1; j < file; j++) { // Заполнение Files
        BAZA[0][j] = "File" + to_string(j);
    }
}

void Security::matrix_output() {
    // Вывод матрицы
    for (int i = 0; i < BAZA.size(); i++) {
        for (int j = 0; j < BAZA[i].size(); j++) {
            cout << setw(15) << BAZA[i][j];
        }
        cout << endl;
    }
}

void Security::filling_operations(int user, int file) {
    // Заполнение операций
    int rng, random_minus;
    string S_;
    int index;
    bool flag_r, flag_w, flag_m, flag_g;
    for (int i = 1; i < user; i++) {
        for (int j = 1; j < file; j++) {
            S_ = S;
            random_minus = 4;
            flag_r = false;
            flag_w = false;
            flag_m = false;
            flag_g = false;
            if (i == 1) {
                BAZA[i][j] = S;
            }
            else {
                rng = (rand() % 4) + 1;
                while (rng != 0) {
                    if (rng == 4) {
                        BAZA[i][j] = S;
                        rng = 0;
                    }
                    else {
                        BAZA[i][j] += S_[rand() % random_minus];
                        if (BAZA[i][j].find("r") != string::npos && !flag_r) {
                            index = S_.find("r");
                            S_.erase(index, 1);
                            flag_r = true;
                        }
                        else if (BAZA[i][j].find("w") != string::npos && !flag_w) {
                            index = S_.find("w");
                            S_.erase(index, 1);
                            flag_w = true;
                        }
                        else if (BAZA[i][j].find("m") != string::npos && !flag_m) {
                            index = S_.find("m");
                            S_.erase(index, 1);
                            flag_m = true;
                        }
                        else if (BAZA[i][j].find("g") != string::npos && !flag_g) {
                            index = S_.find("g");
                            S_.erase(index, 1);
                            flag_g = true;
                        }
                        rng--;
                        random_minus--;
                    }
                }
            }
        }
    }
}

void Security::matrix_security(int user, int file) {
    // Работа с матрицей
    bool flag_exit = false;
    bool flag_login = false;
    string login;
    string menu;
    int operations;
    string grant_temp, komu;
    int komu_int;
    bool pravo = false;
    bool komu_bool = false;
    while (!flag_exit) {
        cout << "Введите индентификатор пользователя: ";
        cin >> login;
        for (int i = 1; i < user; i++) {
            if (BAZA[i][0] == login) {
                flag_login = true;
            }
        }
        if (!flag_login && login != "exit") cout << "Ошибка входа, пользователь не найден" << endl;
        for (int i = 1; i < user; i++) {
            if (login == BAZA[i][0]) {
                cout << "Пользователь: " << BAZA[i][0] << endl;
                cout << "Идентификация прошла успешно, добро пожаловать в систему" << endl;
                cout << "Перечень Ваших прав:" << endl;
                for (int j = 1; j < file; j++) {
                    cout << BAZA[0][j] << ": " << BAZA[i][j] << endl;
                }
                flag_login = true;
                while (flag_login) {
                    cout << "Все команды: read, write, modify, grant, quit" << endl;
                    cout << "Жду ваших указаний > ";
                    cin >> menu;
                    if (menu == "read" || menu == "write" || menu == "modify") {
                        cout << "Над каким объектом производится операция? ";
                        cin >> operations;
                        if (operations > file - 1) {
                            cout << "Файла не существует" << endl;
                        }
                        else if ((BAZA[i][operations].find("r") != string::npos) && menu == "read") {
                            cout << "Операция прошла успешно" << endl;
                        }
                        else if ((BAZA[i][operations].find("w") != string::npos) && menu == "write") {
                            cout << "Операция прошла успешно" << endl;
                        }
                        else if ((BAZA[i][operations].find("m") != string::npos) && menu == "modify") {
                            cout << "Операция прошла успешно" << endl;
                        }
                        else cout << "Отказ в выполнении операции. У Вас нет прав для ее осуществления" << endl;
                    }
                    else if (menu == "quit") {
                        cout << "Работа пользователя " << BAZA[i][0] << " завершена. До свидания." << endl;
                        flag_login = false;
                    }
                    else if (menu == "grant") { // дополнительно задание
                        cout << "Право на какой объект передается? ";
                        cin >> operations;
                        if (operations > file - 1 || operations < 1) {
                            cout << "Файла не существует" << endl;
                        }
                        else {
                            cout << "Какое право передается (r,w,m,g)? ";
                            cin >> grant_temp;
                            if (BAZA[i][operations].find(grant_temp) != string::npos) {
                                pravo = true;
                            }
                            if (pravo) {
                                cout << "Какому пользователю передается право? ";
                                cin >> komu;
                                for (int i = 1; i < user; i++) {
                                    if (komu == BAZA[i][0]) {
                                        komu_int = i;
                                        komu_bool = true;
                                    }
                                }
                                if (komu_bool) {
                                    if (BAZA[komu_int][operations].find(grant_temp) != string::npos) {
                                        cout << "Пользователь уже имеет такое право" << endl;
                                    }
                                    else {
                                        BAZA[komu_int][operations] += grant_temp;
                                        komu_bool = false;
                                        cout << "Операция прошла успешно" << endl;
                                        matrix_output();
                                    }
                                }
                                else cout << "Пользователя не существует" << endl;
                            }
                            else cout << "Отказ в выполнении операции. У Вас нет прав для ее осуществления" << endl;
                        }

                    }
                    else cout << "Операции не существет" << endl;
                }
            }
            else {
                flag_login = false;
            }
        }
        if (login == "exit") flag_exit = true;
    }
}