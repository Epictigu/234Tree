#include "knotpos.h"

knotpos::knotpos(int x, int y, int size, int value)
{
    knotpos(x, y , size, value, nullptr, nullptr);
}

knotpos::knotpos(int x, int y, int size, int value, knotpos *left, knotpos *right)
{
    parent = nullptr;
    if(x < 0 || y < 0)
        throw "Die Koordinaten x oder y dürfen nicht kleiner als 0 sein!";
    if(size < 1)
        throw "Die Größe des Knotens darf nicht kleiner als 1 sein!";
    this->x = x;
    this->y = y;
    this->size = size;
    this->value = value;

    this->leftK = left;
    this->rightK = right;
}

knotpos::knotpos(int x, int y, int size, int *values, int valueN)
{
    parent = nullptr;
    if(x < 0 || y < 0)
        throw "Die Koordinaten x oder y dürfen nicht kleiner als 0 sein!";
    if(size < 1)
        throw "Die Größe des Knotens darf nicht kleiner als 1 sein!";
    this->x = x;
    this->y = y;
    this->size = size;
    this->values = values;
    this->valueN = valueN;
}

int knotpos::getX(){
    return x;
}

int knotpos::getY(){
    return y;
}

int knotpos::getSize(){
    return size;
}

int knotpos::getValue(){
    return value;
}

int *knotpos::getValues(){
    return values;
}

knotpos* knotpos::getLeft(){
    return leftK;
}

knotpos* knotpos::getRight(){
    return rightK;
}

void knotpos::setLeft(knotpos *k){
    leftK = k;
}

void knotpos::setRight(knotpos *k){
    rightK = k;
}

void knotpos::setParent(knotpos *k){
    parent = k;
}
