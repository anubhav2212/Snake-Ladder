#include<bits/stdc++.h>
using namespace std;

class Snake {
    int startpos;
    int endpos;
public:
    Snake(int startp, int endp) {
        startpos = startp;
        endpos = endp;
    }
    int getStart() {
        return startpos;
    }
    int getEnd() {
        return endpos;
    }
};

class Ladder {
    int startpos;
    int endpos;
public:
    Ladder(int startp, int endp) {
        startpos = startp;
        endpos = endp;
    }
    int getStart() {
        return startpos;
    }
    int getEnd() {
        return endpos;
    }
};

class Player {
public:
    string name;
    int id;

    Player(string nam, int idVal) {
        name = nam;
        id = idVal;
    }
    string getName() {
        return name;
    }
    int getId() {
        return id;
    }
};

class Board {
    int size;
    vector<Snake> snakes;
    vector<Ladder> ladders;
public:
    map<int, int> pieces;
    Board(int siz) {
        size = siz;
    }
    int getSize() {
        return size;
    }
    vector<Ladder> getLadders() {
        return ladders;
    }
    vector<Snake> getSnakes() {
        return snakes;
    }
    map<int, int> getpieces() {
        return pieces;
    }
    void setLadders(vector<Ladder> ls) {
        ladders = ls;
    }
    void setSnakes(vector<Snake> ss) {
        snakes = ss;
    }
    void setPieces(map<int, int> ps) {
        pieces = ps;
    }
};

class GameService {
    int numOfPlayers;
    int curPlayers;
    Board *gameBoard;
    vector<Player> players;
public:
    GameService() {
        gameBoard = new Board(100);
    }
    void setPlayers(vector<Player> ps) {
        numOfPlayers = ps.size();
        curPlayers = ps.size();
        map<int, int> playerPieces;
        for(Player p : ps) {
            players.push_back(p);
            playerPieces.insert(pair<int, int>(p.getId(), 0));
        }
        gameBoard->setPieces(playerPieces);
    }
    void setSnakes(vector<Snake> snakes) {
        gameBoard->setSnakes(snakes);
    }
    void setLadders(vector<Ladder> ladders) {
        gameBoard->setLadders(ladders);
    }
    int getDiceValue() {
        return (rand()%6) + 1;
    }
    int getNewPosition(int newPosition) {
        int prevPosition;
        do {
            prevPosition = newPosition;
            for(Snake snake : gameBoard->getSnakes()) {
                if(snake.getStart() == newPosition) {
                    newPosition = snake.getEnd();
                }
            }
            for(Ladder ladder : gameBoard->getLadders()) {
                if(ladder.getStart() == newPosition) {
                    newPosition = ladder.getEnd();
                }
            }
        }while(newPosition != prevPosition);
        return newPosition;
    }
    void movePlayer(Player player, int position) {
        int oldPosition = gameBoard->getpieces()[player.getId()];
        int newPosition = oldPosition + position;
        int boardSize = gameBoard->getSize();
        if(newPosition > boardSize) {
            newPosition = oldPosition;
        }
        else {
            newPosition = getNewPosition(newPosition);
        }
        gameBoard->pieces[player.getId()] = newPosition;
        cout<<player.getName()<<" rolled a "<<position<<" and moved from "<<oldPosition<<" to "<<newPosition<<endl;
    }
    bool hasPlayerWon(Player player) {
        int playerPosition = gameBoard->getpieces()[player.getId()];
        return playerPosition == gameBoard->getSize();
    }
    bool isGameCompleted() {
        return curPlayers < numOfPlayers;
    }
    void startGame() {
        int chance = 0;
        while(!isGameCompleted()) {
            int diceVal = getDiceValue();
            Player currentPlayer = players[chance];
            movePlayer(currentPlayer, diceVal);
            if(hasPlayerWon(currentPlayer)) {
                gameBoard->getpieces().erase(currentPlayer.getId());
                cout<<currentPlayer.getName()<<" wins the game";
                curPlayers--;
            }
            chance = (chance + 1)%players.size();
        }
    }

};

int main() {
    srand(time(NULL));
    int numOfPlayers, numOfSnakes, numOfLadders;
    int idCounter = 1;
    int s, e;
    string name;
    cin>>numOfSnakes;
    cin>>numOfLadders;
    cin>>numOfPlayers;
    vector<Snake> snakes;
    vector<Ladder> ladders;
    vector<Player> players;
    for(int i=0;i<numOfSnakes;i++) {
        cin>>s>>e;
        Snake q(s, e);
        snakes.push_back(q);
    }
    for(int i=0;i<numOfLadders;i++) {
        cin>>s>>e;
        Ladder r(s, e);
        ladders.push_back(r);
    }
    for(int i=0;i<numOfPlayers;i++) {
        cin>>name;
        Player p(name, idCounter);
        idCounter++;
        players.push_back(p);
    }
    GameService *game = new GameService();
    game->setSnakes(snakes);
    game->setLadders(ladders);
    game->setPlayers(players);

    game->startGame();
    return 0;
}

/* input
4
1
2
20
10
30
10
40
10
60
10
10
50
a
b
*/
