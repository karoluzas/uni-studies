SELECT stud.skaitytojas.vardas, stud.skaitytojas.pavarde, COUNT(DISTINCT stud.egzempliorius.grazinti) AS "Grazinimo datu skaicius"
FROM stud.egzempliorius
JOIN stud.skaitytojas ON stud.egzempliorius.skaitytojas = stud.skaitytojas.nr
GROUP BY stud.skaitytojas.vardas, stud.skaitytojas.pavarde
ORDER BY COUNT(DISTINCT stud.egzempliorius.grazinti) DESC;
