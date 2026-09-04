#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

class transact{
    
    public:
    
    std:: vector <double> tvalue{};
    std::vector <std::string> tdesc{};
    std::vector <std::string> tname{};

    double totalvalue(){
        int totval{};
        for (int i{}; i<tvalue.size(); i++){
            totval+=tvalue[i];
        }
        return totval;
    }
};


transact bills{};
transact expenses{};
transact invest{};
transact income{};

void exitstate(){
    char exit{};
    std::cout<<"\nEnter any key to exit page: ";
    std::cin>>exit;
}

void displayinfo(transact trans){

    if (trans.tname.size()>0){
        for(int i{}; i<trans.tname.size();i++){
            std::cout<<"\n---------------------------------";
            std::cout<<"\n"<<trans.tname[i]<<": $"<<trans.tvalue[i]<<"\n";
            std::cout<<"\nDescription:\n\n"<<trans.tdesc[i];
            std::cout<<"\n---------------------------------";
    }
    }else{
        std::cout<<"\nThere are no entries in this category\n";
    }

    exitstate();
}

void modtrans(transact& trans){
    
        for(int i{}; i<trans.tname.size();i++){
            std::cout<<"\n";
            std::cout<<i+1<<". "<<trans.tname[i]<<"       $"<<trans.tvalue[i]<<"\n\n";
        }

        char getoption{};
        std::cout<<"Would you like to remove or add a transaction? (r/a): ";
        std::cin>>getoption;

        if (getoption=='r'){
            if (trans.tname.size()>0){
                int popval{};
                    std::cout<<"\nSelect a transaction you would like to remove: ";
                    std::cin>>popval;
                    
                    trans.tname.erase(trans.tname.begin()+popval-1);
                    trans.tvalue.erase(trans.tvalue.begin()+popval-1);
                    trans.tdesc.erase(trans.tdesc.begin()+popval-1);
            }else{
                std::cout<<"\nThere are no entries to remove\n";
            }
    
        }else if (getoption=='a'){
            std::string name{};
            double value{};
            std::string desc{};

            std::cout<<"\nEnter the name of your transaction: ";
            std::getline(std::cin>>std::ws, name);
            std::cout<<"\nEnter a brief description of your transaction: ";
            std::getline(std::cin>>std::ws, desc);
            std::cout<<"\n Enter the value of your transaction: ";
            std::cin>>value;

            trans.tname.push_back(name);
            trans.tdesc.push_back(desc);
            trans.tvalue.push_back(value);

        }else{
            std::cout<<"\nYou did not enter a valid option\n";
        }
    
    char contval{};
    std::cout<<"\nWould you like to modify another transaction?(Enter 'y', or any other key to exit): ";
    std::cin>>contval;
    if (contval=='y'){
        modtrans(trans);
    }
}


void indat(){
    std::fstream finfile("fininf.txt",std::ios::in); 

    if (!finfile){
        std::cerr<<"Couldn't open file";
    }
    
    std::string readin{};
    int tswap{};
    
    while(getline(finfile,readin)){
        if (readin.length()<=0){
            break;
        }
        else if (readin=="expenses"){
            tswap=0;
            continue;
        }else if (readin=="bills"){
            tswap=1;
            continue;
        }else if (readin=="income"){
            tswap=2;
            continue;
        }else if (readin=="invest"){
            tswap=3;
            continue;
        }
        std::string t1{readin.substr(0,readin.find("/"))};
        std::string t2{readin.substr(readin.find("/")+1,readin.find("~") - readin.find("/")-1)};
        std::string t3{readin.substr(readin.find("~")+1,readin.length()-1)};

        if (tswap==0){
            expenses.tname.push_back(t1);
            expenses.tdesc.push_back(t2);
            expenses.tvalue.push_back(std::stod(t3));
        }else if (tswap==1){
            bills.tname.push_back(t1);
            bills.tdesc.push_back(t2);
            bills.tvalue.push_back(std::stod(t3));
        }else if (tswap==2){
            income.tname.push_back(t1);
            income.tdesc.push_back(t2);
            income.tvalue.push_back(std::stod(t3));          
        }else if (tswap==3){
            invest.tname.push_back(t1);
            invest.tdesc.push_back(t2);
            invest.tvalue.push_back(std::stod(t3));
        }
    }

    finfile.close();
}

