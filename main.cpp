#include <iostream>
#include <cstring>
#include <fstream>
#include <windows.h>
#include <cmath>
#include <conio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <thread>
#include<atomic>
///de facut fierarul
using namespace std;
/// de refacut cc

class No_Money:public exception{
public:
    virtual const char* what() const noexcept{
            cout<<"Nu ai destui bani pentru acest lucru!";
    }
};
class Index_Invalid:public exception{
public:
    virtual const char* what() const noexcept{
        cout<<"Index invalid!";
    }
};


class Drop_Item{
    int price;
    string name;
    int given_mana;
    int given_health;
public:
    Drop_Item():price(rand()%100+100),given_mana(rand()%40),given_health(rand()%30){
        vector<string> vec = {"Suc ciudat","Hamei Magic","Bere Mov","Elixir Misterios"};
        int random = rand()%4;
        name = vec[random];

    }
    Drop_Item(string name,int price,int given_mana, int given_health):name(name),price(price),given_health(given_health),given_mana(given_mana){}
    ~Drop_Item() = default;
    void operator = (const Drop_Item &item){
        name = item.name;
        price = item.price;
        given_health = item.given_health;
        given_mana = item.given_mana;
    }
    bool operator == (const Drop_Item &item) const{
        return (name == item.name and price == item.price and given_mana == item.given_mana
                and item.given_health ==given_health);
    }

    const int Getprice() const{return price;}
    const int GetMana() const {return given_mana;}
    const string GetName() const {return name;}
    const int GetHealth() const {return given_health;}
    friend ostream & operator <<(ostream &out,const Drop_Item &item);
};
ostream & operator <<(ostream &out,const Drop_Item &item){
    out<<item.name<<"(P:"<<item.price<<" ,M:"<<item.given_mana<<" ,H:"<<item.given_health<<" )";
    return out;
}

class Ability {
    int ability_damage;
    string ability_name;

public:
    Ability() : ability_damage(0), ability_name("") {};

    Ability(const Ability &ability){
        if(ability.ability_name == ""){
            if(ability_name != ""){
                ability_name = "";
                ability_damage = 0;
            }
        }
        else if(ability.ability_name == ability_name) {cout<<"Nu poti copia aceeasi abilitate!\n";}
        else{
            ability_damage = ability.ability_damage;
            ability_name = ability.ability_name;

        }
    }
    ~Ability() = default;
    bool operator== (const Ability &abilitate) const{
        return (ability_name == abilitate.ability_name && ability_damage == abilitate.ability_damage);
    }
    void operator = (const Ability &ability){
        if(ability.ability_name == ""){
            if(ability_name != ""){
                ability_name = "";
                ability_damage = 0;
            }
        }
        else if(ability.ability_name == ability_name) {cout<<"Nu poti copia aceeasi abilitate!\n";}
        else{
            ability_damage = ability.ability_damage;
            ability_name = ability.ability_name;

        }
    }

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
    string type;
    Ability abilitate;
    int damage;

public:
    Weapon():abilitate(),price(-1),weapon_name(""),damage(0),type("") {}

    Weapon(const Weapon &arma):abilitate(arma.abilitate){
        if(arma.weapon_name == ""){
            if(this->weapon_name != ""){
                weapon_name = "";
                type = "";
                price = 0;
                damage = 0;
            }
        }
        else if(arma.weapon_name == this->weapon_name)
        {cout<<"Nu poti copia acceasi arma\n";}
        else{
            weapon_name = arma.weapon_name;
            this->price = arma.price;
            this->type = arma.type;
            this->damage = arma.damage;
        }

    }
    ~Weapon() = default;

    int getPrice() const {
        return price;
    }
    const string &getType() const{
        return type;
    }
    const string &getWeaponName() const {
        return weapon_name;
    }

    int getDamage() const {
        return damage;
    }

    const Ability &getAbilitate() const {
        return abilitate;
    }

    void setType(const string &tip){
        type = tip;
    }
    void setAbilitate(const Ability &abilitate) {
        //Weapon::abilitate = abilitate;
// Noul vlog: E ora 4:00 si fac debug-ing de 4 ore si aici e problema, alta rezolvare nu am gasit decat sa folosesc
// setter si getter din functia mama;)
        string nume(abilitate.getAbilityName());
        this->abilitate.setAbilityName(nume);
        this->abilitate.setAbilityDamage(abilitate.getAbilityDamage());

    }
    bool operator ==(const Weapon &arma) const{
        return (arma.weapon_name == this->weapon_name and arma.abilitate ==this->abilitate
        and arma.damage == this->damage and arma.price == this->price);
    }


    void setWeaponName( const string &weaponName) {
        weapon_name = weaponName;
    }

    void setDamage(int damage) {
        Weapon::damage = damage;
    }

    void setPrice(int price) {
        Weapon::price = price;
    }

    friend ostream & operator <<(ostream &out, const Weapon &arma);
};
ostream & operator <<(ostream &out, const Weapon &arma){
    out<<arma.weapon_name<<"("<<arma.type<<")";
}
class Shop{
public:
    virtual ~Shop() = default;
    virtual void citire(const char *filename) = 0;
    virtual void afisare() = 0;

};
class Weapon_Shop:public Shop{
    int size;
   vector<Weapon> list;
public:
    Weapon_Shop():size(0){}
    /// sa vorbesc cu majeri pentru cc
    ~Weapon_Shop() = default;

    void add_weapon(int dmg, string &name, int pret, int dmg_special, string &special_name, string &tipul) {
        Ability abilitate;
        abilitate.setAbilityName(special_name);
        abilitate.setAbilityDamage(dmg_special);
        Weapon instet;
        instet.setWeaponName(name);
        instet.setAbilitate(abilitate);
        instet.setPrice(pret);
        instet.setDamage(dmg);
        instet.setType(tipul);
        list.push_back(instet);
        size++;
    }

    Weapon find_weapon_by_index(int index) {
        if(index-1 < 0 and index-1 > list.size()){
            Weapon ret;
            return ret;
        }
        else
            return list[index-1];
    }
    void citire(const char *filename) override{
        int dmg, pret, speciala;
        string nume, nume_speciala, tipul;
        fstream file(filename);


        while (file >> dmg && file>>nume && file >> pret && file >> speciala &&
               file>>nume_speciala && file>>tipul) {
            replacer(nume, '_', ' ');
            replacer(nume_speciala, '_', ' ');
            add_weapon(dmg, nume, pret, speciala, nume_speciala,tipul);


        }

        }
    void afisare() override{

        cout << "---------------------------\n";
        cout << "|          SHOP           |\n";
        cout << "---------------------------\n";

        for(int i = 0 ;i<size;i++){
            cout << list[i].getWeaponName() << "\n Damage:" << list[i].getDamage() << "\n Price: " << list[i].getPrice()
                << "\n";
            cout << list[i].getAbilitate().getAbilityName() << " | " << list[i].getAbilitate().getAbilityDamage() << "\n";
            cout << "--------------"<<i+1<<"-------------\n";

        }

    }
private:
    void replacer(string &nume, const char relpace, const char replace_with) {
        for (int i = 0; i < nume.size(); i++)
            if (nume[i] == relpace)
                nume[i] = replace_with;

    }


};

class Plant {
    string name;
    int price;
    int grow_time;
public:
    Plant(string name ="",int price = 0 , int grow_time = 0):name(name),price(price),grow_time(grow_time) {}
    Plant(const Plant &plantuta){
        if(plantuta.name == ""){
            if(name != ""){
                name = "";
                price = 0;
                grow_time = 0;
            }

        }
        else if(plantuta.name == name){cout<<"Nu poti copia aceeasi planta!\n";}
        else{
        price = plantuta.price;
        grow_time = plantuta.grow_time;
        name = plantuta.name;
        }
    }

    ~Plant() = default;

    bool operator ==(const Plant &planta) const {
        return (planta.name == this->name and planta.price == this->price and planta.grow_time == this->grow_time);
    }
    const string &getName() const {
        return name;
    }
    Drop_Item plant_to_item(){
        Drop_Item planta(this->name,(this->price*3)/2,rand()%10,this->grow_time+10);
        return planta;
    }

    int getPrice() const {
        return price;
    }

    int getGrowTime() const {
        return grow_time;
    }

    void setName(const string &plantname) {
        this->name = plantname;
    }

    void setPrice(int price) {
        Plant::price = price;
    }

    void setGrowTime(int growTime) {
        grow_time = growTime;
    }
    void operator=(const Plant &planta) {
        if (planta.name != "") {
            this->name = planta.name;
            this->grow_time = planta.grow_time;
            this->price = planta.price;
        } else if (planta.name == "") {
            this->name = "";
            grow_time = 0;
            price = 0;
        } else if (this->name == planta.name) {
            cout << "Nu poti copia aceeasi planta!\n";
        }
    }
    Plant &operator[](int index) {
        return *(this + index);
    };

    friend istream &operator>>(istream &in, Plant &plantuta);
    friend ostream &operator<<(ostream &out,const Plant &plant);

};
ostream &operator<<(ostream &out,const Plant &plant){
    out<<"Samanta de "<<plant.name;
    return out;
}
istream &operator>>(istream &in, Plant &plantuta){
    cout<<"Citeste numele plantei(20 caractere maxim): ";
    in>>plantuta.name;
    plantuta.price = 0;
    plantuta.grow_time = 0;
    while(plantuta.price <= 0){
        cout<<"Citeste pretul: ";in>>plantuta.price;
    }
    while(plantuta.grow_time <= 0){
        cout<<"Citeste timpul de crestere: ";in>>plantuta.grow_time;
    }
}

