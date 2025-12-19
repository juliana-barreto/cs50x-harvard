SELECT name FROM people
WHERE id IN (
  -- Get person_ids of actors who starred in those movies
  SELECT person_id FROM stars
  WHERE movie_id IN (
    -- Get Kevin Bacon's movie IDs
    SELECT movie_id FROM stars
    WHERE person_id IN (
    -- Get Kevin Bacon's id
      SELECT id FROM people
      WHERE name = 'Kevin Bacon' AND birth = 1958
    )
  )
)
-- Exclude Kevin Bacon himself
AND name != 'Kevin Bacon';