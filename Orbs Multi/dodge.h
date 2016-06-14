#include<iostream>
#include<graphics.h>
#include<math.h>
#include<ctime>
#include "globais.h"


#define PI 3.14159265
#define ESC        27
#define MaxBolas   10


double d[24];
char array[10];
char array2[10];



struct TSprites {
	void *sprite;
	void *mascara;
};

struct TVidas{
	int x0,y0;
	int r;
	int x,y;	
};

struct TBolas {
  int x0, y0;
  int r;
  float ang;
  int passo;
  int d;
  int x, y;
  int move;
};

struct THeitor{
	int x0,y0;
	int r;
	int passo;
	int d;
	int x,y;
};

TBolas Bolas[MaxBolas];
THeitor Heitor[1];
TSprites Sprites[MaxBolas];

double ColH[MaxBolas];

void DesenhaFundo();
void IniciaDados();
void MoveBolas();
void DesenhaHeitor();
void DesenhaBolas();
void Score();
void CalcColB();
void CalcColH();
void VerColH();
void VerColB();
void FimJogo();
void DetectTecla();

void *R;
void *RH, *RHM;

void IniciaDados() {
	
  //Heitor
  Heitor[0].x0 = 680;
  Heitor[0].y0 = 320;
  Heitor[0].x = Heitor[0].x0;
  Heitor[0].y = Heitor[0].y0;
  Heitor[0].r = 30;
  Heitor[0].passo = 30;
	
  //bola vertical cima	
  Bolas[0].x0    = 680;
  Bolas[0].y0    = 110;
  Bolas[0].x     = Bolas[0].x0;
  Bolas[0].y     = Bolas[0].y0;
  Bolas[0].r     = 50;
  Bolas[0].passo = 8;
  Bolas[0].d     = 0;
  Bolas[0].ang   = 90;
  Bolas[0].move  = 0;
  
  //bola vertical baixo
  Bolas[1].x0    = 680;
  Bolas[1].y0    = 505;
  Bolas[1].x     = Bolas[1].x0;
  Bolas[1].y     = Bolas[1].y0;
  Bolas[1].r     = 50;
  Bolas[1].passo = 8;
  Bolas[1].d     = 0;
  Bolas[1].ang   = 90;
  Bolas[1].move  = 0;
  
  //bola horizontal esquerda
  Bolas[2].x0    = 70;
  Bolas[2].y0    = 300;
  Bolas[2].x     = Bolas[2].x0;
  Bolas[2].y     = Bolas[2].y0;
  Bolas[2].r     = 50;
  Bolas[2].passo = 8;
  Bolas[2].d     = 0;
  Bolas[2].ang   = 0;
  Bolas[2].move  = 0;
  
  //bola horizontal direita
  Bolas[3].x0    = 1290;
  Bolas[3].y0    = 300;
  Bolas[3].x     = Bolas[3].x0;
  Bolas[3].y     = Bolas[3].y0;
  Bolas[3].r     = 50;
  Bolas[3].passo = 8;
  Bolas[3].d     = 0;
  Bolas[3].ang   = 0;
  Bolas[3].move  = 0;
  
  //bola diagonal superior esquerda
  Bolas[4].x0    = 105;
  Bolas[4].y0    = 110;
  Bolas[4].x     = Bolas[4].x0;
  Bolas[4].y     = Bolas[4].y0;
  Bolas[4].r     = 50;
  Bolas[4].passo = 8;
  Bolas[4].d     = 0;
  Bolas[4].ang   = 165;
  Bolas[4].move  = 0;
  
  //bola diagonal inferior direita
  Bolas[5].x0    = 1280;
  Bolas[5].y0    = 500;
  Bolas[5].x     = Bolas[5].x0;
  Bolas[5].y     = Bolas[5].y0;
  Bolas[5].r     = 50;
  Bolas[5].passo = 8;
  Bolas[5].d     = 0;
  Bolas[5].ang   = 156;
  Bolas[5].move  = 0;
  
  //bola diagonal superior direita
  Bolas[6].x0    = 1280;
  Bolas[6].y0    = 110;
  Bolas[6].x     = Bolas[6].x0;
  Bolas[6].y     = Bolas[6].y0;
  Bolas[6].r     = 50;
  Bolas[6].passo = 8;
  Bolas[6].d     = 0;
  Bolas[6].ang   = 15;
  Bolas[6].move  = 0;
  
  //bola diagonal inferior esquerda
  Bolas[7].x0    = 90;
  Bolas[7].y0    = 500;
  Bolas[7].x     = Bolas[7].x0;
  Bolas[7].y     = Bolas[7].y0;
  Bolas[7].r     = 50;
  Bolas[7].passo = 8;
  Bolas[7].d     = 0;
  Bolas[7].ang   = 370;
  Bolas[7].move  = 0;
  
  //Bola horizontal Inferior
  Bolas[8].x0    = 90;
  Bolas[8].y0    = 500;
  Bolas[8].x     = Bolas[8].x0;
  Bolas[8].y     = Bolas[8].y0;
  Bolas[8].r     = 50;
  Bolas[8].passo = 8;
  Bolas[8].d     = 0;
  Bolas[8].ang   = 180;
  Bolas[8].move  = 0;
  
  //Bola horizontal Superior
  Bolas[9].x0    = 1280;
  Bolas[9].y0    = 110;
  Bolas[9].x     = Bolas[9].x0;
  Bolas[9].y     = Bolas[9].y0;
  Bolas[9].r     = 50;
  Bolas[9].passo = 8;
  Bolas[9].d     = 0;
  Bolas[9].ang   = 180;
  Bolas[9].move  = 0;
  
}

