ACTUALIZAREA TABELELOR - COMENZI LMD
 (Data Manipulation Language – Limbaj de Manipulare a Datelor)

Comanda	Scop

INSERT	Adauga o noua inregistrare in tabela
UPDATE	Modifica valorile unor inregistrari din tabele
DELETE	Sterge inregistrari din tabele
MERGE	Actualizeaza o tabela in functie de anumite conditii
SELECT	Regaseste inregistrari in tabele sau vederi (view). 


Dupa actualizarea datelor se va utiliza comanda SELECT * FROM nume_tabela; pentru a vizualiza rezultatele! 
ADAUGAREA INREGISTRARILOR – COMANDA INSERT
Inregistrarile se pot adauga in tabele in mai multe moduri:
-	precizand explicit in sintaxa comenzii valorile
-	cu ajutorul variabilelor de substitutie
-	pe baza valorilor din alte tabele
a) Precizarea explicita a valorilor introduse se realizeaza cu comanda:
INSERT INTO nume_tabela VALUES (lista de valori pentru fiecare coloana in ordinea in care sunt declarate coloanele in tabela);
Atentie! Trebuie precizate valori pentru toate coloanele tabelei.

Vezi scriptul pentru adaugarea inregistrarilor in tabelele utilizate ca exemplu. Descarcati de pe site scriptul de adaugare http://bd.ase.ro/uploads/bd_seminar_zi/ru_lmd.txt

O varianta a acestei comenzi este urmatoarea:
INSERT INTO nume_tabela (lista de coloane) VALUES (lista de valori pentru fiecare coloana);
Exemplu 1. Sa creeze tabela salariati pe baza tabelei angajati fara a prelua si inregistrarile (doar structura) si sa se adauge un nou angajat

CREATE TABLE salariati AS
SELECT * FROM angajati WHERE 1=2;
INSERT INTO salariati VALUES(1, ‘Ionel’, ‘Gheorghe’, ‘ig@gmail.com’, ‘0792344232’, TO_DATE(’19 Oct, 2023’, ‘dd mon, yyyy’), NULL, 5000, 0.2, NULL, NULL); 


b) Adaugarea inregistrarilor pe baza valorilor din alte tabele:
INSERT INTO nume_tabela SELECT */lista de coloane
FROM tabela_sursa 
[WHERE conditie];


Exemplul 2. Sa se adauge in tabela salariati toti angajatii din tabela angajati care lucreaza in departamentele 20, 30 si 50. Si sa se finalizeze tranzactia (salvarea modificarii).



INSERT INTO salariati SELECT * FROM angajati WHERE id_departament IN(20, 30, 50);
COMMIT; // daca 2 comenzi sunt plasate in acelasi timp, se asigura ca desi tabela este blocata si cea de a doua comanda este plasata. 

c) Utilizarea variabilelor de substitutie pentru adaugarea inregistrarilor pe baza valorilor introduse de utilizator de la tastatura:
INSERT INTO nume_tabela (col1,col2,col3) VALUES (‘&valoare_coloana1’, ‘&valoare_coloana2’, TO_DATE((‘&valoare_coloana3’, ‘DD/MM/YYYY’));

// INSERT INTO nume_tabela (lista coloane) VALUES (&valoare_coloana1, &valoare_coloana2,...);

Exemplul 3. Sa se adauge in tabela salariati un angajat ale carui date sunt introduse de utilizator de la tastatura


Atentie! Pentru data_angajare  se va utiliza functia de conversie TO_DATE.
Ex: TO_DATE('jan 20, 2005','mon dd, yyyy')
MODIFICAREA DATELOR – COMANDA UPDATE
Sintaxa comenzii este: 
UPDATE nume_tabela SET nume_coloana = valoare
[WHERE conditie]; 

Exemplul 4. Sa se creasca cu 100 salariul angajatilor din tabela salariati care au salariul mai mic decat 3000: 

UPDATE salariati SET salariul=salariul + 100
WHERE salariul < 3000;


Exemplul 5. Sa se actualizeze salariul angajatilor al caror manager are id = 122 cu salariul angajatului cu id = 125. 

UPDATE salariati SET salariul=(SELECT salariul FROM salariati WHERE id_angajat = 125) WHERE id_manager = 122;


Exemplul 6. Sa se actualizeze salariul si comisionul angajatilor din tabela salariati cu salariul si comisionul anagajatului cu id_angajat = 167 din tabela angajati, doar pentru angajatii care au salariul mai mic decat salariul angajatului cu id = 173 din tabela angajati si care lucreaza in departamentul 50. 
STERGEREA DATELOR – COMANDA DELETE
Sintaxa comenzii este: 
DELETE FROM nume_tabela
WHERE conditie; 


UPDATE salariati SET salariul=(SELECT salariul FROM salariati WHERE id_angajati = 167), comision = (SELECT comision FROM salariati WHERE id_angajati = 167)
FROM
WHERE 
Exemplul 7. Sa se stearga angajatii din tabela salariati care au id_manager egal cu 122 sau 123.

Exemplul 8. Sa se sterga angajatii din tabela salariati angajati inainte de anul 1999. 


Exemplul 9. Sa se sterga toti angajatii din tabela salariati. Sa se anuleze tranzactia.
;

ACTUALIZAREA DATELOR CU COMANDA MERGE

Sintaxa comenzii este: 
MERGE INTO nume_tabela USING nume_tabela_sursa
ON (conditia_de_legatura)
WHEN MATCHED THEN
UPDATE SET nume_coloana=valoare
WHEN NOT MATCHED THEN
INSERT VALUES (lista_valori);

Exemplul 10. Sa se actualizeze tabela salariati astfel incat toti salariatii din tabela salariati sa aiba salariile egale cu cei din tabela angajati, iar pentru cei care nu sunt in tabela salariati sa se adauge valorile coloanelor (id_angajat, nume, salariul) din tabela sursa agajati. Sa se numere inregistrarile din cele doua tabele si sa se explice diferenta. Sa se finalizeze tranzactia.

MERGE INTO salariati USING angajati 
ON (salariati.id_angajat = angajati.id_angajat)
WHEN MATCHED THEN 
UPDATE SET salariati.salariul=angajati.salariul
WHEN NOT MATCHED THEN
INSERT  (id_angajat, nume, salariul) VALUES (angajati.id_angajat, angajati.nume, angajati.salariul);
SELECT COUNT (*) FROM salariati;
SELECT COUNT (*) FROM angajati;
COMMIT;


Seminar 4

ACTUALIZAREA TABELELOR - COMENZI LMD
 (Data Manipulation Language – Limbaj de Manipulare a Datelor)
Comanda	Scop
INSERT	Adauga o noua inregistrare in tabela
UPDATE	Modifica valorile unor inregistrari din tabele
DELETE	Sterge inregistrari din tabele
MERGE	Actualizeaza o tabela in functie de anumite conditii
SELECT	Regaseste inregistrari in tabele sau vederi (view). 
Dupa actualizarea datelor se va utiliza comanda SELECT * FROM nume_tabela; pentru a vizualiza rezultatele! 
ADAUGAREA INREGISTRARILOR – COMANDA INSERT
Inregistrarile se pot adauga in tabele in mai multe moduri:
-	precizand explicit in sintaxa comenzii valorile
-	cu ajutorul variabilelor de substitutie
-	pe baza valorilor din alte tabele
a) Precizarea explicita a valorilor introduse se realizeaza cu comanda:
INSERT INTO nume_tabela VALUES (lista de valori pentru fiecare coloana in ordinea in care sunt declarate coloanele in tabela);
Atentie! Trebuie precizate valori pentru toate coloanele tabelei.

Vezi scriptul pentru adaugarea inregistrarilor in tabelele utilizate ca exemplu. Descarcati de pe site scriptul de adaugare http://bd.ase.ro/uploads/bd_seminar_zi/ru_lmd.txt

O varianta a acestei comenzi este urmatoarea:
INSERT INTO nume_tabela (lista de coloane) VALUES (lista de valori pentru fiecare coloana);
Exemplu 1. Sa creeze tabela salariati pe baza tabelei angajati fara a prelua si inregistrarile (doar structura) si sa se adauge un nou angajat

CREATE TABLE salariati AS
SELECT * FROM angajati WHERE 1=2;
INSERT INTO salariati VALUES(1, ‘Ionel’, ‘Gheorghe’, ‘ig@gmail.com’, ‘0792344232’, TO_DATE(’19 Oct, 2023’, ‘dd mon, yyyy’), NULL, 5000, 0.2, NULL, NULL); 


