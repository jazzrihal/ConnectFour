//
//  main.cpp
//  ConnectFour
//
//  Created by Jazz Rihal on 07/11/2020.
//

#include <iostream>
using namespace std;

enum SlotState {
    BLANK,
    PLAYER_1,
    PLAYER_2
};

class Game {
public:
    virtual void Play() {};
};

class ConnectFour : public Game {
    int height, width;
    SlotState **board;
    SlotState current_player;
    int user_in;
    
public:
    ConnectFour() {
        cout << "Enter board height then width: " << endl;
        cin >> height;
        cin >> width;
        
        // Allocate memory
        board = new SlotState*[height];
        for (int i = 0; i < height; i++)
            board[i] = new SlotState[width];
        
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                board[i][j] = BLANK;
        
        // Prepare for first player
        current_player = PLAYER_1;
        user_in = 1;
    }
    
    ~ConnectFour() {
        // Deallocate memory
        for (int i = 0; i < height; i++)
            delete [] board[i];
        delete [] board;
    }
    
    void Play() override {
        while (user_in) {
            Draw();
            Input();
        }
    }
    
private:
    void Draw() {
        // Print column header
        cout << "0 - Quit | 1 - " << height << " to drop token in row\n";
        for (int j = 0; j < width; j++)
            cout << j + 1 << " ";
        cout << endl;
        
        // Print board in its current state
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                SlotState state = board[i][j];
                switch (state)
                {
                case BLANK:     cout << "_ ";   break;
                case PLAYER_1:  cout << "+ ";   break;
                case PLAYER_2:  cout << "x ";   break;
                default:        cout << "E";    break;
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void Input() {
        cin >> user_in;
        cout << endl;
        
        if (user_in >= 0 && user_in <= width) {
            PlaceToken(user_in);
        } else {
            cout << "Enter number between 1 and " << width << endl;
        }
    }
    
    void PlaceToken(int column) {
        column--; // Offset input by 1 to align with desired column
        
        // Find first BLANK slot in column to place current player token
        for (int i = height - 1; i >= 0; i--) {
            SlotState current_state = board[i][column];
            if (current_state == BLANK) {
                if (current_player == PLAYER_1) {
                    board[i][column] = PLAYER_1;
                    break;
                } else {
                    board[i][column] = PLAYER_2;
                    break;
                }
            }
        }
        SwitchPlayer();
    }
    
    void SwitchPlayer() {
        if (current_player == PLAYER_1) {
            current_player = PLAYER_2;
        } else {
            current_player = PLAYER_1;
        }
    }
};

int main() {
    cout << "Welcome to Connect Four!" << endl;
    Game *Game = new ConnectFour();
    Game->Play();
    delete Game;
    
    return 0;
}