void CarregaFundo(){
	//carrega o Fundo
  int tam = imagesize(0, 0, 1360, 650);
  R = malloc(tam);
  readimagefile("game.bmp", 0, 0, 1360, 600);
  getimage(0, 0, 1360, 600, R);
  settextstyle(4, 0, 4);	
}

void CarregaBolas(){
	//carrega os sprites da spritesheet e a mascara
  int verSprites;
  int tamSprites = imagesize(0, 0, 3224, 104);
  int tamMascara = imagesize(0, 0, 104, 104);
  for(verSprites = 0; verSprites < MaxBolas; verSprites++){
  	Sprites[verSprites].sprite = malloc(tamSprites);
  	Sprites[verSprites].mascara = malloc(tamMascara);
  	readimagefile("objetos.bmp", 0, 0, 3224, 104);
  	getimage(104*verSprites, 0, 104 + 104*verSprites, 104, Sprites[verSprites].sprite);
  	readimagefile("mascara.bmp", 0, 0, 104, 104);
  	getimage(0, 0, 104, 104, Sprites[verSprites].mascara);
  }
}

void CarregaHeitor(){
  int verHeitor;
  int tamHeitor = imagesize(0, 0, 60, 60);
  int tamMascaraH = imagesize(0, 0, 60, 60);
  	RH = malloc(tamHeitor);
  	RHM = malloc(tamMascaraH);
  	readimagefile("naveesquerda.bmp", 0, 0, 60, 60);
  	getimage(0, 0, 60, 60, RH);
  	readimagefile("naveesquerdamask.bmp", 0, 0, 60, 60);
  	getimage(0, 0, 60, 60, RHM);
	
	
}


void DesenhaFundo() { // exibe o fundo na tela
	putimage(0, 0, R, AND_PUT);
}


