#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;
struct ClientData
{
    string Account_Number;
    string PinCode;
    string Client_Name;
    string PhoneNumber;
    long double AccountBalance = 0;
    bool markfordelete = false;
};
enum WithdrawChoices
{
    one = 20,
    two = 50,
    three = 100,
    four = 200,
    five = 400,
    six = 600,
    seven = 800,
    eight = 1000
};
const string filename = "ClientsDATA.txt";
ClientData CLIENT;
void ClientLogin();
void ATM_Main_Menue_Screen();

vector <string> Split(string STRING, string delim)
{
    vector <string> VECTOR;

    int pos = 0;
    string sword;
    while ((pos = STRING.find(delim)) != std::string::npos)
    {
        sword = STRING.substr(0, pos);
        if (sword != "")
        {
            VECTOR.push_back(sword);
        }
        STRING.erase(0, pos + delim.length());
    }
    if (STRING != "")
    {
        VECTOR.push_back(STRING);
    }

    return VECTOR;
}
ClientData Client_Record(string str)
{
    ClientData CD;
    vector <string> vstruct = Split(str, "#//#");
    CD.Account_Number = vstruct[0];
    CD.PinCode = vstruct[1];
    CD.Client_Name = vstruct[2];
    CD.PhoneNumber = vstruct[3];
    CD.AccountBalance = stod(vstruct[4]);
    return CD;
}
string ClientRecord(ClientData CD, string Delim)
{

    string RECORD = "";
    RECORD = CD.Account_Number + Delim;
    RECORD = RECORD + CD.PinCode + Delim;
    RECORD = RECORD + CD.Client_Name + Delim;
    RECORD = RECORD + CD.PhoneNumber + Delim;
    RECORD = RECORD + to_string(CD.AccountBalance);
    return RECORD;

}
void SHOWClientDATA(ClientData CD)
{
    cout << "|" << left << setw(18) << CD.Account_Number << "| " << left << left << setw(11) << CD.PinCode << "| " << left << setw(48) << CD.Client_Name << " | " << left << setw(10) << CD.PhoneNumber << "|" << left << setw(12) << CD.AccountBalance << endl;

}
vector <ClientData> PrintDataFromFile_ClientsDATA_()
{
    vector <ClientData> VClient;
    ClientData CD;
    fstream File;
    File.open(filename, ios::in);
    if (File.is_open())
    {
        string line;
        while (getline(File, line))
        {
            CD = Client_Record(line);
            VClient.push_back(CD);

        }
        File.close();
    }
    return VClient;
}
vector <ClientData> saveVectorTofile(vector <ClientData> VClient)
{
    fstream FILE;
    FILE.open(filename, ios::out);
    string data = "";
    if (FILE.is_open())
    {

        for (ClientData& C : VClient)
        {
            if (C.markfordelete == false)
            {
                data = ClientRecord(C, "#//#");
                FILE << data << endl;
            }
        }
        FILE.close();
    }
    return VClient;
}

