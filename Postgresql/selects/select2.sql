SELECT stud.egzempliorius.nr, stud.knyga.pavadinimas, stud.egzempliorius.paimta, stud.egzempliorius.grazinti, stud.skaitytojas.ak
FROM stud.egzempliorius
JOIN stud.knyga ON stud.egzempliorius.isbn = stud.knyga.isbn
JOIN stud.skaitytojas ON stud.egzempliorius.skaitytojas = stud.skaitytojas.nr
WHERE pavadinimas LIKE 'Duom%' AND egzempliorius.nr > 32105;
