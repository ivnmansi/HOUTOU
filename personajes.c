#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "personajes.h"
#include "config.h"

 

/*---------------- FUNCIONES GENERALES-----------------------------------*/

/*VERIFICADOR TECLADO------*/
void verificadorteclado(ALLEGRO_EVENT *event, personaje *principal){
   if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
            key[event->keyboard.keycode] = true;
        } else if (event->type == ALLEGRO_EVENT_KEY_UP) {
            key[event->keyboard.keycode] = false;
            principal->imagen=principal->estatico;
        }
}

/*MOVIMIENTO HITBOXS*/
void movimiento_hitbox(personaje *personaje){
  personaje->hitbox.x=personaje->x+personaje->hitbox.arreglo_x;
  personaje->hitbox.y=personaje->y+personaje->hitbox.arreglo_y;
}

/*MOVIMIENTO HITBOXS PROYECTILES*/
void movimiento_hitbox_proyectiles(personaje *personaje){
  int i;
  for(i=0;i<maxproyectiles;i++){
  if(personaje->proyectiles[i].activo==true){
  personaje->proyectiles[i].hitbox.x=personaje->proyectiles[i].x+personaje->proyectiles[i].hitbox.arreglo_x;
  personaje->proyectiles[i].hitbox.y=personaje->proyectiles[i].y+personaje->proyectiles[i].hitbox.arreglo_y;
  } else {
    personaje->proyectiles[i].hitbox.x=-100;
    personaje->proyectiles[i].hitbox.y=-100;
    }
  }
}

/*COLISION PERSONAJE-PROYECTIL------*/
   bool colisionproyectiles(personaje *personaje1 ,personaje *enemigo){
    int i;
    

    for(i=0;i<maxproyectiles;i++){
     if(  (personaje1->hitbox.x < enemigo->proyectiles[i].hitbox.x+enemigo->proyectiles[i].hitbox.ancho)&&(personaje1->hitbox.x+personaje1->hitbox.ancho > enemigo->proyectiles[i].hitbox.x)&&  (personaje1->hitbox.y < enemigo->proyectiles[i].hitbox.y+enemigo->proyectiles[i].hitbox.alto)&&(personaje1->hitbox.y+personaje1->hitbox.alto > enemigo->proyectiles[i].hitbox.y)  ){
        enemigo->proyectiles[i].activo=false;
        return true;
     }
     
    }
    return false;
   }

/*COLISION CON ATAQUE ESPECIAL*/
   bool colisionataqueespecial(personaje *personaje1, personaje *enemigo){
      int i;
    for(i=0;i<maxproyectiles;i++){
     if(  (personaje1->hitbox.x < enemigo->especial[i].hitbox.x+enemigo->especial[i].hitbox.ancho)&&(personaje1->hitbox.x+personaje1->hitbox.ancho > enemigo->especial[i].hitbox.x)&&  (personaje1->hitbox.y < enemigo->especial[i].hitbox.y+enemigo->especial[i].hitbox.alto)&&(personaje1->hitbox.y+personaje1->hitbox.alto > enemigo->especial[i].hitbox.y)  ){
        enemigo->proyectiles[i].activo=false;
        return true;
     }
    }
    return false;
   }

/*COLISION PERSONAJE-PERSONAJE*/
   bool colisionpersonajes(personaje *personaje1 ,personaje *enemigo){
    int i;
    if(enemigo->activo==true){
     if(  (personaje1->hitbox.x < enemigo->hitbox.x+enemigo->hitbox.ancho)&&(personaje1->hitbox.x+personaje1->hitbox.ancho > enemigo->hitbox.x)&&  (personaje1->hitbox.y < enemigo->hitbox.y+enemigo->hitbox.alto)&&(personaje1->hitbox.y+personaje1->hitbox.alto > enemigo->hitbox.y)  ){
        return true;
     }
    }
    return false;
   }



/*------------------FUNCIONES PERSONAJE PRINCIPAL------------------------------------------------*/

