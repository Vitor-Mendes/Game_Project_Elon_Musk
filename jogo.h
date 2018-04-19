#ifndef JOGO_H
#define JOGO_H

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <math.h>
#define PI 3.14159

typedef struct Tamanho{
    double width,heigth;
}Tamanho;

typedef struct Coordenadas{
    double X;
    double Y;
}Coord;

typedef struct Spaceship{
    Coord Coordi;
    Coord Vel;
    Tamanho tamanhoNave;
    char explosao;
}Ship;

typedef struct Colisao{
    char colidiu;
    Coord centro;
    Coord cnormal;
}Colision;

typedef struct Solo{
    Coord Coordinates;
    Tamanho tamanhoSolo;
}Solo;

typedef struct meteoro{
    Coord pos;
    Coord vel;
    char explodiu;
}meteor;

typedef struct linha{
    Coord pos1;
    Coord vect;
    Coord normal;
    Coord posnorm;
}linha;

extern double Gravity;
extern double tempof;
extern double impulse;
extern int angulo;
extern double anguloradian;
extern unsigned int tecladao[128];
extern int n_meteoros;
extern int cena;
extern int verdade;
extern int gasolina;
extern int vida_nave;
extern int tela_Atual;
extern double produto;
extern int nexplosao;
extern int ganhou;
extern int dificuldade;

extern double teste_Velocidade;
extern double teste_Aceleracao;
extern double teste_Altitude;

extern Colision objnave;
extern Ship nave;

extern Solo solo;

extern Coord gravidade;
extern Coord impulso;
extern Coord nuvem[10];
extern Coord animacao[4];

extern meteor meteoro[100];
extern linha linhas[15];

extern GLuint textura_nave;
extern GLuint textura_fundo;
extern GLuint textura_animado[4];
extern GLuint textura_nuvem;
extern GLuint textura_explosao[8];
extern GLuint textura_meteoro;
extern GLuint textura_vida;

void tocar_musica(char const nome[40], int loop);

void parar_musica();

void delay(int v);

void escreve_Texto(void * font, char *s, double x, double y, double z);

void escreve_Numero(void * font, double numero, double x, double y, double z);

void teclado4(unsigned char key, int x, int y);

void teclado3(unsigned char key, int x, int y);

void atualizanave();

void atualizameteoros();

void desenhalinhasdecolisao();

void desenharposicoesmeteoro();

void checacena();

double colisionball_line(int k);

void Arquivodepontuacao(float pontuacao);

void colisiondetect();

void atualiza_Jogo();

void inicializa_Jogo(void);

void desenha_Jogo();

#endif
