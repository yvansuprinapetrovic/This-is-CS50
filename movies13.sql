SELECT name FROM people
JOIN stars ON person_id = people.id
JOIN movies ON movies.id = movie_id
--: selecting all names that are associated with the movie id from movies where Kevin Bacon starred
WHERE movie_id IN (SELECT movie_id FROM movies
JOIN stars ON movies.id = movie_id
JOIN people ON people.id = person_id
WHERE name = "Kevin Bacon" AND birth = 1958)
--: using not keyword to exclude Kevin Bacon from results
AND NOT name = "Kevin Bacon"
--: Group by name allows me to filter out duplicates. There are multiples ways to do it but this works a charm in this case
GROUP BY name;