/*INICIALIZACION DE IMAGENES*/
void iniciarimagenesjugador(personaje *principal){
  int i=0;
   principal->imagen=al_load_bitmap("imagenes/sprites/principal1.png"); /*imagen del personaje que se muestra en pantalla*/
   principal->estatico=al_load_bitmap("imagenes/sprites/principal1.png");
   principal->izquierda=al_load_bitmap("imagenes/sprites/principal3.png");
   principal->derecha=al_load_bitmap("imagenes/sprites/principal2.png");

   principal->imagen_proyectil = al_load_bitmap("imagenes/obstaculos/proyectilprincipal.png");
   for(i=0;i<maxproyectiles;i++){
    principal->especial[i].imagen = al_load_bitmap("imagenes/obstaculos/rayo.png");
   }
}

/*INICIALIZACION*/
void iniciarjugador(personaje *principal){
  int i=0;
   principal->x=((x_display/2)-30); /*posicion inicial x*/
   principal->y=y_display-120; /*posicion inicial y*/
   principal->velocidad=5; /*velocidad de movimiento*/
   principal->vida=6; /*vida del personaje*/
   // > PROYECTIL
   principal->velocidad_proyectiles = 15; /*velocidad de movimiento proyectiles*/
   principal->espaciado_proyectiles = 8; /*veces por segundo que se puede tirar un proyectil*/
     // >> iniciacion proyectiles principal;
     for(i=0;i<maxproyectiles;i++){
       principal->proyectiles[i].activo=false;
       // hitbox proyectiles
       principal->proyectiles[i].hitbox.x=principal->proyectiles[i].x+2;
       principal->proyectiles[i].hitbox.y=principal->proyectiles[i].y+2;
       principal->proyectiles[i].hitbox.ancho=11;
       principal->proyectiles[i].hitbox.alto=11;
       principal->proyectiles[i].hitbox.arreglo_x=3;
       principal->proyectiles[i].hitbox.arreglo_y=3;
      }
    // > ATAQUE ESPECIAL
    for(i=0;i<maxproyectiles;i++){
    principal->especial[i].activo=false;
      //hitbox
       principal->especial[i].hitbox.x=principal->especial[i].x+2;
       principal->especial[i].hitbox.y=principal->especial[i].y+2;
       principal->especial[i].hitbox.ancho=16;
       principal->especial[i].hitbox.alto=14;
       principal->especial[i].hitbox.arreglo_x=0;
       principal->especial[i].hitbox.arreglo_y=0;
    }

    // > HITBOX
    principal->hitbox.x=principal->x+23;
    principal->hitbox.y=principal->y+25;
    principal->hitbox.ancho=20;
    principal->hitbox.alto=20;
    principal->hitbox.arreglo_x=23;
    principal->hitbox.arreglo_y=25;
}

/*MOVIMIENTO DEL JUGADOR---*/
void movimiento_principal(float *velocidad_principal_real, personaje *principal){

     if(key[ALLEGRO_KEY_LSHIFT]){ /*para que vaya mas lento al presionar X*/
                *velocidad_principal_real=0.5;
            } else {
                *velocidad_principal_real=1;
            }

            if(  (((key[ALLEGRO_KEY_W]||key[ALLEGRO_KEY_UP])&&(key[ALLEGRO_KEY_A]||key[ALLEGRO_KEY_LEFT])) || ((key[ALLEGRO_KEY_W]||key[ALLEGRO_KEY_UP])&&(key[ALLEGRO_KEY_D]||key[ALLEGRO_KEY_RIGHT])) || ((key[ALLEGRO_KEY_S]||key[ALLEGRO_KEY_DOWN])&&(key[ALLEGRO_KEY_A]||key[ALLEGRO_KEY_LEFT])) || ((key[ALLEGRO_KEY_S]||key[ALLEGRO_KEY_DOWN])&&(key[ALLEGRO_KEY_D]||key[ALLEGRO_KEY_RIGHT])))  ){
                *velocidad_principal_real=(*velocidad_principal_real*principal->velocidad)/sqrt(2);
            } else {
                *velocidad_principal_real=(*velocidad_principal_real)*principal->velocidad;
            } /*arreglo de la velocidad en diagonal*/

                if (key[ALLEGRO_KEY_W] || key[ALLEGRO_KEY_UP]) { /*hacia arriba*/
                    principal->y -= *velocidad_principal_real;
                    if(principal->y<0){ /*colision con arriba*/
                        principal->y=0;
                    }
                    movimiento_hitbox(principal);
                }
                if (key[ALLEGRO_KEY_S] || key[ALLEGRO_KEY_DOWN]) {
                    principal->y += *velocidad_principal_real;
                    if(principal->y>y_display-60){ /*colision con abajo*/
                        principal->y=y_display-60;
                    }
                    movimiento_hitbox(principal);
                }
                if (key[ALLEGRO_KEY_A] || key[ALLEGRO_KEY_LEFT]) {
                    principal->x -= *velocidad_principal_real;
                    principal->imagen = principal->izquierda;
                    if(principal->x<0){ /*colision con izquierda*/
                        principal->x=0;
                    }
                    movimiento_hitbox(principal);
                }
                if (key[ALLEGRO_KEY_D] || key[ALLEGRO_KEY_RIGHT]) {
                    principal->x += *velocidad_principal_real;
                    principal->imagen = principal->derecha;
                    if(principal->x>x_display-60){ /*colision con derecha*/
                        principal->x=x_display-60;
                    }
                    movimiento_hitbox(principal);
                }
       }

