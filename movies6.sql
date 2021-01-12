--: avg is built in function of SLQ
SELECT AVG(rating)
FROM (SELECT rating, year FROM movies JOIN ratings ON id = movie_id)
--: filtering by year
WHERE year = 2012;
