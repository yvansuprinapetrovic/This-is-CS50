SELECT title
FROM movies
--: first time nesting queries
WHERE id = (SELECT movie_id FROM ratings WHERE rating = 10.0);
