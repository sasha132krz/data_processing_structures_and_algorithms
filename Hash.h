#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <regex>
#include <iomanip>

using namespace std;
class SimCards {
public:
    //��������� Sim-���� (���)
    struct SimCard
    {
        string sim_card_num; // �NNN-NNNNNNN� N - �����
        string tariff; // �����
        int year_issue; // ��� ������� SIM-�����
        bool is_reach = false; // �������
        bool del = false;//���� ��������
    };
    int TABLE_SIZE = 1;
    int tabsize = 0;
    SimCards()
    {
        hashTable = new SimCard[TABLE_SIZE];
    }
    ~SimCards()
    {
        delete[] hashTable;
    }
    int Hash_Func1(int i, string key);
    void resize();
    void IsDigit(int& digit);
    SimCard* hashTable;
    string Sim_Check();
    void AddSim();
    void PrintSim();
    void DeleteSim();
    void Cleaning();
    void SearchSimCardToTariff();
    void SearchSimCardForNum(string* findpas);
    void SimCardIssue(string sim_num);
    void SimCardReturn(string sim_num);
    bool SearchSimCardforIssue();
    bool SearchSimCardforReturn();
};