class Plant_Shop:public Shop {
    int size;
    vector<Plant> list;

public:
    Plant_Shop():size(0) {}
    Plant_Shop(const Plant_Shop &magazin){
        if(magazin.list.empty()){
            if(this->size != 0){
                this->size = 0;
                list.clear();
            }
        }
        else if(list.begin() == magazin.list.begin()){cout<<"Nu poti copia aceeasi magazin de plante!\n";}
        else{
            this->size = magazin.size;
            if(!list.empty()){list.clear();}

            for(auto i = magazin.list.begin(); i< magazin.list.end();i++){
                list.push_back(*i);
            }
        }
    }
    ~Plant_Shop() =default;

    int getSize() const;

    vector<Plant> getList() const;

    void citire(const char *filename) override { ///nu este completat, trebuie gandit
        ifstream file(filename);
        int pret, timp;
        string nume;
        while (file >> pret && file >> timp && file >> nume) {
            Plant insert(nume,pret,timp);
            list.push_back(insert);
            size++;

        }


    }

    void afisare() override{
        cout << "------------------------\n";
        cout << "|      Plant Shop      |\n";
        cout << "------------------------\n";

        for (int i = 0; i < size; i++) {
            cout << "Price: " << list[i].getPrice() << "\n";
            cout << "Name: " << list[i].getName() << "\n";
            cout << "Time: " << list[i].getGrowTime() << "\n";
            //out<<"------------------------\n";
            if (i + 1 < 10)
                cout << "-----------" << i + 1 << "------------\n";
            else
               cout << "-----------" << i + 1 << "-----------\n";

        }

    }
    void operator=(const Plant_Shop &magazin) {
        if(magazin.list.empty()){
            if(this->size != 0){
                this->size = 0;
                list.clear();
            }
        }
        else if(list.begin() == magazin.list.begin()){cout<<"Nu poti copia aceeasi magazin de plante!\n";}
        else{
            this->size = magazin.size;
            if(!list.empty()){list.clear();}

            for(auto i = magazin.list.begin(); i< magazin.list.end();i++){
                list.push_back(*i);
            }
        }
    }

    friend istream &operator>>(istream &in, Plant_Shop &shop);

};
istream &operator>>(istream &in, Plant_Shop &shop){

    if(shop.list.empty()){
        shop.size++;
    }
    else {
        Plant_Shop aux = shop;
        for (int i = 0; i < shop.size; i++) {shop.list[i] = aux.list[i];}
        shop.size++;
    }
    cin>>shop.list[shop.size-1];

    }


vector<Plant> Plant_Shop::getList() const {
    return list;
}

int Plant_Shop::getSize() const {
    return size;
}

template <class inv>
class Inventory{
    vector <inv> items;
public:


    void show_inventory(){
        if(items.size() == 0){cout<<"Inventar gol!\n";}
        else{
            cout<<"|----------|\n";
            cout<<"| Inventar |\n";
            cout<<"|----------|\n";
            for(int i = 1; i<=items.size();i++){
                cout<<i<<"."<<items[i-1]<<"\n";

            }
        }
    }
    int getSize(){return items.size();}
    inv getItem(int index){return items[index];}

    void del_item(inv item){
        for(int i = 0; i<items.size();i++){
            if(items[i] == item){
                pop(i+1);
                break;
            }
        }
    }
    void add_to_inventory(inv item){
        items.push_back(item);
    }
    inv ret(int poz){
        if(poz-1 >= 0 and poz-1 <= items.size()){
            inv ret = items[poz -1];
            return ret;
        }
        else{throw(Index_Invalid());}
    }
    void pop(int poz){
        if(poz-1 >= 0 and poz-1 <= items.size()) {
            items.erase(items.begin() + (poz - 1));

        }
        else{throw(Index_Invalid());}

    }
};
class Player {
    int health_point;
    int mana;
    int level;
    float experience;
    int gold;
    string player_name;
    class Arma{
        string weapon_name;
        int damage;
        string type;
        Ability speciala;
    public:
        Arma():weapon_name("Batz"),damage(1),speciala(),type("lemn") {}
        ~Arma() = default;

        bool are_speciala(){
            if(speciala.getAbilityDamage() == 0 and speciala.getAbilityName() =="")
                return false;
            else return true;
        }

        bool is_default(){
            return (weapon_name == "Batz" && damage == 1 && are_speciala() && type == "lemn");
        }
        void setdefault(){
           weapon_name = "Batz";
           damage = 1;
           type = "lemn";
           speciala.setAbilityName("");
           speciala.setAbilityDamage(0);
        }
        bool operator==(const Arma &weapon) const{
        return (weapon_name == weapon.weapon_name && damage == weapon.damage && speciala == weapon.speciala);
        }

        void operator =(const Arma &weapon){
            if(weapon.weapon_name == "Batz"){
                setdefault();
            }
            else if(weapon.weapon_name == this->weapon_name) {cout<<"Nu poti sa copiezi aceeasi arma!\n";}
            else {
                weapon_name = weapon.weapon_name;
                damage = weapon.damage;
                speciala = weapon.speciala;
            }
        }

        const string &GetWeaponName() const { return weapon_name;}
        const int GetDamage() const {return damage;}
        const Ability &GetSpeciala() const {return speciala;}
        const string &GetType() const {return type;}

        void SetType(const string &nume){this->type = nume;}
        void SetWeaponName(const string &nume){this->weapon_name = nume;}
        void SetDamage(const int &damage){this->damage = damage;}
        void SetSpeciala(const Ability &abilitate){
            speciala.setAbilityDamage(abilitate.getAbilityDamage());
            string aux(abilitate.getAbilityName());
            speciala.setAbilityName(aux);
        }
    }sword;
public:
    Player() : health_point(100), mana(100), level(1), experience(0), gold(100),sword() {

        player_name = "";
    }
   Player(const Player &jucator){
        if(jucator.player_name == ""){
            if(this->player_name != ""){
                player_name = "";
                if(!sword.is_default()){
                    sword.setdefault();
                }
                this->gold = 100;
                this->level = 1;
                this->health_point = 100;
                this->experience = 0;
                this->mana = 100;

            }
        }
        else if (jucator.player_name == this->player_name){cout<<"Nu poti copia acelasi jucator!\n";}
        else{
            this->player_name = jucator.player_name;
            this->gold = jucator.gold;
            this->level = jucator.level;
            this->health_point = jucator.health_point;
            this->experience = jucator.experience;
            this->mana = jucator.mana;
            sword = jucator.sword;
        }
    }
    Player(const string name) : Player() { //apeleaza intai constructorul fara parametrii si dupa aceaia se uita
        // la ce are el de facut in constructorul cu parametrii
        player_name = name;
    }

    ~Player() = default;

    void take_damage(int damage){
        health_point -= damage;
    }
    void take_mana(int minus = 10){
        mana-=minus;
    }
    void respawn_character(){
        health_point = 100 + (level-1) * 10;
        if(gold <=100){gold = 0;}
        else{gold -= 100;}
    }
    void give_hp(int hp){
        if(health_point+hp >= 100 + (level-1) * 10){health_point = 100 + (level-1) * 10;}
        else{health_point+=hp;}
    }
    void give_mana(int ma){
        if(mana+ma >= 100 + (level-1) * 200){mana = 100 + (level-1) * 20;}
        else{mana+=ma;}
    }
    void give_xp(float exp) {
        this->experience += exp;
        float amount_xp = 0.07, gap_between_level = 2;
        float required_exp_per_level = pow((this->level / amount_xp), gap_between_level);
        /// formula este (level / amount_xp) ^ quickly_required_xp_per_level
        int actual_level = this->level;
        if (this->level < 10)
            while (this->experience >= required_exp_per_level) {
                this->level++;
                this->health_point += 10;
                this->mana +=20;
                required_exp_per_level = pow((this->level / amount_xp), gap_between_level);
            }
        if (this->level > 10)
            this->level = 10;
        if(this->level > actual_level)
            cout<<endl;
    }


    void schimba_tipul(string posibil_tip,Inventory<Weapon> &inventory){
        //gold = 100000;
        if(this->gold >=1000 and sword.GetWeaponName() !="Batz"){
            pay(1000);
            int rand_number = rand()%101;
            if(rand_number >=40){
                this->sword.SetType(posibil_tip);
                Weapon actuala(getArma());
                inventory.del_item(actuala);
                inventory.add_to_inventory(actuala);
                cout<<"Tip schimbat cu succes!\n Press ANY key to go back!\n";
            }
            else{
               Weapon arma_actuala(getArma());
               inventory.del_item(arma_actuala);
                if (inventory.getSize() > 0) { switch_weapon(1, inventory); }
                else { sword.setdefault();}
                cout<<"Schimbare esuata!\n Press ANY key to go back!\n";

            }
                }
        else{cout<<"[Fierar]\n Nu ai bani sau ai un batz!\n";}
    }
    void give_money(int gold) {
        this->gold += gold;
    }
    void pay(int value){
        if(this->gold - value >= 0)
            this->gold -= value;

    }

    bool buy_plant(Plant_Shop &magazin, int alegere,Inventory<Plant> &inv_plant) {
        vector<Plant> list = magazin.getList();
        if (gold >= list[alegere - 1].getPrice() and alegere <= magazin.getSize() and alegere > 0) {
            gold -= list[alegere - 1].getPrice();
            inv_plant.add_to_inventory(list[alegere-1]);
            return true;
        } else if (gold < list[alegere - 1].getPrice()) {
            throw(No_Money());
            return false;
        } else {
            throw(Index_Invalid());
            return false;
        }

    }