b) Adaugarea inregistrarilor pe baza valorilor din alte tabele:
INSERT INTO nume_tabela SELECT */lista de coloane
FROM tabela_sursa 
[WHERE conditie];


Exemplul 2. Sa se adauge in tabela salariati toti angajatii din tabela angajati care lucreaza in departamentele 20, 30 si 50. Si sa se finalizeze tranzactia (salvarea modificarii).



INSERT INTO salariati SELECT * FROM angajati WHERE id_departament IN(20, 30, 50);
COMMIT; // daca 2 comenzi sunt plasate in acelasi timp, se asigura ca desi tabela este blocata si cea de a doua comanda este plasata. 

c) Utilizarea variabilelor de substitutie pentru adaugarea inregistrarilor pe baza valorilor introduse de utilizator de la tastatura:
INSERT INTO nume_tabela (col1,col2,col3) VALUES (‘&valoare_coloana1’, ‘&valoare_coloana2’, TO_DATE((‘&valoare_coloana3’, ‘DD/MM/YYYY’));

// INSERT INTO nume_tabela (lista coloane) VALUES (&valoare_coloana1, &valoare_coloana2,...);

Exemplul 3. Sa se adauge in tabela salariati un angajat ale carui date sunt introduse de utilizator de la tastatura


Atentie! Pentru data_angajare  se va utiliza functia de conversie TO_DATE.
Ex: TO_DATE('jan 20, 2005','mon dd, yyyy')
MODIFICAREA DATELOR – COMANDA UPDATE
Sintaxa comenzii este: 
UPDATE nume_tabela SET nume_coloana = valoare
[WHERE conditie]; 

Exemplul 4. Sa se creasca cu 100 salariul angajatilor din tabela salariati care au salariul mai mic decat 3000: 

UPDATE salariati SET salariul=salariul + 100
WHERE salariul < 3000;


Exemplul 5. Sa se actualizeze salariul angajatilor al caror manager are id = 122 cu salariul angajatului cu id = 125. 

UPDATE salariati SET salariul=(SELECT salariul FROM salariati WHERE id_angajat = 125) WHERE id_manager = 122;


Exemplul 6. Sa se actualizeze salariul si comisionul angajatilor din tabela salariati cu salariul si comisionul anagajatului cu id_angajat = 167 din tabela angajati, doar pentru angajatii care au salariul mai mic decat salariul angajatului cu id = 173 din tabela angajati si care lucreaza in departamentul 50. 
STERGEREA DATELOR – COMANDA DELETE
Sintaxa comenzii este: 
DELETE FROM nume_tabela
WHERE conditie; 


UPDATE salariati SET salariul=(SELECT salariul FROM salariati WHERE id_angajati = 167), comision = (SELECT comision FROM salariati WHERE id_angajati = 167)
FROM
WHERE 
Exemplul 7. Sa se stearga angajatii din tabela salariati care au id_manager egal cu 122 sau 123.
DELETE FROM salariati WHERE id_manager=122 OR id_manager=123;

Exemplul 8. Sa se sterga angajatii din tabela salariati angajati inainte de anul 1999. 

DELETE FROM salariati WHERE data_angajare <TO_DATE(’01.01.1999’, ‘dd.mm.yyyy’);
Exemplul 9. Sa se sterga toti angajatii din tabela salariati. Sa se anuleze tranzactia.
;
DELETE FROM salariati
Rollback;
ACTUALIZAREA DATELOR CU COMANDA MERGE

Sintaxa comenzii este: 
MERGE INTO nume_tabela USING nume_tabela_sursa
ON (conditia_de_legatura)
WHEN MATCHED THEN
UPDATE SET nume_coloana=valoare
WHEN NOT MATCHED THEN
INSERT VALUES (lista_valori);

Exemplul 10. Sa se actualizeze tabela salariati astfel incat toti salariatii din tabela salariati sa aiba salariile egale cu cei din tabela angajati, iar pentru cei care nu sunt in tabela salariati sa se adauge valorile coloanelor (id_angajat, nume, salariul) din tabela sursa agajati. Sa se numere inregistrarile din cele doua tabele si sa se explice diferenta. Sa se finalizeze tranzactia.

MERGE INTO salariati USING angajati
//salariati= tabela in care vrem sa avem datele, angajati = tabela de unde vrem sa preluam date
ON (salariati.id_angajat = angajati.id_angajat)	//on = conditia de legatura
WHEN MATCHED THEN //ce se intampla daca gaseste egalitate
UPDATE SET salariati.salariul=angajati.salariul	//pun alias-uri pentru a face diferentierea dintre coloane. Updateaza coloanele din tabela salariati pe baza datelor din coloana sursa
WHEN NOT MATCHED THEN
INSERT  (id_angajat, nume, salariul) VALUES (angajati.id_angajat, angajati.nume, angajati.salariul);
SELECT COUNT (*) FROM salariati;
SELECT COUNT (*) FROM angajati;
COMMIT;



Seminar 5


INTEROGAREA TABELELOR

Instructiunea SELECT  realizeza regasirea datelor din tabele pe baza cererilor de interogare
SELECT	[DISTINCT] (*/coloana1 [alias], expresii [alias])
FROM	tabela1, tabela2, ...
WHERE     (conditii, precizarea legaturilor dintre tabele)
GROUP BY nume_tabela.nume_coloana
HAVING  (conditii impuse valorilor de grup)
ORDER BY nume_tabela.nume_coloana ASC/DESC;

UNDE:
SELECT		specifică atributele selectate;
DISTINCT		suprimă valorile duplicate;
*			selectează toate atributele;
coloana	selectează o anumită coloana sau mai multe coloana dintr-una sau mai multe tabele;
expresie		permite construirea de expresii avand ca rezultat valori noi
alias			denumiri pentru coloanele selectate;
FROM tabele		specifică tabelele ce conţin coloanele selectate;
WHERE	clauza permite specificarea conditiilor si a criteriilor de selectie a datelor;
GROUP BY	se precizeaza campul dupa care vor fi grupate datele in cazul expresiilor si functiilor de grup (SUM(), AVG(), COUNT(), MIN(), MAX());
HAVING	in cazul functiilor de grup conditiile impuse acestora se precizeaza in clauza HAVING;
ORDER BY	precizeaza ordonarea in functie un anumite campuri ascendent (ASC) – implicit sau descendent (DESC). Numai ORDER BY permite utilizarea aliasului;
Comenzile SQL:
-	Nu sunt case sensitive, de regula comezile se scriu cu litere mari pentru a se distinge mai usor;
-	Pot fi scrise pe mai multe linii;
-	Cuvintele cheie nu pot fi prescurtate sau scrise pe mai multe linii;
 In construirea comenzilor SQL se utilizeaza urmatorii operatori:
<, >, =, >=, <=, NOT	operatori de comparatie
BETWEEN val_min AND val_max	între două valori (inclusiv).
SELECT id_angajat, nume, salariul, id_departament FROM salariati WHERE salariul BETWEEN 2000 AND 6100 AND id_departament NOT IN (20, 30);
SELECT id_angajat, nume, salariul, id_departament FROM salariati WHERE salariul >= 2000 AND salariul <=6100 AND id_departament = 50;
IN (listă valori)	egal cu oricare valoare din lista de valori
SELECT id_angajat, nume, id_manager FROM salariati WHERE id_manager IN (120, 122, 123);
LIKE	similar cu un şablon
% oricâte caractere;  _  un caracter;
SELECT id_angajat, nume, id_functie FROM salariati WHERE nume LIKE 'B% ';
SELECT id_angajat, nume, id_functie FROM salariati WHERE nume LIKE '__t%';
IS NULL	are valoarea NULL 
SELECT id_angajat, nume, comision FROM salariati WHERE comision IS NULL;
Coloanele se specifică în ordinea în care se doresc a fi afişate, nu obligatoriu în ordinea în care apar în descrierea tabelelor.
Valoarea NULL, ca şi în alte limbaje, semnifică valoare ne-disponibilă, ne-alocată, şi nu este acelaşi lucru cu „blank” sau „zero”.
Cu ajutorul comenzii select se pot extrage informaţii din baza de date.  Comanda SELECT permite imprementarea operatorilor algebrei relationale: 
Selecţia:	Permite obţinerea unei noi relaţii care conţine toate atributele relaţiei iniţiale şi un număr redus de tupluri. Reducerea se face după o condiţie numită condiţie de selecţie.
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 

Proiecţia:	Permite obţinerea unei noi relaţii care conţine un număr redus de atribute faţă de relaţia iniţială şi toate valorile sau combinaţiile distincte de valori ale acestor atribute. 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 
 	 	 	 	 

Joncţiunea:	Operator binar, caz particular fiind produsul cartezian. Relaţia rezultat va conţine tuplurile corespunzătore atributelor de jonctiune care se află într-o anumită relaţie. Cel mai utilizat caz de joncţiune este acela în care atributele de jonctiune sunt cheie primară într-o relaţie si cheie externă in cealalta relatie.
 	 	 	 	 	 	 	 	 	 	 
 	 	 	 	 	 	 	 	 	 	 
 	 	 	 	 	 	 	 	 	 	 
 	 	 	 	 	 	 	 	 	 	 
 	 	 	 	 	 	 	 	 	 	 
 	 	 	 	 	 	 	 	 	 	 
 	 	 	 	 	 	 	 	 	 	 
 	 	 	 	 	 	 	 	 	 	 
 	 	 	 	 	 	 	 	 	 	 

Exemple:

1.	Sa se selecteze toti angajatii din tabela salariati.

SELECT * FROM salariati

2.	Sa se selecteze coloanele id_angajat, nume, prenume si id_functie din tabela salariati.

SELECT s.id_angajat, s.nume, s.prenume, s.id_functie FROM salariati s
3.	Sa se selecteze numai angajatii care fac parte din categoria functionar (al caror id_functie contine „CLERK”).

SELECT * FROM angajati WHERE (id_functie=’CLERK’)
4.	Sa se selecteze comenzile incheiate de salariatul cu id_angajat = 161.
SELECT * FROM comenzi WHERE (id_angajat=161)

5.	Sa se selecteze toate comezile care au fost lansate online dupa 1 ianuarie 2000.

SELECT * FROM comenzi
WHERE LOWER(modalitate) LIKE '%online%' 
AND data > TO_DATE('01.01.2000','DD.MM.YYYY');

6.	Sa se selecteze id_angajat, nume, prenume, id_manager, id_departament din tabela angajati si denumire_departament din tabela departamente si sa se realizeze jonctiunea dintre cele doua tabele.

SELECT a.id_angajat, a.nume, a.prenume, a.id_manager, a.id_departament, d.denumire_departament 
FROM angajati a, departamente d
WHERE a.id_departament=d.id_departament;
 
Operatorul ANY si operatorul ALL    
ANY Comapara valoarea cu oricare valoare returnata de interogare
ALL compara valoarea cu fiecare valoare returnata de interogare 
<ANY() - less than maximum
>ANY() - more than minimum
=ANY() - equivalent to IN
>ALL() - more than the maximum
<ALL() - less than the minimum

7.	Să se afişeze id_angajat, prenume, id_functie si salariul pentru angajatii care nu lucreaza in departamentul IT_PROG si al caror salariu este mai mic decat oricare dintre salariile angajatilor care lucreaza in departamentul IT_PROG:
SELECT id_angajat, prenume, id_functie, salariul
FROM angajati
WHERE salariul < ANY
 (SELECT salariul FROM angajati
WHERE id_functie = 'IT_PROG') 
AND id_functie <> 'IT_PROG'
ORDER BY salariul DESC; 	 
 
 
8.	Să se afişeze id_angajat, prenume, id_functie si salariul pentru angajatii care nu lucreaza in departamentul IT_PROG si al caror salariu este mai mic decat fiecare dintre salariile angajatilor care lucreaza in departamentul IT_PROG:
SELECT id_angajat, prenume, id_functie, salariul
FROM angajati
WHERE salariul < ALL
 (SELECT salariul FROM angajati
WHERE id_functie = 'IT_PROG') 
AND id_functie <> 'IT_PROG'
ORDER BY salariul DESC; 	 
 
 
Realizarea jonctiunilor între relaţii. Tipuri de jonctiuni

a. Jonctiune de egalitate

9.	Sa se selecteze comenzile incheiate de angajati  (in clauza WHERE se va preciza conditia de legatura dintre tabele).

SELECT c.data, a.nume FROM comenzi c, angajati a WHERE c.id_angajat= a.id_angajat; 

//SELECT c.data, a.angajati FROM comenzi, angajati

10.	Sa se selecteze comenzile incheiate de angajatul Greene numai in luna noiembrie.
SELECT comenzi FROM angajati WHERE (angajati.nume=’Greene’)

SELECT c.data, a.nume FROM comenzi c, angajati a WHERE c.id_angajat= a.id_angajat AND upper(a.nume)=’GREENE’ AND upper(c.data) LIKE ’%NOV%’



11.	Sa se calculeze valoarea fiecarui produs (valoare = cantitate * pret) si sa se afiseze denumirea produsului, pretul, cantitatea si valoarea.

Many to many => exista o tabela intermediara numita rand_comenzi txt document

SELECT p.denumire_produs, rc.pret, rc.cantitate, rc.pret*rc.cantitate AS valoare FROM produse p, rand_comenzi rc WHERE p.id_produs = rc.id_produs;

Sa se selecteze numai produsele cu valoarea cuprinsa intre 1000 si 2000.
AND rc.pret*rc.cantitate BETWEEN 1000 AND 2000  
//sau valoare
b. Jonctiune externa

12.	Să se afişeze id-ul produsului, denumirea produsului şi cantitatea chiar daca nu au fost comandate 
 SELECT p.id, p.denumire_produs, r.pret, r.cantitate FROM produse p, rand_comenzi r WHERE p.id_produs=r.id_produs(+); 

c. Jonctiunea dintre o tabelă cu aceeaşi tabelă 

13.	Să se afişeze numele fiecarui angajat şi numele sefului direct superior: 
SELECT a.nume||' lucreaza pentru: '||m.nume  
FROM angajati a, angajati m
WHERE a.id_manager=m.id_angajat;
Realizarea interogarilor subordonate (se utilizeaza 2 comenzi SELECT imbricate)

14.	Sa se selecteze angajatii care sunt in acelasi departament cu angajatul Smith.
 
SELECT * FROM angajati
WHERE id_departament = 
(SELECT id_departament FROM angajati WHERE upper(nume)= 'SMITH');
Eroare "single-row subquery returns more than one row"

SELECT nume, prenume, id_angajat, id_departament FROM angajati WHERE nume = 'Smith';
 

SELECT * FROM angajati
WHERE id_departament IN 
(SELECT id_departament FROM angajati WHERE upper(nume)= 'SMITH');

15.	Să se afişeze produsele care au preţul unitar cel mai mic:

Clauza FOR UPDATE - blocheaza randurile selectate de o interogare in vederea actualizarii ulterioare, ceilalti utilizatori nu pot modifica acele randuri pana la finalizarea tranzactiei;
FOR UPDATE nu se foloseste cu: 
•	DISTINCT 
•	GROUP BY  
•	Functii de grup

SELECT a.id_angajat, a.id_functie, c.nr_comanda
FROM angajati a, comenzi c 
WHERE a.id_angajat = c.id_angajat
FOR UPDATE;	//cand avem actualizari ulterioare


Seminar 6

UTILIZAREA FUNCTIILOR PREDEFINITE IN INTEROGARI  
•	Funcţii de tip single-row (sau scalare). O funcţie single-row întoarce un singur rezultat pentru fiecare rând al tabelei interogate sau view 
•	Funcţii de grup (sau agregate). O funcţie de grup întoarce un singur rezultat pentru un grup de rânduri interogate. Funcţiile de grup pot apare în clauza HAVING. 


FUNCTII SINGLE-ROW

Funcţii de tip caracter  Functia LOWER() , UPPER(), INITCAP()

1.	Sa se afiseze cu litere mari denumirea departamentelor din locatia 1700:
SELECT UPPER (denumire_departament) FROM departamente WHERE id_locatie=1700;

2.	Sa se afiseze salariatii al caror nume incepe cu litera s

SELECT * FROM angajati WHERE LOWER (nume) LIKE 's%';

3.	Sa se afiseze toti angajatii cu numele Smith utilizand functiile INITCAP, UPPER, LOWER

SELECT * FROM angajati WHERE INITCAP(nume)='Smith';
Si a se pune UPPER, LOWER
Operatorul de concatenare (||)

4.	Să se afişeze denumirea produsului şi stocul disponibil

SELECT 'Produsul: ' || INITCAP(denumire_produs) || ' are pretul_minim ' || pret_min produs_pret_minim
FROM produse;


Funcţia CONCAT() , funcţia LENGTH() , funcţia SUBSTR()

5.	Să se afişeze id_client, numele clientilor concatenată cu sexul acestora şi lungimea prenumelui, nivel_venituri numai pentru clientii cu venituri in categoria F: 110000 - 129999
SELECT id_client, CONCAT(nume_client,sex), LENGTH(prenume_client), nivel_venituri FROM clienti 
WHERE SUBSTR(nivel_venituri,1,1)='F';
INSTR(), LPAD(), RPAD(), REPLACE(), REVERSE()
Funcţii de tip numeric  Funcţia ROUND(), TRUNC()

6.	Să se afişeze numărul 45,923 rotunjit la două zecimale si rotunjit la numar intreg.
Sa se aplice si functia TRUNC.
 SELECT ROUND(45.923,2), ROUND(45.923,0) FROM DUAL;
SELECT TRUNC(45.923,2), TRUNC(45.923,0) FROM DUAL;

SIGN(), POWER(), MOD(), SQRT(),CORR(),STDDEV()
Funcţii de tip dată calendaristică  Funcţia SYSDATE 
7.	Să se afişeze perioada de timp corespunzătoare (în săptămâni) între data încheierii comenzii şi data curentă:   SELECT nr_comanda, (SYSDATE-data)/7 saptamani
FROM comenzi;

8.	Afisati data curenta (se selecteaza data din tabela DUAL):



Funcţiile MONTHS_BETWEEN() , ADD_MONTHS() , NEXT_DAY() , LAST_DAY() 
9.	Să se afişeze comenzile, data încheierii comenzilor, numărul de luni între data curentă şi data încheierii, următoarea zi de vineri după data încheierii, ultima zi din luna din care face parte data încheierii, precum şi data corespunzătoare după 2 luni de la data încheierii comenzii  SELECT nr_comanda, data, round(MONTHS_BETWEEN(sysdate, data)) luni, NEXT_DAY(data, 'FRIDAY'), 
LAST_DAY(data)
ADD_MONTHS(data,2),
FROM comenzi; 
10.	Să se afişeze comenzile incheiate in luna trecuta:

;

Funcţia ROUND(), TRUNC()

11.	Să se afişeze comenzile incheiate in 2000. Se va rotunji data încheierii la prima zi din luna corespunzătoare dacă data încheierii este în prima jumatate a lunii sau la prima zi din luna următoare:  SELECT nr_comanda, data, ROUND(data, 'MONTH') FROM comenzi
WHERE data LIKE '%-00%'; 
 Funcţii de conversie

 

Funcţia TO_CHAR 
12.	Să se afişeze comenzile si data încheierii in formatul initial si in format “MM/YY”  SELECT nr_comanda, data, TO_CHAR(data, 'MM/YY') data_incheierii_comenzii FROM comenzi;

Funcţia TO_DATE 
13.	Să se afişeze comenzile incheiate intre 15 ianuarie si 15 decembrie 1999. 

Funcţia TO_NUMBER - Converteste sirul de caractere intr-un numar cu un anumit format
TO_NUMBER(char[, 'format_model'])
SELECT TO_NUMBER('RON12.345,64', 'L99G999D99') FROM DUAL;
   ALTER SESSION SET NLS_CURRENCY = 'RON';
   CREATE TABLE test(NUMAR VARCHAR2(50));
   INSERT INTO test SELECT salariul FROM angajati;
   UPDATE test
   SET numar = 'RON'||numar;
   SELECT * FROM test;
   SELECT TO_NUMBER(numar,'L99999') FROM test;

Funcţia EXTRACT() 
14.	Sa se afiseze comenzile incheiate in anii 1997 si 1998.

SELECT nr_comanda, data  FROM comenzi
	WHERE EXTRACT(YEAR FROM data) IN (1997, 1998);

15.	Sa se afiseze comenzile incheiate in lunile iulie si august.

SELECT nr_comanda, data  FROM comenzi
	WHERE EXTRACT(MONTH FROM data) IN (7,8);

Functiile NVL, NVL2, NULLIF, COALESCE
NVL
NVL(comision,0)
NVL(data_angajarii,'01-JAN-97')
NVL(id_functia,'Nu_exista_functia')

16.	Sa se calculeze veniturile anuale ale angajatilor

SELECT (salariul+NVL(comision, 0)*salariul)*12 AS venit_anual FROM angajati;
NVL2
17.	Sa se afiseze angajatii care au comision (1) si pe cei care nu au comision (0).
SELECT NVL2(comision, 1, 0) AS val_comision FROM  angajati;

NULLIF
18.	Sa se afiseze lungimea numelui, lungimea prenumelui, daca acestea sunt egale sa se returneze nul ca rezultat, iar daca nu sunt egale se va returna lungimea numelui.
SELECT LENGTH(nume), LENGTH(prenume), NULLIF(LENGTH(nume), LENGTH(prenume)) FROM angajati;

COALESCE
19.	Sa se afiseze id-ul managerului fircarui angajat, daca acesta este nul, se va afisa comisionul, iar daca si acesta este nul se va afisa -1.

SELECT COALESCE(id_manager, comision, -1) FROM angajati;

FUNCŢII DE GRUP

AVG([DISTINCT|ALL] n) – calculeaza media aritmetica a valorilor
COUNT(* | [DISTINCT|ALL] expr) – intoarce numarul total al valorilor
MAX([DISTINCT|ALL] expr) – intoarce valoarea maxima MIN([DISTINCT|ALL] expr) – intoarce valoarea minima
SUM([DISTINCT|ALL] n) – calculeaza suma valorilor

Se utilizeaza urmatoarele clauze:
GROUP BY – grupeaza datele in functie de un anumit camp;
ORDER BY – ordoneaza datele in functie de un anumit camp;
HAVING – permite stabilirea unor criterii de selectie asupra functiilor de grup;

Exemple:
1.	Să se afişeze valoarea maximă, valoarea medie, valoarea minimă şi valoarea totală a produselor comandate:

SELECT AVG(rc.cantitate  *  rc.pret), MAX(rc.cantitate  *  rc.pret), MIN(rc.cantitate  *  rc.pret), sum(rc.cantitate  *  rc.pret) 
FROM rand_comenzi rc;

2.	Să se afişeze data primei comenzi încheiate şi data celei mai vechi comenzi încheiate:

SELECT MIN(data), MAX(data) FROM comenzi;

3.	Să se afişeze numărul de produse al căror pret_min>350:

SELECT COUNT(*) nr_produse 
FROM produse 
WHERE pret_min>350;

4.	Sa se afiseze numarul de salarii (distincte) din tabela angajati.
SELECT COUNT(DISTINCT) 

SELECT COUNT(DISTINCT salariul) AS numar_salarii FROM angajati;
5.	Să se afişeze numărul total de comenzi incheiate:

SELECT COUNT(*) 

SELECT COUNT(*) id_produs FROM comenzi;

6.	Să se afişeze pe cate comenzi apare produsul cu codul 3124:

SELECT COUNT(id_comanda) FROM rand_comenzi WHERE id_produs=3124;

7.	Să se afişeze cantitatea medie vândută din fiecare produs. Sa se ordoneze după cantitate (se utilizeaza functia AVG() si clauza GROUP BY pentru gruparea datelor in functie de id_ul produsului, iar ordonarea se realizeaza cu ajutorul functiei ORDER BY).

SELECT id_produs, ROUND(AVG(cantitate),2) medie_produse 
FROM rand_comenzi
GROUP BY id_produs
ORDER BY medie_produse;

8.	Să se afişeze produsele şi cantitatea medie vândută numei pentru acele produse a căror cantitate medie este mai mare de 25 (conditia se specifica in clauza HAVING si nu in clauza WHERE deoarece este utilizata functia de grup AVG si conditia este AVG(cantitate)>25).
SELECT id_produs, ROUND(AVG(cantitate), 2) AS medie_produse FROM rand_comenzi
GROUP BY id_produs HAVING AVG(cantitate)>25
ORDER BY medie_produse;


9.	Sa se calculeze valoarea totala a fiecarei comenzi si sa se sorteze descrescator in functie de valoare:


10.	Sa se afiseze numai comenzile care au valoarea cuprinsa intre 1000 si 3000 (conditia va fi mentionata in clauza HAVING deoarece se utilizeaza functia de grup SUM):

SELECT comenzi.nr_comanda, SUM(rand_comenzi.cantitate  *  rand_comenzi.pret) total_comanda
FROM comenzi, rand_comenzi
WHERE rand_comenzi.nr_comanda=comenzi.nr_comanda
GROUP BY comenzi.nr_comanda
HAVING SUM(rand_comenzi.cantitate  *  rand_comenzi.pret)  BETWEEN 1000 AND 3000  
ORDER BY total_comanda DESC;


Seminar 7


Exercitii:
1.	Sa se selecteze din tabela angajaţi numai angajatii care au salariul cuprins intre 8000 si 10000.

SELECT * FROM angajati
WHERE salariul BETWEEN 8000 AND 10000;

2.	Sa se selecteze din tabela angajati numai angajatii care au functia SA_REP.  

SELECT * FROM angajati
WHERE id_functie = 'SA_REP';

3.	Sa se selecteze angajatii care sunt in acelasi departament cu angajatul Smith.

	SELECT prenume, nume, id_departament FROM angajati WHERE id_departament 	IN (SELECT id_departament FROM angajati WHERE nume = 'Smith');

4.	Să se afişeze produsele care au preţul unitar cel mai mic.

	SELECT * FROM produse
	WHERE pret_lista = (SELECT MIN(pret_lista)FROM produse);

5.	Modificati conditia de sus astfel incat sa fie selectati si cei care au in denumirea functiei atributul ACCOUNT. 

	SELECT * FROM produse
	WHERE pret_lista = (SELECT MIN(pret_lista) FROM produse)
	OR id_produs IN (SELECT id_produs FROM functii WHERE denumire_functie 	LIKE '%ACCOUNT%');

6.	Sa se selecteze toti angajatii pentru care a doua litera din e-mail este A, B sau C.

	SELECT * FROM angajati
	WHERE SUBSTR(email, 2, 1) IN ('A', 'B', 'C');

7.	Sa se selecteze toti angajatii care au numarul de telefon format din al doilea grup de cifre din 123 (de exemplu: 515.123.4569)

	SELECT * FROM angajati
	WHERE SUBSTR(telefon, 5, 3) = '123';

8.	Sa se selecteze toti angajatii angajati inainte de 1 ianuarie 2000 (data_angajare). 

	SELECT * FROM angajati WHERE data_angajare < TO_DATE('01.01.2000', 	'DD.MM.YYYY');

	/*sau*/
	SELECT *
	FROM angajati
	WHERE data_angajare < TO_DATE('2000-01-01', 'YYYY-MM-DD');

9.	Modificati conditia de mai sus astfel incat sa afisati numai salariatii angajati in ianuarie 2000.

	SELECT* FROM salariati WHERE EXTRACT(MONTH FROM data_angajare)=1 	AND EXTRACT (YEAR FROM data_angajare)=2000;

10.	Sa se selecteze numele, salariul, denumirea functiei angajatilor şi denumirea departamentului pentru cei care lucreaza în departamentul IT. 

	SELECT a.nume, a.salariul, a.id_functie, d.denumire_departament FROM angajati a, 	departamente d WHERE d.denumire_departament='IT';

11.	Modificati conditia de mai sus astfel incat sa fie selectati toti angajatii din departamentele care au in denumire specificatia IT, indiferent daca acestea au sau nu angajati.

	SELECT a.nume, a.id_functie, d.denumire_departament FROM angajati a, 	departamente d WHERE d.denumire_departament LIKE '%IT%';

12.	Sa se afiseze toate comenzile, iar pentru comenzile directe sa se afiseze numele angajatilor care le-au intermediat.

	SELECT a.nume, c.id_comanda, c.data, c.id_client, c.stare_comanda, c.id_angajat, 	c.modalitate FROM comenzi c, angajati a WHERE c.modalitate='direct';
	SELECT id_comanda FROM comenzi;

13.	Sa se afiseze toate produsele indiferent daca acestea au fost comandate sau nu.  

	SELECT p.denumire_produs, rc.id_produs, c.stare_comanda FROM produse p, 	rand_comenzi rc, comenzi c WHERE c.stare_comanda =1 OR c.stare_comanda=0;

14.	Afisati numele si in ordine crescatoare salariile si in ordine descrescatoare data angajarii pentru salariatii din departamentul vânzări (Sales).

	SELECT nume, salariul, data_angajare
	FROM angajati
	WHERE id_departament = (SELECT id_departament from departamente WHERE 	denumire_departament = 'Sales')
	ORDER BY salariul ASC, data_angajare DESC;

15.	Sa se selecteze numele, functia, comisionul si departamentul angajatilor care nu au comisionul NULL.

	SELECT nume, id_functie, comision, denumire_departament
	FROM angajati a
	JOIN departamente d ON a.id_departament = d.id_departament
	WHERE comision IS NOT NULL;

Pentru grupele care au facut structurile ierarhice:

16.	  Sa se afiseze numele, denumirea departamentului unde lucreaza si nivelul ierarhic pentru toti angajatii care au subordonati si care au aceeasi functie ca angajatul Russell.

	SELECT a.nume, a.id_functie, LEVEL, d.denumire_departament, 	SYS_CONNECT_BY_PATH(a.nume, '\')
	from angajati a, departamente d
	WHERE a.id_departament=a.id_departament
	AND a.id_functie=(SELECT id_functie FROM angajati WHERE 	INITCAP(nume)='Russell')
	AND LEVEL=2
	CONNECT BY PRIOR a.id_angajat=  a.id_manager
	ORDER BY LEVEL DESC;

17.	Sa se afiseze numele angajatilor care nu au subalterni si care au aceeasi functie ca angajatul Rogers, nivelul ierarhic si denumirea departamentului unde acestia lucreaza.

	SELECT a.nume, a.id_functie, LEVEL, d.denumire_departament, 	SYS_CONNECT_BY_PATH(a.nume, '\')
	FROM angajati a, departamente d
	WHERE a.id_departament=a.id_departament
	AND a.id_functie=(SELECT id_functie FROM angajati
	WHERE  INITCAP(nume)='Rogers')
	CONNECT BY PRIOR a.id_angajat=  a.id_manager
	ORDER BY LEVEL DESC;


Seminar 8

BAZE DE DATE – SEMINAR 8
___________________________________________________________________________
PARCURGEREA STRUCTURILOR IERARHICE
1. Moduri de parcurgere a structurilor arborescente:
● TOP-DOWN – se construieste setul de inregistrari copil incepand cu inregistrarea
radacina
● BOTTOM-UP – se construieste setul de inregistrari parinte pana la inregistrarea
radacina pentru un anumit nivel din ierarhie
● DIRECT PE UN ANUMIT NIVEL – se construieste setul de inregistrari incepand
cu un anumit nivel din ierarhi
2. Comenzi utilizate
Daca o tabela contine date arborescente, se pot selecta tuplurile intr-o ordine ierarhica prin
utilizarea unor clauze suplimentare in comanda SELECT:
SELECT [DISTINCT]
[LEVEL] ,
[SYS_CONNECT_BY_PATH(camp, '/')],
[CONNECT_BY_ROOT],
[CONNECT_BY_ISCYCLE],
[CONNECT_BY_ISLEAF], lista_coloane
FROM nume_tabela
WHERE conditii
CONNECT BY [NOCYCLE] [PRIOR] coloana_inregistrarii_copil=[PRIOR]
coloana_inregistrarii_parinte
START WITH coloana_radacina;
unde:
START WITH - specifica inregistrarile radacina pentru ierarhiile construite. Daca se omite
Oracle foloseste toate inregistrarile din tabela ca inregistrari radacina.
CONNECT BY - specifica relatia intre coloana inregistrarii parinte si coloana inregistrarii
copil ale ierarhiei.
PRIOR – se refera la inregistrarea parcursa anterior. Locul operatorului in conditia de legatura
parinte-copil determina modul de parcurgere al arborelui (top-down sau bottom-up).
LEVEL – se utilizeaza pentru a afisa nivelul inregistrarii parcurse.
Observatii:
1. Nu se recomanda utilizarea clauzei GROUP BY deoarece se pot produce schimbari in setul
returnat de cererea ierarhica.
2. O cerere ierarhica nu se foloseste intr-o jonctiune si nu poate selecta date dintr-o tabela
virtuala.
3. Procesarea interogarilor:
Pas 1: Oracle selecteaza inregistrarile radacina ale ierarhiei ce satisfac conditia din clauza
START WITH.
Pas 2: Oracle selecteaza inregistrarile copil pentru fiecare inregistrare radacina. Fiecare
inregistrare copil trebuie sa satisfaca conditia din clauza CONNECT BY.
1
BAZE DE DATE – SEMINAR 8
___________________________________________________________________________
Pas 3: Oracle selecteaza generatii succesive de inregistrari copil evaluand clauza CONNECT
BY.
Pas 4: Daca exista o conditia in clauza WHERE se elimina toate acele inregistrari care nu
satisfac conditia.
Pas 5: Se construieste setul de inregistrari care satisfac conditia de parcurgere a ierarhiei.
Figura 1: Interogari ierarhice
Exemple:
Structura partiala a tabelei utilizate ca exemplu (tabela angajati din schema HR)
ID_ANGAJAT PRENUME NUME SALARIUL COMISION ID_MANAGER ID_DEPARTAMENT
Observatie: Inregistrarea radacina contine angajatul cu numele Steven King cu ID_ANGAJAT
= 100 si ID_MANAGER = NULL.
I. Parcurgerea arborelui TOP-BOTTOM:
1. Sa se afiseze angajatii si nivelul ierarhic al acestora pornind de la angajatul cu id-ul 100 (sa
se ordoneze in functie de nivelul ierahic).
SELECT id_angajat, nume, id_manager, LEVEL FROM angajati
CONNECT BY PRIOR id_angajat= id_manager
START WITH id_angajat = 100;
2
BAZE DE DATE – SEMINAR 8
___________________________________________________________________________
SELECT id_angajat, nume, id_manager, LEVEL FROM angajati
CONNECT BY PRIOR id_angajat= id_manager
START WITH id_angajat = 100
ORDER BY LEVEL;
2. Afisati angajatii companiei subordonati inregistrarii radacina sub forma de organigrama.
SELECT LEVEL, LPAD(' ', LEVEL)|| nume FROM angajati
CONNECT BY PRIOR id_angajat = id_manager
START WITH id_angajat= 100;
3
BAZE DE DATE – SEMINAR 8
___________________________________________________________________________
SELECT LEVEL, LPAD(' ', LEVEL)|| nume FROM angajati
CONNECT BY PRIOR id_angajat = id_manager
START WITH id_angajat= 100
ORDER BY LEVEL;
3. Afisati angajatii companiei subordonati inregistrarii radacina specificand numarul de
superiori si toti superiorii sai, id-urile (se utilizeaza clauzele: SYS_CONNECT_BY_PATH,
LEVEL-1):
4
BAZE DE DATE – SEMINAR 8
___________________________________________________________________________
SELECT id_angajat, nume,
LEVEL-1 Numar_Superiori, SYS_CONNECT_BY_PATH(id_angajat, '/') ID_Superiori
FROM angajati
START WITH id_angajat= 100
CONNECT BY PRIOR id_angajat = id_manager;
Interogari ierarhice conditionate (clauza WHERE):
4. Sa se selecteze angajatii si gradul de subordonare numai pentru cei din departamentele 20 si
50:
SELECT id_angajat, nume, id_manager, level FROM angajati
WHERE id_departament IN (20, 50)
CONNECT BY PRIOR id_angajat = id_manager
START WITH id_angajat = 100;
II. Parcurgerea arborelui BOTTOM UP
5. Sa se afiseze superiorii angajatilor aflati pe ultimul nivel de subordonare:
SELECT nume, LEVEL-1 Numar_Superiori, SYS_CONNECT_BY_PATH(nume, '/')
Nume_Superiori
FROM angajati
START WITH id_angajat = 100
CONNECT BY PRIOR id_angajat = id_manager
ORDER BY LEVEL desc;
6. Sa se afiseze toti superiorii lui ‘Faviet’:
SELECT id_angajat, nume, id_manager, LEVEL FROM angajati
CONNECT BY id_angajat = PRIOR id_manager
START WITH nume= 'Faviet';
III. Parcurgerea arborelui incepind cu un anumit nivel
7. Sa se afiseze toti subordonatii lui 'De Haan':
SELECT id_angajat, nume, id_manager, LEVEL FROM angajati
CONNECT BY PRIOR id_angajat = id_manager
START WITH nume= 'De Haan'
ORDER BY LEVEL;
5
BAZE DE DATE – SEMINAR 8
___________________________________________________________________________
8. Sa se afiseze toti superiorii lui De Haan:
SELECT id_angajat, nume, id_manager, LEVEL FROM angajati
CONNECT BY id_angajat = PRIOR id_manager
START WITH nume= 'De Haan'
ORDER BY LEVEL;
9. Sa se afiseze toti subordonatii lui 'Kochhar' si care sunt in acelasi departament cu 'Chen':
SELECT id_angajat, nume, id_manager, id_departament, LEVEL FROM angajati
WHERE id_departament = (SELECT id_departament FROM angajati WHERE nume='Chen')
CONNECT BY PRIOR id_angajat = id_manager
START WITH nume = 'Kochhar'
ORDER BY LEVEL;
10. Sa se selecteze toti angajatii din departamentul 100 si subordonatii acestora:
SELECT id_angajat, nume, id_manager, id_departament, LEVEL FROM angajati
CONNECT BY PRIOR id_angajat= id_manager
START WITH id_departament=100
ORDER BY LEVEL;
6
BAZE DE DATE – SEMINAR 8
___________________________________________________________________________
11. Sa se afiseze toti subordonatii lui 'Kochhar' fara cei din departamentul 100.
SELECT id_angajat, nume, id_manager, id_departament, LEVEL FROM angajati
WHERE id_departament != 100
CONNECT BY PRIOR id_angajat = id_manager
START WITH nume= 'Kochhar'
ORDER BY LEVEL;
12. Sa se afiseze toti subordonatii lui 'Kochhar' si mai putin cei din departamentele 100 si 110.
SELECT id_angajat, nume, id_manager, id_departament, LEVEL FROM angajati
WHERE id_departament NOT IN (100,110)
CONNECT BY PRIOR id_angajat = id_manager
START WITH nume= 'Kochhar'
ORDER BY LEVEL;
13. Sa se afiseze toti subordonatii lui 'Kochhar' si cei ai lui ‘De Haan’:
SELECT id_angajat, nume, id_manager, LEVEL FROM angajati
CONNECT BY PRIOR id_angajat = id_manager
START WITH nume = 'Kochhar' OR nume= 'De Haan'
ORDER BY LEVEL;
7
BAZE DE DATE – SEMINAR 8
___________________________________________________________________________
14. Sa se afiseze toti subordonatii de pe nivelul 3:
SELECT id_angajat, nume, id_manager, LEVEL FROM angajati
WHERE LEVEL=3
CONNECT BY PRIOR id_angajat = id_manager
ORDER BY LEVEL;
15. Sa se afiseze toti subordonatii incepand cu nivelul 3:
SELECT id_angajat, nume, id_manager, LEVEL FROM angajati
WHERE LEVEL>=3
8
BAZE DE DATE – SEMINAR 8
___________________________________________________________________________
CONNECT BY PRIOR id_angajat = id_manager
ORDER BY LEVEL;
16. Sa se afiseze numarul total de angajati subordonati lui 'Steven King' grupati pe
departamente:
SELECT id_departament, count(*) Total_Angajati from angajati
CONNECT BY PRIOR id_angajat = id_manager
START WITH id_angajat = 100
GROUP BY id_departament;
17. Sa se selecteze toti subordonatii angajatilor cu functia CLERK.
SELECT id_angajat, nume, id_manager, id_functie FROM angajati
CONNECT BY PRIOR id_angajat = id_manager
START WITH id_functie LIKE '%CLERK%'
ORDER BY LEVEL;
9
BAZE DE DATE – SEMINAR 8
___________________________________________________________________________
10



Seminar 9


Operatorii algebrei relationale
UNION, INTERSECT, MINUS

Sunt operatori care actioneaza asupra inregistrarilor selectate de 2 sau mai multe interogari. Sunt similari operatiilor cu multimi.

Atentie: structura (coloanele) celor 2 interogari trebuie sa fie identica!

3.1) Operatorul MINUS – este utilizat pe 2 interogari pentru a extrage din inregistrarile selectate de prima interogare pe cele selectate de a doua interogare     (A-B).

Exemple:

1) Sa se afiseze angajatii care au salariul intre 4999 si 6500 fara cei care au salariul 5000 si 6000.

SELECT * FROM angajati WHERE salariul BETWEEN 4999 AND 6500
MINUS
SELECT * FROM angajati WHERE salariul IN (5000, 6000);

2) Sa se calculeze diferit discountul (DC) pentru clienti astfel:
•	daca clientul a incheiat 1 comanda atunci DC= 10% ;
•	daca a incheiat 2 comenzi atunci DC =15%; 
•	daca a incheiat mai mult de 3 comenzi atunci DC =20%.
Din acestea sa se elimine inregistrarile incheiate de clientii care incep cu litera M. Ordonati descrescator in functie de numele clientilor. 

