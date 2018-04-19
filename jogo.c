#include "jogo.h"
#define PI 3.14159

//Global Variables && flags//
double Gravity;
double tempof;
double impulse=0.004;
int angulo;
double anguloradian;
unsigned int tecladao[128];
int n_meteoros;
int cena;
int verdade;
int gasolina;
int vida_nave;
double produto;
int nexplosao;
int ganhou;
float calculodapontuacao;
int dificuldade;
//Global Variables//

//Global structures//
Colision objnave;
Ship nave;

Solo solo;

Coord gravidade;
Coord impulso;
Coord nuvem[10];
Coord animacao[4];

meteor meteoro[100];
linha linhas[15];

GLuint textura_nave;
GLuint textura_fundo;
GLuint textura_animado[4];
GLuint textura_nuvem;
GLuint textura_explosao[8];
GLuint textura_meteoro;
GLuint textura_vida;
//Global structures//

void tocar_musica(char const nome[40], int loop){
        Mix_Chunk *som = NULL;
        int canal;
        int canal_audio=2;
        int taxa_audio = 22050;
        Uint16 formato_audio = AUDIO_S16SYS;
        int audio_buffers = 4096;
        if(Mix_OpenAudio(taxa_audio, formato_audio, canal_audio, audio_buffers) != 0) {
                printf("Não pode inicializar audio: %s\n", Mix_GetError());
        }
       som = Mix_LoadWAV(nome);
        if(som == NULL) {
                printf("Não pode inicializar audio: %s\n", Mix_GetError());
        }
       Mix_HaltChannel(-1);
       canal = Mix_PlayChannel( -1, som, loop);
        if(canal == -1) {
                printf("Não pode inicializar audio: %s\n", Mix_GetError());
        }
}

void parar_musica(){
    Mix_HaltChannel(-1);
}

void delay(int v){

    int c, d, k;
 
    for(k=0; k<v; k++){
       for (c = 1; c <= 10000; c++)
           for (d = 1; d <= 10000; d++){
           }
    }
}


void escreve_Texto(void * font, char *s, double x, double y, double z) {
    int i;
    glRasterPos3f(x, y, z);

    for (i = 0; i < strlen(s); i++) {
        glutBitmapCharacter(font, s[i]);
    }
}

void escreve_Numero(void * font, double numero, double x, double y, double z) {
    int i;
    glRasterPos3f(x, y, z);

    char array_Inteiros[50];

    sprintf(array_Inteiros, "%.2f", numero);

    for (i = 0; i < strlen(array_Inteiros); i++) {
        glutBitmapCharacter(font, array_Inteiros[i]);
    }
}

void teclado4(unsigned char key, int x, int y)
{
    ////Keyboard events////

    if(tela_Atual==9){

        switch(key)
        {
        case 'w':
            tempof=0;
            tecladao[key]=0;
            break;

        case 'a':
            tecladao[key]=0;
            break;

        case 'd':
            tecladao[key]=0;
            break;
           
        case 's':
            //tecladao[key]=0;
            break;

        default:
            break;
        }
    }
    ////Keyboard events////

}

void teclado3(unsigned char key, int x, int y)
{

        switch(key)
        {

        // Tecla ESC
        case 27:
            tecladao[112]=1;
            tecladao[key]=1;
            glutPostRedisplay();
            break;

        case 'w':
            tecladao[key]=1;
            break;

        case 'a':
            tecladao[key]=1;
            break;

        case 'd':
            tecladao[key]=1;
            break;
        case 'r':
            tecladao[key]=1;
            tecladao[112]=1;
            glutPostRedisplay();
            break;

        case 'p':
            if(tecladao[key]==1){
                tecladao[key]=0;
                break;
            }
            else if(tecladao[key]==0){
                tecladao[key]=1;
                glutPostRedisplay();
            }
            break;

        default:
            break;
        }

        if(tecladao[114]==1){

            switch(key){

                case 's':
                    parar_musica();
                    tocar_musica("Ambient-Space-Music-Shooting-Stars.ogg", 1);
                    verdade=1;
                    tecladao[112]=0;
                    tecladao[115]=1;
                    tecladao[114]=0;
                    break;

                case 'n':
                    tecladao[112]=0;
                    tecladao[114]=0;
                    break;
            }
        }

        if(tecladao[27]==1){

            switch(key){

                case 's':
                    exit(0);
                    break;

                case 'n':
                    tecladao[112]=0;
                    tecladao[27]=0;
                    break;
            }
        }
}