/*ATAQUE DEL JUGADOR----*/
    void disparar_principal(ALLEGRO_EVENT *event, ALLEGRO_TIMER **timer_proyectil_principal, bool *espacio_disparos, personaje *principal, ALLEGRO_TIMER *fps, bool *ataquetripleactivo){
     int i,j=0;
     if(event->timer.source == *timer_proyectil_principal){
            *espacio_disparos=true;
           } /*para que los proyectiles del personaje principal se disparen espaciados*/

                if((key[ALLEGRO_KEY_Z]==true || key[ALLEGRO_KEY_SPACE]==true) && (*espacio_disparos==true) && (event->timer.source == fps)){
                   for(i=0,j=0;i<maxproyectiles;i++){
                    if(principal->proyectiles[i].activo==false){
                        principal->proyectiles[i].x=principal->x+20;
                        principal->proyectiles[i].y=principal->y;
                        principal->proyectiles[i].aceleracion_angular=(M_PI/2)*j;
                        principal->proyectiles[i].activo=true;
                        j++;

                        if(*ataquetripleactivo==false){ // si este ataque especial no está activo
                        *espacio_disparos = false;
                        break;
                        } else
                        if(*ataquetripleactivo==true&&j==3){ // si está activo el ataque triple
                          *espacio_disparos = false;
                           break;
                        }
                    }
                   }
                 } 
                 for(i=0;i<maxproyectiles;i++){
                    if(principal->proyectiles[i].activo==true){
                        principal->proyectiles[i].y -= principal->velocidad_proyectiles+sin(principal->proyectiles[i].aceleracion_angular);
                        if(*ataquetripleactivo==true){
                        principal->proyectiles[i].x += cos(principal->proyectiles[i].aceleracion_angular);
                        }
                        
                        if(principal->proyectiles[i].y<-16){
                            principal->proyectiles[i].activo=false;
                        }
                    } else {
                        principal->proyectiles[i].y=principal->y;
                        principal->proyectiles[i].x=principal->x+20;
                    }
                 }
                 movimiento_hitbox_proyectiles(principal);
   }