Observatie: clauza Order by se poate mentiona o singura data la sfarsitul intregii cereri.

SELECT cl.nume_client, COUNT(co.nr_comanda) numar_comenzi,
(CASE WHEN COUNT(co.nr_comanda)=1 THEN 0.1
WHEN COUNT(co.nr_comanda)=2 THEN 0.15
WHEN COUNT(co.nr_comanda)>=3 THEN 0.2
ELSE 0 END)  discount
FROM clienti cl, comenzi co
WHERE cl.id_client=co.id_client
GROUP BY cl.nume_client
MINUS
SELECT cl.nume_client, COUNT(co.nr_comanda) numar_comenzi,
(CASE WHEN COUNT(co.nr_comanda)=1 THEN 0.1
WHEN COUNT(co.nr_comanda)=2 THEN 0.15
WHEN COUNT(co.nr_comanda)>=3 THEN 0.2
ELSE 0 END)  discount
FROM clienti cl, comenzi co
WHERE cl.id_client=co.id_client
AND cl.nume_client like 'M%'
GROUP BY cl.nume_client
ORDER BY nume_client;
3.2.) Operatorul UNION – este utilizat pe 2 interogari pentru a reuni inregistrarile selectate de prima interogare cu cele selectate de a doua interogare (A + B).

3) Sa se calculeze distinct comisionul pentru angajati folosind operatorul UNION:
•	Daca au 1 comanda comisionul va fi de 10% din valoare totala a comenzilor;
•	Daca au 2 comenzi comisionul va fi de 20% din valoare totala a comenzilor;
•	Daca au 3 comenzi comisionul va fi de 30% din valoare totala a comenzilor.

