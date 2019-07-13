#include "Common.h"
#include "Stack.h"

struct Nodo {
    int valor;
    Nodo*siguiente;
};

struct StackRepr {
    int tam;
    Nodo*tope;
};

Stack emptyS() {
    Stack s = new StackRepr;
    s->tam = 0;
    s->tope = NULL;
    return s;
}

int sizeS(Stack s) {
    return s->tam;
}

void pushS(Stack s, int x) {
    Nodo* n = new Nodo;
    n->valor = x;
    n->siguiente = s->tope;
    s->tam++;
    s->tope = n;
}

int topS(Stack s) {
    return s->tope->valor;
}

void popS(Stack s) {
    Nodo* n = s->tope;
    s->tam--;
    s->tope = n->siguiente;
    delete n;
}

void destroyS(Stack s) {
    while(s->tope!=NULL){
        Nodo* n = s->tope;
        s->tope = n->siguiente;
        delete n;
    }
    delete s;
}
