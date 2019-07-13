#include "Common.h"
#include "Network.h"
#include "Map.h"
#include "Stack.h"

//Invariante: El tamaño de stack tiene como minimo el mismo tamaño que el map.

struct NetworkRepr {
    Map flechas;
    Stack acciones;
};


Network emptyN() {
    Network n = new NetworkRepr;
    n->flechas = emptyM();
    n->acciones = emptyS();
    return n;
}


void addN(Network net, Id id) {
    insertM(net->flechas,id,id);
    pushS(net->acciones,id);
}

bool elemN(Network net, Id id) {
    Value v;
    return lookupM(net->flechas,id,v);
}

Id representante(Network net,Id id){
    Id r;
    lookupM(net->flechas,id,r);
    while(id!=r){
        id = r;
        lookupM(net->flechas,id,r);
    }
    return r;
}

void connectN(Network net, Id id1, Id id2) {
    Id r1 = representante(net,id1);
    Id r2 = representante(net,id2);
    if(r1!=r2){
        insertM(net->flechas,r1,r2);
        pushS(net->acciones,r1);
    }
}

bool connectedN(Network net, Id id1, Id id2) {
    return representante(net,id1) == representante(net,id2);
}

void undoN(Network net) {
    Id y;
    int x = topS(net->acciones);
    lookupM(net->flechas,x,y);
    popS(net->acciones);
    if(x == y){
        removeM(net->flechas,x);
    }
    else {
        insertM(net->flechas,x,x);
    }
}

void destroyN(Network net) {
    destroyM(net->flechas);
    destroyS(net->acciones);
    delete net;
}