    void weapon_upgrade(Weapon_Shop &magazin,const int alegere, Inventory<Weapon> &inventar) { ///daca nu punt &magazin o sa faca un nou obiect care are aceleasi
/// adrese ca obiectul initial, iar cand vrea sa dea la destructor practic o sa incerce sa stearga de 2 ori aceeasi adresa;)

    Weapon noua_arma(magazin.find_weapon_by_index(alegere));

        if (this->gold >= noua_arma.getPrice() and noua_arma.getPrice() > 0) {
            if(noua_arma.getWeaponName() == sword.GetWeaponName()){cout<<"Ai deja arma asta!\n";}
            else{
                inventar.add_to_inventory(noua_arma);
                this->gold -= noua_arma.getPrice();
                this->sword.SetDamage(noua_arma.getDamage());
                this->sword.SetWeaponName(noua_arma.getWeaponName());
                this->sword.SetSpeciala(noua_arma.getAbilitate());
                this->sword.SetType(noua_arma.getType());
              }
        } else if (this->gold < noua_arma.getPrice()) {
            throw(No_Money());
        }
        else throw(Index_Invalid());
    }
    void switch_weapon(const int alegere,Inventory<Weapon> &inventar){
        if(alegere-1 >= 0 and alegere-1 <=inventar.getSize()){
            Weapon noua_arma(inventar.getItem(alegere-1));
            this->sword.SetDamage(noua_arma.getDamage());
            this->sword.SetWeaponName(noua_arma.getWeaponName());
            this->sword.SetSpeciala(noua_arma.getAbilitate());
            this->sword.SetType(noua_arma.getType());
            cout<<"Noua ta arma este: "<<sword.GetWeaponName()<<endl;
        }
        else{
            throw(Index_Invalid());
        }
    }
    void sell_weapon(const int alegere,Inventory<Weapon> &inventar) {

        if (alegere - 1 >= 0 and alegere - 1 <= inventar.getSize()) {
            Weapon sell(inventar.ret(alegere));
            inventar.pop(alegere);
            this->gold += (sell.getPrice() / 100) * 75;
            if (inventar.getSize() > 0) { switch_weapon(alegere, inventar); }
            else { sword.setdefault(); cout<<"Inventarul fiind gol, ai gasit un bat pe jos!\n"; }
        }
    }
    void sell_p(const int alegere,Inventory<Plant> &inventar) {
        if (alegere - 1 >= 0 and alegere - 1 <= inventar.getSize()) {
            Plant sell(inventar.ret(alegere));
            inventar.pop(alegere);
            this->gold += (sell.getPrice() / 100) * 75;
            }
    }
    void sell_drop(const int alegere,Inventory<Drop_Item> &inventar) {
        if (alegere - 1 >= 0 and alegere - 1 <= inventar.getSize()) {
            Drop_Item sell(inventar.ret(alegere));
            inventar.pop(alegere);
            this->gold += sell.Getprice();
        }
    }

    int getHealth() const{return health_point;}
    int getMana() const{return mana;}
    int getGold() const;
    int getlevel() const {return level;}
    Weapon getArma() const{
        Weapon ret;
        ret.setType(sword.GetType());
        ret.setDamage(sword.GetDamage());
        ret.setWeaponName(sword.GetWeaponName());
        ret.setAbilitate(sword.GetSpeciala());
        return ret;
    }

    const string &getPlayerName() const;

    friend istream &operator>>(istream &in, Player &player);

    friend ostream &operator<<(ostream &out, const Player &player);

    void setGold(int gold);
};

istream &operator>>(istream &in, Player &player) {
    cout << "Introdu numele tau(acesta poate avea maxim 16 caractere): ";
    in>>player.player_name;
    return in;

}

ostream &operator<<(ostream &out, const Player &player) {
    out << "\n";
    out << "------------------------\n";
    out << "|      Statistici      |\n";
    out << "------------------------\n";
    out << "| Name: " << player.player_name << "\n";
    out << "| HP: " << player.health_point << "\n";
    out << "| Mana: " << player.mana << "\n";
    out << "| Gold: " << player.gold << "\n";
    out << "| Sword: " << player.sword.GetWeaponName() <<" | "<<player.sword.GetDamage()<< " damage\n";
    out << "| Sword Ultimate: "<<player.sword.GetSpeciala().getAbilityName()<<" | "
    <<player.sword.GetSpeciala().getAbilityDamage()<<" damage\n";
    if (player.level == 10)
        out << "| Level: Max Level\n";
    else
        out << "| Level: " << player.level << "\n";
    return out;
}

int Player::getGold() const {
    return gold;
}

void Player::setGold(int gold) {
    Player::gold = gold;
}

const string &Player::getPlayerName() const {
    return player_name;
}


class Farm {
///
    char ***parcel;
    int size;

public:
    Farm() {
        size = 0;
        parcel = nullptr;
    }
   Farm(const Farm &ferma){
        if(ferma.size == 0){
            if(parcel != nullptr){
                for(int i = 0; i< size; i++)
                    for(int j = 0; j< size;j++)
                        delete [] this->parcel[i][j];

                for( int i = 0;i <size;i++)
                    delete [] this->parcel[i];

                this->size = 0;
                delete [] this->parcel;
            }
        }
        else if(this->parcel == ferma.parcel){cout<<"Nu poti copia acceasi ferma\n";}
        else{
            if(parcel != nullptr){
                for(int i = 0; i< size; i++)
                    for(int j = 0; j< size;j++)
                        delete [] this->parcel[i][j];

                for( int i = 0;i <size;i++)
                    delete [] this->parcel[i];

                delete [] this->parcel;
            }
            this->size = ferma.size;
            this->parcel = new char **[this->size];
            for (int i = 0; i < this->size; i++)
                this->parcel[i] = new char *[this->size];
            for (int i = 0; i < this->size; i++)
                for (int j = 0; j < this->size; j++){
                    this->parcel[i][j] = new char [strlen(ferma.parcel[i][j])];
                    strcpy(this->parcel[i][j],ferma.parcel[i][j]);
                }

        }
    }
    ~Farm() {
        if (parcel != nullptr) {

         for(int i = 0; i< size; i++)
             for(int j = 0; j< size;j++)
             delete [] parcel[i][j];

         for( int i = 0;i <size;i++)
             delete [] parcel[i];

         delete [] parcel;
        }
    }

    void generate_farm(const int size = 2) {
        this->size = size;
        parcel = new char **[this->size];
        for (int i = 0; i < this->size; i++)
            parcel[i] = new char *[this->size];
        for (int i = 0; i < this->size; i++)
            for (int j = 0; j < this->size; j++)
                parcel[i][j] = new char [1], parcel[i][j] = "0";
    }

    int delete_farm() {  ///e un destructor, dar imi intoarce size. Eficient cand nu folosesc ferma, practic nu am nevoie de ea
        /// si sa tin mine size ma ajuta ca sa fie un fel de save-game pentru ferma.

        if (parcel != nullptr) {
            delete[] parcel;

        }
        return size;
    }

    bool empty_farm() {
        int nr = 0;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if ( strcmp(parcel[i][j],"0") == 0)
                    nr++;
        if (nr == size * size)
            return true;
        else
            return false;
    }

    bool full_farm(){
        int nr = 0;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (strcmp(parcel[i][j],"0") != 0)
                    nr++;
        if (nr == size * size)
            return true;
        else
            return false;

    }

    void farm_upgrade(Player &jucator) {
        int price = size*size * 1000;
        if (jucator.getGold() >= price && empty_farm()) {
            delete_farm();
            size++;
            jucator.pay(price);
            generate_farm(size);

            cout << "Ai marit ferma cu succes!\n";
        } else if (empty_farm() == false) {
            cout << "Ai ceva inca la crescut!\n";
        } else {
        throw(No_Money());
        }
    }

    string what_to_plant(Inventory<Plant> &inv_plant, int alegere,vector<Plant> &plant) {

       Plant ret = inv_plant.ret(alegere);
       plant.push_back(ret);
        inv_plant.pop(alegere);
        return ret.getName();

    }

    void where_to_plant(string choise) {
        int ok = 0;
        for(int i = 0; i<size;i++)
        {
            for(int j = 0 ;j<size;j++)
                if(strcmp(parcel[i][j],"0") == 0){
                    parcel[i][j] = new char [choise.size()];
                    strcpy(parcel[i][j],choise.c_str());
                    ok = 1;
                    break;
                }
            if(ok == 1){
                break;
            }
        }


    }

    int farming(Plant_Shop const &magazin) {
        int a[size][size];


        for (int i = 0; i < this->size; i++)
            for (int j = 0; j < this->size; j++) {
                a[i][j] = -1;
                for (int k = 0; k < magazin.getSize(); k++) {
                    if (parcel[i][j] == magazin.getList()[k].getName())
                        a[i][j] = magazin.getList()[k].getGrowTime();
                }
            }
        int nr = 0, ok = 0,gold = 0;
        char alegere;
        while (nr != this->size * this->size) {
            for (int i = 0; i < this->size; i++) {
                for (int j = 0; j < this->size; j++) {
                    /// deci daca este -1 inseamna ca nu s-a plantat nimic acolo
                    /// daca e 0 insemana ca timpul pentru aceea planta s-a terminat, deci o sa ii dau bani
                    /// cand e minus -2 inseamnca ca l-am numarat deja ca sa nu fac repetie la nr o sa fac asa
                    if (a[i][j] == -1)
                        nr++, a[i][j] = -2;
                    else if (a[i][j] > 0)
                        a[i][j]--;
                    else if (a[i][j] == 0) {
                        a[i][j] = -2;
                        gold =gold + culege_planta(i, j, magazin);
                        ok = 1;
                        nr++;
                    }

                }
            }
            Sleep(700); /// calcule, ca o sa piarda putin timp in cod, so scad din mili secunde ca sa nu se vada;)

        }
    return gold;
    }

