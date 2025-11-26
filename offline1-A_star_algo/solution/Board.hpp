#include <bits/stdc++.h>
using namespace std;


class Board
{
    private:  
        vector<vector<int>> grid;
        int boardSize;
        Board *parent;

    public:
        Board(int _boardSize){
            boardSize = _boardSize;
            grid.resize(boardSize, vector<int>(boardSize, 0));
            parent = nullptr;
        }

        void setGrid(vector<vector<int>> _grid){
            grid = _grid;
        }

        void setParent(Board *_parent){
            parent = _parent;
        }

        vector<vector<int>> getGrid(){
            return grid;
        }

        Board* getParent(){
            return parent;
        }

        int getBoardSize(){
            return boardSize;
        }

        friend ostream& operator<<(ostream &os, const Board &board) {
            os<<"\n";
            for (const auto &row : board.grid) {
                for (const auto &cell : row) {
                    os << cell << " ";
                }
                os << endl;
            }
            return os;
        }

        friend istream& operator>>(istream &is, Board &board){


            for (int i = 0;i < board.boardSize;i++){
                for (int j = 0; j < board.boardSize;j++) {
                    is >> board.grid[i][j];
                }
            }


            return is;
        }

        bool isSolveable(){
            int inversion = getInversionCount();
            int row = getRowCount();
            if(boardSize%2 == 1){
                if(inversion%2 == 0) return true;
                else return false;
            }else{
                if(row%2 == 1 and inversion%2 == 0) return true;
                else if(row % 2 == 0 and inversion % 2 == 1) return true;
                else return false;

            }
        }


    

    
    
    private:
        int getInversionCount(){
            vector<int> v;

            for(int i = 0; i < boardSize; i++) {
                for(int j =0; j < boardSize; j++) {
                    if(grid[i][j] != 0){
                        v.push_back(grid[i][j]);
                    }
                }
            }

            int count = 0;

            for(int i =0;i<v.size();i++){
                for(int j =i;j<v.size();j++){
                    if(v[i]>v[j]) count++;
                }
            }

            return count;

        }

        int getRowCount(){
            for(int i = boardSize-1;i>=0;i--) {
                for(int j = boardSize -1; j >= 0; j--) {
                    if(grid[i][j] == 0){
                        return i;
                    }
                }
            }
            return 0;
        }

};