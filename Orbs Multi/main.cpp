#include <winsock2.h>
#include <windows.h>
#include<iostream>
#include<graphics.h>
#include<math.h>
#include<ctime>


#include "globais.h"
#include "dodge.h"
#include "rede.h"

#define PI 3.14159265
#define ESC        27
#define MaxX     1360
#define MaxY      700
#define MaxBolas   10

int porta = 0;
int scoreAdv;

char ip[16];
char buffer[100];

Rede comm;


using namespace std;


bool EscolheModoDeJogo()
{
	cout << "Bem vindo ao Orbs Multiplayer!!!.\n Voce deseja hospedar uma partida (H) ou entrar em uma partida (E) ?\n";
	char opcao;
	while(opcao!='H' && opcao!='E')
	{
		cin >> opcao;
		if(opcao!='H' && opcao!='E')
		{
			cout << "Favor informar uma das opcoes, em MAIUSCULO!!!.\n";
		}
	}
	system("cls");
	if(opcao =='H')
		return true;//true= ser host
	else
		return false;//false= dar join
		
}

bool IsClient(){
	if(comm.clienteOuServidor == "cliente"){
		return true;
	}else{
		return false;
	}
}

bool TrataScoreAdv(){
	bool recebi;
	char c;
	char temp[2];
	
	if(IsClient()){
		recebi = comm.RecebeDoServer();
	}else{
		recebi = comm.RecebeDoClient();
	}
	
	if(recebi){
		c = comm.pacote[0];
		int i = 0;
		strcpy(buffer,"");
		
		while(c != '\0'){
				temp[0] = c;
				temp[1] = '\0';
				strcat(buffer,temp);
				
				i++;
				c = comm.pacote[i];
		}
		scoreAdv = atoi(buffer);
		return true;
	}else{
		return false;
	}
	
	
}

int main()  { 
  comm.WinSockInit();
  comm.FlagsInit();
  
 if(EscolheModoDeJogo())
	{
		//true= ser host
		cout << "Modo Host: Informe uma porta TCP para ser utilizada.\n";
		while(porta<1024||porta>65535)
		{
			cin >> porta;
			if(porta<1024||porta>65535)
			{
				cout << "Insira um valor entre 1024 e 65535\n";
			}
			else if(!comm.ServerInit(porta))
			{
				cout << "Erro ao iniciar servidor na porta informada. Tente outra porta.\n";
				porta=0;
			}			
		}
		cout << "Esperando outro jogador se conectar pela porta "<< porta <<"...\n";
		while(!comm.AceitaConexaoClient());
		cout << "Cliente conectado. Começando partida...";
	}
	else
	{
		//false= dar join
		cout << "Modo Cliente: ";
		bool informacoesvalidas=false;
		while(!informacoesvalidas)
		{
			cout << "Informe o IP da máquina host.\n";
			cin >> ip;
			cout << "Informe a porta TCP da máquina host para se conectar.\n";
			cin >> porta;
			if(!comm.ClientInit(ip,porta))
			{
				cout << "Configuração incorreta. Favor preencher novamente.\n\n";
			}
			else
				informacoesvalidas=true;
		}
		cout << "Tentando se conectar ao servidor "<< ip <<" na porta "<< porta <<"...\n";
		bool conectou=false;
		while(!conectou)
		{
			if(comm.ConectaServer())
				conectou=true;
			else
			{
				comm.WinSockInit();
				comm.ClientInit(ip,porta);
				delay(10000);
				cout<<"Tentando novamente...\n";
			}
		}
		cout << "Conectado. Começando partida...";
	}
	delay(100);
  
  int pg, i;
  
  initwindow(MaxX, MaxY);	
  setbkcolor(RGB(230, 230, 220));
 
  	  IniciaDados();
  	  CarregaFundo();
 	  CarregaBolas();
 	  CarregaHeitor();
	  while(MaxVidas > 0) {
	    if (pg == 1) pg = 2; else pg=1;
	    setactivepage(pg);
	    cleardevice();
	    DesenhaFundo();
	    
	    DesenhaHeitor();
	    DesenhaBolas();
	    
	    MoveBolas();
	    
	    setcolor(0);
	    
	    Score();
	    setvisualpage(pg);
	    
	    CalcColH();
		CalcColB();
	    
		VerColH();
	    VerColB();
	    
	    DetectTecla();
			
		FimJogo();
		
	    delay(20);
	  }
	  if(comm.clienteOuServidor == "cliente"){
	  	comm.EnviaParaOServer(array);
	  }else{
	  	comm.EnviaParaOClient(array);
	  }
	  cleardevice();
	  DesenhaFundo();
	  outtextxy(450,300, "Aguardando Adversario...");
	  while(!TrataScoreAdv()){
	  	delay(1000);
	  }
	  while(tecla != ESC){
	  	if (pg == 1) pg = 2; else pg=1;
	    setactivepage(pg);
	    cleardevice();
	    DesenhaFundo();
	  	outtextxy(200, 200, "Score Final Adversario: ");
	  	outtextxy(800, 200, buffer);
	  	
	  	outtextxy(200,400, "Seu Score Final: ");
	  	outtextxy(800,400, array);
	  	
	  	if(scoreAdv > intScore){
	  		outtextxy(300,600, "Voce Perdeu!!!");
		  }else if(scoreAdv == intScore){
		  	outtextxy(300,600, "Empate!!!");
		  }else{
		  	outtextxy(300,600, "Voce Ganhou!!!");
		  }
	  	
	  	setvisualpage(pg);
	  	DetectTecla();
	  	delay(20);
	  }
	  
  comm.FechaConexaoClient();
  comm.EncerraWinSock();
  closegraph();	
  return 0; 
	  
}








