
/*       BIBLIOTEAS       */
#include "menu.h"
/**********************/

char hotkey;
int hotkey_Bind;
int verdade2=0;

int tela_Atual;

int tela_Opcoes=0;

int tecla_Bind;
   
float highscores[10];

//double teste_Velocidade;
//double teste_Aceleracao;
//double teste_Altitude;

int Jogar_Tela, 
    Dificuldade_Tela, 
    Instrucoes_Tela, 
    Configuracoes_Tela, 
    Sair_Tela;

double largura_Base,
      altura_Base,
      largura_Destaque,
      altura_Destaque;

Opcao Jogar;
Opcao Dificuldade;
Opcao Instrucoes;
Opcao Configuracoes;
Opcao Creditos;
Opcao Sair;

Opcao Facil;
Opcao Medio;
Opcao Dificil;

Coord posicaoMouseTela;
Coord posicaoMouseMundo;

GLuint menuBackground;
GLuint tecla_Esc;
GLuint tecla_P;
GLuint tecla_R;
GLuint tecla_wasd;

double largura_Janela;
double altura_Janela;

double Ortho_X = 1000, Ortho_Y = 1000;


void gethighscores(float highscores[10]){
	int k,z;
	FILE* fp;
	fp = fopen("pontuacao.txt","a+");
	for(k=0;k<10;k++){
			if(fscanf(fp,"%f*",highscores+k)==1){
			highscores+k;
			
		}
	}
	fclose(fp);
	float copo;
	for(k=0;k<10;k++){
		for(z=0;z<10;z++){
			if(highscores[k]>highscores[z] && z!=k){
				copo = highscores[z];
				highscores[z] = highscores[k];
				highscores[k]=copo;
			}
		}
	}
}


