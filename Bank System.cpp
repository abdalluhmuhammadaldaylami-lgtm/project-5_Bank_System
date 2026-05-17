#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <ctime>
using namespace std;

struct stuser{
    string username;
    string password;
    int pass;
    string time;
    bool markuser=false;
};

struct stcleints {
    string acontnumber;
    string pincod;
    string name;
    string phon;
    string blank;
    string time;
    bool markcleint=false;
};

enum entrasactiont {
    Deposit=1,ewithdraw=2,totalblank=3,showmainmenue=4
};

enum enmainmenueoption{
    List_Cleints=1, Add_Cleint=2,
    Delete_Cleint=3,Update_Cleint=4,
    Find_Cleint=5,Deposaction=6,Mananguser=7,Exit=8
};

enum enuser{
    ListUser=1,AddUser=2,DeletUser=3,UpdetUser=4,FindUser=5,mainmenu=6
};

enum enpermintion{
    All=-1,Lestcleint=1,Addcleint=2,Deletcleint=4,Updetcleint=8,Findcleint=16,Transaction=32,Manangusers=64
};

//const string userfile = "/sdcard/Download/users.txt"; // بديل
const string cleintfile("clint.txt");
const string userfile("user.txt");

stuser correntuser;

void ShowMainMenue();
void  Show_transaction_menue();
void Show_Manang_User();

void ClearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
    return string(buffer);
}

vector<string> SepliterString(string v,string g){
    short pos=0;
    string sword;
    vector<string> vstring;
    
    while((pos=v.find(g))!=string::npos){
        sword=v.substr(0,pos);
        if(sword!=""){
            vstring.push_back(sword);
        }
        v.erase(0,pos+g.length());
    }
    if(v!=""){
        vstring.push_back(v);
    }
    return vstring;
}

stcleints converttoline(string line,string dal="//"){
    vector<string> vstring=SepliterString(line,dal);
    stcleints cleint;
    cleint.acontnumber=vstring[0];
    cleint.pincod=vstring[1];
    cleint.name=vstring[2];
    cleint.phon=vstring[3];
    cleint.blank=vstring[4];
    cleint.time=vstring[5];
    return cleint;
}

string Convert_Record(stcleints cleint,string line="//"){
    string dal="";
    dal+=cleint.acontnumber+line;
    dal+=cleint.pincod+line;
    dal+=cleint.name+line;
    dal+=cleint.phon+line;
    dal+=cleint.blank+line;
    dal+=cleint.time;
    return dal;
}

vector<stcleints> loadcleintdata(string filename){
    fstream myfile;
    vector<stcleints> vcleint;
    string line;
    stcleints cleint;
    
    myfile.open(filename,ios::in);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            cleint=converttoline(line);
            vcleint.push_back(cleint);
        }
        myfile.close();
    }
    return vcleint;
}

stuser converttolineuser(string line,string dal="//"){    
    vector<string> vstring=SepliterString(line,dal);
    stuser user;
    user.username=vstring[0];
    user.password=vstring[1];
    user.pass=stoi(vstring[2]);
    user.time=vstring[3];
    return user;
}

string Convert_Record_user(stuser user,string line="//"){
    string dal="";
    dal+=user.username+line;
    dal+=user.password+line;
    dal+=to_string(user.pass)+line;
    dal+=user.time;
    return dal;
}

vector<stuser> Load_user(string filename){
    fstream myfile;
    vector<stuser> vuser;
    string line;
    stuser user;
    
    myfile.open(filename,ios::in);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            user=converttolineuser(line);
            vuser.push_back(user);
        }
        myfile.close();
    }
    return vuser;
}

bool checkAccessPermission(enpermintion permintion){
    if(correntuser.pass==enpermintion::All)
        return true;
    if((permintion&correntuser.pass)==permintion)
        return true;
    else
        return false;
}

bool Finduserandpassword(string username,string passowrd, stuser &resultUser){
    vector<stuser> vuser=Load_user(userfile);
    for(stuser &C : vuser){
        if(C.username == username && C.password == passowrd){
            resultUser = C;
            return true;
        }
    }
    return false;
}