void outdat(){
    std::fstream finfile("fininf.txt",std::ios::out|std::ios::trunc); 

    if (!finfile){
        std::cerr<<"Couldn't open file";
    }

    finfile<<"expenses\n";
    for (int i{}; i<expenses.tname.size(); i++){
        finfile<<expenses.tname[i]<<"/"<<expenses.tdesc[i]<<"~"<<expenses.tvalue[i]<<"\n";
    }
    
    finfile<<"bills\n";
    
    for (int i{}; i<bills.tname.size(); i++){
        finfile<<bills.tname[i]<<"/"<<bills.tdesc[i]<<"~"<<bills.tvalue[i]<<"\n";
    }

    finfile<<"income\n";
    for (int i{}; i<income.tname.size(); i++){
        finfile<<income.tname[i]<<"/"<<income.tdesc[i]<<"~"<<income.tvalue[i]<<"\n";
    }

    finfile<<"invest\n";
    for (int i{}; i<invest.tname.size(); i++){
        finfile<<invest.tname[i]<<"/"<<invest.tdesc[i]<<"~"<<invest.tvalue[i]<<"\n";
    }
    finfile.close();
    std::cout<<"Your data was successfully saved!";
}

int main(){
    indat();
    
    while(true){
        
        std::cout<<"----------Finance Tracker----------\n";
        std::cout<<"1: Review your finances\n";
        std::cout<<"2: Review bill payments, income, expenses\n";
        std::cout<<"3: Modify your bill payments, income, expenses\n";
        std::cout<<"4: Exit the program\n";

        std::cout<<"Enter your option here: ";
        std::cout << std::fixed << std::setprecision(2);

        char pagestate{};

        std::cin>>pagestate;

        if (pagestate=='1'){
            std::cout<<"\nThe total value of your bill payments is: -"<<bills.totalvalue()<<"\n";
            std::cout<<"The total value of your expenses is: -"<<expenses.totalvalue()<<"\n";
            std::cout<<"The total value of your income is: "<<income.totalvalue()<<"\n";
            std::cout<<"The total value of your investments is: "<<invest.totalvalue()<<"\n";

            std::cout<<"Your current net worth is: "<<income.totalvalue()+invest.totalvalue()
            -bills.totalvalue()-expenses.totalvalue()<<"\n";

            exitstate();

        }else if (pagestate=='2'){
            int option{};
            std::cout<<"\nSelect the type of transaction you would like to review:\n";
            std::cout<<"1. Bills\n2. Expenses \n3. Income\n4. Investments\n Enter your option here:  ";
            std::cin>>option;

            switch(option){
                case 1:
                    displayinfo(bills);
                    break;
                case 2:
                    displayinfo(expenses);
                    break;     
                case 3:
                    displayinfo(income);
                    break;
                case 4:
                    displayinfo(invest);
                    break;
            };

        }else if (pagestate=='3'){
            char option{};
            std::cout<<"\nSelect the type of transaction you would like to modify:\n";
            std::cout<<"1. Bills\n2. Expenses \n3. Income\n4. Investments\nEnter your option here: ";
            std::cin>>option;

            switch(option){
                case '1':
                    modtrans(bills);
                    break;
                case '2':
                    modtrans(expenses);
                    break;
                case '3':
                    modtrans(income);
                    break;
                case '4':
                    modtrans(invest);
                    break;
                default:
                    std::cout<<"\nOption not recognized\n";
            };

        }else if (pagestate=='4'){
            break;
        }else{
            std::cout<<"\n\nThe option you entered was invalid, please try again\n\n";
            continue;
        }
    }
    outdat();
}