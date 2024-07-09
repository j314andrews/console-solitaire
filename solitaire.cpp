#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <random>
#include <stdexcept>

using namespace std;

class Card {

    private:

        int rank; // must be 1 to 13 (1=A, 11=J, 12=Q, 13=K)
        int suit; // 0 = spades, 1 = hearts, 2 = clubs, 3 = diamonds
        bool faceUp; // true if card is face up.

    public:

        // null card, used in blank foundations
        Card() {
            rank = 0;
            suit = -1;
            faceUp = false;
        }

        // A = 1, J = 11, Q = 12, K = 13
        // spades = 0, hearts = 1, clubs = 2, diamonds = 3
        Card(int rank, int suit, bool faceUp) {
            if (rank < 1 || rank > 13 || suit < 0 || suit > 3) {
                throw invalid_argument("Card rank or suit value is invalid.");
            }
            Card::rank = rank;
            Card::suit = suit;
            Card::faceUp = faceUp;
        }

        int getSuit() {
            return suit;
        }

        int getRank() {
            return rank;
        }

        bool isFaceUp() {
            return faceUp;
        }

        void flip() { 
            faceUp = !faceUp;
        }

        // 
        string toString() {
            if (rank == 0){
                return "[   ]";
            }
            if (!faceUp) {
                return "[///]";
            } else {
                string val = "";
                if (suit % 2 == 1) {
                    val += "\x1B[91m";
                } else {
                    val += "\x1B[96m";
                }
                val += "[";
                switch (rank) {
                    case 13:
                        val += "K ";
                        break;
                    case 12:
                        val += "Q ";
                        break;
                    case 11:
                        val += "J ";
                        break;
                    case 10:
                        val += "10";
                        break;
                    case 1:
                        val += "A ";
                        break;
                    default: 
                        val += to_string(rank) + " ";
                }
                switch (suit) {
                    case 0: 
                        val += "\u2660";
                        break;
                    case 1:
                        val += "\u2665";
                        break;
                    case 2:
                        val += "\u2663";
                        break;
                    case 3:
                        val += "\u2666";
                        break;
                }
                val += "]\033[0m";
                return val;
            }
        }
};

class RussianSolitaire {

    private:

        Card foundations[4];
        vector<Card> tableau[7];
        string dealcode;

    public: 

        RussianSolitaire() {

            // Generate random order of cards;
            int indices[52];
            for (int i = 0; i < 52; i++) {
                indices[i] = i;
            }
            random_device rd;
            mt19937 g(rd());
            shuffle(&indices[0], &indices[52], g);

            Card arrangement[52];

            string ranks = "A23456789XJQK";
            string suits = "SHCD";

            // flip cards that should be face up at the start of a game of Russian Solitaire
            for (int i = 0; i < 52; i++) {
                int j = indices[i];
                arrangement[i] = *(new Card(j % 13 + 1, j / 13, false));
                dealcode += ranks[j % 13];
                dealcode += suits[j / 13];
            }
            arrangement[0].flip();
            for (int i = 2; i <= 6; i++) {
                arrangement[i].flip();
            }
            for (int i = 9; i <= 13; i++) {
                arrangement[i].flip();
            }
            for (int i = 17; i <= 21; i++) {
                arrangement[i].flip();
            }
            for (int i = 26; i <= 30; i++) {
                arrangement[i].flip();
            }
            for (int i = 36; i <= 40; i++) {
                arrangement[i].flip();
            }
            for (int i = 47; i <= 51; i++) {
                arrangement[i].flip();
            }

            // deal cards to the proper piles
            tableau[0].push_back(arrangement[0]);
            for (int i = 1; i <= 6; i++) {
                tableau[1].push_back(arrangement[i]);
            }
            for (int i = 7; i <= 13; i++) {
                tableau[2].push_back(arrangement[i]);
            }
            for (int i = 14; i <= 21; i++) {
                tableau[3].push_back(arrangement[i]);
            }
            for (int i = 22; i <= 30; i++) {
                tableau[4].push_back(arrangement[i]);
            }
            for (int i = 31; i <= 40; i++) {
                tableau[5].push_back(arrangement[i]);
            }
            for (int i = 41; i <= 51; i++) {
                tableau[6].push_back(arrangement[i]);
            }

        }

        RussianSolitaire(Card f[], vector<Card> t[], string dealcode) {
            for (int i = 0; i < 4; i++) {
                foundations[i] = f[i];
            }
            for (int j = 0; j < 7; j++) {
                tableau[j] = t[j];
            }
            RussianSolitaire::dealcode = dealcode;
        }

