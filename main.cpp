#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

const std::string DAYS_OF_THE_WEEK[5] = {"Ponedeljak", "Utorak", "Sreda", "Četvrtak", "Petak"};

struct node{
    std::string name;
    int TOD;
    int TOT;
    std::string exc;
    node* next;
};
node* head;

void push(std::string name, int TOD, int TOT, std::string exc){
    node* y = (node*) malloc(sizeof(node));
    y->next = nullptr;
    y->name = name;
    y->TOD = TOD;
    y->TOT = TOT;
    y->exc = exc;
    if(head==nullptr){
        head = y;
    }else{
        y->next=head;
        y->name = name;
        y->TOD = TOD;
        y->TOT = TOT;
        y->exc = exc;
        head = y;
    }
}

void pop(){
    node* y= head;
    if(head->next!=nullptr){
        head = head->next;
        free(y);
        y=nullptr;
    }else{
        free(y);
        y=nullptr;
    }
    
}

void print_list(){
    node* y = head;
    while(y!=nullptr){
        std::cout<<y->name<<std::endl;
        std::cout<<y->TOD<<std::endl;
        std::cout<<y->TOT<<std::endl;
        std::cout<<y->exc<<std::endl;
        y = y->next;
    }
}

std::string file_reader(std::string line, int y){
    if(y==0){
        return line.substr(5, line.size()-5);
    }else if(y==1){
        return line.substr(7, line.size()-7);
    }else if(y==2){
        return line.substr(14, line.size()-14);
    }else if(y==3){
        return line.substr(9, line.size()-9);
    }else{
        std::cout<<"Error reading file line!"<<std::endl;
        return "ERROR";
    }
}

std::string translator(std::string line, int y){
    if(y==0){
        return line;
    }else if(y==1){
        if(line == "Prepodnevna"){
            return "00";
        }else if(line == "Popodnevna"){
            return "01";
        }else{
            std::cout<<"Error translating TOD!!!"<<std::endl;
            return "-01";
        }
    }else if(y==2){
        if(line == "Dvostruki"){
            return "02";
        }else if(line == "Trostruki"){
            return "03";
        }else{
            std::cout<<"Error translating TOT!!!"<<std::endl;
            return "-01";
        }
    }else if(y==3){
        return line;    //eventualno dodati
    }else{
        std::cout<<"Error reading file line!"<<std::endl;
        return "ERROR";
    }
}

void load_file(std::string path){
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error! File: "  << path << " can't be read!" << std::endl;
        return;
    }

    std::string line;
    std::string inserter[4];
    int i = 0;
    while (std::getline(file, line)) {
        inserter[i] = "";
        if(i!=4){
            inserter[i] = translator(file_reader(line, i), i);
            i++;
        }else{
            push(inserter[0], std::stoi(inserter[1]), std::stoi(inserter[2]), inserter[3]);
            i = 0;
        }

    }

    file.close();
}

int list_size(){
    node* y = head;
    int i = 0;
    while(y!=nullptr){
        y = y->next;
        i++;
    }return i;
}

bool check_array(int T[]){
    for(int i=0;i<list_size();i++){
        if(T[i]!=0){        
            return false;
        }
    }return true;
}

void counter(std::string W){
    int L[list_size()];
    for(int i=0; i<list_size();i++){
        L[i] = 0;
    }
    for(int y=0;y<W.size();y++){
        if((W[y]!='/' && W[y]!='-' && W[y]!='~') && (W[y+1]!='/' && W[y+1]!='-' && W[y+1]!='~')){
            int n = (W[y] - '0')*10 + (W[y+1]-'0');
            L[n]++;
            y++;
        }else if((W[y]!='/' && W[y]!='-' && W[y]!='~') && !(W[y+1]!='/' && W[y+1]!='-' && W[y+1]!='~')){
            int n = (W[y] - '0');
            L[n]++;
        }
    }for(int i=0;i<list_size();i++){
        std::cout<<"The user, number "<<i<<", appears "<<L[i]<<" times."<<std::endl;
    }
}

void divider(std::string W){
    std::string w = W;
    for(int i=0;i<5;i++){
        std::cout<<std::endl<<std::endl<<DAYS_OF_THE_WEEK[i]<<std::endl<<std::endl;
        int t = w.find('~');
        for(int y=0;y<t;y++){
            if(w[y]!='-'){
                std::cout<<w[y];
            }else{
                std::cout<<std::endl;
            }
        }w = w.substr(t+1, w.size()-t);
    }
}

std::string calculator(){
    std::string M;
    int T[list_size()];
    node* temporary_node = head;
    for(int i=0;i<list_size();i++){
        T[i] = temporary_node->TOT;
        temporary_node = temporary_node->next;
    }


    //preparation done//


    int n = 0;
    int average_day = list_size()/5;
    int left = list_size()%5;

    int c = 0;
    int trigger = average_day+(12-average_day)/2;
    bool k = true;
    for(int i=0;i<5;i++){
        c = c + left;
        if(c>=5){
            trigger++;
            c = c - 5;
            k = false;
        }
        for(int y=(12-average_day)/2;y<trigger;y++){

            for(int j=0;j<3;j++){
                if(check_array(T)){y=420;i=420;}else{
                    while(T[n]==0 && !check_array(T)){
                        n++;
                        if(n>=list_size()){
                            n=0;
                        }
                    }M = M + std::to_string(n) + '/';
                    T[n] = T[n]-1;
                    n++;
                    if(n>=list_size()){
                            n=0;
                    }  
                }
            }
            M = M + '-';
            
        }
        if(k==false){
            trigger = trigger - 1;
            k = true;
        }
        M = M + '~';
    }
    return M;
}

int main(int argc, char *argv[])
{
    load_file(argv[1]);
    divider(calculator());
    std::cout<<std::endl<<std::endl;
    counter(calculator());
    std::cout<<std::endl<<"It's compiled!!"<<std::endl;
    return 0;
}