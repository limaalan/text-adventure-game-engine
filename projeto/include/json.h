#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include "structs.h"

Game readFromFile(string filename);
int hashFunction(string key);
void hashPrint(Hash h);
Hash hashCreate();
int hashFind(Hash h, string idCena);

