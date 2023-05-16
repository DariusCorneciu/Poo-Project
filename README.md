# Poo-Project
![image](https://user-images.githubusercontent.com/116907008/229105332-cbfc8d39-f504-4694-a391-50117d684104.png)

## Despre joc?
- Este un RPG text-based in care trebuie sa completezi toate pesterile pentru a termina jocul.

## Un mini story-line.
- Esti un fermier intr-un oras rupt de realite. Se apropie primavara, iar recolta de hamei este aproape gata. Deodata din pesteri apar creaturi nemaivazute pe acest pamant. Acestea iti fura toata recolta de hamei pentru a-si face bere in pesteri.
- Suparat pe viata te hotarasti sa distrugi toate creaturile care vin din pesteri, dar fiind un fermier nu iti permiti sa iti cumperi o sabie asa ca apuci primul lucru pe care il ai la indemana, adica un bat si portnesti catre pestera.
- In drum spre pestera un alt fermier te avertizeaza ca monstii acestia sunt foarte puternici si nu poti sa ii dobori doar cu un bat. Suparat te intorci acasa si incepi sa cauti metode pentru a face bani.
- Realizezi ca esti fermier asa ca iti verifici sacul cu galbeni si observi ca ai 100 de banuti. Cu acestia te duci la Baba Smaranda si iti cumperi seminte pentru a planta recolta. Fiind un univers magic plantele cresc mult mai repede decat in lumea reala.
- Restul povestii iti apartine dragule jucator.... 

## Sisteme
- Fiind un joc bazat pe text acesta foloseste clase pentru a instantia obiectele necesare pentru aceasa aventura.
### Sistem de Shop
![tumblr_p5flokH8161qbw2q1o1_1280](https://github.com/DariusCorneciu/Poo-Project/assets/116907008/1eb870af-92ff-44de-9934-d57af89eb068)

- Acest sistem este facut printr-o interfata numita Shop
- Exista in momentul de fata 2 shopuri: #arme, #plante
```cpp
class Shop{}
class Weapon_Shop:public Shop{} ///este un vector de arme
class Plant_Shop:public{} ///este un vector de plante
```
### Sistem de level up
- In clasa de player exista o metoda cu numele give_exp care iti creste experienta si tot odata nivelul.
```cpp
Formula folosita pentru exp:
(level / amount_xp) ^ quickly_required_xp_per_level
```
### Sistem de Inventar
Sistemul de inventar este bazat pe un template pentru a usura codul si a nu aveam 3 clase diferite pentru inventar.
```cpp
template <class inv>
class Inventory{
    vector <inv> items;
```
- Acesta este un vector de typename(in cazul meu inv)
- Are diferite metode pentru a oferi un obiect, al arunca din inventar, a adauga un obiect in inventar

### Sistem de Pesteri
![6d13119ec35d038c0649f6f4d5f2b9ad](https://github.com/DariusCorneciu/Poo-Project/assets/116907008/8baaaba9-721d-4e08-8651-b011c6894999)

Aici este magia propriu zisa a codului. Sistemul se bazeaza pe o 4 clase care sunt mostenite in diamant:
- Clasa de baza este o clasa abrstracta care viata, damage-ul, numele abilitatii normale, dar are in componenta si un vector static de Drop_Items
- Totul in aceste clase a incercat sa se bazeze pe o componenta random
- Clasele copil: Minion si Boss au abilitati diferite(una poate sa dea defend, ala dodge) pentru a avea sens sa se faca upcast si downcast.
- Ultma clasa mosteneste clasele Minion si Boss si poate sa aiba defend sau dodge ca si abilitate.
- Sistemul de pesteri este bazat pe un vector<Monster*> cave care are un numar de monstrii in functie de nivelul jucatorului. Ulterior acesta este amestecat, dar lasand boss-ul la final.
Exemple de upcast si downcast in codul meu:
```cpp
try{
        Minion *minion = dynamic_cast<Minion*>(monstru);
    }catch(bad_cast &a){
    try{
        Boss *boss = dynamic_cast<Boss *>(monstru);
        } catch(bad_cast &a) {
            Minion_Boss *minionBoss = dynamic_cast<Minion_Boss *>(monstru);
            }
```
### Sistem de Farm
![Wheat_Farm_1619093296938](https://github.com/DariusCorneciu/Poo-Project/assets/116907008/df5bb66f-bad6-43e6-8a5b-b5ed90b0a977)

- Initial ai o parcela de 2x2 care este exsinsa tot cu bani
- Pentru a incepe sa plantezi trebuie sa mergi la magazinul de plante pentru a-ti cumpara seminte
- Semintele se gasesc in inventarul pentru plante
- Fiecare planta are un anumit timp de asteptate pentru a creste
- Cand plantele au crescut, o sa primesti o planta
- Sistemul de crestere este facut pe un alt thread pentru a rula in fundal.
```cpp
thread lala([&](){
        planting =true;
        experienta_plante = ferma.farming(f)/2;
        cout<<"|----------------------|\n";
        cout<<"TI-AU CRESCUT PLANTELE |\n";
        cout<<"|----------------------|\n";
        Sleep(1000);

    });
    lala.detach();
```