void atualizanave()
{
    //////Calculates and animates Spaceship related things//////

    nave.Coordi.Y+=nave.Vel.Y;
    nave.Coordi.X+=nave.Vel.X;

    if(nave.explosao==1){
        vida_nave=0;
        nave.Vel.X=0;
        nave.Vel.Y=0;
    }

    if(tecladao[119]==1)
    {
        if(gasolina>0)
        {
            if(tempof==0&&gasolina>0)
            {
                tempof+=1;
            }

            if(nave.Coordi.Y>=(solo.tamanhoSolo.heigth+0.2)&&tempof>0)
            {
                if(tempof==0)
                {
                    textura_nave = SOIL_load_OGL_texture(
                                       "fogo3.png",
                                       SOIL_LOAD_AUTO,
                                       SOIL_CREATE_NEW_ID,
                                       SOIL_FLAG_INVERT_Y);
                    if(textura_nave==0)
                    {
                        printf("erro:%s",SOIL_last_result());
                    }
                }
                if(tempof>0 && tempof<=1.25)
                {
                    textura_nave = SOIL_load_OGL_texture(
                                       "fogo2.png",
                                       SOIL_LOAD_AUTO,
                                       SOIL_CREATE_NEW_ID,
                                       SOIL_FLAG_INVERT_Y);
                    if(textura_nave==0)
                    {
                        printf("erro:%s",SOIL_last_result());
                    }
                }
                else if(tempof>0 && tempof>1.25)
                {
                    textura_nave = SOIL_load_OGL_texture(
                                       "fogo1.png",
                                       SOIL_LOAD_AUTO,
                                       SOIL_CREATE_NEW_ID,
                                       SOIL_FLAG_INVERT_Y);
                    if(textura_nave==0)
                    {
                        printf("erro:%s",SOIL_last_result());
                    }
                }
            }



            if(tempof<3)
            {
                tempof+=0.25;

            }


            if(nave.Coordi.Y<=solo.tamanhoSolo.heigth)
            {
                textura_nave = SOIL_load_OGL_texture(
                                   "fogopousado3.png",
                                   SOIL_LOAD_AUTO,
                                   SOIL_CREATE_NEW_ID,
                                   SOIL_FLAG_INVERT_Y);
                if(textura_nave==0)
                {
                    printf("erro:%s",SOIL_last_result());
                }
            }
            if(nave.Coordi.Y>=(solo.tamanhoSolo.heigth+0.1) && nave.Coordi.Y<(solo.tamanhoSolo.heigth+0.2))
            {
                textura_nave = SOIL_load_OGL_texture(
                                   "fogo1.png",
                                   SOIL_LOAD_AUTO,
                                   SOIL_CREATE_NEW_ID,
                                   SOIL_FLAG_INVERT_Y);
                if(textura_nave==0)
                {
                    printf("erro:%s",SOIL_last_result());
                }
            }
            if(nave.Coordi.Y>solo.tamanhoSolo.heigth && nave.Coordi.Y<(solo.tamanhoSolo.heigth+0.1))
            {
                textura_nave = SOIL_load_OGL_texture(
                                   "fogopousado2.png",
                                   SOIL_LOAD_AUTO,
                                   SOIL_CREATE_NEW_ID,
                                   SOIL_FLAG_INVERT_Y);
                if(textura_nave==0)
                {
                    printf("erro:%s",SOIL_last_result());
                }
            }
            gasolina--;

            if(gasolina<=0)
            {
                tempof=0;
            }
        }
    }
    if(nave.Coordi.Y>solo.tamanhoSolo.heigth)
    {
        nave.Vel.Y+=-Gravity;
    }
    else if(nave.Coordi.Y<=solo.tamanhoSolo.heigth)
    {

        nave.Coordi.Y=solo.tamanhoSolo.heigth;
        nave.Vel.X=0;
        if(tecladao[119]==0)
        {
            textura_nave = SOIL_load_OGL_texture(
                               "Sprite-0003.png",
                               SOIL_LOAD_AUTO,
                               SOIL_CREATE_NEW_ID,
                               SOIL_FLAG_INVERT_Y);
            if(textura_nave==0)
            {
                printf("erro:%s",SOIL_last_result());
            }
        }
    }

    if(cena==1){
        if(nave.Coordi.X<=0)
        {
            nave.Vel.X=0;
            nave.Coordi.X=0;
        }
        if(nave.Coordi.X>=140)
        {
            nave.Coordi.X=140;
            nave.Vel.X=0;
        }

    }

    if(cena==2)
    {
        if(nave.Coordi.X<=0)
        {
            nave.Vel.X=0;
            nave.Coordi.X=0;
        }
        if(nave.Coordi.Y>=470)
        {
            nave.Vel.Y=0;
            nave.Coordi.Y=470;
        }
        if(nave.Coordi.Y<=0)
        {
            nave.Vel.Y=0;
            nave.Coordi.Y=0 ;
        }
        if(nave.Coordi.X>=630)
        {
            nave.Coordi.X=630;
            nave.Vel.X=0;
        }
        if(nave.Coordi.X>=560 && nave.Coordi.X<=620 && nave.Coordi.Y>=400 && nave.Coordi.Y<=465)
        {
            cena=3;
            verdade=1;
        }
    }
    if(cena==3)
    {
        if(nave.Coordi.X<=0)
        {
            nave.Vel.X=0;
            nave.Coordi.X=0;
        }
        if(nave.Coordi.Y>=190)
        {
            nave.Vel.Y=0;
            nave.Coordi.Y=190;
        }
        if(nave.Coordi.X>=390)
        {
            nave.Coordi.X=390;
            nave.Vel.X=0;
        }

    }
    if(nave.Coordi.Y>solo.tamanhoSolo.heigth && tecladao[119]==0)
    {
        textura_nave = SOIL_load_OGL_texture(
                           "Sprite-0002.png",
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y);
        if(textura_nave==0)
        {
            printf("erro:%s",SOIL_last_result());
        }
    }
    if(nave.Coordi.Y>=(solo.tamanhoSolo.heigth+0.1) && tecladao[119]==0)
    {
        textura_nave = SOIL_load_OGL_texture(
                           "Sprite-0001.png",
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y);
        if(textura_nave==0)
        {
            printf("erro:%s",SOIL_last_result());
        }
    }
    nave.Vel.Y+=impulse*tempof*sin(anguloradian);
    nave.Vel.X+=impulse*tempof*cos(anguloradian);

    if(tecladao[97]==1&&nave.Coordi.Y>solo.tamanhoSolo.heigth)
    {
        angulo+=4;
    }
    if(tecladao[100]==1&&nave.Coordi.Y>solo.tamanhoSolo.heigth)
    {
        angulo-=4;
    }

    anguloradian=angulo*(PI/180);
    if(nave.Coordi.Y<=solo.tamanhoSolo.heigth && ((angulo!=90&&angulo>98||angulo<82)||nave.Vel.Y<-0.4))
    {
        nave.Vel.Y=0;
        nave.explosao=1;

    }
    if(nave.Coordi.Y>=150 && cena==1)
    {
        verdade=1;
        cena=2;
    }
    if(vida_nave==0)
    {
        nave.explosao=1;
    }

    //////Calculates and animates Spaceship related things//////
}


void atualizameteoros()
{
    //tells the new position of meteors//
    int k;
    for(k=0; k<n_meteoros; k++)
    {
        if(meteoro[k].explodiu==0)
        {
            meteoro[k].pos.Y+=meteoro[k].vel.Y;
            meteoro[k].pos.X+=meteoro[k].vel.X;
        }
    }
    //tells the new position of meteors//

}


void desenhalinhasdecolisao()
{
    //Function for debugging//
    //Draws Collision hitboxes//
    int k;
    glColor3f(1,0,0);
    for(k=0; k<15; k++)
    {
        glBegin(GL_LINES);
        glVertex2f(linhas[k].pos1.X,linhas[k].pos1.Y);
        glVertex2d(linhas[k+1].pos1.X,linhas[k+1].pos1.Y);
        glEnd();
        glPushMatrix();
        glTranslatef(linhas[k].pos1.X,linhas[k].pos1.Y,0);
        glBegin(GL_LINES);
        glVertex2f(0,0);
        glVertex2f(2*linhas[k].posnorm.X,2*linhas[k].posnorm.Y);
        glEnd();
        glPopMatrix();

    }
    //Draws Collision hitboxes//



}

