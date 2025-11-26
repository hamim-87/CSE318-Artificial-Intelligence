


#include "Heuristic.hpp"


class AStar
{
    private:
        Board *startBoard;
        Board *goalBoard;
        string heuristicType;
        Heuristic *heuristic;

        bool isReachedGoal(Board *currentBoardState){
            auto currentGrid = currentBoardState->getGrid();
            auto goalGrid = goalBoard->getGrid();

            for(int i = 0; i < startBoard->getGrid().size(); i++){
                for(int j = 0; j < startBoard->getGrid().size(); j++){
                    if(currentGrid[i][j] != goalGrid[i][j]){
                        return false;
                    }
                }
            }

            return true;
        }

        vector<Board *> getPossibleBoards(Board *currentBoardState){
            vector<Board *> possibleBoards;
            auto grid = currentBoardState->getGrid();

             for(int r = 0; r < startBoard->getBoardSize(); r++){
                for(int c = 0; c < startBoard->getBoardSize(); c++){
                    if(grid[r][c] == 0){

                        for(int i = -1; i <= 1; i++){
                            for(int j = -1; j<= 1; j++){
                                if(abs(i) != abs(j)){

                                    int newRow = r + i;
                                    int newCol = c + j;

                                    if(newRow >= 0 && newRow < startBoard->getBoardSize() && newCol >= 0 && newCol < startBoard->getBoardSize()){
                                        Board *newBoard = new Board(startBoard->getBoardSize());
                                        auto newGrid = currentBoardState->getGrid();
                                        swap(newGrid[r][c], newGrid[newRow][newCol]);
                                        newBoard->setGrid(newGrid);
                                        newBoard->setParent(currentBoardState);
                                        possibleBoards.push_back(newBoard);
                                    }
                                    
                                }
                            }
                         }
                       
                       
                    }
                }
             }

            return possibleBoards;
            
        }

    public:
        AStar(Board *_startBoard,  string _heuristicType ){
            startBoard = _startBoard;
            
            heuristicType = _heuristicType;
            heuristic = new Heuristic(startBoard, heuristicType);
            goalBoard = heuristic->getGoalBoard(startBoard->getBoardSize());
        }

        string gridToString(const vector<vector<int>>& grid){
            string result = "";
            for(int i = 0; i < grid.size(); i++){
                for(int j = 0; j < grid[i].size(); j++){
                    result += to_string(grid[i][j]) + ",";
                }
            }
            return result;
        }

        void search(){

            if(!startBoard->isSolveable()){
                cout<<"Unsolvable puzzle"<<endl;
                return;
            }
            
            priority_queue<
                pair<double, Board*>,
                vector<pair<double, Board*>>,
                greater<pair<double, Board*>>
            > openList;

            set<string> visitedStates;

            double intitalHeuristicValue = heuristic->getHeuristicValue();

            Board *goalstate = nullptr;

            int explored = 0, expanded = 0;

            openList.push({intitalHeuristicValue, startBoard});
            visitedStates.insert(gridToString(startBoard->getGrid()));

            while(!openList.empty()){
                auto currentBoardState = openList.top().second;
                double _heuristicValue = openList.top().first;

                openList.pop();

                Heuristic *currentHeuristic = new Heuristic(currentBoardState, heuristicType);

                double sampleDistance = _heuristicValue - currentHeuristic->getHeuristicValue();

                if(isReachedGoal(currentBoardState)){
                    goalstate = currentBoardState;
                    break;
                }

                expanded++;

                auto possibleBoards = getPossibleBoards(currentBoardState);
                for(auto possibleBoard: possibleBoards){

                    string boardString = gridToString(possibleBoard->getGrid());
                    
                    if(visitedStates.find(boardString) == visitedStates.end()){
                        visitedStates.insert(boardString);
                        
                        Heuristic *nextHeuristic = new Heuristic(possibleBoard, heuristicType);

                        double newHeuristicValue = nextHeuristic->getHeuristicValue() + sampleDistance + 1;
                        openList.push({newHeuristicValue, possibleBoard});
                        explored++;
                        delete nextHeuristic;
                    } else {
                        delete possibleBoard;
                    }
                }

                delete currentHeuristic;

                
            }

            stack<Board *> allMoves;

            while(goalstate != nullptr){
                allMoves.push(goalstate);
                goalstate = goalstate->getParent();
            }


            cout<<"Minimum number of moves = "<<allMoves.size()-1<<endl<<endl;

            while(!allMoves.empty()){
                cout<< *allMoves.top()<<endl;
                allMoves.pop();
            }

            cout<<"Number of explored Node: "<<explored<<endl;
            cout<<"Number of expanded Node: "<<expanded<<endl;





        }
};

