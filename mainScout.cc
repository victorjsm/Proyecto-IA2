/*
 *  Copyright (C) 2012 Universidad Simon Bolivar
 * 
 *  Permission is hereby granted to distribute this software for
 *  non-commercial research purposes, provided that this copyright
 *  notice is included with any such distribution.
 *  
 *  THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 *  EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
 *  SOFTWARE IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU
 *  ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 *  
 *  Blai Bonet, bonet@ldc.usb.ve
 *
 *  Last revision: 11/08/2012
 *
 */

#include "othello_cut.h" // won't work correctly until .h is fixed!
#include <iostream>
#include <limits>

using namespace std;

int Scout(state_t state, int depth, int color);

int main(int argc, const char **argv) {
    state_t state;
    cout << "Principal variation:" << endl;
    int j, x=2;
    for( int i = 0; PV[i] != -1; ++i ) {
        j=i;
        bool player = i % 2 == 0; // black moves first!
        int pos = PV[i]; 
        cout << state << "\n";
        if (PV[j+x]==-1) 
            break;
        state = state.move(player, pos);
    }
    
    cout << state;
    cout << "\nCall to negamax\n";
    int score = Scout(state,j-x,1);

    cout << score;
    cout << "\n";
    /*
    for( int i = 0; PV[i] != -1; ++i ) {
        bool player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        cout << state;
        cout << (player ? "Black" : "White")
             << " moves at pos = " << pos << (pos == 36 ? " (pass)" : "")
             << endl;
        state = state.move(player, pos);
        cout << "Board after " << i+1 << (i == 0 ? " ply:" : " plies:") << endl;
    }
    cout << state;
    cout << "Value of the game = " << state.value() << endl;
    cout << "#bits per state = " << sizeof(state) * 8 << endl;

    if( argc > 1 ) {
        int n = atoi(argv[1]);
        cout << endl << "Apply " << n << " random movements at empty board:";
        state = state_t();
        for( int i = 0; i < n; ++i ) {
            bool player = i % 2 == 0; // black moves first
            int pos = state.get_random_move(player);
            state = state.move(player, pos);
            cout << " " << pos;
        }
        cout << endl << state;
    */

    return 0;
}
bool TestMayor(state_t state, int depth, int value, int color){
    if (depth==0 || state.terminal() ){
        return (state.value()>value); 

    }
    bool player=color<0;
    std::vector<int> v= state.get_valid_moves(player);
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if ((color>0) && !TestMayor(state.move(player,*it),depth-1,value,-color)) {
            return false;
        }
    }
    return color<0;
}
bool TestMinor(state_t state, int depth, int value, int color){
    if (depth==0 || state.terminal() ){
        return (state.value()<value); 

    }
    bool player=color<0;
    std::vector<int> v= state.get_valid_moves(player);
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if ((color>0) && !TestMinor(state.move(player,*it),depth-1,value,-color)) {
            return false;
        }
    }
    return color>0;
}

int Scout(state_t state, int depth, int color){
    cout << "depth: "<< depth << "\n";
    cout << state << "\n";
    if (depth==0 || state.terminal() ){
        cout << "Done \n";
        return state.value();//check for implementation in othelo_cut
    } 
    int score=0;
    bool player=color<0;
    int first =0;
    std::vector<int> v= state.get_valid_moves(player);
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << "it:" << *it << "\n\n";
        if (first == 0){
            score = Scout(state.move(player,*it),depth-1,-color);
            first = first +1;
        }
        else{
            if ((color>0) && TestMayor(state.move(player,*it),depth-1,score,-color)){
                score = Scout(state.move(player,*it),depth-1,-color);
            }
            if ((color<0) && TestMinor(state.move(player,*it),depth-1,score,-color)){
                score = Scout(state.move(player,*it),depth-1,-color);
            }
        }
    }
    cout << "Going back \n";
    return score;
}


