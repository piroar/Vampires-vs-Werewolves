# Vampires-vs-Werewolves
## Description
There is a war between the vampires and the werewolves and you get caught in the middle of it. In this game you dont control none of them but you let them battle it out and you can decide who of the 2 to help by healing them or blocking the opossite team.
You already have a potion and can collect one other potion in the map. In order to heal each team you must do it at the correct time of day, use the potion on Day to help the vampires and on Night for the Werewolves. Each unit of each team has its own hp, atk and def points (generated randomly), but move diferrently according to their kind. Werewolves can move up, down, left, right while vampires can move diagonally too (Werewolves move like the rook from chess and Vampires move like the queen).

## Controls
You move with the arrow keys, use potion with space and pause the game with Esc.

## Classes:

1)Terrain, which has as member the contnent of each square of the map:

0 for blank

1 for Lake

2 for Tree

3 for Vampires

4 for Werewolves

5 for Avatar

2)Beings, which consists of coordinates x,y and contain every movable object (monsters, avatars, potions)

3)Avatar, the main character that the player controls.  It has variables as members that depict his stash of potions (and all the corresponding functions about increasing or decreasing the potions) and its type as referred to above (3)

4)Monsters, which contail all the shared characteristics between werewolves and vampires like type(1 or 2 depending the kind of monster), damage, defense, hp, meds stash and if the unit is dead or alive. It also has all the corresponding functions.

5)One separate class for werewolves and one for vampires which implement their different types of movement

6)Potion, which has the info about whether it is collected or not
