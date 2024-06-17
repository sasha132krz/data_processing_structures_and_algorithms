#include <iostream>
#include <string>
#include <Windows.h>
#include "Hash.h"

using namespace std;
SimCards SCard;

//Главное меню
void MainMenu()
{
    cout << "Меню информационной системы:" << endl;
    cout << "1. Клиент" << endl;
    cout << "2. SIM-карта" << endl;
    cout << "3. Выдача или возврат SIM-карты" << endl;
    cout << "0. Завершение работы" << endl;
    cout << "_________________________" << endl;
    cout << "Выберите 1 из пунктов меню: ";
}
//Меню Клиента
void ClientMenu()
{
    cout << "Меню взаимодействия с клиентом" << endl;
    cout << "1. Регистрация нового клиента" << endl;
    cout << "2. Снятие с обслуживания клиента" << endl;
    cout << "3. Просмотр зарегистрированных клиентов" << endl; //Отобразить не менее 2 полей о каждом клиенте
    cout << "4. Поиск клиента по номеру паспорта" << endl;
    cout << "5. Поиск клиента по ФИО" << endl;
    cout << "6. Очистка данных обо всех клиентах" << endl;
    cout << "0. Возврат в главное меню" << endl;
    cout << "_________________________" << endl;
    cout << "Выберите 1 из пунктов меню: ";
}
//Меню SIM-карты
void SimCardMenu()
{
    cout << "Меню обслуживания SIM-карт" << endl;
    cout << "1. Добавление новой SIM-карты" << endl; // NNN-NNNNNN, строка
    cout << "2. Удаление сведений о SIM-карте" << endl;
    cout << "3. Просмотр всех SIM-карт" << endl; //Отобразить не менее 2 полей о каждой SIM-карте
    cout << "4. Поиск SIM-карты по её номеру" << endl;
    cout << "5. Поиск SIM-карты по тарифу" << endl;
    cout << "6. Очистка данных о SIM-картах" << endl;
    cout << "0. Возврат в главное меню" << endl;
    cout << "_________________________" << endl;
    cout << "Выберите 1 из пунктов меню: ";
}
// Меню Выдачи и возврата SIM-карты
void MenuIssueAndReturn()
{
    cout << "Выдача или возврат SIM-карты" << endl;
    cout << "1. Регистрация выдачи SIM-карты" << endl;
    cout << "2. Регистрация возврата SIM-карты" << endl;
    cout << "0. Возврат в главное меню" << endl;
    cout << "_________________________" << endl;
    cout << "Выберите 1 из пунктов меню: ";
}
// Для проверки ввода числа
void IsDigit(int& digit)
{
    cin >> digit; // ввод числа
    while (cin.fail() || (cin.rdbuf()->in_avail() > 1))
    {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail()); cout << "Введите число повторно: ";
        cin >> digit;
    }
}
// Прямой алгоритм поиска
bool DirectSearchAlgorithm(string str, string substr)
{
//#pragma warning(disable : 4996)
    char str_[100]{};
    strcpy_s(str_, str.c_str());
    char substr_[100]{};
    strcpy_s(substr_, substr.c_str());
    for (const char* hp = str_; hp != str_ + strlen(str_); ++hp)
    {
        const char* np = substr_;
        const char* tmp = hp;
        for (; np != substr_ + strlen(substr_); ++np)
        {
            if (*tmp != *np)
            {
                break;
            }
            else
            {
                ++tmp;
            }
        }
        if (np == substr_ + strlen(substr_))
        {
            return true;
        }
    }
    return false;
}
// Структура данных Клиент
struct Client
{
    string passport; // «NNNN-NNNNNN» N - цифры
    string place_and_date_issue_passport; //Место и дата выдачи паспорта
    string full_name; // ФИО
    int year_of_birth; // Год рождения
    string address; // Адрес
};
// Структура дерева, данные о клиентах
struct Three
{
    int height_tree; // Высота поддерева
    Client* client = NULL; // Данные о клиенте
    Three* left = NULL; // Левый элемент поддерева
    Three* right = NULL; // Правый элемент поддерева
};
// Выдача/возврат SIM-карт
struct Data
{
    string passport; // Паспорт клиента
    string sim_card_num; // Номер SIM-кврты
    string date_issue; // Дата выдачи
    string expiration_date; // Дату окончания действия
    Data* next = NULL; // Следующий элемент линейного списка
};
Data* Partition(Data*& start, Data*& end) {
    string pivotValue = start->sim_card_num;
    Data* p = start;
    Data* q = start->next;
    while (q != end) {
        if (q->sim_card_num < pivotValue) {
            p = p->next;
            swap(p->sim_card_num, q->sim_card_num);
        }
        q = q->next;
    }
    swap(p, start);
    return p;
}
//Быстрая сортировка
void QuickSort(Data*& head, Data*& end)
{
    if (head != end) {
        Data* mid = Partition(head, end);
        QuickSort(head, mid);
        QuickSort(mid->next, end);
    }
}
// Проверка, есть ли такой паспорт в базе
void SearchPassportInData(Three*& element, int& count, string value)
{
    if (element == NULL)
    {
        return;
    }
    if (element->client->passport == value)
    {
        count++;
        return;
    }
    SearchPassportInData(element->left, count, value); // Обошли левое поддерево
    SearchPassportInData(element->right, count, value); // Обошли правое поддерево
}
// Проверка на ввод паспорта
void CheckPassport(string& passport)
{
    int count = 0;
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());
    getline(cin, passport);
    while (true)
    {
        // «NNNN-NNNNNN» N - цифры
        if ((int)passport[0] >= 48 && (int)passport[0] <= 57 && (int)passport[1] >= 48 && (int)passport[1] <= 57
            && (int)passport[2] >= 48 && (int)passport[2] <= 57 && (int)passport[3] >= 48 && (int)passport[3] <= 57
            && (int)passport[4] == 45 && (int)passport[5] >= 48 && (int)passport[5] <= 57 && (int)passport[6] >= 48
            && (int)passport[6] <= 57 && (int)passport[7] >= 48 && (int)passport[7] <= 57 && (int)passport[8] >= 48
            && (int)passport[8] <= 57 && (int)passport[9] >= 48 && (int)passport[9] <= 57 && (int)passport[10] >= 48
            && (int)passport[10] <= 57 && passport.size() == 11)
        {
            break;
        }
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail()); cout << "Введите номер паспорта повторно NNNN-NNNNNN (где N - цифра): ";
        getline(cin, passport);
    }
}
// Проверка на ввод паспорта
void CheckPassportToAdd(Three*& element, string& passport)
{
    int count = 0;
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());
    getline(cin, passport);
    while (true)
    {
        // «NNNN-NNNNNN» N - цифры
        if ((int)passport[0] >= 48 && (int)passport[0] <= 57 && (int)passport[1] >= 48 && (int)passport[1] <= 57
            && (int)passport[2] >= 48 && (int)passport[2] <= 57 && (int)passport[3] >= 48 && (int)passport[3] <= 57
            && (int)passport[4] == 45 && (int)passport[5] >= 48 && (int)passport[5] <= 57 && (int)passport[6] >= 48
            && (int)passport[6] <= 57 && (int)passport[7] >= 48 && (int)passport[7] <= 57 && (int)passport[8] >= 48
            && (int)passport[8] <= 57 && (int)passport[9] >= 48 && (int)passport[9] <= 57 && (int)passport[10] >= 48
            && (int)passport[10] <= 57 && passport.size() == 11)
        {
            SearchPassportInData(element, count, passport);
            if (count == 0)
            {
                break;
            }
        }
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail()); cout << "Введите номер паспорта повторно NNNN-NNNNNN (где N - цифра): ";
        getline(cin, passport);
    }
}
// Поиск ФИО по номеру паспорта
void SearchFullNameToPassport(const Three* element, string value)
{
    if (element == NULL)
    {
        return;
    }
    if (element->client->passport == value)
    {
        cout << "ФИО клиента: " << element->client->full_name << endl;
        return;
    }
    SearchFullNameToPassport(element->left, value); // Обошли левое поддерево
    SearchFullNameToPassport(element->right, value); // Обошли правое поддерево
}
// Поиск паспорта по номеру SIM-карты
void SearchPassportToSimNum(Data*& start, Data*& end, string sim_number, const Three* element)
{
    int check = 0;
    Data* help = start;
    while (help != NULL)
    {
        if (help->sim_card_num == sim_number)
        {
            check++;
            cout << "Номер паспорта: " << help->passport << endl;
            SearchFullNameToPassport(element, help->passport);
            cout << "_______________________________" << endl;
        }
        help = help->next;
    }
    if (check == 0) {
        cout << "SIM-карта не зарегистрированна на клиента" << endl;
        cout << "_______________________________" << endl;
    }
}
// Удаление данных всех SIM-карт
bool DeleteAllSimCard(Data*& start, Data*& end)
{
    if (start != NULL)
    {
        cout << "Нельзя удалить SIM-карты, зарегистрированные на клиентов!" << endl;
        cout << "_______________________________" << endl;
        system("pause");
        return false;
    }
    return true;
}
//Проверка высоты
int Height(Three*& element)
{
    if (element == NULL)
    {
        return -1;
    }
    else
    {
        return element->height_tree;
    }
}
//малый левый поворот
Three* SmallLeftTurn(Three*& element)
{
    Three* help = element->right;
    element->right = help->left;
    help->left = element;
    element->height_tree = max(Height(element->left), Height(element->right)) + 1;
    help->height_tree = max(Height(element->left), element->height_tree) + 1;
    return help;
}
//малый правый поворот
Three* SmallRightTurn(Three*& element)
{
    Three* help = element->left;
    element->left = help->right;
    help->right = element;
    element->height_tree = max(Height(element->left), Height(element->right)) + 1;
    help->height_tree = max(Height(help->left), element->height_tree) + 1;
    return help;
}
//большой левый поворот
Three* BigLeftTurn(Three*& element)
{
    element->right = SmallRightTurn(element->right);
    return SmallLeftTurn(element);
}
//большой правый поворот
Three* BigRightTurn(Three*& element)
{
    element->left = SmallLeftTurn(element->left);
    return SmallRightTurn(element);
}
// Добавление Клиента
void AddClient(Three*& element, string c_passport)
{
    if (element == NULL)
    {
        Client* client = new Client; client->passport = c_passport;
        cout << "Введите место и дату выдачи паспорта: "; cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        getline(cin, client->place_and_date_issue_passport); cout << "Введите ФИО нового клиента: "; cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        getline(cin, client->full_name);
        cout << "Введите год рождения: ";
        IsDigit(client->year_of_birth); cout << "Введите адрес проживания: ";
        cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
        getline(cin, client->address);
        element = new Three;
        element->height_tree = 0;
        element->client = client;
    }
    else
    {
        if (c_passport < element->client->passport)
        {
            AddClient(element->left, c_passport);
            //Если произошла разбалансировка
            if (Height(element->left) - Height(element->right) == 2)
            {
                if (c_passport < element->left->client->passport)
                {
                    element = SmallRightTurn(element);
                }
                else
                {
                    element = BigRightTurn(element);
                }
            }
        }
        else if (c_passport > element->client->passport)
        {
            AddClient(element->right, c_passport);
            if (Height(element->right) - Height(element->left) == 2)
            {
                if (c_passport > element->right->client->passport)
                {
                    element = SmallLeftTurn(element);
                }
                else
                {
                    element = BigLeftTurn(element);
                }
            }
        }
    }
    element->height_tree = max(Height(element->left), Height(element->right)) + 1;
}
// Удаление минимального значения
Client* DeleteMin(Three*& element)
{
    Client* a;
    if (element->left == NULL)
    {
        a = element->client;
        element = element->right;
        return a;
    }
    else
    {
        a = DeleteMin(element->left);
        return a;
    }
}
//Печать данных клиентов
void PrintClient(const Three* element, int count = 0)
{
    if (count == 0 && element == NULL)
    {
        cout << "Нет зарегистрированных клиентов" << endl; cout << "__________________________" << endl;
        return;
    }
    if (element == NULL)
    {
        return;
    }
    count++;
    cout << "Номер паспорта: " << element->client->passport << endl;
    cout << "Место и дата выдачи паспорта: " << element->client->place_and_date_issue_passport << endl;
    cout << "ФИО клиента: " << element->client->full_name << endl;
    cout << "Год рождения: " << element->client->year_of_birth << endl;
    cout << "Адрес клиента: " << element->client->address << endl;
    cout << "_________________________________" << endl;
    PrintClient(element->left, count); // Обошли левое поддерево
    PrintClient(element->right, count); // Обошли правое поддерево
}
// Проверка, действующий клиент или нет
bool CheckClientInBase(Data*& start, Data*& end, string value)
{
    Data* help = start;
    while (help != NULL)
    {
        if (help->passport == value)
        {
            return 1;
        }
        help = help->next;
    }
    return 0;
}
// Удаление данных о клиенте
void DeleteClient(Three*& element, string value, Data*& start, Data*& end)
{
    if (CheckClientInBase(start, end, value)) {
        cout << "Удаление действующего клиента невозможно" << endl;
        cout << "___________________________________________________" << endl;
        return;
    }
    Three* d;
    if (element == NULL)
    {
        cout << "Клиента с таким паспортом в базе нет" << endl;
        cout << "_________________" << endl;
    }
    else if (value < element->client->passport)
    {
        DeleteClient(element->left, value, start, end);
    }
    else if (value > element->client->passport)
    {
        DeleteClient(element->right, value, start, end);
    }
    else if ((element->left == NULL) && (element->right == NULL))
    {
        d = element;
        free(element->client);
        element->client = nullptr;
        free(d);
        d = nullptr;
        element = nullptr;
        cout << "Данные о клиенте удалены" << endl;
        cout << "____________________________" << endl;
    }
    else if (element->left == NULL)
    {
        Three* help = element->right;
        d = element;
        delete element->client;
        element->client = nullptr;
        delete d;
        d = nullptr;
        element = help; cout << "Данные о клиенте удалены" << endl;
        cout << "____________________________" << endl;
    }
    else if (element->right == NULL)
    {
        d = element;
        element = element->left;
        free(element->client);
        element->client = nullptr; free(d);
        d = nullptr;
        cout << "Данные о клиенте удалены" << endl;
        cout << "____________________________" << endl;
    }
    else
    {
        free(element->client);
        element->client = nullptr;
        element->client = DeleteMin(element->right);
        cout << "Данные о клиенте удалены" << endl;
        cout << "____________________________" << endl;
    }
}
// Поиск клиента по ФИО
void SearchByFullName(const Three* element, string value, int count = 0)
{
    if (count == 0 && element == NULL)
    {
        cout << "Нет зарегистрированных клиентов" << endl;
        cout << "__________________________" << endl;
        return;
    }
    if (element == NULL)
    {
        return;
    }
    if (DirectSearchAlgorithm(element->client->full_name, value))
    {
        cout << "Номер паспорта: " << element->client->passport << endl;
        cout << "ФИО клиента: " << element->client->full_name << endl;
        cout << "Адрес клиента: " << element->client->address << endl;
        cout << "___________________________________" << endl;
    }
    count++;
    SearchByFullName(element->left, value, count); // Обошли левое поддерево
    SearchByFullName(element->right, value, count); // Обошли правое поддерево
}
// Поиск SIM-карты по номеру паспорта
void SearchSimCardToPassport(Data*& start, Data*& end, string value)
{
    int check = 0; // для проверки, что SIM-карта зарегиcтрирована на клиента
    Data* help = start;
    while (help != NULL)
    {
        if (help->passport == value)
        {
            check++;
            cout << "Номер SIM-карты: " << help->sim_card_num << endl;
        }
        help = help->next;
    }
    if (check == 0) {
        cout << "На данного клиента не зарегистрированны SIM-карты" << endl;
        cout << "________________________" << endl;
    }
}
// Поиск клиента по номеру паспорта
void SearchClientToPassport(const Three* element, Data*& start, Data*& end, string value, int count = 0)
{
    if (count == 0 && element == NULL) {
        cout << "Нет зарегистрированных клиентов" << endl;
        cout << "__________________________" << endl;
        return;
    }
    if (element == NULL)
    {
        return;
    }
    if (element->client->passport == value)
    {
        cout << "Номер паспорта: " << element->client->passport << endl;
        cout << "Место и дата выдачи паспорта: " << element->client->place_and_date_issue_passport << endl;
        cout << "ФИО клиента: " << element->client->full_name << endl;
        cout << "Год рождения: " << element->client->year_of_birth << endl;
        cout << "Адрес: " << element->client->address << endl;
        cout << "_________________________________" << endl;
        SearchSimCardToPassport(start, end, value);
    }
    count++;
    SearchClientToPassport(element->left, start, end, value, count); // Обошли левое поддерево
    SearchClientToPassport(element->right, start, end, value, count); // Обошли правое поддерево
}
// Удалить всех клиентов
void DeleteAllClients(Three*& element, Data*& start, Data*& end, int count = 0)
{
    if (start != NULL)
    {
        cout << "Невозможно удалить действующих клиентов" << endl;
        cout << "__________________________" << endl;
        return;
    }
    if (count == 0 && element == NULL) {
        cout << "Нет зарегистрированных клиентов" << endl;
        cout << "__________________________" << endl;
        return;
    }
    if (element == NULL)
    {
        return;
    }
    count++;
    DeleteAllClients(element->left, start, end, count); // Обошли левое поддерево
    DeleteAllClients(element->right, start, end, count); // Обошли правое поддерево
    delete element->client;
    element->client = nullptr;
    delete element;
    element = nullptr;
    cout << "Все клиенты удалены" << endl;
    cout << "__________________________" << endl;
    return;
}
// Выдача SIM-карты
void IssueSimCard(Data*& start, Data*& end, Three*& element, string sim_num)
{
    string passport;
    string d_issue;
    string expiration_d;
    cout << "Введите номер паспорта NNNN-NNNNNN (где N - цифра): ";
    CheckPassport(passport); // ввод паспорта
    cout << "Введите дату выдачи Sim-карты (ДД.ММ.ГГГГ): ";
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail()); getline(cin, d_issue);
    cout << "Введите дату окончания действия (ДД.ММ.ГГГГ): "; cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());
    getline(cin, expiration_d);
    int count = 0;
    SearchPassportInData(element, count, passport);
    if (count > 0)
    {
        SCard.SimCardIssue(sim_num);
        cout << "Sim-карта успешно оформлена!" << endl;
        cout << "____________________________" << endl;
    }
    else
    {
        cout << "Такого клиента нет" << endl;
        cout << "___________________________" << endl;
        system("pause");
        return;
    }
    Data* append = new Data;
    append->sim_card_num = sim_num;
    append->passport = passport;
    append->date_issue = d_issue;
    append->expiration_date = expiration_d;
    if (start == NULL)
    {
        start = append;
        end = append;
    }
    else
    {
        Data* help = start;
        while (true)
        {
            if (help->next == NULL)
            {
                help->next = append;
                end = append;
                break;
            }
            help = help->next;
        }
    }
}
// Возврат SIM-карты
void ReturnSimCard(Data*& start, Data*& end, Three*& element, string sim_num)
{
    string passport;
    cout << "Введите номер паспорта NNNN-NNNNNN (где N - цифра): ";
    CheckPassport(passport); // ввод паспорта
    int count = 0;
    SearchPassportInData(element, count, passport); // Есть ли такой номер паспорта
    if (count == 0)
    {
        cout << "Нет клиента с таким паспортом" << endl;
        cout << "_____________________________" << endl;
        return;
    }
    Data* help = start; // Поиск и удаление из списка записи
    while (help != NULL)
    {
        if (help->sim_card_num == sim_num && help->passport == passport)
        {
            // если всего 1 элемент
            if (start == end)
            {
                delete start;
                start = nullptr;
                end = nullptr;
                SCard.SimCardIssue(sim_num);
                cout << "Возврат SIM-карты оформлен" << endl;
                cout << "___________________________" << endl;
                return;
            }
            // если удаляем первый элемент
            else if (help == start && help->next != NULL)
            {
                start = help->next;
                delete help;
                help = nullptr;
                help = start;
                SCard.SimCardIssue(sim_num); cout << "Возврат SIM-карты оформлен" << endl;
                cout << "___________________________" << endl;
                return;
            }
            // если удаляем последний элемент
            else if (help == end)
            {
                Data* last = start; // храним тут последний элемент
                help = start;
                while (help != NULL)
                {
                    if (help->next == end)
                    {
                        last = help->next;
                        help->next = NULL; // обнуляем указатель
                        break;
                    }
                    help = help->next;
                }
                // удаляем элемент из списка
                delete last;
                last = nullptr;
                end = nullptr; help = start;
                // бежим до последнего элемента и назначаем end
                while (help != NULL)
                {
                    if (help->next == NULL)
                    {
                        end = help;
                        break;
                    }
                    help = help->next;
                }
                SCard.SimCardIssue(sim_num);
                cout << "Возврат SIM-карты оформлен" << endl;
                cout << "___________________________" << endl;
                return;
            }
            // если удаляем элемент откуда-то из центра
            else
            {
                Data* del_element = help; // запоминаем удаляемый элемент
                Data* next_element = help->next; // запоминаем следующий элемент за удаляемым
                help = start;
                // бежим, пока не встретим следующий элемент за удаляемый
                while (help != NULL)
                {
                    if (help->next == del_element) {
                        help->next = next_element; // помещаем следующий элемент разрывая цепочку
                        delete del_element;
                        del_element = nullptr;
                        break;
                    }
                    help = help->next;
                }
                SCard.SimCardIssue(sim_num); cout << "Возврат SIM-карты оформлен" << endl;
                cout << "___________________________" << endl;
                return;
            }
        }
        help = help->next;
    }
    cout << "Данная SIM-карта не содержится в списке выданных" << endl;
    cout << "_________________________________" << endl;
}
int main()
{
    //setlocale(LC_ALL, "rus");
    //SetConsoleOutputCP(CP_UTF8);

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");

    Three* start = NULL; // указатель на дерево
    Data* start_list = NULL; // указатель на начало списка
    Data* end_list = NULL; // указатель на конец списка
    string sim_num;
    string passport;
    while (true)
    {
        MainMenu();
        int k;
        IsDigit(k);
        cout << k;
        switch (k)
        {
        case 1:
            while (true)
            {
                system("cls");
                ClientMenu();
                int k1;
                IsDigit(k1);
                int l = 0;
                switch (k1)
                {
                case 1:
                {
                    system("cls");
                    cout << "Введите номер паспорта «NNNN-NNNNNN», где (N - цифры): ";
                    CheckPassportToAdd(start, passport);
                    AddClient(start, passport);
                    system("pause");
                    break;
                }
                case 2:
                {
                    system("cls");
                    cout << "Введите номер паспорта «NNNN-NNNNNN», где (N - цифры): ";
                    CheckPassport(passport);
                    DeleteClient(start, passport, start_list, end_list);
                    system("pause");
                    break;
                }
                case 3:
                {
                    system("cls");
                    PrintClient(start);
                    system("pause");
                    break;
                }
                case 4:
                {
                    system("cls");
                    cout << "Введите номер паспорта «NNNN-NNNNNN», где (N - цифры): ";
                    CheckPassport(passport);
                    SearchClientToPassport(start, start_list, end_list, passport);
                    system("pause");
                    break;
                }
                case 5:
                {
                    system("cls");
                    string value;
                    cout << "Введите ФИО: ";
                    cin.clear();
                    cin.ignore(cin.rdbuf()->in_avail());
                    getline(cin, value);
                    system("cls");
                    SearchByFullName(start, value);
                    system("pause");
                    break;
                }
                case 6:
                {
                    system("cls");
                    DeleteAllClients(start, start_list, end_list);
                    system("pause");
                    break;
                }
                case 0:
                    l++;
                    break;
                }
                if (l == 1)
                {
                    system("cls");
                    break;
                }
            }
            break;
        case 2:
            while (true)
            {
                system("cls");
                SimCardMenu();
                int k2;
                IsDigit(k2);
                int l = 0;
                switch (k2)
                {
                case 1:
                {
                    system("cls");
                    SCard.AddSim();
                    system("pause");
                    break;
                }
                case 2:
                {
                    system("cls");
                    SCard.DeleteSim();
                    system("pause");
                    break;
                }
                case 3:
                    system("cls");
                    SCard.PrintSim();
                    system("pause");
                    break;
                case 4:
                {
                    system("cls");
                    string sim_num = "";
                    SCard.SearchSimCardForNum(&sim_num);
                    if (sim_num != "")
                    {
                        SearchPassportToSimNum(start_list, end_list, sim_num, start);
                    }
                    system("pause");
                    break;
                }
                case 5:
                {
                    system("cls");
                    SCard.SearchSimCardToTariff();
                    system("pause");
                    break;
                }
                case 6:
                    system("cls");
                    if (DeleteAllSimCard(start_list, end_list))
                    {
                        SCard.Cleaning();
                    }
                    break;
                case 0:
                    l++;
                    break;
                }
                if (l == 1)
                {
                    system("cls");
                    break;
                }
            }
            break;
        case 3:
            while (true)
            {
                system("cls");
                MenuIssueAndReturn();
                int k3;
                IsDigit(k3);
                int l = 0;
                switch (k3)
                {
                case 1:
                    system("cls");
                    if (SCard.SearchSimCardforIssue() == true)
                    {
                        IssueSimCard(start_list, end_list, start, sim_num);
                        QuickSort(start_list, end_list);
                    }
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    if (SCard.SearchSimCardforReturn() == true)
                    {
                        ReturnSimCard(start_list, end_list, start, sim_num);
                        QuickSort(start_list, end_list);
                    }
                    system("pause");
                break; case 0:
                    l++;
                    break;
                }
                if (l == 1)
                {
                    system("cls");
                    break;
                }
            }
            break;
        case 0:
            return 0;
        }
    }
}