SELECT a.nume, COUNT(c.nr_comanda) numar_comenzi, 
0.1* SUM(r.cantitate*r.pret) valoare_comision
FROM angajati a, comenzi c, rand_comenzi r
WHERE a.id_angajat=c. id_angajat
AND c.nr_comanda=r.nr_comanda
GROUP BY a.nume
HAVING COUNT(c.nr_comanda)=1
UNION 
SELECT a.nume, COUNT(c.nr_comanda) numar_comenzi, 
0.2* SUM(r.cantitate*r.pret) valoare_comision
FROM angajati a, comenzi c, rand_comenzi r
WHERE a.id_angajat=c.id_angajat
AND c.nr_comanda=r.nr_comanda
GROUP BY a.nume
HAVING COUNT(c.nr_comanda)=2
UNION
SELECT a.nume, COUNT(c.nr_comanda) numar_comenzi, 
0.3* SUM(r.cantitate*r.pret) valoare_comision
FROM angajati a, comenzi c, rand_comenzi r
WHERE a.id_angajat=c.id_angajat
AND c.nr_comanda=r.nr_comanda
GROUP BY a.nume
HAVING COUNT(c.nr_comanda)>=3;

3.3.) Operatorul INTERSECT – este utilizat pe 2 interogari pentru a returna doar inregistrarile comune selectate de prima interogare si cele selectate de a doua interogare.