/*                 INICIALIZA VALORES                    */
void inicializa_Menu(void){

    glEnable(GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    menuBackground = SOIL_load_OGL_texture(
        "fundo.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    tecla_Esc = SOIL_load_OGL_texture(
        "tecla_Esc.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    tecla_R = SOIL_load_OGL_texture(
        "tecla_R.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    tecla_P = SOIL_load_OGL_texture(
        "tecla_P.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    tecla_wasd = SOIL_load_OGL_texture(
        "wasd.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );



    if (menuBackground == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }


    tocar_musica("Undertale - Megalovania.ogg", 1);

}
/******************************************************/

/******************************************************/
void movimentoMouse(int x, int y) {

    posicaoMouseTela.X = x;
    posicaoMouseTela.Y = y;

    posicaoMouseMundo.X=posicaoMouseTela.X*1000/640;
    posicaoMouseMundo.Y=(posicaoMouseTela.Y*(-1)+640)*1000/640;

    if(tela_Opcoes==0){

	    if(tela_Atual<=5){

		    if(posicaoMouseMundo.X>Jogar.Coordinates.X && posicaoMouseMundo.X<Jogar.Coordinates.X+Jogar.tamanhoCaixa.width && 
				posicaoMouseMundo.Y>Jogar.Coordinates.Y && posicaoMouseMundo.Y<Jogar.Coordinates.Y+Jogar.tamanhoCaixa.heigth){

		    		tela_Atual=1;

		    }

		    if(posicaoMouseMundo.X>Dificuldade.Coordinates.X && posicaoMouseMundo.X<Dificuldade.Coordinates.X+Dificuldade.tamanhoCaixa.width && 
				posicaoMouseMundo.Y>Dificuldade.Coordinates.Y && posicaoMouseMundo.Y<Dificuldade.Coordinates.Y+Dificuldade.tamanhoCaixa.heigth){

		    		tela_Atual=2;

		    }

		    if(posicaoMouseMundo.X>Instrucoes.Coordinates.X && posicaoMouseMundo.X<Instrucoes.Coordinates.X+Instrucoes.tamanhoCaixa.width && 
				posicaoMouseMundo.Y>Instrucoes.Coordinates.Y && posicaoMouseMundo.Y<Instrucoes.Coordinates.Y+Instrucoes.tamanhoCaixa.heigth){

		    		tela_Atual=3;

		    }

		    if(posicaoMouseMundo.X>Configuracoes.Coordinates.X && posicaoMouseMundo.X<Configuracoes.Coordinates.X+Configuracoes.tamanhoCaixa.width && 
				posicaoMouseMundo.Y>Configuracoes.Coordinates.Y && posicaoMouseMundo.Y<Configuracoes.Coordinates.Y+Configuracoes.tamanhoCaixa.heigth){

		    		tela_Atual=4;

		    }

		    if(posicaoMouseMundo.X>Sair.Coordinates.X && posicaoMouseMundo.X<Sair.Coordinates.X+Sair.tamanhoCaixa.width && 
				posicaoMouseMundo.Y>Sair.Coordinates.Y && posicaoMouseMundo.Y<Sair.Coordinates.Y+Sair.tamanhoCaixa.heigth){

		    		tela_Atual=5;

		    }
		}

		if(tela_Atual>5 && tela_Atual<9){

			if(posicaoMouseMundo.X>Facil.Coordinates.X && posicaoMouseMundo.X<Facil.Coordinates.X+Facil.tamanhoCaixa.width && 
				posicaoMouseMundo.Y>Facil.Coordinates.Y && posicaoMouseMundo.Y<Facil.Coordinates.Y+Facil.tamanhoCaixa.heigth){

		    		tela_Atual=6;

		    }

		    if(posicaoMouseMundo.X>Medio.Coordinates.X && posicaoMouseMundo.X<Medio.Coordinates.X+Medio.tamanhoCaixa.width && 
				posicaoMouseMundo.Y>Medio.Coordinates.Y && posicaoMouseMundo.Y<Medio.Coordinates.Y+Medio.tamanhoCaixa.heigth){

		    		tela_Atual=7;

		    }

		    if(posicaoMouseMundo.X>Dificil.Coordinates.X && posicaoMouseMundo.X<Dificil.Coordinates.X+Dificil.tamanhoCaixa.width && 
				posicaoMouseMundo.Y>Dificil.Coordinates.Y && posicaoMouseMundo.Y<Dificil.Coordinates.Y+Dificil.tamanhoCaixa.heigth){

		    		tela_Atual=8;

		    }
		}
	}
}

void OnMouseClick(int button, int state, int x, int y){

	if(tela_Opcoes==0){

		if(tela_Atual==1){

			  if(posicaoMouseMundo.X>Jogar.Coordinates.X && posicaoMouseMundo.X<Jogar.Coordinates.X+Jogar.tamanhoCaixa.width && 
			  	  posicaoMouseMundo.Y>Jogar.Coordinates.Y && posicaoMouseMundo.Y<Jogar.Coordinates.Y+Jogar.tamanhoCaixa.heigth){  

			        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
				        parar_musica();
				        tocar_musica("Ambient-Space-Music-Shooting-Stars.ogg", 1);
			            Ortho_X=150;
		    			Ortho_Y=150;
		    			tela_Atual=9;
		    			verdade2=1;
			        }
	    		}
	  	}

	  	if(tela_Atual==2){

			if(posicaoMouseMundo.X>Dificuldade.Coordinates.X && posicaoMouseMundo.X<Dificuldade.Coordinates.X+Dificuldade.tamanhoCaixa.width && 
			  	posicaoMouseMundo.Y>Dificuldade.Coordinates.Y && posicaoMouseMundo.Y<Dificuldade.Coordinates.Y+Dificuldade.tamanhoCaixa.heigth){  

			    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			        tela_Atual=6;
			    }
	    	}
	  	}

	  	if(tela_Atual==3){

			if(posicaoMouseMundo.X>Instrucoes.Coordinates.X && posicaoMouseMundo.X<Instrucoes.Coordinates.X+Instrucoes.tamanhoCaixa.width && 
			  	posicaoMouseMundo.Y>Instrucoes.Coordinates.Y && posicaoMouseMundo.Y<Instrucoes.Coordinates.Y+Instrucoes.tamanhoCaixa.heigth){  

			    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			        gethighscores(highscores);
			        tela_Opcoes=2;

			    }
	    	}
	  	}

	  	if(tela_Atual==4){

			if(posicaoMouseMundo.X>Configuracoes.Coordinates.X && posicaoMouseMundo.X<Configuracoes.Coordinates.X+Configuracoes.tamanhoCaixa.width && 
			  	posicaoMouseMundo.Y>Configuracoes.Coordinates.Y && posicaoMouseMundo.Y<Configuracoes.Coordinates.Y+Configuracoes.tamanhoCaixa.heigth){  

			    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			        tela_Opcoes=1;
			    }
	    	}
	  	}

	  	if(tela_Atual==5){

			if(posicaoMouseMundo.X>Sair.Coordinates.X && posicaoMouseMundo.X<Sair.Coordinates.X+Sair.tamanhoCaixa.width && 
				posicaoMouseMundo.Y>Sair.Coordinates.Y && posicaoMouseMundo.Y<Sair.Coordinates.Y+Sair.tamanhoCaixa.heigth){  

			    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			    	exit(0);
			    }
	    	}
	  	}

	  	if(tela_Atual==6){

			if(posicaoMouseMundo.X>Facil.Coordinates.X && posicaoMouseMundo.X<Facil.Coordinates.X+Facil.tamanhoCaixa.width && 
				posicaoMouseMundo.Y>Facil.Coordinates.Y && posicaoMouseMundo.Y<Facil.Coordinates.Y+Facil.tamanhoCaixa.heigth){  

			   	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			        	
			        // Dificuldade Fácil
			        dificuldade=1;
			        tela_Atual=1;


			    }
	    	}
	  	}

	  	if(tela_Atual==7){

			if(posicaoMouseMundo.X>Medio.Coordinates.X && posicaoMouseMundo.X<Medio.Coordinates.X+Medio.tamanhoCaixa.width && 
				posicaoMouseMundo.Y>Medio.Coordinates.Y && posicaoMouseMundo.Y<Medio.Coordinates.Y+Medio.tamanhoCaixa.heigth){  

			    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			        	
			       	// Dificuldade Média
			       	dificuldade=2;
			       	tela_Atual=1;

			    }
	    	}
	  	}

	  	if(tela_Atual==8){

			if(posicaoMouseMundo.X>Dificil.Coordinates.X && posicaoMouseMundo.X<Dificil.Coordinates.X+Dificil.tamanhoCaixa.width && 
				posicaoMouseMundo.Y>Dificil.Coordinates.Y && posicaoMouseMundo.Y<Dificil.Coordinates.Y+Dificil.tamanhoCaixa.heigth){  

			    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			        	
			        // Dificuldade Difícil
			        dificuldade=3;
			        tela_Atual=1;

			    }
	    	}
	  	}
	}
}
/******************************************************/

