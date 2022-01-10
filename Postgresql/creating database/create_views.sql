CREATE VIEW Laisvi_Sunkvezimiai (Sunkvezimis, Marke, Talpa) AS
	SELECT sunkvezimio_ID, marke, talpa
	FROM Sunkvezimis
	WHERE laisvas IS TRUE
	ORDER BY talpa;

CREATE VIEW Uzimti_Sunkvezimiai (Sukvezimis, Marke, Talpa) AS
	SELECT sunkvezimio_ID, marke, talpa
	FROM Sunkvezimis
	WHERE laisvas IS FALSE
	ORDER BY talpa;

CREATE MATERIALIZED VIEW Dabartiniu_Uzsakymu_Uzdarbis (Uzdarbis) AS
	SELECT SUM(numatyta_kaina)
	FROM Uzsakymai;
