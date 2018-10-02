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
 * Created on 1 de Junho de 2016, 9:35
 */

#ifndef Fluxos_H
#define Fluxos_H

#include "Lista.h"
#include <string>
#include "Capturador.h"

using namespace std;

/*Requisita ao Capturador que capture pacotes, e implementa as regras de análise dos pacotes capturados */
class Fluxos {
    
public:
    //Construtor
    Fluxos();
    
    //Destrutor
    ~Fluxos();
    
    // Primeiro requisito - apresentar de forma crescente e decrescente:
    void OrdemCrescente();
    void OrdemDecrescente();
    
    // Segundo requisito - contar pacotes transferidos classificando-os de 100 em 100 bytes
    void Conta100em100();
    
    // Terceiro requisito - apresentar taxa de bits de cada Fluxos
    void TaxadeFluxo();
    
    // Quarto requisito - Contar quantos fluxos existem na rede durante a captura
    void ContaFluxo();
    
    // Quinto requisito - Identificar os Fluxos que mais transferiram durante a captura
    //void MaioresFluxos();
    
    // Sexto requisito - Apresentar periodicamente a taxa de bits ou bytes capturados
    void TaxaPeriodo();
    
private:
    Capturador cap;
    
};

#endif /* Fluxos_H */
