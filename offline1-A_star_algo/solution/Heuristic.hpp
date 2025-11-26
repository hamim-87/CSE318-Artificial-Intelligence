#include <bits/stdc++.h>
using namespace std;
#include "Board.hpp"


class Heuristic
{
    private:
        Board *board;
        Board *goalBoard;
        int boardSize;
        string heuristicType;

        long long linearConflictCount(){
            long long conflictCount = 0;
            auto grid = board->getGrid();
            auto goalGrid = goalBoard->getGrid();

            vector<int> posRow(boardSize* boardSize+1), posCol(boardSize* boardSize+1);

            for(int i = 0; i < boardSize; i++){
                for(int j = 0; j < boardSize; j++){
                    posRow[goalGrid[i][j]] = i;
                    posCol[goalGrid[i][j]] = j;
                }
            }

            // row conflicts
            for(int r = 0; r < boardSize; r++){
                for(int cLeft = 0; cLeft < boardSize; cLeft++){
                    for(int cRight = cLeft + 1; cRight < boardSize; cRight++){
                        bool isBlank = (grid[r][cLeft] != 0 && grid[r][cRight] != 0);
                        bool isSameRow = (posRow[grid[r][cLeft]] == r && posRow[grid[r][cRight]] == r);
                        bool isWrongOrder = (posCol[grid[r][cLeft]] > posCol[grid[r][cRight]]);


                        if(isBlank && isSameRow && isWrongOrder){
                            conflictCount++;
                        }
                    }
                }
            }
            // column conflicts

            for(int c = 0; c< boardSize; c++){
                for(int rUp = 0; rUp < boardSize; rUp++){
                    for(int rDown = rUp + 1; rDown < boardSize; rDown++){
                        bool isBlank = (grid[rUp][c] != 0 && grid[rDown][c] != 0);
                        bool isSameCol = (posCol[grid[rUp][c]] == c && posCol[grid[rDown][c]] == c);
                        bool isWrongOrder = (posRow[grid[rUp][c]] > posRow[grid[rDown][c]]);


                        if(isBlank && isSameCol && isWrongOrder){
                            conflictCount++;
                        }
                    }
                }
            }

            return conflictCount;
        }



    public:

        Heuristic(Board *_board,string _heuristicType = "hamming"){
            heuristicType = _heuristicType;
            board = _board;
            goalBoard = getGoalBoard(board->getBoardSize());
            boardSize = _board->getGrid().size();
            
        }

        long long hammingDistance(){
            int distance = 0;
            auto grid = board->getGrid();
            auto goalGrid = goalBoard->getGrid();

            for(int i = 0; i < boardSize; i++){
                for(int j = 0; j < boardSize; j++){
                    if(grid[i][j] != goalGrid[i][j] && !(boardSize-1 == i && boardSize-1 == j)){
                        distance++;
                    }
                }
            }

            return distance;
        }

        long long manhattanDistance(){
            int distance = 0;
            auto grid = board->getGrid();
            auto goalGrid = goalBoard->getGrid();

            for(int i = 0; i < boardSize; i++){
                for(int j = 0; j < boardSize; j++){
                    if(grid[i][j] != goalGrid[i][j] && !(boardSize-1 == i && boardSize-1 == j)){
                        int value = grid[i][j];
                        int goalX = (value-1) / boardSize;
                        int goalY = (value-1) % boardSize;
                        distance += abs(i - goalX) + abs(j - goalY);
                    }
                }
            }

            return distance;
        }

        double euclideanDistance(){
            double distance = 0.0;
            auto grid = board->getGrid();
            auto goalGrid = goalBoard->getGrid();

            for(int i = 0; i < boardSize; i++){
                for(int j = 0; j < boardSize; j++){
                    if(grid[i][j] != goalGrid[i][j] && !(boardSize-1 == i && boardSize-1 == j)){
                        int value = grid[i][j];
                        int goalX = (value-1) / boardSize;
                        int goalY = (value-1) % boardSize;
                        distance += sqrt(pow(i - goalX, 2) + pow(j - goalY, 2));
                    }
                }
            }

            return distance;
        }

        double linearConflict(){
            return manhattanDistance() + 2 * linearConflictCount();
        }


        double getHeuristicValue(){
            if(heuristicType == "hamming"){
                return hammingDistance();
            }
            else if(heuristicType == "manhattan"){
                return manhattanDistance();
            }
            else if(heuristicType == "euclidean"){
                return euclideanDistance();
            }
            else if(heuristicType == "linear"){
                return linearConflict();
            }
            else{
                cout << "Invalid heuristic type!" << endl;
                return 0;
            }
        }

        Board* getGoalBoard(int dimension) {
            Board* gb = new Board(dimension);
            
            vector<vector<int>> gd(dimension,vector<int>(dimension,0));

            int ct = 1;
            for(int i = 0;i<dimension;i++) {
                for(int j = 0; j<dimension; j++ ){
                    if(j == dimension-1 and i == dimension-1) continue;
                    gd[i][j] = ct;
                    ct++;
                }
            }

            gb->setGrid(gd);

            return gb;

        }

};