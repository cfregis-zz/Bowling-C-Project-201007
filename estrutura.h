#include <GL/glut.h>
#ifndef _estrutura_h_
#define _estrutura_h_

//calcular normais
typedef struct p3d{
    double x, y, z;
}Point3D;
//tipo pino: util para saber se houve colisao, alterando status
typedef struct pino{
        double x , y ,z ;
        int status;
        }tPino;

typedef struct ponto{
       struct ponto *proximo;
       float x;
       float y;
       float z;
}tPonto, *tPtrPonto;
//estrutura base para a lista de pontos

typedef struct face{
        struct face *proximo;
        tPonto *p1;
        tPonto *p2;
        tPonto *p3;
}tFace, *tPtrFace;
//estrutura base para a lista faces

//alusões 
extern void criaPonto(tPtrPonto *p);
extern void criaFace(tPtrFace *f);
extern void compVetorNormalTriangulo(Point3D p1, Point3D p2, Point3D p3, Point3D *n);
extern int inserePonto(tPtrPonto *p,double x,double y,double z);
extern void CarregaArquivo(tPtrPonto *p, tPtrFace *f,  char *arqNome);
extern int insereFace(tPtrFace *f,tPtrPonto *p, int c1, int c2, int c3);
extern void gera(tPtrFace f, float r, float g, float b);
extern void iluminacao(void);
#endif