4) Sa se selecteze denumirea produselor, valoare totala comandata (SUM(cantitate*pret)) si numarul de comenzi (count(nr_comanda)) pentru produsele comandate de cel putin 3 ori si care au valoarea totala diferita de 1440, 3916.

SELECT p.denumire_produs, SUM(r.cantitate*r.pret) valoare, COUNT(r.nr_comanda) numar_comenzi
FROM produse p, rand_comenzi r
WHERE r.id_produs=p.id_produs
GROUP BY p.denumire_produs
HAVING COUNT(r.nr_comanda)<=3
INTERSECT
SELECT p.denumire_produs, SUM(r.cantitate*r.pret) valoare, COUNT(r.nr_comanda) nrcomenzi
FROM produse p, rand_comenzi r
WHERE r.id_produs=p.id_produs
GROUP BY p.denumire_produs
HAVING SUM(r.cantitate*r.pret) NOT IN (1440, 3916);


Seminar 10


GESTIUNEA ALTOR OBIECTE ALE BAZEI DE DATE

TABELE VIRTUALE
Tabele virtuale
- Stocheaza interogări si permite reutilizarea  acestora
- Protejeaza informaţiile de natura confidentiala
- Protejeaza BD la actualizare
- Tabele virtuale materializate stocheaza si inregistrarile

