SELECT title FROM movies
--: joining three tables: movies, stars and people
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name = "Helena Bonham Carter"
--: using intersect to find the commone titles between the movies where HBC starred and the ones of JD
INTERSECT
SELECT title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name = "Johnny Depp";