/******************************************************/
void teclado2(int key,int x,int y){

	if(tela_Atual<9){

    switch(key){

        case GLUT_KEY_UP:

	        if(tela_Atual<=5){

	        	if((posicaoMouseMundo.X>Jogar.Coordinates.X && posicaoMouseMundo.X<Jogar.Coordinates.X+Jogar.tamanhoCaixa.width && 
				   posicaoMouseMundo.Y>Jogar.Coordinates.Y && posicaoMouseMundo.Y<Jogar.Coordinates.Y+Jogar.tamanhoCaixa.heigth) 
				   || (posicaoMouseMundo.X>Dificuldade.Coordinates.X && posicaoMouseMundo.X<Dificuldade.Coordinates.X+Dificuldade.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Dificuldade.Coordinates.Y && posicaoMouseMundo.Y<Dificuldade.Coordinates.Y+Dificuldade.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Instrucoes.Coordinates.X && posicaoMouseMundo.X<Instrucoes.Coordinates.X+Instrucoes.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Instrucoes.Coordinates.Y && posicaoMouseMundo.Y<Instrucoes.Coordinates.Y+Instrucoes.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Configuracoes.Coordinates.X && posicaoMouseMundo.X<Configuracoes.Coordinates.X+Configuracoes.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Configuracoes.Coordinates.Y && posicaoMouseMundo.Y<Configuracoes.Coordinates.Y+Configuracoes.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Sair.Coordinates.X && posicaoMouseMundo.X<Sair.Coordinates.X+Sair.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Sair.Coordinates.Y && posicaoMouseMundo.Y<Sair.Coordinates.Y+Sair.tamanhoCaixa.heigth)){
			    	break;
			    }
			    else{
		            if(tela_Atual>1){
		                tela_Atual--;
		            }
		        }
		        glutPostRedisplay();
		    }

		    if(tela_Atual>5){

		    	if((posicaoMouseMundo.X>Facil.Coordinates.X && posicaoMouseMundo.X<Facil.Coordinates.X+Facil.tamanhoCaixa.width && 
				   posicaoMouseMundo.Y>Facil.Coordinates.Y && posicaoMouseMundo.Y<Facil.Coordinates.Y+Facil.tamanhoCaixa.heigth) 
				   || (posicaoMouseMundo.X>Medio.Coordinates.X && posicaoMouseMundo.X<Medio.Coordinates.X+Medio.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Medio.Coordinates.Y && posicaoMouseMundo.Y<Medio.Coordinates.Y+Medio.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Dificil.Coordinates.X && posicaoMouseMundo.X<Dificil.Coordinates.X+Dificil.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Dificil.Coordinates.Y && posicaoMouseMundo.Y<Dificil.Coordinates.Y+Dificil.tamanhoCaixa.heigth)){
			    	break;
			    }
			    else{
		            if(tela_Atual>6){
		                tela_Atual--;
		            }
		        }
		        glutPostRedisplay();
		    }
             break;

        case GLUT_KEY_DOWN:

	        if(tela_Atual<=5){

	        	if((posicaoMouseMundo.X>Jogar.Coordinates.X && posicaoMouseMundo.X<Jogar.Coordinates.X+Jogar.tamanhoCaixa.width && 
				   posicaoMouseMundo.Y>Jogar.Coordinates.Y && posicaoMouseMundo.Y<Jogar.Coordinates.Y+Jogar.tamanhoCaixa.heigth) 
				   || (posicaoMouseMundo.X>Dificuldade.Coordinates.X && posicaoMouseMundo.X<Dificuldade.Coordinates.X+Dificuldade.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Dificuldade.Coordinates.Y && posicaoMouseMundo.Y<Dificuldade.Coordinates.Y+Dificuldade.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Instrucoes.Coordinates.X && posicaoMouseMundo.X<Instrucoes.Coordinates.X+Instrucoes.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Instrucoes.Coordinates.Y && posicaoMouseMundo.Y<Instrucoes.Coordinates.Y+Instrucoes.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Configuracoes.Coordinates.X && posicaoMouseMundo.X<Configuracoes.Coordinates.X+Configuracoes.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Configuracoes.Coordinates.Y && posicaoMouseMundo.Y<Configuracoes.Coordinates.Y+Configuracoes.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Sair.Coordinates.X && posicaoMouseMundo.X<Sair.Coordinates.X+Sair.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Sair.Coordinates.Y && posicaoMouseMundo.Y<Sair.Coordinates.Y+Sair.tamanhoCaixa.heigth)){
			    	break;
			    }
			    else{
		            if(tela_Atual<5){
		                tela_Atual++;
		            }
		        }
	            glutPostRedisplay();
	        }

	        if(tela_Atual>5){

	        	if((posicaoMouseMundo.X>Facil.Coordinates.X && posicaoMouseMundo.X<Facil.Coordinates.X+Facil.tamanhoCaixa.width && 
					   posicaoMouseMundo.Y>Facil.Coordinates.Y && posicaoMouseMundo.Y<Facil.Coordinates.Y+Facil.tamanhoCaixa.heigth) 
					   || (posicaoMouseMundo.X>Medio.Coordinates.X && posicaoMouseMundo.X<Medio.Coordinates.X+Medio.tamanhoCaixa.width && 
						  posicaoMouseMundo.Y>Medio.Coordinates.Y && posicaoMouseMundo.Y<Medio.Coordinates.Y+Medio.tamanhoCaixa.heigth)
					   || (posicaoMouseMundo.X>Dificil.Coordinates.X && posicaoMouseMundo.X<Dificil.Coordinates.X+Dificil.tamanhoCaixa.width && 
						  posicaoMouseMundo.Y>Dificil.Coordinates.Y && posicaoMouseMundo.Y<Dificil.Coordinates.Y+Dificil.tamanhoCaixa.heigth)){
				    	break;
				    }
				    else{
			            if(tela_Atual<8){
			                tela_Atual++;
			            }
			        }
			        glutPostRedisplay();
	        }
             break;

        default:
             break;
    	}
	}
}