/*ATAQUE ESPECIAL PERSONAJE PRINCIPAL (RAYO)----*/
void ataque_especial(ALLEGRO_EVENT *event, ALLEGRO_TIMER *timer_segundos, int *contadorespecial, int *contadorduracionespecial, bool *especialactivo, char *elcontadordelataque, personaje *principal, int *auxespecial_x){
   int i;
     //contadores
         if(event->timer.source == timer_segundos){
           
           if((*contadorespecial)!=-1){// no se puede tirar
            (*contadorespecial)++;
            if((*contadorespecial)==20){// ya se puede tirar a los 20 segundos (si contadorespecial=-1)
              (*contadorespecial)=-1;
              (*contadorduracionespecial)=0;
            }
           }
           if(*contadorduracionespecial>0){ //se está tirando el ataque especial
             (*contadorduracionespecial)++;
             if(*contadorduracionespecial==2){ //se termina el tiempo
               *contadorespecial=0; //se inicia el tiempo de espera
               *especialactivo=false;
             }
           }
          }
      
        //tirar
          if(key[ALLEGRO_KEY_X]==true&&(*contadorespecial)==-1){
            if((*especialactivo)==false){
               *contadorduracionespecial=1;
               for(i=0;i<maxproyectiles;i++){
                principal->especial[i].activo=false;
                }
                *auxespecial_x=principal->x+20;
               *especialactivo=true;
               
              }
          } else

          if((*especialactivo)==true){

            for(i=0;i<maxproyectiles;i++){
                  if(principal->especial[i].activo==false){
                        principal->especial[i].x=*auxespecial_x;
                        principal->especial[i].y=principal->y;
                        principal->especial[i].activo=true;
                        break;
                    }
               }
            }

            for(i=0;i<maxproyectiles;i++){
                    if(principal->especial[i].activo==true){
                        principal->especial[i].y -= 10;
                        
                        if(principal->especial[i].y<0){
                            principal->especial[i].activo=false;
                        }
                    } else {
                        principal->especial[i].y=principal->y;
                        principal->especial[i].x=principal->x+20;
                    }
                 }

            // movimiento hitboxs
            for(i=0;i<maxproyectiles;i++){
            if(principal->especial[i].activo==true){
            principal->especial[i].hitbox.x=principal->especial[i].x+principal->especial[i].hitbox.arreglo_x;
            principal->especial[i].hitbox.y=principal->especial[i].y+principal->especial[i].hitbox.arreglo_y;
            } else {
            principal->especial[i].hitbox.x=-100;
            principal->especial[i].hitbox.y=-100;
            }
           }
    }

/*INMUNIDAD PERSONAJE PRINCIPAL-----*/
//>por proyectil
void inmunidadporproyectil(int numenemigos, personaje *principal, personaje enemigo[numenemigos], bool *inmunidad){
    int i=0,j=0,k=0;
    for(i=0;i<numenemigos;i++){
         if(colisionproyectiles(principal, &enemigo[i])){
            principal->vida--;

            for(k=0;k<numenemigos;k++){
              for(j=0;j<maxproyectiles;j++){
                enemigo[k].proyectiles[j].activo=false;
              }
            }
            *inmunidad=true;
         }
        }
      }

//>por colision con personaje
void inmunidadporenemigo(int numenemigos,personaje *principal,personaje enemigo[numenemigos], bool *inmunidad){
    int i;
    for(i=0;i<numenemigos;i++){
        if(colisionpersonajes(principal,&enemigo[i])){
          (principal->vida)--;

            principal->x=((x_display/2)-30);
            principal->y=y_display-120;
            movimiento_hitbox(principal);

            *inmunidad=true;
        }
       }
   }

 //> tiempo de inmunidad
   void inmunidadactiva(ALLEGRO_EVENT *event, ALLEGRO_TIMER *timer_segundos, int *contadorinmunidad, bool *inmunidad,bool *powerup_inmunidad_tomado){
    int tiempo;
      if(*powerup_inmunidad_tomado==true){
        tiempo=5;
      } else {
        tiempo=3;
      }
       
      if(event->timer.source == timer_segundos){
          (*contadorinmunidad)++;
          if(*contadorinmunidad==tiempo){
            *inmunidad=false;
            *contadorinmunidad=0;
            if(*powerup_inmunidad_tomado==true){
            *powerup_inmunidad_tomado=false;
            }
            }
           }
     }


/*---------------FUNCIONES ENEMIGOS------------------*/

