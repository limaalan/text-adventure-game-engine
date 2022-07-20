#pragma once
#include <vector>
#include <string>

using namespace std;

struct Node {

    string key;

    Node* next;
    int index;

};


struct Hash {
    // Max table indexes
    static const int MAX = 100;
    // linked lists array 
    Node* table[MAX];
};



struct Command {
    // command text
    string text;
    // result of given choice
    string result;
    // Scene ID or NONE (dead end)
    string outcome;
};

struct Scene {
    // Scene ID
    string id;
    // Scene title 
    string title;
    // Scene description 
    string description;
    // Possible choices 
    vector<Command> comands;
};

struct Game {
    // all game scenes
    vector<Scene> scenes;
    Hash hash;
    // current Scene index
    int current;
};
