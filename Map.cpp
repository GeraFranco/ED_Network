#include "Common.h"
#include "Map.h"

typedef int Priority;


Priority randomPriority() {
    return rand();
}

struct Node {
    Key clave;
    Value valor;
    Priority prioridad;
    Node* hijoIzq;
    Node* hijoDer;
};

struct MapRepr {
    Node* raiz;
    int tam;
};

Map emptyM() {
    Map m = new MapRepr;
    m->raiz = NULL;
    m->tam = 0;
    return m;
}

int sizeM(Map m) {
    return m->tam;
}

bool belongsN(Node *n, Key k, Value& v){
    if(n == NULL) {
        return false;
    }
    else {
        if(n->clave == k){
            v = n->valor;
            return true;
        }
        else{
            if(n->clave > k){
                return belongsN(n->hijoIzq,k,v);
            }
            else {
                return belongsN(n->hijoDer,k,v);
            }
        }
    }
}

bool lookupM(Map m, Key k, Value& v) {
    return belongsN(m->raiz,k,v);
}

Node* rotarAIzq(Node* n){
    if(n->hijoDer->prioridad > n->prioridad){
        Node* x = n->hijoDer;
        n->hijoDer = x->hijoIzq;
        x->hijoIzq = n;
        n = x;
    }
    return n;
}

Node* rotarADer(Node* n){
    if(n->hijoIzq->prioridad > n->prioridad){
        Node* x = n->hijoIzq;
        n->hijoIzq = x->hijoDer;
        x->hijoDer = n;
        n = x;
    }
    return n;
}

Node* nuevoNodo(Key k , Value v){
    Node* newNode = new Node;
    newNode->clave = k;
    newNode->valor = v;
    newNode->prioridad = randomPriority();
    newNode->hijoDer = NULL;
    newNode->hijoIzq = NULL;
    return newNode;
}

Node* insertNode(Node* n, Key k, Value v, Map m){
    if (n == NULL){
        n = nuevoNodo(k,v);
        m->tam++;
    }
    else {
        if(n->clave == k){
            n->valor = v;
        } else if (n->clave > k){
                 n->hijoIzq = insertNode(n->hijoIzq,k,v,m);
                 n = rotarADer(n);
        } else if(n->clave < k ){
                    n->hijoDer = insertNode(n->hijoDer,k,v,m);
                    n = rotarAIzq(n);
        }
    }
    return n;
}


void insertM(Map m, Key k, Value v) {
    m->raiz = insertNode(m->raiz,k,v,m);
}

Node* sucesor(Node* n){
//Precondicion: El nodo n tiene hijo derecho.
    Node* tmp = n->hijoDer;
    while(tmp->hijoIzq != NULL){
        tmp = tmp->hijoIzq;
    }
    return tmp;
}

bool esHoja(Node* n){
    return n->hijoDer == NULL && n->hijoIzq == NULL;
}

void reemplazarContenido(Node* n, Node* n2){
    n->clave = n2->clave;
    n->valor = n2->valor;
}

Node* removeNode(Node*& n, Key k){
    if(n == NULL) {return n;}
    else {
        if(n->clave == k){
            if(esHoja(n)){
                delete n;
                n = NULL;
            } else if(n->hijoDer != NULL && n->hijoIzq!=NULL){
                Node* sNode = sucesor(n);
                reemplazarContenido(n,sNode);
                n->hijoDer = removeNode(n->hijoDer,sNode->clave);
                delete sNode;
            } else if (n->hijoIzq != NULL && n->hijoDer == NULL){
                n = n->hijoIzq;
            } else if (n->hijoDer != NULL){
                n = n->hijoDer;
            }
        } else{
            if(n->clave > k){
                n->hijoIzq = removeNode(n->hijoIzq,k);
            }else{
                n->hijoDer = removeNode(n->hijoDer,k);
            }
        }
    }
    return n;

}

void removeM(Map m, Key k) {
    Value v;
    if(lookupM(m,k,v)){
        m->raiz = removeNode(m->raiz,k);
        m->tam--;
    }
}

void destroyNode(Node* n){
    if(n != NULL){
        destroyNode(n->hijoIzq);
        destroyNode(n->hijoDer);
        delete n;
        n = NULL;
    }
}

void destroyM(Map m) {
    destroyNode(m->raiz);
    delete m;
}
