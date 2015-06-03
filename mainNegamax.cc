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
 *  Carlo Polisano
 *  
 *  Compile as such
 *      g++ mainNegamax.cc -o negamax
 *  and run 
 *      ./negamax
 *
 *  if negamax is not executable do
 *      chmod -x negamax
 */

#include "othello_cut.h" 
#include <iostream>
#include <limits>
#include <ctime>
#include <iostream>

using namespace std;

int negamaxAB(state_t state, int depth, int A, int B, int color);
int negamax(state_t state, int depth, int color);

int main(int argc, const char **argv) {
    std::clock_t begin, end;
    state_t state;
    cout << "Principal variation:" << endl;
    int j, x=4;
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

    begin= std::clock();
    int score = negamax(state,31,1);
    end =std::clock();
    cout << "time: " << (end - begin) / (double)(CLOCKS_PER_SEC / 1000) << "ms \n";
    cout << "h:" << score << "\n";

    cout << "\nCall to negamaxAB\n";
    begin= std::clock();
    score = negamaxAB(state,31,std::numeric_limits<int>::min(),std::numeric_limits<int>::max(),1);
    end =std::clock();
    cout << "time: " << (end - begin) / (double)(CLOCKS_PER_SEC / 1000) << "ms \n";
    cout << "h:" << score << "\n";

    return 0;
}


int negamax(state_t state, int depth, int color){
    cout << "depth: "<< depth << "\n";
    cout << state << "\n";
    if (depth==0 || state.terminal() ){
        cout << "Done \n";
        return color*state.value();//check for implementation in othelo_cut
    } 
    int score=std::numeric_limits<int>::min();
    int val;
    bool player=color<0;
    std::vector<int> v= state.get_valid_moves(player);
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << "it:" << *it << "\n\n";
        val=negamax(state.move(player,*it),depth-1,-color);
        cout << "val:" << val << "\n";
        score= max(score,-val);
    }
    cout << "Going back \n";
    return score;
}

int negamaxAB(state_t state, int depth, int A, int B, int color){
    cout << "depth: "<< depth << "\n";
    cout << state << "\n";
    if (depth==0 || state.terminal() ){
        cout << "Done \n";
        return color*state.value();//check for implementation in othelo_cut
    } 
    int score=std::numeric_limits<int>::min();
    int val;
    bool player=color<0;
    std::vector<int> v= state.get_valid_moves(player);
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << "it:" << *it << "\n\n";
        val=negamaxAB(state.move(player,*it),depth-1,-B,-A,-color);
        cout << "val:" << val << "\n";
        score= max(score,-val);
        A= max(A,-val);
        if (A>=B)
            break;
    }
    cout << "Going back \n";
    return score;
}