void CalcColB(){ // calcula a colisao entre as bolas
	//colisao com a Bola 0
    d[0] = sqrt(pow(Bolas[0].x - Bolas[2].x, 2) + pow(Bolas[0].y - Bolas[2].y, 2));
    d[1] = sqrt(pow(Bolas[0].x - Bolas[3].x, 2) + pow(Bolas[0].y - Bolas[3].y, 2));
    d[2] = sqrt(pow(Bolas[0].x - Bolas[4].x, 2) + pow(Bolas[0].y - Bolas[4].y, 2));
    d[3] = sqrt(pow(Bolas[0].x - Bolas[5].x, 2) + pow(Bolas[0].y - Bolas[5].y, 2));
    d[4] = sqrt(pow(Bolas[0].x - Bolas[6].x, 2) + pow(Bolas[0].y - Bolas[6].y, 2));
    d[5] = sqrt(pow(Bolas[0].x - Bolas[7].x, 2) + pow(Bolas[0].y - Bolas[7].y, 2));
    
    // colisao com a bola 1
    d[6] = sqrt(pow(Bolas[1].x - Bolas[2].x, 2) + pow(Bolas[1].y - Bolas[2].y, 2));
    d[7] = sqrt(pow(Bolas[1].x - Bolas[3].x, 2) + pow(Bolas[1].y - Bolas[3].y, 2));
    d[8] = sqrt(pow(Bolas[1].x - Bolas[4].x, 2) + pow(Bolas[1].y - Bolas[4].y, 2));
    d[9] = sqrt(pow(Bolas[1].x - Bolas[5].x, 2) + pow(Bolas[1].y - Bolas[5].y, 2));
    d[10] = sqrt(pow(Bolas[1].x - Bolas[6].x, 2) + pow(Bolas[1].y - Bolas[6].y, 2));
    d[11] = sqrt(pow(Bolas[1].x - Bolas[7].x, 2) + pow(Bolas[1].y - Bolas[7].y, 2));
    
    // colisao com a bola 2
    d[12] = sqrt(pow(Bolas[2].x - Bolas[4].x, 2) + pow(Bolas[2].y - Bolas[4].y, 2));
    d[13] = sqrt(pow(Bolas[2].x - Bolas[5].x, 2) + pow(Bolas[2].y - Bolas[5].y, 2));
    d[14] = sqrt(pow(Bolas[2].x - Bolas[6].x, 2) + pow(Bolas[2].y - Bolas[6].y, 2));
    d[15] = sqrt(pow(Bolas[2].x - Bolas[7].x, 2) + pow(Bolas[2].y - Bolas[7].y, 2));
    
    // colisao com a bola 3
    d[16] = sqrt(pow(Bolas[3].x - Bolas[4].x, 2) + pow(Bolas[3].y - Bolas[4].y, 2));
    d[17] = sqrt(pow(Bolas[3].x - Bolas[5].x, 2) + pow(Bolas[3].y - Bolas[5].y, 2));
    d[18] = sqrt(pow(Bolas[3].x - Bolas[6].x, 2) + pow(Bolas[3].y - Bolas[6].y, 2));
    d[19] = sqrt(pow(Bolas[3].x - Bolas[7].x, 2) + pow(Bolas[3].y - Bolas[7].y, 2));
    
    // colisao com a bola 4
    d[20] = sqrt(pow(Bolas[4].x - Bolas[6].x, 2) + pow(Bolas[4].y - Bolas[6].y, 2));
    d[21] = sqrt(pow(Bolas[4].x - Bolas[7].x, 2) + pow(Bolas[4].y - Bolas[7].y, 2));
    
    // colisao com a bola 5
    d[22] = sqrt(pow(Bolas[5].x - Bolas[6].x, 2) + pow(Bolas[5].y - Bolas[6].y, 2));
    d[23] = sqrt(pow(Bolas[5].x - Bolas[7].x, 2) + pow(Bolas[5].y - Bolas[7].y, 2));  
	
}

void CalcColH(){ //calcula a colisao das Bolas com o heitor
	int i;
	for(i = 0; i < MaxBolas; i++){
		ColH[i] = sqrt(pow(Heitor[0].x - Bolas[i].x, 2) + pow(Heitor[0].y - Bolas[i].y, 2));
	}
}

