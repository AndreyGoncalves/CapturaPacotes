// -*- C++ -*-
/*
 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Fluxos.h
 * Author: andrey e victor
 *
 * Created on 1 de Junho de 2016, 10:05
 */

#include <iostream>
#include <string>
#include "Lista.h"
#include "Capturador.h"
#include "Fluxo.h"
#include "Pacote.h"

using namespace std;

struct Fluxo {
    in_addr src_ip;
    in_addr dst_ip;
    u_char proto;
    u_short src_port;
    u_short dst_port;
    int contador;
    
    
    inline bool operator==(const Fluxo& outro){
        
        if ( (src_ip.s_addr==outro.src_ip.s_addr ) && (dst_ip.s_addr==outro.dst_ip.s_addr) && (proto==outro.proto) && (src_port==outro.src_port) && (dst_port==outro.dst_port) ) {
            return true;
        } else {
            return false;
        }
    } 
    
    inline bool operator<(const Fluxo& outro){
        return contador>outro.contador;
    }
          
};


Fluxos::Fluxos() : cap(1518, "wlan0") {
}


Fluxos::~Fluxos(){
    
}

//captura em ordem crescente
void Fluxos::OrdemCrescente(){
    Lista<Frame> * crescente = cap.capture(0,5);
    crescente->ordenaselecao();
    
    for (crescente->inicia();not crescente->fim();){
        Frame & Pacote = crescente->proximo();
        cout << Pacote << " Tamanho do pacote: " << Pacote->get_size() << endl;
    }
    
    
    
}

void Fluxos::OrdemDecrescente(){
    Lista<Frame> * descrescente = cap.capture(10,0);
    descrescente->ordenaselecao();
    for (int y=descrescente->comprimento() - 2;y>=0;y--){
        descrescente->anexa(descrescente->remove(y));
    }
    for (descrescente->inicia(); not descrescente->fim(); ) {
        Frame & Pacote = descrescente->proximo();
        cout << Pacote << " Size: " << Pacote->get_size() << endl;
    }  
}

//de 100 em 100 bytes
void Fluxos::Conta100em100(){
    Lista<Frame> * t = cap.capture(0,10);
    t->ordenaselecao();
    int cont=0;
    int bytes=100;
    
    for(t->inicia(); not t->fim(); ) {
        Frame & Pacote = t->proximo();
        if ( Pacote->get_size() <= bytes ) {
            cont++;
        } else if ( Pacote->get_size() > bytes ) {
            cout << cont << " Pacotes ate " << bytes << " bytes." << endl;
            if ( Pacote->get_size() < (bytes+100) )
                cont=1;
            else cont=0;
            bytes=bytes+100;
        }
    }

}

//retorna a quantidade de bytes por fluxo
void Fluxos::TaxadeFluxo(){
    cap.muda_filtro("ip");
    Lista<Frame> * taxa = cap.capture(0,10);
    Lista<Fluxo> listataxa;
    
    taxa->inicia();
    while ( not taxa->fim() ){
        struct Fluxo umFluxo;
        Frame & Pacote = taxa->proximo();
        IP * ip = (IP*)Pacote->get_payload();
        umFluxo.src_ip=ip->get_src();
        umFluxo.dst_ip=ip->get_dest();
        umFluxo.proto=ip->get_proto();
        if ( ip->get_proto() == IP::proto_TCP ){
            TCP * tcp = (TCP*) ip->get_payload();
            umFluxo.src_port=tcp->get_sport();
            umFluxo.dst_port=tcp->get_dport();
        } else if ( ip->get_proto() == IP::proto_UDP ){
            UDP * udp = (UDP*) ip->get_payload();
            umFluxo.src_port=udp->get_sport();
            umFluxo.dst_port=udp->get_dport();
        }
        umFluxo.contador=Pacote->get_size();
        listataxa.inicia();
        bool verdade=0;
        while ( not listataxa.fim() ){
            int i=0;
            struct Fluxo outro = listataxa.proximo();
            if ( umFluxo == outro ){
                struct Fluxo novoFluxo = listataxa.remove(i);
                novoFluxo.contador = novoFluxo.contador + Pacote->get_size();
                listataxa.insere(novoFluxo,i);
                verdade=1;
                break;
            }
            i++;
        }
        if ( not verdade ) listataxa.anexa(umFluxo);        
    }
    
    listataxa.inicia();
    int ifluxo=1;
    while (not listataxa.fim()){
        cout << "Fluxo " << ifluxo << " :" << endl;
        struct Fluxo mostraFluxo = listataxa.proximo();
        in_addr src = mostraFluxo.src_ip;
        in_addr dest = mostraFluxo.dst_ip;
        cout << "qtd de bytes: " << mostraFluxo.contador << endl;
        cout << "protocolo: " << (int)mostraFluxo.proto << endl;
        cout << "porta de origem: " << mostraFluxo.src_port << endl;
        cout << "porta de destino: " << mostraFluxo.dst_port << endl;
        cout << "ip de origem: " << IP::addr2string(src) << endl;
        cout << "ip do destino: " << IP::addr2string(dest) << endl;
        
        ifluxo++;
    }
}

void Fluxos::ContaFluxo(){
    cap.muda_filtro("ip");
    Lista<Frame> * qtd = cap.capture(0,10);
    Lista<Fluxo> listacfluxo;
    
    
    for (qtd->inicia();not qtd->fim(); ){
        struct Fluxo umFluxo;
        Frame & Pacote = qtd->proximo();
        IP * ip = (IP*)Pacote->get_payload();
        umFluxo.src_ip=ip->get_src();
        umFluxo.dst_ip=ip->get_dest();
        umFluxo.proto=ip->get_proto();
        if ( ip->get_proto() == IP::proto_TCP ){
            TCP * tcp = (TCP*) ip->get_payload();
            umFluxo.src_port=tcp->get_sport();
            umFluxo.dst_port=tcp->get_dport();
        } else if ( ip->get_proto() == IP::proto_UDP ){
            UDP * udp = (UDP*) ip->get_payload();
            umFluxo.src_port=udp->get_sport();
            umFluxo.dst_port=udp->get_dport();
        }
        umFluxo.contador=Pacote->get_size();
        listacfluxo.inicia();
        bool existe=0;
        while ( not listacfluxo.fim() ){
            struct Fluxo outro = listacfluxo.proximo();
            if ( not (umFluxo == outro) ){
                listacfluxo.anexa(umFluxo);
                break;
            }
        }    
    }
    
    cout << listacfluxo.comprimento() << "qtd de fluxos " << endl;
}

void Fluxos::TaxaPeriodo() {
    while ( true ){
        
        Lista<Frame> * taxaperiodo = cap.capture(0,5); 
        int cont = 0;
        for (taxaperiodo->inicia();not taxaperiodo->fim(); ){
            Frame & Pacote = taxaperiodo->proximo();
            cont += Pacote->get_size();
        }
        string leitura;
        cout << "capturou:" << cont << " bytes em 5 segundos." << endl;
        cout << "Continuar = Enter // Sair = S";
        getline(cin, leitura);
        if (leitura == "s" || leitura == "S")
            break;
    }
}