CREATE FUNCTION KainosSkaiciavimas ()
RETURNS TRIGGER
AS $$
DECLARE
	kaina INTEGER;
BEGIN
	kaina = (NEW.atstumas * 2) + NEW.krovinio_dydis;
	NEW.numatyta_kaina = kaina;
	RETURN NEW;	
END;
$$
LANGUAGE plpgsql;

CREATE FUNCTION KrovinioDydzioTikrinimas ()
RETURNS TRIGGER
AS $$
BEGIN
	IF(SELECT Sunkvezimis.talpa FROM Sunkvezimis 
		WHERE Sunkvezimis.sunkvezimio_ID = NEW.sunkvezimio_ID) < NEW.krovinio_dydis
		THEN RAISE EXCEPTION 'Virsyta sio sunkvezimio talpa';
	END IF;
RETURN NEW;
END;
$$
LANGUAGE plpgsql;

CREATE FUNCTION BusenosPakeitimas ()
RETURNS TRIGGER
AS $$
BEGIN
	IF(SELECT Sunkvezimis.laisvas FROM Sunkvezimis
		WHERE Sunkvezimis.sunkvezimio_ID = NEW.sunkvezimio_ID) IS TRUE
		THEN UPDATE Sunkvezimis SET laisvas = FALSE WHERE Sunkvezimis.sunkvezimio_ID = NEW.sunkvezimio_ID;
		REFRESH MATERIALIZED VIEW Dabartiniu_Uzsakymu_Uzdarbis;
	ELSE 
		RAISE EXCEPTION 'Vairuotojas uzimtas';
	END IF;
RETURN NEW;
END;
$$
LANGUAGE plpgsql;

CREATE FUNCTION VairuotojasLaisvas ()
RETURNS TRIGGER
AS $$
BEGIN
	IF(SELECT Sunkvezimis.laisvas FROM Sunkvezimis
		WHERE Sunkvezimis.sunkvezimio_ID = OLD.sunkvezimio_ID) IS FALSE
		THEN UPDATE Sunkvezimis SET laisvas = TRUE WHERE Sunkvezimis.sunkvezimio_ID = OLD.sunkvezimio_ID;
		REFRESH MATERIALIZED VIEW Dabartiniu_Uzsakymu_Uzdarbis;
	END IF;
RETURN NEW;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER KainosPriskyrimas
BEFORE INSERT ON Uzsakymai 
FOR EACH ROW 
EXECUTE PROCEDURE KainosSkaiciavimas();

CREATE TRIGGER TalposVirsinimas
BEFORE INSERT ON Uzsakymai
FOR EACH ROW
EXECUTE PROCEDURE KrovinioDYdzioTikrinimas();

CREATE TRIGGER ArUzimtas
BEFORE INSERT ON Uzsakymai
FOR EACH ROW
EXECUTE PROCEDURE BusenosPakeitimas();

CREATE TRIGGER ArAtsilaisvino
AFTER DELETE ON Uzsakymai
FOR EACH ROW
EXECUTE PROCEDURE VairuotojasLaisvas();