void VerColB(){
	//verifica a colisao entre as bolas de difetentes linhas, menos as horizontais superior e inferior
    if (d[0] <= Bolas[0].r + Bolas[2].r){
      Bolas[0].passo = -Bolas[0].passo;
      Bolas[2].passo = -Bolas[2].passo;
    }else if (d[1] <= Bolas[0].r + Bolas[3].r){
      Bolas[0].passo = -Bolas[0].passo;
      Bolas[3].passo = -Bolas[3].passo;
  	}else if (d[2] <= Bolas[0].r + Bolas[4].r){
      Bolas[0].passo = -Bolas[0].passo;
      Bolas[4].passo = -Bolas[4].passo;
    }else if (d[3] <= Bolas[0].r + Bolas[5].r){
      Bolas[0].passo = -Bolas[0].passo;
      Bolas[5].passo = -Bolas[5].passo;
	}else if (d[4] <= Bolas[0].r + Bolas[6].r){
      Bolas[0].passo = -Bolas[0].passo;
      Bolas[6].passo = -Bolas[6].passo;
	}else if (d[5] <= Bolas[0].r + Bolas[7].r){
      Bolas[0].passo = -Bolas[0].passo;
      Bolas[7].passo = -Bolas[7].passo;
	}else if (d[6] <= Bolas[1].r + Bolas[2].r){
      Bolas[1].passo = -Bolas[1].passo;
      Bolas[2].passo = -Bolas[2].passo;
	}else if (d[7] <= Bolas[1].r + Bolas[3].r){
      Bolas[1].passo = -Bolas[1].passo;
      Bolas[3].passo = -Bolas[3].passo;
	}else if (d[8] <= Bolas[1].r + Bolas[4].r){
      Bolas[1].passo = -Bolas[1].passo;
      Bolas[4].passo = -Bolas[4].passo;
	}else if (d[9] <= Bolas[1].r + Bolas[5].r){
      Bolas[1].passo = -Bolas[1].passo;
      Bolas[5].passo = -Bolas[5].passo;
	}else if (d[10] <= Bolas[1].r + Bolas[6].r){
      Bolas[1].passo = -Bolas[1].passo;
      Bolas[6].passo = -Bolas[6].passo;
	}else if (d[11] <= Bolas[1].r + Bolas[7].r){
      Bolas[1].passo = -Bolas[1].passo;
      Bolas[7].passo = -Bolas[7].passo;
	}else if (d[12] <= Bolas[2].r + Bolas[4].r){
      Bolas[2].passo = -Bolas[2].passo;
      Bolas[4].passo = -Bolas[4].passo;
	}else if (d[13] <= Bolas[2].r + Bolas[5].r){
      Bolas[2].passo = -Bolas[2].passo;
      Bolas[5].passo = -Bolas[5].passo;
	}else if (d[14] <= Bolas[2].r + Bolas[6].r){
      Bolas[2].passo = -Bolas[2].passo;
      Bolas[6].passo = -Bolas[6].passo;
	}else if (d[15] <= Bolas[2].r + Bolas[7].r){
      Bolas[2].passo = -Bolas[2].passo;
      Bolas[7].passo = -Bolas[7].passo;
	}else if (d[16] <= Bolas[3].r + Bolas[4].r){
      Bolas[3].passo = -Bolas[3].passo;
      Bolas[4].passo = -Bolas[4].passo;
	}else if (d[17] <= Bolas[3].r + Bolas[5].r){
      Bolas[3].passo = -Bolas[3].passo;
      Bolas[5].passo = -Bolas[5].passo;
	}else if (d[18] <= Bolas[3].r + Bolas[6].r){
      Bolas[3].passo = -Bolas[3].passo;
      Bolas[6].passo = -Bolas[6].passo;
	}else if (d[19] <= Bolas[3].r + Bolas[7].r){
      Bolas[3].passo = -Bolas[3].passo;
      Bolas[7].passo = -Bolas[7].passo;
	}else if (d[20] <= Bolas[4].r + Bolas[6].r){
      Bolas[4].passo = -Bolas[4].passo;
      Bolas[6].passo = -Bolas[6].passo;
	}else if (d[21] <= Bolas[4].r + Bolas[7].r){
      Bolas[4].passo = -Bolas[4].passo;
      Bolas[7].passo = -Bolas[7].passo;
	}else if (d[22] <= Bolas[5].r + Bolas[6].r){
      Bolas[5].passo = -Bolas[5].passo;
      Bolas[6].passo = -Bolas[6].passo;
  	}else if (d[23] <= Bolas[5].r + Bolas[7].r){
      Bolas[5].passo = -Bolas[5].passo;
      Bolas[7].passo = -Bolas[7].passo;
  	}
}

void VerColH(){ // verifica se a colisao com o Jogador Ocorreu
	int i;
	for(i = 0; i < MaxBolas; i++){
		if(ColH[i] <= Heitor[0].r + Bolas[i].r){
			Bolas[i].d = 0;
			if(MaxVidas > 0){
				MaxVidas -= 1;
			}
		}
	}
	
}

void DetectTecla(){
	 if (kbhit()) {
      tecla = getch();
      if(MaxVidas > 0){
      	if (tecla == ' ') {
        	Bolas[0].move = !Bolas[0].move;
        	Bolas[1].move = !Bolas[1].move;
        	Bolas[2].move = !Bolas[2].move;
        	Bolas[3].move = !Bolas[3].move;
        	Bolas[4].move = !Bolas[4].move;
        	Bolas[5].move = !Bolas[5].move;
        	Bolas[6].move = !Bolas[6].move;
        	Bolas[7].move = !Bolas[7].move;
        	Bolas[8].move = !Bolas[8].move;
        	Bolas[9].move = !Bolas[9].move;
      	}
  	
      if(Bolas[0].move != 0){
      	if(GetKeyState(VK_UP)&0x80){
      		if (Heitor[0].y <= 50 + Heitor[0].r){
      			
      		 }else{
      		 	Heitor[0].y = Heitor[0].y - Heitor[0].passo;
			 }
	  	}
	  	if(GetKeyState(VK_DOWN)&0x80){
	  		if (Heitor[0].y >= 550 - Heitor[0].r){
      			
      		 }else{
      		 	Heitor[0].y = Heitor[0].y + Heitor[0].passo;
			 }
	  	 }
	  	if(GetKeyState(VK_LEFT)&0x80){
	  		if (Heitor[0].x <= 20 + Heitor[0].r){
	  			
	  		}else{
	  			Heitor[0].x = Heitor[0].x - Heitor[0].passo;
	  		  }
	  	}
	  	if(GetKeyState(VK_RIGHT)&0x80){
	  		if ( Heitor[0].x >= 1350 - Heitor[0].r){
	  			
	  		}else{
	  			Heitor[0].x = Heitor[0].x + Heitor[0].passo;
	  		}
	  	 }
	    }	
      }
    }
}

