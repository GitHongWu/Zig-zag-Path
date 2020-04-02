/*
 There is an m×n array of positive integers. A zig-zag
 path from the top left corner to the bottom right corner
 can move down or to the right. The cost of a move is the 
 absolute value of the difference between the two numbers. 
 For example, moving from 5 to 8 costs |5 − 8| = 3. Design 
 a dynamic programming algorithm to find a maximum cost 
 path. There is an m×n array of positive integers. A 
 zig-zag path from the top left corner to the bottom right
 corner can move down or to the right. The cost of a move 
 is the absolute value of the difference between the two 
 numbers. For example, moving from 5 to 8 costs |5 − 8| = 3. 
 Design a dynamic programming algorithm to find a maximum 
 cost path.
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>   //sstringstream
#include <cmath>    //abs
using namespace std;

vector<vector<int>> generateMatrix(istream& inFile){
    vector<vector<int>> tempVec;
    string s;
    while(getline(inFile, s)){
        istringstream ss(s);
        string tmpStr;
        vector<int> tempRow;
        tempRow.clear();
        while (getline(ss, tmpStr, ' ')) {
            tempRow.push_back(stoi(tmpStr));
        }
        tempVec.push_back(tempRow);
    }
    return tempVec;
}

void printMatrix(vector<vector<int>> matrix){
    for(auto i : matrix){
        for(auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }
}

void printDPtable(int **dp, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }
}

void max_path(vector<vector<int>> M){
    
    int numRows = M.size() * 2;
    int numColumns = M[0].size() * 2;
    int **dp;
    int abs_value;

    //generate the dp table
    dp = new int *[numRows];
    for(int i = 0; i < numRows; i++){
        dp[i] = new int[numColumns];
    }

    //initialize the dp table
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numColumns; j++){
            dp[i][j] = 0;
        }
    }
    for(int i = 1; i < numRows; i+=2){
        for(int j = 1; j < numColumns; j+=2) {
            dp[i][j] = M[(i-1)/2][(j-1)/2];
        }
    }

    cout << endl << "DP Table: (after initialize)" << endl;
    printDPtable(dp, numRows, numColumns);

    //Dynamic programming
    for(int i = 1; i < numRows;i++){
        if(i%2 == 0) {
            for (int j = 1; j < numColumns; j+=2){
                // cout << i << " " << j << endl;
                // cout << dp[i-1][j] << " " << dp[i+1][j] << endl;
                abs_value = abs(dp[i-1][j] - dp[i+1][j]);
                dp[i][j] = max(dp[i-2][j], dp[i-1][j-1]) + abs_value;
            }
        }
        else{
            for(int j = 2; j < numColumns; j+=2){
                // cout << i << " " << j << endl;
                // cout << dp[i][j-1] << " " << dp[i][j+1] << endl;
                abs_value = abs(dp[i][j-1] - dp[i][j+1]);
                dp[i][j] = max(dp[i][j-2], dp[i-1][j-1]) + abs_value;
            }
        }
    }

    cout << endl << "DP Table: " << endl;
    printDPtable(dp, numRows, numColumns);
    return;
}

//TODO
void printPath(){
    return;
}

int main()
{
    ifstream inFile;
    inFile.open("test.txt",ios_base::in);
    if (!inFile)
    {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    vector<vector<int>> matrix = generateMatrix(inFile);

    cout << "Original Matrix" << endl;
    printMatrix(matrix);

    max_path(matrix);

    return 0;
}