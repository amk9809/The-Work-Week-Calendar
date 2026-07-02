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
        }else if(line == "Ceo dan"){
            return "02";
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
    }
    node* temp = head;
    for(int i=0;i<list_size();i++){
        std::cout<<"The user, number "<<i<<", appears "<<L[i]<<" times.";
        std::cout<<" The user should appear "<<temp->TOT<<" times.";
        if(L[i] == temp->TOT){
            std::cout<<" All correct!"<<std::endl;
        }else{
            std::cout<<" Wrong amount!"<<std::endl;
        }
        temp = temp->next;
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
            }else if(w[y]=='-' && w[y+1]!='-'){
                std::cout<<std::endl;
            }
        }w = w.substr(t+1, w.size()-t);
    }
}

std::string calculator(){
    std::string M;
    int T[list_size()], D[list_size()];
    node* temporary_node = head;
    for(int i=0;i<list_size();i++){
        T[i] = temporary_node->TOT;
        temporary_node = temporary_node->next;
    }
    temporary_node = head;
    for(int i=0;i<list_size();i++){
        D[i] = temporary_node->TOD;
        temporary_node = temporary_node->next;
    }
    int count1 = 0, count2 = 0;
    for(int i=0;i<list_size();i++){
        if(D[i]==0){
            count1 = count1 + T[i];
        }else{
            count2 = count2 + T[i];
        }
    }


    int n1 = 0, n2 = 0, n = 0, c1 = (count1)%15, c2 = (count2)%15;
    bool k1 = true, k2 = true;
    std::cout<<std::endl<<"Counter1: "<<count1<<std::endl<<"Counter2: "<<count2<<std::endl;
    for(int i=0;i<5;i++){
        n1 = n1 + c1;
        int t = int(count1/15);
        if(n1>=15){
            t++;
            k1 = false;
        }
        int mem1[t*3];
        std::cout<<std::endl<<"t: "<<t<<std::endl;
        for(int y=0;y<t;y++){
            for(int j=0;j<3;j++){
                bool loop_breaker = false;
                if(check_array(T)){y=420;i=420;j=420;}else{
                    int loop_counter = 0;
                    while((T[n]==0 || !D[n] == 0) && !check_array(T) && (loop_breaker == false)){
                        n++;
                        if(n>=list_size()){
                            n=0;
                            loop_counter++;
                            if(loop_counter>2){
                                loop_breaker = true;
                            }
                        }for(int u=0;u<3*y+j;u++){
                            if(mem1[u] == n){
                                n++;
                            }
                        }
                    }if(loop_breaker == false){
                        M = M + std::to_string(n) + '/';
                        mem1[3*y+j] = n; 
                        T[n] = T[n]-1;
                        std::cout<<n<<" : "<<T[n]<<"   ";
                        n++;
                        if(n>=list_size()){
                            n=0;
                        }
                    }
                }
            }
            if(y==t-1){std::cout<<"--  Day "<<i+1<<" has "<<y+1<<" morning trainings."<<std::endl;}
            M = M + '-';    
        }if(k1==false){
            k1 = true;
            n1 = n1-14;
        }
        
        
        n2 = n2 + c2;
        t = int(count2/15);
        if(n2>=15){
            t++;
            k2 = false;
        }
        int mem2[t*3];
        std::cout<<std::endl<<"t: "<<t<<std::endl;
        for(int y=0;y<t;y++){
            for(int j=0;j<3;j++){
                bool loop_breaker = false;
                if(check_array(T)){y=420;i=420;j=420;}else{
                    int loop_counter = 0;
                    while((T[n]==0 || !(D[n] == 1 || D[n] == 2)) && !check_array(T) && (loop_breaker == false)){
                        n++;
                        if(n>=list_size()){
                            n=0;
                            loop_counter++;
                            if(loop_counter>2){
                                loop_breaker = true;
                            }for(int u=0;u<3*y+j;u++){
                                if(mem2[u] == n){
                                    
                                }
                            }
                        }
                    }if(loop_breaker == false){ 
                        M = M + std::to_string(n) + '/';
                        mem2[3*y+j] = n; 
                        T[n] = T[n]-1;
                        std::cout<<n<<" : "<<T[n]<<"   ";
                        n++;
                        if(n>=list_size()){
                                n=0;
                        }
                    }
                }
            }if(k2==false){
            k2 = true;
            n2 = n2-14;
            }
            if(y==t-1){std::cout<<"--  Day "<<i+1<<" has "<<y+1<<" afternoon trainings."<<std::endl;}
            M = M + '-'; 
        }
        std::cout<<std::endl<<"List after today: "<<std::endl;
        for(int i=0;i<list_size();i++){
            std::cout<<T[i]<<" ";
        }
        std::cout<<std::endl<<"Prepodnevna smena: "<<std::endl;
        for(int i=0;i<list_size();i++){
            if(D[i]==0){std::cout<<T[i]<<" ";}else{std::cout<<"  ";}
        }
        std::cout<<std::endl<<"Popodnevna smena: "<<std::endl;
        for(int i=0;i<list_size();i++){
            if(D[i]==1 || D[i]==2){std::cout<<T[i]<<" ";}else{std::cout<<"  ";}
        }
        std::cout<<std::endl<<std::endl;
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