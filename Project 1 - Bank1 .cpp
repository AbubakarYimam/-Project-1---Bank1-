#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
const string FileName = "Clients.txt";

struct sClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

// Read Client
vector <string> splitingstring(string Line, string deli = "#//#") {
    vector <string>vClient;
    string sWord = "";
    short pos = 0;
    while ((pos = Line.find(deli)) != std::string::npos) {
        sWord = Line.substr(0, pos);
        if (sWord != "") {
            vClient.push_back(sWord);
        }
        Line.erase(0, pos + deli.length());
    }
    if (Line != "") {
        vClient.push_back(Line);
    }
    return vClient;
}

sClient ConvertLineToRecord(string Line) {
    sClient Client;
    vector <string> vClient = splitingstring(Line);
    Client.AccountNumber = vClient[0];
    Client.PinCode = vClient[1];
    Client.Name = vClient[2];
    Client.Phone = vClient[3];
    Client.AccountBalance = stod(vClient[4]);

    return Client;

}

vector <sClient> LoadClintFromFile() {
    vector<sClient>vsClient;
    fstream MyFile(FileName, ios::in);
    if (MyFile.is_open()) {
        sClient Client;
        string Line;
        while (getline(MyFile, Line)) {
            Client = ConvertLineToRecord(Line);
            vsClient.push_back(Client);
        }
        MyFile.close();
    }
    return vsClient;
}

// write Client
string ConvertRecordToLine(sClient Client, string sepa = "#//#") {
    string Line;
    Line += Client.AccountNumber + sepa;
    Line += Client.PinCode + sepa;
    Line += Client.Name + sepa;
    Line += Client.Phone + sepa;
    Line += to_string(Client.AccountBalance);

    return Line;
}

short manue() {
    short num;
    cout << "============================================The Main Menue Page =============================\n\n";
    cout << "\t[1] Show All Client " << endl;
    cout << "\t[2] Add New Client" << endl;
    cout << "\t[3] Delete a Client" << endl;
    cout << "\t[4] Update Client" << endl;
    cout << "\t[5] Find Client" << endl;
    cout << "\t[6] Exist" << endl;
    cout << "\n=============================================================================================\n\t\tSelect one of these  : ";
    cin >> num;
    return num;
}

string readAcc() {
    string Acc;
    cout << "Enter Account Number : ";
    cin >> Acc;
    return Acc;
}


void printClient(sClient Client) {
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "Pin Code : " << Client.PinCode << endl;
    cout << "Name : " << Client.Name << endl;
    cout << "Phone : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;
}

// [1] show Client
void PrintClientData(sClient Client) {
    cout << "|" << setw(20) << left << Client.AccountNumber;
    cout << "|" << setw(20) << left << Client.PinCode;
    cout << "|" << setw(20) << left << Client.Name;
    cout << "|" << setw(20) << left << Client.Phone;
    cout << "|" << setw(20) << left << Client.AccountBalance;
}

void displayClient(vector<sClient> vsClient) {
    cout << "\n==============================================================================================================\n";
    cout << "|" << setw(20) << left << "Account Number ";
    cout << "|" << setw(20) << left << "Pin Code ";
    cout << "|" << setw(20) << left << "Name ";
    cout << "|" << setw(20) << left << "Phone ";
    cout << "|" << setw(20) << left << "Account Balance " << endl;
    cout << "==============================================================================================================\n";
    for (sClient s : vsClient) {
        if (s.MarkForDelete == false) {
            PrintClientData(s);
            cout << "\n";
        }
    }
    cout << "==============================================================================================================\n";
}

// [2] Add New
sClient AddNew(vector<sClient>& vsClient) {
    sClient Client;
    cout << "\nEnter Client Information\n";
    cout << "--------------------------\n";
    while (true) {
        cout << "Enter Account Number : ";
        getline(cin >> ws, Client.AccountNumber);
        bool exists = false;
        for (sClient& s : vsClient) {
            if (s.AccountNumber == Client.AccountNumber) {
                exists = true;
                cout << "\nThis Account Number already exists. Please enter again.\n";
                break;
            }
        }
        if (!exists)
            break;
    }
    cout << "Enter Pin Code : ";
    getline(cin, Client.PinCode);
    cout << "Enter Name : ";
    getline(cin, Client.Name);
    cout << "Enter Phone : ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance : ";
    cin >> Client.AccountBalance;
    vsClient.push_back(Client);
    cout << "\nClient added successfully!\n";
    return Client;
}

