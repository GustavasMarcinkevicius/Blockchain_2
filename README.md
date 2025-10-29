# Blockchain_2

Aprašymas

Šis projektas įgyvendina supaprastintą blokų grandinę C++ kalba, imituojančią pagrindinę realios blokų grandinės logiką. Kiekvienas blokas turi antraštę ir transakcijų sąrašą. Naudojamas Proof-of-Work mechanizmas su savita hash funkcija, kad bloko hash prasidėtų nuo nurodyto nulio skaičiaus.

Funkcionalumas:

- Generuojama 1000 vartotojų su atsitiktiniais balansas ir viešaisiais raktais.

- Generuojama 10 000 transakcijų tarp vartotojų.

- Kuriami blokai po 100 transakcijų.

- Skaičiuojami blokų hash naudojant savą funkciją.

- Realizuotas Proof-of-Work: hash pradžioje bent 3 nuliai.

- Blokai sujungiami į blokų grandinę.

- Konsolėje galima peržiūrėti blokų informaciją ir transakcijas.

1. Vartotojų generavimas 

<img width="516" height="317" alt="image" src="https://github.com/user-attachments/assets/ae3486cf-7eb4-4467-821a-66c8227239e6" />

2. Transakcijų generavimas

<img width="1153" height="318" alt="image" src="https://github.com/user-attachments/assets/d891f2a2-868d-414d-8356-58c68d6ff85b" />


3. Panaudojus komandą bc[x].printBlockTransactions(), kur bc - mūsų blockchainas, o x - norimas blokas, galima gauti visas to bloko transakcijas
(jų yra 100 kiekvienam bloke, nuotraukoje neparodytos visos)
<img width="1084" height="675" alt="image" src="https://github.com/user-attachments/assets/4da010e9-a6f8-42df-b8ed-69b1a5f1b35b" />

4. Bloko kasimas (Proof-of-Work):
<img width="1621" height="75" alt="image" src="https://github.com/user-attachments/assets/f6810111-685d-43c1-86ae-92d17d07e7c5" />
<img width="1623" height="152" alt="image" src="https://github.com/user-attachments/assets/c9c60918-8961-4af7-bc32-0ffef721f93c" />

5. Vartotojų balansai pabaigoj

<img width="497" height="292" alt="image" src="https://github.com/user-attachments/assets/201e23b5-6249-4497-8e89-cca270ca659b" />

