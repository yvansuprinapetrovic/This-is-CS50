SELECT title, rating
FROM (SELECT title, rating, year FROM movies JOIN ratings ON id = movie_id)
WHERE year = 2010
--: Can combine fields in ORDER BY clause by separating them with a comma and it will respect the ordering order from left to right
--: This will print the list ordering first by rating and then alphabetically by title if rating is same
ORDER BY rating DESC, title
