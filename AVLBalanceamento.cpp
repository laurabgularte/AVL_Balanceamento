#include <iostream>
#include <algorithm>
using namespace std;

struct Nodo {
    int chave;
    Nodo* esquerda;
    Nodo* direita;
    int altura;
    
    Nodo(int chave) : chave(chave), esquerda(nullptr), direita(nullptr), altura(1) {}
};

int altura(Nodo* n) {
    return (n == nullptr) ? 0 : n->altura;
}

int fatorBalanceamento(Nodo* n) {
    return (n == nullptr) ? 0 : altura(n->esquerda) - altura(n->direita);
}

Nodo* rotacionarDireita(Nodo* y) {
    Nodo* x = y->esquerda;
    Nodo* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x; 
}

Nodo* rotacionarEsquerda(Nodo* x) {
    Nodo* y = x->direita;
    Nodo* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y; 
}

Nodo* balancear(Nodo* n) {
    int balance = fatorBalanceamento(n);

    if (balance > 1 && fatorBalanceamento(n->esquerda) >= 0)
        return rotacionarDireita(n);

    if (balance < -1 && fatorBalanceamento(n->direita) <= 0)
        return rotacionarEsquerda(n);

    if (balance > 1 && fatorBalanceamento(n->esquerda) < 0) {
        n->esquerda = rotacionarEsquerda(n->esquerda);
        return rotacionarDireita(n);
    }

    if (balance < -1 && fatorBalanceamento(n->direita) > 0) {
        n->direita = rotacionarDireita(n->direita);
        return rotacionarEsquerda(n);
    }

    return n;
}

Nodo* inserir(Nodo* n, int chave) {
    if (n == nullptr)
        return new Nodo(chave);

    if (chave < n->chave)
        n->esquerda = inserir(n->esquerda, chave);
    else if (chave > n->chave)
        n->direita = inserir(n->direita, chave);
    else
        return n;

    n->altura = max(altura(n->esquerda), altura(n->direita)) + 1;

    return balancear(n);
}

bool buscar(Nodo* n, int chave) {
    if (n == nullptr)
        return false;
    if (n->chave == chave)
        return true;
    else if (chave < n->chave)
        return buscar(n->esquerda, chave);
    else
        return buscar(n->direita, chave);
}

void emOrdem(Nodo* n) {
    if (n != nullptr) {
        emOrdem(n->esquerda);
        cout << n->chave << " ";
        emOrdem(n->direita);
    }
}

int main() {
    Nodo* raiz = nullptr;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 25);
    raiz = inserir(raiz, 5);

    cout << "Árvore em ordem: ";
    emOrdem(raiz);
    cout << endl;

    int chave = 25;
    if (buscar(raiz, chave))
        cout << "Valor " << chave << " encontrado na árvore." << endl;
    else
        cout << "Valor " << chave << " não encontrado na árvore." << endl;

    chave = 15;
    if (buscar(raiz, chave))
        cout << "Valor " << chave << " encontrado na árvore." << endl;
    else
        cout << "Valor " << chave << " não encontrado na árvore." << endl;

    return 0;
}