        RussianSolitaire(string dealcode) {
            string ranks = "A23456789XJQK";
            string suits = "SHCD";
            if (dealcode.length() != 104) {
                throw invalid_argument("Deal code must be 104 characters long.");
            }
            for (int i = 0; i < 13; i++) {
                for (int j = 0; j < 4; j++) {
                    string cardstr = "";
                    cardstr += ranks.at(i);
                    cardstr += suits.at(j);
                    int index = dealcode.find(cardstr);
                    if (index == -1) {
                        throw invalid_argument("Each card must appear exactly once in the dealcode");
                    }
                }
            }

            Card arrangement[52];
            for (int i = 0; i < 52; i++) {
                char rchar = dealcode[2 * i], schar = dealcode[2 * i + 1];
                int rank = ranks.find(rchar) + 1;
                int suit = suits.find(schar); 
                arrangement[i] = *(new Card(rank, suit, false));
            }
            arrangement[0].flip();
            for (int i = 2; i <= 6; i++) {
                arrangement[i].flip();
            }
            for (int i = 9; i <= 13; i++) {
                arrangement[i].flip();
            }
            for (int i = 17; i <= 21; i++) {
                arrangement[i].flip();
            }
            for (int i = 26; i <= 30; i++) {
                arrangement[i].flip();
            }
            for (int i = 36; i <= 40; i++) {
                arrangement[i].flip();
            }
            for (int i = 47; i <= 51; i++) {
                arrangement[i].flip();
            }
            // deal cards to the proper piles
            tableau[0].push_back(arrangement[0]);
            for (int i = 1; i <= 6; i++) {
                tableau[1].push_back(arrangement[i]);
            }
            for (int i = 7; i <= 13; i++) {
                tableau[2].push_back(arrangement[i]);
            }
            for (int i = 14; i <= 21; i++) {
                tableau[3].push_back(arrangement[i]);
            }
            for (int i = 22; i <= 30; i++) {
                tableau[4].push_back(arrangement[i]);
            }
            for (int i = 31; i <= 40; i++) {
                tableau[5].push_back(arrangement[i]);
            }
            for (int i = 41; i <= 51; i++) {
                tableau[6].push_back(arrangement[i]);
            }
        }

        // displays state of Russian Solitaire game
        string toString() {

            string val = "\n";
            for (Card c : foundations) {
                val += c.toString();
            }
            val += "\n\n";
            int maxSize = 0;
            for (int i = 0; i < 7; i++) {
                int length = tableau[i].size();
                if (length > maxSize) {
                    maxSize = length;
                }
                if (length == 0) {
                    val += "[   ]";
                } else {
                    val += tableau[i].at(0).toString();
                }
            }
            val += "\n";
            for (int i = 1; i < maxSize; i++) {
                for (int j = 0; j < 7; j++) {
                    int length = tableau[j].size();
                    
                    if (i >= length) {
                        val += "     ";
                    } else {
                        val += tableau[j].at(i).toString();
                    }
                }
                val += "\n";
            }
            return val;
        }

        // Moves all playable cards to foundation piles.
        void autoplay() {
            bool addedCard = true;
            while (addedCard) {
                addedCard = false;
                for (int i = 0; i < 7; i++) {
                    int length = tableau[i].size();
                    if (length > 0) {
                        Card last = tableau[i].at(length - 1);
                        int suit = last.getSuit(), rank = last.getRank();
                        if (foundations[suit].getRank() == rank - 1) {
                            foundations[suit] = last;
                            tableau[i].pop_back();
                            addedCard = true;
                            if (length > 1 && !tableau[i].at(length - 2).isFaceUp()) {
                                tableau[i].at(length - 2).flip();
                            }
                        }
                    }
                }
            }
        } 