void desenharposicoesmeteoro()
{
    //Calculates meteor's positions//
    srand(time(0));
    int k;
    int r2;
    int r;
    r=rand()%100;
    r=r+30;
    meteoro[0].pos.X=r;
    meteoro[0].pos.Y=nave.Coordi.Y+150;
    for(k=1; k<n_meteoros; k++)
    {
        r=rand()%80;
        r2=rand()%100;
        r2=r2+60;
        if(meteoro[k-1].pos.X>=620)
        {
            meteoro[k].pos.X=r2+50;
            meteoro[k].pos.Y=nave.Coordi.Y+140+r;
        }
        else
        {
            meteoro[k].pos.X=meteoro[k-1].pos.X+r2;
            meteoro[k].pos.Y=meteoro[k-1].pos.Y+40+r;
        }

    }
    double v;
    double velx;
    for(k=0; k<n_meteoros; k++)
    {
        v=rand()%100-0.2;
        v=v/400;
        velx=rand()%50-0.1;
        velx=velx/500;
        meteoro[k].vel.Y=-v;
        meteoro[k].vel.X=-velx;
    }
    //Calculates meteor's positions//
}




void checacena()
{

    //Changes scenes based on a event listener//
    if(tecladao[114]==1 || tecladao[115]==1){
        cena=1;
        tecladao[115]=0;
    }
    if(cena==3)
    {
        textura_fundo = SOIL_load_OGL_texture(
                            "marte.png",
                            SOIL_LOAD_AUTO,
                            SOIL_CREATE_NEW_ID,
                            SOIL_FLAG_INVERT_Y);
        glClear(GL_COLOR_BUFFER_BIT);
        Gravity=0.003;
        impulse=0.002;
        nave.Coordi.X=5;
        nave.Coordi.Y=170;
        if(nave.Vel.X>0.5){
        nave.Vel.X=1;
        }
        else{
        nave.Vel.X=0.5;
        }
        n_meteoros=0;
        verdade=0;

    }

    if(cena==2)
    {
        Gravity=0;
        nave.Coordi.X=25;
        nave.Coordi.Y=20;
        nave.Vel.X=0.1;
        nave.Vel.Y=0.1;
        impulse=0.006;
        solo.tamanhoSolo.heigth=-10;
        textura_fundo = SOIL_load_OGL_texture(
                            "Terra-marte2.png",
                            SOIL_LOAD_AUTO,
                            SOIL_CREATE_NEW_ID,
                            SOIL_FLAG_INVERT_Y);
        glClear(GL_COLOR_BUFFER_BIT);
        if(dificuldade==1){
            n_meteoros=50;
        }
        if(dificuldade==2){
            n_meteoros=70;
        }
        if(dificuldade==3){
            n_meteoros=100;
        }


        desenharposicoesmeteoro();
        verdade=0;
    }

    if(cena==1){

        nave.Coordi.X = 14.6;
        nave.Coordi.Y = 7;

        solo.tamanhoSolo.width = 640;
        solo.tamanhoSolo.heigth = 7;

        Gravity = 0.1;
        tempof = 0;
        impulse = 0.04;
        angulo = 90;
        anguloradian = 0;
        n_meteoros = 0;
        verdade = 0;
        gasolina = 1000;
        vida_nave = 3;
        produto = 0;
        nexplosao = 0;
        ganhou=0;
        nave.explosao=0;

        //Initial values//
        //glClearColor(1, 1, 1, 0);

        nave.Vel.Y=0;

        animacao[0].X=0;
        animacao[0].Y=0;

    }
    //Changes scenes based on a event listener//

}


double colisionball_line(int k)
{
    //Collision between a Ball and a Line implementation//
    double magnitude;
    Coord normal;
    Coord produtoescalar;
    magnitude = sqrt(pow(linhas[k].posnorm.X,2)+pow(linhas[k].posnorm.Y,2));
    normal.X = linhas[k].posnorm.X/magnitude;
    normal.Y = linhas[k].posnorm.Y/magnitude;
    produtoescalar.X=objnave.cnormal.X*normal.X;
    produtoescalar.Y=objnave.cnormal.Y*normal.Y;
    return (produtoescalar.X+produtoescalar.Y);
    //Collision between a Ball and a Line implementation//

}

void Arquivodepontuacao(float pontuacao){
    int k;
    float valor[10];
    FILE* arquivo;
    
    
    arquivo = fopen("pontuacao.txt","r");

    for(k=0;k<10;k++){
         if(fscanf(arquivo,"%f*",valor+k)==0||fscanf(arquivo,"%f*",valor+k)==EOF){
            printf("atendeu a condicao");
            fclose(arquivo);
            arquivo = fopen("pontuacao.txt","a+");
            fprintf(arquivo, "%f*" ,pontuacao);
            fclose(arquivo);
            break;
         }
         else if(fscanf(arquivo,"%f*",valor+k)==1){
            if(pontuacao>*(valor+k)){
                printf("a pontuacao foi sobrescrita");
                fclose(arquivo);
                arquivo = fopen("pontuacao.txt","a+");
                fprintf(arquivo,"%f*",pontuacao);
                fclose(arquivo);
                break;
            }
         }
    }
}

void colisiondetect()
{
    //Collision detection
    int k;
    int x;

    if(cena==2){

        for(k=0; k<n_meteoros; k++)
        {
            if(meteoro[k].explodiu==0)
            {
                if(sqrt(pow(meteoro[k].pos.X-(nave.Coordi.X+5),2)+pow(meteoro[k].pos.Y-(nave.Coordi.Y+5),2))<7.5)
                {

                    if(meteoro[k].vel.X>=0)
                        nave.Vel.X+=-meteoro[k].vel.X;
                    else
                        nave.Vel.X+=meteoro[k].vel.X;
                    if(meteoro[k].vel.Y>=0)
                        nave.Vel.Y+=-meteoro[k].vel.Y;
                    else
                        nave.Vel.Y+=meteoro[k].vel.Y;

                    meteoro[k].vel.X=0;
                    meteoro[k].vel.Y=0;


                    vida_nave--;

                    meteoro[k].explodiu=1;
                }
            }
        }
    }

    if(cena==3)
    {
        if(nave.Coordi.X<22)
        {
            k=0;
        }
        if(nave.Coordi.X<46&&nave.Coordi.X>=22)
        {
            k=1;
        }
        if(nave.Coordi.X<81&&nave.Coordi.X>=46)
        {
            k=2;
        }
        if(nave.Coordi.X<107&&nave.Coordi.X>=81)
        {
            k=3;
        }
        if(nave.Coordi.X<122&&nave.Coordi.X>=107)
        {
            k=4;
        }
        if(nave.Coordi.X<163 && nave.Coordi.X>=122)
        {
            k=5;
        }
        if(nave.Coordi.X<192&&nave.Coordi.X>=163)
        {
            k=6;
        }
        if(nave.Coordi.X<212&&nave.Coordi.X>=192)
        {
            k=7;
        }
        if(nave.Coordi.X<262&&nave.Coordi.X>=212)
        {
            k=8;
        }
        if(nave.Coordi.X<302&&nave.Coordi.X>=262)
        {
            k=9;
        }
        if(nave.Coordi.X<334&&nave.Coordi.X>=302)
        {
            k=10;
        }
        if(nave.Coordi.X<344&&nave.Coordi.X>=334)
        {
            k=11;
        }
        if(nave.Coordi.X<359&&nave.Coordi.X>=344)
        {
            k=12;
        }
        if(nave.Coordi.X<366&&nave.Coordi.X>=359)
        {
            k=13;
        }
        if(nave.Coordi.X<400&&nave.Coordi.X>=366)
        {
            k=14;
        }

        objnave.centro.X=nave.Coordi.X+5;
        objnave.centro.Y=nave.Coordi.Y+5;
        objnave.cnormal.X=objnave.centro.X-linhas[k].pos1.X;
        objnave.cnormal.Y=objnave.centro.Y-linhas[k].pos1.Y;
        produto = colisionball_line(k);
        if(produto<=4.9 && ganhou==0)
        {
            
            if(((k==1||k==3||k==5||k==7||k==9||k==12||k==14)&&(produto<=4.9&&produto>=4.4))&&(nave.Vel.Y>=-0.4&&(angulo<=98||angulo>=82)))
            {
                if(nave.explosao==0&&ganhou==0)
                {

                    solo.tamanhoSolo.heigth=nave.Coordi.Y-0.2;
                    //double calculodapontuacao;
                    if(k==1 || k==3){
                        calculodapontuacao=vida_nave*2+gasolina;
                    }
                    if(k==5||k==9){
                        calculodapontuacao=vida_nave*3+gasolina;
                    }
                    if(k==7||k==14){
                        calculodapontuacao=vida_nave*4+gasolina;
                    }
                    if(k==12){
                        calculodapontuacao=vida_nave*5+gasolina;
                    }
                    Arquivodepontuacao(calculodapontuacao);


                }
                ganhou=1;

                glutPostRedisplay();

            }
            if(((k==0||k==2||k==4||k==6||k==8||k==10||k==11||k==13)&&((angulo!=90&&angulo>98||angulo<82)||nave.Vel.Y<-0.4)) && (nave.explosao==0))
            {
                nave.explosao=1;
            }
        }
    }

    //Collision detection
}

