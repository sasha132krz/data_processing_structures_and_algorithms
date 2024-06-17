#include "Hash.h"

using namespace std;

int SimCards::Hash_Func1(int i, string key)//хеш-функция
{
    int index_1 = 13 * (int(key[0]) + int(key[1]) + int(key[2])) + 18 * (int(key[4])
        + int(key[5]) + int(key[6])) + 3 * (int(key[7]) + int(key[8]) + int(key[9]) + int(key[10]));
    int index_2 = 5 * (int(key[0]) + int(key[1]) + int(key[2])) + 12 * (int(key[4])
        + int(key[5]) + int(key[6])) + 7 * (int(key[7]) + int(key[8]) + int(key[9]) + int(key[10]));
    int position = index_1 + i * index_2;
    return(position % TABLE_SIZE);
}
// Для проверки ввода числа
void SimCards::IsDigit(int& digit)
{
    cin >> digit; // ввод числа
    while (cin.fail() || (cin.rdbuf()->in_avail() > 1))
    {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail()); cout << "Введите число повторно: ";
        cin >> digit;
    }
}
//проверка правильности номера Sim-card
string SimCards::Sim_Check()
{
    string key;
    bool flag = false;//флаг
    regex re("[0-9]{3}-[0-9]{7}");
    cout << "Введите номер Sim-card (формата NNN-NNNNNNN): ";
    while (flag == false)
    {
        cin >> key;
        if (regex_match(key, re))
        {
            flag = true;
        }
        else
            cout << "Номер Sim-card введен неверно, повторите ввод: ";
    }
    return key;
}
void SimCards::resize()
{
    int TSize = TABLE_SIZE;
    TABLE_SIZE *= 2;
    SimCard* htold = new SimCard[TABLE_SIZE];
    for (int ii = 0; ii < TSize; ii++)
    {
        int i = 0;
        int position = Hash_Func1(i, hashTable[ii].sim_card_num);
        while ((htold[position].sim_card_num != ""))
        {
            position = Hash_Func1(i, hashTable[i].sim_card_num);
            i++;
        }
        htold[position].tariff = hashTable[ii].tariff;
        htold[position].sim_card_num = hashTable[ii].sim_card_num;
        htold[position].year_issue = hashTable[ii].year_issue;
        htold[position].is_reach = hashTable[ii].is_reach;
    }
    this->hashTable = htold;
}
//добавление Sim-card
void SimCards::AddSim()
{
    if (tabsize == TABLE_SIZE)
        resize();
    string sim_card = Sim_Check();
    int i = 0;
    int position = Hash_Func1(i, sim_card);
    while ((hashTable[position].sim_card_num != ""))
    {
        if (hashTable[position].sim_card_num == sim_card)//проверка на уникальность
        {
            cout << "Это неуникальный номер Sim-card" << endl; sim_card = Sim_Check();
            i = 0;
            position = Hash_Func1(i, sim_card);
            if (hashTable[position].sim_card_num == "")
                break;
        }
        position = Hash_Func1(i, sim_card);
        i++;
    }
    string tariff;
    cin.ignore();
    cout << "Введите тариф Sim-card: ";
    getline(cin, tariff);
    int year; cout << "Введите год выпуска SIM-карты: ";
    IsDigit(year);
    hashTable[position].sim_card_num = sim_card;
    hashTable[position].tariff = tariff;
    hashTable[position].year_issue = year;
    hashTable[position].is_reach = true; cout << "Добавлено" << endl;
    tabsize++;
}
//вывод на экран
void SimCards::PrintSim()
{
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hashTable[i].sim_card_num != "")
        {
            cout << "Номер Sim-card: " << hashTable[i].sim_card_num << endl;
            cout << "Тариф: " << hashTable[i].tariff << endl;
            cout << "Год выпуска Sim-card: " << hashTable[i].year_issue << endl;
            cout << "Наличие Sim-card: " << hashTable[i].is_reach << endl;
            cout << "__________________" << endl;
            count++;
        }
    }
    if (count == 0) {
        cout << "Нет зарегистрированных SIM-card" << endl;
    }
}
//удаление
void SimCards::DeleteSim()
{
    string sim_card = Sim_Check();
    int i = 0;
    int position = Hash_Func1(i, sim_card);
    while ((hashTable[position].sim_card_num != sim_card && i < TABLE_SIZE))
    {
        if (hashTable[position].sim_card_num == "" && hashTable[position].del == false)
            break;
        else
        {
            position = Hash_Func1(i, sim_card);
            i++;
        }
    }
    if (hashTable[position].sim_card_num != sim_card)
    {
        cout << "Такой Sim-card нет" << endl;
        cout << "__________________" << endl;
    }
    else if (hashTable[position].is_reach == true)
    {
        hashTable[position].sim_card_num = "";
        hashTable[position].del = true;
        hashTable[position].tariff = "";
        hashTable[position].year_issue = 0;
        hashTable[position].is_reach = false;
        tabsize--;
        cout << "Данные о Sim-card удалены" << endl;
        cout << "__________________" << endl;
    }
    else
    {
        cout << "Sim-card нельзя удалить, она оформлена на клиента" << endl;
        cout << "__________________" << endl;
    }
}
//очистка
void SimCards::Cleaning()
{
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hashTable[i].sim_card_num != "")
        {
            hashTable[i].sim_card_num = "";
            hashTable[i].del = false;
            hashTable[i].tariff = "";
            hashTable[i].year_issue = 0;
            hashTable[i].is_reach = false;
            count++;
        }
    }
    if (count > 0)
    {
        tabsize = 0;
        cout << "Данные удалены" << endl;
        cout << "______________" << endl;
    }
    else
    {
        cout << "Нет зарегистрированных Sim-card" << endl;
        cout << "_______________________________" << endl;
        system("pause");
    }
}
//поиск Sim-card по тарифу
void SimCards::SearchSimCardToTariff()
{
    string tariff;
    cin.ignore();
    cout << "Введите тариф Sim-card: ";
    getline(cin, tariff);
    bool flag = false;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hashTable[i].tariff == tariff)
        {
            cout << "Номер Sim-card: " << hashTable[i].sim_card_num << endl;
            cout << "Тариф: " << hashTable[i].tariff << endl;
            cout << "Год выпуска: " << hashTable[i].year_issue << endl;
            cout << "_____________________" << endl;
            flag = true;
        }
    }
    if (flag == false) cout << "Sim-card с таким тарифом нет" << endl;
}
//поиск по номеру Sim-card для проверки возможности её выдачи
bool SimCards::SearchSimCardforIssue()
{
    string sim_card = Sim_Check();
    int i = 0;
    int position = Hash_Func1(i, sim_card);
    while ((hashTable[position].sim_card_num != sim_card && i < TABLE_SIZE))
    {
        position = Hash_Func1(i, sim_card);
        i++;
    }
    if (hashTable[position].sim_card_num == sim_card && hashTable[position].is_reach == true)
        return true;
    cout << "Sim-карта не подходит для выдачи" << endl;
    cout << "______________________________" << endl;
    return false;
}
//поиск по номеру Sim-card для проверки возможности её возврата
bool SimCards::SearchSimCardforReturn()
{
    string sim_card = Sim_Check();
    int i = 0;
    int position = Hash_Func1(i, sim_card);
    while ((hashTable[position].sim_card_num != sim_card && i < TABLE_SIZE))
    {
        position = Hash_Func1(i, sim_card);
        i++;
    }
    if (hashTable[position].sim_card_num == sim_card && hashTable[position].is_reach == false)
        return true;
    cout << "Sim-карта не подходит для возврата" << endl;
    cout << "______________________________" << endl;
    return false;
}
//поиск по номеру Sim-card для выдачи
void SimCards::SimCardIssue(string sim_card)
{
    int i = 0; int position = Hash_Func1(i, sim_card);
    while ((hashTable[position].sim_card_num != sim_card && i < TABLE_SIZE))
    {
        position = Hash_Func1(i, sim_card); i++;
    }
    if (hashTable[position].sim_card_num == sim_card && hashTable[position].is_reach == true)
    {
        hashTable[position].is_reach = false;
    }
}
//поиск по номеру Sim-card для возврата
void SimCards::SimCardReturn(string sim_card)
{
    int i = 0; int position = Hash_Func1(i, sim_card);
    while ((hashTable[position].sim_card_num != sim_card && i < TABLE_SIZE))
    {
        position = Hash_Func1(i, sim_card);
        i++;
    }
    if (hashTable[position].sim_card_num == sim_card && hashTable[position].is_reach == false)
    {
        hashTable[position].is_reach = true;
    }
}
//поиск по номеру Sim-card
void SimCards::SearchSimCardForNum(string* findpas)
{
    string sim_card = Sim_Check();
    int i = 0;
    int position = Hash_Func1(i, sim_card);
    while (hashTable[position].sim_card_num != sim_card && i < TABLE_SIZE)
    {
        if (hashTable[position].sim_card_num == "" && hashTable[position].del == false)
            break;
        else
        {
            position = Hash_Func1(i, sim_card);
            i++;
        }
    }
    if (hashTable[position].sim_card_num != sim_card)
    {
        cout << "Такой Sim-карты нет" << endl;
    }
    else
    {
        *findpas = sim_card;
        cout << "Номер Sim-card: " << hashTable[i].sim_card_num << endl;
        cout << "Тариф: " << hashTable[i].tariff << endl;
        cout << "Год выпуска Sim-card: " << hashTable[i].year_issue << endl;
        cout << "Наличие Sim-card: " << hashTable[i].is_reach << endl; cout << "__________________" << endl;
    }
}