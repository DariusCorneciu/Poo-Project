#include <iostream>
#include <cstring>
#include <fstream>
#include <windows.h>
#include <cmath>
#include <conio.h>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
/// de refacut cc
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
    Ability abilitate;
    int damage;
    Weapon *next;

public:
    Weapon():abilitate() {
        next = nullptr;
        price = 0;
        weapon_name = "";
    }

    Weapon(const Weapon &arma):abilitate(arma.abilitate){
        if(arma.weapon_name == "" and arma.next == nullptr){
            if(this->weapon_name != "" and this-> next != nullptr){
                weapon_name = "";
                delete next;
                price = 0;
                damage = 0;
            }
        }
        else if(arma.weapon_name == this->weapon_name and (arma.next == this->next))
        {cout<<"Nu poti copia acceasi arma\n";}
        else{
            if(this->weapon_name != "" and this-> next != nullptr) {
                this->weapon_name = "";
                delete this->next;
            }
            weapon_name = arma.weapon_name;
            setNext(arma.next);
            this->price = arma.price;
            this->damage = arma.damage;
        }

    }
    ~Weapon() {
        if (next != nullptr)
            delete next;
        }

    int getPrice() const {
        return price;
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

    void setAbilitate(const Ability &abilitate) {
        //Weapon::abilitate = abilitate;
// Noul vlog: E ora 4:00 si fac debug-ing de 4 ore si aici e problema, alta rezolvare nu am gasit decat sa folosesc
// setter si getter din functia mama;)
        string nume(abilitate.getAbilityName());
        this->abilitate.setAbilityName(nume);
        this->abilitate.setAbilityDamage(abilitate.getAbilityDamage());

    }

    Weapon *getNext() const {
        return next;
    }

    void setWeaponName(string &weaponName) {
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

class Shop {
    Weapon *start;
public:
    Shop() {
        start = nullptr;
    };
    /// sa vorbesc cu majeri pentru cc
    ~Shop() {
        if (start != nullptr) {
            delete start;
        }
    }

    void add_weapon(int dmg, string &name, int pret, int dmg_special, string &special_name) {
        Ability abilitate;
        if (start == nullptr) {
            start = new Weapon();
            start->setDamage(dmg);
            start->setPrice(pret);
            start->setWeaponName(name);
            abilitate.setAbilityDamage(dmg_special);
            abilitate.setAbilityName(special_name);
            start->setAbilitate(abilitate);
            start->setNext(nullptr);
        } else {
            Weapon *actual = start, *viitor;
            while (actual->getNext() != nullptr) { actual = actual->getNext(); }
            viitor = new Weapon();
            viitor->setDamage(dmg);
            viitor->setWeaponName(name);
            viitor->setPrice(pret);
            abilitate.setAbilityDamage(dmg_special);
            abilitate.setAbilityName(special_name);
            viitor->setAbilitate(abilitate);
            actual->setNext(viitor);

        }
    }

    int find_weapon_price_by_name(string &name) {
        Weapon *actual = start;
        while (actual->getNext() != nullptr) {

            if (actual->getWeaponName() == name)
                return actual->getPrice();
            actual = actual->getNext();
        }
        if (actual->getWeaponName() == name)
            return actual->getPrice();
        return -1;

    }

    Weapon find_weapon_by_index(int index) {
        Weapon *actual = start;
        Weapon ret;

        if(index < 1)
            return ret;
        for (int i = 1; i < index; i++) {
            if (actual->getNext() != nullptr)
                actual = actual->getNext();
            else
                return ret;
        }

        return *actual;
    }

    void citire_arme(const char *filename) {
        int dmg, pret, speciala;
        string nume, nume_speciala, spatiu;
        fstream file(filename);


        while (file >> dmg && file>>nume && file >> pret && file >> speciala &&
               file>>nume_speciala) {
            replacer(nume, '_', ' ');
            replacer(nume_speciala, '_', ' ');
            add_weapon(dmg, nume, pret, speciala, nume_speciala);


        }

        }

private:
    void replacer(string &nume, const char relpace, const char replace_with) {
        for (int i = 0; i < nume.size(); i++)
            if (nume[i] == relpace)
                nume[i] = replace_with;

    }

    friend ostream &operator<<(ostream &out, const Shop &arme);

};

ostream &operator<<(ostream &out, const Shop &arme) {
    Weapon *actual = arme.start;
    out << "---------------------------\n";
    out << "|          SHOP           |\n";
    out << "---------------------------\n";
    int i = 1;
    while (actual->getNext() != nullptr) {
        out << actual->getWeaponName() << "\n Damage:" << actual->getDamage() << "\n Price: " << actual->getPrice()
            << "\n";
        out << actual->getAbilitate().getAbilityName() << " | " << actual->getAbilitate().getAbilityDamage() << "\n";
        out << "--------------"<<i<<"-------------\n";
        i++;
        actual = actual->getNext();
    }
    out << actual->getWeaponName() << "\n Damage:" << actual->getDamage() << "\n Price: " << actual->getPrice() << "\n";
    out << actual->getAbilitate().getAbilityName() << " | " << actual->getAbilitate().getAbilityDamage() << "\n";
    out << "--------------"<<i<<"-------------\n";


    return out;
}

class Plant { ///restructurat ca sa mearga intr-un vector de astrel de elemente
    string name;
    int price;
    int grow_time;
public:
    Plant() {
        name = "";
        price = 0;
        grow_time = 0;
    }
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

    const string &getName() const {
        return name;
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

};
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

class Plant_Shop {
    int size;
    Plant *list;
public:
    Plant_Shop() {
        size = 0;
        list = nullptr;
    }
    Plant_Shop(const Plant_Shop &magazin){
        if(magazin.size){
            if(this->size != 0){
                this->size = 0;
                delete [] list;
            }
        }
        else if(this->list == magazin.list){cout<<"Nu poti copia aceeasi magazin de plante!\n";}
        else{
            this->size = magazin.size;
            if(list != nullptr){delete [] list;}
            list = new Plant [this->size];
            for(int i = 0; i< this->size;i++){
                this->list[i] = magazin.list[i];
            }
        }
    }
    ~Plant_Shop() {
        if (list != nullptr)
            delete [] list;

    }

    int getSize() const;

    Plant *getList() const;

    void citire_plante(char *filename) { ///nu este completat, trebuie gandit
        ifstream file(filename);
        int pret, timp;
        string nume;
        list = new Plant[20];
        while (file >> pret && file >> timp && file >> nume) {
            list[size].setPrice(pret);
            list[size].setGrowTime(timp);
            list[size].setName(nume);
            size++;

        }


    }

    void operator=(const Plant_Shop &shop) {
        if (shop.list != nullptr) {
            delete[] this->list;
            list = new Plant[shop.size];
            for (int i = 0; i < shop.size; i++)
                list[i] = shop.list[i];
            size = shop.size;
        }
        else if(shop.list == nullptr)
                delete []  this->list;
        else if(shop.list == list)
            cout<<"Nu poti sa copiezi aceeazi lista!\n";
    }

    friend ostream &operator<<(ostream &out, const Plant_Shop &shop);
    friend istream &operator>>(istream &in, Plant_Shop &shop);

};
istream &operator>>(istream &in, Plant_Shop &shop){

    if(shop.list == nullptr){
        shop.size++;
        shop.list = new Plant [shop.size];
    }
    else {
        Plant_Shop aux = shop;
        shop.list = new Plant[shop.size + 1];
        for (int i = 0; i < shop.size; i++) {shop.list[i] = aux.list[i];}
        shop.size++;
    }
    cin>>shop.list[shop.size-1];

    }


ostream &operator<<(ostream &out, const Plant_Shop &shop) {
    out << "------------------------\n";
    out << "|      Plant Shop      |\n";
    out << "------------------------\n";

    for (int i = 0; i < shop.size; i++) {
        cout << "Price: " << shop.list[i].getPrice() << "\n";
        cout << "Name: " << shop.list[i].getName() << "\n";
        cout << "Time: " << shop.list[i].getGrowTime() << "\n";
        //out<<"------------------------\n";
        if (i + 1 < 10)
            out << "-----------" << i + 1 << "------------\n";
        else
            out << "-----------" << i + 1 << "-----------\n";

    }
    return out;
}

Plant *Plant_Shop::getList() const {
    return list;
}

int Plant_Shop::getSize() const {
    return size;
}

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
        Ability speciala;
    public:
        Arma():weapon_name("Batz"),damage(10),speciala() {}
        ~Arma() = default;

        bool are_speciala(){
            if(speciala.getAbilityDamage() == 0 and speciala.getAbilityName() =="")
                return false;
            else return true;
        }

        bool is_default(){
            return (weapon_name == "Batz" && damage == 10 && are_speciala());
        }
        void setdefault(){
           weapon_name = "Batz";
           damage = 10;
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
                required_exp_per_level = pow((this->level / amount_xp), gap_between_level);
            }
        if (this->level > 10)
            this->level = 10;
        if(this->level > actual_level)
            cout<<endl;
    }


    void give_money(int gold) {
        this->gold += gold;
    }
    void pay(int value){
        if(this->gold - value >= 0)
            this->gold -= value;

    }

    bool buy_plant(Plant_Shop &magazin, int alegere) {
        Plant *list = magazin.getList();
        if (gold >= list[alegere - 1].getPrice() and alegere <= magazin.getSize() and alegere > 0) {
            gold -= list[alegere - 1].getPrice();
            return true;
        } else if (gold < list[alegere - 1].getPrice()) {
            cout << "Nu ai destui bani pentru aceasta planta!\n";
            return false;
        } else {
            cout << "Ai facut o alegere gresita!\n";
            return false;
        }

    }

    void weapon_upgrade(Shop &magazin,const int alegere) { ///daca nu punt &magazin o sa faca un nou obiect care are aceleasi
/// adrese ca obiectul initial, iar cand vrea sa dea la destructor practic o sa incerce sa stearga de 2 ori aceeasi adresa;)

    Weapon noua_arma(magazin.find_weapon_by_index(alegere));

        if (this->gold >= noua_arma.getPrice() and noua_arma.getPrice() > 0) {
            if(noua_arma.getWeaponName() == sword.GetWeaponName()){cout<<"Ai deja arma asta!\n";}
            else{
                this->gold -= noua_arma.getPrice();
                this->sword.SetDamage(noua_arma.getDamage());
                this->sword.SetWeaponName(noua_arma.getWeaponName());
                this->sword.SetSpeciala(noua_arma.getAbilitate());
                cout << "Arma cumaparata cu succes!\n";
            }
        } else if (this->gold <noua_arma.getPrice()) {
            cout << "Nu ai destui bani!\n";
        }
        else cout<<"Index invalid!\n";
    }

    int getGold() const;

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
            cout << "Nu ai destui bani pentru acest upgrade!\n";
        }
    }

    string what_to_plant(Plant_Shop &magazin, int alegere) {
        alegere = alegere - 1;
        Plant *lista = magazin.getList();
        return lista[alegere].getName();

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

    void farming(Plant_Shop const &magazin, Player &player) {
        int a[size][size];


        for (int i = 0; i < this->size; i++)
            for (int j = 0; j < this->size; j++) {
                a[i][j] = -1;
                for (int k = 0; k < magazin.getSize(); k++) {
                    if (parcel[i][j] == magazin.getList()[k].getName())
                        a[i][j] = magazin.getList()[k].getGrowTime();
                }
            }
        int nr = 0, ok = 0,gold;
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
                        gold = culege_planta(i, j, magazin);
                        player.give_money(gold);
                        player.give_xp(gold/2);
                        ok = 1;
                        nr++;
                    }

                }
            }
            Sleep(700); /// calcule, ca o sa piarda putin timp in cod, so scad din mili secunde ca sa nu se vada;)
            if (ok == 1 and nr != this->size * this->size) {
                cout << "\n Continui sa cresti plantele?(1/0)\n";

                alegere = getch();
                if (alegere != '1')
                    break;
                else{
                    system("CLS");
                    cout<<*this;
                    cout<<"\n";
                    cout<<"Continui sa cresti plantele...\n";
                    ok = 0;
                }

            }
        }

    }

    int culege_planta(int index, int jndex, Plant_Shop const &magazin) {
        for (int i = 0; i < magazin.getSize(); i++)
            if (parcel[index][jndex] == magazin.getList()[i].getName()) {
               parcel[index][jndex] = new char [1];
                strcpy(parcel[index][jndex],"0");
                cout << "Ai cules o planta de " << magazin.getList()[i].getName() << "\n";
                cout << "Ai primit suma de "
                     << 2 * (magazin.getList()[i].getPrice()) + magazin.getList()[i].getPrice() / 2 << "$\n";
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
    Monster(){
        vector<string> vec = {"Lovitura simpla","Lovitura de sabie","Lovitura cu arc","Lovitura cu prastia"};
        int number = rand() % 4;
        name = vec[number];
    }
public:
   virtual void attack() = 0;
   virtual void show_monster() = 0;
   virtual ~Monster() = default;

};
class Minion : public Monster{
    string type;
    Ability speciala;
public:
    Minion():Monster(){
        int random_number = rand() % 5 ; // generez random in constructor un type(eu nu stiu ce tipe e)
        // de ce? pentru ca e mai fun
        vector<string> vec = {"foc","apa","pamant","ghiata","lava","aer"};
        type = vec[random_number];
        random_number = rand() % 21 +10;
        speciala.setAbilityDamage(random_number);
        vec = {"Pumnul de ","Furtuna de ","Greierul de ","Furia de "};
        if(random_number >=10 && random_number <=15){speciala.setAbilityName(vec[0]+type);}
        else if(random_number >15 && random_number <=20){speciala.setAbilityName(vec[1]+type);}
        else if(random_number >20 && random_number <=25){speciala.setAbilityName(vec[2]+type);}
        else {{speciala.setAbilityName(vec[3]+type);}}

        // pe partea de lovituri simple ale minionului lucrez mai jos
        this->damage = rand() % 4 + 2; //random intre [2,5]
        this->health = 100;
    }
    void show_monster() override{

        /// de lucrat cu atentie
        cout<<"Minionul de "<<type<<endl;
        cout<<"Abilitate normala:\n";
        cout<<this->name<<endl;
        cout<<this->damage<<endl;
        cout<<"Abilitate speciala:\n";
        cout<<this->speciala.getAbilityName()<<endl;
        cout<<this->speciala.getAbilityDamage()<<endl;


    }
    void attack() override{
        cout<<"Minionul loveste";
    }


    ~Minion() = default;

};
class Boss: public Monster{

};

class Minion_Boss: public Minion,public Boss{
    
};

/*
       Mob
Minion      Boss
    Boss-Minion
*/
/*
void loading_bar(char *unde){
    char *loading_bar = new char [16];
    char a = 177;
    strcpy(loading_bar,"...............");
    for(int i=0; i<15;i++){
        system("CLS");
        cout<<"\n"<<unde<<"\n";
        loading_bar[i] = a;

        cout<<loading_bar;
        Sleep(100);
    }
}
void farm_upgrade(Player &player,Farm &farm){
    loading_bar("Incerci sa maresti ferma...");
    cout<<"\n";
    farm.farm_upgrade(player);
    Sleep(500);
}
void planteaza(Farm &farm, Player &jucator,Plant_Shop &shop_plante){
    system("CLS");
    cout<<shop_plante;
    int alegere;
    cout << "Ce doresti sa plantezi?: ";
    cin >> alegere;
    if(!farm.full_farm()){
        if (jucator.buy_plant(shop_plante, alegere)) {
            cout << "Ai cumparat planta cu succes!\n";
            farm.where_to_plant(farm.what_to_plant(shop_plante, alegere));

        }
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
void start_grow(Player &jucator,Farm &ferma, Plant_Shop &plante){
    system("CLS");
    cout<<ferma;
    cout<<"\n Plantele incep sa creasca...\n";
    ferma.farming(plante,jucator);
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
    cout<<"[1] Upgrade Farm\n";
    cout<<"[2] Plant\n";
    cout<<"[3] Show Farm\n";
    cout<<"[4] Start Grow\n";
    cout<<"[5] Gold\n";
    cout<<"[0] Return \n";

}
void farming(Player &player, Farm &ferma, Plant_Shop &plante){
    loading_bar("Mergi la ferma...");

    char choise = 'p';
    while(choise != '0'){
        menu_farm(player);
        choise = getch();
        switch(choise){
            case '1':farm_upgrade(player,ferma);break;
            case '2':planteaza(ferma,player,plante);break;
            case '3':showfarm(ferma);break;
            case '4':start_grow(player,ferma,plante);break;
            case '5':gold(player);break;
        }
    }
    cout<<"Press any key to get back\n";

}

void magazin_arme(Shop &magazin_arme, Player &jucator){
    system("CLS");
    cout << magazin_arme;
    int input;
    cout<<"Ce arma alegi?:";
    cin>>input;
    jucator.weapon_upgrade(magazin_arme,input);
}

void meniu_weapon_store(){

    system("CLS");
    cout<<"|-----------------------------------------|\n";
    cout<<"| Magazinul de arme al Fierarul Maiestuos |\n";
    cout<<"|-----------------------------------------|\n";
    cout<<"[1] Vezi Gold\n";
    cout<<"[2] Magazin de arme\n";
    cout<<"[0] Exit \n";
}
void shopping(Player &player,Shop &magazin){
    loading_bar("Mergi la magazin...");
    char choise = 'p';
    while(choise != '0'){
        meniu_weapon_store();
        choise = getch();
        switch(choise){
            case '1':gold(player);getch();break;
            case '2':magazin_arme(magazin,player);getch();break;

        }
    }
    cout<<"Press any key to get back\n";

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
    cout<<"[0] Exit Game\n";
}

void the_game_menu(Player &player,Farm &ferma,Plant_Shop &plante,Shop &magazin){
    char choise = 'p';
    while(choise != '0'){
        menu_game();
        choise = getch();
        switch(choise){
            case '1':statistici(player);getch();break;
            case '2':farming(player,ferma, plante);getch();break;
            case '3':shopping(player,magazin);getch();break;
        }
    }
    exit(0);

}

void intro(Player &player,Farm &ferma, Plant_Shop &plante, Shop &magazin){
    system("CLS");
    cin>>player;
    system("CLS");

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

    the_game_menu(player,ferma, plante,magazin);
}


void add_plant(Plant_Shop &plante){
    system("CLS");
    cin>>plante;
    system("CLS");
    cout<<"Felicitari, o noua planta a fost adaugata in shop! \n";
    Sleep(500);
    system("CLS");
    cout<<plante;
    cout<<"Press ENTER to get back\n";

}
void dev_menu(){
    system("CLS");
    cout<<"|----------------|\n";
    cout<<"| Developer Menu |\n";
    cout<<"|----------------|\n";
    cout<<"\n";
    cout<<"[1] Add New Plant\n";
    cout<<"[0] Exit Game\n";
}
void developer(Player &player,Farm &ferma, Plant_Shop &plante, Shop &magazin){
    char choise = 'p';
    while(choise != '0'){
        dev_menu();
        choise = getch();
        switch(choise){
            case '1':add_plant(plante);getch();break;

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

void start_menu(Player &player,Farm &ferma, Plant_Shop &plante,Shop &magazin){
char choise = 'p';
while(choise != '0'){
    afis_start_menu();
    choise = getch();
    switch(choise){
        case '1':intro(player,ferma,plante,magazin);getch();break;
        case '2':developer(player,ferma,plante,magazin);getch();break;
    }
}
    exit(0);
}
int main() {


      Player jucator;
      Farm ferma;
      ferma.generate_farm();
      Plant_Shop shop_plante;
    shop_plante.citire_plante("C:\\Users\\Darius Corneciu\\CLionProjects\\POO_Game\\plants.txt");

      Shop arme;
      arme.citire_arme("C:\\Users\\Darius Corneciu\\CLionProjects\\POO_Game\\arme.txt");
      start_menu(jucator,ferma,shop_plante,arme);
     return 0;
}
*/
int main(){
    Minion *a =new Minion();
    a->show_monster();
    delete a;
    a = new Minion();
   // a->show_monster();
    Sleep(10000);
    return 0;
}