int readpermistion(){
    int permisetion=0;
    char enswar='n';
    
    cout<<"Do you want to give full access [Y/N] ";
    cin>>enswar;
    ClearInputBuffer();
    if(enswar=='y'||enswar=='Y'){
        return -1;
    }
    
    cout<<"Do you want to give access to..? \n";        
    cout<<"Show cleint lest[Y/N] ..";    
    cin>>enswar;
    ClearInputBuffer();
    if(enswar=='y'||enswar=='Y'){
        permisetion+=enpermintion::Lestcleint;
    }    
        
    cout<<"Show add cleint [Y/N] ..";    
    cin>>enswar;
    ClearInputBuffer();
    if(enswar=='y'||enswar=='Y'){
        permisetion+=enpermintion::Addcleint;
    }    
    
    cout<<"Show Delet cleint [Y/N] ..";    
    cin>>enswar;
    ClearInputBuffer();
    if(enswar=='y'||enswar=='Y'){
        permisetion+=enpermintion::Deletcleint;
    }    
        
    cout<<"Show Updet cleint [Y/N] ..";    
    cin>>enswar;
    ClearInputBuffer();
    if(enswar=='y'||enswar=='Y'){
        permisetion+=enpermintion::Updetcleint;
    }
    
    cout<<"Show find cleint [Y/N] ..";    
    cin>>enswar;
    ClearInputBuffer();
    if(enswar=='y'||enswar=='Y'){
        permisetion+=enpermintion::Findcleint;
    }
    
    cout<<"Show Deposaction cleint [Y/N] ..";    
    cin>>enswar;
    ClearInputBuffer();
    if(enswar=='y'||enswar=='Y'){
        permisetion+=enpermintion::Transaction;
    }
        
    cout<<"Show manang cleint [Y/N] ..";    
    cin>>enswar;
    ClearInputBuffer();
    if(enswar=='y'||enswar=='Y'){
        permisetion+=enpermintion::Manangusers;
    }
    return permisetion;
}

void printcleintcarduser(stuser user){    
    cout<<"|"<<left<<setw(13)<<user.username;
    cout<<"|"<<left<<setw(13)<<user.password;        
    cout<<"|"<<left<<setw(16)<<user.pass;
    cout<<"|"<<left<<setw(13)<<user.time;
}

void Show_Lest_User(){
    vector<stuser> vuser=Load_user(userfile);
    
    cout<<"__________________________________________________________________\n";
    cout<<"\t\t\t the cleints ("<<vuser.size()<<") \n";
    cout<<"__________________________________________________________________\n";
    cout<<"|"<<setw(13)<<left<<"\033[47;42m  User Name  \033[0m\a";
    cout<<"|"<<setw(13)<<left<<"\033[47;42m  Passowrd   \033[0m\a";
    cout<<"|"<<setw(20)<<left<<"\033[47;42m   passeaction  \033[0m\a";
    cout<<"|"<<setw(13)<<left<<"\033[47;42m   time    \033[0m\a";
    cout<<"\n__________________________________________________________________\n";
    if(vuser.size()==0){
        cout<<" no cleint in the system ";
    }
    else{
        for(stuser& user:vuser){
            printcleintcarduser(user);
            cout<<endl;
        }
    }
    cout<<"___________________________________________________________________\n";
}

void printuser(stuser user){
    cout<<"______________________\n";
    cout<<"user name   :"<<user.username<<endl;
    cout<<"password    :"<<user.password<<endl;
    cout<<" permacion  :"<<user.pass<<endl;
    cout<<" time   :"<<user.time<<endl;
    cout<<"_______________________\n";
}

string readname(){
    string name;
    cout<<"Enter User Name :";
    getline(cin,name);
    return name;
}

string readpassword(){
    string pass;
    cout<<"Enter Password :";
    getline(cin,pass);
    return pass;
}

bool clientexist_by_acc2(string username, string filename){
    vector<stuser> users = Load_user(filename);
    for(stuser &u : users){
        if(u.username == username)
            return true;
    }
    return false;
}

stuser Read_user(){
    stuser user;
    cout<<" enter user name :";
    getline(cin>>ws,user.username);
    
    cout<<" enter password :";
    getline(cin,user.password);
    
    while(clientexist_by_acc2(user.username,userfile)){
        cout<<"the user name is reserved ["<<user.username<<"]❌ ..\n";
        cout<<" enter the user name :";
        getline(cin>>ws,user.username);
    }
    
    user.pass = readpermistion();
    user.time=getCurrentDateTime();
    
    return user;
}

void Add_to_fileuser(string filename,string data){
    fstream myfile;
    myfile.open(filename,ios::out|ios::app);
    if(myfile.is_open()){
        myfile<<data<<endl;
        myfile.close();
    }
}

