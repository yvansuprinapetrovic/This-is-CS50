SELECT title, year
FROM movies
--: with % I can tell sql get me everything that starts with Harry Potter. It's a wildcard representing 0 or more characters
WHERE title LIKE "Harry Potter%"
ORDER BY year;
