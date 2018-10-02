#ifndef LISTA_H
#define LISTA_H

#include <ostream>

using namespace std;

// uma classe template para nodos da Lista ...

template <class T> struct nodo {
    T dado;
    nodo<T> * proximo;

    // um construtor para criar um nodo facilmente ...
    nodo(const T & umdado);
};

// a classe template para a Lista ...

template <class T> class Lista {
protected:
    nodo<T> *atual;

private:
    // ponteiros para o primeiro e último nodos da Lista
    nodo<T> * inicio, * ultimo;

    // a quantidade de nodos existente na Lista
    int comp;
public:
    //construtor: não precisa de parâmetros para criar uma nova Lista
    Lista();

    // construtor de cópia
    Lista(const Lista &outra);

    // destrutor
    ~Lista();

    //inicia uma iteração
    void inicia();

    // adiciona "algo" no inicio da Lista
    void adiciona(const T & algo);

    // adiciona "algo" no final da Lista
    void anexa(const T & algo);

    // adiciona "algo" em uma posição específica da Lista  
    void insere(const T & algo, int posicao);

    // remove o dado que está na "posicao" na Lista, e retorna 
    // uma cópia desse dado
    T remove(int posicao);

    // remove o dado que for equivalente a "algo", e retorna 
    // uma cópia desse dado
    T retira(const T & algo);

    //retorna uma referencia ao proximo dado da iteração, senão houver mais dados...
    //... gera uma exceção
    T& proximo();
    // estas duas operações são idênticas: retorna
    // uma referência ao dado que está na "posicao" na Lista
    T& obtem(int posicao) const;
    T& operator[](int pos) const;

    // estes operadores podem ser implementados depois
    Lista& operator=(const Lista<T> & outra);
    bool operator==(const Lista<T> & outra) const;

    bool fim() const;


    // Retorna uma referência a um dado que seja equivalente a "algo"
    //T& procura(const T &algo) const;

    Lista<T> * procura(const T & algo) const;


    // Procura todos os dados equivalentes a "algo", e os
    // anexa a "Lista". Retorna uma referência a "Lista".
    Lista<T> & procuraMuitos(const T &algo, Lista<T> & Lista) const;

    // retorna a quantidade de dados armazenados na Lista
    int comprimento() const;

    // retorna true se Lista estiver vazia
    bool vazia() const;

    // Esvazia a Lista
    void esvazia();

    // apresenta o conteúdo da Lista no stream "out"
    void escrevaSe(ostream & out) const; //const significa que nao modifica a Lista dentro dessa função//
    void escrevaSe(ostream & out, char delim) const;

    // ordena a Lista
    void ordenabolha();
    void ordenaselecao();
    void insereordenado(const T & algo);

};

template <typename T> nodo<T>::nodo(const T& umdado) {
    proximo = NULL;
    dado = umdado;
}

template <typename T> Lista<T>::Lista() {
    inicio = NULL;
    ultimo = NULL;
    comp = 0;
}

template <typename T> Lista<T>::Lista(const Lista<T> & outra) {

    inicio = NULL;
    ultimo = NULL;
    comp = 0;
    nodo<T> * algo;

    for (algo = outra.inicio; algo != NULL; algo = algo->proximo) {
        anexa(algo->dado);
    }
}

template <typename T> Lista<T>::~Lista() {
}

template <typename T> void Lista<T>::inicia() {
    if (inicio == NULL) throw -1;
    atual = inicio;
}

template <typename T> T& Lista<T>::proximo() {

    if (atual == NULL)throw -1;
    T & dado = atual->dado;
    atual = atual->proximo;
    return dado;

}

template<class T> bool Lista<T>::fim() const {

    return (atual == NULL);

}

template <typename T> void Lista<T>::adiciona(const T& algo) {

    nodo<T> * nodoadd = new nodo<T>(algo);

    nodoadd->proximo = inicio;
    inicio = nodoadd;
    if (ultimo == NULL)ultimo = nodoadd;
    comp++;
}

template <typename T> void Lista<T>::anexa(const T& algo) {
    nodo<T> *nodoanexa = new nodo<T>(algo);

    /* if(comp==0) adiciona(algo);
     else {
         comp++;
         ultimo->proximo = nodoanexa;
         ultimo=nodoanexa;
         }*/
    //ou assim
    if (comp == 0) {
        inicio = nodoanexa;
    } else {
        ultimo->proximo = nodoanexa;
    }
    ultimo = nodoanexa;
    comp++;
}

template <typename T> int Lista<T>::comprimento() const {
    return comp;
}

template <typename T> void Lista<T>::esvazia() {
    while (comp != 0) remove(0);
}

template <typename T> void Lista<T>::insere(const T& algo, int posicao) {
    int aux = 0;
    nodo<T> * nodoinsere = inicio;
    //  nodo<T> * nodoinsere2 = new nodo <T>(algo);
    if (posicao == 0) {
        adiciona(algo);
        return;
    }
    if (posicao == comp) {

        anexa(algo);
        return;
    } else {
        for (nodoinsere = inicio; aux != posicao; aux++, nodoinsere = nodoinsere->proximo);
        if (aux == posicao)
            aux--;
        nodoinsere->dado = algo;

    }


}

template <typename T> T& Lista<T>::obtem(int posicao) const {
    nodo<T> *nodoobtem;
    int aux = 0;
    if (posicao >= comp) throw -1;
    for (nodoobtem = inicio; aux < posicao; posicao--, nodoobtem = nodoobtem->proximo) {
        aux++;
    }
    return nodoobtem->dado;
}

