# heatEquation.cpp
Program na simuláciu rovnice vedenia tepla.

Riadky **5** až **13** sú sadou parametrov, ktoré potrebujeme na simuláciu.<br>
**DELTAX** - priestorový krok<br>
**DELTAT** - časový krok<br>
**ENDTIME** - čas, v ktorom sa simulácia ukončí<br>
**ALPHA** - súčiniteľ tepelnej vodivosti<br>
**R** - nenastavuje sa<br>
**STARTX** - začiatok intervalu, ktorý simulujeme<br>
**ENDX** - koniec intervalu, ktorý simulujeme<br>
**POINTS** - nenastavuje sa<br>
**PERIODIC_BOUNDARY_CONDITIONS** - (PBC) bool, či chceme použiť periodické okrajové podmienky (true - budú použité PBC)

Vo funkcii **function** na riadku **15** sa nastavuje funkcia (rozloženie tepla), ktorá sa bude simulovať.<br>
**fp** - na riadku **111** sa nastavuje cesta a názov súboru, kde sa zapisujú výsledky simulácie.

Po spustení programu treba zvoliť, ktorú z metód chceme použiť:
1. Eulerova metóda
2. Runge-Kutta metóda druhého rádu (midpoint)
3. Runge-Kutta metóda štvrtého rádu

# schrodinger_1D.cpp
Program na simuláciu 1D Schrödingerovej rovnice.

Riadky **5** až **10** sú sadou parametrov, ktoré potrebujeme na simuláciu.<br>
**DELTAX** - priestorový krok<br>
**DELTAT** - časový krok<br>
**ENDTIME** - čas, v ktorom sa simulácia ukončí<br>
**R** - nenastavuje sa<br>
**STARTX** - začiatok intervalu, ktorý simulujeme<br>
**POINTS** - počet bodov od začiatku **STARTX**, na ktorých sa bude počítať simulácia

Vo funkcii **function** na riadku **13** sa nastavuje funkcia **reálnej zložky**, ktorá sa bude simulovať.<br>
Vo funkcii **function2** na riadku **17** sa nastavuje funkcia **imaginárnej zložky**, ktorá sa bude simulovať.<br>
**skipSteps** - na riadku **186** určuje počet časových krokov, ktoré sa majú v súbore vo výsledkoch simulácie vynechať, dáta sa však nevynechávajú.<br>
**fp** - na riadku **188** sa nastavuje cesta a názov súboru, kde sa zapisujú výsledky simulácie. V každom čase sú zapísané dva riadky. Prvý riadok zodpovedá reálnej zložke, druhý riadok imaginárnej zložke.<br>
**fp2** - na riadku **193** sa nastavuje cesta a názov súboru, kde sa zapisujú dáta simulácie.<br>
Na riadku **202** môžeme inicializovať potenciál. Na riadkoch **128** a **129** môžeme nastaviť interval, na ktorom potenciál inicializujeme, a s akou hodnotou.

Po spustení programu treba zvoliť, ktorú z metód chceme použiť:
1. Eulerova metóda
2. Runge-Kutta metóda druhého rádu (midpoint)
3. Runge-Kutta metóda štvrtého rádu

# schrodinger_2D.cpp
Program na simuláciu 2D Schrödingerovej rovnice.

Riadky **4** až **11** sú sadou parametrov, ktoré potrebujeme na simuláciu.<br>
**DELTAT** - časový krok<br>
**ENDTIME** - čas, v ktorom sa simulácia ukončí<br>
**STARTX** - začiatok intervalu, ktorý simulujeme<br>
**NX** - počet bodov na *x* osi od začiatku **STARTX**, na ktorých sa bude počítať simulácia<br>
**NY** - počet bodov na *y* osi od začiatku **STARTX**, na ktorých sa bude počítať simulácia<br>
**DELTAX** - priestorový krok<br>
**R** - nenastavuje sa<br>
**U** - potenciál

Vo funkcii **function** na riadku **14** sa nastavuje funkcia **reálnej zložky**, ktorá sa bude simulovať.<br>
Vo funkcii **function2** na riadku **18** sa nastavuje funkcia **imaginárnej zložky**, ktorá sa bude simulovať.<br>
**fp** - na riadku **129** sa nastavuje cesta a názov súboru, kde sa zapisujú výsledky simulácie reálnej zložky.<br>
**fp2** - na riadku **134** sa nastavuje cesta a názov súboru, kde sa zapisujú výsledky simulácie imaginárnej zložky.<br>
**fp_data** - na riadku **140** sa nastavuje cesta a názov súboru, kde sa zapisujú dáta simulácie.

Po spustení programu sa rovno začne výpočet bez potreby inputu užívateľa, keďže je implementované riešenie iba Eulerovou metódou.

# filter1D.cpp
Program na filtráciu (vynechanie) výsledkov z programu **schrodinger_1D.cpp**.<br>
Program je zastaralejší, keďže v programe **schrodinger_1D.cpp** bolo neskôr implementované vynechávanie nejakého počtu časových krokov simulácie.

**SKIPNDATA** - na riadku **25** sa nastavuje počet riadkov, ktoré má program vyfiltrovať.<br>
**STARTINIT** - na riadku **26** sa nastavuje počet riadkov, ktoré sú na začiatku programu a majú vo vyfiltrovanom súbore zostať.<br>
**NUMROWS** - na riadku **27** sa nastavuje počet riadkov, ktoré sa majú po vynechaných riadkoch vypísať do vyfiltrovaného súboru.<br>
**fp** - na riadku **28** sa nastavuje cesta a názov súboru, v ktorom už sú výsledky simulácie.<br>
**fp2** - na riadku **33** sa nastavuje cesta a názov súboru, do ktorého sa zapisujú filtrované výsledky.

Po spustení súboru sa rovno začne filtrácia bez potreby inputu užívateľa.

# filter2D.cpp
Program na filtráciu (vynechanie) výsledkov z programu **schrodinger_2D.cpp**.

**SKIPNDATA** - na riadku **41** sa nastavuje počet riadkov, ktoré má program vyfiltrovať.<br>
**STARTINIT** - na riadku **42** sa nastavuje počet riadkov, ktoré sú na začiatku programu a majú vo vyfiltrovanom súbore zostať.<br>
**NUMROWS** - na riadku **43** sa nastavuje počet riadkov, ktoré sa majú po vynechaných riadkoch vypísať do vyfiltrovaného súboru.<br>
**fp** - na riadku **44** sa nastavuje cesta a názov súboru, v ktorom už sú výsledky simulácie.<br>
**fp2** - na riadku **49** sa nastavuje cesta a názov súboru, do ktorého sa zapisujú filtrované výsledky.

Po spustení súboru sa rovno začne filtrácia bez potreby inputu užívateľa.
