#include <cstdlib>
#include <iostream>
#include "Capturador.h"
#include "Lista.h"
#include "Fluxo.h"

#include "Timer.h"
#include "Pacote.h"

using namespace std;

int main(int argc, char** argv) {
     
    bool sair=false;

    while ( not sair ){
        
        int opts=0;
        
        cout << endl;
        cout << "*****************************************" << endl;
	cout << "*******Analisador de rede 2,2 ***********" << endl;
        cout << "**************************.**************" << endl;
        cout << "Selecione o modo de captura:" << endl;
        cout << "1 - Capturar pacotes em ordem crescente." << endl;
        cout << "2 - Capturar pacotes em ordem decrescente." << endl;
        cout << "3 - Capturar e contar quantos pacotes foram transmitidos." << endl;
        cout << "4 - Capturar pacotes e apresentar taxa de bits/fluxo." << endl;
        cout << "5 - Contar quantidade de fluxos de uma captura." << endl;
        cout << "6 - Qual fluxo com maior transfer�ncia de dados." << endl;
        cout << "7 - Apresentar periodicamente as taxas de bps." << endl;
        cout << "0 - Para sair da interface do capturador" << endl;
        cout << "OPCAO: ";

        cin >> opts;
        
        Fluxos fluxo;
        
	if(opts==1){
		cout << "Inicio da captura..." << endl;
                fluxo.OrdemCrescente();
                cout << "Fim da captura!" << endl;
	}

	if(opts==2){
		cout << "Inicio da captura..." << endl;
                fluxo.OrdemDecrescente();
                cout << "Fim da captura!" << endl;

	}
	
	if(opts==3){
		cout << "Iniciando captura ..." << endl;
                fluxo.Conta100em100();
                cout << "Fim da captura!" << endl;
	}

	if(opts==4){
		cout << "Iniciando captura ..." << endl;
                fluxo.TaxadeFluxo();
                cout << "Fim da captura!" << endl;
	}
	
	if(opts==5){
		cout << "Iniciando captura ..." << endl;
                fluxo.ContaFluxo();
                cout << "Fim da captura!" << endl;
	}

	/*if(opts==6){
		cout << "Iniciando captura ..." << endl;
                fluxo.MaioresFluxos();
                cout << "Fim da captura!" << endl;
	}*/

	if(opts==7){
		cout << "Iniciando captura ..." << endl;
				fluxo.TaxaPeriodo();
                cout << "Fim da captura!" << endl;
	}

	if(opts==0){
		cout << "Saindo do capturador ..." << endl;
		sair=true;
	}

       if(opts!=0 && opts!=1 && opts!=2 && opts!=3 && opts!=4 && opts!=5 && opts!=6 && opts!=7)throw -1; 
    }
    
    return 0;
}