void teclado1(unsigned char key, int x, int y){

	if(tela_Atual<9){

   switch(key){

      // Tecla ESC
    case 27:
    
	    if((tela_Atual<=5 || tela_Atual==9) && tela_Opcoes!=1 && tela_Opcoes!=2){
	        exit(0);
	    }
	    if(tela_Atual>5 || tela_Opcoes==1 || tela_Opcoes==2){
	    	tela_Opcoes=0;
	    	tela_Atual=1;
	    	glutPostRedisplay();
	    }
         break;

    case 13:

    	if(tela_Atual<=5){

	    	if((posicaoMouseMundo.X>Jogar.Coordinates.X && posicaoMouseMundo.X<Jogar.Coordinates.X+Jogar.tamanhoCaixa.width && 
				   posicaoMouseMundo.Y>Jogar.Coordinates.Y && posicaoMouseMundo.Y<Jogar.Coordinates.Y+Jogar.tamanhoCaixa.heigth) 
				   || (posicaoMouseMundo.X>Dificuldade.Coordinates.X && posicaoMouseMundo.X<Dificuldade.Coordinates.X+Dificuldade.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Dificuldade.Coordinates.Y && posicaoMouseMundo.Y<Dificuldade.Coordinates.Y+Dificuldade.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Instrucoes.Coordinates.X && posicaoMouseMundo.X<Instrucoes.Coordinates.X+Instrucoes.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Instrucoes.Coordinates.Y && posicaoMouseMundo.Y<Instrucoes.Coordinates.Y+Instrucoes.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Configuracoes.Coordinates.X && posicaoMouseMundo.X<Configuracoes.Coordinates.X+Configuracoes.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Configuracoes.Coordinates.Y && posicaoMouseMundo.Y<Configuracoes.Coordinates.Y+Configuracoes.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Sair.Coordinates.X && posicaoMouseMundo.X<Sair.Coordinates.X+Sair.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Sair.Coordinates.Y && posicaoMouseMundo.Y<Sair.Coordinates.Y+Sair.tamanhoCaixa.heigth)){
			    	break;
			    }
	    	else{
		        if(tela_Atual==1){
		            parar_musica();
		            tocar_musica("Ambient-Space-Music-Shooting-Stars.ogg", 1);
		            Ortho_X=150;
	    			Ortho_Y=150;
	    			cena=1;
	    			verdade=1;
	    			tela_Atual=9;
	    			verdade2=1;
		        }

		        if(tela_Atual==2){
		        	tela_Atual=6;
		        	break;
		        }

		        if(tela_Atual==3){
		        	gethighscores(highscores);
		        	tela_Opcoes=2;
		        }

		        if(tela_Atual==4){
		        	tela_Opcoes=1;
		        }

		        if(tela_Atual==5){
		            exit(0);
		        }
	    	}
      	}

      if(tela_Atual>5){

      		if(tela_Atual==6){
	        	
      			// Dificuldade Fácil
      			dificuldade=1;
			    tela_Atual=1;

	        }

	        if(tela_Atual==7){
	        	
	        	// Dificuldade Média
	        	dificuldade=2;
			    tela_Atual=1;

	        }

	        if(tela_Atual==8){

	        	// Dificuldade Difícil
	        	dificuldade=3;
			    tela_Atual=1;

	        }
      }
        //glutPostRedisplay();
         break;

    case 'w':

    	if(tela_Atual<=5 && tela_Atual<9){

	        	if((posicaoMouseMundo.X>Jogar.Coordinates.X && posicaoMouseMundo.X<Jogar.Coordinates.X+Jogar.tamanhoCaixa.width && 
				   posicaoMouseMundo.Y>Jogar.Coordinates.Y && posicaoMouseMundo.Y<Jogar.Coordinates.Y+Jogar.tamanhoCaixa.heigth) 
				   || (posicaoMouseMundo.X>Dificuldade.Coordinates.X && posicaoMouseMundo.X<Dificuldade.Coordinates.X+Dificuldade.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Dificuldade.Coordinates.Y && posicaoMouseMundo.Y<Dificuldade.Coordinates.Y+Dificuldade.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Instrucoes.Coordinates.X && posicaoMouseMundo.X<Instrucoes.Coordinates.X+Instrucoes.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Instrucoes.Coordinates.Y && posicaoMouseMundo.Y<Instrucoes.Coordinates.Y+Instrucoes.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Configuracoes.Coordinates.X && posicaoMouseMundo.X<Configuracoes.Coordinates.X+Configuracoes.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Configuracoes.Coordinates.Y && posicaoMouseMundo.Y<Configuracoes.Coordinates.Y+Configuracoes.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Sair.Coordinates.X && posicaoMouseMundo.X<Sair.Coordinates.X+Sair.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Sair.Coordinates.Y && posicaoMouseMundo.Y<Sair.Coordinates.Y+Sair.tamanhoCaixa.heigth)){
			    	break;
			    }
			    else{
		            if(tela_Atual>1){
		                tela_Atual--;
		            }
		        }
		        glutPostRedisplay();
		    }

		    if(tela_Atual>5 && tela_Atual<9){

		    	if((posicaoMouseMundo.X>Facil.Coordinates.X && posicaoMouseMundo.X<Facil.Coordinates.X+Facil.tamanhoCaixa.width && 
				   posicaoMouseMundo.Y>Facil.Coordinates.Y && posicaoMouseMundo.Y<Facil.Coordinates.Y+Facil.tamanhoCaixa.heigth) 
				   || (posicaoMouseMundo.X>Medio.Coordinates.X && posicaoMouseMundo.X<Medio.Coordinates.X+Medio.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Medio.Coordinates.Y && posicaoMouseMundo.Y<Medio.Coordinates.Y+Medio.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Dificil.Coordinates.X && posicaoMouseMundo.X<Dificil.Coordinates.X+Dificil.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Dificil.Coordinates.Y && posicaoMouseMundo.Y<Dificil.Coordinates.Y+Dificil.tamanhoCaixa.heigth)){
			    	break;
			    }
			    else{
		            if(tela_Atual>6){
		                tela_Atual--;
		            }
		        }
		        glutPostRedisplay();
		}
         break;

    case 's':

    	if(tela_Atual<=5 && tela_Atual<9){

	        	if((posicaoMouseMundo.X>Jogar.Coordinates.X && posicaoMouseMundo.X<Jogar.Coordinates.X+Jogar.tamanhoCaixa.width && 
				   posicaoMouseMundo.Y>Jogar.Coordinates.Y && posicaoMouseMundo.Y<Jogar.Coordinates.Y+Jogar.tamanhoCaixa.heigth) 
				   || (posicaoMouseMundo.X>Dificuldade.Coordinates.X && posicaoMouseMundo.X<Dificuldade.Coordinates.X+Dificuldade.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Dificuldade.Coordinates.Y && posicaoMouseMundo.Y<Dificuldade.Coordinates.Y+Dificuldade.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Instrucoes.Coordinates.X && posicaoMouseMundo.X<Instrucoes.Coordinates.X+Instrucoes.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Instrucoes.Coordinates.Y && posicaoMouseMundo.Y<Instrucoes.Coordinates.Y+Instrucoes.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Configuracoes.Coordinates.X && posicaoMouseMundo.X<Configuracoes.Coordinates.X+Configuracoes.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Configuracoes.Coordinates.Y && posicaoMouseMundo.Y<Configuracoes.Coordinates.Y+Configuracoes.tamanhoCaixa.heigth)
				   || (posicaoMouseMundo.X>Sair.Coordinates.X && posicaoMouseMundo.X<Sair.Coordinates.X+Sair.tamanhoCaixa.width && 
					  posicaoMouseMundo.Y>Sair.Coordinates.Y && posicaoMouseMundo.Y<Sair.Coordinates.Y+Sair.tamanhoCaixa.heigth)){
			    	break;
			    }
			    else{
		            if(tela_Atual<5){
		                tela_Atual++;
		            }
		        }
	            glutPostRedisplay();
	        }

	        if(tela_Atual>5 && tela_Atual<9){

	        	if((posicaoMouseMundo.X>Facil.Coordinates.X && posicaoMouseMundo.X<Facil.Coordinates.X+Facil.tamanhoCaixa.width && 
					   posicaoMouseMundo.Y>Facil.Coordinates.Y && posicaoMouseMundo.Y<Facil.Coordinates.Y+Facil.tamanhoCaixa.heigth) 
					   || (posicaoMouseMundo.X>Medio.Coordinates.X && posicaoMouseMundo.X<Medio.Coordinates.X+Medio.tamanhoCaixa.width && 
						  posicaoMouseMundo.Y>Medio.Coordinates.Y && posicaoMouseMundo.Y<Medio.Coordinates.Y+Medio.tamanhoCaixa.heigth)
					   || (posicaoMouseMundo.X>Dificil.Coordinates.X && posicaoMouseMundo.X<Dificil.Coordinates.X+Dificil.tamanhoCaixa.width && 
						  posicaoMouseMundo.Y>Dificil.Coordinates.Y && posicaoMouseMundo.Y<Dificil.Coordinates.Y+Dificil.tamanhoCaixa.heigth)){
				    	break;
				    }
				    else{
			            if(tela_Atual<8){
			                tela_Atual++;
			            }
			        }
			    	glutPostRedisplay();
	        }
         break;

    default:
         break;

   }
  }

}
/******************************************************/

