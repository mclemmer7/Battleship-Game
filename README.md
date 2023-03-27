# Battleship-Game
Battleship is a guessing game for two players. It is played on four grids. Two grids (one for each player) are used to mark each players' fleets of ships. The locations of the fleet (these first two grids) are concealed from the other player so that they do not know the positions of the opponent's ships. Players alternate turns by "firing" at the other player's ships. The game's objective is to destroy the opposing player's entire fleet. In your game, "firing" will allow the player to guess where their opponent may have placed a ship on the grid.

I created this entire program from scratch as a final project for my Data Structures class.

This program takes in the ship_placement.csv file and reads it to set up the player's ships. Once prompted for a coordinate, the player will input a coordinate like A1 to fire at the enemy's ships. After this coordinate is entered, the enemy computer will generate a random coordinate and fire at the player's ships. After each round, the player's battleships and firing grid will be displayed. If one of the player's ships has been hit, a message will say that you have been hit, and your sunken battleship will be displayed with 0s instead of its original number. If the player sinks an enemy ship, it will be displayed with 0s on the firing grid.

After all the player's ships or all the enemy's ships have been sunken, the game will end.
