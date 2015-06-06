#include "TodosAlgoritmos.cc"
#include <ctime>
using namespace std;


int main(int argc, const char **argv) {
    state_t state, state1, state2, state3;
    bool player;
    
    int x=2;
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
        state = state.move(player, pos);
    }
    state1 = state;
    state2 = state;
    state3 = state;
    clock_t begin,end;
    double elapsed_secs;
    int score;

    cout << "----------------NEGAMAXAB------------------\n"; 
    begin = clock();
    score = negamaxAB(state3,std::numeric_limits<int>::max(),std::numeric_limits<int>::min(),std::numeric_limits<int>::max(),color);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Tiempo: "<< elapsed_secs << "\n";
    cout << score<< "\n";//<< score3 << "\n"<< score1 << "\n"<< score2 << "\n";
    cout << "\n";
    cout << "Nodos: "<< Nodos << "\n";
    cout << "Hojas: "<< Hojas << "\n";
    Nodos=0;
    Hojas=0;
    cout << "----------------NEGAMAX------------------\n"; 
    begin = clock();
    score = negamax(state3,std::numeric_limits<int>::max(),color);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Tiempo: "<< elapsed_secs << "\n";
    cout << score<< "\n";//<< score3 << "\n"<< score1 << "\n"<< score2 << "\n";
    cout << "\n";
    cout << "Nodos: "<< Nodos << "\n";
    cout << "Hojas: "<< Hojas << "\n";
    Nodos=0;
    Hojas=0;
    cout << "----------------SCOUT------------------\n"; 
    begin = clock();
    score = Scout(state3,std::numeric_limits<int>::max(),color);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Tiempo: "<< elapsed_secs << "\n";
    cout << score<< "\n";//<< score3 << "\n"<< score1 << "\n"<< score2 << "\n";
    cout << "\n";
    cout << "Nodos: "<< Nodos << "\n";
    cout << "Hojas: "<< Hojas << "\n";
    Nodos=0;
    Hojas=0;
    cout << "----------------NEGASCOUT------------------\n"; 
    begin = clock();
    score = negaScout(state3,std::numeric_limits<int>::max(),std::numeric_limits<int>::min(),std::numeric_limits<int>::max(),color);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Tiempo: "<< elapsed_secs << "\n";
    cout << score<< "\n";//<< score3 << "\n"<< score1 << "\n"<< score2 << "\n";
    cout << "\n";
    cout << "Nodos: "<< Nodos << "\n";
    cout << "Hojas: "<< Hojas << "\n";
    Nodos=0;
    Hojas=0;
    return 0;
}
