## 22
More structs? God no, please no. I'm sorry, but yes. One more struct excercise. We're putting arrays in our structs, we're leveling up.

The goal here is to create a program that takes input for five player's point totals and games played totals and then calculates the scoring averages for each player. Create a struct with members for total points and games played. Create an array of structures that is five elements deep (one for each player) and loop through the array filling it with the point totals and games played totals for each player.

```terminal_session
struct stats {
  int points;
  int games;
};

struct stats player[5];
```

You can declare an int counter variable and use it to iterate through the array for both points and games.
