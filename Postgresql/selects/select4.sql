WITH DatuSkaicius (grazinti, skaitytojuSkaicius) AS (
		SELECT stud.egzempliorius.grazinti, COUNT(DISTINCT stud.egzempliorius.skaitytojas)
		FROM stud.egzempliorius
		WHERE stud.egzempliorius.grazinti IS NOT NULL
		GROUP BY stud.egzempliorius.grazinti
),
	MaziausiasSk (minSk) AS(
		SELECT MAX(skaitytojuSkaicius)
		FROM DatuSkaicius
)

SELECT grazinti, skaitytojuSkaicius
FROM DatuSkaicius, MaziausiasSk
WHERE skaitytojuSkaicius = minSk;
