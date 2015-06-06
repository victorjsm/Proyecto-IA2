#include "othello_cut.h" 
#include <iostream>
#include <limits>
#include <ctime>
#include <iostream>

using namespace std;

int Nodos=0;
int Hojas=0;

int negamax(state_t state, int depth, int color){
    Nodos = Nodos+1;
    if (depth==0 || state.terminal() ){
        Hojas = Hojas+1;
        return state.value();//check for implementation in othelo_cut
    } 
    int score=- std::numeric_limits<int>::max();
    int val;
    bool player=color>0;
    std::vector<int> v= state.get_valid_moves(player);
    if (v.size() == 0) {
        val=-negamax(state,depth-1,-color);
        score = max(score,val);
    }
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        val=-negamax(state.move(player,*it),depth-1,-color);
        score= max(score,val);
    }
    return score;
}

int negamaxAB(state_t state, int depth, int A, int B, int color){
    Nodos= Nodos+1;
    if (depth==0 || state.terminal() ){
        cout << Hojas << "\n";
        Hojas = Hojas+1;
        return color*state.value();//check for implementation in othelo_cut
    } 
    int score=- std::numeric_limits<int>::max();
    int val;
    bool player=color>0;
    std::vector<int> v= state.get_valid_moves(player);
    if (v.size()==0){
        val = negamaxAB(state,depth-1,-B,-A,-color);
        score = max(score,-val);
    }
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        val=negamaxAB(state.move(player,*it),depth-1,-B,-A,-color);
        score= max(score,-val);
        A= max(A,-val);
        if (A>=B)
            break;
    }
    return score;
}


bool TestMayor(state_t state, int depth, int value, int color){
    if (depth==0 || state.terminal() ){
        return (state.value()>value); 

    }
    bool player=color>0;
    std::vector<int> v= state.get_valid_moves(player);
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if (player && TestMayor(state.move(player,*it),depth-1,value,-color)) {
            return true;
        }
    }
    if (player) {
        return false;
    }
    return true;
}
bool TestMinor(state_t state, int depth, int value, int color){
    if (depth==0 || state.terminal() ){
        return (state.value()<value); 

    }
    bool player=color>0;
    std::vector<int> v= state.get_valid_moves(player);
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if (player && !TestMinor(state.move(player,*it),depth-1,value,-color)) {
            return false;
        }
        if (!player && TestMinor(state.move(player,*it),depth-1,value,-color)) {
            return true;
        }
    }
    if (player) {
        return true;
    }
    return false;
}

int Scout(state_t state, int depth, int color){
    Nodos = Nodos+1;
    if (depth==0 || state.terminal() ){
        Hojas = Hojas+1;
        cout << state << "\n";
        return state.value();//check for implementation in othelo_cut
    } 
    int score=0;
    bool player=color>0;
    int first =0;
    std::vector<int> v= state.get_valid_moves(player);
    if (v.size() == 0) {
        score= Scout(state,depth-1,-color);
    }

    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if (first == 0){
            score = Scout(state.move(player,*it),depth-1,-color);
            first = first +1;
        }
        else{
            if (player && TestMayor(state.move(player,*it),depth-1,score,-color)){
                score = Scout(state.move(player,*it),depth-1,-color);
            }
            if (!player && !TestMayor(state.move(player,*it),depth-1,score,-color)){
                score = Scout(state.move(player,*it),depth-1,-color);
            }
        }
    }
    return score;
}


int negaScout(state_t state, int depth, int A, int B, int color){
    Nodos = Nodos+1;
    if (depth==0 || state.terminal() ){
        Hojas = Hojas+1;
        return color*state.value();//check for implementation in othelo_cut
    } 
    int score=0;
    bool player=color>0;
    int first =0;

    std::vector<int> v= state.get_valid_moves(player);
    if (v.size() == 0) {
        score = -negaScout(state,depth-1,-B,-A,-color);
    }

    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if (first == 0){
            score = -negaScout(state.move(player,*it),depth-1,-B,-A,-color);
            first = first +1;            
        }
        else{
            score = -negaScout(state.move(player,*it),depth-1,-A-1,-A,-color);
            if ((A < score) && ( score < B)){
                score = -negaScout(state.move(player,*it),depth-1,-B,-score,-color);
            }
        }

        A = max(A,score);
        if (A>=B)
            break;
    }
    return A;
}
