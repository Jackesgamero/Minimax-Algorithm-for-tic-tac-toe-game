## Minimax-Algorithm-for-tic-tac-toe-game
Simple Minimax algorithm applied to tic-tac-toe game to obtain the most optimal movement for the player at a certain moment of the game.

## How it works

The different states of the game are represented by nodes in the game tree.

In the game tree, the nodes are arranged in levels that correspond to each player's turns in the game so that the “root” node of the tree (usually depicted at the top of the diagram) is the beginning position in the game.

Each node on the second level, would further have as its children nodes the states that can be reached from it by the opposing player's moves. This is continued, level by level, until reaching states where the game is over. In tic-tac-toe, this means that either one of the players gets a line of three and wins, or the board is full and the game ends in a tie.

In order to be able to create game AI that attempts to win the game, it is attach a numerical value to each possible end result. To the board positions where X has a line of three so that Max wins, we attach the value +1, and likewise, to the positions where Min wins with three Os in a row we attach the value -1. For the positions where the board is full and neither player wins, we use the neutral value 0 (it doesn’t really matter what the values are as long as they are in this order so that Max tries to maximize the value, and Min tries to minimize it).

## A sample game tree

Consider, for example, the following game tree which begins not at the root but in the middle of the game (because otherwise, the tree would be way too big to display). Note that this is different from the game shown in the illustration in the beginning of this section.The nodes are numbered with numbers 1, 2, ..., 14.

The tree is composed of alternating layers where it is either Min's turn to place an O or Max's turn to place an X at any of the vacant slots on the board. The player whose turn it is to play next is shown at the left.

![1](https://user-images.githubusercontent.com/71594504/97509550-e1d1d480-1982-11eb-9129-27b2dfb4b00d.PNG)

![2](https://user-images.githubusercontent.com/71594504/97509554-e26a6b00-1982-11eb-9b52-8726b541122b.PNG)

![3](https://user-images.githubusercontent.com/71594504/97509555-e39b9800-1982-11eb-9af7-86861ff5cc55.PNG)

![4](https://user-images.githubusercontent.com/71594504/97509556-e4ccc500-1982-11eb-9a69-7cff9cc4336f.PNG)
