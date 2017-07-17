//
//  main.cpp
//  sample
//
//  Created by Shaan Diwanji on 7/11/17.
//  Copyright © 2017 Shaan Diwanji. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cassert>
using namespace std;


class coords{
public:
    int x, y;
};


bool horizontal (coords coordinates, vector < vector < int > > vec){
    map <int, int > mp;
    
    for (int i = 0; i < 9; ++i){
        mp[vec[coordinates.y][i]] += 1;
    }
    
    for (map <int, int>::iterator iter = mp.begin(); iter != mp.end(); ++iter){
        if (iter->first > 0 && iter->second > 1){
            return false;
        }
    }
    
    return true;
}


bool vertical (coords coordinates, vector < vector < int > > vec){
    map <int, int > mp;
    for (int i = 0; i < 9; ++i){
        mp[vec[i][coordinates.x]] += 1;
    }
    for (map <int, int>::iterator iter = mp.begin(); iter != mp.end(); ++iter){
        if (iter->first > 0 && iter->second > 1){
            return false;
        }
    }
    return true;
}

bool unit (coords coordinates, vector < vector < int > > vec ){
    
    
    int first_horiz_trio = coordinates.x;

    if (coordinates.x % 3 == 1){
        --first_horiz_trio;
    } else if (coordinates.x % 3 == 2){
        --first_horiz_trio;
        --first_horiz_trio;
    }
    
    
    int first_vert_trio  = coordinates.y;
    if (coordinates.y % 3 == 1){
        --first_vert_trio;
    } else if (coordinates.y % 3 == 2){
        --first_vert_trio;
        --first_vert_trio;
    }
    
    
    map <int, int > mp;
    
    for (int y = first_vert_trio; y < first_vert_trio + 3; ++y){
        for (int x = first_horiz_trio; x < first_horiz_trio + 3; ++x){
            mp[vec[y][x]] += 1;
        }
    }
    
    for (map <int, int>::iterator iter = mp.begin(); iter != mp.end(); ++iter){
        if (iter->first > 0 && iter->second > 1){
            return false;
        }
    }
    
    return true;
}


int main(int argc, const char * argv[]) {
    
    cout << "enter the unsolved sudoku puzzle you would like to be completed\n";
    cout << endl;
    
    vector < vector <int> > puzzle;
    int bar = 0;
    for (int i = 0; i < 9; i++){
        vector <int> vec;
        for (int j = 0; j < 9; j++){
            cin >> bar;
            cout << bar << " ";
            vec.push_back(bar);
        }
        cout << endl;
        puzzle.push_back(vec);
    }
    
    cout << endl;
    
        vector <coords> open_spaces;
        
        for (int y = 0; y < 9; ++y){
            for (int x = 0; x < 9; ++x){
                if (puzzle[y][x] == 0){
                    coords co;
                    co.x = x;
                    co.y = y;
                    open_spaces.push_back(co);
                }
            }
        }
    
    
    
        int curr_ind = 0;
        int open_spaces_length = (int)open_spaces.size();

    
        bool solution_found = true;
    
        
        
        
        while (curr_ind < open_spaces_length){

            //cout << "curr_ind is " << curr_ind << endl;
            
            coords cod = open_spaces[curr_ind];
            
            if (curr_ind <= 0 && puzzle[cod.y][cod.x] > 9){
                solution_found = false;
                break;
            }
            
            ++puzzle[cod.y][cod.x];
            
            bool regressed = false;
            
            if (puzzle[cod.y][cod.x] > 9){
                puzzle[cod.y][cod.x] = 0;
                --curr_ind;
                regressed = true;
            }
            
            if (curr_ind <= 0 && puzzle[cod.y][cod.x] > 9){
                solution_found = false;
                break;
            }
            
            
            if (!regressed && horizontal(cod, puzzle) && vertical(cod, puzzle) && unit(cod, puzzle)){
                ++curr_ind;
            }
            
        }
        
        
        if (!solution_found){
            cout << "\n\nNo solution was found for puzzle # \n\n";
        } else {
            cout << "solution:\n\n";
            for (int row = 0; row < 9; ++row){
                for (int col = 0; col < 9; ++col){
                    cout << puzzle[row][col] << " ";
                }
                cout << endl;
            }
            
            
        }
    
        puzzle.clear();
    

    
    return 0;
}