bool markuser(string username,vector<stuser>&vuser){
    for(stuser &c:vuser){
        if(c.username==username){
            c.markuser=true;
            return true;
        }
    }
    return false;
}

vector<stuser> seveuser(string filename,vector<stuser> vuser){
    fstream myfile;
    myfile.open(filename,ios::out);
    string data;
    if(myfile.is_open()){
        for(stuser c:vuser){
            if(c.markuser==false){
                data=Convert_Record_user(c);
                myfile<<data<<endl;
            }
        }
        myfile.close();
    }
    return vuser;
}

void showaccessmassag(){
    cout<<"_____________________________________\n";
    cout<<"Access Denide ,\nYou dont Have permission To Do this ,\n please conact \n";
    cout<<"_____________________________________\n";
}

void printcleintcard(stcleints cleint){    
    cout<<"|"<<left<<setw(7)<<cleint.acontnumber;
    cout<<"|"<<left<<setw(7)<<cleint.pincod;        
    cout<<"|"<<left<<setw(17)<<cleint.name;
    cout<<"|"<<left<<setw(11)<<cleint.phon;
    cout<<"|"<<left<<setw(8)<<cleint.blank;
    cout<<"|"<<left<<setw(5)<<cleint.time;
}

void Showlistcleint(){
    if(!checkAccessPermission(enpermintion::Lestcleint)){
        showaccessmassag();
        return;
    }
        
    vector<stcleints> vcleint=loadcleintdata(cleintfile);
    
    cout<<"__________________________________________________________________\n";
    cout<<"\t\t\t the cleints ("<<vcleint.size()<<") \n";
    cout<<"__________________________________________________________________\n";
    cout<<"|"<<setw(6)<<left<<"\033[47;42maccont \033[0m\a";
    cout<<"|"<<setw(5)<<left<<"\033[47;42mpincod \033[0m\a";
    cout<<"|"<<setw(30)<<left<<"\033[47;42mname\033[0m\a";
    cout<<"|"<<setw(24)<<left<<"\033[47;42mphon\033[0m\a";;
    cout<<"|"<<setw(21)<<left<<"\033[47;42mblank \033[0m\a";;
    cout<<"|"<<setw(5)<<left<<"\033[47;42mtime \033[0m\a";
    cout<<"\n__________________________________________________________________\n";
    if(vcleint.size()==0){
        cout<<" no cleint in the system ";
    }
    else{
        for(stcleints& cleint:vcleint){
            printcleintcard(cleint);
            cout<<endl;
        }
    }
    cout<<"___________________________________________________________________\n";
}

void printcleint(stcleints cleint){
    cout << "\nThe following are the client details: ✅\n";
    cout << "--------------------------------\n";
    cout << " Account Number : " << cleint.acontnumber;
    cout << "\n Pin Code       : " << cleint.pincod;
    cout << "\n Name           : " << cleint.name;
    cout << "\n Phone          : " << cleint.phon;
    cout << "\n Account Balance: " << cleint.blank;
    cout << "\n time           : " << cleint.time<<endl;
    cout << "---------------------------------\n";
}

bool chakname(string& name){
    for(char v:name){
        if(!isalpha(v) && v!=' '){
            return false;
        }
    }
    return true;
}

bool chakpincod(string& pin){
    for(char c:pin){
        if(!isdigit(c)){
            return false;
        }
    }
    return true;
}

bool chakphon(string& phon){
    if(phon.length()!=9){
        return false;
    }
    if(phon.substr(0,1)!="7"){
        return false;
    }
    for(char c:phon){
        if(!isdigit(c)){
            return false;
        }
    }
    return true;
}

bool clientexist_by_acc(string accont,string fileName){
    fstream myFile;
    myFile.open(fileName, ios::in);
    if (myFile.is_open()){
        stcleints cleint;
        string line;
        while (getline(myFile, line)){
            cleint = converttoline(line);
            if (cleint.acontnumber == accont){
                myFile.close();
                return true;
            }
        }
        myFile.close();
    }
    return false;
}