        // Search for a card in the tableau.
        int findCard(int rank, int suit) {
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < tableau[i].size(); j++) {
                    Card c = tableau[i].at(j);
                    if (c.getSuit() == suit && c.getRank() == rank) {
                        return i * 100 + j;
                    }
                }
            }
            return -1; 
        }

        // If legal, move a pile of cards to tableau pile i.
        // Returns whether the move was successful.  
        bool moveToNonEmptyPile(int i) {
            int length = tableau[i].size();
            if (length > 0) {
                Card last = tableau[i].at(length - 1);
                int location = findCard(last.getRank() - 1, last.getSuit());
                if (location != -1) {
                    int pile = location / 100, position = location % 100;
                    Card next = tableau[pile].at(position);
                    if (next.isFaceUp() && pile != i) {
                        int pileLength = tableau[pile].size();
                        for (int j = position; j < pileLength; j++) {
                            tableau[i].push_back(tableau[pile].at(j));
                        }
                        tableau[pile].erase(tableau[pile].begin() + position, tableau[pile].end());
                        if (position >= 1 && !tableau[pile].at(position - 1).isFaceUp()) {
                            tableau[pile].at(position - 1).flip();
                        }
                        return true;
                    }
                }
            }
            return false;
        }

        // retrieves the state of the foundation piles and stores in buffer.
        void getFoundations(Card buffer[]) {
            for (int i = 0; i < 4; i++) {
                Card c = foundations[i];
                if (c.getRank() == 0) {
                    buffer[i] = *(new Card());
                } else {
                    buffer[i] = *(new Card(c.getRank(), c.getSuit(), c.isFaceUp()));
                }
            }
        }

        // retrieves the state of the tableau piles and stores in buffer.
        void getTableau(vector<Card> buffer[]) {
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < tableau[i].size(); j++) {
                    Card c = tableau[i].at(j);
                    buffer[i].push_back(*(new Card(c.getRank(), c.getSuit(), c.isFaceUp())));
                }
            }
        }

        // returns the game's dealcode.
        string getDealCode() {
            return dealcode;
        }

        // determines whether a pile of cards may be moved to the specified tableau pile.
        bool hasLegalPileMove(int pile) {
            if (tableau[pile].size() == 0) {
                return false;
            } else {
                Card last = tableau[pile].at(tableau[pile].size() - 1);
                int loc = findCard(last.getRank() - 1, last.getSuit());
                if (loc == -1) {
                    return false;
                }
                int otherPile = loc / 100; 
                int otherPos = loc % 100;
                if (otherPile == pile) {
                    return false;
                } else {
                    Card c = tableau[otherPile].at(otherPos);
                    return c.isFaceUp();
                }
            }
        }

        // determines whether the king of the specified suit may be moved to an empty tableau pile.
        bool hasLegalKingMove(int suit) {
            bool emptyPile = false;
            for (int i = 0; i < 7; i++) {
                if (tableau[i].size() == 0) {
                    emptyPile = true;
                    break;
                }
            }
            if (!emptyPile) {
                return false;
            }
            int loc = findCard(13, suit);
            if (loc == -1) {
                return false;
            }
            int pile = loc / 100;
            int pos = loc % 100;
            return pos != 0 && tableau[pile].at(pos).isFaceUp();
        }

        // moves king of the specified suit to an empty tableau pile.
        // returns whether the move was successful.
        bool moveKingToEmptySpace(int suit) {
            int emptyPile = -1;
            for (int i = 0; i < 7; i++) {
                if (tableau[i].size() == 0) {
                    emptyPile = i;
                    break;
                }
            }
            if (emptyPile != -1) {
                int location = findCard(13, suit);
                if (location != -1) {
                    int pile = location / 100, position = location % 100;
                    Card king = tableau[pile].at(position);
                    if (king.isFaceUp() && position != 0) {
                        int pileLength = tableau[pile].size();
                        for (int j = position; j < pileLength; j++) {
                            tableau[emptyPile].push_back(tableau[pile].at(j));
                        }
                        tableau[pile].erase(tableau[pile].begin() + position, tableau[pile].end());
                        if (position >= 1 && !tableau[pile].at(position - 1).isFaceUp()) {
                            tableau[pile].at(position - 1).flip();
                        }
                        return true;
                    }
                }
            }
            return false;
        }

        // describes all current legal moves and commands. 
        string legalMoves() {
            string moves = "";
            string piles = "1234567";
            for (int i = 0; i < 7; i++) {
                if (hasLegalPileMove(i)) {
                    Card c = tableau[i].at(tableau[i].size() - 1);
                    Card next = *(new Card(c.getRank() - 1, c.getSuit(), true));
                    int otherPile = findCard(next.getRank(), next.getSuit()) / 100;
                    moves += "[";
                    moves += piles[i];
                    moves += "] Move the ";
                    moves += next.toString();
                    moves += " in pile ";
                    moves += piles[otherPile];
                    moves += " to the ";
                    moves += c.toString();
                    moves += " in pile ";
                    moves += piles[i];
                    moves += ".\n";
                } 
            }
            string suits = "SHCD";
            for (int suit = 0; suit <= 3; suit++) {
                if (hasLegalKingMove(suit)) {
                    Card king = *(new Card(13, suit, true));
                    moves += "[";
                    moves += suits[suit];
                    moves += "] Move the ";
                    moves += king.toString();
                    moves += " to an empty pile.\n";
                }
            }
            return moves;
        }

        bool hasNoMoves() {
            string moves = legalMoves();
            return moves == "" && !isWon();
        }

        // updates the game based on the specified 
        bool processUserInput(string input) {
            char c = input[0];
            bool response = false;
            if (c >= '1' && c <= '7') {
                return moveToNonEmptyPile((int) (c - '1'));
            } else if (c == 'S' || c == 's') {
                return moveKingToEmptySpace(0);
            } else if (c == 'H' || c == 'h') {
                return moveKingToEmptySpace(1);
            } else if (c == 'C' || c == 'c') {
                return moveKingToEmptySpace(2);
            } else if (c == 'D' || c == 'd') {
                return moveKingToEmptySpace(3);
            } else {
                return false;
            }
        }

        bool isWon() {
            for (Card c : foundations) {
                if (c.getRank() != 13) {
                    return false;
                }
            }
            return true;
        }

};