void atualiza_Jogo(int indice)
{
    //Event listeners//
    atualizanave();

    atualizameteoros();
    if(verdade==1)
    {
        glutTimerFunc(0,checacena,0);
    }
    if(cena==2||cena==3){
        colisiondetect();
    }
    glutPostRedisplay ();
    //Event listeners//
}

void inicializa_Jogo(void)
{

    Gravity = 0.1;
    tempof = 0;
    impulse = 0.04;
    angulo = 90;
    anguloradian = 0;
    n_meteoros = 0;
    cena = 1;
    verdade = 1;
    gasolina = 1000;
    vida_nave = 3;
    produto = 0;
    nexplosao = 0;
    ganhou=0;

    int k;

    //Initial values//
    glClearColor(1, 1, 1, 0);

    solo.tamanhoSolo.width = 640;
    solo.tamanhoSolo.heigth = 7;

    nave.Coordi.X = 15.6;
    nave.Coordi.Y = 7;
    nave.Vel.Y=0;
    nave.tamanhoNave.width = 10;
    nave.tamanhoNave.heigth = 10;

    animacao[0].X=0;
    animacao[0].Y=0;

    //Initial values//




    ////Loading textures////

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


    textura_explosao[0] = SOIL_load_OGL_texture(
                              "explosao1.png",
                              SOIL_LOAD_AUTO,
                              SOIL_CREATE_NEW_ID,
                              SOIL_FLAG_INVERT_Y);
    if(textura_explosao[0]==0)
    {
        printf("erro:%s",SOIL_last_result());
    }
    textura_explosao[1] = SOIL_load_OGL_texture(
                              "explosao2.png",
                              SOIL_LOAD_AUTO,
                              SOIL_CREATE_NEW_ID,
                              SOIL_FLAG_INVERT_Y);
    if(textura_explosao[1]==0)
    {
        printf("erro:%s",SOIL_last_result());
    }
    textura_explosao[2] = SOIL_load_OGL_texture(
                              "explosao3.png",
                              SOIL_LOAD_AUTO,
                              SOIL_CREATE_NEW_ID,
                              SOIL_FLAG_INVERT_Y);
    if(textura_explosao[2]==0)
    {
        printf("erro:%s",SOIL_last_result());
    }
    textura_explosao[3] = SOIL_load_OGL_texture(
                              "explosao4.png",
                              SOIL_LOAD_AUTO,
                              SOIL_CREATE_NEW_ID,
                              SOIL_FLAG_INVERT_Y);
    textura_explosao[4] = SOIL_load_OGL_texture(
                              "explosao5.png",
                              SOIL_LOAD_AUTO,
                              SOIL_CREATE_NEW_ID,
                              SOIL_FLAG_INVERT_Y);
    textura_explosao[5] = SOIL_load_OGL_texture(
                              "explosao6.png",
                              SOIL_LOAD_AUTO,
                              SOIL_CREATE_NEW_ID,
                              SOIL_FLAG_INVERT_Y);
    textura_explosao[6] = SOIL_load_OGL_texture(
                              "explosao7.png",
                              SOIL_LOAD_AUTO,
                              SOIL_CREATE_NEW_ID,
                              SOIL_FLAG_INVERT_Y);
    textura_explosao[7] = SOIL_load_OGL_texture(
                              "explosao8.png",
                              SOIL_LOAD_AUTO,
                              SOIL_CREATE_NEW_ID,
                              SOIL_FLAG_INVERT_Y);

    textura_nave = SOIL_load_OGL_texture(
                       "Sprite-0001.png",
                       SOIL_LOAD_AUTO,
                       SOIL_CREATE_NEW_ID,
                       SOIL_FLAG_INVERT_Y);
    if(textura_nave==0)
    {
        printf("erro:%s",SOIL_last_result());
    }

    textura_fundo = SOIL_load_OGL_texture(
                        "chao1.bmp",
                        SOIL_LOAD_AUTO,
                        SOIL_CREATE_NEW_ID,
                        SOIL_FLAG_INVERT_Y);
    if(textura_nave==0)
    {
        printf("erro:%s",SOIL_last_result());
    }
    textura_nuvem = SOIL_load_OGL_texture(
                        "cloud.png",
                        SOIL_LOAD_AUTO,
                        SOIL_CREATE_NEW_ID,
                        SOIL_FLAG_INVERT_Y);
    if(textura_nave==0)
    {
        printf("erro:%s",SOIL_last_result());
    }
    textura_animado[0] = SOIL_load_OGL_texture(
                             "chao1.bmp",
                             SOIL_LOAD_AUTO,
                             SOIL_CREATE_NEW_ID,
                             SOIL_FLAG_INVERT_Y);
    if(textura_nave==0)
    {
        printf("erro:%s",SOIL_last_result());
    }
    textura_animado[1] = SOIL_load_OGL_texture(
                             "chao2.bmp",
                             SOIL_LOAD_AUTO,
                             SOIL_CREATE_NEW_ID,
                             SOIL_FLAG_INVERT_Y);
    if(textura_nave==0)
    {
        printf("erro:%s",SOIL_last_result());
    }
    textura_animado[2] = SOIL_load_OGL_texture(
                             "chao3.bmp",
                             SOIL_LOAD_AUTO,
                             SOIL_CREATE_NEW_ID,
                             SOIL_FLAG_INVERT_Y);
    if(textura_nave==0)
    {
        printf("erro:%s",SOIL_last_result());
    }
    textura_animado[3] = SOIL_load_OGL_texture(
                             "chao4.bmp",
                             SOIL_LOAD_AUTO,
                             SOIL_CREATE_NEW_ID,
                             SOIL_FLAG_INVERT_Y);
    if(textura_nave==0)
    {
        printf("erro:%s",SOIL_last_result());
    }
    textura_meteoro = SOIL_load_OGL_texture(
                          "meteoro.png",
                          SOIL_LOAD_AUTO,
                          SOIL_CREATE_NEW_ID,
                          SOIL_FLAG_INVERT_Y);

    textura_vida    = SOIL_load_OGL_texture(
                          "coracao.png",
                          SOIL_LOAD_AUTO,
                          SOIL_CREATE_NEW_ID,
                          SOIL_FLAG_INVERT_Y);

    ////Loading textures////

    linhas[0].pos1.X=0;
    linhas[1].pos1.X=27;
    linhas[2].pos1.X=51;
    linhas[3].pos1.X=86;
    linhas[4].pos1.X=112;
    linhas[5].pos1.X=130;
    linhas[6].pos1.X=168;
    linhas[7].pos1.X=197;
    linhas[8].pos1.X=217;
    linhas[9].pos1.X=267;
    linhas[10].pos1.X=307;
    linhas[11].pos1.X=339;
    linhas[12].pos1.X=349;
    linhas[13].pos1.X=364;
    linhas[14].pos1.X=371;
    linhas[15].pos1.X=400;
    linhas[0].pos1.Y=57;
    linhas[1].pos1.Y=21;
    linhas[2].pos1.Y=21;
    linhas[3].pos1.Y=49;
    linhas[4].pos1.Y=49;
    linhas[5].pos1.Y=86;
    linhas[6].pos1.Y=86;
    linhas[7].pos1.Y=21;
    linhas[8].pos1.Y=21;
    linhas[9].pos1.Y=115;
    linhas[10].pos1.Y=115;
    linhas[11].pos1.Y=143;
    linhas[12].pos1.Y=135;
    linhas[13].pos1.Y=135;
    linhas[14].pos1.Y=148;
    linhas[15].pos1.Y=150;

    for(k=0; k<15; k++)
    {
        linhas[k].vect.X=linhas[k+1].pos1.X-linhas[k].pos1.X;
        linhas[k].vect.Y=linhas[k+1].pos1.Y-linhas[k].pos1.Y;

        if(linhas[k].vect.Y<0&&linhas[k].vect.X>=0)
        {
            linhas[k].posnorm.Y=linhas[k].vect.X;
            linhas[k].posnorm.X=linhas[k].vect.Y*-1;
        }
        if(linhas[k].vect.Y>=0 && linhas[k].vect.X>=0)
        {
            linhas[k].posnorm.Y=linhas[k].vect.X;
            linhas[k].posnorm.X=linhas[k].vect.Y*-1;
        }
    }
    nuvem[0].X=20;
    nuvem[0].Y=80;
    for(k=1; k<10; k++)
    {

        nuvem[k].X=nuvem[k-1].X+20;
        nuvem[k].Y=nuvem[k-1].Y+rand()%40-20;
    }


}