CREATE [OR REPLACE] VIEW nume_view AS SELECT...

Exemple: 
1.	Sa realizeze o tabela virtuala cu toti angajatii din departamentul 50. Actualizăm salariul.

CREATE OR REPLACE VIEW v_angajati_50
AS SELECT * FROM angajati
WHERE id_departament=50;

SELECT * FROM v_angajati_50;

UPDATE v_angajati_50
SET salariul = salariul + 100;

2.	Stocarea unei interogări care să permită adăugarea unor condiţii ulterioare
SELECT * FROM v_angajati_50 WHERE EXTRACT(MONTH FROM data_angajare) = 7;

3.	Actualizarea tabelelor virtuale cu ajutorul declanşatorilor
CREATE OR REPLACE VIEW v_rand_comenzi
AS SELECT nr_comanda, pret, pret*cantitate valoare FROM rand_comenzi;

UPDATE v_rand_comenzi
SET valoare = valoare+100;

CREATE OR REPLACE TRIGGER t_rand_comenzi
INSTEAD OF UPDATE ON v_rand_comenzi
BEGIN
UPDATE rand_comenzi SET pret = pret+100;
end;
/
4.	Opţiunea WITH READ ONLY
CREATE OR REPLACE VIEW v_rand_comenzi
AS SELECT nr_comanda, pret, pret*cantitate valoare FROM rand_comenzi
WITH READ ONLY;