void Score(){ // calcula e exibe a área de dados na tela
	if(MaxVidas > 0 && Bolas[0].move != 0){
		score = score + 0.1;
	}
	
	intScore = score;
	itoa(intScore, array, 10);
	outtextxy(50, 620, "Score:");
	outtextxy(200, 620, array);
	
	sprintf(array2, "%d", MaxVidas);
    outtextxy(1100, 620, "Vidas:");
    outtextxy(1250, 620 , array2);
	
	if(MaxVidas != 0){
		if(Bolas[0].move == 0){
			outtextxy(555, 660, "Space = Start");
		}else{
			outtextxy(555, 660, "Space = Pause");
		}
		
	}			
}

void MoveBolas() { // move as bolas pela tela de forma que rebatam nos cantos da tela
  int i;
  for(i = 0; i <= MaxBolas; i++) {
    if (Bolas[i].move) {
      Bolas[i].d = Bolas[i].d + Bolas[i].passo;
      Bolas[i].x = Bolas[i].x0 + Bolas[i].d * cos(Bolas[i].ang*PI/180);
      Bolas[i].y = Bolas[i].y0 - Bolas[i].d * sin(Bolas[i].ang*PI/180);
      if (Bolas[i].x <= 10 + Bolas[i].r || Bolas[i].x >= 1360 - Bolas[i].r) 
        Bolas[i].passo = -Bolas[i].passo;
      if (Bolas[i].y <= 50 + Bolas[i].r || Bolas[i].y >= 560 - Bolas[i].r) 
        Bolas[i].passo = -Bolas[i].passo;
    }
  }
}

void DesenhaBolas() { 	// desenha as bolas na tela
  int i;
  for(i = 0; i < MaxBolas; i++) {
    fillellipse(Bolas[i].x, Bolas[i].y, Bolas[i].r, Bolas[i].r);
    putimage(Bolas[i].x - Bolas[i].r, Bolas[i].y - Bolas[i].r, Sprites[i].mascara, AND_PUT);
    putimage(Bolas[i].x - Bolas[i].r, Bolas[i].y - Bolas[i].r, Sprites[i].sprite, OR_PUT);
  }
}

void DesenhaHeitor(){	//desenha o jogador na tela
	int i;
	setfillstyle(1,RGB(0,0,0));
	for(i = 0; i < 1; i++){
		fillellipse(Heitor[i].x, Heitor[i].y, Heitor[i].r, Heitor[i].r);
		putimage(Heitor[i].x - Heitor[i].r, Heitor[i].y - Heitor[i].r, RHM, AND_PUT);
		putimage(Heitor[i].x - Heitor[i].r, Heitor[i].y - Heitor[i].r, RH, OR_PUT);
	}
}

void FimJogo(){
	if(MaxVidas == 0){		//Pausa o jogo no fim
		Bolas[0].move = 0;
		Bolas[1].move = 0;
		Bolas[2].move = 0;
		Bolas[3].move = 0;
		Bolas[4].move = 0;
		Bolas[5].move = 0;
		Bolas[6].move = 0;
		Bolas[7].move = 0;
		Bolas[8].move = 0;
		Bolas[9].move = 0;
		outtextxy(555,660,"Fim de Jogo");
	//	outtextxy(300,330, "PRESSIONE ESPAÇO PARA REINICIAR");
	//	Score();
	//	tecla = getch();
	//	if (tecla == ' '){
	//		MaxVidas = 4;
	//		score = 0;
	//		IniciaDados();
	//	}
	}
}


