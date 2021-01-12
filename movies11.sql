SELECT title
FROM (SELECT stars.movie_id, person_id, title, people.id, name, rating, ratings.movie_id
FROM stars JOIN movies ON movies.id = stars.movie_id
JOIN people ON people.id = person_id
JOIN ratings ON ratings.movie_id = stars.movie_id)
WHERE name = "Chadwick Boseman"
--: ascending is by default so I must specificy I want results sorted by descending order
ORDER BY rating DESC
--: limit allows me to filter only the first 5 results
LIMIT 5;