    int culege_planta(int index, int jndex, Plant_Shop const &magazin) {
        for (int i = 0; i < magazin.getSize(); i++)
            if (parcel[index][jndex] == magazin.getList()[i].getName()) {
               parcel[index][jndex] = new char [1];
                strcpy(parcel[index][jndex],"0");
               // cout << "Ai cules o planta de " << magazin.getList()[i].getName() << "\n";
                //cout << "Ai primit suma de "
                  //   << 2 * (magazin.getList()[i].getPrice()) + magazin.getList()[i].getPrice() / 2 << "$\n";
                return 2 * (magazin.getList()[i].getPrice()) + magazin.getList()[i].getPrice() / 2;
            }
    }

    friend ostream &operator<<(ostream &out, const Farm &ferma);
};

ostream &operator<<(ostream &out, const Farm &ferma) {
    for (int i = 0; i < ferma.size; i++)
        out << "-------";
    out << "\n";
    for (int i = 0; i < ferma.size; i++) {
        for (int j = 0; j < ferma.size; j++)
            out << "| " << ferma.parcel[i][j][0] <<ferma.parcel[i][j][1]<< " | ";
        out << "\n";
        for (int i = 0; i < ferma.size; i++)
            out << "-------";
        out << "\n";
    }
    return out;
}
class Monster{
protected:
    int health;
    int damage;
    string name;
    static vector<Drop_Item> posibil_drop;
    static int size;
    Drop_Item drop;
    Monster(int health = 0, int damage = 0):health(health),damage(damage){
        vector<string> vec = {"Lovitura simpla","Lovitura de sabie","Lovitura cu arc","Lovitura cu prastia"};
        int number = rand() % 4;
        name = vec[number];

    }
    void generate_item(){
        if(!posibil_drop.empty()){
            int random = rand()%size;
            drop = posibil_drop[random];
        }
        else{
            cout<<"Nu ai dropurile initializate!\n";
        }
    }
public:
    static void create_drop(string file_name){
        ifstream file(file_name);
        int pret;
        string nume;
        int gmana;
        int ghealth;
        while(file>>nume && file>>pret && file>>gmana && file>>ghealth){
            Drop_Item insert(nume,pret,gmana,ghealth);
            posibil_drop.push_back(insert);
            size++;
        }
        file.close();

    }
    static vector<Drop_Item> getVect(){return posibil_drop;}
    static int getSize(){return size;}

    virtual Drop_Item item_dropat(){return drop;}
   virtual int attack() const = 0;
   virtual void show_monster() const = 0;
   virtual void damage_by_player(const Weapon &arma_player,const int alegere) = 0;
   virtual bool is_dead() {
       if(health > 0) return false;
       return true;
   }
   virtual ~Monster() = default;

};
vector<Drop_Item> Monster::posibil_drop ={};
int Monster::size = 0;

class Minion : virtual public Monster{
    string type;
    Ability speciala;
public:
    Minion():Monster(250,rand() % 4 + 2){
        int random_number = rand() % 5 ; // generez random in constructor un type(eu nu stiu ce tipe e)
        // de ce? pentru ca e mai fun
        vector<string> vec = {"foc","apa","pamant","gheata","lava","aer"};
        type = vec[random_number];
        random_number = rand() % 21 +10;
        speciala.setAbilityDamage(random_number);
        vec = {"Pumnul de ","Furtuna de ","Greierul de ","Furia de "};
        if(random_number >=10 && random_number <=15){speciala.setAbilityName(vec[0]+type);}
        else if(random_number >15 && random_number <=20){speciala.setAbilityName(vec[1]+type);}
        else if(random_number >20 && random_number <=25){speciala.setAbilityName(vec[2]+type);}
        else {speciala.setAbilityName(vec[3]+type);}
        generate_item();
        // pe partea de lovituri simple ale minionului lucrez mai jos
       // this->damage = rand() % 4 + 2; random intre [2,5]

    }
    ~Minion() = default;

    void show_monster() const override{

        /// de lucrat cu atentie
        cout<<"|-------------";
        for(auto i=type.begin();i<type.end();i++)
            cout<<"-";
        cout<<"-|\n";
        cout<<"| Minionul de "<<type<<" |"<<endl;
        cout<<"|-------------";
        for(auto i=type.begin();i<type.end();i++)
            cout<<"-";
        cout<<"-|\n";

        cout<<"| Abilitate normala \n";

        cout<<"|";
        for(auto i =name.begin(); i<name.end();i++)
            cout<<"-";
        cout<<"--------|\n";
        cout<<"|"<<this->name;
        cout<<"("<<this->damage<<" dmg) |"<<endl;
        cout<<"|";
        for(auto i =name.begin(); i<name.end();i++)
            cout<<"-";
        cout<<"--------|\n";

        cout<<"| Abilitate speciala \n";
        cout<<"|";
        for(auto i = this->speciala.getAbilityName().begin(); i<this->speciala.getAbilityName().end();i++)
            cout<<"-";
        cout<<"---------|\n";
        cout<<"|"<<this->speciala.getAbilityName();
        cout<<"("<<this->speciala.getAbilityDamage()<<" dmg) |"<<endl;
        cout<<"|";
        for(auto i = this->speciala.getAbilityName().begin(); i<this->speciala.getAbilityName().end();i++)
            cout<<"-";
        cout<<"---------|\n";
        cout<<"HP: "<<health;


    }
    int attack() const override {
        int random_number = rand()% 101;
        if(random_number >=70){
            cout<<"Minionul isi incarca "<<this->speciala.getAbilityName()<<endl;
            cout<<speciala.getAbilityDamage()<<"DMG";
            return this->speciala.getAbilityDamage();
        }
            else{
            cout<<"Minionul foloseste "<<this->name;
            cout<<damage<<"DMG";
            return this->damage;
        }

    }
    bool defend() {
        int random  = rand() %101;
        if(random <=20){return true;}
        return false;
    }
    void damage_by_player(const Weapon &arma_player,const int dmg_given_by_player) override{
      int initial_health = health;
        if(arma_player.getType() == type){
            int damage_given = dmg_given_by_player-((dmg_given_by_player /100)*25);
            health -=damage_given;
        }
        else if((arma_player.getType() == "apa" and type =="foc") or
                (arma_player.getType() =="aer" and type =="lava") or
                (arma_player.getType() =="foc" and type == "gheata") or
                (arma_player.getType() =="lava" and type =="pamant") or
                (arma_player.getType() =="pamant" and type == "aer") or
                (arma_player.getType() =="gheata" and type =="apa")){
            int damage_given = dmg_given_by_player+((dmg_given_by_player /100)*25);
            health -=damage_given;
        }
        else if((arma_player.getType() == "foc" and type =="apa") or
               (arma_player.getType() =="lava" and type =="aer") or
               (arma_player.getType() =="gheata" and type == "foc") or
               (arma_player.getType() =="pamant" and type =="lava") or
               (arma_player.getType() =="aer" and type == "pamant") or
               (arma_player.getType() =="apa" and type =="gheata")){
            int damage_given = dmg_given_by_player-((dmg_given_by_player /100)*40);
            health -=damage_given;
        }
        else {health -= dmg_given_by_player;}

        cout<<"Minionul a fost lovit cu succes!\n I-ai dat "<<initial_health-health<<" damage. ";
    }


};
class Boss: virtual public Monster{
    string type;
    string boss_name;
    int level;
    Ability speciala;
public:
    Boss():level(rand()%3+2),Monster(level*100,rand()%5+5){
        int random_number = rand() % 5 ; // generez random in constructor un type(eu nu stiu ce tipe e)
        // de ce? pentru ca e mai fun
        vector<string> vec = {"foc","apa","pamant","gheata","lava","aer"};
        type = vec[random_number];
        vec ={"Inferno","Enigma","Dust","Frostbite","Moltenfire","Tornado"};
        boss_name = vec[random_number];
        random_number = rand() % 21 +20;
        speciala.setAbilityDamage(random_number);
        vec = {"Taietura de ","Ghiarele de ","Furtuna de ","Rasuflarea dragonului de "};
        if(random_number >=20 && random_number <=25){speciala.setAbilityName(vec[0]+type);}
        else if(random_number >25 && random_number <=30){speciala.setAbilityName(vec[1]+type);}
        else if(random_number >30 && random_number <=35){speciala.setAbilityName(vec[2]+type);}
        else {speciala.setAbilityName(vec[3]+type);}
        generate_item();

    }
    ~Boss() = default;
///pentru show_monster o sa fie in functie de tip:
    ///foc->Inferno,gheata->Frostbite,apa->Enigma,pamant->Dust,lava->Moltenfire,aer->Tornado

