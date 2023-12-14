# Míny

Tento projekt predstavuje logickú hru s názvom Míny. Je určený pre precvičenie vývoja softvéru v tíme na predmete [Základy softvérového inžinierstva](https://kurzy.kpi.fei.tuke.sk/zsi/).


## Príprava prostredia

Pre chod programu a možnosť vývoja sú potrebné tieto nástroje.

* GCC
* GNU Make


## Kompilácia programu

Na kompiláciu programu a ďalšie úlohy súvisiace s vývojom sa používa nástroj `make`. Priložený [Makefile](Makefile) definuje nasledovné ciele:

- `make` alebo `make all` — skompiluje hru a testy
- `make build` — skompiluje iba hru
- `make build_tests` — skompiluje iba testy  
- `make test` — spúšťa jednotkové testy projektu
- `make coverage` — zobrazuje pokrytie kódu jednotlivých modulov testmi
- `make clean` — odstraňuje všetky skompilované súbory


## Spúšťanie hry

Skompilovaná hra spolu so všetkými ostatnými výsledkami kompilácie je uložená do adresáre `build`. Hru teda môžete spústiť príkazom `./build/mines` (Unix) alebo `.\build\mines.exe` (Windows).


## Pokrytie kódu testami

Po spustení testov je možné zobraziť percento pokrytia kódu testami pomocou `make coverage`. Na výpočet sa využíva nástroj [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html), ktorý je súčasťou GCC, ale počíta pokrytie pre každý modul samostatne. Súhrne výsledky pokrytia kódu testmi všetkých modulov je možné získať pomocou [nástroja gcovr](https://gcovr.com/):

    gcovr -e test


## Vývoj

Vývoj sa bude odohrávať vo vašich samostatných [vetvách](https://docs.gitlab.com/ee/user/project/repository/branches/) (branches) projektu.

Po odoslaní riešenia do systému GitLab je potrebné vytvoriť [žiadosť o zlúčenie vetiev](https://docs.gitlab.com/ee/user/project/merge_requests/index.html) (merge request) pre zlúčenie zmien.


## Autori

* **Pavol Dlugoš** — vývoj
* **Sergej Chodarev** — vývoj, posudok


## Licencia

Tento projekt je distribuovaný v súlade s podmienkami [licencie MIT](LICENSE).


## Poďakovanie

* Inšpirované projektom  [Minesweeper](https://git.kpi.fei.tuke.sk/jaroslav.poruban/gamestudio2019)
* Zahrňa knižnicu [C String Builder](https://github.com/cavaliercoder/c-stringbuilder)
* Zahrňa knižnicu pre jednotkové testovanie [greatest](https://github.com/silentbicycle/greatest/)
