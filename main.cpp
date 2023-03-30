#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;

class Ability{
    int ability_damage;
    string ability_name;
public:
    Ability(): ability_damage(0),ability_name("-"){};

    int getAbilityDamage() const {
        return ability_damage;
    }

    const string &getAbilityName() const {
        return ability_name;
    }
    void setAbilityDamage(int abilityDamage) {
        ability_damage = abilityDamage;
    }

    void setAbilityName(const string &abilityName) {
        ability_name = abilityName;
    }


};
class Weapon {
    string weapon_name;
    int price;
    Ability abilitate;
    int damage;
    Weapon *next;

public:
    Weapon(){
        next = nullptr;
    }
    ~Weapon(){
        if(next != nullptr)
            delete next;
    }

    int getPrice() const {
        return price;
    }

    string getWeaponName() const {
        return weapon_name;
    }

    int getDamage() const {
        return damage;
    }

    const Ability &getAbilitate() const {
        return abilitate;
    }

    void setAbilitate(const Ability &abilitate) {
        Weapon::abilitate = abilitate;
    }

    Weapon *getNext() const {
        return next;
    }

    void setWeaponName(string weaponName) {
        weapon_name = weaponName;
    }

    void setDamage(int damage) {
        Weapon::damage = damage;
    }

    void setPrice(int price) {
        Weapon::price = price;
    }

    void setNext(Weapon *next) {
        Weapon::next = next;
    }
};
class Shop{
    Weapon *start;
public:
    Shop(){
        start = nullptr;
    };
    ~Shop(){
        if(start!= nullptr){
            delete start;
        }
    }

    void add_weapon(int dmg,string name,int pret, int dmg_special, string special_name){
       Ability abilitate;
        if(start == nullptr){
            start = new Weapon();
            start->setDamage(dmg);
            start ->setPrice(pret);
            start->setWeaponName(name);
            abilitate.setAbilityDamage(dmg_special);
            abilitate.setAbilityName(special_name);
            start->setAbilitate(abilitate);
            start->setNext(nullptr);
        }
        else{
            Weapon *actual = start, *viitor;
            while(actual ->getNext() != nullptr) {actual = actual ->getNext();}
            viitor = new Weapon();
            viitor->setDamage(dmg);
            viitor ->setWeaponName(name);
            viitor->setPrice(pret);
            abilitate.setAbilityDamage(dmg_special);
            abilitate.setAbilityName(special_name);
            viitor->setAbilitate(abilitate);
            actual ->setNext(viitor);

        }
    }

    int find_weapon_damage_by_name(string name){
        Weapon *actual = start;
        while(actual->getNext() != nullptr){
            if(actual->getWeaponName() == name)
                return actual ->getPrice();
            actual = actual->getNext();
        }
        if(actual->getWeaponName() == name)
            return actual ->getPrice();
            return -1;

    }

    string find_weapon_by_index(int index){
        Weapon *actual = start;
        for(int i=1;i<index;i++){
            if(actual->getNext() != nullptr)
                actual = actual->getNext();
            else
                return "Invalid Index for a weapon!";
        }
        return actual->getWeaponName();
    }

    void citire_arme(const char *filename){
        int dmg,pret,speciala;
        string nume,nume_speciala;
        fstream file(filename);
        while(file >> dmg && file >> nume && file >>pret && file >> speciala && file >>nume_speciala){
            replacer(nume,'_',' ');
            replacer(nume_speciala,'_',' ');
            add_weapon(dmg,nume,pret,speciala,nume_speciala);

        }
    }
private:
    void replacer(string &nume,const char relpace,const char replace_with){
        for(int i=0; i< nume.size();i++)
            if(nume[i] == relpace)
                nume[i] = replace_with;

    }