    void show_monster() const override{

        /// de lucrat cu atentie
        cout<<"|-";
        for(auto i=boss_name.begin();i<boss_name.end();i++)
            cout<<"-";
        cout<<"-|\n";
        cout<<"| "<<boss_name<<" |"<<endl;
        cout<<"|-";
        for(auto i=boss_name.begin();i<boss_name.end();i++)
            cout<<"-";
        cout<<"-|\n";

        cout<<"| Abilitate normala \n";

        cout<<"|";
        for(auto i =name.begin(); i<name.end();i++)
            cout<<"-";
        cout<<"--------|\n";
        cout<<"|"<<this->name;
        cout<<"("<<this->damage<<" dmg) |"<<endl;
        cout<<"|";
        for(auto i =name.begin(); i<name.end();i++)
            cout<<"-";
        cout<<"--------|\n";

        cout<<"| Abilitate speciala \n";
        cout<<"|";
        for(auto i = this->speciala.getAbilityName().begin(); i<this->speciala.getAbilityName().end();i++)
            cout<<"-";
        cout<<"---------|\n";
        cout<<"|"<<this->speciala.getAbilityName();
        cout<<"("<<this->speciala.getAbilityDamage()<<" dmg) |"<<endl;
        cout<<"|";
        for(auto i = this->speciala.getAbilityName().begin(); i<this->speciala.getAbilityName().end();i++)
            cout<<"-";
        cout<<"---------|\n";
        cout<<"HP: "<<health;


    }
    ///pentru attack mai mare sansa de criticala
    int attack() const override {
        int random_number = rand()% 101;
        if(random_number >=70){
            cout<<boss_name<<" isi incarca "<<this->speciala.getAbilityName()<<endl;
            cout<<speciala.getAbilityDamage()<<"DMG";
            return this->speciala.getAbilityDamage();
        }
        else{
            cout<<boss_name<<"  foloseste "<<this->name;
            cout<<this->damage<<"DMG";
            return this->damage;
        }

    }
    string getBossName() const {return boss_name;}
    bool dodge(){
        int random = rand() %101;
        if(random >= 40) return false;
        return true;

    }
    /// sa dai mai putin dmg cand e couter, chiar sa dai 0
    /// cand e acelasi tipe sa dai mai putin
    void damage_by_player(const Weapon &arma_player,const int dmg_given_by_player) override{
        int initial_health = health;
        if(arma_player.getType() == type){
            int damage_given = dmg_given_by_player-((dmg_given_by_player /100)*30);
            health -=damage_given;
        }
        else if((arma_player.getType() == "apa" and type =="foc") or
                (arma_player.getType() =="aer" and type =="lava") or
                (arma_player.getType() =="foc" and type == "gheata") or
                (arma_player.getType() =="lava" and type =="pamant") or
                (arma_player.getType() =="pamant" and type == "aer") or
                (arma_player.getType() =="gheata" and type =="apa")){
            int damage_given = dmg_given_by_player+((dmg_given_by_player /100)*30);
            health -=damage_given;
        }
        else if((arma_player.getType() == "foc" and type =="apa") or
                (arma_player.getType() =="lava" and type =="aer") or
                (arma_player.getType() =="gheata" and type == "foc") or
                (arma_player.getType() =="pamant" and type =="lava") or
                (arma_player.getType() =="aer" and type == "pamant") or
                (arma_player.getType() =="apa" and type =="gheata")){
            int damage_given = dmg_given_by_player-((dmg_given_by_player /100)*50);
            health -=damage_given;
        }
        else {health -= dmg_given_by_player;}

        cout<<"Minionul a fost lovit cu succes!\n I-ai dat "<<initial_health-health<<" damage. ";
    }


};

class Minion_Boss:public Minion, public Boss{
    string type;
    string mini_name;
    Ability speciala;
    int traint;
public:
    Minion_Boss():Monster(300,rand()%3+1),traint(rand()%2){
        int random_number = rand() % 5 ; // generez random in constructor un type(eu nu stiu ce tipe e)
        // de ce? pentru ca e mai fun
        vector<string> vec = {"foc","apa","pamant","gheata","lava","aer"};
        type = vec[random_number];
        vec ={"Ignisrex","Malphasor","Skulkrax","Gnarlfang","Necrogrin","Pyrodor"};
        mini_name = vec[random_number];
        random_number = rand() % 21 +20;
        speciala.setAbilityDamage(random_number);
        vec = {"Explozie de ","Lovitura de ","Sarpele de ","Vartejul de "};
        if(random_number >=20 && random_number <=25){speciala.setAbilityName(vec[0]+type);}
        else if(random_number >25 && random_number <=30){speciala.setAbilityName(vec[1]+type);}
        else if(random_number >30 && random_number <=35){speciala.setAbilityName(vec[2]+type);}
        else {speciala.setAbilityName(vec[3]+type);}
        generate_item();

    }
    ~Minion_Boss() = default;
    int attack() const override {
        int random_number = rand()% 101;
        if(random_number >=70){
            cout<<mini_name<<" isi incarca "<<this->speciala.getAbilityName()<<endl;
            cout<<speciala.getAbilityDamage()<<"DMG";
            return this->speciala.getAbilityDamage();
        }
        else{
            cout<<mini_name<<" foloseste "<<this->name;
            cout<<damage<<"DMG";
            return this->damage;
        }

    }
    string getMiniName() const {return mini_name;}
    int defend_or_dodge() {
       /// 1 daca defend 0 daca dodge
       return traint;
    }
    void show_monster() const override {

        /// de lucrat cu atentie
        cout << "|-";
        for (auto i = mini_name.begin(); i < mini_name.end(); i++)
            cout << "-";
        cout << "-|\n";
        cout << "| " << mini_name << " |" << endl;
        cout << "|-";
        for (auto i = mini_name.begin(); i < mini_name.end(); i++)
            cout << "-";
        cout << "-|\n";

        cout << "| Abilitate normala \n";

        cout << "|";
        for (auto i = name.begin(); i < name.end(); i++)
            cout << "-";
        cout << "--------|\n";
        cout << "|" << this->name;
        cout << "(" << this->damage << " dmg) |" << endl;
        cout << "|";
        for (auto i = name.begin(); i < name.end(); i++)
            cout << "-";
        cout << "--------|\n";

        cout << "| Abilitate speciala \n";
        cout << "|";
        for (auto i = this->speciala.getAbilityName().begin(); i < this->speciala.getAbilityName().end(); i++)
            cout << "-";
        cout << "---------|\n";
        cout << "|" << this->speciala.getAbilityName();
        cout << "(" << this->speciala.getAbilityDamage() << " dmg) |" << endl;
        cout << "|";
        for (auto i = this->speciala.getAbilityName().begin(); i < this->speciala.getAbilityName().end(); i++)
            cout << "-";
        cout << "---------|\n";
        cout<<"HP: "<<health;

    }
            void damage_by_player(const Weapon &arma_player,const int dmg_given_by_player) override{
                    int initial_health = health;
                    if(arma_player.getType() == type){
                        int damage_given = dmg_given_by_player-((dmg_given_by_player /100)*25);
                        health -=damage_given;
                    }
                    else if((arma_player.getType() == "apa" and type =="foc") or
                    (arma_player.getType() =="aer" and type =="lava") or
                    (arma_player.getType() =="foc" and type == "gheata") or
                    (arma_player.getType() =="lava" and type =="pamant") or
                    (arma_player.getType() =="pamant" and type == "aer") or
                    (arma_player.getType() =="gheata" and type =="apa")){
                        int damage_given = dmg_given_by_player+((dmg_given_by_player /100)*25);
                        health -=damage_given;
                    }
                    else if((arma_player.getType() == "foc" and type =="apa") or
                    (arma_player.getType() =="lava" and type =="aer") or
                    (arma_player.getType() =="gheata" and type == "foc") or
                    (arma_player.getType() =="pamant" and type =="lava") or
                    (arma_player.getType() =="aer" and type == "pamant") or
                    (arma_player.getType() =="apa" and type =="gheata")){
                        int damage_given = dmg_given_by_player-((dmg_given_by_player /100)*40);
                        health -=damage_given;
                    }
                    else {health -= dmg_given_by_player;}

                    cout<<"Minionul a fost lovit cu succes!\n I-ai dat "<<initial_health-health<<" damage. ";
            }



        };



/*
       Mob
Minion      Boss
    Boss-Minion
*/

void loading_bar(char *unde) {
    char *loading_bar = new char[16];
    char a = 177;
    strcpy(loading_bar, "...............");
    for (int i = 0; i < 15; i++) {
        system("CLS");
        cout << "\n" << unde << "\n";
        loading_bar[i] = a;

        cout << loading_bar;
        Sleep(100);
    }
    delete [] loading_bar;

}

void dialog_cu_personaje(string nume_personaj="",string mesaj1_67="",string mesaj2_67="",string mesaj3_67="") {
        atomic <bool> exit(false);
        cout<<"| Pentru a da SKIP apasa tasta [Q] |\n";

        thread t1([&](){
            cout << "[ ";
            for (auto i = nume_personaj.begin(); i < nume_personaj.end(); i++) {
                cout << *i;
                if(exit == true) {
                    break;
                }
                Sleep(100);
            }
            cout << " ]\n";
            for (auto i = mesaj1_67.begin(); i < mesaj1_67.end(); i++) {
                cout << *i;
                if(exit == true) {
                    break;
                }
                Sleep(100);
            }
            cout << "\n";
            for (auto i = mesaj2_67.begin(); i < mesaj2_67.end(); i++) {
                cout << *i;
                if(exit == true) {
                    break;
                }
                Sleep(100);
            }
            cout << "\n";
            for (auto i = mesaj3_67.begin(); i < mesaj3_67.end(); i++) {
                cout << *i;
                if(exit == true) {
                    break;
                }
                Sleep(100);
            }
            cout << endl;
            Sleep(100);
        });
     char choise = 'p';
    while(choise != 'q'){
        choise = getch();
        if(choise == 'q'){
            exit = true;
            system("CLS");
            cout<<"Tocmai ai dat skip...";
            Sleep(300);
            system("CLS");
            }
    }
    t1.join();
}



void ghiozdan_menu(){
    system("CLS");
    cout<<"|----------|\n";
    cout<<"| Ghiozdan |\n";
    cout<<"|----------|\n";
    cout<<"\n";
    cout<<"[1] Inventar Arme\n";
    cout<<"[2] Inventar Seminte\n";
    cout<<"[3] Inventar Consumabile\n";
    cout<<"[0] Inapoi\n";
}