template <typename T> T& Lista<T>::operator[](int pos) const {
    return obtem(pos);
}

/*out é um arquivo de saída*/
template <typename T> void Lista<T>::escrevaSe(ostream& out) const {
    escrevaSe(out, '\n');
    /*
    nodo<T> *nodomostra;
    for (nodomostra = inicio; nodomostra != NULL; nodomostra = nodomostra->proximo) {
        out << nodomostra->dado << endl;
    }*/
}

template <typename T> void Lista<T>::escrevaSe(ostream& out, char delim) const {

    nodo<T> *nodomostra;
    for (nodomostra = inicio; nodomostra != NULL; nodomostra = nodomostra->proximo) {
        out << nodomostra->dado << delim;
    }
}

template <typename T> T Lista<T>::remove(int posicao) {

    if (comp == 0) throw -1;
    if (posicao >= comp) throw -2;

    nodo<T> *p = inicio;
    T dado;

    if (posicao == 0) {
        dado = p->dado;
        inicio = p->proximo;
        delete p;
        comp--;
        return dado;
    }

    nodo<T> *p_anterior = inicio;
    for (int n = posicao - 1; n > 0; n--, p_anterior = p_anterior->proximo);
    for (; posicao > 0; posicao--, p = p->proximo);
    p_anterior->proximo = p->proximo;
    dado = p->dado;
    delete p;
    comp--;
    return dado;

}

template <typename T> T Lista<T>::retira(const T& algo) {

    if (comp == 0) throw -1;
    nodo<T> *nodoretira;
    int aux = 0;

    for (nodoretira = inicio; nodoretira->dado != algo; nodoretira = nodoretira->proximo) {
        aux++;
    }

    nodo<T> *p = inicio;
    T dado;

    if (aux == 0) {
        dado = p->dado;
        inicio = p->proximo;
        delete p;
        return dado;
    }

    nodo<T> *p_anterior = inicio;
    for (int n = aux - 1; n > 0; n--, p_anterior = p_anterior->proximo);
    for (; aux > 0; aux--, p = p->proximo);
    p_anterior->proximo = p->proximo;
    dado = p->dado;
    delete p;
    return dado;

}

template <typename T> bool Lista<T>::vazia() const {

    return (inicio == NULL);

}

template <typename T> void Lista<T>::ordenabolha() {

    int j, k;
    nodo <T> *ordena;
    nodo <T> *aux;


    for (j = comp; j > 0; j--) {
        ordena = inicio;
        for (k = j - 1; k > 0; k--) {
            aux = ordena->proximo;
            if (ordena->dado > aux->dado) {
                T dado = ordena->dado;
                ordena->dado = aux->dado;
                aux->dado = dado;

            }
            ordena = ordena->proximo;
        }
    }
}

template <typename T> void Lista<T>::ordenaselecao() {

    T dado;
    int posicao = comprimento();
    posicao--;
    int posicao2 = comprimento();
    nodo<T> *ordena = inicio;
    nodo<T> *aux;


    for (int j = 0; j < posicao; j++, ordena = ordena->proximo) {
        aux = ordena;
        for (int k = j + 1; k < posicao2; k++, aux = aux->proximo) {
            if (aux->proximo->dado < ordena->dado) {
                dado = ordena->dado;
                ordena->dado = aux->proximo->dado;
                aux->proximo->dado = dado;

            }

        }
    }
}

template <typename T> void Lista<T>::insereordenado(const T & algo) {

    nodo<T> * nodoinsereordenado = new nodo<T>(algo);

    if (algo < inicio->dado) {
        adiciona(algo);
        return;
    } else {
        nodo<T> * pont;
        nodo<T> * pont_ant = inicio;
        for (pont = inicio; pont->proximo != NULL; pont_ant = pont_ant->proximo) {
            pont = pont->proximo;
            if (pont->dado > algo) {
                nodoinsereordenado->proximo = pont;
                pont_ant->proximo = nodoinsereordenado;
                return;
            }
        }
        anexa(algo);

    }

}

template <typename T> Lista<T> *Lista<T>::procura(const T & algo) const {
    Lista<T> *search = new Lista<T>;
    nodo<T> *nodoprocura;
    T dado;

    for (nodoprocura = inicio; nodoprocura != NULL; nodoprocura = nodoprocura->proximo) {
        if (nodoprocura->dado == algo) 
            search->anexa(nodoprocura->dado);
    }
    return search;
}

template <typename T> Lista<T>& Lista<T>::procuraMuitos(const T& algo, Lista<T>& Lista) const {

}

template <typename T> Lista<T>& Lista<T>::operator=(const Lista<T>& outra) {
    esvazia();

    for (nodo<T> *nodo = outra.inicio; nodo != NULL; nodo = nodo->proximo)
        anexa(nodo->dado);
    return *this;

}

template <typename T> bool Lista<T>::operator==(const Lista<T>& outra) const {

    if (comp != outra.comp)
        return false;

    nodo<T> *nodo1 = inicio;
    nodo<T> *aux = outra.inicio;

    while (nodo1 != NULL) {
        if (nodo1->dado == aux->dado) {
            nodo1 = nodo1->proximo;
            aux = aux->proximo;
        } else return false;
    }
    return true;
}
#endif /* LISTA_H */