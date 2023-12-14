/*
/ Testul 1 /


1.  Sa se redenumeasca tabela “rute” in “curse”.  1p
2.  a.Sa se afiseze destinatiile curselor ce se vor efectua in urmatoarele 7 zile. 1 p
     b. Sa se afiseze toti soferii care sunt asignati la curse ce au ca destinatii ‘Paris’, ‘Madrid’ sau ‘Berlin’. 1p
3. Sa se introduca o coloana noua in tabela curse, cu urmatoarele valori:
-daca data cursei este in luna decembrie sa aiba valoarea 'Extern' altfel sa aiba valoarea 'Intern'; 1p
4. Sa se afiseze 'Itinerariu'  sub forma ‘adresa’ – ‘destinatie’ pentru fiecare cursa in ordinea descrescatoare a numarului de soferi asignati acestora. 2p
5. Sa se afiseze numele soferului asignat la cea mai veche cursa, precum si data acesteia. 3p


drop table curse cascade constraints;
drop table soferi cascade constraints;

create table curse(
    id number(3) constraint pk_curse primary key,
    data date,
    adresa varchar2(30),
    destinatie varchar2(30)
);
create table soferi(
    id number(2) constraint pk_soferi primary key,
    nume varchar2(30),
    cursa_id number(3), constraint fk_cursa_soferi foreign key(cursa_id) references curse(id)
);

insert into curse1(id, data, adresa, destinatie) values(1, to_date('09.12.2019', 'dd.mm.yyyy'), 'Viena', 'Paris');
insert into curse1(id, data, adresa, destinatie) values(2, to_date('14.12.2019', 'dd.mm.yyyy'), 'Bucharest', 'Madrid');
insert into curse1(id, data, adresa, destinatie) values(3, to_date('17.12.2019', 'dd.mm.yyyy'), 'Helsinki', 'Berlin');

insert into soferi(id, nume, cursa_id) values(1, 'I.A.', 1);
insert into soferi(id, nume, cursa_id) values(2, 'T.N.', 1);
insert into soferi(id, nume, cursa_id) values(3, 'M.B.', 1);
insert into soferi(id, nume, cursa_id) values(4, 'C.G.', 2);
insert into soferi(id, nume, cursa_id) values(5, 'A.D', 3);

SELECT* FROM curse
SELECT* FROM soferi
SELECT* FROM rute

/ Cerinta 1 /
RENAME curse TO rute;
/ Cerinta 2 /
SELECT destinatie from rute WHERE data BETWEEN SYSDATE AND SYSDATE + 7;
/ Cerinta 2b /
SELECT s.nume
FROM soferi s, rute r
WHERE r.id = s.cursa_id AND r.destinatie IN('Paris', 'Madrid', 'Berlin');

/ Cerinta 3 /
ALTER TABLE rute
ADD(extern_intern varchar2(20));

UPDATE rute
SET extern_intern = CASE WHEN EXTRACT(MONTH FROM data) = 12 THEN 'Extern' ELSE 'Intern' END;

/ Cerinta 4 /
SELECT r.adresa || '-' || r.destinatie AS Itinerariu
FROM rute r
ORDER BY(
    SELECT COUNT(s.id)
    FROM soferi s
    WHERE s.cursa_id = r.id
) DESC;
/ sau /
SELECT c.adresa || '-' || c.destinatie AS Itinerariu
FROM rute c, soferi s
WHERE c.id = s.cursa_id
GROUP BY c.id, c.adresa, c.destinatie
ORDER BY COUNT(s.id) DESC;

/ Cerinta 5 /
SELECT s.nume, MIN(r.data) AS data_cea_mai_veche
FROM soferi s, rute r
WHERE r.id = s.cursa_id
GROUP BY s.nume
ORDER BY data_cea_mai_veche ASC
FETCH FIRST 1 ROW ONLY;
/ -------------------------------------------------------------------------------------------- - /

/Testul 2 /


1.  Sa se adauge  in tabela “agentie” o restrictie de integritate asupra campului rating, care sa nu permita introducerea de valori mai mici sau egale cu 1 si mai mari sau egale cu 5. 1.5p
2.  a. Sa se afiseze numele agentiilor ce au organizat excursii in luna august. 1 p
     b. Sa se afiseze ca numar intreg, numarul de luni dintre cea mai veche si cea mai recenta excursie.1p
4.  Sa se afiseze pretul excursiilor ce apartin agentiilor cu rating peste rating-ul mediu. 2.5p
5.  Sa se afiseze totalul persoanelor participante la excursiile fiecarei agentii si numele agentiei, doar pentru agentiile care au organizat excursii al caror numar total de persoane este peste 100. 3p


drop table agentie cascade constraints;
drop table excursie cascade constraints;

create table agentie(
    id number(3) constraint pk_agentie  primary key,
    nume varchar2(30),
    rating number(4)
);
create table excursie(
    id number(2) constraint pk_excursie primary key,
    data date,
    nr_persoane number(10),
    pret number(8, 2),
    agentie_id number(3),
    constraint fk_agentie_excursie foreign key(agentie_id) references agentie(id)
);

insert into agentie(id, nume, rating)  values(1, 'Travel Plus', 2);
insert into agentie(id, nume, rating)  values(2, 'ExtraTourism', 3);
insert into agentie(id, nume, rating)  values(3, 'Fun Travel', 4);
insert into agentie(id, nume, rating)  values(4, 'Around The World', 5);
insert into agentie(id, nume, rating)  values(5, 'Travel Agency', 1);
insert into agentie(id, nume, rating)  values(6, 'Easy Trip', 2);
insert into agentie(id, nume, rating)  values(7, 'Globe-Trotter', 3);
insert into excursie(id, data, nr_persoane, pret, agentie_id) values(1, to_date('04.12.2019', 'dd.mm.yyyy'), 90, 9800, 1);
insert into excursie(id, data, nr_persoane, pret, agentie_id) values(2, to_date('05.12.2019', 'dd.mm.yyyy'), 10, 1000, 2);
insert into excursie(id, data, nr_persoane, pret, agentie_id) values(3, to_date('06.12.2019', 'dd.mm.yyyy'), 15, 1200, 1);
insert into excursie(id, data, nr_persoane, pret, agentie_id) values(4, to_date('07.12.2019', 'dd.mm.yyyy'), 20, 2500, 3);
insert into excursie(id, data, nr_persoane, pret, agentie_id) values(5, to_date('08.08.2019', 'dd.mm.yyyy'), 25, 6500, 4);
insert into excursie(id, data, nr_persoane, pret, agentie_id) values(6, to_date('09.08.2019', 'dd.mm.yyyy'), 34, 4300, 5);


/ Cerinta 1 /
ALTER TABLE agentie
ADD CONSTRAINT checkerS CHECK(rating >= 1 and rating <= 5);
/ Cerinta 2 /
SELECT a.nume from agentie a, excursie e WHERE e.agentie_id = a.id AND EXTRACT(MONTH FROM e.data) = 8;
/ Cerinta 2b /
SELECT EXTRACT(MONTH FROM MAX(data)) - EXTRACT(MONTH FROM MIN(data)) as rezultat from excursie;
/ Cerinta 3/

/Cerinta 4 /
SELECT e.pret FROM excursie e, agentie a WHERE e.agentie_id = a.id AND a.rating > (SELECT AVG(rating) FROM agentie);

/ Cerinta 5 /
SELECT  SUM(e.nr_persoane) as total_pers, a.nume
FROM excursie e, agentie a
WHERE e.agentie_id = a.id
GROUP BY a.nume
HAVING SUM(e.nr_persoane) > 100;

/ ---------------------------------------------------------------------------------------------------------------------- - /
/Testul 3 /


1.	Sa  se modifice pretul cartii cu id-ul 1 cu pretul cartii cu id-ul 6 . 1p
2.	a.  Sa se afiseze numele cartilor aparute la edituri din Bucuresti in ordine alfabetica. 1p
b. Sa se afiseze toate cartile lansate in primele 10 zile ale lunii decembrie. 1p
3.	Sa se adauge o coloana noua in tabela ‚carte’, si sa se adauge in aceasta coloana, printr-un singur query, urmatoarele valori:
daca numarul de exemplare este mai mare sau egal cu 40, sa se adauge  ‚stoc disponibil’, altfel sa se adauge ‚stoc limitat’ ; 1p
4.	Sa se afiseze pretul mediu de vanzare al cartilor pentru fiecare localitate. 2p
5.	Sa se afiseze numele editurii, numarul total de carti publicat de fiecare editura, doar daca numarul total de carti publicat este mai mare de 25. 3p


drop table editura cascade constraints;
drop table carte cascade constraints;

create table editura(
    id number(3) constraint pk_editura  primary key,
    nume varchar2(30),
    localitate varchar2(40)
);
create table carte(
    id number(2) constraint pk_carte primary key,
    nume varchar2(30),
    data_aparitie date,
    nr_exemplare number(10),
    pret number(8, 2),
    editura_id number(3),
    constraint fk_carte_editura foreign key(editura_id) references editura(id)
);

insert into editura(id, nume, localitate)  values(1, 'Litera', 'Bucuresti');
insert into editura(id, nume, localitate)  values(2, 'Nemira', 'Cluj');
insert into editura(id, nume, localitate)  values(3, 'Niculescu', 'Timisoara');
insert into editura(id, nume, localitate)  values(4, 'Minerva', 'Bucuresti');
insert into editura(id, nume, localitate)  values(5, 'Paralela 45', 'Iasi');
insert into editura(id, nume, localitate)  values(6, 'Corint', 'Bucuresti');
insert into editura(id, nume, localitate)  values(7, 'Polirom', 'Constanta');

insert into carte(id, nume, data_aparitie, nr_exemplare, pret, editura_id) values(1, 'Micul print', to_date('04.12.2020', 'dd.mm.yyyy'), 90, 98, 1);
insert into carte(id, nume, data_aparitie, nr_exemplare, pret, editura_id) values(2, 'Stapanul inelelor', to_date('03.12.2020', 'dd.mm.yyyy'), 50, 10, 2);
insert into carte(id, nume, data_aparitie, nr_exemplare, pret, editura_id) values(3, 'Harry Potter', to_date('02.12.2020', 'dd.mm.yyyy'), 25, 30, 3);
insert into carte(id, nume, data_aparitie, nr_exemplare, pret, editura_id) values(4, 'Marile sperante', to_date('05.05.2020', 'dd.mm.yyyy'), 40, 20, 1);
insert into carte(id, nume, data_aparitie, nr_exemplare, pret, editura_id) values(5, 'Povestiri', to_date('06.09.2020', 'dd.mm.yyyy'), 10, 10, 1);
insert into carte(id, nume, data_aparitie, nr_exemplare, pret, editura_id) values(6, 'De veghe in lanul de secara', to_date('15.12.2020', 'dd.mm.yyyy'), 7, 100, 4);
insert into carte(id, nume, data_aparitie, nr_exemplare, pret, editura_id) values(7, 'Poezii', to_date('23.12.2020', 'dd.mm.yyyy'), 15, 12, 5);


SELECT* FROM carte
SELECT* FROM editura
/ Cerinta 1 /
update carte set pret = (select pret from carte where id = 6) where id = 1;
/ Cerinta 2 /
select c.nume from carte c, editura e where c.editura_id = e.id and e.localitate = 'Bucuresti'
order by c.nume asc;
/ Cerinta 2b /
select nume from carte where extract(month from data_aparitie) = 12 and extract(day from data_aparitie) < 10;
/ Cerinta 3 /
alter table carte
add(disponibil varchar2(45));
update carte set disponibil = case  when nr_exemplare >= 40 then 'stoc disponibil' else 'stoc limitat' end;
/ Cerinta 4 /
select avg(c.pret), e.localitate from carte c, editura e where c.editura_id = e.id
group by e.localitate;
/ Cerinta 5 /
select sum(c.nr_exemplare), e.nume from editura e, carte c where e.id = c.editura_id
group by e.nume
having sum(c.nr_exemplare) > 25;

/ ------------------------------------------------------------------------------------------------------------/


/Testul 4 /


1. Sa se modifice tipul coloanei cod_cofetarie astfel incat lungimea maxima coloanei sa fie 5.  1.5p
    2.        a. Sa se adauge o restrictie de integritate astfel incat coloana cod_cofetarie sa aiba valori unice. 1 p
   b. Sa se adauge 10% la pretul de lista al furnizorilor asignati la cofetaria cu id-ul 1. 1p
    3. Sa se afiseze codul cofetariei concatenat cu adresa pentru fiecare cofetarie in ordinea crescatoare a numarului de furnziori asignati acestora. 2.5p
    4. Sa se afiseze pretul mediu de lista al furnizorilor ce sunt asignati cofetariilor al caror cod se termina cu litera ‘A’. 3 p


drop table cofetarie cascade constraints;
drop table furnizori cascade constraints;

create table cofetarie(
    id number(3) constraint pk_cofetarie primary key,
    nume varchar2(40),
    adresa varchar2(40),
    cod_cofetarie varchar2(40)
);

create table furnizori(
    id number(2) constraint pk_furnizor primary key,
    nume varchar2(40), pret_lista number(4),
    cofetarie_id number(3),
    constraint fk_cofetarie_furnzior foreign key(cofetarie_id) references cofetarie(id)
);

insert into cofetarie(id, nume, adresa, cod_cofetarie) values(1, 'Cofetaria Amareto', 'Șoseaua Ștefan cel Mare 36', 'AMA');
insert into cofetarie(id, nume, adresa, cod_cofetarie) values(2, 'Cofetaria Agapitos', 'Strada Doctor Dimitrie D. Gerota', 'AGA');
insert into cofetarie(id, nume, adresa, cod_cofetarie) values(3, 'Cofetaria Armand Mosilor', 'Calea Moșilor 221', 'ARM');
insert into furnizori(id, nume, pret_lista, cofetarie_id) values(1, 'I.A.', 100, 1);
insert into furnizori(id, nume, pret_lista, cofetarie_id) values(2, 'T.N.', 1475, 1);
insert into furnizori(id, nume, pret_lista, cofetarie_id) values(3, 'M.B.', 2535, 1);
insert into furnizori(id, nume, pret_lista, cofetarie_id) values(4, 'C.G.', 200, 2);
insert into furnizori(id, nume, pret_lista, cofetarie_id) values(5, 'A.D', 45, 3);

SELECT* FROM cofetarie
SELECT* FROM furnizori

/ Cerinta 1 /
alter table cofetarie
modify(cod_cofetarie varchar2(5));
/ Cerinta 2 /
alter table cofetarie
add constraint unic unique(cod_cofetarie);
/ Cerinta 2b /
update furnizori set pret_lista = 1.1 * pret_lista
where cofetarie_id = 1;
/ Cerinta 3 /
select c.cod_cofetarie || ' ' || c.adresa from cofetarie c, furnizori f where c.id = f.cofetarie_id
group by c.cod_cofetarie, c.adresa
order by count(f.cofetarie_id) asc;
/ Cerinta 4 /
select avg(f.pret_lista), f.cofetarie_id from furnizori f, cofetarie c where c.id = f.cofetarie_id
and c.cod_cofetarie LIKE '%A'
group by f.cofetarie_id;

/ Cerinta 5 /


Test 5

1. Afișarea datei celei mai recente conferințe

SELECT MAX(data) AS data_celei_mai_recente_conferinte
FROM conferinta;

--2. a.Afișarea numelui și adresei conferințelor în ordinea descrescătoare a codului salilor

SELECT c.nume, s.adresa
FROM conferinta c, sala s
WHERE c.sala_id = s.id
ORDER BY s.cod_sala DESC;

--2. b.Afișarea conferințelor ce au avut loc în luna august

SELECT *
FROM conferinta
WHERE EXTRACT(MONTH FROM data) = 8;

--3. Afișarea numărului total și numărului mediu de participanți pentru fiecare sală

SELECT sala_id, COUNT(nr_participanti) AS numar_total_participanti, AVG(nr_participanti) AS numar_mediu_participanti
FROM conferinta
GROUP BY sala_id;

--4. Afișarea codului salilor și numele conferințelor pentru conferințele ce au avut un număr de participanți mai mare decât numărul mediu de participanți

SELECT s.cod_sala, c.nume
FROM sala s, conferinta c
WHERE s.id = c.sala_id
AND c.nr_participanti > (
    SELECT AVG(c_avg.nr_participanti)
    FROM conferinta c_avg
    WHERE c_avg.sala_id = s.id
    );

Test 6


-- 1. Sa se adauge, printr - un singur query, tabela furnizori_vechi care sa contina aceleasi date si aceleasi inregistrari precum tabela furnizori

CREATE TABLE furnizori_vechi AS SELECT* FROM furnizori;

--2a.Sa se schimbe numele coloanei pret_lista in pret

ALTER TABLE furnizori RENAME COLUMN pret_lista TO pret;

--2b.Sa se afiseze numele furnizorului si adresa pentru fiecare cofetarie


SELECT f.nume AS nume_furnizor, c.adresa
FROM furnizori f
JOIN cofetarie c ON f.cofetarie_id = c.id;

--3. Sa se introduca o coloana noua in tabela furnizori, cu urmatoarele valori :

ALTER TABLE furnizori ADD furnizor_tip VARCHAR2(10);
UPDATE furnizori SET furnizor_tip = CASE WHEN pret > 200 THEN 'Premium' ELSE 'Default' END;

--4. Sa se afiseze numarul total de furnizori pentru fiecare cofetarie concatenat cu codul acesteia

SELECT c.cod_cofetarie || COUNT(f.id) AS furnizori_total
FROM cofetarie c
LEFT JOIN furnizori f ON c.id = f.cofetarie_id
GROUP BY c.cod_cofetarie;

--5. Sa se afiseze numele cofetariilor si numele furnizorilor ce livreaza la acestea, doar daca furnizorii au pretul cuprins intre 1000 si 1500

SELECT c.nume AS nume_cofetarie, f.nume AS nume_furnizor
FROM cofetarie c
JOIN furnizori f ON c.id = f.cofetarie_id
WHERE f.pret BETWEEN 1000 AND 1500;

Test 7


1.         Sa se afiseze cursele realizate dupa 15 decembrie.  1p

SELECT * FROM curse WHERE data > TO_DATE('15.12.2019', 'dd.mm.yyyy')

2.         a.Sa se afiseze anul  pentru fiecare cursa. 1 p
SELECT SUBSTR(data, 7, 4) FROM curse;
b.Sa se afiseze salariul soferilorce sunt asignati la curse ce au ca destinatie  ‚Viena’  1p
SELECT c.destinatie, s.salariul FROM curse c, soferi s WHERE c.id = s.cursa_id AND c.destinatie = 'Viena';

3. Sa se afiseze valoarea unui comision pentru soferi, astfel:
-daca soferul este asignat la o cursa, comisionul este 10 % din salariu, daca este asignat la mai mult de doua curse, comisionul este 15 % din salariu.; 1p
SELECT s.id, s.nume, s.salariul, COUNT(c.id) AS numar_cursa,
CASE
WHEN COUNT(c.id) = 1 THEN 0.1 * s.salariul
END AS comision
FROM soferi s
JOIN curse c ON s.cursa_id = c.id
GROUP BY s.id, s.nume, s.salariul;

4. Sa se afiseze salariul mediu al soferilor asignati la fiecare cursa. 2p

SELECT c.id, AVG(s.salariul) AS salariul_mediu FROM curse c JOIN soferi s ON c.id = s.cursa_id GROUP BY c.id;

5. Sa modifice valoarea coloanei destinatie cu valoarea coloanei adresa daca soferul asignat are salariul mai mic de 1500. 3p

UPDATE curse c SET c.destinatie = c.adresa WHERE c.id IN(SELECT s.cursa_id FROM soferi s WHERE s.salariul < 1500);



Test 8

--afiseaza cu litere mari numele editurilor din bucuresti

select upper(nume) from editura where localitate = 'Bucuresti';

--adauga 10 % la pretul cartilor publicate in luna decembrie

update carte set pret = 1.1 * pret
where extract(month from data_aparitie) = 12;
--adauga 100 la numarul de exemplare al cartilor aparute la edituri din bucuresti

update carte set nr_exemplare = nr_exemplare + 100
where editura_id in(select id from editura where localitate = 'Bucuresti');

--afiseaza pretul mediu de vanzare al cartilor pentru fiecare localitate

select e.localitate, avg(c.pret) from carte c, editura e
where c.editura_id = e.id
group by e.localitate;

--afiseaza numele cartilor aparute la edituri ce au numarul mediu de exemplare publicate mai mare decat 20

select nume
from carte
where editura_id IN(
    select editura_id
    from carte
    group by editura_id
    having avg(nr_exemplare) > 20
);

------------------------------------------------------------

Rezolvare Edi

CREATE TABLE Authors(
    author_id INT PRIMARY KEY,
    name VARCHAR2(100),
    bio CLOB
);
CREATE TABLE Genres(
    genre_id INT PRIMARY KEY,
    name VARCHAR2(100),
    description CLOB
);
CREATE TABLE Libraries(
    library_id INT PRIMARY KEY,
    name VARCHAR2(100),
    location VARCHAR2(255)
);
CREATE TABLE Books(
    book_id INT PRIMARY KEY,
    title VARCHAR2(255),
    publication_year INT,
    library_id INT,
    FOREIGN KEY(library_id) REFERENCES Libraries(library_id)
);
CREATE TABLE BookAuthors(
    book_id INT,
    author_id INT,
    PRIMARY KEY(book_id, author_id),
    FOREIGN KEY(book_id) REFERENCES Books(book_id),
    FOREIGN KEY(author_id) REFERENCES Authors(author_id)
);
CREATE TABLE BookGenres(
    book_id INT,
    genre_id INT,
    PRIMARY KEY(book_id, genre_id),
    FOREIGN KEY(book_id) REFERENCES Books(book_id),
    FOREIGN KEY(genre_id) REFERENCES Genres(genre_id)
);

INSERT INTO Authors(author_id, name, bio) VALUES(1, 'Alice Munro', 'Nobel Prize-winning author');
INSERT INTO Authors(author_id, name, bio) VALUES(2, 'Haruki Murakami', 'Contemporary Japanese writer');
INSERT INTO Authors(author_id, name, bio) VALUES(3, 'J.K. Rowling', 'Author of the Harry Potter series');
INSERT INTO Authors(author_id, name, bio) VALUES(4, 'Stephen King', 'Famous for horror and supernatural fiction');
INSERT INTO Genres(genre_id, name, description) VALUES(1, 'Fantasy', 'Fiction with magical or supernatural elements');
INSERT INTO Genres(genre_id, name, description) VALUES(2, 'Horror', 'Fiction intended to scare or unsettle');
INSERT INTO Genres(genre_id, name, description) VALUES(3, 'Literary', 'Focus on artistic value and thematic depth');
INSERT INTO Libraries(library_id, name, location) VALUES(1, 'Downtown Library', '123 City Center');
INSERT INTO Libraries(library_id, name, location) VALUES(2, 'Riverside Library', '456 Riverside Drive');
INSERT INTO Books(book_id, title, publication_year, library_id) VALUES(1, 'Harry Potter and the Sorcerers Stone', 1997, 1);
INSERT INTO Books(book_id, title, publication_year, library_id) VALUES(2, 'Norwegian Wood', 1987, 2);
INSERT INTO Books(book_id, title, publication_year, library_id) VALUES(3, 'The Shining', 1977, 1);
INSERT INTO Books(book_id, title, publication_year, library_id) VALUES(4, 'Dear Life', 2012, 2);
INSERT INTO Books(book_id, title, publication_year, library_id) VALUES(5, 'Runaway', 2012, 2);
INSERT INTO Books(book_id, title, publication_year, library_id) VALUES(6, 'The moons of Jupiter', 1994, 2);
INSERT INTO BookAuthors(book_id, author_id) VALUES(1, 3);
INSERT INTO BookAuthors(book_id, author_id) VALUES(2, 2);
INSERT INTO BookAuthors(book_id, author_id) VALUES(3, 4);
INSERT INTO BookAuthors(book_id, author_id) VALUES(4, 1);
INSERT INTO BookAuthors(book_id, author_id) VALUES(5, 1);
INSERT INTO BookAuthors(book_id, author_id) VALUES(6, 1);
INSERT INTO BookGenres(book_id, genre_id) VALUES(1, 1);
INSERT INTO BookGenres(book_id, genre_id) VALUES(2, 3);
INSERT INTO BookGenres(book_id, genre_id) VALUES(3, 2);
INSERT INTO BookGenres(book_id, genre_id) VALUES(4, 3);
INSERT INTO BookGenres(book_id, genre_id) VALUES(5, 3);
INSERT INTO BookGenres(book_id, genre_id) VALUES(6, 3);










Cerințe:

1.	Actualizați tabelul Books astfel încât să modificați anul publicării la 2000 pentru toate cărțile ale căror titluri încep cu litera 'H' și care se află în biblioteca cu ID - ul 1. După actualizare, afișați toate cărțile care îndeplinesc aceste condiții, afișând titlul și anul publicării.
DESCRIBE BOOKS;
SHOW BOOKS;
--astfel încât să modificați anul publicării la 2000 pentru toate cărțile ale căror titluri încep cu litera 'H' și care se află în biblioteca cu ID - ul.Facut !:)
UPDATE BOOKS
SET PUBLICATION_YEAR = 2000
WHERE TITLE LIKE 'H%' AND BOOK_ID = 1;
SELECT* FROM BOOKS; --Verificarea mea
SELECT * FROM BOOKS
WHERE TITLE LIKE 'H%' AND BOOK_ID = 1;
--- OUTPUT :
--BOOK_ID	TITLE	PUBLICATION_YEAR	LIBRARY_ID
1	Harry Potter and the Sorcerers Stone	2000	1
2	Norwegian Wood	1987	2
3	The Shining	1977	1
4	Dear Life	2012	2
5	Runaway	2012	2
6	The moons of Jupiter	1994	2
-- - BOOK_ID	TITLE	PUBLICATION_YEAR	LIBRARY_ID
----1	Harry Potter and the Sorcerers Stone	2000	1
Alternativ : (Acelasi rezultat)
UPDATE Books
SET publication_year = 2000
WHERE title LIKE 'H%' AND library_id = 1;

SELECT title, publication_year
FROM Books
WHERE title LIKE 'H%' AND library_id = 1;

2.	Afișați numărul de cărți din fiecare gen literar.
DESCRIBE GENRES;
SELECT* FROM GENRES;
SELECT* FROM BOOKS;


SELECT Genres.name, COUNT(BookGenres.book_id) AS num_books
FROM Genres
LEFT JOIN BookGenres ON Genres.genre_id = BookGenres.genre_id
GROUP BY Genres.name; Afișați autorii care au scris mai mult de două cărți.

3.	Listează toate cărțile cu același gen ca 'Runaway', excluzând 'Runaway'.
-- - Exercitiul 1  a, b, c, d1.Actualizați tabelul Books astfel încât să modificați anul publicării la 2000 pentru toate cărțile ale căror titluri încep cu litera 'H' și care se află în biblioteca cu ID - ul 1. După actualizare, afișați toate cărțile care îndeplinesc aceste condiții, afișând titlul și anul publicării.

DESCRIBE BOOKS;
DESCRIBE GENRES;
SELECT* FROM GENRES;
SELECT* FROM BOOKS;
SELECT* FROM BOOKS b, GENRES g
WHERE b.LIBRARY_ID = 2 AND g.NAME = 'Horror';
--Listeaza toate cartile care au acelasi gen ca Runaway  si excluzand pe Runaway : ^) - BIFAT
SELECT * FROM BOOKS b, GENRES g WHERE b.LIBRARY_ID = 2 AND g.NAME = 'Horror' AND b.BOOK_ID != 2;
OUTPUT:
BOOK_ID	TITLE	               PUBLICATION_YEAR	LIBRARY_ID	GENRE_ID	NAME	DESCRIPTION
4	Dear Life	2012	2	2	Horror	Fiction intended to scare or unsettle
5	Runaway	2012	2	2	Horror	Fiction intended to scare or unsettle
6	The moons of Jupiter	1994	2	2	Horror	Fiction intended to scare or unsettle

-- - Exercitiul 4 4.	Listează toate cărțile cu același gen ca 'Runaway', excluzând 'Runaway'.

DESCRIBE BOOKS;
DESCRIBE GENRES;
SELECT* FROM GENRES;
SELECT* FROM BOOKS;
SELECT* FROM BOOKS b, GENRES g
WHERE b.LIBRARY_ID = 2 AND g.NAME = 'Horror';
--Listeaza toate cartile care au acelasi gen ca Runaway  si excluzand pe Runaway : ^) - BIFAT
SELECT * FROM BOOKS b, GENRES g WHERE b.LIBRARY_ID = 2 AND g.NAME = 'Horror' AND b.BOOK_ID != 2;
OUTPUT:
BOOK_ID	TITLE	               PUBLICATION_YEAR	LIBRARY_ID	GENRE_ID	NAME	DESCRIPTION
4	Dear Life	2012	2	2	Horror	Fiction intended to scare or unsettle
5	Runaway	2012	2	2	Horror	Fiction intended to scare or unsettle
6	The moons of Jupiter	1994	2	2	Horror	Fiction intended to scare or unsettle

Sau

Varianta complicata :
SELECT B.title, B.Library_id, B.book_id, g.genre_id
FROM Books B
JOIN BookGenres BG ON B.book_id = BG.book_id
JOIN Genres G ON BG.genre_id = G.genre_id
WHERE G.genre_id IN(
    SELECT G.genre_id
    FROM Books B
    JOIN BookGenres BG ON B.book_id = BG.book_id
    JOIN Genres G ON BG.genre_id = G.genre_id
    WHERE B.title = 'Runaway'
)
AND B.title != 'Runaway';
Output:
TITLE	LIBRARY_ID	BOOK_ID	GENRE_ID
Norwegian Wood	2	2	3
Dear Life	2	4	3
The moons of Jupiter	2	6	3


----------------------------------------------------------------------------ORACLE APEX MY
DESCRIBE BOOKS;
SHOW BOOKS;
--astfel încât să modificați anul publicării la 2000 pentru toate cărțile ale căror titluri încep cu litera 'H' și care se află în biblioteca cu ID - ul.Facut !:)
UPDATE BOOKS
SET PUBLICATION_YEAR = 2000
WHERE TITLE LIKE 'H%' AND BOOK_ID = 1;
SELECT* FROM BOOKS; --Verificarea mea
SELECT * FROM BOOKS
WHERE TITLE LIKE 'H%' AND BOOK_ID = 1;

--- OUTPUT :
--- BOOK_ID	TITLE	PUBLICATION_YEAR	LIBRARY_ID
----1	Harry Potter and the Sorcerers Stone	2000	1
-- - Exercitiul 2 2.	Afișați numărul de cărți din fiecare gen literar.
DESCRIBE GENRES;
SELECT* FROM GENRES;
SELECT* FROM BOOKS;
SELECT COUNT(b.LIBRARY_ID)  FROM BOOKS b, GENRES g;
WHERE
ORDER BY



-- - Exercitiul 3 3.	Afișați autorii care au scris mai mult de două cărți.
DESCRIBE AUTHORS;
SELECT* FROM AUTHORS;
SELECT* FROM BOOKS;
SELECT* FROM BOOKAUTHORS;

SELECT* FROM AUTHORS
SELECT COUNT(b.LIBRARY_ID) AS numere_carti FROM AUTHORS a, BOOKS b
WHERE numere_carti > 2;


--- Exercitiul 4 4.	Listează toate cărțile cu același gen ca 'Runaway', excluzând 'Runaway'.

DESCRIBE BOOKS;
DESCRIBE GENRES;
SELECT* FROM GENRES;
SELECT* FROM BOOKS;
SELECT* FROM BOOKS b, GENRES g
WHERE b.LIBRARY_ID = 2 AND g.NAME = 'Horror';
--Listeaza toate cartile care au acelasi gen ca Runaway  si excluzand pe Runaway : ^) - BIFAT
SELECT * FROM BOOKS b, GENRES g WHERE b.LIBRARY_ID = 2 AND g.NAME = 'Horror' AND b.BOOK_ID != 2;
OUTPUT:
BOOK_ID	TITLE	               PUBLICATION_YEAR	LIBRARY_ID	GENRE_ID	NAME	DESCRIPTION
4	Dear Life	2012	2	2	Horror	Fiction intended to scare or unsettle
5	Runaway	2012	2	2	Horror	Fiction intended to scare or unsettle
6	The moons of Jupiter	1994	2	2	Horror	Fiction intended to scare or unsettle
*/