void AddOnFile(sClient vsClient) {
    fstream MyFile(FileName, ios::app);
    MyFile << ConvertRecordToLine(vsClient) << endl;

    MyFile.close();

}

// [3] delete
bool FindClientToDelete(vector<sClient>& vsClient, string Acc, sClient& Client) {
    for (sClient& s : vsClient) {
        if (s.AccountNumber == Acc) {
            s.MarkForDelete = true;
            Client = s;
            return true;
        }
    }
    return false;
}

void WritOnFile(vector<sClient>& vsClient) {
    fstream MyFile(FileName, ios::out);
    for (sClient& s : vsClient) {
        if (s.MarkForDelete == false) {
            MyFile << ConvertRecordToLine(s) << endl;
        }
    }
    MyFile.close();
}

void showTheDelete(vector <sClient>& vsClient) {
    sClient Client;
    char is = 'y';

    while (true) {
        string Acc = readAcc();
        if (FindClientToDelete(vsClient, Acc, Client)) {
            printClient(Client);
            cout << "\nDo Want To Delete The Client (y/n)?  ";
            cin >> is;
            if (is == 'y') {
                WritOnFile(vsClient);
                cout << "\n\t\tDelete Succesfully .\n";
            }
            break;

        }

        else {
            cout << "\nThe Account Number(" << Acc << ") : Not Found!\n";
        }
    }
}

// [4] Update
sClient Update() {
    sClient Client;
    cout << "Update The Client Info\n\n";
    cout << "Enter Account Number : ";
    getline(cin >> ws, Client.AccountNumber);
    cout << "Enter Pin Code : ";
    getline(cin, Client.PinCode);
    cout << "Enter Name : ";
    getline(cin, Client.Name);
    cout << "Enter Phone : ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance : ";
    cin >> Client.AccountBalance;

    return Client;
}

bool FindClientToUpdate(vector<sClient>& vsClient, string Acc, sClient& Client) {
    for (sClient& s : vsClient) {
        if (s.AccountNumber == Acc) {
            Client = s;
            return true;
        }
    }
    return false;
}

void ShowTheUpdate(vector<sClient>& vsClient) {
    sClient Client;
    char is = 'n';
    while (true) {
        string Acc = readAcc();
        if (FindClientToUpdate(vsClient, Acc, Client)) {
            printClient(Client);

            cout << "\nDo You Want To updaten(y/n) ? ";
            cin >> is;

            if (is == 'y') {
                for (sClient &s : vsClient) {
                    if (s.AccountNumber == Acc) {
                        s = Update();
                    }
                }
               
                WritOnFile(vsClient);
                cout << "\nClient Update Succesfully !\n";

            }
            break;
        }
        else {
            cout << "\nThe Account Number(" << Acc << ") : Not Update Found!\n";
        }
    }
}

bool isExisted(string Acc, vector<sClient> vsClient, sClient& Client) {
    for (sClient s : vsClient) {
        if (s.AccountNumber == Acc) {
            Client = s;
            return true;
        }
    }
    return false;
}

void ShowClients(vector<sClient> vsClient) {
    string Acc = readAcc();
    sClient Client;
    if (isExisted(Acc, vsClient, Client)) {
        printClient(Client);
    }
    else {
        cout << "\nThe Account Number (" << Acc << ") Not Found !\n";

    }
}

void Choose(short num, vector<sClient>& Client, string& Acc, bool& dot) {
    switch (num) {
    case 1: {
        displayClient(Client);
        break;
    }
    case 2: {
        AddOnFile(AddNew(Client));
        break;
    }
    case 3:
        showTheDelete(Client);
        break;
    case 4: {
        ShowTheUpdate(Client);
        break;
    }
    case 5: {
        ShowClients(Client);
        break;
        
    }
    case 6 :
        dot = false;
        break;

    default:
        cout << "\n\n\t\t\tError  \n";

    }
}

void TheMainPage(vector<sClient>& Client, string& Acc) {
    char is = 'y';
    bool dot = true;
    do {
        system("cls");
        Choose(manue(), Client, Acc, dot);
        if (dot) {
            cout << "do want to ReTurn To the Menue  : ";
            cin >> is;
        }

    } while (is == 'y' && dot == true);
}

int main()
{
    string Acc;
    vector<sClient> Client = LoadClintFromFile();
    TheMainPage(Client, Acc);

}