void deschide_inventar_arme(Player &jucator,Inventory<Weapon> &inventar_arme){
    system("CLS");
    inventar_arme.show_inventory();
    int input;
    cout<<endl<<"Arma actuala: "<<jucator.getArma()<<endl;
    cout<<"Doresti sa iti schimbi arma?[0/1]:\n";cin>>input;
    if(input == 1){
        system("CLS");
        inventar_arme.show_inventory();
        cout<<"Ce arma ?:";cin>>input;
        try{
            jucator.switch_weapon(input,inventar_arme);
        }
        catch(const Index_Invalid& ex){
            cout<<ex.what();
        }
        cout<<"Arma schimbata cu succes. Press ANY key to go back.\n";
    }
}
void deschide_inventar_plante(Inventory<Plant> &inventar_plante){
    system("CLS");
    inventar_plante.show_inventory();
}
void deschide_inventar_drop(Player &player,Inventory<Drop_Item> &inventar_drop){
    system("CLS");
    inventar_drop.show_inventory();
    int alegere;
    cout<<"Vrei sa consumi ceva?: ";cin>>alegere;
    try{
        Drop_Item mancat(inventar_drop.ret(alegere));
        inventar_drop.pop(alegere);
        player.give_hp(mancat.GetHealth());
        player.give_mana(mancat.GetMana());

    }catch(const Index_Invalid &ex){cout<<ex.what();}
    }
void deschide_inventar(Player &jucator,Inventory<Weapon> &inventar_arme,Inventory<Plant> &inventar_plante, Inventory<Drop_Item> &inventar_mobi){
    char choise = 'p';
    while(choise != '0'){
        ghiozdan_menu();
        choise = getch();
        switch(choise){
            case '1':deschide_inventar_arme(jucator,inventar_arme);getch();break;
            case '2':deschide_inventar_plante(inventar_plante);getch();break;
            case '3':deschide_inventar_drop(jucator,inventar_mobi);getch();break;
        }
    }

}

void farm_upgrade(Player &player,Farm &farm){
    try{
        loading_bar("Incerci sa maresti ferma...");
        cout<<"\n";
        farm.farm_upgrade(player);
    }catch(No_Money &ex){cout<<ex.what();}
    Sleep(500);
}

vector<Plant> drops;
void planteaza(Farm &farm, Player &jucator,Inventory<Weapon> &inventar_arme,Inventory<Plant> &inventar_plante){ //geko
    system("CLS");
    cout<<"Iti deschizi ghiozdanul si te uiti in buzunarul cu seminte...\n";
    Sleep(2000);
    system("CLS");
    inventar_plante.show_inventory();
    cout<<"Ce planta alegi?";
    int alegere;
    cin >> alegere;
    if(!farm.full_farm()){
        try{
            farm.where_to_plant(farm.what_to_plant(inventar_plante,alegere,drops));
        }catch(Index_Invalid &ex){cout<<ex.what();}
    }
    else{
        cout<<"Ferma este plina si nu mai poti planta nimic \n";
    }
    char a;
    cout<<"Press ENTER to get back\n";
    a = getch();
}

void showfarm(Farm &ferma){
    system("CLS");
    cout<<ferma;
    char a;
    cout<<"Press ENTER to get back\n";
    a = getch();
}

void gold(Player &jucator){
    system("CLS");
    cout<<jucator.getPlayerName()<<" ai suma de "<<jucator.getGold()<<" $.\n";
    char a;
    cout<<"Press ENTER to get back\n";
    a = getch();
}

atomic<bool> planting{false};
atomic<float> experienta_plante = 0;

    void colect_gold(Player &player,Inventory<Drop_Item> &inventar_mobi){
    system("CLS");
    planting = false;
    cout<<"Tocmai ce ai cules recolta:\n";
    for(auto i = drops.begin();i<drops.end();i++){
        inventar_mobi.add_to_inventory(i->plant_to_item());
    }
    drops.clear();
    player.give_xp(experienta_plante);
    experienta_plante = 0;

}
Plant_Shop f;
void pleaca_thread(Farm &ferma, vector<Shop*> magazine){
        system("CLS");
        cout<<"Ai terminat de plantat si de udat plantele.\n Trebuie sa astepti pana cresc, dar nu trebuie sa le pazesti...\n"
              <<"Trebuie sa vii inapoi sa le si culegi...\n";
        for(auto i = magazine.begin(); i<magazine.end();i++){
            if(dynamic_cast<Plant_Shop*>(*i) != nullptr){
                f = *dynamic_cast<Plant_Shop*>(*i);
                break;
            }
        }

    thread lala([&](){
        planting =true;
        experienta_plante = ferma.farming(f)/2;
        cout<<"|----------------------|\n";
        cout<<"TI-AU CRESCUT PLANTELE |\n";
        cout<<"|----------------------|\n";
        Sleep(1000);

    });
    lala.detach();
    }
void menu_farm(Player &jucator){
    system("CLS");
    cout<<"|------------";
    for(int i =0;i<jucator.getPlayerName().size();i++)
        cout<<"-";
    cout<<"|\n";
    cout<<"| Ferma lui "<<jucator.getPlayerName()<<" |\n";
    cout<<"|------------";
    for(int i =0;i<jucator.getPlayerName().size();i++)
        cout<<"-";
    cout<<"|";
    cout<<"\n";
    if(!planting){
        cout<<"[1] Upgrade Farm\n";
        cout<<"[2] Plant\n";
        cout<<"[3] Show Farm\n";
        cout<<"[4] Start Grow\n";
        cout<<"[5] Gold\n";
        cout<<"[6] Inventar\n";
        cout<<"[0] Return \n";
    }
    else  if(experienta_plante !=0){
        cout<<"[5] Gold\n";
        cout<<"[6] Inventar\n";
        cout<<"[7] Culege Plantele\n";
        cout<<"[0] Return \n";

    }
    else{
        cout<<"[5] Gold\n";
        cout<<"[6] Inventar\n";
        cout<<"[0] Return \n";
    }
}
void farming(Player &player, Farm &ferma, vector<Shop*> magazine, Inventory<Weapon> &inventar_arme, Inventory<Plant> &inventar_plante, Inventory<Drop_Item> &inventar_mobi){
    loading_bar("Mergi la ferma...");

    char choise = 'p';
    while(choise != '0'){
        menu_farm(player);
        choise = getch();
        switch(choise){
            if(!planting){
                case '1':farm_upgrade(player,ferma);break;
                case '2':planteaza(ferma,player,inventar_arme,inventar_plante);break;
                case '3':showfarm(ferma);break;
                case '4':pleaca_thread(ferma,magazine);getch();break;

            }
            else if(experienta_plante != 0){
                case'7':colect_gold(player,inventar_mobi);getch();break;


            }
            case '5':gold(player);break;
            case '6':deschide_inventar(player,inventar_arme,inventar_plante,inventar_mobi);break;

        }
    }
    cout<<"Press any key to get back\n";

}

void magazin_arme(vector<Shop*> magazine, Player &jucator, Inventory<Weapon> &inventar_arme, Inventory<Plant> &inventar_plante){
    system("CLS");
    Weapon_Shop *copy;
    for(auto i = magazine.begin(); i<magazine.end();i++){
        if(dynamic_cast<Weapon_Shop*>(*i) != nullptr){
            copy = dynamic_cast<Weapon_Shop*>(*i);
            break;
        }
    }

    copy->afisare();
    int input;
    cout<<"Ce arma alegi?:";
    cin>>input;
    try{
        jucator.weapon_upgrade(*copy,input,inventar_arme);
        cout<<"Ai cumparat arma cu succes\nPress ANY key to go back!\n";
    }
    catch(No_Money &ex1){cout<<ex1.what();}
    catch(Index_Invalid &ex2){cout<<ex2.what();}
    }