/*DETERMINACIÓN DE NUM DE ENEMIGOS---*/
void leernumeroenemigos(int numenemigospornivel[10], int *numenemigostotal){
  int i=0,j=0;
  int totalenemigos=0,totalniveles=0;
  int filascolumnas[10][10] = {0};

     FILE *file=fopen("enemigos.txt", "r");
    if(file!=NULL) {
        // Lee datos del archivo
        for(i=0;i<10;i++){
            for(j=0;j<10;j++) {
                fscanf(file, "%d", &filascolumnas[i][j]);
            }
          }
        // definicion del total de enemigos
        for(i=0;i<10;i++) {
            for(j=0;j<10;j++) {
                if (filascolumnas[i][j]!=0) {
                    totalenemigos++;
                }
               }
              }

        // Total de niveles
        for(i=0;i<10;i++) {
            if(filascolumnas[i][0] != 0) {
                totalniveles++;
            }
           }

        // Enemigos por cada nivel
        for (i=0; i<10;i++) {
            for (j=0;j<10;j++) {
                if(filascolumnas[i][j]!=0) {
                    numenemigospornivel[i]++;
                }
              }
          }

        (*numenemigostotal)=totalenemigos;
        
    fclose(file);
    } else {
        printf("Error al abrir el archivo\n");
    }
}

/*LECTURA DE ENEMIGOS----------*/
void leerenemigos(int numenemigos,int numenemigospornivel[10],personaje enemigos[numenemigos]){
  int i=0,j=0,k=0,l=0;
  int aux[100];
    FILE *file=fopen("enemigos.txt", "r");
    if(file!=NULL) {

        // Leer todos los valores en aux
        for (i=0;i<100;i++){
           fscanf(file,"%d",&aux[i]);
        }
        for (i=0;i< 10;i++) {
            for (j=0;j<numenemigospornivel[i];j++) {
                while(aux[k]==0) {
                    k++;
                }
                    enemigos[l].tipoenemigo = aux[k];
                    l++;
                    k++;
               }
              }
        
    fclose(file);
    } else {
        printf("Error al abrir el archivo\n");
    }
}