stcleints Read_Cleint(){
    stcleints cleint;
    cout<<" enter the accont number :";
    getline(cin>>ws,cleint.acontnumber);
    
    while(clientexist_by_acc(cleint.acontnumber,cleintfile)){
        cout<<"the accont number is reserved ["<<cleint.acontnumber<<"]❌ ..\n";
        cout<<" enter the accont number :";
        getline(cin>>ws,cleint.acontnumber);
    }
    
    do{
        cout<<" enter the pin cod :";
        getline(cin,cleint.pincod);
        if(!chakpincod(cleint.pincod)){
            cout<<"the pin cod which you entered incorect❌ \n";
        }
    }while(!chakpincod(cleint.pincod));
        
    do{
        cout<<" enter the name :";
        getline(cin,cleint.name);
        if(!chakname(cleint.name)){
            cout<<"the name which you entered incorect❌ \n";
        }
    }while(!chakname(cleint.name));
        
    do{
        cout<<" enter the phon number :";
        getline(cin,cleint.phon);
        if(!chakphon(cleint.phon)){
            cout<<"the phon which you entered incorect❌ \n";
        }
    }while(!chakphon(cleint.phon));
    
    do{
        cout<<" enter the accont blank :";
        cin>>cleint.blank;
        ClearInputBuffer();
        if(!chakpincod(cleint.blank)){
            cout<<"the blank which you entered incorect❌ \n";
        }
    }while(!chakpincod(cleint.blank));
    
    cleint.time=getCurrentDateTime();
    
    return cleint;
}

void Add_to_file(string filename,string data){
    fstream myfile;
    myfile.open(filename,ios::out|ios::app);
    if(myfile.is_open()){
        myfile<<data<<endl;
        myfile.close();
    }
}

void Adde_Cleint(){
    stcleints cleint=Read_Cleint();
    Add_to_file(cleintfile,Convert_Record(cleint));
}

void Add_New_Cleints(){
    char cho='y';
    do{
        Adde_Cleint();
        cout<<" Do you want to add another cleint [Y/N]";
        cin>>cho;
        ClearInputBuffer();
    }while(cho=='y'||cho=='Y');
}

bool Find_cleint(string acountnumber, vector<stcleints> vcleint, stcleints& cleint){
    for (stcleints C : vcleint){
        if (C.acontnumber == acountnumber){
            cleint= C;
            return true;
        }
    }
    return false;
}

bool markcleint(string acontnumber,vector<stcleints>&vcleint){
    for(stcleints &c:vcleint){
        if(c.acontnumber==acontnumber){
            c.markcleint=true;
            return true;
        }
    }
    return false;
}

vector<stcleints> sevecleint(string filename,vector<stcleints> vcleint){
    fstream myfile;
    myfile.open(filename,ios::out);
    string data;
    if(myfile.is_open()){
        for(stcleints c:vcleint){
            if(c.markcleint==false){
                data=Convert_Record(c);
                myfile<<data<<endl;
            }
        }
        myfile.close();
    }
    return vcleint;
}

bool deletcleint(string acontnumber,vector<stcleints>&vcleint){
    stcleints cleint;
    char en='no';
    if(Find_cleint(acontnumber,vcleint,cleint)){
        printcleint(cleint);
        cout<<"wat do you delet cleint [y/ N]";
        cin>>en;
        ClearInputBuffer();
        if(en=='y'||en=='Y'){
            markcleint( acontnumber,vcleint);
            sevecleint(cleintfile,vcleint);
            vcleint=loadcleintdata(cleintfile);
            cout<<"cleint delet succsr ✅";
            return true;
        }
    }
    else{
        cout<<"the cleint is ("<<acontnumber<<")not fond ❌ "<<endl;
    }
    return false;
}

string readaconut(){
    string acont;
    cout<<"\n \033[3;33menter the acont number\033[0m :";
    cin>>acont;
    ClearInputBuffer();
    return acont;
}

stcleints chandcleint(string acontnumber){
    stcleints cleint;
    cleint.acontnumber=acontnumber;
    cout<<"enter the pin cod ";
    getline(cin>>ws,cleint.pincod);
    cout<<"enter the name ";
    getline(cin,cleint.name);
    cout<<"enter the phon ";
    getline(cin ,cleint.phon);
    cout<<"enter the blank ";
    getline(cin,cleint.blank);
    cleint.time = getCurrentDateTime();
    
    return cleint;
}