5.	Sa se stearga tabela virtuală v_rand_comenzi
DROP VIEW v_rand_comenzi;

6.	Vizualizarea informatiilor despre tabelele virtuale:
SELECT VIEW_NAME, TEXT FROM USER_VIEWS;
INDECSI

-	Permit accesul rapid la date prin sortarea logica a înregistrărilor. 
-	Se crează automat la introducerea unei restricţii de cheie primară sau de unicitate sau manual de către utilizator.

Exemple:
1.	Sa se creeze un index pe tabela angajati pe coloana prenume:

SELECT * FROM angajati WHERE prenume = 'Kevin';
Cost 3
CREATE INDEX idx _nume ON angajati(prenume);
SELECT * FROM angajati WHERE prenume = 'Kevin';
Cost 2

SELECT * FROM angajati WHERE UPPER(prenume) = 'KEVIN';
CREATE INDEX idx_upper_prenume ON angajati(UPPER(prenume));

2.	Vizualizarea indecşilor unui anumit utilizator:

SELECT * FROM USER_INDEXES;

3.	Sa se stearga indexul creat anterior:
DROP INDEX idx_prenume;

SECVENTE

-	Sunt utilizate pentru asigurarea unicitatii cheilor primare sau a valorilor pentru care s-a impus o restrictie de tip UNIQUE.
-	Pot fi utilizate pentru mai multe tabele.
-	Pentru fiecare secventa se va preciza valoarea de inceput, pasul de incrementare si valoarea maxima generata.

Exemple:
1.	Sa se creeze o secventa pentru asigurarea unicitatii cheii primare din tabela Comenzi.

CREATE SEQUENCE seq_nrcomanda 
START WITH 500 INCREMENT BY 10
MAXVALUE 1000 NOCYCLE;

INSERT INTO comenzi VALUES (seq_nrcomanda.NEXTVAL, TO_DATE('oct 12,05', 'mon dd,yy'), 'direct', '104', '1', NULL);

2.	Sa se afiseze valoarea curenta a secventei:

SELECT seq_nrcomanda.CURRVAL FROM DUAL;
 
3.	Să se modifice pasul de incrementare şi valoarea maximă pentru secvenţa anterioară:

ALTER SEQUENCE seq_nrcomanda INCREMENT BY 100;
ALTER SEQUENCE seq_nrcomanda MAXVALUE 2000;

INSERT INTO comenzi VALUES (seq_nrcomanda.NEXTVAL, TO_DATE('oct 12,05', 'mon dd,yy'), 'direct', '104', '1', NULL);

4.	Să se vizualizeze informaţiile depre secvenţele utilizatorilor:

SELECT * FROM USER_SEQUENCES;

5.	Să se steargă secvenţa seq_nrcomanda:

DROP SEQUENCE seq_nrcomanda;

SINONIME

-	Sunt nume alternative utilizate pentru referirea obiectelor unei baze de date.
-	Pot fi sinonime publice (accesibile tuturor utilizatorilor) sau private.
-	Sinonimele publice pot fi create numai de administratorul bazei de date. 

Exemple: 

1.	Sa se creeze un sinonim pentru tabela rând_comenzi:

