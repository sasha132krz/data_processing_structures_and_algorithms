#include "Hash.h"

using namespace std;

int SimCards::Hash_Func1(int i, string key)//���-�������
{
    int index_1 = 13 * (int(key[0]) + int(key[1]) + int(key[2])) + 18 * (int(key[4])
        + int(key[5]) + int(key[6])) + 3 * (int(key[7]) + int(key[8]) + int(key[9]) + int(key[10]));
    int index_2 = 5 * (int(key[0]) + int(key[1]) + int(key[2])) + 12 * (int(key[4])
        + int(key[5]) + int(key[6])) + 7 * (int(key[7]) + int(key[8]) + int(key[9]) + int(key[10]));
    int position = index_1 + i * index_2;
    return(position % TABLE_SIZE);
}
// ��� �������� ����� �����
void SimCards::IsDigit(int& digit)
{
    cin >> digit; // ���� �����
    while (cin.fail() || (cin.rdbuf()->in_avail() > 1))
    {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail()); cout << "������� ����� ��������: ";
        cin >> digit;
    }
}
//�������� ������������ ������ Sim-card
string SimCards::Sim_Check()
{
    string key;
    bool flag = false;//����
    regex re("[0-9]{3}-[0-9]{7}");
    cout << "������� ����� Sim-card (������� NNN-NNNNNNN): ";
    while (flag == false)
    {
        cin >> key;
        if (regex_match(key, re))
        {
            flag = true;
        }
        else
            cout << "����� Sim-card ������ �������, ��������� ����: ";
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
//���������� Sim-card
void SimCards::AddSim()
{
    if (tabsize == TABLE_SIZE)
        resize();
    string sim_card = Sim_Check();
    int i = 0;
    int position = Hash_Func1(i, sim_card);
    while ((hashTable[position].sim_card_num != ""))
    {
        if (hashTable[position].sim_card_num == sim_card)//�������� �� ������������
        {
            cout << "��� ������������ ����� Sim-card" << endl; sim_card = Sim_Check();
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
    cout << "������� ����� Sim-card: ";
    getline(cin, tariff);
    int year; cout << "������� ��� ������� SIM-�����: ";
    IsDigit(year);
    hashTable[position].sim_card_num = sim_card;
    hashTable[position].tariff = tariff;
    hashTable[position].year_issue = year;
    hashTable[position].is_reach = true; cout << "���������" << endl;
    tabsize++;
}
//����� �� �����
void SimCards::PrintSim()
{
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hashTable[i].sim_card_num != "")
        {
            cout << "����� Sim-card: " << hashTable[i].sim_card_num << endl;
            cout << "�����: " << hashTable[i].tariff << endl;
            cout << "��� ������� Sim-card: " << hashTable[i].year_issue << endl;
            cout << "������� Sim-card: " << hashTable[i].is_reach << endl;
            cout << "__________________" << endl;
            count++;
        }
    }
    if (count == 0) {
        cout << "��� ������������������ SIM-card" << endl;
    }
}
//��������
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
        cout << "����� Sim-card ���" << endl;
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
        cout << "������ � Sim-card �������" << endl;
        cout << "__________________" << endl;
    }
    else
    {
        cout << "Sim-card ������ �������, ��� ��������� �� �������" << endl;
        cout << "__________________" << endl;
    }
}
//�������
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
        cout << "������ �������" << endl;
        cout << "______________" << endl;
    }
    else
    {
        cout << "��� ������������������ Sim-card" << endl;
        cout << "_______________________________" << endl;
        system("pause");
    }
}
//����� Sim-card �� ������
void SimCards::SearchSimCardToTariff()
{
    string tariff;
    cin.ignore();
    cout << "������� ����� Sim-card: ";
    getline(cin, tariff);
    bool flag = false;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hashTable[i].tariff == tariff)
        {
            cout << "����� Sim-card: " << hashTable[i].sim_card_num << endl;
            cout << "�����: " << hashTable[i].tariff << endl;
            cout << "��� �������: " << hashTable[i].year_issue << endl;
            cout << "_____________________" << endl;
            flag = true;
        }
    }
    if (flag == false) cout << "Sim-card � ����� ������� ���" << endl;
}
//����� �� ������ Sim-card ��� �������� ����������� � ������
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
    cout << "Sim-����� �� �������� ��� ������" << endl;
    cout << "______________________________" << endl;
    return false;
}
//����� �� ������ Sim-card ��� �������� ����������� � ��������
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
    cout << "Sim-����� �� �������� ��� ��������" << endl;
    cout << "______________________________" << endl;
    return false;
}
//����� �� ������ Sim-card ��� ������
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
//����� �� ������ Sim-card ��� ��������
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
//����� �� ������ Sim-card
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
        cout << "����� Sim-����� ���" << endl;
    }
    else
    {
        *findpas = sim_card;
        cout << "����� Sim-card: " << hashTable[i].sim_card_num << endl;
        cout << "�����: " << hashTable[i].tariff << endl;
        cout << "��� ������� Sim-card: " << hashTable[i].year_issue << endl;
        cout << "������� Sim-card: " << hashTable[i].is_reach << endl; cout << "__________________" << endl;
    }
}