int CHOICES(short userchoice)
{
    switch (userchoice)
    {
    case 1:
        return WithdrawChoices::one;
        break;
    case 2:
        return WithdrawChoices::two;
        break;
    case 3:
        return WithdrawChoices::three;
        break;
    case 4:
        return WithdrawChoices::four;
        break;
    case 5:
        return WithdrawChoices::five;
        break;
    case 6:
        return WithdrawChoices::six;
        break;
    case 7:
        return WithdrawChoices::seven;
        break;
    case 8:
        return WithdrawChoices::eight;
        break;
    default:
        return 0;
        break;
    }
}
void Change_AccountBalance_In_File(vector <ClientData>& vClients, int&Balance)
{
    for (ClientData& Client : vClients)
    {
        if (Client.Account_Number == CLIENT.Account_Number && Client.PinCode == CLIENT.PinCode)
        {
            Client.AccountBalance = Balance;
            CLIENT.AccountBalance = Balance;
            break;
        }

    }
    saveVectorTofile(vClients);
    vClients = PrintDataFromFile_ClientsDATA_();
}
void Show_Quick_WithDraw(vector <ClientData> vClients)
{
    system("cls");
    system("color 5f");
    short UserChoice = 0;
    char UserChoice2 = ' ';
    int balance = 0;
    cout << "=======================================\n";
    cout << "\tQuick Withdraw         " << endl;
    cout << "=======================================\n";
    cout << "        [1] 20           [2] 50        \n";
    cout << "        [3] 100          [4] 200        \n";
    cout << "        [5] 400          [6] 600        \n";
    cout << "        [7] 800          [8] 1000        \n";
    cout << "        [9] Exit        \n";
    cout << "=======================================\n";
    cout << "Your Balance is " << CLIENT.AccountBalance << endl;

    while (UserChoice < 1 || UserChoice > 9)
    {
        cout << "\nChoose what to Withdraw from[1] to [8] ?  ";
        cin >> UserChoice;
    }

    if (UserChoice == 9)
        return;
    
    if ((CLIENT.AccountBalance - CHOICES(UserChoice)) < 0)
    {
        cout << "\nThe amount exceeds your balance, make another choice." << endl;
        cout << "Press Anykey to continue..." << endl;
        system("pause>0");
        Show_Quick_WithDraw(vClients);
    }

    cout << "\nAre You Sure You Want Perform This Transaction? y/n ?  ";
    cin >> UserChoice2;


    if (UserChoice2 == 'y' || UserChoice2 == 'Y')
    {
        balance = CLIENT.AccountBalance - CHOICES(UserChoice);
        Change_AccountBalance_In_File(vClients, balance);
        cout << "\nDone Successfully. New Balance is : " << balance << endl;
    }


}
void Show_Balance_Screen(vector <ClientData> vClients)
{
    system("cls");
    system("color 5f");
    cout << "=======================================\n";
    cout << "\tCheck Balance Screen        " << endl;
    cout << "=======================================\n";
    cout << "Your Balance is " << CLIENT.AccountBalance << endl;
}
void Show_Normal_Withdraw(vector <ClientData> vClients)
{
    system("cls");
    system("color 5f");
    char option = ' ';
    int numberOf5s = 0;
    int NewBalance = 0;
    cout << "=======================================\n";
    cout << "\tNormal Withdraw Screen         " << endl;
    cout << "=======================================\n";
    do
    {
        cout << "\nEnter an amount multiple of 5's ?  ";
        cin >> numberOf5s;

    } while (numberOf5s % 5 != 0);

    if (numberOf5s > CLIENT.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, make another choice." << endl;
        cout << "Press Anykey to continue..." << endl;
        system("pause>0");
        Show_Normal_Withdraw(vClients);
    }

    cout << "\nAre You Sure You Want Perform This Transaction? y/n ?  ";
    cin >> option;

    if (option == 'y' || option == 'Y')
    {
        NewBalance = CLIENT.AccountBalance - numberOf5s;
        Change_AccountBalance_In_File(vClients, NewBalance);
        cout << "\nDone Successfully. New Balance is : " << NewBalance << endl;
    }
}
void Show_Deposit_Screen(vector <ClientData> vClients)
{
    system("cls");
    system("color 5f");
    char option = ' ';
    int AddedValue = 0;
    int BALANCE = 0;
    cout << "=======================================\n";
    cout << "\tDeposit Screen         " << endl;
    cout << "=======================================\n";
    cout << "\nEnter a Positive Deposit Amount? ";
    cin >> AddedValue;
    cout << "\nAre You Sure You Want Perform This Transaction? y/n ?  ";
    cin >> option;

    if (option == 'y' || option == 'Y')
    {
        BALANCE = CLIENT.AccountBalance + AddedValue;
        Change_AccountBalance_In_File(vClients,BALANCE);
        cout << "\nDone Successfully. New Balance is : " << BALANCE << endl;
    }

}

void BackToATMMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...\n";
    system("pause>0");
    ATM_Main_Menue_Screen();
}
void ATM_Main_Menue_Screen()
{
    system("cls");
    system("color 0f");
    vector <ClientData> VClients = PrintDataFromFile_ClientsDATA_();
    short User_Choice = 0;
    cout << "======================================\n";
    cout << "\tATM MAIN MENUE SCREEN" << endl;
    cout << "======================================\n";
    cout << "       [1] Quick WithDraw.         " << endl;
    cout << "       [2] Normal WithDraw.         " << endl;
    cout << "       [3] Deposite.         " << endl;
    cout << "       [4] Check Balance.         " << endl;
    cout << "       [5] Logout.         " << endl;
    cout << "======================================\n";
    cout << "Choose what do you want to do? [1 to 5]? ";
    cin >> User_Choice;
    switch (User_Choice)
    {
    case 1:
        Show_Quick_WithDraw(VClients); 
        BackToATMMainMenue();
        break;
    case 2:
        Show_Normal_Withdraw(VClients);
        BackToATMMainMenue();
        break;

    case 3:
        Show_Deposit_Screen(VClients);
        BackToATMMainMenue();
        break;
    case 4:
        Show_Balance_Screen(VClients);
        BackToATMMainMenue();
        break;
    case 5:
        ClientLogin();
        break;
    }


}
bool SearchingForAccountNumberandPinCode(vector <ClientData> vClients, string AccountNumber, string PinCode, ClientData& client_data)
{
    for (ClientData& client : vClients)
    {
        if (AccountNumber == client.Account_Number && PinCode == client.PinCode)
        {

            client_data = client;
            return true;

        }
    }
    return false;


}
void LoginScreen()
{
    system("cls");
    system("color 8f");
    cout << "\n---------------------------------" << endl;
    cout << "\t Login Screen\t" << endl;
    cout << "---------------------------------" << endl;

}
void ClientLogin()
{
    string AccountNumber;
    string pinCode;

    LoginScreen();
    cout << "Enter AccountNumber? ";
    cin >> AccountNumber;
    cout << "Enter PinCode? ";
    cin >> pinCode;
    vector <ClientData> VClients = PrintDataFromFile_ClientsDATA_();

    while (!SearchingForAccountNumberandPinCode(VClients,AccountNumber,pinCode,CLIENT))
    {
        LoginScreen();
        cout << "Invalid AccountNumber/PinCode!" << endl;
        cout << "Enter AccountNumber? ";
        cin >> AccountNumber;
        cout << "Enter PinCode? ";
        cin >> pinCode;
    }
    ATM_Main_Menue_Screen();
}

int main()
{
    ClientLogin();
}
