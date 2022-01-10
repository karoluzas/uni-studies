SELECT A.Table_Schema, A.Table_Name, B.Column_Name
FROM Information_Schema.Views A, Information_Schema.Columns B
WHERE A.Table_Name = 'paemimai' AND A.Table_Name = B.Table_Name
ORDER BY 2, 3;
