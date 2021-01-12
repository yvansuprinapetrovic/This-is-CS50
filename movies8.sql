SELECT name
--: merging two tables together
FROM (SELECT name, title, movie_id, person_id
FROM stars
JOIN people ON people.id = person_id
JOIN movies ON movies.id = movie_id)
WHERE title = "Toy Story";
