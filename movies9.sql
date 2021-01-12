SELECT name
--: merging three tables together
FROM (SELECT year, movies.id, movie_id, person_id, name, birth
FROM movies
JOIN stars ON movies.id = movie_id
JOIN people ON people.id = person_id)
WHERE year = 2004
--: grouping by person_id in order to remove duplicates
GROUP BY person_id
ORDER BY birth;

--: https://www.w3schools.com/sql/sql_distinct.asp vs https://www.w3schools.com/sql/sql_groupby.asp
