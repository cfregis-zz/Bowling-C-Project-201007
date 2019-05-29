#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

int aux = 0;

    
void criaPonto(tPtrPonto *p){
     *p = NULL;
}

void criaFace(tPtrFace *f){
     *f = NULL;
}

int inserePonto(tPtrPonto *p, double x, double y, double z){
    tPtrPonto aux, novo;
    
    aux = *p;
    if(aux == NULL){
        novo = malloc(sizeof(tPonto));
        if (novo == NULL)
	    return 0;
        novo -> x = x;
        novo -> y = y;
        novo -> z = z;
        novo -> proximo = NULL;
        *p = novo;
        return 1;
    }else{
        while(aux -> proximo){
              aux = aux -> proximo;
        }
        novo = malloc(sizeof(tPonto));
        if (novo == NULL)
	    return 0;
        novo -> x = x;
        novo -> y = y;
        novo -> z = z;
        novo ->proximo = aux -> proximo;
        aux -> proximo = novo;
        return 1;
    }
}

int insereFace(tPtrFace *f,tPtrPonto *p, int c1, int c2, int c3){
      tPtrFace auxF, novo;
      tPtrPonto auxP;
      int i;
      
      auxF = *f;
      auxP = *p;    
      
      if(auxP == NULL)
	return 0;
      novo = malloc(sizeof(tFace));
      if (novo == NULL)
         return 0;
      
      for(i=0; i<c1; i++)
         auxP = auxP -> proximo;      
      novo -> p1 = auxP;
    
      auxP = *p;
      for(i=0; i<c2; i++)
         auxP = auxP -> proximo;
      novo -> p2 = auxP;
    
      auxP = *p;
      for(i=0; i<c3; i++)
         auxP = auxP -> proximo;
      novo -> p3 = auxP;
      
      if(*f == NULL){
            novo -> proximo = NULL;
            *f = novo;
            return 1;
      }else{
            while(auxF -> proximo)
                    auxF = auxF -> proximo;
            novo -> proximo = auxF -> proximo;
            auxF -> proximo = novo;
            return 1;          
      }
    
}

void CarregaArquivo(tPtrPonto *p, tPtrFace *f, char *arqNome){
    FILE *arquivo;
    int v1,v2,v3,v4,ok;
    char linha[500];
    float x,y,z;
    if ((arquivo = fopen(arqNome, "r")) == NULL)
        printf("Arquivo nao pode ser aberto\n");
     else{         
	while(!feof(arquivo)){
            fscanf(arquivo,"%s",linha);
	    if(memcmp(linha,"point",5) == 0){
		fscanf(arquivo,"%s",linha);
		if(memcmp(linha,"[",1) == 0){
		    while(!feof(arquivo)){
			ok = fscanf(arquivo,"%f %f %f",&x,&y,&z); 
			//printf("%f %f %f\n",x,y,z);
			if(ok == 0) break;
			inserePonto(p,x,y,z);
		    }
		}
	    }
        }
	if ((arquivo = fopen(arqNome, "r")) == NULL)
	    printf("Arquivo nao pode ser aberto\n");
	else{	
	    ok=1;
	    while(!feof(arquivo)){
		fscanf(arquivo,"%s",linha);
		if(memcmp(linha,"coordIndex",10)==0){
		    fscanf(arquivo,"%s",linha);
		    if(memcmp(linha,"[",1)==0 ){
			    while(!feof(arquivo)){			  
				ok=  fscanf(arquivo,"%d %d %d",&v1,&v2,&v3);
				fscanf(arquivo,"%s",linha);
				if(ok==0)break;
				insereFace(f,p,v1,v2,v3);
				}
		    }
		    
		}
	    }
	}
    //printf("Arquivo lido com sucesso\n");
    fclose(arquivo);
    }
    
}

void gera(tPtrFace f, float r, float g, float b){  
    tPtrFace aux;
    aux = f;
    Point3D n;
//    tPtrPonto n;    
    if(aux == NULL)
	return;
    while(aux){             
             Point3D p1={aux -> p1 -> x, aux -> p1 -> y, aux -> p1 -> z};
             Point3D p2={aux -> p2 -> x, aux -> p2 -> y, aux -> p2 -> z};
             Point3D p3={aux -> p3 -> x, aux -> p3 -> y, aux -> p3 -> z};    
             compVetorNormalTriangulo(p1, p2, p3, &n);
      glBegin(GL_TRIANGLE_STRIP);
            glColor3f(r, g, b);
             glNormal3f(n.x, n.y, n.z);
             glVertex3d(aux -> p1 -> x, aux -> p1 -> y, aux -> p1 -> z);
             glVertex3d(aux -> p2 -> x, aux -> p2 -> y, aux -> p2 -> z);
             glVertex3d(aux -> p3 -> x, aux -> p3 -> y, aux -> p3 -> z);
	    aux=aux->proximo;
      glEnd();
    }
}

void compVetorNormalTriangulo(Point3D p1, Point3D p2, Point3D p3, Point3D *n){
    Point3D v1, v2;
    double len;

    /* Encontra vetor v1 */
    v1.x = p2.x - p1.x;
    v1.y = p2.y - p1.y;
    v1.z = p2.z - p1.z;

    /* Encontra vetor v2 */
    v2.x = p3.x - p1.x;
    v2.y = p3.y - p1.y;
    v2.z = p3.z - p1.z;

    /* Calculo do produto vetorial de v1 e v2 */
    n->x = (v1.y * v2.z) - (v1.z * v2.y);
    n->y = (v1.z * v2.x) - (v1.x * v2.z);
    n->z = (v1.x * v2.y) - (v1.y * v2.x);

    /* normalizacao de n */
    len = sqrt(n->x*n->x + n->y*n->y + n->z*n->z);
    n->x /= len;
    n->y /= len;
    n->z /= len;
}

void iluminacao(void){
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={1,1,1,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, 0.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

 	// Especifica que a cor de fundo da janela sera preta
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	// Habilita o modelo de colorizacao de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletancia do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentracao do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a definicao da cor do material a partir da cor corrente
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminacao
	glEnable(GL_LIGHTING);  
	// Habilita a luz de numero 0
    glEnable(GL_LIGHT0);


     
     
}
