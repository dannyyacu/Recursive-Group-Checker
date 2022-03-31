/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

/*USE THIS TO COMPILE
g++ -std=c++17 Grouping.cpp                                                                                                    
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Represents an occupied square in the grid
//Do not modify the GridSquare class or its member functions
class GridSquare
{
    private:
        int row, col;
    public:
        GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square
        GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square
        //Compare with == operator, used in test cases
        bool operator== (const GridSquare r) const
        {
            if ((row == r.row) && (col == r.col))
            {
                return true;
            }
            return false;
        }
        int getRow() { return row; } //return row value
        int getCol() { return col; } //return column value
        //Output using << operator, used in Grouping::printGroups()
        friend ostream& operator<< (ostream& os, const GridSquare obj);
};

//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

/*
Groups squares in 10x10 grid upon construction
Additional private helper functions may be added
Need to implement the constructor that takes a file name
as well as findGroup
The findGroup function's parameter list may be changed based
on how the function is implemented
*/
class Grouping
{
    private:
        int grid[10][10];
        vector<vector<GridSquare> > groups;
    public:
        Grouping() : grid{}, groups() {} //Default constructor, no groups
        Grouping(string fileName); //Implement this function
        // void findGroup(int r, int c); //Implement this function (recursive)
        void findGroup(int r, int c);
        void printGroups() //Displays grid's groups of squares
        {
            for(int g=0; g<groups.size(); g++)
            {
                cout << "Group " << g+1 << ": ";
                for(int s=0; s<groups[g].size(); s++)
                {
                    cout << " " << groups[g][s];
                }
                cout << endl;
            }
        }
        vector<vector<GridSquare> > getGroups() //Needed in unit tests
        {
            return groups;
        }
};

    Grouping::Grouping(string fileName){
        ifstream input;
        input.open(fileName);
        if(input.fail()){
            cout << "ERROR: File not opened correctly" << endl;
        }
        char num = '\0';
            for(int row = 0; row < 10; row++){
                for(int col = 0; col < 10; col++){
                    input >> num;
                    int letter = 0;
                    if (num != '.'){ 
                        letter = 1;
                    }
                    grid[row][col] = letter;
                }   
            }
        input.close();
        for(int row = 0; row < 10; row++){
            for(int col = 0; col < 10; col++){
                if(grid[row][col] == 1){
                groups.push_back(vector<GridSquare>());    
                findGroup(row, col);
                }
            }
        }
    }
         
    void Grouping::findGroup(int row, int col){
        //check row col to see if x or .
        //if x continue else do nothing
        if(grid[row][col] == 1){
                grid[row][col] = 0;
                GridSquare object(row, col);
                groups.at(groups.size()-1).push_back(object);
            if(col+1 < 10){
                findGroup(row, col+1);
            }
            if(col - 1 >= 0){
                findGroup(row, col-1);
            }
            if(row+1 < 10){
                findGroup(row+1, col);
            }
             if(row-1 >= 0){
                findGroup(row-1, col);
            }
        }
    }







//Simple main function to test Grouping
int main()
{
    Grouping input1("input1.txt");
    input1.printGroups();

    
    return 0;
}