
## Failai

- **Klases.h** – Apibrėžia pagrindines klases:
  - **User** – vartotojo informacija (vardas, viešasis raktas, balansas)
  - **Transaction** – transakcijos duomenys (siuntėjas, gavėjas, suma, ID)
  - **Block** – bloko duomenys (transakcijos, hash, ankstesnio bloko hash, nonce, merkle root, timestamp, version)
  - **Blockchain** – grandinės valdymas (blokų saugojimas, paskutinio bloko gavimas)

- **Funkcijos.h** – Funkcijos:
  - generuoti vartotojus
  - generuoti transakcijas
  - rinktis atsitiktines transakcijas
  - filtruoti galiojančias transakcijas
  - vykdyti balanso pakeitimus
  - kasimo logika

- **Hash.h** – Paprasta hash funkcija (simuliuoja blokų ir transakcijų hash)

- **main.cpp** – Programos paleidimas ir demonstracija:
  - sukuriami vartotojai
  - generuojamos transakcijos
  - kuriama grandinė ir kasami blokai
  - išvedama informacija apie vartotojus, transakcijas ir blokus

---

## Funkcionalumas

### Vartotojų generavimas
- Generuojami N vartotojų su atsitiktiniais balansais
- Visi vartotojai turi unikalų viešąjį raktą

<img width="770" height="317" alt="image" src="https://github.com/user-attachments/assets/d840928b-678a-45d3-8493-c1b9ede7ae7e" />


### Transakcijų generavimas
- Generuojamos atsitiktinės transakcijos tarp vartotojų
- Transakcijos, kurių suma didesnė nei siuntėjo balansas, automatiškai pašalinamos

<img width="1155" height="315" alt="image" src="https://github.com/user-attachments/assets/eaceda68-c959-4663-8b83-325b8fcc31eb" />


### Blokų kasimas
- Kuriami kandidatinių blokų rinkiniai su ribotu transakcijų skaičiumi (pvz., 100 transakcijų viename bloke)
- Blokai kasami su nustatytu sunkumo lygiu (`difficulty`) ir laiko limitu
- Jei blokas neiškasamas per ribotą laiką, laiko limitas padidinamas

<img width="745" height="136" alt="image" src="https://github.com/user-attachments/assets/cc0ad6a8-01f0-4c63-ad4f-5a5daea18e2f" />


### Galiojančių transakcijų filtravimas
- Patikrinamas siuntėjo balansas
- Patikrinamas, ar transakcijos ID sutampa su hash
- Negaliojančios transakcijos pašalinamos iš bloko

<img width="746" height="65" alt="image" src="https://github.com/user-attachments/assets/b558ed75-2e5c-469b-b5d2-eca99683af61" />


### Blokų informacijos pateikimas
- pateikiami visi blokų duomenys:
  - hash
  - ankstesnio bloko hash
  - merkle root
  - nonce
  - timestamp
  - sunkumo lygis
  - transakcijos
- Transakcijų lentelė su stulpeliais:
  - siuntėjas
  - gavėjas
  - suma
  - transakcijos ID

<img width="1093" height="326" alt="image" src="https://github.com/user-attachments/assets/c4a140e2-59dd-463d-a5d7-5a6f27f6dce0" />


AI naudojimas:
AI naudotas ReadME generavimui, minimaliems klausimams/debuginimui