/*INICIALIZACION ENEMIGOS-------------*/
void iniciarenemigos(int numenemigos, personaje enemigos[numenemigos]){
int i=0,j=0;

   for(i=0;i<numenemigos;i++){
     enemigos[i].x=-70;
     enemigos[i].y=-70;

      //--------PAYASOS---------------------------
      if(enemigos[i].tipoenemigo==1){
    enemigos[i].velocidad=2;
    enemigos[i].velocidad_angular=i;
    enemigos[i].choqueborde=1; /*empieza yendo a la derecha*/
    enemigos[i].imagen=al_load_bitmap("imagenes/sprites/enemigos3.png");
    enemigos[i].vida=10; /*vida enemigo*/
    enemigos[i].activo=true;
    //hitbox payasos
    enemigos[i].hitbox.x=10;
    enemigos[i].hitbox.y=4;
    enemigos[i].hitbox.ancho=44;
    enemigos[i].hitbox.alto=39;
    enemigos[i].hitbox.arreglo_x=10;
    enemigos[i].hitbox.arreglo_y=3;

    // > proyectil
    enemigos[i].velocidad_proyectiles=4;
    enemigos[i].espaciado_proyectiles=1;
        // >> inicialización proyectiles
        for(j=0;j<maxproyectiles;j++){

            if(j%2==0){
            enemigos[i].proyectiles[j].imagen=al_load_bitmap("imagenes/obstaculos/proyectil_enemigo.png");
            } else {
                enemigos[i].proyectiles[j].imagen=al_load_bitmap("imagenes/obstaculos/proyectil2.png");
            }
            enemigos[i].proyectiles[j].destruido=al_load_bitmap("imagenes/obstaculos/proyectil2muerto.png");
            
          
            enemigos[i].proyectiles[j].aceleracion_angular=0;
            enemigos[i].proyectiles[j].aceleracion=-(i+1);
            enemigos[i].proyectiles[j].activo=false;
            // hitbox proyectiles
            enemigos[i].proyectiles[j].hitbox.x=enemigos[i].proyectiles[i].x+1;
            enemigos[i].proyectiles[j].hitbox.y=enemigos[i].proyectiles[i].y+1;
            enemigos[i].proyectiles[j].hitbox.ancho=5;
            enemigos[i].proyectiles[j].hitbox.alto=11;
            enemigos[i].proyectiles[j].hitbox.arreglo_x=2;
            enemigos[i].proyectiles[j].hitbox.arreglo_y=2;
        }
      } else
      

      //-----------------BUFONES--------------------
      if(enemigos[i].tipoenemigo==2){
    enemigos[i].velocidad=3;
    enemigos[i].velocidad_angular=i;
    enemigos[i].imagen=al_load_bitmap("imagenes/sprites/enemigos1.png");
    enemigos[i].vida=30; /*vida enemigo*/
    enemigos[i].activo=true;
    //hitbox bufones
    enemigos[i].hitbox.x=12;
    enemigos[i].hitbox.y=6;
    enemigos[i].hitbox.ancho=33;
    enemigos[i].hitbox.alto=54;
    enemigos[i].hitbox.arreglo_x=12;
    enemigos[i].hitbox.arreglo_y=6;

    // > proyectil
    enemigos[i].velocidad_proyectiles=2;
    enemigos[i].espaciado_proyectiles=0.5;
        // >> inicialización proyectiles
        for(j=0;j<maxproyectiles;j++){
            
            enemigos[i].proyectiles[j].imagen=al_load_bitmap("imagenes/obstaculos/proyectilbufon.png");
            enemigos[i].proyectiles[j].destruido=al_load_bitmap("imagenes/obstaculos/proyectilbufondestruido.png");
            
          
            enemigos[i].proyectiles[j].aceleracion_angular=0;
            enemigos[i].proyectiles[j].aceleracion=2;
            enemigos[i].proyectiles[j].activo=false;
            // hitbox proyectiles
            enemigos[i].proyectiles[j].hitbox.x=enemigos[i].proyectiles[i].x+3;
            enemigos[i].proyectiles[j].hitbox.y=enemigos[i].proyectiles[i].y+3;
            enemigos[i].proyectiles[j].hitbox.ancho=11;
            enemigos[i].proyectiles[j].hitbox.alto=11;
            enemigos[i].proyectiles[j].hitbox.arreglo_x=3;
            enemigos[i].proyectiles[j].hitbox.arreglo_y=3;
        }
      } else

      //--------------MIMOS---------------
      if(enemigos[i].tipoenemigo==3){
    enemigos[i].velocidad=5;
    enemigos[i].velocidad_angular=0;
    enemigos[i].imagen=al_load_bitmap("imagenes/sprites/enemigos2.png");
    enemigos[i].vida=30; /*vida enemigo*/
    enemigos[i].activo=true;
    //hitbox bufones
    enemigos[i].hitbox.x=15;
    enemigos[i].hitbox.y=0;
    enemigos[i].hitbox.ancho=29;
    enemigos[i].hitbox.alto=53;
    enemigos[i].hitbox.arreglo_x=15;
    enemigos[i].hitbox.arreglo_y=0;

    // > proyectil
    enemigos[i].velocidad_proyectiles=3;
    enemigos[i].espaciado_proyectiles=0.5;
        // >> inicialización proyectiles
        for(j=0;j<maxproyectiles;j++){
            
            enemigos[i].proyectiles[j].imagen=al_load_bitmap("imagenes/obstaculos/proyectilmimo.png");
            enemigos[i].proyectiles[j].destruido=al_load_bitmap("imagenes/obstaculos/proyectilmimodestruido.png");
            
          
            enemigos[i].proyectiles[j].aceleracion_angular=0;
            enemigos[i].proyectiles[j].aceleracion=0;
            enemigos[i].proyectiles[j].activo=false;
            // hitbox proyectiles
            enemigos[i].proyectiles[j].hitbox.x=enemigos[i].proyectiles[i].x+8;
            enemigos[i].proyectiles[j].hitbox.y=enemigos[i].proyectiles[i].y+6;
            enemigos[i].proyectiles[j].hitbox.ancho=16;
            enemigos[i].proyectiles[j].hitbox.alto=14;
            enemigos[i].proyectiles[j].hitbox.arreglo_x=8;
            enemigos[i].proyectiles[j].hitbox.arreglo_y=6;
        }

      } else
      //---------------------------------------

      //--------------BOSS FINAL---------------
      if(enemigos[i].tipoenemigo==5){
    enemigos[i].velocidad=7;
    enemigos[i].velocidad_angular=0;
    enemigos[i].imagen=al_load_bitmap("imagenes/sprites/boss.png");
    enemigos[i].vida=60; /*vida enemigo*/
    enemigos[i].activo=true;
    enemigos[i].contadorataque=0;
    //hitbox bufones
    enemigos[i].hitbox.x=27;
    enemigos[i].hitbox.y=5;
    enemigos[i].hitbox.ancho=23;
    enemigos[i].hitbox.alto=63;
    enemigos[i].hitbox.arreglo_x=27;
    enemigos[i].hitbox.arreglo_y=5;
    

    // > proyectil
    enemigos[i].velocidad_proyectiles=5;
    enemigos[i].espaciado_proyectiles=0.5;
        // >> inicialización proyectiles
        for(j=0;j<maxproyectiles;j++){
            
            enemigos[i].proyectiles[j].imagen=al_load_bitmap("imagenes/obstaculos/proyectilboss.png");
            enemigos[i].proyectiles[j].destruido=al_load_bitmap("imagenes/obstaculos/proyectilbossdestruido.png");
            
          
            enemigos[i].proyectiles[j].aceleracion_angular=0;
            enemigos[i].proyectiles[j].aceleracion=0;
            enemigos[i].proyectiles[j].activo=false;
            // hitbox proyectiles
            enemigos[i].proyectiles[j].hitbox.x=enemigos[i].proyectiles[i].x+9;
            enemigos[i].proyectiles[j].hitbox.y=enemigos[i].proyectiles[i].y+8;
            enemigos[i].proyectiles[j].hitbox.ancho=12;
            enemigos[i].proyectiles[j].hitbox.alto=14;
            enemigos[i].proyectiles[j].hitbox.arreglo_x=9;
            enemigos[i].proyectiles[j].hitbox.arreglo_y=8;
        }

      }
      //---------------------------------------

   }
}