void atualiza_Cena(void){

    // Cor para limpar a tela
    glClearColor(0.6, 0.6, 0.6, 0);// Branco

    //Define as coordenadas do solo e da nave
    Jogar.Coordinates.X = 300; //-25
    Jogar.Coordinates.Y = 780; //-15
    Jogar.tamanhoCaixa.width = largura_Base; //+50
    Jogar.tamanhoCaixa.heigth = altura_Base; //+30

    Dificuldade.Coordinates.X = 300;
    Dificuldade.Coordinates.Y = 610;
    Dificuldade.tamanhoCaixa.width = largura_Base;
    Dificuldade.tamanhoCaixa.heigth = altura_Base;

    Instrucoes.Coordinates.X = 300;
    Instrucoes.Coordinates.Y = 440;
    Instrucoes.tamanhoCaixa.width = largura_Base;
    Instrucoes.tamanhoCaixa.heigth = altura_Base;

    Configuracoes.Coordinates.X = 300;
    Configuracoes.Coordinates.Y = 270;
    Configuracoes.tamanhoCaixa.width = largura_Base;
    Configuracoes.tamanhoCaixa.heigth = altura_Base;

    Sair.Coordinates.X = 300;
    Sair.Coordinates.Y = 100;
    Sair.tamanhoCaixa.width = largura_Base;
    Sair.tamanhoCaixa.heigth = altura_Base;

    Facil.Coordinates.X = 50;
    Facil.Coordinates.Y = 780;
    Facil.tamanhoCaixa.width = 200;
    Facil.tamanhoCaixa.heigth = 60;

    Medio.Coordinates.X = 50;
    Medio.Coordinates.Y = 610;
    Medio.tamanhoCaixa.width = 200;
    Medio.tamanhoCaixa.heigth = 60;

    Dificil.Coordinates.X = 50;
    Dificil.Coordinates.Y = 440;
    Dificil.tamanhoCaixa.width = 200;
    Dificil.tamanhoCaixa.heigth = 60;

}
/******************************************************/