bool Updet_cleint(string acontnumber,vector<stcleints>&vcleint){
    stcleints cleint;
    char en='no';
    if(Find_cleint(acontnumber,vcleint,cleint)){
        printcleint(cleint);
        cout<<"wat do you delet cleint [y/ N]";
        cin>>en;
        ClearInputBuffer();
        if(en=='y'||en=='Y'){
            for(stcleints &c:vcleint){
                if(c.acontnumber==acontnumber){
                    c=chandcleint(acontnumber);
                    break;
                }
            }
            sevecleint(cleintfile,vcleint);
            cout<<"cleint Updet succsr ✅\n";
            return true;
        }
    }
    else{
        cout<<"the cleint is ("<<acontnumber<<")not fond ❌ "<<endl;
    }
    return false;
}

bool transaction(string acontnumber ,double amont,vector<stcleints>&vcleint){
    char ch;
    cout<<"the emont the cleint [Y/N]";
    cin>>ch;
    ClearInputBuffer();
    if (ch=='y'||ch=='Y'){
        for(stcleints &v:vcleint){
            if(v.acontnumber==acontnumber){
                double blenk=stod(v.blank);
                blenk+=amont;
                if(blenk<0){
                    cout<<"insufficient blank <0 :";
                    return false;
                }
                v.blank=to_string((int)blenk);
                v.time=getCurrentDateTime();
                
                sevecleint(cleintfile,vcleint);
                cout<<"\ncleint mony is succsr ✅ ["<<v.blank<<"].\n";
                return true;
            }
        }
    }
    return false;
}

void show_deposaction(){
    stcleints cleint;
    vector<stcleints> vcleint=loadcleintdata(cleintfile);
    string acontnumber=readaconut();
    while(!Find_cleint(acontnumber,vcleint,cleint)){
        cout<<"the acont number ["<<acontnumber<<"] not fond.❌ .?\n ";
        acontnumber=readaconut();
    }
    double amont;
    printcleint(cleint);
    cout<<" enter the amont mony $ :";
    cin>>amont;
    ClearInputBuffer();
    transaction(acontnumber,amont,vcleint);
}

void show_withdraw(){
    stcleints cleint;
    vector<stcleints> vcleint=loadcleintdata(cleintfile);
    string acontnumber=readaconut();
    while(!Find_cleint(acontnumber,vcleint,cleint)){
        cout<<"\nthe acont number ["<<acontnumber<<"] not fond.❌ .?\n ";
        acontnumber=readaconut();
    }
    double amont;
    printcleint(cleint);
    cout<<" enter the amont mony $ :";
    cin>>amont;
    ClearInputBuffer();
    transaction(acontnumber,amont*-1,vcleint);
}

bool find_user(string name,string password,vector<stuser>&vuser,stuser& user){
    for(stuser &h:vuser){
        if(h.username==name&&h.password==password){
            user=h;
            return true;
        }
    }
    return false;
}

bool delet_user(string username,string password,vector<stuser>&vuser){
    stuser user;
    char en='no';
    if(find_user(username,password,vuser,user)){
        printuser(user);
        cout<<"wat do you delet user [y/ N]";
        cin>>en;
        ClearInputBuffer();
        if(en=='y'||en=='Y'){
            markuser( username,vuser);
            seveuser(userfile,vuser);
            vuser=Load_user(userfile);
            cout<<"user delet succsr ✅";
            return true;
        }
    }
    else{
        cout<<"the user is ("<<username<<")not fond ❌ "<<endl;
    }
    return false;
}