/*---------------------DEPURACION-------------------*/
  //dibujar hitboxs
       void dibujohitboxs(int numenemigos, personaje principal, personaje enemigos1[numenemigos], proyectil powerup){
        int i=0,j=0;

        // hitbox personaje
            al_draw_rectangle(principal.hitbox.x, principal.hitbox.y, principal.hitbox.x + principal.hitbox.ancho, principal.hitbox.y + principal.hitbox.alto, al_map_rgb(255, 0, 0), 1);
            //hitbox disparos personaje
            for(i=0;i<maxproyectiles;i++){
            if(principal.proyectiles[i].activo==true){
            al_draw_rectangle(principal.proyectiles[i].hitbox.x, principal.proyectiles[i].hitbox.y, principal.proyectiles[i].hitbox.x + principal.proyectiles[i].hitbox.ancho, principal.proyectiles[i].hitbox.y + principal.proyectiles[i].hitbox.alto, al_map_rgb(255, 0, 0), 1);
             }
            }
            
            //hitbox enemigos
            for(i=0;i<numenemigos;i++){
                al_draw_rectangle(enemigos1[i].hitbox.x, enemigos1[i].hitbox.y, enemigos1[i].hitbox.x + enemigos1[i].hitbox.ancho, enemigos1[i].hitbox.y + enemigos1[i].hitbox.alto, al_map_rgb(255, 0, 0), 1);
            }


            //hitbox proyectiles enemigos
            for(i=0;i<numenemigos;i++){
                for(j=0;j<maxproyectiles;j++){
                    al_draw_rectangle(enemigos1[i].proyectiles[j].hitbox.x, enemigos1[i].proyectiles[j].hitbox.y, enemigos1[i].proyectiles[j].hitbox.x + enemigos1[i].proyectiles[j].hitbox.ancho, enemigos1[i].proyectiles[j].hitbox.y + enemigos1[i].proyectiles[j].hitbox.alto, al_map_rgb(255, 0, 0), 1);
                }
            }

            // powerup
            if(powerup.activo==true){
                al_draw_rectangle(powerup.hitbox.x, powerup.hitbox.y, powerup.hitbox.x + powerup.hitbox.ancho, powerup.hitbox.y + powerup.hitbox.alto, al_map_rgb(255, 0, 0), 1);
            }
        }