#include "TodosAlgoritmos.cc"
#include <ctime>

using namespace std;


int main(int argc, const char **argv) {
    state_t state, state3, state2, state1;
    bool player;

    clock_t begin,end;
    double elapsed_secs;
    int score;
    int mini = -std::numeric_limits<int>::max();
    int maxi = std::numeric_limits<int>::max();
    
    
    int x=15;
    if (argc>1)
        x=atoi(argv[1]);
    cout << x << "\n";
    int j;
    int color = 1;
    for( int i = 0; PV[i] != -1; ++i ) {
        j=i;

        player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        color = -color; 
        if (PV[j+x]==-1) 
            break;
        state1 = state1.move(player, pos);
        state2 = state2.move(player, pos);
        state3 = state3.move(player, pos);
        state = state.move(player, pos);
    }
    if (x<3){
        color = -color;
    }
    
/*    cout << "----------------NEGAMAX------------------\n"; 
    begin = clock();
    score = negamax(state,maxi,color);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "Tiempo: "<< elapsed_secs << "\n";

    cout << "Nodos: "<< Nodos << "\n";
    cout << "Hojas: "<< Hojas << "\n";
    Nodos=0;
    Hojas=0;
    cout << "-------------------------------------------\n";
    cout << "Score: " << score << "\n";
*/    cout << "-------------------------------------------\n";
    cout << "----------------NEGASCOUT------------------\n"; 
    begin = clock();
    score = negaScout(state3,std::numeric_limits<int>::max(),-std::numeric_limits<int>::max(),std::numeric_limits<int>::max(),color);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "Tiempo: "<< elapsed_secs << "\n";

    cout << "Nodos: "<< Nodos << "\n";
    cout << "Hojas: "<< Hojas << "\n";
    Nodos=0;
    Hojas=0;
    cout << "-------------------------------------------\n";
    cout << "Score: " << score << "\n";
    cout << "-------------------------------------------\n";
/*  
    cout << "----------------NEGAMAXAB------------------\n"; 
    begin = clock();
    score = negamaxAB(state1,maxi,mini,maxi,color);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "Tiempo: "<< elapsed_secs << "\n";

    cout << "Nodos: "<< Nodos << "\n";
    cout << "Hojas: "<< Hojas << "\n";
    Nodos=0;
    Hojas=0;
    cout << "-------------------------------------------\n";
    cout << "Score: " << score << "\n";
    cout << "-------------------------------------------\n";


    cout << "----------------SCOUT------------------\n"; 
    begin = clock();
    score = Scout(state2,maxi,color);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "Tiempo: "<< elapsed_secs << "\n";

    cout << "Nodos: "<< Nodos << "\n";
    cout << "Hojas: "<< Hojas << "\n";
    Nodos=0;
    Hojas=0;

    cout << "-------------------------------------------\n";
    cout << "Score: " << score << "\n";
    cout << "-------------------------------------------\n";
    cout << "-------------------------------------------\n";
*/
    return 0;
}
