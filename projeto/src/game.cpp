#include "../include/game.h"

using namespace std;


string processaCena (Game game, string idCena, bool print){

    
        Hash h = game.hash;
        int index =hashFind(h,idCena);
        if (print){
            cout <<"\n"<< game.scenes[index].title << endl;
            cout << game.scenes[index].description << endl;

            cout << "---------OPÇÕES---------"<<endl;

            for ( int i=0 ; i < game.scenes[index].comands.size() ; i++){ // display all options 

                    cout <<"["<<i<<"]"<< game.scenes[index].comands[i].text << endl;

            }
        }

        // Asks the user for a number then return the scene.
        cout << "\nAção : ";
        int idxNext;
        int a =0 ;
        int cont=0;
        do {
        if (cont > 0)
            cout <<"Insira um valor válido : ";
        cont++;
        cin >>idxNext;

        } while (idxNext >=game.scenes[index].comands.size() || idxNext<0);

        cout << game.scenes[index].comands[idxNext].result<< endl;

         if (game.scenes[index].comands[idxNext].outcome != "NONE")
            return game.scenes[index].comands[idxNext].outcome;
         return idCena;
}


void motor (Game game){

    bool flag=true;
    string next= processaCena(game,game.scenes[0].id,flag);
    string last="";

    while(next!="EXIT"){
        next = processaCena(game,next,flag);
        if (last==next){
            flag=false;
        } else {
            flag=true;
        }

        last=next;
    }


}

