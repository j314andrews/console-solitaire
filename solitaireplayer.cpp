#include <stdio.h>
#include "solitaire.cpp"
#include <random>
#include <fstream>

using namespace std;

int main() {

    cout << "Welcome to Russian Solitaire!\n";
    cout << "Enter R to play a random deal.\n";
    cout << "Enter W to play a winnable deal.\n";
    cout << "Enter Q to quit.\n\n";
    cout << ">>> ";

    // 0: Select Game Type.
    // 1: During Game.
    // 2: Out of Moves.
    // 3: Won game.
    int gameState = 0;

    string resp = "";

    char response = 0;
    while (response != 'R' && response != 'r' && response != 'W' && response != 'w') {
        getline(cin, resp);
        if (resp != "") {
            response = resp.at(0);
            if (response == 'Q' || response == 'q') {
                return 0;
            }
        }
        if (response != 'R' && response != 'r' && response != 'W' && response != 'w') {
            cout << "Invalid response.\n>>> ";
        }
    }

    gameState = 1;

    cout << "\nRussian Solitaire\n\n";
    cout << "To move a stack between two tableau piles, enter a number\n";
    cout << "from 1 to 7 specifying the destination pile. \n\n";
    cout << "To move a king into an empty pile, enter C, D, H, or S to \n";
    cout << "specify the suit: clubs, diamonds, hearts, or spades. \n\n";
    cout << "Enter W to start a new winnable game. \n";
    cout << "Enter R to start a new random game. \n";
    cout << "Enter Z to undo your most recent move. \n";
    cout << "Enter Q to quit playing. \n";
    cout << "Enter M to show all valid moves. \n";

    RussianSolitaire rs;
    if (response == 'R' || response == 'r') {
        rs = *(new RussianSolitaire());
    } else if (response == 'W' || response == 'w') {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 10000);
        int seed = distrib(gen);
        ifstream file("winnable_deals.txt");
        string dealcode;
        for (int i = 0; i < seed; i++) {
            getline(file, dealcode);
        }
        rs = *(new RussianSolitaire(dealcode));
    }
    rs.autoplay();
    cout << rs.toString() << "\n>>> ";
    
    vector<RussianSolitaire> prevStates;
    prevStates.push_back(rs);
    string move = "";
    bool announcedOutOfMoves = false;
    bool announcedWin = false;

    if (rs.hasNoMoves()) {
        cout << "You are out of moves!\n\n";
        cout << "Enter Z to undo your last move.\n";
        cout << "Enter R to start a new random game.\n";
        cout << "Enter W to start a new winnable game.\n";
        cout << "Enter Q to quit.\n\n>>> ";
        announcedOutOfMoves = true;
        gameState = 2;
    }

    if (rs.isWon() && !announcedWin) {
        announcedWin = true; 
        cout << "Congratulations! You won!\n\n";
        cout << "Enter R to start a new random game.\n";
        cout << "Enter W to start a new winnable game.\n";
        cout << "Enter Q to quit.\n\n>>> ";
        gameState = 3;
    }

    response = 0;

    while (response != 'Q' && response != 'q') {
        getline(cin, move);
        if (move != "") {
            response = move.at(0);
        }
        if (response == 'R' || response == 'r') {
            gameState = 1;
            announcedOutOfMoves = false;
            announcedWin = false;
            prevStates.clear();
            rs = *(new RussianSolitaire());
            rs.autoplay();
            cout << rs.toString() << "\n>>> ";
            prevStates.push_back(rs);
        } else if (response == 'W' || response == 'w') {
            gameState = 1;
            announcedWin = false;
            announcedOutOfMoves = false;
            prevStates.clear();
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(1, 10000);
            int seed = distrib(gen);
            ifstream file("winnable_deals.txt");
            string dealcode;
            for (int i = 0; i < seed; i++) {
                getline(file, dealcode);
            }
            rs = *(new RussianSolitaire(dealcode));
            rs.autoplay();
            cout << rs.toString() << "\n>>> ";
            prevStates.push_back(rs);
        } else if ((gameState == 1 || gameState == 2) && (response == 'Z' || response == 'z') && prevStates.size() >= 1) {
            gameState = 1;
            announcedOutOfMoves = false;
            int size = prevStates.size();
            if (size >= 2) {
                prevStates.pop_back();
                rs = prevStates.at(size - 2);
                cout << rs.toString() << "\n>>> ";
            }
        } else if (gameState == 1 && (response == 'M' || response == 'm')) {
            cout << "\n" << rs.legalMoves() << "\n>>> ";
        } else if (gameState == 1 && response != 'Q' && response != 'q') {
            Card oldFoundations[4];
            vector<Card> oldTableau[7];
            rs.getFoundations(oldFoundations);
            rs.getTableau(oldTableau);
            string oldDealcode = rs.getDealCode();
            rs = *(new RussianSolitaire(oldFoundations, oldTableau, oldDealcode));
            bool moved = rs.processUserInput(move);
            if (moved) {
                rs.autoplay();
                cout << rs.toString() << "\n>>> ";
                prevStates.push_back(rs);
            } else {
                cout << "Invalid move.\n>>> ";
            }
        } else if (response != 'Q' && response != 'q') {
            cout << "Invalid response.\n>>> ";
        }
        if (rs.hasNoMoves() && !announcedOutOfMoves) {
            announcedOutOfMoves = true;
            cout << "You are out of moves!\n\n";
            cout << "Enter Z to undo your last move.\n";
            cout << "Enter R to start a new random game.\n";
            cout << "Enter W to start a new winnable game.\n";
            cout << "Enter Q to quit.\n\n>>> ";
            gameState = 2;
        }
        if (rs.isWon() && !announcedWin) {
            announcedWin = true; 
            cout << "Congratulations! You won!\n\n";
            cout << "Enter W to start a new winnable game.\n";
            cout << "Enter R to start a new random game.\n";
            cout << "Enter Q to quit.\n\n>>> ";
            gameState = 3;
        }
    }

    return 0;
}