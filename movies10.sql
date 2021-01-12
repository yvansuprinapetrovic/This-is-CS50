SELECT name
--: to join three tables together you just have to think what is the common denominator
--: in this case directors can be merged with ratings through the movie id and with people table through the person id
FROM (SELECT name, people.id, directors.movie_id, person_id, ratings.movie_id, rating
FROM directors JOIN ratings ON directors.movie_id = ratings.movie_id
JOIN people ON person_id = people.id)
WHERE rating >= 9.0
--: grouping by person_id in order to avoid duplicates
GROUP BY person_id;
