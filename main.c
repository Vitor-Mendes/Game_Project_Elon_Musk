
/*       BIBLIOTEAS       */
#include "menu.h"
/**********************/



/*                 INICIALIZA VALORES                    */
void inicializa(void){

    hotkey='m';
    hotkey_Bind=15;
    tela_Atual=1;
    tecla_Bind=0;

    Jogar_Tela=1;
    Dificuldade_Tela=2;
    Instrucoes_Tela=3;
    Configuracoes_Tela=4; 
    Sair_Tela=5;

    largura_Base=400;
    altura_Base=120;
    largura_Destaque=450;
    altura_Destaque=150;

    inicializa_Menu();
    inicializa_Jogo();

}

void drawAll(){

  if(tela_Atual<=8){
	 desenha_Menu();
  }

  if(tela_Atual==9){
    desenha_Jogo();
  }

}

void redimensionar(int w, int h){

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Ortho_X*w/h, 0, Ortho_Y*w/h, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void atualiza(int indice) {

  if(tecladao[112]==0){

    if(tela_Atual<=8){
      if(ganhou==1){
        parar_musica();
        tocar_musica("Undertale - Megalovania.ogg", 1);
        Ortho_X=1000;
        Ortho_Y=1000;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, Ortho_X, 0, Ortho_Y, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        ganhou=0;
      }
      atualiza_Menu();
    }

    if(tela_Atual==9 && ganhou==0){
      if(verdade2==1){
        cena=1;
        Ortho_X=150;
        Ortho_Y=150;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, Ortho_X, 0, Ortho_Y, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        verdade2=0;
      }
      atualiza_Jogo();
    }
}

   glutTimerFunc(33, atualiza, 0);
}

void escolhe_Teclado(unsigned char key, int x, int y){

  if(tela_Atual<=8){
    teclado1(key,x,y);
  }
  if(tela_Atual==9){
    teclado3(key,x,y);
  }

}

int main(int argc,char** argv){

    srand(time(0));

    glutInit(&argc,argv);
    glutInitContextVersion(1,1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640,640);
    glutInitWindowPosition(200,100);

    glutCreateWindow("Jogo.exe");
    inicializa();

    glutDisplayFunc(drawAll);
    glutReshapeFunc(redimensionar);

    glutIgnoreKeyRepeat(1);

    glutKeyboardFunc(escolhe_Teclado);

    //glutKeyboardFunc(teclado1);
    glutSpecialFunc(teclado2);

    //glutKeyboardFunc(teclado3);
    glutKeyboardUpFunc(teclado4);
    

    glutTimerFunc(0, atualiza, 0);

    glutMainLoop();
    return 0;

}