   friend ostream & operator << (ostream &out,const Shop &arme);

};
ostream & operator << (ostream &out,const Shop &arme){
    Weapon *actual = arme.start;
    out<<"---------------------------\n";
    out<<"|          SHOP           |\n";
    out<<"---------------------------\n";
    while(actual->getNext() != nullptr){
        out<<actual ->getWeaponName()<<"\n Damage:"<<actual->getDamage()<<"\n Price: "<<actual->getPrice()<<"\n";
        out<<actual->getAbilitate().getAbilityName()<<" | "<<actual->getAbilitate().getAbilityDamage()<<"\n";
        out<<"---------------------------\n";
        actual = actual -> getNext();
    }
    out<<actual ->getWeaponName()<<"\n Damage:"<<actual->getDamage()<<"\n Price: "<<actual->getPrice()<<"\n";




}
class Player{
    int health_point;
    int mana;
    int level;
    float experience;
    int gold;
    char* player_name;
    string sword;

public:
    Player(): health_point(100),mana(100),level(1),experience(0),gold(100){

        sword = "Batz";
        player_name = nullptr;
    }
    Player(const char* name) :Player(){ //apeleaza intai constructorul fara parametrii si dupa aceaia se uita
        // la ce are el de facut in constructorul cu parametrii
        player_name = new char [strlen(name)];
        strcpy(player_name,name);
    }
    ~Player(){
        if(player_name!= nullptr)
            delete [] player_name;
    }
    void give_xp(float exp) {
        this->experience += exp;
        float amount_xp = 0.07, gap_between_level = 2;
        float required_exp_per_level = pow((this->level / amount_xp), gap_between_level);
        /// formula este (level / amount_xp) ^ quickly_required_xp_per_level

        if (this->level < 10)
            while (this->experience >= required_exp_per_level) {
                this->level++;
                this ->health_point+=10;
                required_exp_per_level = pow((this->level / amount_xp), gap_between_level);
            }
        if (this->level > 10)
            this->level = 10;
    }


    void give_money(int gold){
        this -> gold +=gold;
    }

    void weapon_upgrade(Shop &magazin,const int alegere){ ///daca nu punt &magazin o sa faca un nou obiect care are aceleasi
/// adrese ca obiectul initial, iar cand vrea sa dea la destructor practic o sa incerce sa stearga de 2 ori aceeasi adresa;)
       string noua_arma = magazin.find_weapon_by_index(alegere);
       int pretul = magazin.find_weapon_damage_by_name(noua_arma);
          if(this -> gold >= pretul){
              this -> gold -= pretul;
              this ->sword = noua_arma;
              cout<<"Arma cumaparata cu succes!\n";
          }
          else{
              cout<<"Nu ai destui bani!\n";
          }
    }

    int getGold() const;

    friend istream & operator >> (istream &in,Player &player);
    friend ostream & operator << (ostream &out, const Player &player);

    void setGold(int gold);
};
istream  & operator >> (istream &in, Player &player){
    cout<<"Introdu numele tau(acesta poate avea maxim 16 caractere): ";
    char *v = new char [16];
    in.getline(v,16);
    player.player_name = new char[strlen(v)];
    strcpy(player.player_name,v);
    delete [] v;

}
ostream & operator << (ostream &out,const Player &player){
    out<<"\n";
    out<<"------------------------\n";
    out<<"|      Statistici      |\n";
    out<<"------------------------\n";
    out<<"| Name: "<<player.player_name<<"\n";
    out<<"| HP: "<<player.health_point<<"\n";
    out<<"| Mana: "<<player.mana<<"\n";
    out<<"| Gold: "<<player.gold<<"\n";
    out<<"| Sword: "<<player.sword<<"\n";
    if(player.level == 10)
        out<<"| Level: Max Level\n";
    else
        out<<"| Level: "<<player.level<<"\n";
}

int Player::getGold() const {
    return gold;
}

void Player::setGold(int gold) {
    Player::gold = gold;
}

