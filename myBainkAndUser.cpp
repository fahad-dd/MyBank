#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>


using namespace std;



struct SCliun
{
    string ClientNum;
    string CountNumber;
    string ponFon;
    string poineCod;
    double Balns = 0;
    bool MarkofAount = false;
};
enum enEnpotClien { enShoeCliunLaste = 1, enAddNowClients = 2, enDalsetClient = 3, enUpdateClaentInfo = 4, enFindClinet = 5, ShowTransactionsMenue = 6, enMangaMenueUser = 7, enLogoun = 8 };
enum enUsers { enLastrUser = 1, enAddUser = 2, enDaletUser = 3, enUpdateUser = 4, enFinudUser = 5, MainMen = 6 };
enum enETransActions { enDeposit = 1, enWithdraw = 2, enTotalBalans = 3, MainMea = 4 };
enum enPMainMenueOprions {
    eAll = -1, PListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
    pUpdateClient = 8, pFindClient = 16, pTranactions = 32, pManageUser = 64
};
const string NumFileClient = "Clien.txt";
const string NumeFileUser = "User.txt";

struct SUser
{
    string UserNum;
    string Pspord;
    int Reform = 0;
    bool MarkofNuem = false;

};
SUser CurentUser;

void shoeMainManeUserScreen();
void ShwMainManewCleint();
void ShwMeinmaienTransActionsScrrain();
void Login();
bool CheckAcooessPermission(enPMainMenueOprions Permission);
void ShowAccessDeiedMessage();
vector <string> SplitString(string S1, string Sepertor = "#//#")
{
    vector<string>VClient;
    short Pos = 0;
    string Line;
    while ((Pos = S1.find(Sepertor)) != std::string::npos)
    {
        Line = S1.substr(0, Pos);
        if (Line != " ")
        {
            VClient.push_back(Line);
        }

        S1.erase(0, Pos + Sepertor.length());

    }
    if (S1 != " ")
    {
        VClient.push_back(S1);
    }
    return VClient;
}
SCliun CountSringToStrucg(string Line, string Dalem = "#//#")
{
    vector <string> VCline = SplitString(Line, Dalem);
    SCliun Sclient;
    Sclient.CountNumber = VCline[0];
    Sclient.ClientNum = VCline[1];
    Sclient.poineCod = VCline[2];
    Sclient.ponFon = VCline[3];
    Sclient.Balns = stod(VCline[4]);
    return Sclient;
}
vector <SCliun> LoapClientFiuale(string Faile)
{
    fstream DataeClain;
    vector <SCliun> VClient;

    DataeClain.open(Faile, ios::in);
    if (DataeClain.is_open())
    {
        string Line;
        SCliun SClient;

        while (getline(DataeClain, Line))
        {
            SClient = CountSringToStrucg(Line, "#//#");
            VClient.push_back(SClient);

        }
        DataeClain.close();
    }
    return VClient;
}
string ConvertRecordToLien(SCliun Clent, string Dalem = "#//#")
{
    string Lien;
    Lien = Clent.CountNumber + Dalem + Clent.ClientNum + Dalem + Clent.poineCod + Dalem + Clent.ponFon + Dalem + to_string(Clent.Balns);
    return Lien;
}
bool ClientExistByAcountNuber(string CountNuber, string NumberFile)
{
    fstream DatraClient;
    SCliun Client;
    DatraClient.open(NumberFile, ios::in); // Moad in

    if (DatraClient.is_open())// is opain
    {
        string Lien;
        while (getline(DatraClient, Lien))
        {
            Client = CountSringToStrucg(Lien, "#//#");

            if (Client.CountNumber == CountNuber)
            {
                DatraClient.close();
                return true;
            }

        }
    }
    DatraClient.close();
    return false;
}
string RaedAcouentNumber(string Maseg)
{
    string CoentNumber;
    cout << Maseg << "\n";
    getline(cin >> ws, CoentNumber);
    return CoentNumber;
}
bool FiuendClienfBuAcountNumber(string AcouentNumber, vector<SCliun>Vclient, SCliun& Client)
{
    for (SCliun& C : Vclient)
    {
        if (C.CountNumber == AcouentNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
void PeintinfiClientLast(SCliun Client)
{
    cout << "|" << setw(16) << left << Client.CountNumber;
    cout << "|" << setw(10) << left << Client.poineCod;
    cout << "|" << setw(40) << left << Client.ClientNum;
    cout << "|" << setw(12) << left << Client.ponFon;
    cout << "|" << setw(12) << left << Client.Balns;

}
void PreintsckeinInfoClent(SCliun C)
{

    cout << "\t\t============================\n";
    cout << "\t\t\t Info Client\n";
    cout << "\t\t============================\n";
    cout << "\t\t- - - - - - - - - - - - - - - - - \n";
    cout << "\t\tCouNumb  : " << C.CountNumber << "\n";
    cout << "\t\tNumClient:" << C.ClientNum << "\n";
    cout << "\t\tPoninCod :" << C.poineCod << "\n";
    cout << "\t\tPonFoain :" << C.ponFon << "\n";
    cout << "\t\tBalans   :" << C.Balns << "\n";
    cout << "\t\t- - - - - - - - - - - - - - - - - \n";
}
SCliun ChangeClientRecord(string CoountNumber)
{
    SCliun  C;
    C.CountNumber = CoountNumber;
    cout << "Enter Num? "; getline(cin >> ws, C.ClientNum);
    cout << "Enter Poin Coud/"; getline(cin >> ws, C.poineCod);
    cout << "Enter Poin Fon ?"; getline(cin >> ws, C.ponFon);
    cout << "Enter Balein?"; cin >> C.Balns;
    return C;
}
bool MarkofDalaetByAccountNumber(vector<SCliun>& V, string Coun)
{
    for (SCliun& C : V)
    {
        if (C.CountNumber == Coun)
        {
            C.MarkofAount = true;
            return true;
        }
    }
    return false;
}
void AddClentFaile(string NumFail, string Lien)
{
    fstream DataFile;
    DataFile.open(NumFail, ios::app);
    if (DataFile.is_open())
    {
        DataFile << Lien << "\n";
    }

    DataFile.close();
}
void SaevCleintFaile(vector<SCliun>V, string NumFile)
{
    fstream DatFile;
    DatFile.open(NumFileClient, ios::out);
    if (DatFile.is_open())
    {
        for (SCliun C : V)
        {
            if (C.MarkofAount != true)
            {
                string Lien = ConvertRecordToLien(C, "#//#");
                DatFile << Lien << "\n";
            }
        }
    }
    DatFile.close();

}
SCliun RaedNewCliient()
{
    SCliun AddCleint;
    cout << "Enter Count Number?\n";
    getline(cin >> ws, AddCleint.CountNumber);

    while (ClientExistByAcountNuber(AddCleint.CountNumber, NumFileClient))
    {
        cout << "\nClaent With [" << AddCleint.CountNumber << "] already Exists, Enter another ?\n";
        cout << "\nEnter Count Number?\n";
        getline(cin >> ws, AddCleint.CountNumber);
    }
    cout << "Enter Num \n";
    getline(cin >> ws, AddCleint.ClientNum);
    cout << "Enter Poin.?\n";
    getline(cin >> ws, AddCleint.poineCod);
    cout << "Enter Poin Fon..?\n";
    getline(cin >> ws, AddCleint.ponFon);
    cout << "Enter Balns..? \n";
    cin >> AddCleint.Balns;
    return AddCleint;

}
void AddNewClient()
{
    SCliun Client;
    Client = RaedNewCliient();
    AddClentFaile(NumFileClient, ConvertRecordToLien(Client));
}
void AddClients()
{


    char AddCMor = 'Y';
    do
    {
        cout << "Adding New Client \n\n";
        AddNewClient();
        cout << "\n Cleint Add Succfule, do you Wient to Add Mor Clients ? y / N\n";
        cin >> (AddCMor);
    } while (toupper(AddCMor == 'Y'));
}
bool UpdateClentsInfo(vector<SCliun>Vclient, string AcourntNumber)
{
    char inpot = 'N';

    SCliun c;

    if (FiuendClienfBuAcountNumber(AcourntNumber, Vclient, c))
    {
        PreintsckeinInfoClent(c);
        cout << " Are you suer Waent Update this Client? y/N "; cin >> inpot;
        if (inpot != 'N')
        {
            for (SCliun& C : Vclient)
            {

                if (C.CountNumber == AcourntNumber)
                {
                    C = ChangeClientRecord(C.CountNumber);
                    break;
                }
            }
        }
        SaevCleintFaile(Vclient, NumFileClient);
        cout << "Client pudat SucrsFaulee\n";
        return true;
    }
    return false;
}
bool DalaetClientByAcouentNumber(vector<SCliun>& Vclent, string Couent)
{
    char Inpot = 'y';

    SCliun C;
    if (FiuendClienfBuAcountNumber(Couent, Vclent, C));
    {
        PreintsckeinInfoClent(C);
        cout << "Yoe Waint Dalet Couent\n";
        cin >> Inpot;

        if (Inpot == 'y')
        {
            MarkofDalaetByAccountNumber(Vclent, Couent);
            SaevCleintFaile(Vclent, "#//#");
            system("cls");
            //Rfrshe Clients
            Vclent = LoapClientFiuale(NumFileClient);
            cout << "Yes Dalet Couent..\n";
            return true;
        }
    }
    return false;

}
void ShwPudateClientInfoScreen()
{
    cout << "______________________________\n";
    cout << "pudate Client Info Screen\n";
    cout << "______________________________\n";

    if (!CheckAcooessPermission(enPMainMenueOprions::pUpdateClient))
    {
        ShowAccessDeiedMessage();
        return;
    }

    vector<SCliun> Vclient = LoapClientFiuale(NumFileClient);
    string AountNumber = RaedAcouentNumber("Enter Count Number ? ");
    UpdateClentsInfo(Vclient, AountNumber);
}
void ShwGotoDaletClent()
{
    cout << "\t\t---------------------------------\n";
    cout << "\t\t\tDalet Claent\n";
    cout << "\t\t---------------------------------\n";

    if (!CheckAcooessPermission(enPMainMenueOprions::pDeleteClient))
    {
        ShowAccessDeiedMessage();
        return;
    }

    vector<SCliun> Voter = LoapClientFiuale(NumFileClient);
    string Couen = RaedAcouentNumber("Enteer Acournt Number..?");
    DalaetClientByAcouentNumber(Voter, Couen);
}
void ShowAddNewClientsScreen()
{
    cout << "\t\t=====================\n";
    cout << "\t\tAdd New Client Screen\n";
    cout << "\t\t=====================\n";

    if (!CheckAcooessPermission(enPMainMenueOprions::pAddNewClient))
    {
        ShowAccessDeiedMessage();
        return;
    }

    AddClients();
}
void PrintFormatLastClient()
{

    if (!CheckAcooessPermission(enPMainMenueOprions::PListClients))
    {
        ShowAccessDeiedMessage();
        return;
    }

    vector <SCliun> Vclien = LoapClientFiuale(NumFileClient);

    cout << "\n\t\t\t\tLasrt Cleint[" << Vclien.size() << "]Client(S)..";
    cout << "\n______________________________________________________________________________________________________________________________";
    cout << "__________________________________________________________________________________________________________________\n" << endl;

    cout << "|" << left << setw(15) << "CountNum";
    cout << "|" << left << setw(10) << "Pin Cod";
    cout << "|" << left << setw(40) << "Client Naum";
    cout << "|" << left << setw(12) << "poinFon";
    cout << "|" << left << setw(12) << "Balns";
    cout << "\n\n________________________________________________________________________________________________________________________\n";
    cout << "_______________________________________________________________________________________________________________________\n" << endl;

    if (Vclien.size() == 0)
    {
        cout << "\t\t\t\tNo Client in  the system!\n";

    }
    else
    {
        for (SCliun C : Vclien)
        {
            PeintinfiClientLast(C);
            cout << "\n";
        }
    }
    cout << "\n___________________________________________________________________________________________________________________________________________________";
    cout << "_____________________________________________________________________________________________\n\n";


}
void SwhFiendClientscreen()
{
    cout << "_________________________________\n";
    cout << "\tFiuen Client Screeen\n";
    cout << "_________________________________\n";
    if (!CheckAcooessPermission(enPMainMenueOprions::pFindClient))
    {
        ShowAccessDeiedMessage();
        return;
    }
    vector<SCliun> Vclient = LoapClientFiuale(NumFileClient);
    string AcountNumber = RaedAcouentNumber(" Enter Acouent Number");
    SCliun Client;
    if (FiuendClienfBuAcountNumber(AcountNumber, Vclient, Client))
    {
        PreintsckeinInfoClent(Client);
    }
    else
    {
        cout << "Client with Acouent[" << AcountNumber << "] is Not Found\n";
    }

}
void DapositBalansClientByAcountNumber(double Amone, string AcountNum, vector<SCliun>& Vclient)
{

    char Inpot = 'y';
    cout << "Are you suer Wnt Perfrom this transaction Y/ N\n"; cin >> Inpot;
    if (toupper(Inpot == 'y'))
    {
        for (SCliun& Dep : Vclient)
        {
            if (Dep.CountNumber == AcountNum)
            {
                Dep.Balns += Amone;
                SaevCleintFaile(Vclient, NumFileClient);
                cout << "\n\n Folwe Scssfluue \n";
                break;
            }
        }
    }

}
void SwhDepostClients()
{
    cout << "--------------------------------\n";
    cout << "\t\tDepos Screen\n";
    cout << "--------------------------------\n";
    vector<SCliun> Vclient = LoapClientFiuale(NumFileClient);
    string AountClient = RaedAcouentNumber("Enter Aount Number");
    SCliun C;
    while (!FiuendClienfBuAcountNumber(AountClient, Vclient, C))
    {
        cout << "Aount with [ " << AountClient << "] Dos nOT exist \n";
        AountClient = RaedAcouentNumber("Enter Aount Number");
    }
    PreintsckeinInfoClent(C);
    double Amon = 0;
    cout << "Enter Depos Amon:"; cin >> Amon;
    DapositBalansClientByAcountNumber(Amon, AountClient, Vclient);
}
void ShwWithDrawScrren()
{
    cout << "------------------------------------\n";
    cout << "\t\tWithdraw Screen\n";
    cout << "------------------------------------\n";
    vector<SCliun> Vclient = LoapClientFiuale(NumFileClient);
    SCliun C;
    string AcourntNumber = RaedAcouentNumber("Enter Acouent Number?");
    while (!FiuendClienfBuAcountNumber(AcourntNumber, Vclient, C))
    {
        cout << "Aount with [ " << AcourntNumber << "] Dos nOT exist \n";
        AcourntNumber = RaedAcouentNumber("Enter Acouent Number?");
    }
    PreintsckeinInfoClent(C);
    double Amount = 0;
    cout << " Plaes Enter Withdraw Amount...? "; cin >> Amount;
    while (Amount > C.Balns)
    {
        cout << " Amount Exceeds the dalance. you can withdraw up to : " << C.Balns << "\n";
        cout << " Plaes Enter Withdraw Amount...? "; cin >> Amount;
    }
    DapositBalansClientByAcountNumber(Amount * -1, AcourntNumber, Vclient);
    cout << "Balens thr  Now :" << C.Balns - Amount << "\n";

}
void PrintScraeninfoBalansClient(SCliun Client)
{
    cout << "|" << setw(20) << left << Client.CountNumber;
    cout << "|" << setw(28) << left << Client.ClientNum;
    cout << "|" << setw(20) << left << Client.Balns;

}
void printFormaScrain()
{
    vector<SCliun>Vclient = LoapClientFiuale(NumFileClient);
    double totalBalns = 0;
    cout << "\n_____________________________________________________________________________________________________________________________";
    cout << "_____________________________________________________________________________________________________________________\n";
    cout << "|" << left << setw(20) << "CountNum";
    cout << "|" << left << setw(25) << "Nuem Client";
    cout << "|" << left << setw(25) << "Baluens";
    cout << "\n______________________________________________________________________________________________________________________________";
    cout << "__________________________________________________________________________________________________________________\n";

    for (SCliun C : Vclient)
    {
        totalBalns += C.Balns;
        PrintScraeninfoBalansClient(C);
        cout << "\n";
    }
    cout << "\n_____________________________________________________________________________________________________________________________";
    cout << "___________________________________________________________________________________________________________________\n";

    cout << "\t\t\t\t\t Totale Blans is : " << totalBalns << "\n";
}
string RaedNumUser()
{
    string Num;
    cout << " Enter User Nuem\n";
    cin >> Num;
    return Num;
}
SUser LienUserTostring(string Lien, string Dliem)
{
    vector< string> vUser = SplitString(Lien, Dliem);
    SUser User;
    User.UserNum = vUser[0];
    User.Pspord = (vUser[1]);
    User.Reform = stoi(vUser[2]);

    return User;
}
vector<SUser>LoadUsersFile(string NumeFile)
{
    fstream DatUser;
    vector<SUser> Vsuser;
    DatUser.open(NumeFile, ios::in);
    if (DatUser.is_open())
    {
        string Lien;
        SUser Suser;
        while (getline(DatUser, Lien))
        {
            Suser = LienUserTostring(Lien, "#//#");
            Vsuser.push_back(Suser);

        }
        DatUser.close();
    }
    return Vsuser;
}
string RaedLogien(string Masg)
{
    string Enter;
    cout << Masg << endl;
    getline(cin >> ws, Enter);
    return Enter;
}
string ConvertUserStringToLien(SUser User, string Daliem = "#//#")
{
    string Lien;
    Lien = User.UserNum + Daliem + User.Pspord + Daliem + to_string(User.Reform);
    return Lien;
}
void printinfoUsers(SUser U)
{

    cout << "|" << setw(33) << left << U.UserNum;
    cout << "|" << setw(28) << left << U.Pspord;
    cout << "|" << setw(24) << left << U.Reform;

}
void SaevinfoUsertoFile(string NumFile, vector<SUser> VUser)
{
    fstream DataUser;
    DataUser.open(NumFile, ios::out);
    if (DataUser.is_open())
    {
        for (SUser u : VUser)
        {
            if (u.MarkofNuem != true)
            {
                string Lien = ConvertUserStringToLien(u);

                DataUser << Lien << "\n";
            }
        }
        DataUser.close();
    }
    DataUser.close();
}
bool UserExistByNem(string AddNum, string NemFile)
{

    fstream Dat;
    Dat.open(NemFile, ios::in);
    if (Dat.is_open())
    {
        string Lien;
        SUser Users;
        while (getline(Dat, Lien))
        {
            Users = LienUserTostring(Lien, "#//#");
            if (Users.UserNum == AddNum)
            {
                Dat.close();

                return true;
            }
        }
    }
    Dat.close();
    return false;
}
int RaedpermissionsToSet()
{
    char Inpo = 'y';
    int Permissions = 0;
    cout << " \nDo you want to give him full reform? y / N\n";
    cin >> Inpo;
    if (toupper(Inpo) == 'Y')
    {

        return -1;
    }

    cout << " Do you waint gief  Access to   \n\n";

    cout << " show Last Client Y/ N\n";
    cin >> Inpo;
    if (toupper(Inpo) == 'Y')
    {
        Permissions = +enPMainMenueOprions::PListClients;
    }

    cout << " Show Add Client  y / N \n"; cin >> Inpo;
    if (toupper(Inpo) == 'Y')
    {

        Permissions += enPMainMenueOprions::pAddNewClient;
    }

    cout << " Show Deleat Client  y / N \n"; cin >> Inpo;
    if (toupper(Inpo) == 'Y')
    {
        Permissions += enPMainMenueOprions::pDeleteClient;
    }

    cout << " Show Updatat Client  y / N \n"; cin >> Inpo;
    if (toupper(Inpo) == 'Y')
    {
        Permissions += enPMainMenueOprions::pUpdateClient;
    }

    cout << " Shw Fiend Client y/ N \n";
    cin >> Inpo;

    if (toupper(Inpo) == 'Y')
    {
        Permissions += enPMainMenueOprions::pFindClient;
    }
    cout << "Main TransactionsMenue y / N\n";
    cin >> Inpo;
    if (Inpo == 'y' || Inpo == 'Y')
    {
        Permissions += enPMainMenueOprions::pTranactions;
    }
    cout << " Main  Usre y /N \n";
    cin >> Inpo;
    if (Inpo == 'y' || Inpo == 'Y')
    {
        Permissions += enPMainMenueOprions::pManageUser;
    }

    return Permissions;
}
void SaevAdduser(string NumFileUs, string Lien)
{
    fstream DatUser;
    DatUser.open(NumFileUs, ios::app);
    if (DatUser.is_open())
    {
        DatUser << Lien << endl;
        DatUser.close();
    }
    DatUser.close();
}
SUser RaedNowUser()
{
    SUser User;
    cout << "Enter Nem "; cin >> User.UserNum;
    while (UserExistByNem(User.UserNum, NumeFileUser))
    {
        cout << "The name is already listed; please add the full name. (There is no match.) \n";
        cout << "Enter Nem "; cin >> User.UserNum;
    }
    cout << "Enter  the Passeord:"; cin >> User.Pspord;

    User.Reform = RaedpermissionsToSet();

    return User;

}
void AddNewUser()
{
    SUser User;
    User = RaedNowUser();
    SaevAdduser(NumeFileUser, ConvertUserStringToLien(User, "#//#"));

}
void GotoAddUser()
{
    SUser User;
    char Inpot = 'Y';
    {
        system("cls");
        AddNewUser();
        cout << " do You Wient Add User y / N \n";
        cin >> Inpot;

    }  while (toupper(Inpot) == 'y');
}
void DalaetUsers(string Num, vector<SUser>& Vuser)
{
    for (SUser& U : Vuser)
    {
        if (U.UserNum == Num)
        {
            U.MarkofNuem = true;

            break;
        }
    }
}
void PrintScreenInfoUser(SUser User)
{
    cout << "- - - - - - - -- - - - - - -- - -  \n";
    cout << "Num:" << User.UserNum << "\n";
    cout << "Paspoerd:" << User.Pspord << "\n";
    cout << "Reform" << User.Reform << "\n";
    cout << "- - - - -- - - - -- - - -- - - -- - \n";
}
bool FindUserByUserAndPassWord(string Num, string Passpword, SUser& User)
{
    vector<SUser> Vuser = LoadUsersFile(NumeFileUser);
    for (SUser U : Vuser)
    {
        if (U.UserNum == Num && U.Pspord == Passpword)
        {
            User = U;
            return true;
        }
    }
    return false;
}
bool FiendUserSystem(vector <SUser>Vuser, string Neum, SUser& User)
{
    for (SUser& U : Vuser)
    {
        if (U.UserNum == Neum)
        {
            User = U;
            return true;
        }
    }
    return false;

}
SUser ChangeUserRecord(string Nuem)
{
    SUser  User;
    User.UserNum = Nuem;
    cout << "Enter Pospoerd Number";  getline(cin >> ws, User.Pspord);
    cout << "Enter Reform..\n";
    return User;

}
void AbduatUserNuem(string UNum, vector<SUser> Vuser)
{
    char Inpo = 'Y';

    cout << "Do you Wient Abduet User Y / N \n";
    cin >> Inpo;
    if (Inpo == 'Y')
    {
        for (SUser& U : Vuser)
        {
            if (U.UserNum == UNum)
            {
                U = ChangeUserRecord(U.UserNum);
                SaevinfoUsertoFile(NumeFileUser, Vuser);
                break;
            }
        }
    }
}
void ShowApduerSceewnUser()
{
    cout << "___________________________\n";
    cout << "Abduet User\n";
    cout << "____________________________\n";
    vector<SUser>Vuser = LoadUsersFile(NumeFileUser);
    SUser Us;
    string UserNum = RaedNumUser();
    while (!FiendUserSystem(Vuser, UserNum, Us))
    {
        cout << "Nuem Not System...[" << UserNum << "]\n";
        string UserNum = RaedNumUser();
    }
    PrintScreenInfoUser(Us);
    AbduatUserNuem(UserNum, Vuser);
    cout << "The changes have been saved\n";

}
void ShowFienScreendNumUser()
{
    cout << "__________________________\n";
    cout << "Fiuend User\n";
    cout << "__________________________\n";
    vector<SUser>Vuser = LoadUsersFile(NumeFileUser);
    SUser User;
    string NumeUser = RaedNumUser();
    while (!FiendUserSystem(Vuser, NumeUser, User))
    {
        cout << " Nuem Use Not System [" << NumeUser << "]\n";
        string NumeUser = RaedNumUser();
    }
    PrintScreenInfoUser(User);
}
void ShowDelaetScreenUser()
{
    cout << "______________________________\n";
    cout << "\t\t\t Dalet User\n";
    cout << "_______________________________\n";
    vector<SUser>Vuser = LoadUsersFile(NumeFileUser);
    SUser User;
    string Num = RaedNumUser();
    while (!FiendUserSystem(Vuser, Num, User))
    {
        system("cls");
        cout << " The Nuem Not system\n";
        string Num = RaedNumUser();
    }
    PrintScreenInfoUser(User);
    if (User.UserNum == "UnerFahad")
    {
        cout << " Uner No Dalaet\n";
    }
    else
    {
        char inpo = 'Y';
        cout << " do You Wient Dalet [" << User.UserNum << "] Y or N \n";
        cin >> inpo;
        if (inpo == 'Y')
        {
            DalaetUsers(Num, Vuser);
            SaevinfoUsertoFile(NumeFileUser, Vuser);
            cout << " User has been deleted\n ";
        }
    }
}
void ShowScreenPeintUser()
{
    vector<SUser>Vuser = LoadUsersFile(NumeFileUser);
    cout << "\t\t\t Last Users [" << Vuser.size() << "]\n";
    cout << "\n_____________________________________________________________________________________________________________________\n";
    cout << "|" << left << setw(33) << "Neum";
    cout << "|" << left << setw(28) << "paspoerd";
    cout << "|" << left << setw(25) << "Refom";
    cout << "\n_____________________________________________________________________________________________________________________\n";
    if (Vuser.size() == 0)
    {
        cout << "NO Not User..?\n";
    }
    else
    {
        for (SUser u : Vuser)
        {
            printinfoUsers(u);
            cout << "\n";
        }
    }
    cout << "\n_____________________________________________________________________________________________________________________\n";


}
void showScreenAddUser()
{
    cout << "=====================\n";
    cout << "\t\tAdd usern\n";
    cout << "=====================\n";
    GotoAddUser();

}
short RaedScreenUser()
{
    short Inpot;
    cout << " Chos what do you want to do {1 to 6]";
    cin >> Inpot;
    return Inpot;
}
void GoToScreenUser()
{
    cout << " go to Screen User Enter \n";
    system("pause>0");
    shoeMainManeUserScreen();
}
void ShowMangerUsers(enUsers Inpout)
{
    switch (Inpout)
    {
    case(enUsers::enLastrUser):
    {
        system("Cls");
        ShowScreenPeintUser();
        GoToScreenUser();
        break;

    }
    case(enUsers::enAddUser):
    {
        system("Cls");
        showScreenAddUser();
        GoToScreenUser();
    }
    case (enUsers::enDaletUser):
    {
        system("cls");
        ShowDelaetScreenUser();
        GoToScreenUser();
        break;
    }
    case(enUsers::enUpdateUser):
    {
        system("cls");
        ShowApduerSceewnUser();
        GoToScreenUser();
        break;
    }
    case(enUsers::enFinudUser):
    {
        system("cls");
        ShowFienScreendNumUser();
        GoToScreenUser();

    }
    case(enUsers::MainMen):
    {
        system("cls");
        ShwMainManewCleint();
        break;;
    }
    }

}
void shoeMainManeUserScreen()
{

    if (!CheckAcooessPermission(enPMainMenueOprions::pManageUser))
    {
        ShowAccessDeiedMessage();
        return;
    }


    system("cls");
    cout << "================================================\n";
    cout << "\t\t\t Main Maine Screen User\n";
    cout << "================================================\n";
    cout << "[1]" << "LastUsees\n";
    cout << "[2]" << "AddNowUser\n";
    cout << "[3]" << "Delaet User\n";
    cout << "[4]" << "Update User\n";
    cout << "[5]" << "FindUser\n";
    cout << "[6]" << "MainMaine\n";
    cout << "================================================\n";
    ShowMangerUsers(enUsers(RaedScreenUser()));

}
short RaedMaiunTransActions()
{
    short Inpot;
    cout << " Chose what do you Want to do ? [1 to 4 ]\n";
    cin >> Inpot;
    return Inpot;
}
void GotoBainkMain()
{
    cout << "\n\nGo to Baink Main....\n";
    system("pause>0");
    ShwMainManewCleint();
}
void ShowAccessDeiedMessage()
{
    cout << "\n____________________________________\n";
    cout << "You don't have the authority to..";
    cout << "\n_____________________________________\n";
    GotoBainkMain();
}
bool CheckAcooessPermission(enPMainMenueOprions Permission)
{
    if (CurentUser.Reform == enPMainMenueOprions::eAll)
        return true;
    if ((Permission & CurentUser.Reform) == Permission)
        return true;
    else
        return false;

}
void GoToTraensactionsScreen()
{
    cout << "\n\ngo to Maine ";
    system("pause>0");
    ShwMeinmaienTransActionsScrrain();

}
short RaedMainManew()
{

    short Number;
    cout << "Enter Hoe Main Munew [1] to [8]" << endl;
    cin >> Number;
    return Number;
}
void AlinpotScraenTransActiond(enETransActions INpot)
{
    switch (INpot)
    {
    case(enETransActions::enDeposit):
    {
        system("cls");
        SwhDepostClients();
        GoToTraensactionsScreen();
        break;
    }
    case(enETransActions::enWithdraw):
    {
        system("cls");
        ShwWithDrawScrren();
        GoToTraensactionsScreen();
        break;
    }
    case(enETransActions::enTotalBalans):
    {
        system("cls");
        printFormaScrain();
        GoToTraensactionsScreen();
        break;
    }
    case(enETransActions::MainMea):
        system("cls");
        GotoBainkMain();
        break;
    }
}
void ShwMeinmaienTransActionsScrrain()
{
    system("cls");
    if (!CheckAcooessPermission(enPMainMenueOprions::pTranactions))
    {
        ShowAccessDeiedMessage();

        return;
    }


    cout << "=====================================\n";
    cout << "\t\t\tTransactions Mean Scran\n";
    cout << "=====================================\n";
    cout << "[1" << "] Deposit\n";
    cout << "[2" << "] Withdraw\n";
    cout << "[3" << "] Total Balans\n";
    cout << "[4" << "] Main Menue\n";
    cout << "=====================================\n";
    AlinpotScraenTransActiond(enETransActions(RaedMaiunTransActions()));

}
void AlInpotScrenCliun(enEnpotClien theAnpot)
{

    switch (theAnpot)
    {
    case(enEnpotClien::enShoeCliunLaste):
    {
        system("cls");
        PrintFormatLastClient();
        GotoBainkMain();
        break;
    }
    case(enEnpotClien::enAddNowClients):
    {
        system("cls");
        ShowAddNewClientsScreen();
        GotoBainkMain();
        break;
    }
    case(enEnpotClien::enDalsetClient):
    {
        system("cls");
        ShwGotoDaletClent();
        GotoBainkMain();
        break;

    }
    case(enEnpotClien::enUpdateClaentInfo):
    {
        system("cls");
        ShwPudateClientInfoScreen();
        GotoBainkMain();
        break;
    }
    case(enEnpotClien::enFindClinet):
    {
        system("Cls");
        SwhFiendClientscreen();
        GotoBainkMain();
        break;
    }
    case(enEnpotClien::ShowTransactionsMenue):
    {
        system("clse");
        ShwMeinmaienTransActionsScrrain();
        break;
    }
    case(enEnpotClien::enMangaMenueUser):
    {
        system("cls");
        shoeMainManeUserScreen();
        break;
    }
    case(enEnpotClien::enLogoun):
    {
        system("cls");
        Login();
        break;
    }
    }
}
void ShwMainManewCleint()
{

    system("cls");
    cout << "\n=============================================\n";
    cout << "\t\t Main Menue Screen\n";
    cout << "\n=============================================\n";

    cout << "\t[1]" << "Show Cline Last\n";
    cout << "\t[2]" << "Add New Cline\n";
    cout << "\t[3]" << "Delet Client\n";
    cout << "\t[4]" << "Updet Client\n";
    cout << "\t[5]" << "Fint Client\n";
    cout << "\t[6]" << "TransaaCtions Menue Screen\n";
    cout << "\t[7]" << "Manage User Screeen\n";
    cout << "\t[8]" << "Logout\n";

    AlInpotScrenCliun(enEnpotClien(RaedMainManew()));
}
bool LoadUserinfo(string Naum, string Password)
{
    SUser infoUser;


    if (FindUserByUserAndPassWord(Naum, Password, CurentUser))
        return true;
    else
        return false;
}
void Login()
{
    bool LoginFaild = false;
    string UserNaun, Password;
    do
    {
        cout << "========================\n";
        cout << "\tLogin\n";
        cout << "========================\n";
        if (LoginFaild)
        {
            cout << " Invlaid UserNaum / PassWord\n";
        }
        cout << "Enter User Naum? ";
        cin >> UserNaun;
        cout << "Entrer PassWord? ";
        cin >> Password;
        LoginFaild = !LoadUserinfo(UserNaun, Password);

    } while (LoginFaild);

    ShwMainManewCleint();

}

int main()
{

    Login();

    system("pause>0");


    return 0;
}