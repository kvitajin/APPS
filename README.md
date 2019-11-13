# APPS - Architektury počítačů a paralelních systémů 

## Cíle předmětu vyjádřené dosaženými dovednostmi a kompetencemi
Cílem předmětu je seznámit studenty se základním technickým vybavením počítačů a principem činnosti jejich jednotlivých částí. Vybrané principy jsou demonstrovány na mikropočítačích, osobních počítačích a GPU (dostupné architektury). 
Absolvováním kurzu získají studenti znalosti o základních komponentách počítače a pochopí obecné principy jejich fungování. Během praktické části kurzu si studenti osvojí schopnost vyvíjet programy pro mikropočítače, víceprocesorové počítače a programování GPU. Seznámí se také se základy programování v jazyce symbolických instrukcí. 
## Vyučovací metody

Přednášky</br>
Cvičení (v učebně)</br>
Experimentální práce v laboratoři</br>
## Anotace
Studenti v předmětu získají znalosti o základních komponentách počítače a pochopí obecné principy jejich fungování. 
## Povinná literatura:
[1] Olivka P.: Studijní materiály v elektronické verzi pro předmět APPS (česky), http://poli.cs.vsb.cz/edu/apps/osnova.html</br>
[2] Olivka P.: Programování ve jazyce symbolických instrukcí, elektronická verze studijních materiálů, http://poli.cs.vsb.cz/edu/soj</br>
[3] Olivka, P., Seidl, D.: Návody do cvičení, elektronická verze, http://poli.cs.vsb.cz/edu/apps/</br>
[3] Ličev L.: Architektury počítačů, 2010, Elektronický sborník přednášek k předmětu Architektury počítačů. </br>
[4] Patterson, D.: The Top 10 Innovations in the New NVIDIA Fermi Architecture, and the Top 3 Next Challenges. 2009.</br>
## Doporučená literatura:
[1] Hennessy J. L, Patterson D. A., Computer Architecture, 4th ed., A Quantitative Approach, Morgan Kaufmann, 2006, ISBN 978-0-12-370490-0</br>
[2] Hennessy J. L, Patterson D. A., Computer Architecture, 5th ed., A Quantitative Approach, Morgan Kaufmann, 2011, ISBN 978-0123838728</br>
[3] David Patterson, John Hennessy, Computer Organization and Design, 4th ed., Morgan Kaufmann, 2011, ISBN 9780080886138</br>
[4] David Patterson, John Hennessy, Computer Organization and Design MIPS Edition, 5th ed., Morgan Kaufmann, 2013, ISBN 978-0124077263</br>
## Forma způsobu ověření studijních výsledků a další požadavky na studenta
Během semestru studenti získávají body za úkoly ve cvičení.
## E-learning
## Další požadavky na studenta
Programování v jazyce C. 
## Prerekvizity
| Kód předmětu |	Zkratka	| Název |	Povinnost |
| ------------ | -------- | ----- | --------- |
|440-2102 |	LO | Logické obvody |	Doporučená
|460-2001 | ALG I |	Algoritmy I |	Doporučená
|460-2003 | ALG II |	Algoritmy II |	Doporučená
|460-2042 | PR I |	Programování I |	Doporučená
|460-2043 |PR II |	Programování II |	Doporučená
## Korekvizity

Předmět nemá žádné korekvizity.
## Osnova předmětu
Přednášky:
1. Technologie výroby číslicových obvodů. Architektura počítače dle von Neumanna, harvardská, základní vlastnosti a principy činnosti.
2. Strojová instrukce, adresování, adresní prostory. Měření výkonu počítačů.
3. Principy komunikace s perifériemi, V/V brány, programové řízení, přerušení, řešení priorit. Činnost DMA kanálu a kanálu (SCSI), rozdíly v činnosti.
4. Procesory CISC a RISC, základní rysy a podněty pro vznik, zřetězení, predikce skoků, hazardy, základní zástupci RISC.
5. Procesory Intel, vývojová řada, základní rysy a vnitřní architektura.
6. Procesory jiných firem, jejich vlastnosti a oblasti použití.
7. Monolitické počítače, požadavky na konstrukci, vlastnosti a použití, typické integrované periférie. Mikrokontrolery firmy Microchip a Atmel.
8. Organizace pamětí v počítačích, paměťová hierarchie. Vnitřní paměti statické, dynamické, organizace virtuální paměti. Paměti vnější - magnetické, optické, magneto-optické. Rozhraní IDE PATA/SATA.
9. Sběrnice, rozdělení signálů na adresní, datové a řídící. Cyklus sběrnice. Základní vlastnosti PCI, AGP a PCI Express technologie. USB.
10. Videoadaptéry a zobrazovací jednotky. Princip činnosti zobrazovací jednotky a tvorby obrazu.
11. Moderní trendy architektur počítačů. Architektury paralelních systémů a počítačů.
12. Pokročilé architektury počítačů GPU – CUDA. Historie výpočtů na grafických akcelerátorech
13. Paralelní architektury grafických procesorů (CUDA - Architektura Fermi).
14. Super počítače a počítačové clustery a High Performance Computing. 

Laboratorní cvičení:
1. Bezpečnostní školení, seznámení s vývojovým Kitem a programovacím prostředím, programování jednoduché aplikace. 
2. Princip pulzně šířkové modulace, ovládání LED, jednoduchá animace.
3. Pulzně šířková modulace,paralelní ovládání LED, skládání RGB barev, ovládání pomocí tlačítek. 
4. Ovládání LCD grafického displeje, skládání barev, zpracování bitmapového fontu. 
5. Ovládání LCD, zobrazení grafických i textových informací, jednoduchá aplikace ovládaná tlačítky. 
6. I2C sběrnice, ovládání expandéru a LED. 
7. I2C sběrnice, ovládání FM rádiového modulu, zobrazení RDS informací. 
8. Opakování témat programování mikropočítače. 
9. Vytváření vláken, rozložení algoritmu do více vláken. 
10. Programování základních algoritmů s využitím vláken, porovnání časové složitosti sekvenční a paralelní implementace. 
11. Technologie CUDA, základní koncepce programu, programování aplikace využívající vektory a matice. 
12. Technologie CUDA, zpracování digitálních obrázků, programování základních transformací. 
13. Technologie CUDA, vytváření jednoduchý animací. 
14. Opakování technologie CUDA a paralelního počítání. 

Projekt:
Projekt je tvořen samostatnou prací studentů mezi jednotlivými laboratorními úlohami. 

