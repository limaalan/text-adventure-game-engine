#include "../include/xdot.h"

using namespace std;


const string fileName = "game_graph.txt";

void show_xDot(Game game) {
ofstream file;
    file.open(fileName);
    file << "digraph g {" << endl;
    file << "graph [rankdir=\"LR\"];"<< endl;
    file << "/*******CENAS********/"<< endl;
    //File format
    /*
    "TITULO" [
    label = "<f0>ID:TITULO|<f1>TEXTORAMA|<f2>1-Iniciar Jogo|<f3>2-Sair do Jogo"
    shape = "record"
    ];
    */
    for ( Scene s : game.scenes){ 
        file << "\""<<s.id<<"\" [" << endl;

        string idTitulo= "<f0>ID:" + s.id +"|<f1>"+s.title;
        int i=2;
        string comandos="";
        for (Command c : s.comands) {
            comandos+="|<f"+to_string(i)+">"+to_string(i)+"-"+c.text;
            i++;

        }       
        i=0;
        file << "label = "<<"\""<<idTitulo<<comandos<<"\"" << endl;
        file << "shape =  \"record\""<<endl;
        file << "];"<<endl;

        
        }

        

        for (Scene s:game.scenes ) {
            int i =2 ;
            for (Command c : s.comands) {

                file << "\""<<s.id<<"\":f"<<to_string(i)<<" -> \""<<c.outcome<<"\":f0";
                i++;

            }
        }


    file << "}" << endl;
    file.close();
    cout << "\n\n** DOT FILE **" << endl;
    cout << "File " << fileName << " successfully generated." << endl;
    cout << "Use graphviz to visualize it. You can test it on http://www.webgraphviz.com/" << endl;

    system( ("xdot " + fileName).c_str() );

}