CREATE SYNONYM rc FOR RAND_COMENZI;

2.	Vizualizarea sinonimelor se realizeaza astfel:

SELECT * FROM USER_SYNONYMS;

3.	Sa se stearga sinonimul creat anterior:

DROP SYNONYM rc;

PARTITII

CREATE TABLE tabela_p(data DATE, cont VARCHAR2(50), divizia VARCHAR2(50))
PARTITION BY RANGE(data)
(PARTITION P1 VALUES LESS THAN (TO_DATE('01.04.2007','DD.MM.YYYY')),
PARTITION P2 VALUES LESS THAN (TO_DATE('01.09.2007','DD.MM.YYYY')));

INSERT INTO tabela_p SELECT data, cont, divizia FROM tabela_m;

SELECT * FROM tabela_p WHERE DATA <TO_DATE('01.02.2007','DD.MM.YYYY');
SELECT * FROM tabela_p  partition (p1) WHERE DATA <TO_DATE('01.02.2007','DD.MM.YYYY');

Cost 17
SELECT * FROM  tabela_m WHERE DATA <TO_DATE('01.02.2007','DD.MM.YYYY');
Cost 99

GRANT SELECT ON tabela_m TO PUBLIC;
REVOKE SELECT ON tabela_m FROM PUBLIC;	

CLUSTERE 

Sa se realizeze un cluster pentru  campul nr_comanda si sa se adauge la acest cluster 2 tabele: comenzi2 si rand_comenzi2 cu aceeasi structura cu tabelele din aplicatie.
CREATE CLUSTER cls_id (id_departament NUMBER(4));

CREATE TABLE ang2
(
id_angajat	NUMBER(6,0),
prenume	VARCHAR2(20 BYTE),
nume	VARCHAR2(25 BYTE),
email	VARCHAR2(25 BYTE),
telefon	VARCHAR2(20 BYTE),
data_ANGAJARE	DATE,
id_functie	VARCHAR2(10 BYTE),
salariul	NUMBER(8,2),
comision	NUMBER(2,2),
id_manager	NUMBER(6,0),
id_departament	NUMBER(4,0))
CLUSTER cls_id (id_departament);

CREATE TABLE dep2
(
id_departament	NUMBER(4,0),
denumire_departament	VARCHAR2(30 BYTE),
id_manager	NUMBER(6,0),
id_locatie	NUMBER(4,0))
CLUSTER cls_id (id_departament);

CREATE INDEX idx_id ON CLUSTER cls_id;

ALTER TABLE dep2 ADD CONSTRAINT pk_dep PRIMARY KEY (id_departament);
ALTER TABLE ang2 ADD CONSTRAINT pk_ang PRIMARY KEY (id_angajat);
ALTER TABLE ang2 ADD CONSTRAINT fk_ang FOREIGN KEY (id_departament) REFERENCES dep2 (id_departament);

INSERT INTO ang2 SELECT * FROM angajati;
INSERT INTO dep2 SELECT * FROM departamente;


SELECT * FROM USER_INDEXES WHERE TABLE_NAME = 'ANGAJATI';
SELECT denumire_departament, nume, salariul
FROM angajati a, departamente d
WHERE a.id_departament = d.id_departament
AND a.id_departament = 20;

SELECT denumire_departament, nume, salariul
FROM ang2 a, dep2 d
WHERE a.id_departament = d.id_departament
AND a.id_departament = 20;

Vizualizarea informatiilor despre clustere:
SELECT * FROM USER_CLUSTERS;

Tema I


Exerciţii recapitulative I – LDD, LMD
1.	Creaţi tabela Dep conform machetei următoare:
CREATE TABLE Dep(
id NUMBER(7) PRIMARY KEY,
denumire VARCHAR2(25)
);
Nume coloană	ID	Denumire
Tipul restricţiei	Primary key	 
Tip data	Number	Varchar2
Lungime	7	25
2.	Introduceţi înregistrări în tabela Dep preluând date din tabela Departamente, incluzând doar câmpurile de care aveţi nevoie (id_department, denumire_departament).
Obs: Mai întâi afişaţi pe ecran structura tabelei Departamente.
SELECT * FROM departamente
INSERT INTO Dep SELECT id_departament, denumire_departament FROM departamente;  
SELECT * FROM Dep ;
3.	Creaţi tabela Ang conform machetei următoare:
CREATE TABLE Ang(
    id NUMBER(7) PRIMARY KEY,
    prenume VARCHAR2(25),
    nume VARCHAR2(25),
    dep_id NUMBER(7),
    CONSTRAINT dep_id_fk FOREIGN KEY(dep_id) REFERENCES Dep(id)
);
SELECT * FROM Ang
Nume coloană	ID	Prenume	Nume	Dep_ID
Tipul restricţiei	Primary key	 	 	Foreign key - referă tabela Dep, coloana ID
Tip data	Number	Varchar2	Varchar2	Number
Lungime	7	25	25	7
4.	Adăugaţi coloana Varsta în tabela Ang având tipul Number(2). 
ALTER TABLE Ang
ADD varsta Number(2);
5.	Adăugaţi restricţia de integritate Verifica_varsta care să nu permită introducerea în câmpul Varsta  a unor valori mai mici de 18 şi mai mari decât 65. 
ALTER TABLE Ang ADD CONSTRAINT verifica_varsta CHECK (varsta>=18 AND varsta<=65);
6.	Dezactivaţi restricţia de integritate Verifica_varsta. 
ALTER TABLE Ang DROP CONSTRAINT verifica_varsta;
7.	Modificaţi proprietăţile câmpului Nume astfel încât lungimea acestuia să fie de 30. 
ALTER TABLE Ang MODIFY nume VARCHAR2(30);
8.	Modificaţi numele tabelei Ang în Ang2. 
ALTER TABLE Ang RENAME TO Ang2;
SELECT * FROM Ang2;
9.	Creaţi tabela Salariati bazată pe structura tabelei Angajati, preluând toate înregistrările. 
CREATE TABLE salariati AS SELECT * FROM angajati; 
SELECT *FROM salariati;
SELECT *FROM angajati; 
/*Cele 2 tabele trebuie sa coincida*/
10.	Adăugaţi următoarele înregistrări în tabela Salariati:
INSERT INTO salariati VALUES(1, 'Stephen', 'Kong', 'SKONG', '515.123.4567', TO_DATE('17.06.1987', 'dd.mm.yyyy'), 'AD_PRES', 24000, 0.1, NULL, 90);
INSERT INTO salariati VALUES(2, 'Neena', 'Koch', 'NKOCH', '515.123.4568', TO_DATE('21.09.1989', 'dd.mm.yyyy'), 'AD_VP', 17000, 0.1, 100, 90);
INSERT INTO salariati VALUES(3, 'Lex', 'Haan', 'LHAAN', '515.123.4569', TO_DATE('13.01.1993', 'dd.mm.yyyy'), 'AD_VP', 17000, 0.2, 100, 90);
1	Steven	Kong	SKONG	515.123.4567	17-06-1987	AD_PRES	24000	0.1	 	90
2	Neena	Koch	NKOCH	515.123.4568	21-09-1989	AD_VP	17000	0.1	100	90
3	Lex	Haan	LHAAN	515.123.4569	13-01-1993	AD_VP	17000	0.2	100	90
11.	Modificaţi în John prenumele angajatului cu id_angajat egal cu 3 (câmpul prenume). 
UPDATE salariati SET prenume='John' WHERE id_angajat=3;
12.	Modificaţi în JHAAN mailul angajatului cu id_angajat egal cu 3 (câmpul email). 
UPDATE salariati SET email='JHAAN' WHERE id_angajat=3;
13.	Creşteţi cu 10% salariile angajaţilor care au în prezent salariul mai mic decât 20000 (câmpul salariul). 
UPDATE salariati SET salariul=salariul+salariul/10 WHERE salariul<20000;
14.	Modificaţi în AD_PRES codul funcţiei (câmpul id_functie) angajatului cu id_angajat egal cu 2. 
UPDATE salariati SET id_functie='AD_PRES' WHERE id_angajat=2;
15.	Modificaţi comisionul (câmpul comision) salariatului cu id_angajat egal cu 2 astfel încât să fie egal cu comisionul salariatului id_angajat egal cu 3, utilizând clauza SELECT. 
UPDATE salariati SET comision=(SELECT comision FROM salariati WHERE id_angajat=3) WHERE id_angajat=2;
16.	Ştergeţi tuplul corespunzător codului id_angajat egal cu 1.
DELETE FROM salariati WHERE id_angajat=1;
