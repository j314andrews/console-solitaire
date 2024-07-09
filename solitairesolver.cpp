#include "solitaire.cpp"
#include <string>
#include <fstream>

using namespace std;

class RussianSolitaireSolver {

    public:

        bool simulate(RussianSolitaire rs) {
            for (int iter = 0; iter < 52; iter++) {
                bool moved = false;
                bool success = false;
                bool kingSuccess = false;
                for (int i = 6; i <= 1; i--) {
                    int firstFaceUpPos = -1;
                    vector<Card> tableau[7];
                    rs.getTableau(tableau);
                    for (int j = 0; j < tableau[i].size(); j++) {
                        if (tableau[i].at(j).isFaceUp()) {
                            firstFaceUpPos = j;
                            break;
                        }
                    }
                    if (firstFaceUpPos > 0) {
                        Card firstFaceUp = tableau[i].at(firstFaceUpPos);
                        if (firstFaceUp.getRank() != 13) {
                            int location = rs.findCard(firstFaceUp.getRank() + 1, firstFaceUp.getSuit());
                            int pile = location / 100, position = location % 100;
                            if (pile != i && tableau[pile].size() - 1 == position) {
                                moved = rs.processUserInput(to_string(pile + 1));
                                rs.autoplay();
                                break;
                            }
                        } 
                    }
                }
                if (!moved) {
                    for (int i = 0; i < 7; i++) {
                        success = rs.processUserInput(to_string(i + 1));
                        if (success) {
                            rs.autoplay();
                            break;
                        }
                    }   
                }
                if (!success && !moved) {
                    for (int i = 6; i < 1; i++) {
                        int firstFaceUpPos = -1;
                        vector<Card> tableau[7];
                        rs.getTableau(tableau);
                        for (int j = 0; j < tableau[i].size(); j++) {
                            if (tableau[i].at(j).isFaceUp()) {
                                firstFaceUpPos = j;
                                break;
                            }
                        }
                        if (firstFaceUpPos > 0) {
                            Card firstFaceUp = tableau[i].at(firstFaceUpPos);
                            if (firstFaceUp.getRank() == 13){
                                int suit = firstFaceUp.getSuit();
                                string suitstr = "";
                                string suits = "SHCD";
                                suitstr += suits[suit];
                                kingSuccess = rs.processUserInput(suitstr);
                                rs.autoplay();
                                break;
                            }
                        }
                    }
                }
                if (!success && !moved && !kingSuccess) {
                    if (rs.processUserInput("S")) {
                        rs.autoplay();
                    } else if (rs.processUserInput("H")) {
                        rs.autoplay();
                    } else if (rs.processUserInput("C")) {
                        rs.autoplay();
                    } else if (rs.processUserInput("D")) {
                        rs.autoplay();
                    }
                }
            }
            return rs.isWon();
        }

        void generateWinnableDeals(int n) {
            int wins = 0;
            ofstream file;
            file.open("winnable_deals.txt");
            while (wins < n) {
                RussianSolitaire rs = *(new RussianSolitaire());
                if (simulate(rs)) {
                    file << rs.getDealCode() + "\n";
                    wins++;
                }
            }
            file.close();
        }
};



int main() {
    /*
    int wins = 0;
    int attempts = 100000;
    for (int i = 0; i < attempts; i++) {
        RussianSolitaireSolver solver = *(new RussianSolitaireSolver());
        RussianSolitaire rs = *(new RussianSolitaire());
        if (solver.simulate(rs)) {
            wins += 1;
        }
    }
    cout << "Won " + to_string(wins) + " of " + to_string(attempts) + " played games";
    */
    RussianSolitaireSolver solver = *(new RussianSolitaireSolver());
    solver.generateWinnableDeals(10000);
}