#include <iostream>
#include <array>
#include <vector>
#include <thread>
using namespace std;

struct data_hero{
    array <string , 3 > hero = {
        "anam",
        "asep",
        "jamal"
    };
    array <array<int , 4>, 3 > stat = {{
        {4000 , 234 , 90 , 40},
        {4750 , 81 , 75 , 78},
        {3600 , 80 , 270 , 27}
    }};
};

struct new_stat{

    array <string , 2>* hero = new array<string , 2>();
    array <array<int,4>,2>* base_stat = new array<array<int,4>,2>();
    array <array<int,4>,2>* static_stat = new array<array<int,4>,2>();
};

struct gameplay{
    bool gameover = false;
};

class Duel{
    private:
        data_hero dat;
        new_stat ns;
        gameplay gmp;;
    public:
        friend void delete_new_stat(Duel &duel);
        friend void insert_hero(Duel &duel , string p1 , string p2);
        friend void guardian_helmet(Duel &duel , string player);
        friend void serang(Duel &duel , string hero);
        int total_hero = dat.hero.size();
};

void guardian_helmet(Duel &duel , string player){
    int id;
    for(int i = 0 ; i < 2 ; i++){
        if((*duel.ns.hero)[i] == player){
            id = i;
            break;
        }
    }
    //atribut
    (*duel.ns.base_stat)[id][0] += 500 ;
    (*duel.ns.static_stat)[id][0] += 500 ;
    //pasif
    while(!duel.gmp.gameover){
        int memulihkan;
        int total_pemulihan = ((*duel.ns.base_stat)[id][0] * 5) / 100;
        if((*duel.ns.static_stat)[id][0]+total_pemulihan > (*duel.ns.base_stat)[id][0]){
            (*duel.ns.static_stat)[id][0] = (*duel.ns.base_stat)[id][0];
        }
        else{
            memulihkan = total_pemulihan;
        }
        (*duel.ns.static_stat)[id][0] += total_pemulihan;
        cout << "memulihkan " << total_pemulihan << " hp " << (*duel.ns.hero)[id] << endl;
        this_thread::sleep_for(chrono::duration<float>(2.5));
    }
}

void delete_new_stat(Duel &duel){
    //p1
    delete duel.ns.hero;
    delete duel.ns.base_stat;
    delete duel.ns.static_stat;
    
}

void insert_hero(Duel &duel , string p1 , string p2){
    for(int i = 0 ; i < duel.dat.hero.size() ; i++){
        if(p1 == duel.dat.hero[i]){
            (*duel.ns.hero)[0] = p1;
            for(int ii = 0 ; ii < 4 ; ii++){
                (*duel.ns.base_stat)[0][ii] = duel.dat.stat[i][ii];
                (*duel.ns.static_stat)[0][ii] = duel.dat.stat[i][ii];
            }
        }
    }
    for(int i = 0 ; i < duel.dat.hero.size() ; i++){
        if(p2 == duel.dat.hero[i]){
            (*duel.ns.hero)[1] = p2;
            for(int ii = 0 ; ii < 4 ; ii++){
                (*duel.ns.base_stat)[1][ii] = duel.dat.stat[i][ii];
                (*duel.ns.static_stat)[1][ii] = duel.dat.stat[i][ii];
            }
        }
    }
    for(int i = 0 ; i < 2 ; i++){
        cout << "set " << (*duel.ns.hero)[i] << " untuk player " << i+1 << endl;
        for(int ii = 0 ; ii < 4 ; ii++){
            cout << (*duel.ns.base_stat)[i][ii] << "\t";
        }
        cout << endl;
    }
}

void serang(Duel &duel , string hero){
    int id;
    int target;
    for(int i = 0 ; i < 2 ; i ++){
        if((*duel.ns.hero)[i] == hero){
            id = i;
            break;
        }
    }
    for(int i = 0 ; i < 2 ; i ++){
        if((*duel.ns.hero)[id] != (*duel.ns.hero)[i]){
            target = i;
            break;
        }
    }
    while(!duel.gmp.gameover){
        if((*duel.ns.static_stat)[target][0] <= 0){
            (*duel.ns.static_stat)[target][0] = 0;
            duel.gmp.gameover = true;
            cout << "sisa hp " <<(*duel.ns.hero)[target] << " adalah "<< (*duel.ns.static_stat)[target][0] << endl;
            cout << (*duel.ns.hero)[target] << " kalah!" << endl;
            delete_new_stat(duel);
            break;
        }
        int total_p_damage;
        int total_m_damage;
        int total_damage = total_p_damage + total_m_damage;
        if((*duel.ns.static_stat)[id][1] <= (*duel.ns.static_stat)[target][3]){
            total_p_damage = 0;
        }
        else{
            total_p_damage = (*duel.ns.static_stat)[id][1] - (*duel.ns.static_stat)[target][3];
        }
        if((*duel.ns.static_stat)[id][2] <= (*duel.ns.static_stat)[target][3]){
            total_m_damage = 0;
        }
        else{
            total_m_damage = (*duel.ns.static_stat)[id][2] - (*duel.ns.static_stat)[target][3];
        }
        cout << hero << "menyerang " << (*duel.ns.hero)[target] << " dengan damage sebesar " << total_damage << endl;
        cout << "sisa hp " <<(*duel.ns.hero)[target] << " adalah "<< (*duel.ns.static_stat)[target][0] << endl;
        (*duel.ns.static_stat)[target][0] -= total_damage;

        this_thread::sleep_for(chrono::duration<float>(0.25));
    }
}

int main(){
    Duel duel;
    insert_hero(duel , "anam","asep");
    thread gh1([&duel](){
        guardian_helmet(duel , "anam");
    });
    thread gh2([&duel](){
        guardian_helmet(duel , "asep");
    });
    thread p1([&duel](){
        serang(duel , "anam");
    });
    thread p2([&duel](){
        serang(duel , "asep");
    });
    p1.join();
    p2.join();
    gh1.join();
    gh2.join();
    return 0;
}