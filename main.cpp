#include <iostream>
#include <cstring>
#include <fstream>
#include <windows.h>
#include <cmath>
#include <conio.h>
#include <algorithm>

using namespace std;

class Ability {
    int ability_damage;
    char *ability_name;

public:
    Ability() : ability_damage(0), ability_name(nullptr) {};

    Ability(const Ability &ability){
        ability_damage = ability.ability_damage;
        ability_name = new char [strlen(ability.ability_name)];
        strcpy(ability_name,ability.ability_name);

    }




    int getAbilityDamage() const {
        return ability_damage;
    }

    char *getAbilityName() const {
        return ability_name;
    }

    void setAbilityDamage(int abilityDamage) {
        ability_damage = abilityDamage;
    }

    void setAbilityName(char *abilityName) {
        ability_name = new char[strlen(abilityName)];
        strcpy(ability_name, abilityName);
    }


};

class Weapon {
    char *weapon_name;
    int price;
    Ability abilitate;
    int damage;
    Weapon *next;

public:
    Weapon() {
        next = nullptr;
        weapon_name = nullptr;
    }
    Weapon(const Weapon &arma):abilitate(arma.abilitate){
        price = arma.price;
        damage = arma.damage;
        weapon_name = new char [strlen(arma.weapon_name)];
        strcpy(weapon_name,arma.weapon_name);
        next = arma.next;

    }

    ~Weapon() {
        if (next != nullptr)
            delete next;
        if (weapon_name != nullptr)
            delete[] weapon_name;
    }

    int getPrice() const {
        return price;
    }

    char *getWeaponName() const {
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

        this->abilitate.setAbilityName(abilitate.getAbilityName());
        this->abilitate.setAbilityDamage(abilitate.getAbilityDamage());

    }

    Weapon *getNext() const {
        return next;
    }

