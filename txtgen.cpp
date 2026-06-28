#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>

std::string smena(){
    int a = rand()%3;
    if(a == 0){
        return "Prepodnevna";
    }else if(a == 1){
        return "Popodnevna";
    }else{
        return "Ceo dan";
    }
}

std::string tip(){
    int a = rand()%2;
    if(a==0){
        return "Dvostruki";
    }else{
        return "Trostruki";
    }
}

int main(){
    for(int i=0;i<40;i++){
        std::cout<<"Ime: "<<"Ta i ta"<<i<<std::endl;
        std::cout<<"Smena: "<<smena()<<std::endl;
        std::cout<<"Tip treninga: "<<tip()<<::std::endl;
        std::cout<<"Izuzeci: "<<"Nema"<<std::endl;
        std::cout<<std::endl;
    }
}