/******************************************************/
void desenha_Titulo() {

	//int glutBitmapLength(void * font, char *string){
	//}

	//int glutBitmapHeight ( void *font );


    //glColor3f(1, 1, 1);

    if(tela_Atual<=5){

	    if(tela_Atual==1){
	        //escreve_Texto(GLUT_BITMAP_HELVETICA_18, "JOGAR", 500-((double)(glutBitmapLength(GLUT_BITMAP_HELVETICA_18,string))/2), 840-(double)(glutBitmapHeight(GLUT_BITMAP_HELVETICA_18)/2), 0);
	        glColor3f(1, 0, 0);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_18, "PLAY", 430, 820, 0);
	        //escreve_Numero(GLUT_BITMAP_HELVETICA_18, 354.32, 50, 700, 0);
	    }
	    else{
	    	glColor3f(1, 1, 1);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "PLAY", 440, 825, 0);
	    }

	    if(tela_Atual==2){
	    	glColor3f(1, 0, 0);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_18, "HELP", 430, 650, 0);
	    }
	    else{
	    	glColor3f(1, 1, 1);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "HELP", 440, 655, 0);
	    }

	    if(tela_Atual==3){
	    	glColor3f(1, 0, 0);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_18, "HIGHSCORES", 370, 482, 0);
	    }
	    else{
	    	glColor3f(1, 1, 1);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "HIGHSCORES", 395, 488, 0);
	    }

	    if(tela_Atual==4){
	    	glColor3f(1, 0, 0);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_18, "CREDITS", 400, 310, 0);
	    }
	    else{
	    	glColor3f(1, 1, 1);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "CREDITS", 420, 315, 0);
	    }

	    if(tela_Atual==5){
	    	glColor3f(1, 0, 0);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_18, "SAIR", 430, 145, 0);
	    }
	    else{
	    	glColor3f(1, 1, 1);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "SAIR", 440, 150, 0);
	    }
	}

	if(tela_Atual>5){

		glColor3f(0, 0, 0);

		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "Selecione a dificuldade:", 70, 850, 0);

	    if(tela_Atual==6){
	    	glColor3f(1, 0, 0);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_18, "FACIL", 100, 820, 0);
	    }
	    else{
	    	glColor3f(1, 1, 1);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "FACIL", 70, 825, 0);
	    }

	    if(tela_Atual==7){
	    	glColor3f(1, 0, 0);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_18, "MEDIO", 100, 650, 0);
	    }
	    else{
	    	glColor3f(1, 1, 1);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "MEDIO", 70, 655, 0);
	    }

	    if(tela_Atual==8){
	    	glColor3f(1, 0, 0);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_18, "DIFICIL", 100, 482, 0);
	    }
	    else{
	    	glColor3f(1, 1, 1);
	        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "DIFICIL", 70, 488, 0);
	    }
	}

	glColor3f(1, 1, 1);

    glutSwapBuffers();

    //teste_Velocidade=teste_Altitude=teste_Aceleracao=teste_Velocidade + 0.2352;
}

