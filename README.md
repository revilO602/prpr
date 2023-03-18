# Procedural Programming

## Project 1
Basic file operations in C.

Program je napísaný v jazyku C a na jeho skompilovanie je potrebný kompilátor C.
Program pracuje so záznamami zapísanými v súbore
autobazar.txt obsahujúci záznamy o predaji áut. Vykonávajú sa
príkazy načítané zo štandardného vstupu. Každý príkaz bude predstavovať malé
písmeno nasledované koncom riadku:

**v** - výpis záznamov s pomenovaním položiek.

**o rrrrmmdd** - tento príkaz treba zadať spolu s dnešným dátumom.
             Výpis mien zamestnancov, ktorí získajú odmenu a jej výška.
             Odmenu získajú ak pracujú dlhšie ako rok, výška závisí od typu auta.

**n** - spočíta počet záznamov a vytvorí pole znakov, do ktorého uloží všetky ŠPZ.

**s** - vypíše ŠPZ z pola s medzerami medzi písmenami a číslami.

**m** - vypíše najčastejšie sa vyskytujúci znak v poli a jeho početnosť.

**p** - vypíše skratku okresu pre ŠPZ, ktoré sú palindrom.

**z** - zistí z ktorých okresov sa predalo najviac áut, všetky ich skratky vypíše spolu s početnosťou.

**a x** - tento príkaz treba zadať s celým číslom predstavujúcim posun v šifre.
      Zdvojí pole a za každú ŠPZ uloží cézarovou šifrou zašifrovanú skratku okresu a 5 medzier pre zachovanie štruktúri poľa. Príkaz s potom vypíše ŠPZ aj so šifrou. **POZOR**: po zadaní tohto príkazu ostatné príkazy berú do úvahy nový obsah poľa. Odporúčame príkazom n pole obnoviť, pred použitím iných príkazov.

**b** - vypíše histogram všetkých číslic v poli, ak sa číslica nevyskytuje nevypíše pre ňu riadok.

**k** - Ukončí program.

Vysvetlenie záznamu v súbore po riadkoch:

meno predávajúceho  
ŠPZ  
typ auta: booleovská hodnota (1 pre nové auto, 0 pre ojazdené auto)  
cena auta  
dátum nástupu do zamestnania, osemmiestne celé číslo v tvare rrrrmmdd. napr.20181030 (30.10.2018)  
(prázdny riadok)

Prikladám do repozitára ukážkový súbor autobazar.txt.

## Project 2
Full linked list implementation and excercise in C.