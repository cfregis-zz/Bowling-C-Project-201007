#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"

/**************************** Definições de Macros ****************************/

#define CUBO     "cubo.wrl"  /* Nome do arquivo (diretório corrente) */
#define PINOS    "pinos.wrl"
#define FITA    "fita.wrl"
#define BOLA     "bola.wrl"
#define PAREDE     "cenario.wrl"
#define REMOVIDO -1 //utilizado para lista de pinos: STATUS
#define DERRUBADO 0
#define FIXO 1

double transBolaX=0, transBolaY=0,transPinoX=-10,transPinoY=0,transPinoZ=2.3,retaX,retaY;
tPtrPonto pPinos,pPista,pPiso ,pBola,pCenario,pHaste,pFita;
tPtrFace fPinos,fPista,fPiso ,fBola,fCenario,fHaste,fFita;
tPino ListaDePinos[10];
//Variaveis globais
int i;
int angX = 0, angY = 0,angZ = 0;//rotação
int time=50,jogadas=0,turn=1,pinosDerrubados=0,pontos=0,placargeral=0 ;//controle do programa
int fimMouseX,fimMouseY,initMouseX,initMouseY,dX,dY,transMouseX,transMouseY;//colisoes
char pino,cena,*texto; //exibir textos
char textpontos[50],textRodada[50];

// Desenha um texto na janela GLUT
void Texto(){
     int i;
     glColor3f(0,0,0);     
     // Posição onde o textpontos será colocado
     glRasterPos3d(1, 3, -7.0);
      for(i=0; textpontos[i] != '\0'; ++i)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,textpontos[i]);
}

void Texto2(){
     int i;
     glColor3f(0,0,0);     
     // Posição onde o textpontos será colocado
     glRasterPos3d(1, -8, -7.0);
      for(i=0; textRodada[i] != '\0'; ++i)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,textRodada[i]);
}
void piso(void){
    glPushMatrix(); 
      glScaled(8,4,0);
      gera(fPista, 0, 0.2, 0.25);
    glPopMatrix();
    glPushMatrix();
      glScaled(10,10,0.00);
      glTranslatef(-0.3,0,0.3);
      gera(fPiso, 1, 0.2, 0.25);
      glTranslatef(0,0,0.5);
      gera(fPista, 1, 0.2, 0.25);
    glPopMatrix();
    
     }

void piso2(void){
    glPushMatrix(); 
    glScalef(7,2,0.25);
    gera(fPista, 0.7, 0.5, 0.35);
    glPopMatrix();
    }


void pista(void){
    glPushMatrix();
     glRotated(90, 0, 1, 0);
     glRotated(90, 0, 0, 1);
     glTranslated(0,10,0);
     glScaled(10,10,10);
     gera(fCenario, 0.5,0.5,0.5);
    glPopMatrix();
     
    glPushMatrix(); 
    glScalef(7,0.25,0.5);
    glPushMatrix();
      glTranslatef(0,12,0);
      gera(fPista, 0, 0, 0.7);
    glPopMatrix();
    
    glPushMatrix();
      glTranslatef(0,-12,0);
      gera(fPista, 0, 0, 0.7);
    glPopMatrix();
    glPopMatrix();
    } 
      
void pinos(void){
    glPushMatrix();
      glScalef(0.5,0.5,0.5); 
      glTranslatef(transPinoX,0,2.3);
      //lista pino 1
      ListaDePinos[0].x = transPinoX;
      ListaDePinos[0].y = transPinoY;
      if(ListaDePinos[0].status!=REMOVIDO&&ListaDePinos[0].status!=DERRUBADO)
        glCallList(1);

        glTranslatef(-1,0,0);
        glPushMatrix();
        //lista pino 2
        ListaDePinos[1].x = transPinoX-1;
        ListaDePinos[1].y = transPinoY+0.6; 
          glTranslatef(0,0.6,0);
          if(ListaDePinos[1].status!=REMOVIDO&&ListaDePinos[1].status!=DERRUBADO)
             glCallList(1);
        glPopMatrix();
        //lista pino 3
        glPushMatrix();
          ListaDePinos[2].x = transPinoX-1;
          ListaDePinos[2].y = transPinoY-0.6; 
          glTranslatef(0,-0.6,0);
          if(ListaDePinos[2].status!=REMOVIDO&&ListaDePinos[2].status!=DERRUBADO)glCallList(1);
        glPopMatrix();
        glTranslatef(-1,0,0);
        //lista pino 4
        ListaDePinos[3].x = transPinoX-2;
        ListaDePinos[3].y = transPinoY;
        if(ListaDePinos[3].status!=REMOVIDO&&ListaDePinos[3].status!=DERRUBADO)glCallList(1);
        glPushMatrix();
          //lista pino 5
          ListaDePinos[4].x = transPinoX-2;
          ListaDePinos[4].y = transPinoY -1.2;
          glTranslatef(0,-1.2,0);
          if(ListaDePinos[4].status!=REMOVIDO&&ListaDePinos[4].status!=DERRUBADO) glCallList(1);
        glPopMatrix();
        glPushMatrix();
          //lista pino 6
          ListaDePinos[5].x = transPinoX-2;
          ListaDePinos[5].y = transPinoY +1.2;
          glTranslatef(0,1.2,0);
          if(ListaDePinos[5].status!=REMOVIDO&&ListaDePinos[5].status!=DERRUBADO)glCallList(1);
        glPopMatrix();
        glTranslatef(-1,0,0);
        glPushMatrix();
        //lista pino 7 e 9
        ListaDePinos[6].x = transPinoX-3;
        ListaDePinos[6].y = transPinoY +0.6;
        ListaDePinos[8].x = transPinoX-3;
        ListaDePinos[8].y = transPinoY +1.2+0.6;
          glTranslatef(0,0.6,0);
          if(ListaDePinos[6].status!=REMOVIDO&&ListaDePinos[6].status!=DERRUBADO) glCallList(1);
          glTranslatef(0,1.2,0);
          if(ListaDePinos[8].status!=REMOVIDO&&ListaDePinos[8].status!=DERRUBADO) glCallList(1);
        glPopMatrix();
        //lista pino 8 e 10
        glPushMatrix();
        ListaDePinos[7].x = transPinoX-3;
        ListaDePinos[7].y = transPinoY -0.6;
        ListaDePinos[9].x = transPinoX-3;
        ListaDePinos[9].y = transPinoY -1.2-0.6;
        glTranslatef(0,-0.6,0);
          if(ListaDePinos[7].status!=REMOVIDO&&ListaDePinos[7].status!=DERRUBADO)glCallList(1);
          glTranslatef(0,-1.2,0);
          if(ListaDePinos[9].status!=REMOVIDO&&ListaDePinos[9].status!=DERRUBADO)glCallList(1);
        glPopMatrix();
        
    glPopMatrix();
     }