void desenha_Retangulo(){

    glClear(GL_COLOR_BUFFER_BIT);

    //if(){

	    glEnable(GL_TEXTURE_2D);

	    glBindTexture(GL_TEXTURE_2D, menuBackground);
	    glBegin(GL_TRIANGLE_FAN);
	        // Associamos um canto da textura para cada vértice
	        glTexCoord2f(0, 0); glVertex3f(0, 0,  0);
	        glTexCoord2f(1, 0); glVertex3f(1000, 0,  0);
	        glTexCoord2f(1, 1); glVertex3f(1000,  1000,  0);
	        glTexCoord2f(0, 1); glVertex3f(0,  1000,  0);
	    glEnd();
	    glDisable(GL_TEXTURE_2D);

	if(tela_Opcoes==0){	    

		if(tela_Atual<=5){

		    //Opção Jogar
		    glColor4f(0,0,0,0);

		    if(tela_Atual==1){
		        glColor4f(1,0,0,0);
		        Jogar.Coordinates.X += (-25);
		        Jogar.Coordinates.Y += (-15);
		        Jogar.tamanhoCaixa.width += (+50);
		        Jogar.tamanhoCaixa.heigth += (+30);
		    }

		    glBegin(GL_TRIANGLE_FAN);
		        glVertex2f(Jogar.Coordinates.X, Jogar.Coordinates.Y);
		        glVertex2f(Jogar.Coordinates.X + Jogar.tamanhoCaixa.width, Jogar.Coordinates.Y);
		        glVertex2f(Jogar.Coordinates.X + Jogar.tamanhoCaixa.width, Jogar.Coordinates.Y + Jogar.tamanhoCaixa.heigth);
		        glVertex2f(Jogar.Coordinates.X, Jogar.Coordinates.Y + Jogar.tamanhoCaixa.heigth);
		    glEnd();

		    glColor4f(0,0,0,0);

		    if(tela_Atual==2){
		        glColor4f(1,0,0,0);
		        Dificuldade.Coordinates.X += (-25);
		        Dificuldade.Coordinates.Y += (-15);
		        Dificuldade.tamanhoCaixa.width += (+50);
		        Dificuldade.tamanhoCaixa.heigth += (+30);
		    }

		    glBegin(GL_TRIANGLE_FAN);
		        glVertex2f(Dificuldade.Coordinates.X, Dificuldade.Coordinates.Y);
		        glVertex2f(Dificuldade.Coordinates.X + Dificuldade.tamanhoCaixa.width, Dificuldade.Coordinates.Y);
		        glVertex2f(Dificuldade.Coordinates.X + Dificuldade.tamanhoCaixa.width, Dificuldade.Coordinates.Y + Dificuldade.tamanhoCaixa.heigth);
		        glVertex2f(Dificuldade.Coordinates.X, Dificuldade.Coordinates.Y + Dificuldade.tamanhoCaixa.heigth);
		    glEnd();

		    glColor4f(0,0,0,0);

		    if(tela_Atual==3){
		        glColor4f(1,0,0,0);
		        Instrucoes.Coordinates.X += (-25);
		        Instrucoes.Coordinates.Y += (-15);
		        Instrucoes.tamanhoCaixa.width += (+50);
		        Instrucoes.tamanhoCaixa.heigth += (+30);
		    }

		    glBegin(GL_TRIANGLE_FAN);
		        glVertex2f(Instrucoes.Coordinates.X, Instrucoes.Coordinates.Y);
		        glVertex2f(Instrucoes.Coordinates.X + Instrucoes.tamanhoCaixa.width, Instrucoes.Coordinates.Y);
		        glVertex2f(Instrucoes.Coordinates.X + Instrucoes.tamanhoCaixa.width, Instrucoes.Coordinates.Y + Instrucoes.tamanhoCaixa.heigth);
		        glVertex2f(Instrucoes.Coordinates.X, Instrucoes.Coordinates.Y + Instrucoes.tamanhoCaixa.heigth);
		    glEnd();

		    glColor4f(0,0,0,0);

		    if(tela_Atual==4){
		        glColor4f(1,0,0,0);
		        Configuracoes.Coordinates.X += (-25);
		        Configuracoes.Coordinates.Y += (-15);
		        Configuracoes.tamanhoCaixa.width += (+50);
		        Configuracoes.tamanhoCaixa.heigth += (+30);
		    }

		    glBegin(GL_TRIANGLE_FAN);
		        glVertex2f(Configuracoes.Coordinates.X, Configuracoes.Coordinates.Y);
		        glVertex2f(Configuracoes.Coordinates.X + Configuracoes.tamanhoCaixa.width, Configuracoes.Coordinates.Y);
		        glVertex2f(Configuracoes.Coordinates.X + Configuracoes.tamanhoCaixa.width, Configuracoes.Coordinates.Y + Configuracoes.tamanhoCaixa.heigth);
		        glVertex2f(Configuracoes.Coordinates.X, Configuracoes.Coordinates.Y + Configuracoes.tamanhoCaixa.heigth);
		    glEnd();

		    glColor4f(0,0,0,0);

		    if(tela_Atual==5){
		        glColor4f(1,0,0,0);
		        Sair.Coordinates.X += (-25);
		        Sair.Coordinates.Y += (-15);
		        Sair.tamanhoCaixa.width += (+50);
		        Sair.tamanhoCaixa.heigth += (+30);
		    }

		    glBegin(GL_TRIANGLE_FAN);
		        glVertex2f(Sair.Coordinates.X, Sair.Coordinates.Y);
		        glVertex2f(Sair.Coordinates.X + Sair.tamanhoCaixa.width, Sair.Coordinates.Y);
		        glVertex2f(Sair.Coordinates.X + Sair.tamanhoCaixa.width, Sair.Coordinates.Y + Sair.tamanhoCaixa.heigth);
		        glVertex2f(Sair.Coordinates.X, Sair.Coordinates.Y + Sair.tamanhoCaixa.heigth);
		    glEnd();

		    desenha_Titulo();

		}

		if(tela_Atual>5){

			glColor4f(0,0,0,0);

			if(tela_Atual==6){
		        glColor4f(1,0,0,0);
		        Facil.Coordinates.X += (-8);
		        Facil.Coordinates.Y += (-5);
		        Facil.tamanhoCaixa.width += (+16);
		        Facil.tamanhoCaixa.heigth += (+10);
		    }

			glBegin(GL_TRIANGLE_FAN);
		        glVertex2f(Facil.Coordinates.X, Facil.Coordinates.Y);
		        glVertex2f(Facil.Coordinates.X + Facil.tamanhoCaixa.width, Facil.Coordinates.Y);
		        glVertex2f(Facil.Coordinates.X + Facil.tamanhoCaixa.width, Facil.Coordinates.Y + Facil.tamanhoCaixa.heigth);
		        glVertex2f(Facil.Coordinates.X, Facil.Coordinates.Y + Facil.tamanhoCaixa.heigth);
		    glEnd();

		    glColor4f(0,0,0,0);

		    if(tela_Atual==7){
		        glColor4f(1,0,0,0);
		        Medio.Coordinates.X += (-8);
		        Medio.Coordinates.Y += (-5);
		        Medio.tamanhoCaixa.width += (+16);
		        Medio.tamanhoCaixa.heigth += (+10);
		    }

		    glBegin(GL_TRIANGLE_FAN);
		        glVertex2f(Medio.Coordinates.X, Medio.Coordinates.Y);
		        glVertex2f(Medio.Coordinates.X + Medio.tamanhoCaixa.width, Medio.Coordinates.Y);
		        glVertex2f(Medio.Coordinates.X + Medio.tamanhoCaixa.width, Medio.Coordinates.Y + Medio.tamanhoCaixa.heigth);
		        glVertex2f(Medio.Coordinates.X, Medio.Coordinates.Y + Medio.tamanhoCaixa.heigth);
		    glEnd();

		    glColor4f(0,0,0,0);

		    if(tela_Atual==8){
		        glColor4f(1,0,0,0);
		        Dificil.Coordinates.X += (-8);
		        Dificil.Coordinates.Y += (-5);
		        Dificil.tamanhoCaixa.width += (+16);
		        Dificil.tamanhoCaixa.heigth += (+10);
		    }

		    glBegin(GL_TRIANGLE_FAN);
		        glVertex2f(Dificil.Coordinates.X, Dificil.Coordinates.Y);
		        glVertex2f(Dificil.Coordinates.X + Dificil.tamanhoCaixa.width, Dificil.Coordinates.Y);
		        glVertex2f(Dificil.Coordinates.X + Dificil.tamanhoCaixa.width, Dificil.Coordinates.Y + Dificil.tamanhoCaixa.heigth);
		        glVertex2f(Dificil.Coordinates.X, Dificil.Coordinates.Y + Dificil.tamanhoCaixa.heigth);
		    glEnd();

		    desenha_Titulo();

		    escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "Teclas do jogo: ", 420, 770, 0);
		    escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "-W ativa o motor", 350, 720, 0);
		    escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "-A e D mudam a angulacao da nave", 350, 690, 0);
		    escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "-Esc sai do jogo", 350, 660, 0);
		    escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "-P pausa o jogo", 350, 630, 0);
		    escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "-R reinicia o jogo", 350, 600, 0);

		}
	}

	if(tela_Opcoes==2){

		glColor3f(0, 0, 0);

		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "HIGHSCORES", 350, 800, 0);
		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "1..........................", 280, 760, 0);
		escreve_Numero(GLUT_BITMAP_TIMES_ROMAN_24, highscores[0], 550, 760, 0);
		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "2..........................", 280, 730, 0);
		escreve_Numero(GLUT_BITMAP_TIMES_ROMAN_24, highscores[1], 550, 730, 0);
		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "3..........................", 280, 700, 0);
		escreve_Numero(GLUT_BITMAP_TIMES_ROMAN_24, highscores[2], 550, 700, 0);
		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "4..........................", 280, 670, 0);
		escreve_Numero(GLUT_BITMAP_TIMES_ROMAN_24, highscores[3], 550, 670, 0);
		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "5..........................", 280, 640, 0);
		escreve_Numero(GLUT_BITMAP_TIMES_ROMAN_24, highscores[4], 550, 640, 0);
		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "6..........................", 280, 610, 0);
		escreve_Numero(GLUT_BITMAP_TIMES_ROMAN_24, highscores[5], 550, 610, 0);
		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "7..........................", 280, 580, 0);
		escreve_Numero(GLUT_BITMAP_TIMES_ROMAN_24, highscores[6], 550, 580, 0);
		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "8..........................", 280, 550, 0);
		escreve_Numero(GLUT_BITMAP_TIMES_ROMAN_24, highscores[7], 550, 550, 0);
		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "9..........................", 280, 520, 0);
		escreve_Numero(GLUT_BITMAP_TIMES_ROMAN_24, highscores[8], 550, 520, 0);
		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "10.........................", 280, 490, 0);
		escreve_Numero(GLUT_BITMAP_TIMES_ROMAN_24, highscores[9], 550, 490, 0);
	}

	if(tela_Opcoes==1){

		glColor3f(0, 0, 0);

		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "CREDITS", 370, 800, 0);
		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "Art by Rafael Schittini", 200, 720, 0);
		escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "Coding by Vitor Mendes and Rafael Schittini", 200, 690, 0);
		//escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "Music:", 330, 650, 0);
	}

		glColor3f(1, 1, 1);

    glutSwapBuffers();
}
/******************************************************/

void desenha_Menu(){

	desenha_Retangulo();

    atualiza_Cena();
}

void atualiza_Menu() {

	glutPassiveMotionFunc(movimentoMouse);

	glutPostRedisplay();
	
	glutMouseFunc(OnMouseClick);

}