    void setWeaponName(char *weaponName) {
        weapon_name = new char[strlen(weaponName)];
        strcpy(weapon_name, weaponName);
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

    ~Shop() {
        if (start != nullptr) {
            delete start;
        }
    }

    void add_weapon(int dmg, char *name, int pret, int dmg_special, char *special_name) {
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

    int find_weapon_price_by_name(char *name) {
        Weapon *actual = start;
        while (actual->getNext() != nullptr) {

            if (strcmp(actual->getWeaponName(),name) == 0)
                return actual->getPrice();
            actual = actual->getNext();
        }
        if (strcmp(actual->getWeaponName(),name) == 0)
            return actual->getPrice();
        return -1;

    }

    char *find_weapon_by_index(int index) {
        Weapon *actual = start;
        if(index < 1)
            return "Invalid Index for a weapon!";
        for (int i = 1; i < index; i++) {
            if (actual->getNext() != nullptr)
                actual = actual->getNext();
            else
                return "Invalid Index for a weapon!";
        }
        return actual->getWeaponName();
    }

    void citire_arme(const char *filename) {
        int dmg, pret, speciala;
        char *nume, *nume_speciala, spatiu;
        nume = new char[50];
        nume_speciala = new char[30];
        fstream file(filename);


        while (file >> dmg && file.get(spatiu) && file.getline(nume, 40, ' ') && file >> pret && file >> speciala &&
               file.get(spatiu) && file.getline(nume_speciala, 22, '\n')) {
            replacer(nume, '_', ' ');
            replacer(nume_speciala, '_', ' ');
            add_weapon(dmg, nume, pret, speciala, nume_speciala);


        }

        delete[] nume;
        delete[] nume_speciala;
    }

private:
    void replacer(char *nume, const char relpace, const char replace_with) {
        for (int i = 0; i < strlen(nume); i++)
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
    while (actual->getNext() != nullptr) {
        out << actual->getWeaponName() << "\n Damage:" << actual->getDamage() << "\n Price: " << actual->getPrice()
            << "\n";
        out << actual->getAbilitate().getAbilityName() << " | " << actual->getAbilitate().getAbilityDamage() << "\n";
        out << "---------------------------\n";
        actual = actual->getNext();
    }
    out << actual->getWeaponName() << "\n Damage:" << actual->getDamage() << "\n Price: " << actual->getPrice() << "\n";
    out << actual->getAbilitate().getAbilityName() << " | " << actual->getAbilitate().getAbilityDamage() << "\n";
    out << "---------------------------\n";


    return out;
}

class Plant { ///restructurat ca sa mearga intr-un vector de astrel de elemente
    char *name;
    int price;
    int grow_time;
public:
    Plant() {
        name = nullptr;
        price = 0;
        grow_time = 0;
    }
    Plant(const Plant &plantuta){
        price = plantuta.price;
        grow_time = plantuta.grow_time;
        name = new char [strlen(plantuta.name)];
        strcpy(name,plantuta.name);
    }

    ~Plant() {
        if (name != nullptr)
            delete [] name;
    }

    char *getName() const {
        return name;
    }

    int getPrice() const {
        return price;
    }

    int getGrowTime() const {
        return grow_time;
    }

    void setName(char *name) {
        this->name = new char[strlen(name)];
        strcpy(this->name, name);
    }

    void setPrice(int price) {
        Plant::price = price;
    }

    void setGrowTime(int growTime) {
        grow_time = growTime;
    }
    void operator=(const Plant &planta) {
        if (planta.name != nullptr) {
            this->name = new char[strlen(planta.name)];
            strcpy(this->name, planta.name);
            this->grow_time = planta.grow_time;
            this->price = planta.price;
        } else if (planta.name == nullptr) {
            delete[] this->name;
            grow_time = 0;
            price = 0;
        } else if (strcmp(this->name, planta.name) == 0) {
            cout << "Nu poti copia aceeasi planta!\n";
        }
    }
    Plant &operator[](int index) {
        return *(this + index);
    };

    friend istream &operator>>(istream &in, Plant &plantuta);

};
istream &operator>>(istream &in, Plant &plantuta){
    char *aux = new char [20];
    cout<<"Citeste numele plantei(20 caractere maxim): ";
    in.getline(aux,20);
    plantuta.name = new char [strlen(aux)];
    strcpy(plantuta.name,aux);
    delete [] aux;
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

    ~Plant_Shop() {
        if (list != nullptr)
            delete [] list;

    }

    int getSize() const;

    Plant *getList() const;

    void citire_plante(char *filename) { ///nu este completat, trebuie gandit
        ifstream file(filename);
        int pret, timp;
        char nume[20];
        ///asta e singura metoda fara sa folosec sting.
        list = new Plant[20];
        while (file >> pret && file >> timp && file.getline(nume, 20, ' ') && file.getline(nume, 20, '\n')) {
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
    char *player_name;
    char *sword;

public:
    Player() : health_point(100), mana(100), level(1), experience(0), gold(100) {

        strcpy(sword, "Batz");
        player_name = nullptr;
    }
    Player(const Player &jucator): health_point(jucator.health_point),mana(jucator.mana),level(jucator.level),experience(jucator.experience),gold(jucator.gold){
        player_name = new char [strlen(jucator.player_name)];
        sword = new char[strlen(jucator.sword)];
        strcpy(player_name,jucator.player_name);
        strcpy(sword,jucator.sword);

    }

    Player(const char *name) : Player() { //apeleaza intai constructorul fara parametrii si dupa aceaia se uita
        // la ce are el de facut in constructorul cu parametrii
        player_name = new char[strlen(name)];
        strcpy(player_name, name);
    }

    ~Player() {
        if (player_name != nullptr)
            delete[] player_name;
        if (sword != nullptr)
            delete[] sword;
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

        char *noua_arma = new char[strlen(magazin.find_weapon_by_index(alegere))];
        strcpy(noua_arma, magazin.find_weapon_by_index(alegere));
        int pretul = magazin.find_weapon_price_by_name(noua_arma);
        if (this->gold >= pretul and strcmp(noua_arma,"Invalid Index for a weapon!") !=0) {
            this->gold -= pretul;
            this->sword = noua_arma;
            cout << "Arma cumaparata cu succes!\n";
        } else if (this->gold <pretul) {
            cout << "Nu ai destui bani!\n";
        }
        else cout<<noua_arma;
    }

    int getGold() const;

    char *getPlayerName() const;

    friend istream &operator>>(istream &in, Player &player);

    friend ostream &operator<<(ostream &out, const Player &player);

    void setGold(int gold);
};

istream &operator>>(istream &in, Player &player) {
    cout << "Introdu numele tau(acesta poate avea maxim 16 caractere): ";
    char *v = new char[16];
    in.getline(v, 16);
    player.player_name = new char[strlen(v)];
    strcpy(player.player_name, v);
    delete[] v;
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
    out << "| Sword: " << player.sword << "\n";
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

char *Player::getPlayerName() const {
    return player_name;
}


class Farm {
///
    char **parcel;
    int size;

public:
    Farm() {
        size = 0;
        parcel = nullptr;
    }
    Farm(const Farm &ferma):size(ferma.size){
        parcel = new char *[size];
        for(int i = 0;i < size;i++){
            parcel[i] = new char [size];
            for(int j = 0;j < size;j++)
                parcel[i][j] = ferma.parcel[i][j];
        }

    }

    ~Farm() {
        if (parcel != nullptr) {

            delete[] parcel;
        }
    }

    void generate_farm(const int size = 2) {
        this->size = size;
        parcel = new char *[this->size];
        for (int i = 0; i < this->size; i++)
            parcel[i] = new char[this->size];
        for (int i = 0; i < this->size; i++)
            for (int j = 0; j < this->size; j++)
                parcel[i][j] = '0';
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
                if (parcel[i][j] == '0')
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
                if (parcel[i][j] != '0')
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

    char what_to_plant(Plant_Shop &magazin, int alegere) {
        alegere = alegere - 1;
        Plant *lista = magazin.getList();
        char *nume = lista[alegere].getName();
        return nume[0];

    }

    void where_to_plant(char choise) {
        int ok = 0;
        for(int i = 0; i<size;i++)
        {
            for(int j = 0 ;j<size;j++)
                if(parcel[i][j] == '0'){
                    parcel[i][j] = choise;
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
                    if (parcel[i][j] == magazin.getList()[k].getName()[0])
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
            if (parcel[index][jndex] == magazin.getList()[i].getName()[0]) {
                parcel[index][jndex] = '0';
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
        out << "------";
    out << "\n";
    for (int i = 0; i < ferma.size; i++) {
        for (int j = 0; j < ferma.size; j++)
            out << "| " << ferma.parcel[i][j] << " | ";
        out << "\n";
        for (int i = 0; i < ferma.size; i++)
            out << "------";
        out << "\n";
    }
    return out;
}

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
            char initiala = farm.what_to_plant(shop_plante, alegere);
            farm.where_to_plant(initiala);

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
    for(int i =0;i<strlen(jucator.getPlayerName());i++)
        cout<<"-";
    cout<<"|\n";
    cout<<"| Ferma lui "<<jucator.getPlayerName()<<" |\n";
    cout<<"|------------";
    for(int i =0;i<strlen(jucator.getPlayerName());i++)
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
    for(int i = 0;i < strlen(player.getPlayerName());i++){
        cout<<player.getPlayerName()[i];
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