void desenha_Jogo()
{


    ////////////////////Scene 3////////////////////
    if(cena==3)
    {
        int k;
        ////////////////////Camera Movement////////////////////
        glPushMatrix();
        if((nave.Coordi.X-75>0  || nave.Coordi.Y-75>0) && (-nave.Coordi.X+325>0 && -nave.Coordi.Y+125>0))
        {
            if(nave.Coordi.X-75>0 && nave.Coordi.Y-75<0 )
            {
                glTranslatef(-nave.Coordi.X+75,0,0);
            }
            else if(nave.Coordi.X-75<=0  && nave.Coordi.Y-75>=0)
            {
                glTranslatef(0,-nave.Coordi.Y+75,0);
            }
            if(nave.Coordi.X-75>0   && nave.Coordi.Y-75>0)
            {
                glTranslatef(-nave.Coordi.X+75,-nave.Coordi.Y+75,0);
            }



        }
        else if(-nave.Coordi.X+325<=0 || -nave.Coordi.Y+125<=0)
        {
            if(-nave.Coordi.X+325>0 && -nave.Coordi.Y+125<=0 )
            {
                if(nave.Coordi.X>75)
                {
                    glTranslatef(-nave.Coordi.X+75,-50,0);
                }
                else
                    glTranslatef(0,-50,0);

            }
            else if(-nave.Coordi.X+325<=0  && -nave.Coordi.Y+125>=0)
            {
                if(nave.Coordi.Y-75>0)
                {
                    glTranslatef(-250,-nave.Coordi.Y+75,0);
                }
                else
                {
                    glTranslatef(-250,0,0);
                }
            }
            if(-nave.Coordi.X+325<=0 && -nave.Coordi.Y+125<=0)
            {
                glTranslatef(-250,-50,0);
            }


        }
        ////////////////////Camera Movement////////////////////



        ////////////////////Background Texture////////////////////
        glColor4f(1,1,1,1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textura_fundo );

        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0,  0);
        glTexCoord2f(1, 0);
        glVertex3f(400, 0,  0);
        glTexCoord2f(1, 1);
        glVertex3f(400, 200,  0);
        glTexCoord2f(0, 1);
        glVertex3f(0,200,  0);
        glEnd();

        glDisable(GL_TEXTURE_2D);
        ////////////////////Background Texture////////////////////



        ////////////////////SpaceShip Texture////////////////////
        if(nave.explosao==0)
        {
            glColor4f(1,1,1,1);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textura_nave);

            glPushMatrix();
            glTranslatef(nave.Coordi.X+5,nave.Coordi.Y+5,0);
            glRotatef(angulo-90,0,0,1);
            glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0);
            glVertex3f(-nave.tamanhoNave.width/2, -nave.tamanhoNave.heigth/2,  0);
            glTexCoord2f(1, 0);
            glVertex3f((nave.tamanhoNave.width)/2, -nave.tamanhoNave.heigth/2,  0);
            glTexCoord2f(1, 1);
            glVertex3f((nave.tamanhoNave.width)/2, (nave.tamanhoNave.heigth)/2,  0);
            glTexCoord2f(0, 1);
            glVertex3f(-nave.tamanhoNave.width/2,(nave.tamanhoNave.heigth)/2,  0);
            glEnd();
            glPopMatrix();

            glDisable(GL_TEXTURE_2D);
        }



        if(nave.explosao==1)
        {
            glColor4f(1,1,1,1);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textura_explosao[nexplosao]);
            glPushMatrix();

            glTranslatef(nave.Coordi.X+5,nave.Coordi.Y+5,0);
            glRotatef(angulo-90,0,0,1);
            glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0);
            glVertex3f(-nave.tamanhoNave.width/2, -nave.tamanhoNave.heigth/2,  0);
            glTexCoord2f(1, 0);
            glVertex3f((nave.tamanhoNave.width)/2, -nave.tamanhoNave.heigth/2,  0);
            glTexCoord2f(1, 1);
            glVertex3f((nave.tamanhoNave.width)/2, (nave.tamanhoNave.heigth)/2,  0);
            glTexCoord2f(0, 1);
            glVertex3f(-nave.tamanhoNave.width/2,(nave.tamanhoNave.heigth)/2,  0);
            glEnd();
            glPopMatrix();

            glDisable(GL_TEXTURE_2D);
            if(nexplosao<7)
            {
                nexplosao++;
            }
        }
        ////////////////////SpaceShip Texture////////////////////

        //glColor3f(1,0,0);
        //desenhalinhasdecolisao();


        glPopMatrix();

        ////////////////////HUD////////////////////

        if(ganhou==1){
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "Voce Ganhou", 55, 93, 0);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "Pontuacao: ", 47, 87, 0);
            escreve_Numero(GLUT_BITMAP_TIMES_ROMAN_24, calculodapontuacao, 74, 87, 0);
        }

        if(tecladao[112]==1){

            glColor3f(1, 1, 1);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "GAME PAUSED", 55, 93, 0);
        }

        if(tecladao[114]==1){

            glColor3f(1, 1, 1);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "RESTART ?", 62, 87, 0);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "[S]  [N]", 66, 81, 0);
        }

        if(tecladao[27]==1){
            glColor3f(1, 1, 1);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "   EXIT ? ", 62, 87, 0);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "[S]  [N]", 66, 81, 0);

        }


        glColor3f(0, 0, 0);

        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Objetivo: Pouse com segurnça em Marte", 42, 140, 0);

        glColor3f(0, 0, 0);        

        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Speed Axis Y: ", 3, 143, 0);
        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Speed Axis X: ", 3, 136, 0);
        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Altitude: ", 3, 129, 0);

        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Fuel: ", 123, 143, 0);
        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Aceleration: ", 122, 136, 0);

        escreve_Numero(GLUT_BITMAP_HELVETICA_12, nave.Vel.Y, 23, 143, 0);
        escreve_Numero(GLUT_BITMAP_HELVETICA_12, nave.Vel.X, 25, 136, 0);
        escreve_Numero(GLUT_BITMAP_HELVETICA_12, nave.Coordi.Y, 19, 129, 0);

        escreve_Numero(GLUT_BITMAP_HELVETICA_12, gasolina, 131, 143, 0);
        escreve_Numero(GLUT_BITMAP_HELVETICA_12, impulse*tempof, 140, 136, 0);

        ////////////////////Heart Texture////////////////////
        glColor4f(1,1,1,1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura_vida);
        for(k=0;k<vida_nave;k++){

            glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0);
            glVertex3f(67.5+(k*5), 145,  0);
            glTexCoord2f(1, 0);
            glVertex3f(72.5+(k*5), 145,  0);
            glTexCoord2f(1, 1);
            glVertex3f(72.5+(k*5), 150,  0);
            glTexCoord2f(0, 1);
            glVertex3f(67.5+(k*5),150,  0);
            glEnd();

        }
        glDisable(GL_TEXTURE_2D);
        ////////////////////Heart Texture////////////////////



        ////////////////////HUD////////////////////

        glutSwapBuffers();

        if(ganhou==1){
            delay(10);
            tela_Atual=1;
        }
    }



    ////////////////////Scene 2////////////////////
    if(cena==2)
    {
         ////////////////////Camera Movement////////////////////
        glPushMatrix();

        if((nave.Coordi.X-70>0  || nave.Coordi.Y-70>0) && (-nave.Coordi.X+560>0 && -nave.Coordi.Y+400>0))
        {
            if(nave.Coordi.X-70>0 && nave.Coordi.Y-70<0 )
            {
                glTranslatef(-nave.Coordi.X+70,0,0);
            }
            else if(nave.Coordi.X-70<=0  && nave.Coordi.Y-70>=0)
            {
                glTranslatef(0,-nave.Coordi.Y+70,0);
            }
            if(nave.Coordi.X-70>0   && nave.Coordi.Y-70>0)
            {
                glTranslatef(-nave.Coordi.X+70,-nave.Coordi.Y+70,0);
            }



        }
        else if(-nave.Coordi.X+560<=0 || -nave.Coordi.Y+400<=0)
        {
            if(-nave.Coordi.X+560>0 && -nave.Coordi.Y+400<=0 )
            {
                if(nave.Coordi.X>70)
                {
                    glTranslatef(-nave.Coordi.X+70,-330,0);
                }
                else
                    glTranslatef(0,-330,0);

            }
            else if(-nave.Coordi.X+560<=0  && -nave.Coordi.Y+400>=0)
            {
                if(nave.Coordi.Y-70>0)
                {
                    glTranslatef(-490,-nave.Coordi.Y+70,0);
                }
                else
                {
                    glTranslatef(-490,0,0);
                }
            }
            if(-nave.Coordi.X+560<=0 && -nave.Coordi.Y+400<=0)
            {
                glTranslatef(-490,-330,0);
            }


        }
        ////////////////////Camera Movement////////////////////


        ////////////////////Background Texture////////////////////
        glColor4f(1,1,1,1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textura_fundo );

        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0,  0);
        glTexCoord2f(1, 0);
        glVertex3f(640, 0,  0);
        glTexCoord2f(1, 1);
        glVertex3f(640, 480,  0);
        glTexCoord2f(0, 1);
        glVertex3f(0,480,  0);
        glEnd();

        glDisable(GL_TEXTURE_2D);
        ////////////////////Background Texture////////////////////



        ////////////////////SpaceShip Texture////////////////////
        if(nave.explosao==0)
        {
            glColor4f(1,1,1,1);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textura_nave);

            glPushMatrix();
            glTranslatef(nave.Coordi.X+5,nave.Coordi.Y+5,0);
            glRotatef(angulo-90,0,0,1);
            glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0);
            glVertex3f(-nave.tamanhoNave.width/2, -nave.tamanhoNave.heigth/2,  0);
            glTexCoord2f(1, 0);
            glVertex3f((nave.tamanhoNave.width)/2, -nave.tamanhoNave.heigth/2,  0);
            glTexCoord2f(1, 1);
            glVertex3f((nave.tamanhoNave.width)/2, (nave.tamanhoNave.heigth)/2,  0);
            glTexCoord2f(0, 1);
            glVertex3f(-nave.tamanhoNave.width/2,(nave.tamanhoNave.heigth)/2,  0);
            glEnd();
            glPopMatrix();

            glDisable(GL_TEXTURE_2D);
        }



        if(nave.explosao==1)
        {
            glColor4f(1,1,1,1);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textura_explosao[nexplosao]);

            glPushMatrix();
            glTranslatef(nave.Coordi.X+5,nave.Coordi.Y+5,0);
            glRotatef(angulo-90,0,0,1);
            glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0);
            glVertex3f(-nave.tamanhoNave.width/2, -nave.tamanhoNave.heigth/2,  0);
            glTexCoord2f(1, 0);
            glVertex3f((nave.tamanhoNave.width)/2, -nave.tamanhoNave.heigth/2,  0);
            glTexCoord2f(1, 1);
            glVertex3f((nave.tamanhoNave.width)/2, (nave.tamanhoNave.heigth)/2,  0);
            glTexCoord2f(0, 1);
            glVertex3f(-nave.tamanhoNave.width/2,(nave.tamanhoNave.heigth)/2,  0);
            glEnd();
            glPopMatrix();

            glDisable(GL_TEXTURE_2D);
            if(nexplosao<7)
            {
                nexplosao++;
            }
        }
        ////////////////////SpaceShip Texture////////////////////



        ////////////////////Meteor Texture////////////////////
        glColor4f(1,0,0,1);
        int k;
        int x;
        glColor4f(1,1,1,1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura_meteoro);
        for(k=0; k<n_meteoros; k++)
        {
            if(meteoro[k].explodiu==0)
            {

                glPushMatrix();
                glTranslatef(meteoro[k].pos.X,meteoro[k].pos.Y,0);
                glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(0, 0);
                glVertex3f(-4, -4,  0);
                glTexCoord2f(1, 0);
                glVertex3f(4, -4,  0);
                glTexCoord2f(1, 1);
                glVertex3f(4, 4,  0);
                glTexCoord2f(0, 1);
                glVertex3f(-4,4,  0);
                glEnd();
                glPopMatrix();

            }


        }
        glDisable(GL_TEXTURE_2D);
        ////////////////////Meteor Texture////////////////////





        glPopMatrix();

        ////////////////////HUD////////////////////

        if(tecladao[112]==1){

            glColor3f(1, 1, 1);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "GAME PAUSED", 55, 93, 0);
        }

        if(tecladao[114]==1){

            glColor3f(1, 1, 1);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "RESTART ?", 62, 87, 0);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "[S]  [N]", 66, 81, 0);
        }

        if(tecladao[27]==1){
            glColor3f(1, 1, 1);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "   EXIT ? ", 62, 87, 0);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "[S]  [N]", 66, 81, 0);

        }


        glColor3f(1, 0, 0);

        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Objetivo: Em relacao a Terra, siga para Marte", 42, 140, 0);
        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "na direcao nordeste", 57, 137, 0);

        glColor3f(1, 1, 1);        

        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Speed Axis Y: ", 3, 143, 0);
        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Speed Axis X: ", 3, 136, 0);
        //escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Altitude: ", 3, 129, 0);

        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Fuel: ", 123, 143, 0);
        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Aceleration: ", 122, 136, 0);

        escreve_Numero(GLUT_BITMAP_HELVETICA_12, nave.Vel.Y, 23, 143, 0);
        escreve_Numero(GLUT_BITMAP_HELVETICA_12, nave.Vel.X, 25, 136, 0);
        //escreve_Numero(GLUT_BITMAP_HELVETICA_12, nave.Coordi.Y, 19, 129, 0);

        escreve_Numero(GLUT_BITMAP_HELVETICA_12, gasolina, 131, 143, 0);
        escreve_Numero(GLUT_BITMAP_HELVETICA_12, impulse*tempof, 140, 136, 0);



        ////////////////////Heart Texture////////////////////
        glColor4f(1,1,1,1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura_vida);
        for(k=0;k<vida_nave;k++){

            glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0);
            glVertex3f(67.5+(k*5), 145,  0);
            glTexCoord2f(1, 0);
            glVertex3f(72.5+(k*5), 145,  0);
            glTexCoord2f(1, 1);
            glVertex3f(72.5+(k*5), 150,  0);
            glTexCoord2f(0, 1);
            glVertex3f(67.5+(k*5),150,  0);
            glEnd();

        }
        glDisable(GL_TEXTURE_2D);
        ////////////////////Heart Texture////////////////////



        ////////////////////HUD////////////////////
        glutSwapBuffers();
    }



    ////////////////////Scene 1////////////////////
    if(cena==1)
    {
        int k;




        ////////////////////Background Animated Texture////////////////////

        /////////Frame 1
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        glPushMatrix();

        glColor4f(1,1,1,1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textura_animado[0] );
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);
        glVertex3f(animacao[0].X, animacao[0].Y,  0);
        glTexCoord2f(1, 0);
        glVertex3f(animacao[0].X +150, animacao[0].Y,  0);
        glTexCoord2f(1, 1);
        glVertex3f(animacao[0].X +150, animacao[0].Y+150,  0);
        glTexCoord2f(0, 1);
        glVertex3f(animacao[0].X,animacao[0].Y+150,  0);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        /////////Frame 2
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textura_animado[1] );

        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);
        glVertex3f(animacao[0].X+150, animacao[0].Y,  0);
        glTexCoord2f(1, 0);
        glVertex3f(animacao[0].X +300, animacao[0].Y,  0);
        glTexCoord2f(1, 1);
        glVertex3f(animacao[0].X +300, animacao[0].Y+150,  0);
        glTexCoord2f(0, 1);
        glVertex3f(animacao[0].X+150,animacao[0].Y+150,  0);
        glEnd();

        glDisable(GL_TEXTURE_2D);

        /////////Frame 3
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textura_animado[2] );

        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);
        glVertex3f(animacao[0].X+300, animacao[0].Y,  0);
        glTexCoord2f(1, 0);
        glVertex3f(animacao[0].X +450, animacao[0].Y,  0);
        glTexCoord2f(1, 1);
        glVertex3f(animacao[0].X +450, animacao[0].Y+150,  0);
        glTexCoord2f(0, 1);
        glVertex3f(animacao[0].X+300,animacao[0].Y+150,  0);
        glEnd();

        glDisable(GL_TEXTURE_2D);

        /////////Freme 4
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textura_animado[3] );

        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);
        glVertex3f(animacao[0].X+450, animacao[0].Y,  0);
        glTexCoord2f(1, 0);
        glVertex3f(animacao[0].X +600, animacao[0].Y,  0);
        glTexCoord2f(1, 1);
        glVertex3f(animacao[0].X +600, animacao[0].Y+150,  0);
        glTexCoord2f(0, 1);
        glVertex3f(animacao[0].X+450,animacao[0].Y+150,  0);
        glEnd();

        glDisable(GL_TEXTURE_2D);



        if(animacao[0].X>-450)
        {
            animacao[0].X-=150;
        }
        else
        {
            animacao[0].X=0;
        }
        ////////////////////Background Animated Texture////////////////////



        ////////////////////Clouds Animated Texture////////////////////
        glEnable(GL_TEXTURE_2D);
        glColor4f(1,1,1,1);
        glBindTexture(GL_TEXTURE_2D,textura_nuvem );
        for(k=0; k<10; k++)
        {

            glPushMatrix();
            glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0);
            glVertex3f(nuvem[k].X,nuvem[k].Y,  0);
            glTexCoord2f(1, 0);
            glVertex3f(nuvem[k].X+10, nuvem[k].Y,  0);
            glTexCoord2f(1, 1);
            glVertex3f(nuvem[k].X+10, nuvem[k].Y+10,  0);
            glTexCoord2f(0, 1);
            glVertex3f(nuvem[k].X,nuvem[k].Y+10,  0);
            glEnd();
            glPopMatrix();

            if(nuvem[k].X<=-10)
            {
                nuvem[k].X=149;
            }
            else
            {
                int divs;
                divs=rand()%10;
                nuvem[k].X-=0.05+divs/100;
            }
        }
        glDisable(GL_TEXTURE_2D);
        ////////////////////Clouds Animated Texture////////////////////



        ////////////////////Spaceship Texture////////////////////
        if(nave.explosao==0)
        {
            glColor4f(1,1,1,1);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textura_nave);

            glPushMatrix();
            glTranslatef(nave.Coordi.X+5,nave.Coordi.Y+5,0);
            glRotatef(angulo-90,0,0,1);
            glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0);
            glVertex3f(-nave.tamanhoNave.width/2, -nave.tamanhoNave.heigth/2,  0);
            glTexCoord2f(1, 0);
            glVertex3f((nave.tamanhoNave.width)/2, -nave.tamanhoNave.heigth/2,  0);
            glTexCoord2f(1, 1);
            glVertex3f((nave.tamanhoNave.width)/2, (nave.tamanhoNave.heigth)/2,  0);
            glTexCoord2f(0, 1);
            glVertex3f(-nave.tamanhoNave.width/2,(nave.tamanhoNave.heigth)/2,  0);
            glEnd();
            glPopMatrix();

            glDisable(GL_TEXTURE_2D);
        }



        if(nave.explosao==1)
        {
            glColor4f(1,1,1,1);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textura_explosao[nexplosao]);

            glPushMatrix();
            glTranslatef(nave.Coordi.X+5,nave.Coordi.Y+5,0);
            glRotatef(angulo-90,0,0,1);
            glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0);
            glVertex3f(-nave.tamanhoNave.width/2, -nave.tamanhoNave.heigth/2,  0);
            glTexCoord2f(1, 0);
            glVertex3f((nave.tamanhoNave.width)/2, -nave.tamanhoNave.heigth/2,  0);
            glTexCoord2f(1, 1);
            glVertex3f((nave.tamanhoNave.width)/2, (nave.tamanhoNave.heigth)/2,  0);
            glTexCoord2f(0, 1);
            glVertex3f(-nave.tamanhoNave.width/2,(nave.tamanhoNave.heigth)/2,  0);
            glEnd();
            glPopMatrix();

            glDisable(GL_TEXTURE_2D);
            if(nexplosao<7)
            {
                nexplosao++;
            }
        }
        ////////////////////Spaceship Texture////////////////////

        glPopMatrix();

        ////////////////////HUD////////////////////

        if(tecladao[112]==1){

            glColor3f(1, 1, 1);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "GAME PAUSED", 55, 93, 0);
        }

        if(tecladao[114]==1){

            glColor3f(1, 1, 1);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "RESTART ?", 62, 87, 0);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "[S]  [N]", 66, 81, 0);
        }

        if(tecladao[27]==1){
            glColor3f(1, 1, 1);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "   EXIT ? ", 62, 87, 0);
            escreve_Texto(GLUT_BITMAP_TIMES_ROMAN_24, "[S]  [N]", 66, 81, 0);

        }

        glColor3f(1, 0, 0);

        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Objetivo: Saia da orbita da Terra", 53, 140, 0);

        glColor3f(0, 0, 0);        

        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Speed Axis Y: ", 3, 143, 0);
        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Speed Axis X: ", 3, 136, 0);
        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Altitude: ", 3, 129, 0);

        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Fuel: ", 123, 143, 0);
        escreve_Texto(GLUT_BITMAP_HELVETICA_12, "Aceleration: ", 122, 136, 0);

        escreve_Numero(GLUT_BITMAP_HELVETICA_12, nave.Vel.Y, 23, 143, 0);
        escreve_Numero(GLUT_BITMAP_HELVETICA_12, nave.Vel.X, 25, 136, 0);
        escreve_Numero(GLUT_BITMAP_HELVETICA_12, nave.Coordi.Y, 19, 129, 0);

        escreve_Numero(GLUT_BITMAP_HELVETICA_12, gasolina, 131, 143, 0);
        escreve_Numero(GLUT_BITMAP_HELVETICA_12, impulse*tempof, 140, 136, 0);


        ////////////////////Heart Texture////////////////////
        glColor4f(1,1,1,1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura_vida);
        for(k=0;k<vida_nave;k++){

            glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0);
            glVertex3f(67.5+(k*5), 145,  0);
            glTexCoord2f(1, 0);
            glVertex3f(72.5+(k*5), 145,  0);
            glTexCoord2f(1, 1);
            glVertex3f(72.5+(k*5), 150,  0);
            glTexCoord2f(0, 1);
            glVertex3f(67.5+(k*5),150,  0);
            glEnd();

        }
        glDisable(GL_TEXTURE_2D);
        ////////////////////Heart Texture////////////////////

        ////////////////////HUD////////////////////


        glutSwapBuffers();
    }
}