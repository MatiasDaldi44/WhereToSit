Problem

Write two related programs where, given the list of people who are going to the movies together,
the pairs of people who can't sit next to each other, and the list of people who are buying popcorn,
determines the two following things:

(1) Program 1 – the number of different orderings (permutations) of the movie attendees
that satisfy all the restrictions.

(2) Program 2 – the first ordering (in lexicographical order) of the movie attendees
that satisfy all the restrictions.


Output (for Program 1)

On a single line, simply output the total number of valid orderings of the people attending the
movie sitting together in a single row, from left to right. It is guaranteed that the input data will be
such that this value will be a positive integer.

Output (for Program 2)

Output, with one name per line, the first lexicographical valid ordering of the people attending the
moving sitting together in a single row, from left to right. In lexicographical ordering, all lists
starting with name1 will come before all lists starting with name2 if name1 comes before name2
alphabetically. Specifically, given two lists, to determine which one comes first lexicographically,
find the first corresponding name on both lists that don't match. Which ever name comes first
alphabetically, is the list that comes first in lexicographical order.
