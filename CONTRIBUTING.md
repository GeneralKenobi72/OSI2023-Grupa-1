# Contributing to softver-za-registraciju-vozila

U ovom fajlu se nalaze osnovna uputstva za:
- Pokretanje projekta i
- doprinos projektu

## 📌 Pokretanje projekta
Nakon sto se pozicionirate na mjesto na disku, na kojem zelite da vam se nalazi projektni zadatak, pozivate komandu:
```sh
git clone https://github.com/GeneralKenobi72/Softver-za-registraciju-vozila.git
```
Nakon prethodne komande imacete citavu istoriju promjena, i sve podatke o projektu. Dalje mozete otvoriti projekat u zeljenom editoru, ili okruzenju(Visual Stduio, Visual Studio Code, vim, nano, ...).

### Pokretanje na Linux-u
Potrebno da imate instaliran cmake i make.
Pozicionirate se na root direktorijum projekta i pozivate sledece komande:
```sh
cmake
make
./bin/Softver-za-registraciju-vozila
```
Komanda cmake se poziva samo jednom, kada se tek preuzme projekat.
Komanda ./bin/Softver-za-registraciju-vozila sluzi za pokretanje projekta.
Ako ste napravili promjene u projektu i zelite da provjerite njihov rad, koristite sledece komande:
```sh
make clean
make
./bin/Softver-za-registraciju-vozila
```
### Pokretanje na Windows-u
Ako koristite Visual Studio ili Visual Studio Code, potrebno je da preuzmete ekstenziju "CMake Tools". Otvorite projekat u VS ili VSC i pokrenite ga.

## 📌 Doprinos projektu
Kada kucate kod za projekat, u direktorijum inc/ stavljate sve .h fajlove, a u src/ direktorijum sve .cpp fajlove.
Kada zelite da ukljucite neki .h fajl u .cpp fajlu dovoljno je:
```sh
#include "naziv_fajla_koji_ukljucujte.h"
```
### Uputstvo za git
Potrebno je da na GitHub-u svako napravi svoju granu(Branch). Pristupite stranici projekta na GitHub-u, Branches > New Branch > Branch name: "vase_ime".
Kada napravite neke promjene koje zelite da sacuvate, u root direktorijumu projekta:
```sh
git add .
git commit -m 'Poruka'
```
Trudite se da poruke budu smislene, i da u njima ukratko napisete sta je uradjeno u commit-u.
#### Procedura za push
1. Commit-ujte vase promjene:
    ```sh
    git add .
    git commit -m 'Poruka'
    ```
2. Sinhronizacija sa develop granom:
    ```sh
    git checkout develop
    git pull origin develop
    ```
    Da se uvjerite da je vasa grana up-to-date sa zadnjim promjenama na 'develop' grani
3. Rebase
    ```sh
    git checkout vasa-grana
    git rebase develop
    ```
    Ako postoje konflikti, razrijesite ih, stage-ujte promjene i nastavite sa rebase-om
    ```sh
    # Poslije rijesavanja konflikta
    git add .
    # Nastavi rebase
    git rebase --continue
    ```
4. Push-ajte promjene:
    ```sh
    git push origin vasa-grana
    ```
    Push-ate promjene na repozitorijum u github-u, ali na svoju granu
5. Kreirate Pull Request:
    Kreirate pull request na GitHub-u, da biste merge-ovali vase promjene sa develop granom.
6. Code Review i Testing:
    Ostali clanovi tima trebaju pregledati vas kod, provjeriti da li radi ocekivano.
7. Merge u develop:
    Kada je Pull request odobren sav novi kod ce biti na develop grani

### 🤖