void cumpara_plante(vector<Shop*>magazine, Player&jucator, Inventory<Plant> &inventar_plante){
    system("CLS");
    Plant_Shop *copy;
    for(auto i = magazine.begin(); i<magazine.end();i++){
        if(dynamic_cast<Plant_Shop*>(*i) != nullptr){
            copy = dynamic_cast<Plant_Shop*>(*i);
            break;
        }
    }

    copy->afisare();
    int input;
    cout<<"Ce planta cumperi?:";
    cin>>input;
    try{
        jucator.buy_plant(*copy,input,inventar_plante);
        cout<<"Planta cumparat cu succes.Press ANY key to go back!\n";
    }
    catch(No_Money &ex1){cout<<ex1.what();}
    catch(Index_Invalid &ex2){cout<<ex2.what();}

}
int ok = 0;
void amanet(Player &player, Inventory<Weapon> &magazin_arme, Inventory<Plant> &magazin_plante,Inventory<Drop_Item> &inventar_mobi){
    system("CLS");
    if(ok == 0){
        ok++;
        dialog_cu_personaje("Marian",
                            "Buna, nu ne-am mai de ceva timp. Ce ai mai facut in tot acest timp...",
                            "Sincer sa iti spun am crezut ca ai plecat cu batzul acela in pestera, ai mare",
                            "grija pentru ca acesta nu are abilitate speciala, iar acest lucru inseamna ca mori. Cu ce te ajut?");
    }
    int ce;
    char input;
    cout<<endl<<"Ce vrei sa vinzi?\n[1] Arme\n[2] Plante\n [3] Consumabile\n";input=getch();
    if(input == '1'){
        magazin_arme.show_inventory();
        cout<<"Alege:";
        cin>>ce;
        player.sell_weapon(ce,magazin_arme);
        cout<<"Arma vanduta cu succes!. Press ANY key to go back";
    }
    else if(input == '2'){
        magazin_plante.show_inventory();
    cout<<"Alege:";
    cin>>ce;
    player.sell_p(ce,magazin_plante);
    cout<<"Samanta vanduta cu succes.Press ANY key to go back";
    }
    else{
        inventar_mobi.show_inventory();
        cout<<"Ce doresti sa vinzi?:";cin>>ce;
        player.sell_drop(ce,inventar_mobi);
        cout<<"Consumabilul a fost vandut cu succes.\n Press ANY key to go back.";

    }
}
void meniu_fierar(){
    system("CLS");
    cout<<"|----------------------------------------|\n";
    cout<<"| Fierarul Maiestos schimbator de tipuri |\n";
    cout<<"|----------------------------------------|\n";
    cout<<"[1] Aer\n";
    cout<<"[2] Lava\n";
    cout<<"[3] Foc\n";
    cout<<"[4] Ghiata\n";
    cout<<"[5] Pamant\n";
    cout<<"[0] Exit \n";
}
int fieraro = 0;
void fierar(Player &jucator,Inventory<Weapon> &arme){
    system("CLS");
    if(fieraro == 0){
        dialog_cu_personaje("Fierar","Nu imi pasa cine esti! Ai bani ca sa te ajut?",
                            "Vezi ca sunt un fierar asa bun incat pot sa o si stric!");
    fieraro ++;
    }
       char choise = 'p';
        while (choise != '0') {
            meniu_fierar();
            choise = getch();
            switch (choise) {
                case '1': jucator.schimba_tipul("aer",arme); getch(); break;
                case '2': jucator.schimba_tipul("lava",arme); getch(); break;
                case '3': jucator.schimba_tipul("foc",arme); getch(); break;
                case '4': jucator.schimba_tipul("ghiata",arme); getch(); break;
                case '5': jucator.schimba_tipul("pamant",arme); getch(); break;


            }
        }

        cout<<"Press any key to get back\n";


    }

void meniu_weapon_store(){

    system("CLS");
    cout<<"|----------------------------------|\n";
    cout<<"| Piata Mare din Regatul de Ghiata |\n";
    cout<<"|----------------------------------|\n";
    cout<<"[1] Vezi Gold\n";
    cout<<"[2] Magazin de arme\n";
    cout<<"[3] Magazin de plante\n";
    cout<<"[4] Inventar\n";
    cout<<"[5] Amanet\n";
    cout<<"[6] Fierarul Maiestos\n";
    cout<<"[0] Exit \n";
}
void shopping(Player& player, vector<Shop*>magazine, Inventory<Weapon>& inventar_arme, Inventory<Plant>& inventar_plante, Inventory<Drop_Item> &inventar_mobi) {
    loading_bar("Mergi in piata din sat...");
    char choise = 'p';
    while (choise != '0') {
        meniu_weapon_store();
        choise = getch();
        switch (choise) {
            case '1': gold(player); getch(); break;
            case '2': magazin_arme(magazine, player, inventar_arme, inventar_plante); getch(); break;
            case '3': cumpara_plante(magazine, player, inventar_plante); getch(); break;
            case '4': deschide_inventar(player,inventar_arme, inventar_plante,inventar_mobi); getch(); break;
            case '5':amanet(player,inventar_arme,inventar_plante,inventar_mobi);getch();break;
            case '6':fierar(player,inventar_arme);getch();break;

        }
    }

    cout<<"Press any key to get back\n";

}

void combat_menu(Monster *monstru,Player &player){
    system("CLS");
    monstru->show_monster();
    cout<<endl;
    cout<<"|------------------------|\n";
    cout<<"| Ce o sa alegi sa faci? |\n";
    cout<<"|------------------------|\n";
    cout<<"Nume:"<<player.getPlayerName()<<endl;
    cout<<"HP: "<<player.getHealth()<<endl;
    cout<<"MANA: "<<player.getMana()<<endl;
    cout<<"[1] Lovitura Normala\n";
    cout<<"[2] Lovitura Speciala\n";
    cout<<"[3] Deschide Inventar\n";
    cout<<"[0] Fugi din pestera\n";


}
bool mort = false;
void lovitura_normala(Player &player,Monster *monstru,Inventory<Weapon> &inventar_arme,Inventory<Plant> &inventar_plante){
    system("CLS");
    try{
        Minion *minion = dynamic_cast<Minion*>(monstru);
        if(!minion->defend()){
            cout << "Lovsti monstrul cu " << player.getArma() << endl;
            Sleep(300);
            monstru->damage_by_player(player.getArma(), player.getArma().getDamage());
        }
        else{
            cout << "Lovsti monstrul cu " << player.getArma() << endl;
            Sleep(300);
            cout<<"Minionul a reusit sa puna un scut magic in fata lui\n";
            monstru->damage_by_player(player.getArma(), player.getArma().getDamage()-10);
        }
    }
    catch(bad_cast &a) {
        try {
            Boss *boss = dynamic_cast<Boss *>(monstru);
            if (!boss->dodge()) {
                cout << "Lovsti monstrul cu " << player.getArma() << endl;
                monstru->damage_by_player(player.getArma(), player.getArma().getDamage());
            } else {
                cout << boss->getBossName() << " a reusit sa se fereasca in ultimul moment!\n";
                Sleep(300);
            }
        } catch (bad_cast &a) {

            Minion_Boss *minionBoss = dynamic_cast<Minion_Boss *>(monstru);
            int dodge_defend = minionBoss->defend_or_dodge();
            if (dodge_defend == 1) {
                Boss *defend = minionBoss;
                if (!defend->dodge()) {
                    cout << "Lovsti monstrul cu " << player.getArma() << endl;
                    monstru->damage_by_player(player.getArma(), player.getArma().getDamage());
                } else {
                    minionBoss = dynamic_cast<Minion_Boss *>(monstru);
                    cout << minionBoss->getMiniName() << " a sarit si a evitat miscarea ta!\n";
                    Sleep(300);
                }
            } else {

                if (minionBoss->defend()) {
                    cout << "Lovsti monstrul cu " << player.getArma() << endl;
                    Sleep(300);
                    monstru->damage_by_player(player.getArma(), player.getArma().getDamage());
                } else {
                    cout << "Lovsti monstrul cu " << player.getArma() << endl;
                    Sleep(300);
                    cout << minionBoss->getMiniName() << " a baut o un suc ciudat si a s-a aparat!\n";
                    monstru->damage_by_player(player.getArma(), player.getArma().getDamage() - 15);
                }
            }
            /// 1 daca defend 0 daca dodge
        }
    }
    Sleep(2000);
    system("CLS");
    cout << "[Monstru]\n";
    int damage = monstru->attack();
    player.take_damage(damage);
    if (player.getHealth() <= 0) {
        player.respawn_character();
        mort = true;

    }

}
void lovitura_speciala(Player &player,Monster *monstru,Inventory<Weapon> &inventar_arme,Inventory<Plant> &inventar_plante){

    if(player.getMana() >=25 ) {
        system("CLS");
        player.take_mana(25);
        try {
            Minion *minion = dynamic_cast<Minion *>(monstru);
            if (!minion->defend()) {
                cout << "Lovsti monstrul cu " << player.getArma() << endl;
                Sleep(300);
                monstru->damage_by_player(player.getArma(),
                                          player.getArma().getAbilitate().getAbilityDamage());
            } else {
                cout << "Lovsti monstrul cu " << player.getArma() << endl;
                Sleep(300);
                cout << "Minionul a reusit sa puna un scut magic in fata lui\n";
                monstru->damage_by_player(player.getArma(),
                                          player.getArma().getAbilitate().getAbilityDamage() - 10);
            }
        } catch (bad_cast &a) {
            try {

                Boss *boss = dynamic_cast<Boss *>(monstru);
                if (!boss->dodge()) {
                    cout << "Lovsti monstrul cu " << player.getArma() << endl;
                    monstru->damage_by_player(player.getArma(),
                                              player.getArma().getAbilitate().getAbilityDamage());
                } else {
                    cout << boss->getBossName() << " a reusit sa se fereasca in ultimul moment!\n";
                    Sleep(300);
                }
            }
            catch (bad_alloc &a) {
                Minion_Boss *minionBoss = dynamic_cast<Minion_Boss *>(monstru);
                int dodge_defend = minionBoss->defend_or_dodge();
                if (dodge_defend == 1) {
                    Boss *defend = minionBoss;
                    if (!defend->dodge()) {
                        cout << "Lovsti monstrul cu " << player.getArma() << endl;
                        monstru->damage_by_player(player.getArma(),
                                                  player.getArma().getAbilitate().getAbilityDamage());
                    } else {
                        minionBoss = dynamic_cast<Minion_Boss *>(monstru);
                        cout << minionBoss->getMiniName() << " a sarit si a evitat miscarea ta!\n";
                        Sleep(300);
                    }
                } else {

                    if (minionBoss->defend()) {
                        cout << "Lovsti monstrul cu " << player.getArma() << endl;
                        Sleep(300);
                        monstru->damage_by_player(player.getArma(),
                                                  player.getArma().getAbilitate().getAbilityDamage());
                    } else {
                        cout << "Lovsti monstrul cu " << player.getArma() << endl;
                        Sleep(300);
                        cout << minionBoss->getMiniName()
                             << " a baut o un suc ciudat si a s-a aparat!\n";
                        monstru->damage_by_player(player.getArma(),
                                                  player.getArma().getAbilitate().getAbilityDamage() -
                                                  15);
                    }
                }
                /// 1 daca defend 0 daca dodge
            }
        }
        Sleep(2000);
        system("CLS");
        cout << "[Monstru]\n";
        int damage = monstru->attack();
        player.take_damage(damage);
        if (player.getHealth() <= 0) {
            player.respawn_character();
            mort = true;

        }


    }
    else{
        system("CLS");
        cout<<"Nu ai mana.\n";
    }

}
void fighting_script(Player &player,Monster *monstru,Inventory<Weapon> &inventar_arme,Inventory<Plant> &inventar_plante,
                     int &intamplare, Inventory<Drop_Item> &inventar_mobi){
    char choise = 'p';
    mort = false;
    while(choise != '0'){
        combat_menu(monstru,player);
        choise = getch();
        switch(choise){
            case '1':lovitura_normala(player,monstru,inventar_arme,inventar_plante) ;getch();break;
            case '2':lovitura_speciala(player,monstru,inventar_arme,inventar_plante);getch();break;
            case'3':deschide_inventar(player,inventar_arme,inventar_plante,inventar_mobi);getch();break;


        }
        if(mort){intamplare = 0;break;}
        else if(monstru->is_dead()){intamplare = 1;break;}
    }
    if(intamplare!=0)
        intamplare = 2;

}

