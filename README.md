This is a console-based card solitaire program.  
Currently, the only available solitaire game is Russian Solitaire.
I hope to implement more solitaire games in the future.

Rules for Russian Solitaire:

**Objective**: Complete all four foundation piles.

**Foundation**: All four foundation piles are initially empty.

Each pile is to be built up from Ace to King in the same suit.

**Tableau**:  Each of the seven columns represents a tableau pile, in order from back to front (bottom to top).

Tableau piles are to be built down in the same suit.  For instance, if a tableau pile's frontmost card is the 7 of Diamonds, and the 6 of Diamonds is face up in another tableau pile, 
the 6 of Diamonds and all cards in front (on top) of it may be picked up and moved in front (on top) of the 7 of Diamonds.

Empty tableau piles may only be filled with a King (along with all cards in front [on top] of the King).

Face-down cards in the tableau are revealed once they are uncovered.  

**Commands**:

1/2/3/4/5/6/7:  Moves card(s) to the specified non-empty tableau pile, if the move is legal.

S/H/C/D:  Moves king of specified suit into empty tableau pile, if the move is legal.

M:  Lists all available legal moves and their respective commands.

Z:  Undoes the previous move.

R:  Starts a new randomly dealt game which may or may not be winnable.

W:  Starts a new game that is guaranteed to be winnable.

Q:  Quits the game.  
