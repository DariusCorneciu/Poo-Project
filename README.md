# Poo-Project
```
░▄▀░█▀▀░░░░░░░█░█░█░█▀▀░█▀▀░█▀▄░█▀▀░░░█░▀█▀░█▀▀░█░█░▀█▀░░░░░█▀▀░█▀█░█▄█░█▀▀░▀▄░░░░▀█▀░█▀█░▀▀█░█▀▀░█▀▀░▀█▀░▀█▀░█▀█░█▀▀░░░█▀█░█▀█░█▀█
▀▄░░█░░░░▀░░▄▀░░█░█░▀▀█░█▀▀░█▀▄░▀▀█░▄▀░░░█░░█▀▀░▄▀▄░░█░░▄▄▄░█░█░█▀█░█░█░█▀▀░░▄▀░░░░█░░█░█░░░█░█▀▀░█░░░░█░░░█░░█░█░█░█░░░█░█░█░█░█▀▀
░░▀░▀▀▀░░▀░░▀░░░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░░░░▀░░▀▀▀░▀░▀░░▀░░░░░░▀▀▀░▀░▀░▀░▀░▀▀▀░▀░░░░░▀▀▀░▀░▀░▀▀░░▀▀▀░▀▀▀░░▀░░▀▀▀░▀░▀░▀▀▀░░░▀▀▀░▀▀▀░▀░░
```

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
- Cu acest sistem poti sa iti cumperi armament
- Pentru retinerea acestui shop este folosita o lista inlantuita
### Sistem de level up
- In clasa de player exista o metoda cu numele give_exp care iti creste experienta si tot odata nivelul.
```p
Formula folosita pentru exp:
(level / amount_xp) ^ quickly_required_xp_per_level
```