void bola(void){
    glPushMatrix(); 
    glTranslatef(7,0,0.75);
    glTranslatef(transBolaX,transBolaY,0);
    glScalef(0.5,0.5,0.5);
    glColor3d(0,0,0);
    gera(fBola, 0,0,0);
    glPopMatrix(); 
    }
void retaDirecao(void){
     glColor3f(0.0f, 0.5f, 1.0f);
     glBegin(GL_LINES);
     glVertex3f(7,0,0.75); 
     glVertex3f(retaX,retaY,0.75);
     glEnd();
}
  
   
     
void DefineCenario (void){
     piso();
     piso2();
     pista();
     bola();
     pinos();
}
    
void Desenha(){    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDrawBuffer(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    //ajuste do angulo de visualizacao
    glTranslated(0, 0, -14);
    glRotated(90, 1, 0, 0);
    glRotated(90, 0, 0, 1);
    glRotated(18, 0, 1, 0);
    
    glRotated(angY, 0, 1, 0);
    glRotated(angZ, 0, 0, 1);
                 
    //eixos
    glBegin(GL_LINES);
        glColor3d(0,0,1);
        glVertex3d(0, 0, 0);
        glVertex3d(0, 0, 10);
        glColor3d(1,0,0);
        glVertex3d(0, 0, 0);
        glVertex3d(10, 0, 0);
        glColor3d(0,1,0);
        glVertex3d(0, 0, 0);
        glVertex3d(0, 10, 0);        
 glEnd();
    
   
    DefineCenario();
    Texto();
    Texto2();
    if((transBolaX == 0) && (transBolaY == 0)) {
    retaDirecao();
    }
    glutSwapBuffers();
}

void resetGameConditions(void){
     for(i=0;i<10;++i){
                 ListaDePinos[i].status=FIXO;
     } 
     angX=0; 
     angY=0;
     angZ=0;
     dX=0,dY=0;
     jogadas=0;
     pinosDerrubados=0;
     transBolaX=0, transBolaY=0;
}
void removePinos(void){
     dX=0,dY=0;
     transBolaX=0, transBolaY=0;
}
void resetGame(void){
     turn=1;
     pontos=0;
     placargeral=0;
     resetGameConditions();
}
void criaListasExib(void){
    pino = glGenLists(1);//criacao da lista de exibicao do pino
    glNewList(pino,GL_COMPILE);
    glPushMatrix();
    criaPonto(&pPinos);
    criaFace(&fPinos);
    CarregaArquivo(&pPinos, &fPinos,PINOS);
    CarregaArquivo(&pFita, &fFita,FITA);
    glScalef(0.5,0.5,0.5);
    gera(fPinos, 1, 1, 1);
    glScalef(0.5,0.5,0.5);
    glTranslatef(0,0,2);
    gera(fFita, 1, 0, 0);
    
    glPopMatrix();
    glEndList();
    cena = glGenLists(2);//criacao da lista de exibicao do cenario
    glNewList(cena,GL_COMPILE);   
      CarregaArquivo(&pPista, &fPista,CUBO);
      CarregaArquivo(&pCenario, &fCenario,PAREDE);
      CarregaArquivo(&pBola, &fBola,BOLA); 
      CarregaArquivo(&pPiso, &fPiso,BOLA);
    glEndList();
     glCallList(cena); 
}

void Inicializa(){
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(300, 1, 0.5, 100);
    
    criaListasExib();
    iluminacao();
    resetGameConditions();
}

void Key(unsigned char key, int x, int y){
    switch (key){
             
	case '1':angY=0;angZ=0; 
          break;
    case 'S':
	case 's': if(angY<30) angY += 2;
		  break;
	
	case 'Z':
	case 'z': if(angZ>-46) angZ-= 2;
		  break;
		 
	case 'X':
	case 'x': if(angY>-10) angY -= 2;
		  break;
		 
	case 'C':
	case 'c': if(angZ<46) angZ += 2;
		  break;
	case 'R':
    case 'r': resetGame();  
              break;         	  
    case 'w':
    case 'W': glEnable(GL_LIGHTING);
              break;
    case 'E':
    case 'e': glDisable(GL_LIGHTING);
              break;
    case 'Q':
    case 'q': exit(0);
    }
    glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y){
    if((transBolaX == 0) && (transBolaY == 0))
          if(state == GLUT_DOWN)
          if(button==GLUT_LEFT_BUTTON){
            fimMouseX=transMouseX;
            fimMouseY=transMouseY;
            //printf("\ninicio :%d %d\n",initMouseX,initMouseY);
            dX =(475 - fimMouseY);
            dY =(450 - fimMouseX);  
            jogadas++;        
            }
    glutPostRedisplay();    
}

void MoveMouse(int x, int y)
{
     //sprintf(texto, "(%d,%d)", x, y);//450 475
     transMouseX= x;
     transMouseY= y;
     //printf("\n%d  %d", x,y);
     retaX = -x;
     if(x<450)
       retaY = -y;
     else
       retaY = y;
     glutPostRedisplay();
}
void pontuacao(void){
     for(i=0;i<10;++i)
       if(ListaDePinos[i].status==DERRUBADO) {
       ListaDePinos[i].status=REMOVIDO;
       pinosDerrubados++;
       }
     pontos=10*pinosDerrubados; //o calculo ta repetindo
     printf("%d \n",pinosDerrubados); 
     sprintf(textpontos,"%s%d","seus pontos: ", pontos);
     if(jogadas==1&&pinosDerrubados==10){
     //pontos=100;
     //strike
     pontos+=10*pinosDerrubados;
     sprintf(textpontos,"%s%d","STRIKE!!! seus pontos: ",pontos);
     resetGameConditions();
     turn++;
     printf("\nstrike!!!");
     }
     if(jogadas==2&&pinosDerrubados==10){
     pontos+=5*pinosDerrubados;                                    
     sprintf(textpontos,"%s%d","SPARE! seus pontos: ",pontos);
     printf("\nspare!!!");//esta condicao ta dando erro
     }
}

void trataColisoes(void){
    //printf("%d",abs(1.0));
    for(i=0;i<10;++i){
     if((abs(transBolaX - ListaDePinos[i].x )<0.2) &&(abs(transBolaY - ListaDePinos[i].y )< 0.2)){
     ListaDePinos[i].status=DERRUBADO;
       if((transBolaY <= -2.2 && transBolaY >= 2.2)){
        if(ListaDePinos[i].status==DERRUBADO)
        ListaDePinos[i].status=FIXO;
        }  
     }
     //condicao de STRIKE
     if(transBolaX +1< ListaDePinos[i].x &&(transBolaY >= -0.2 && transBolaY <= 0.2)&&pinosDerrubados==0){
        ListaDePinos[i].status=DERRUBADO;
     } 
    }
    if(transBolaY >= 2.2)  transBolaY +=0.0006*dY;
    if(transBolaY <= -2.2) transBolaY +=0.0006*dY;
}

void TimerFunction(int value){
    // estas translacoes sao a direcao da bola
    
    trataColisoes();
    sprintf(textRodada,"%s%d. RODADA %d bola %d :","Total de pontos:",placargeral ,turn,jogadas+1);
    if(turn<=10)
    if(dX>0 && abs(dY<150)){
    transBolaX-=0.0006*dX ; 
    transBolaY-=0.0006*dY ;
    }
      if(transBolaX <=-15 ){
       pontuacao();
       removePinos();
       placargeral+=pontos;
       if(jogadas>=2||(pinosDerrubados==10&& jogadas==1)) {
         turn++;
         resetGameConditions();
       }//removePinos();
       //fim de jogo
        //sprintf(textRodada,"%s%d :","RODADA ",turn);
       }
    if(turn>=10&&(jogadas>=2||(pinosDerrubados==10&& jogadas==1))){
       turn++;                                            
      sprintf(textRodada,"%s %d. tecle q para sair","Fim de jogo!! Total de pontos: ",placargeral);
                                                    
    }
    glutPostRedisplay();
    
  glutTimerFunc(time, TimerFunction, 1); 

}

int main(int argc, char **argv){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (900, 700);
   glutInitWindowPosition (50, 50);
   glutCreateWindow("Boliche");
   glutDisplayFunc(Desenha);
   glutKeyboardFunc(Key);
   glutMouseFunc(Mouse);
   glutPassiveMotionFunc(MoveMouse);
   glutTimerFunc(time, TimerFunction, 1);
   Inicializa();
   glutMainLoop();
}