class Plant{ ///restructurat ca sa mearga intr-un vector de astrel de elemente
    char* name;
    int price;
    int grow_time;
public:
    Plant(){
        name = nullptr;
        price = 0;
        grow_time =0;
    }


};
class Plant_Shop{
    Plant *list;
public:
    Plant_Shop(){
        list = nullptr;
    }
    ~Plant_Shop(){
        if(list!= nullptr)
            delete list;

    }
    void citire_plante(){ ///nu este completat, trebuie gandit
        ifstream file("C:\\Users\\Darius Corneciu\\CLionProjects\\POO_Game\\plants.txt");
        ifstream file_name("C:\\Users\\Darius Corneciu\\CLionProjects\\POO_Game\\plants_name.txt");
        int pret,timp;
        char nume[20];
        ///asta e singura metoda fara sa folosec sting.

        while(file >> pret && file >> timp && file_name.getline(nume, 20, ' ')){
            cout<<"P:"<<pret<<' '<<"T:"<< timp <<' '<<"N:"<<nume <<"\n";
        }

    }


};
class Farm {
///
    char **parcel;
    int size;

public:
    Farm(){
        size = 0;
        parcel = nullptr;
    }
    ~Farm(){
        if(parcel!=nullptr){
            delete [] parcel;
        }
    }

    void generate_farm(const int size =2){
        this->size = size;
        parcel = new char *[this->size];
        for(int i=0;i<this->size;i++)
            parcel[i] = new char [this->size];
        for(int i =0;i<this->size;i++)
            for(int j=0;j<this->size;j++)
                parcel[i][j] = '0';
    }
    int delete_farm(){  ///e un destructor, dar imi intoarce size. Eficient cand nu folosesc ferma, practic nu am nevoie de ea
    /// si sa tin mine size ma ajuta ca sa fie un fel de save-game pentru ferma.

        if(parcel!= nullptr){
            delete [] parcel;

        }
        return size;
    }
    bool empty_farm(){
        int nr=0;
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                if(parcel[i][j] == '0')
                    nr++;
        if(nr==size*size)
            return true;
        else
            return false;
    }
    void farm_upgrade(Player &jucator){
        int price = size*1000;
        if(jucator.getGold() >=price && empty_farm()){
            delete_farm();
            size++;
            generate_farm(size);

            cout<<"Ai marit ferma cu succes!\n";
        }
        else if(empty_farm() == false){
            cout<<"Ai ceva inca la crescut!\n";
        }
        else{
            cout<<"Nu ai destui bani pentru acest upgrade!\n";
        }
    }

    void where_to_plant(int line, int column){
        parcel[line-1][column-1] = 't';

    }

    friend ostream & operator <<(ostream &out,const Farm &ferma);
};
ostream  & operator <<(ostream &out,const Farm &ferma){
    for(int i = 0 ;i<ferma.size;i++)
        out<<"------";
    out<<"\n";
    for(int i=0;i<ferma.size;i++){
        for(int j=0;j<ferma.size;j++)
            out<<"| "<<ferma.parcel[i][j]<<" | ";
        out<<"\n";
        for(int i = 0 ;i<ferma.size;i++)
            out<<"------";
        out<<"\n";
    }

}


class Mob{

};
class Boss: public Mob{

};
class Dungeon{

};


int main() {

    Player darius("Darius");
  //  cin>>darius;
   cout<<darius;
/*
    Shop Balea;
    Balea.citire_arme("C:\\Users\\Darius Corneciu\\CLionProjects\\POO_Game\\arme.txt");
    cout<<Balea;

    int input;
    cout<<"Ce arma alegi?:";cin>>input;
    darius.weapon_upgrade(Balea,input);
    darius.give_xp(4000);
    cout<<darius;
    Farm f;
    f.generate_farm();
    cout<<f;
    darius.give_money(40000);
    f.farm_upgrade(darius);
    cout<<f;
    f.where_to_plant(3,3);
    cout<<f;*/
    Plant_Shop shot;
    shot.citire_plante();


/// [1] Upgrade ferma [2] Planteaza  [3] Start_Grow( Care ii da start pracitc si trebuie sa astepti pentru toate plantele.)
/// un for loop merge
/// -> ce vrei sa plantezi? [Shopul de plante] (ai bani)-> succes -> unde vrei sa plantezi?

    return 0;
}
