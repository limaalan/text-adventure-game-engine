#include "../include/json.h"

using namespace std;

int hashFunction(string key)
{
    int sum = 0;
    for (int c : key)
    {
        sum += c;
    }
    return sum % Hash::MAX;
}

void hashPrint(Hash h)
{
    cout << "Hash Table" << endl;

    for (int i = 0; i < h.MAX; i++)
    {

        cout << "[" << i << "] ";
        Node *p = h.table[i];

        while (p)
        {
            cout << "-> {" << p->key << "} ";
            p = p->next;
        }
        cout << endl;
    }
}

Hash hashCreate()
{
    Hash h;
    for (int i = 0; i < h.MAX; i++)
    {
        h.table[i] = NULL;
    }
    return h;
}

int hashFind(Hash h, string idCena)
{
    int idx = hashFunction(idCena);
    Node *p = h.table[idx];

    while (p)
    {
        if (p->key == idCena)
        {
            return p->index;
        }
        p = p->next;
    }
    return -1;
}

Game readFromFile(string fileName)
{
    ifstream infile;
    Hash hash = hashCreate();

    infile.open(fileName);
    Game game;

    if (!infile.is_open())
        cout << "File " << fileName << " not found" << endl;

    while (true)
    {
        string line;
        getline(infile, line);
        if (infile.eof())
            break;

        int pos = line.find(":");
        if (pos != -1)
        {
            Scene scene;

            // GET ID
            int inicio = line.find("\"", pos);
            int fim = line.find("\"", inicio + 1);
            int qtd = fim - inicio;
            string id = line.substr(inicio + 1, qtd - 1);
            scene.id = id;

            // GET TITLE
            getline(infile, line);
            pos = line.find(":");
            inicio = line.find("\"", pos);
            fim = line.find("\"", inicio + 1);
            qtd = fim - inicio;
            string title = line.substr(inicio + 1, qtd - 1);
            scene.title = title;

            //GET DESCRIPTION 
            getline(infile, line);
            pos = line.find(":");
            inicio = line.find("\"", pos);
            fim = line.find("\"", inicio + 1);
            qtd = fim - inicio;
            string desc = line.substr(inicio + 1, qtd - 1); // JOGA ISSO EM UMA NOVA (STRUCT) SCENE
            scene.description = desc;

            // GET COMMANDS
            getline(infile, line); // skip command lines
            getline(infile, line);

            string command = "";
            string text = "";
            string result = "";
            string nextScene = "";

            while (line.find("]") == -1) // Fills command, text, result and nextScene for every command it finds.
            {
                Command command;

                pos = line.find(":");
                if (pos != -1)
                {
                    // GET TEXT
                    inicio = line.find("\"", pos);
                    fim = line.find("\"", inicio + 1);
                    qtd = fim - inicio;
                    text = line.substr(inicio + 1, qtd - 1);
                    command.text = text;

                    // GET RESULT
                    getline(infile, line);
                    pos = line.find(":");

                    inicio = line.find("\"", pos);
                    fim = line.find("\"", inicio + 1);
                    qtd = fim - inicio;
                    result = line.substr(inicio + 1, qtd - 1);
                    command.result = result;

                    // GET NEXTSCENE
                    getline(infile, line);
                    pos = line.find(":");

                    inicio = line.find("\"", pos);
                    fim = line.find("\"", inicio + 1);
                    qtd = fim - inicio;
                    nextScene = line.substr(inicio + 1, qtd - 1);
                    command.outcome = nextScene;

                    scene.comands.push_back(command);
                }
                getline(infile, line); // Skips to next command
            }
            game.scenes.push_back(scene); // pushes created Scene to Game struct 

            Node *node = new Node;
            node->index = game.scenes.size() - 1; // hash insert
            node->key = scene.id;

            int idx = hashFunction(scene.id); // If not first scene, idx = hashfunction .
            node->next = hash.table[idx];
            hash.table[idx] = node;

        }
    }

    infile.close();
    game.hash = hash;
    return game;
}
