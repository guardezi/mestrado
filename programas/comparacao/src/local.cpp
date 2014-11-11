#include "local.h"

local::local(){}

void local::addImg(img m){
    imgs.push_back(m);
}


vector<img> local::getImgs(){
    return imgs;
}

int local::getSize(){
    return imgs.size();
}


void local::addNeighbor(int n){
    neighbors.push_back(n);
}

vector<int> local::getNeighbors(){
    return neighbors;
}
void local::setNeighbors(vector<int> n){
    neighbors = n;
}

int local::getNeighbor(int pos){
    return neighbors.at(pos);
}

void local::setId(int i){
    id = i;
}
int local::getId(){
    return id;
}

void local::setIdReal(int i){
    idReal=i;
}
int local::getIdReal(){
    return idReal;
}