void Show_Delet_User(){
    cout<<"'\n ≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    cout<<"\t\033[1;33mshow delet users Screen\033[0m \n";
    cout<<"'≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    vector<stuser> vuser=Load_user(userfile);
    string name=readname();
    string password=readpassword();

    delet_user(name,password,vuser);
}

void Show_Find_User(){
    stuser user;
    
    cout<<"'\n ≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    cout<<"\t\033[1;33mshow find users Screen\033[0m \n";
    cout<<"'≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    vector<stuser> vuser=Load_user(userfile);
    string name=readname();
    string password=readpassword();

    if(find_user(name,password,vuser,user)){
        printuser(user);
    }
    else{
        cout<<"The user is("<<name<<")"<<"not fond :❌\n";
    }
}

void Show_Add_User(){    
; cout<<"'\n ≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    cout<<"\t\033[1;33mAdd New users Screen\033[0m \n";
    cout<<"'≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    char cho='y';
    do{
        stuser user=Read_user();
        Add_to_fileuser(userfile,Convert_Record_user(user));
        cout<<" Do you want to add another cleint [Y/N]";
        cin>>cho;
        ClearInputBuffer();
    }while(cho=='y'||cho=='Y');
}

void Show_Updet_User(){
    cout<<"'≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
cout<<"\t\033[1;33mUpdate User Screen\033[0m \n";
    cout<<"'≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    
    vector<stuser> vuser=Load_user(userfile);
    string username=readname();
    string password=readpassword();
    
    stuser user;
    if(find_user(username,password,vuser,user)){
        cout << "Enter new username: ";
        getline(cin>>ws, user.username);
        cout << "Enter new password: ";
        getline(cin, user.password);
        user.pass = readpermistion();
        user.time = getCurrentDateTime();
        
        // Update in vector
        for(auto& u : vuser){
            if(u.username == username && u.password == password){
                u = user;
                break;
            }
        }
        
        // Save to file
        seveuser(userfile, vuser);
        cout << "User updated successfully!\n";
    }
    else{
        cout << "User not found! ❌\n";
    }
}

void Show_Updet_Cleint(){
    if(!checkAccessPermission(enpermintion::Updetcleint)){
        showaccessmassag();
        return;
    }
    cout<<"'≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    cout<<"\t\033[1;33mUpdet Cleints Screen \033[0m\n";
    cout<<"'≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    vector<stcleints> vcleint=loadcleintdata(cleintfile);
    string acontnumber=readaconut();
    Updet_cleint(acontnumber,vcleint);
}

void Show_Delet_Cleint(){
    if(!checkAccessPermission(enpermintion::Deletcleint)){
        showaccessmassag();
        return;
    }
    cout<<"'≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    cout<<"\t\033[1;33mdelete Cleints Screen \033[0m\n";
    cout<<"'≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    vector<stcleints> vcleint=loadcleintdata(cleintfile);
    string acontnumber=readaconut();
    deletcleint(acontnumber,vcleint);
}

void Show_Add_Cleint(){
    if(!checkAccessPermission(enpermintion::Addcleint)){
        showaccessmassag();
        return;
    }
    cout<<"'\n ≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    cout<<"\t\033[1;33mAdd New Cleints Screen\033[0m \n";
    cout<<"'≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    Add_New_Cleints();
}

void Show_Find_Cleint(){
    if(!checkAccessPermission(enpermintion::Findcleint)){
        showaccessmassag();
        return;
    }
    cout<<"'\n≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    cout<<"\t\033[1;33mfind Cleints Screen\033[0m \n";
    cout<<"'≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    stcleints cleint;
    vector<stcleints> vcleint=loadcleintdata(cleintfile);
    string acontnumber=readaconut();
    
    if(Find_cleint(acontnumber,vcleint,cleint)){
        printcleint(cleint);
    }
    else{
        cout<<"\n--------------------------------\n";
        cout<<"the cleint ["<<acontnumber<<"] not fond ❌\n";
        cout<<"--------------------------------\n";
    }
}

void Show_End_Cleint(){
    cout<<"'\n≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    cout<<"\t\033[1;44mfinish the program :)\033[0m\n";
    cout<<"'≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠≠\n";
    system("pause>0");
}

void Go_backMain(){
    cout<<"\nprees any key to go back to main menue ..\n";
    system("pause>0");
  Show_Manang_User();
}

short Readoption(){
    short choice;
    cout<<"Choose What Do You Want To Do [1/6]..?";
    cin>>choice;
    ClearInputBuffer();
    return choice;
}

void PerformUser(enuser user){
    switch(user){
        case enuser::ListUser:
            system("cls");
            Show_Lest_User();
            Go_backMain();
            break;
        case enuser::AddUser:
            system("cls");
            Show_Add_User();
            Go_backMain();
            break;
        case enuser::DeletUser:
            system("cls");
            Show_Delet_User();
            Go_backMain();
            break;
        case enuser::UpdetUser:
            system("cls");
            Show_Updet_User();
            Go_backMain();
            break;
        case enuser::FindUser:
            system("cls");
            Show_Find_User();
            Go_backMain();
            break;
        case enuser::mainmenu:
            system("cls");
            ShowMainMenue();
            break;
    }
}

void Show_Manang_User(){
    if(!checkAccessPermission(enpermintion::Manangusers)){
        showaccessmassag();
        return;
    }
    system("cls");
    cout<<"≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n";
    cout<<"\t\033[1;41mManang User screen\033[0m \n";
    cout<<"≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n";
    cout<<"\t[1] List User• \n";
    cout<<"\t[2] Add User• \n";
    cout<<"\t[3] Delet User• \n";
    cout<<"\t[4] Updet User• \n";
    cout<<"\t[5] Find User•\n";
    cout<<"\t[6] main menu•\n";
    cout<<"≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n";
    PerformUser((enuser)Readoption());
}

void GoBackTomaintransaction(){
    cout<<"\nprees any key to go back to main transaction ..\n";
    system("pause>0");
    Show_transaction_menue();
}

void performtransaction(entrasactiont trasaction){
    switch(trasaction){
        case entrasactiont::Deposit:
            system("cls");
            show_deposaction();
            GoBackTomaintransaction();
            break;
        case entrasactiont::ewithdraw:
            system("cls");
            show_withdraw();
            GoBackTomaintransaction();
            break;
        case entrasactiont::totalblank:
            system("cls");
            Showlistcleint();
            GoBackTomaintransaction();
            break;
        case entrasactiont::showmainmenue:
            system("cls");
            ShowMainMenue();
            break;
    }
}

void Show_transaction_menue(){
    if(!checkAccessPermission(enpermintion::Transaction)){
        showaccessmassag();
        
        return;
    }
    
    system("cls");
    cout<<"≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n";
    cout<<"\t\033[1;41mRansaction menue screen\033[0m \n";
    cout<<"≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n";
    cout<<"\t[1] Deposit• \n";
    cout<<"\t[2] withdraw• \n";
    cout<<"\t[3] total cleint• \n";
    cout<<"\t[4] main menue• \n";
    cout<<"≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n";
    performtransaction((entrasactiont)Readoption());
}

void GoBackToMainMenu(){
    cout<<"\nprees any key to go back to main menue ..\n";
    system("pause>0");
    ShowMainMenue();
}

void PreFromMainMenuOption(enmainmenueoption mainmenuoption){
    switch(mainmenuoption){
        case enmainmenueoption::List_Cleints:
            system("cls");
            Showlistcleint();
            GoBackToMainMenu();
            break;
        case enmainmenueoption::Add_Cleint:
            system("cls");
            Show_Add_Cleint();
            GoBackToMainMenu();
            break;
        case enmainmenueoption::Delete_Cleint:
            system("cls");
            Show_Delet_Cleint();
            GoBackToMainMenu();
            break;
        case enmainmenueoption::Update_Cleint:
            system("cls");
            Show_Updet_Cleint();
            GoBackToMainMenu();
            break;
        case enmainmenueoption::Find_Cleint:
            system("cls");
            Show_Find_Cleint();
            GoBackToMainMenu();
            break;
        case enmainmenueoption::Deposaction:
            system("cls");
            Show_transaction_menue();
            GoBackToMainMenu();
            break;
        case enmainmenueoption::Mananguser:
            system("cls");
            Show_Manang_User();
            GoBackToMainMenu();
            break;
        case enmainmenueoption::Exit:
            system("cls");
            Show_End_Cleint();
            break;
    }
}

void ShowMainMenue(){
    system("cls");
    cout<<"≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n";
    cout<<"\t\033[1;41mMain Menue Screen\033[0m \n";
    cout<<"≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n";
    cout<<"\t[1] Show Cleint List• \n";
    cout<<"\t[2] Add New Cleint• \n";
    cout<<"\t[3] Delet Cleint• \n";
    cout<<"\t[4] Updet Cleint• \n";
    cout<<"\t[5] Find Cleint•\n";
    cout<<"\t[6] Transaction•\n";
    cout<<"\t[7] Manang User•\n";
    cout<<"\t[8] Exit•\n";
    cout<<"≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n";
    PreFromMainMenuOption((enmainmenueoption)Readoption());
}

bool Login(){
    string username, password;
    cout << "\n\n\t\t\t\033[1;31mBank Management System\033[0m\n";
    cout << "\t\t\t----------------------\n";
    cout << "\t\t\tUsername: ";
    getline(cin>>ws ,username);
    cout << "\t\t\tPassword: ";
    cin >> password;
    
    if(Finduserandpassword(username, password, correntuser)){
        return true;
    }
    else{
  cout << "\nInvalid username or password! ❌ \n";
        system("pause");
        return false;
    }
}




    
int main(){
     
    while(!Login()){
        system("cls");
  }
    
    ShowMainMenue();
   
    return 0;
}