void enter_cave(Player &player,Inventory<Weapon> &inventar_arme,Inventory<Plant> &inventar_plante, Inventory<Drop_Item> &inventar_mobi) {
    int player_lvl = player.getlevel();
    vector<Monster*> cave;
    for(int i = 0; i<player_lvl;i++){
        Monster *minion = new Minion();
        cave.push_back(minion);
    }
    for(int i = 0; i<player_lvl;i++){
        Monster *mini_boss = new Minion_Boss();
        cave.push_back(mini_boss);
    }
    Monster *final_boss = new Boss();
    cave.push_back(final_boss);
    random_shuffle(cave.begin(),cave.end()-1);
    for(int i = 0; i<cave.size();i++){
        int action=-1;
        fighting_script(player,cave[i],inventar_arme,inventar_plante,action,inventar_mobi);
        if( action== 0 or action == 1){break;}
        else{
            cout<<"\nFelicitari, ai omorat un monstru.\nIn cenusa lui ai gasit "<<cave[i]->item_dropat().GetName();
            inventar_mobi.add_to_inventory(cave[i]->item_dropat());
            getch();
        }
    }
    for(int i = 0; i<cave.size();i++){
        delete cave[i];
    }
    cave.clear();


}

void statistici(Player &player){
    system("CLS");
    cout<<player;
    cout<<"Press ENTER to get back\n";
}
void menu_game(){
    system("CLS");
    cout<<"|--------------|\n";
    cout<<"| Interactiuni |\n";
    cout<<"|--------------|\n";
    cout<<"\n";
    cout<<"[1] Statistici\n";
    cout<<"[2] Mergi la ferma\n";
    cout<<"[3] Mergi la magazin\n";
    cout<<"[4] Inventar\n";
    cout<<"[5] Mergi in pestera\n";
    cout<<"[0] Exit Game\n";
}

void the_game_menu(Player &player, Farm &ferma, vector<Shop*> magazine, Inventory<Weapon> &inventar_arme, Inventory<Plant> &inventar_plante, Inventory<Drop_Item> &inventar_mobi){
    char choise = 'p';
    while(choise != '0'){
        menu_game();
        choise = getch();
        switch(choise){
            case '1':statistici(player);getch();break;
            case '2':farming(player,ferma, magazine,inventar_arme,inventar_plante,inventar_mobi);getch();break;
            case '3':shopping(player,magazine,inventar_arme,inventar_plante,inventar_mobi);getch();break;
            case '4':deschide_inventar(player,inventar_arme,inventar_plante,inventar_mobi);getch();break;
        }
    }
    exit(0);

}

void intro(Player &player, Farm &ferma, vector<Shop*> magazine, Inventory<Weapon> &inventar_arme, Inventory<Plant> &inventar_plante, Inventory<Drop_Item> &inventar_mobi){
    system("CLS");
    cin>>player;
    system("CLS");
    dialog_cu_personaje("Marian","Buna si bine ai venit in minunata noastra calatorie.","Monstrii din pesteri ti-au furat tot hameiul, iar in acest an nu o sa poti face bere.:(");
/*
    cout<<"Marian: \n";
    char *buna = new char [strlen("Buna ")];
    strcpy(buna,"Buna ");
    for(int i = 0;i < strlen(buna);i++){
        cout<<buna[i];
       Sleep(100);
    }
    for(auto i = player.getPlayerName().begin();i < player.getPlayerName().end();i++){
        cout<<*i;
      Sleep(100);
    }
    cout<<' ';
    buna = new char [strlen(" si bine ai venit in minunata noastra calatorie.\n Monstrii din pesteri ti-au furat tot hameiul, iar in acest an nu o sa poti face bere.:(")];
    strcpy(buna,"si bine ai venit in minunata noastra calatorie.\n Monstrii din pesteri ti-au furat tot hameiul, iar in acest an nu o sa poti face bere.:(");
    for(int i = 0;i < strlen(buna);i++){
        cout<<buna[i];
       Sleep(100);
    }
    Sleep(300);
*/
    the_game_menu(player,ferma, magazine,inventar_arme,inventar_plante,inventar_mobi);
}


void add_plant(vector<Shop*> magazine){
    system("CLS");
    Plant_Shop* copy;
    for(auto i = magazine.begin(); i<magazine.end();i++){
        if(dynamic_cast<Plant_Shop*>(*i) != nullptr){
            copy = dynamic_cast<Plant_Shop*>(*i);
            break;
        }
    }

    cin>>*copy;
    system("CLS");
    cout<<"Felicitari, o noua planta a fost adaugata in Shop! \n";
    Sleep(500);
    system("CLS");
    copy->afisare();
    cout<<"Press ENTER to get back\n";

}

void dev_menu(){
    system("CLS");
    cout<<"|----------------|\n";
    cout<<"| Developer Menu |\n";
    cout<<"|----------------|\n";
    cout<<"\n";
    cout<<"[1] Add New Plant\n";
    cout<<"[2] Cave\n";
    cout<<"[0] Exit Game\n";
}
void developer(Player &player, Farm &ferma, vector<Shop*>magazine, Inventory<Weapon> &inventar_arme, Inventory<Plant> &inventar_plante, Inventory<Drop_Item> &inventar_mobi){
    char choise = 'p';
    player.give_money(10000);
    Weapon_Shop* copy;
    for(auto i = magazine.begin(); i<magazine.end();i++){
        if(dynamic_cast<Weapon_Shop*>(*i) != nullptr){
            copy = dynamic_cast<Weapon_Shop*>(*i);
            break;
        }
    }

    player.weapon_upgrade(*copy,6,inventar_arme);
    while(choise != '0'){
        dev_menu();
        choise = getch();
        switch(choise){
            case '1':add_plant(magazine);getch();break;
            case '2':enter_cave(player,inventar_arme,inventar_plante,inventar_mobi);getch();break;

        }
    }
    cout<<"Press any key to get back\n";

}
void afis_start_menu(){
    system("CLS");
    cout<<"|----------|\n";
    cout<<"| OOP Game |\n";
    cout<<"|----------|\n";
    cout<<"\n";
    cout<<"[1] Start Game\n";
    cout<<"[2] Developer Mode\n";
    cout<<"[0] Exit Game\n";
}

void start_menu(Player &player, Farm &ferma, vector<Shop*> magazine, Inventory<Weapon> &inventar_arme, Inventory<Plant> &inventar_plante, Inventory<Drop_Item> &inventar_mobi){
char choise = 'p';
while(choise != '0'){
    afis_start_menu();
    choise = getch();
    switch(choise){
        case '1':intro(player,ferma,magazine,inventar_arme,inventar_plante,inventar_mobi);getch();break;
        case '2':developer(player,ferma,magazine,inventar_arme,inventar_plante,inventar_mobi);getch();break;
    }
}
    exit(0);
}
int main() {


      Player jucator;
      jucator.give_money(10000);
      Farm ferma;
      ferma.generate_farm();
      vector<Shop*> magazine;
      magazine.push_back(new Plant_Shop());
      magazine.push_back(new Weapon_Shop());
      magazine[0]->citire("C:\\Users\\Darius Corneciu\\CLionProjects\\POO_Game\\plants.txt");
      magazine[1]->citire("C:\\Users\\Darius Corneciu\\CLionProjects\\POO_Game\\arme.txt");

      Monster::create_drop("C:\\Users\\Darius Corneciu\\CLionProjects\\POO_Game\\drop_items");
      Inventory<Weapon> inventar_arme;
      Inventory <Plant> inventar_plante;
      Inventory <Drop_Item> inventar_mobi;
      start_menu(jucator,ferma,magazine,inventar_arme,inventar_plante,inventar_mobi);
      for(auto i = magazine.begin();i<magazine.end();i++){delete *i;}
      magazine.clear();
     return 0;
}
/*
int main(){
    Plant_Shop shop_plante;
    shop_plante.citire_plante("C:\\Users\\Darius Corneciu\\CLionProjects\\POO_Game\\plants.txt");

    Shop arme;
    arme.citire_arme("C:\\Users\\Darius Corneciu\\CLionProjects\\POO_Game\\arme.txt");

    Player darius("Darius");
    darius.give_money(100000);
    Inventory<Weapon> inv_arme;
    Inventory<Plant> inv_plante;
    darius.weapon_upgrade(arme,2,inv_arme);
    darius.buy_plant(shop_plante,2,inv_plante);
    inv_arme.show_inventory();
    inv_plante.show_inventory();



    //  cout<<darius;
    //i

    Sleep(10000);
    return 0;
}
*/
