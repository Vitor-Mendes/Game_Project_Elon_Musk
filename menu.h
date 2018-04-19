#ifndef MENU_H
#define MENU_H

/*       BIBLIOTECAS       */
#include "jogo.h"
/**********************/

/*      VARIÁVEIS GLOBAIS      */

extern char hotkey;

extern int hotkey_Bind;

extern int tela_Atual;

extern int tela_Opcoes;

extern int tecla_Bind;

extern int verdade2;

//extern double teste_Velocidade;
//extern double teste_Aceleracao;
//extern double teste_Altitude;

extern int Jogar_Tela, 
    Dificuldade_Tela, 
    Instrucoes_Tela, 
    Configuracoes_Tela, 
    Sair_Tela;

extern double largura_Base,
      altura_Base,
      largura_Destaque,
      altura_Destaque;

 //Opções de menu
typedef struct opcao{
    Coord Coordinates;
    Tamanho tamanhoCaixa;
}Opcao;

extern Opcao Jogar;
extern Opcao Dificuldade;
extern Opcao Instrucoes;
extern Opcao Configuracoes;
extern Opcao Creditos;
extern Opcao Sair;

extern Opcao Facil;
extern Opcao Medio;
extern Opcao Dificil;

extern Coord posicaoMouseTela;
extern Coord posicaoMouseMundo;

extern GLuint menuBackground;

extern double largura_Janela;
extern double altura_Janela;

extern double Ortho_X, Ortho_Y;

//#define WAV_PATH ""
//#define MUS_PATH ""

//Mix_Chunk *wave = NULL;
//Mix_Chunk *music = NULL;

void gethighscores(float highscores[10]);

void inicializa_Menu(void);

void movimentoMouse(int x, int y);

void OnMouseClick(int button, int state, int x, int y);

void teclado2(int key,int x,int y);

void teclado1(unsigned char key, int x, int y);

void atualiza_Cena(void);

void desenha_Titulo();

void desenha_Retangulo();

void desenha_Menu();

void atualiza_Menu();

#endif