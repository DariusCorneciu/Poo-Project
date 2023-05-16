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
![ddh4slr-82c38d93-e1a3-4414-9128-d8613670dc97](https://user-images.githubusercontent.com/116907008/229104732-183e6f08-ca71-4296-9075-951f53b0a17e.gif)
- Acest sistem este facut printr-o interfata numita Shop
- Exista in momentul de fata 2 shopuri: #arme, #plante
```p
class Shop{}
class Weapon_Shop:public Shop{} ///este un vector de arme
class Plant_Shop:public{} ///este un vector de plante
```
### Sistem de level up
- In clasa de player exista o metoda cu numele give_exp care iti creste experienta si tot odata nivelul.
```p
Formula folosita pentru exp:
(level / amount_xp) ^ quickly_required_xp_per_level
```
### Sistem de Inventar
Sistemul de inventar este bazat pe un template pentru a usura codul si a nu aveam 3 clase diferite pentru inventar.
```p
template <class inv>
class Inventory{
    vector <inv> items;
```
- Acesta este un vector de typename(in cazul meu inv)
- Are diferite metode pentru a oferi un obiect, al arunca din inventar, a adauga un obiect in inventar

### Sistem de Farm
![konstantin-tonkonozhko-farmer-export](https://user-images.githubusercontent.com/116907008/229104750-6f6df8d6-ce2a-4b8d-bbac-3a5e47dc5ee0.jpg)
- Initial ai o parcela de 2x2 care este exsinsa tot cu bani
- Pentru a incepe sa plantezi trebuie sa mergi la magazinul de plante pentru a-ti cumpara seminte
- Semintele se gasesc in inventarul pentru plante
- Fiecare planta are un anumit timp de asteptate pentru a creste
- Cand plantele au crescut, o sa primesti o planta
- Sistemul de crestere este facut pe un alt thread pentru a rula in fundal.
