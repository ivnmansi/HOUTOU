#include "niveles.h"

/*---DISPARO A PROYECTILES (PARA ENEMIGOS TIPO 3)*/
void dispararleproyectiles(personaje *personaje1 ,personaje *enemigo, int *puntuacion){
    int i,j;

    for(i=0;i<maxproyectiles;i++){
      for(j=0;j<maxproyectiles;j++){
     if( (personaje1->proyectiles[i].activo==true)&&(personaje1->proyectiles[i].hitbox.x < enemigo->proyectiles[j].hitbox.x+enemigo->proyectiles[j].hitbox.ancho)&&(personaje1->proyectiles[i].hitbox.x+personaje1->proyectiles[i].hitbox.ancho > enemigo->proyectiles[j].hitbox.x)&&  (personaje1->proyectiles[i].hitbox.y < enemigo->proyectiles[j].hitbox.y+enemigo->proyectiles[j].hitbox.alto)&&(personaje1->proyectiles[i].hitbox.y+personaje1->proyectiles[i].hitbox.alto > enemigo->proyectiles[j].hitbox.y)  ){
        (*puntuacion) += 5;
         enemigo->proyectiles[j].activo=false;
         
     }
    }
   }
 }

/*------------ COMPORTAMIENTO DE ENEMIGOS-------------*/
 void comportamientoenemigos(int numenemigos, int *nivel, personaje enemigos[numenemigos], bool espaciado_disparoenemigos, int *inicionivelcontador, int *pasarnivel, personaje principal, int *puntuacion, bool *se_gano, int segundos){
   int i,j,k;
   int numerocorte_abajo=0,numerocorte_arriba=0;
   int numeroenemigosnivel;
    int verificadorganar=0;

     //calculo numeros de corte
     for (i=0;i<(*nivel-1);i++){
        numerocorte_abajo += numenemigospornivel[i];
      }
      numerocorte_arriba = numerocorte_abajo + numenemigospornivel[*nivel-1];

      numeroenemigosnivel=numerocorte_arriba-numerocorte_abajo;
     //-----------------------
     *pasarnivel=0;



    for(i=numerocorte_abajo;i<numerocorte_arriba;i++){

      // entrada al nivel de todos-----
       if((*inicionivelcontador)!=3){
              if(enemigos[i].y<100){
              enemigos[i].y +=0.8;
              
              enemigos[i].x=(y_display-(numeroenemigosnivel+1))/((numeroenemigosnivel+4))*(((i-numerocorte_abajo)))+(y_display/(2*(numeroenemigosnivel+1)))-30;
          }
        }
      //------------------------------


       //ENEMIGOS 1
        if(enemigos[i].tipoenemigo==1&&(*inicionivelcontador)==3){

           if(enemigos[i].activo==true){

            // movimiento
             enemigos[i].velocidad_angular += 0.06;
             enemigos[i].x += (2*cos(enemigos[i].velocidad_angular));
             enemigos[i].y += (3*sin(enemigos[i].velocidad_angular));
            

            // >proyectiles----------

             if(espaciado_disparoenemigos==true){
              for(j=0;j<maxproyectiles;j++){
                  
                    if(enemigos[i].proyectiles[j].activo==false){ /*spawneo de los proyectiles*/
                        enemigos[i].proyectiles[j].x=enemigos[i].x+21;
                        enemigos[i].proyectiles[j].y=enemigos[i].y+50;
                        enemigos[i].proyectiles[j].activo=true;
                        enemigos[i].proyectiles[j].aceleracion=(i+1)*0.5;
                        break;
                      }
                    }
                  } 
               else{
                    
              for(j=0;j<maxproyectiles;j++){
                    if(enemigos[i].proyectiles[j].activo==true){

                        if(enemigos[i].proyectiles[j].aceleracion>0){
                        enemigos[i].proyectiles[j].aceleracion -= 0.01;
                        }
                        
                        if(enemigos[i].proyectiles[j].aceleracion_angular<90){
                        enemigos[i].proyectiles[j].aceleracion_angular += 0.3;
                        } else {
                          enemigos[i].proyectiles[j].aceleracion_angular=enemigos[i].proyectiles[j].aceleracion_angular*-1;
                        }
                       
                        enemigos[i].proyectiles[j].x = enemigos[i].proyectiles[j].x+cos(enemigos[i].proyectiles[j].aceleracion_angular);
                        enemigos[i].proyectiles[j].y += enemigos[i].proyectiles[j].aceleracion+enemigos[i].velocidad_proyectiles;

                        if(enemigos[i].proyectiles[j].y>y_display||enemigos[i].proyectiles[j].y<0){ /*eliminacion al salir de pantalla*/
                            enemigos[i].proyectiles[j].activo=false;
                        }
                    }

               }
             }

           } 
           else { /*si el enemigo es eliminado*/
            
            enemigos[i].x=-50;
            enemigos[i].y=-50;

             for(j=0;j<maxproyectiles;j++){
                    

                    if(enemigos[i].proyectiles[j].activo==true){
                        enemigos[i].proyectiles[j].imagen=enemigos[i].proyectiles[j].destruido;

                        enemigos[i].proyectiles[j].aceleracion -= 0.05;
                       
                        enemigos[i].proyectiles[j].x += sin(10);
                        enemigos[i].proyectiles[j].y += enemigos[i].proyectiles[j].aceleracion+enemigos[i].velocidad_proyectiles+cos(10);

                        if(enemigos[i].proyectiles[j].y>y_display||enemigos[i].proyectiles[j].y<0){ /*eliminacion al salir de pantalla*/
                            enemigos[i].proyectiles[j].activo=false;
                        }
                    }

               }
            }

        } else
        //FIN ENEMIGOS 1

        //ENEMIGOS 2
        if(enemigos[i].tipoenemigo==2&&(*inicionivelcontador)==3){
          
           // mov principal
           if(enemigos[i].activo==true){
           /*movimiento*/
          
           enemigos[i].velocidad_angular += 0.1;

           enemigos[i].x += (4*(cos(enemigos[i].velocidad_angular)));
           enemigos[i].y += (1*(sin(enemigos[i].velocidad_angular)));

           enemigos[i].aux_x=enemigos[i].x;
           enemigos[i].aux_y=enemigos[i].y;

           /*proyectiles*/
            if(espaciado_disparoenemigos==true){
              for(j=0,k=0;j<maxproyectiles;j++){
                  
                    if(enemigos[i].proyectiles[j].activo==false){ /*spawneo de los proyectiles*/
                        enemigos[i].proyectiles[j].x=enemigos[i].x+29;
                        enemigos[i].proyectiles[j].y=enemigos[i].y+50;
                        enemigos[i].proyectiles[j].activo=true;
                        enemigos[i].proyectiles[j].aceleracion=1;
                        enemigos[i].proyectiles[j].aceleracion_angular=((2* M_PI) /n)*k;
                        k++;
                        if(k==n){
                        break;
                        }
                      }
                    }
                  } 
               else{
                    
              for(j=0;j<maxproyectiles;j++){
                    if(enemigos[i].proyectiles[j].activo==true){
                       
                        enemigos[i].proyectiles[j].x += 2*cos(enemigos[i].proyectiles[j].aceleracion_angular);
                        enemigos[i].proyectiles[j].y += 2*sin(enemigos[i].proyectiles[j].aceleracion_angular);

                        if(enemigos[i].proyectiles[j].y>y_display||enemigos[i].proyectiles[j].y<0||enemigos[i].proyectiles[j].x<-16||enemigos[i].proyectiles[j].x>x_display){ /*eliminacion al salir de pantalla*/
                            enemigos[i].proyectiles[j].activo=false;
                        }
                    }

               }
             }

           }
           else if(enemigos[i].activo==false){ //cuando son eliminados
             enemigos[i].x=-60;
             enemigos[i].y=-60;
             for(j=0;j<maxproyectiles;j++){
                if(enemigos[i].proyectiles[j].activo==true){
                        
                        enemigos[i].proyectiles[j].imagen=enemigos[i].proyectiles[j].destruido;

                        enemigos[i].proyectiles[j].aceleracion_angular = atan2(enemigos[i].proyectiles[j].y-enemigos[i].aux_y, enemigos[i].proyectiles[j].x-enemigos[i].aux_x);
                       
                        enemigos[i].proyectiles[j].x -= 5*cos(enemigos[i].proyectiles[j].aceleracion_angular);
                        enemigos[i].proyectiles[j].y -= 5*sin(enemigos[i].proyectiles[j].aceleracion_angular);

                        if(enemigos[i].proyectiles[j].y>y_display||enemigos[i].proyectiles[j].y<-16||enemigos[i].proyectiles[j].x<-16||enemigos[i].proyectiles[j].x>x_display){ /*eliminacion al salir de pantalla*/
                            enemigos[i].proyectiles[j].activo=false;
                        } else
                        if((abs(enemigos[i].proyectiles[j].x-(enemigos[i].aux_x)<10&&abs(enemigos[i].proyectiles[j].y-enemigos[i].aux_y)<10))){
                           enemigos[i].proyectiles[j].activo=false;
                        }
                    }
                }
             }
        } else
       //FIN ENEMIGOS 2
    

      // ENEMIGOS 3---------------------
       if(enemigos[i].tipoenemigo==3&&(*inicionivelcontador)==3){
          
           // mov principal

           if(enemigos[i].activo==true){

           /*movimiento*/
          
           
           enemigos[i].velocidad_angular += 0.1;
           if(enemigos[i].velocidad_angular>=2*M_PI){
            enemigos[i].velocidad_angular=0;
           }

           enemigos[i].x += (5*(cos(enemigos[i].velocidad_angular)));

           /*proyectiles*/
            if(espaciado_disparoenemigos==true){
              for(j=0,k=0;j<maxproyectiles;j++){

                  
                    if(enemigos[i].proyectiles[j].activo==false){ /*spawneo de los proyectiles*/
                        enemigos[i].proyectiles[j].x=enemigos[i].x+29;
                        enemigos[i].proyectiles[j].y=enemigos[i].y+50;
                        enemigos[i].proyectiles[j].activo=true;
                        enemigos[i].proyectiles[j].aceleracion=1;
                        enemigos[i].proyectiles[j].aceleracion_angular=((M_PI)/15)*k+(M_PI/4);
                        k++;
                        if(k==7){
                        break;
                        }
                        
                      }
                    }
                  } 
               else{
                    
              for(j=0;j<maxproyectiles;j++){
                    if(enemigos[i].proyectiles[j].activo==true){
                        
                        if(enemigos[i].proyectiles[j].y>250&&(enemigos[i].proyectiles[j].y<(principal.y-150))){
                        enemigos[i].proyectiles[j].aceleracion_angular=atan2(principal.y-enemigos[i].proyectiles[j].y,principal.x-enemigos[i].proyectiles[j].x);
                        }
                       
                        enemigos[i].proyectiles[j].x += 2*cos(enemigos[i].proyectiles[j].aceleracion_angular);
                        enemigos[i].proyectiles[j].y += 2*sin(enemigos[i].proyectiles[j].aceleracion_angular);

                        if(enemigos[i].proyectiles[j].y>y_display||enemigos[i].proyectiles[j].y<0||enemigos[i].proyectiles[j].x<-16||enemigos[i].proyectiles[j].x>x_display){ /*eliminacion al salir de pantalla*/
                            enemigos[i].proyectiles[j].activo=false; // eliminacion cuando salen de pantalla
                        }
                        dispararleproyectiles(&principal,&enemigos[i],puntuacion);
                        
                    }

               }
             }

           }
           else if(enemigos[i].activo==false){ //cuando son eliminados
             enemigos[i].x=-60;
             enemigos[i].y=-60;
             for(j=0;j<maxproyectiles;j++){
                if(enemigos[i].proyectiles[j].activo==true){
                        
                        enemigos[i].proyectiles[j].imagen=enemigos[i].proyectiles[j].destruido;
                       
                        enemigos[i].proyectiles[j].y += 3;

                        if(enemigos[i].proyectiles[j].y>y_display||enemigos[i].proyectiles[j].y<0||enemigos[i].proyectiles[j].x<-16||enemigos[i].proyectiles[j].x>x_display){ /*eliminacion al salir de pantalla*/
                            enemigos[i].proyectiles[j].activo=false;
                        }
                    }
                }
             }
        } else//FIN ENEMIGOS 3

        //boss
        if(enemigos[i].tipoenemigo==5 && *inicionivelcontador==3){


           // mov principal

           if(enemigos[i].activo==true){

           /*movimiento*/
          
           
           enemigos[i].velocidad_angular += 0.05;

           enemigos[i].x += (6*(cos(enemigos[i].velocidad_angular)));

           enemigos[i].aux_x=enemigos[i].x;
           enemigos[i].aux_y=enemigos[i].y;

           /*proyectiles*/
           
            if(espaciado_disparoenemigos==true){

              for(j=0,k=0;j<maxproyectiles;j++){
                  
                    if(enemigos[i].proyectiles[j].activo==false){ /*spawneo de los proyectiles*/
                        enemigos[i].proyectiles[j].x=enemigos[i].x+29;
                        enemigos[i].proyectiles[j].y=enemigos[i].y+50;
                        enemigos[i].proyectiles[j].activo=true;
                        enemigos[i].proyectiles[j].aceleracion=1;
                        enemigos[i].proyectiles[j].aceleracion_angular=((2* M_PI) /n_boss)*k;
                        k++;
                        if(k==n_boss){
                        break;
                        }
                      }
                    }

                 }
               else{
                     
              for(j=0;j<maxproyectiles;j++){
                    if(enemigos[i].proyectiles[j].activo==true){
                       
                        enemigos[i].proyectiles[j].x += (6*cos(4*(enemigos[i].proyectiles[j].aceleracion_angular))*cos(enemigos[i].proyectiles[j].aceleracion_angular));
                        enemigos[i].proyectiles[j].y += (6*cos(4*(enemigos[i].proyectiles[j].aceleracion_angular))*sin(enemigos[i].proyectiles[j].aceleracion_angular));

                        if(enemigos[i].proyectiles[j].y>y_display||enemigos[i].proyectiles[j].y<0||enemigos[i].proyectiles[j].x<-16||enemigos[i].proyectiles[j].x>x_display){ /*eliminacion al salir de pantalla*/
                            enemigos[i].proyectiles[j].activo=false;
                        }
                    }

               }
              }
               
           }
           else if(enemigos[i].activo==false){ //cuando son eliminados
             enemigos[i].x=-60;
             enemigos[i].y=-60;
             for(j=0;j<maxproyectiles;j++){
                if(enemigos[i].proyectiles[j].activo==true){
                        
                        enemigos[i].proyectiles[j].imagen=enemigos[i].proyectiles[j].destruido;

                        enemigos[i].proyectiles[j].aceleracion_angular = atan2(enemigos[i].proyectiles[j].y-enemigos[i].aux_y, enemigos[i].proyectiles[j].x-enemigos[i].aux_x);
                       
                        enemigos[i].proyectiles[j].x -= 5*cos(enemigos[i].proyectiles[j].aceleracion_angular);
                        enemigos[i].proyectiles[j].y -= 5*sin(enemigos[i].proyectiles[j].aceleracion_angular);

                        if(enemigos[i].proyectiles[j].y>y_display||enemigos[i].proyectiles[j].y<-16||enemigos[i].proyectiles[j].x<-16||enemigos[i].proyectiles[j].x>x_display){ /*eliminacion al salir de pantalla*/
                            enemigos[i].proyectiles[j].activo=false;
                        } else
                        if((abs(enemigos[i].proyectiles[j].x-(enemigos[i].aux_x)<10&&abs(enemigos[i].proyectiles[j].y-enemigos[i].aux_y)<10))){
                           enemigos[i].proyectiles[j].activo=false;
                        }
                    }
                }
             }

        }
    
       






       // PARA PASAR DE NIVEL
            for(j=0;j<maxproyectiles;j++){
             if(enemigos[i].activo==false&&(enemigos[i].proyectiles[j].activo==false)){
              (*pasarnivel)++;
             }
            }

      }

       if((*pasarnivel)==(numeroenemigosnivel*maxproyectiles)){
            
            for(i=0;i<numenemigos;i++){
              if(enemigos[i].activo==false){
                verificadorganar++;
              }
            }

            if(verificadorganar==numenemigos){
               *se_gano=true;
            } else

            (*pasarnivel)=0;
            *inicionivelcontador=0;
            (*nivel)++;
           }
    }



/*------------INICIALIZACION DE POWERUPS----------*/
    void iniciarpowerup(proyectil *powerup){
       powerup->x=-16;
       powerup->y=-16;
       powerup->activo=false;
       powerup->aceleracion=1;
       powerup->aceleracion_angular=0;
       powerup->imagen=al_load_bitmap("imagenes/obstaculos/powerupsheet.png");
       powerup->tipo=0;
       //hitbox
           powerup->hitbox.x=0;
           powerup->hitbox.y=0;
           powerup->hitbox.ancho=16;
           powerup->hitbox.alto=15;
           powerup->hitbox.arreglo_x=0;
            powerup->hitbox.arreglo_y=0;
    }

/*----TIRAR POWERUP--------*/
    void poweruptirar(proyectil *powerup, personaje *principal, int nivel, bool *inmunidad,bool *powerup_activo, bool *powerup_inmunidad_tomado, bool *ataquetripleactivo){
       // definicion aleatoria del tipo del powerup. 1) inmunidad 2) +1 vida 3) disparo triple
       if(powerup->tipo==0){
       powerup->tipo=(rand()%3)+1; 
       }
 
       double dif_y=(principal->hitbox.y+principal->hitbox.y)/2-powerup->y;
       double dif_x=(principal->hitbox.x+principal->hitbox.x)/2-powerup->x;
       //movimiento

       powerup->aceleracion_angular=atan2(dif_y,dif_x);
       
       if(abs(principal->x-powerup->x)<100&&abs(principal->y-powerup->y)<100){
         powerup->x +=2*cos(powerup->aceleracion_angular);
         powerup->x +=2*sin(powerup->aceleracion_angular);
       }

       powerup->y++;
       powerup->hitbox.x=powerup->x;
       powerup->hitbox.y=powerup->y;

       if((principal->hitbox.x < powerup->hitbox.x+powerup->hitbox.ancho)&&(principal->hitbox.x+principal->hitbox.ancho > powerup->hitbox.x)&&  (principal->hitbox.y < powerup->hitbox.y+powerup->hitbox.alto)&&(principal->hitbox.y+principal->hitbox.alto > powerup->hitbox.y)){
          
          if(powerup->tipo==1){
          *inmunidad=true;
          *powerup_inmunidad_tomado=true;
          } else
          if(powerup->tipo==2&&(principal->vida)<6){
            (principal->vida)++;
          } else
          if(powerup->tipo==3){
            *ataquetripleactivo=true;
          }

          powerup->tipo=0;
          powerup->activo=false;
          *powerup_activo=false;
       }

       if(powerup->y>y_display){
         powerup->activo=false;
         *powerup_activo=false;
       }
    }

/*-----INICIALIZACION DE VARIABLES DEL JUEGO (PARA REINICIAR EL JUEGO CUANDO SE TERMINA UNA PARTIDA)------*/
    void iniciarvariables(int *animacion_fondo,int *animacion_fondo_encima, int *opcion_menu, int *segundos, int *inicionivelcontador, int *pasarnivel, int *puntuacion, float *puntuacionfinal, bool *inmunidad, int *contadorinmunidad, bool *ataquetripleactivo, int *contadortriple, int *contadorespecial, int *contadorduracionespecial, bool *especialactivo, bool *espacio_disparos){

      /*FONDO*/
      *animacion_fondo=0; /*variable con la que se hará la animacion del fondo*/
      *animacion_fondo_encima=0;
      /*-----*/

      *opcion_menu=1;

      /*--PUNTUACION--*/
       *segundos=0; /*donde se registrarán los segundos*/

       *inicionivelcontador=0;
       *pasarnivel=0;

       *puntuacion=0;
       *puntuacionfinal=0;
       /*-------------*/


       /*PERSONAJE PRINCIPAL*/

       *inmunidad=false;
       *contadorinmunidad=0;
       *ataquetripleactivo=false;
       *contadortriple=0;
       *contadorespecial=-1;
       *contadorduracionespecial=0;
       *especialactivo=false;
       *espacio_disparos=false;

    }

/*----------LECTURA DEL RANKING------------*/
void leerranking(ranking ranking1[10]){
  int i=0,j=0,k=0;
    FILE *file=fopen("ranking.txt", "r+b");
    if(file!=NULL) {

        for (i=0;i<10;i++){
          fscanf(file, "%s %d", ranking1[i].nombre, &ranking1[i].puntaje);
        }
    fclose(file);
    } else {
        printf("Error al abrir el archivo\n");
    }
}

/*----ORDENAR AUTOMATICAMENTE EL RANKING DE MAYOR A MENOR*/
void ordenar_ranking(ranking ranking1[10]){
   
    int i=0,j=0;
    ranking aux;

    for(i=0;i<9;i++){
      for(j=0;j<9-i;j++){
     
      if(ranking1[j].puntaje<ranking1[j+1].puntaje){
         aux=ranking1[j];
         ranking1[j]=ranking1[j+1];
         ranking1[j+1]=aux;
      }
     }
    }

    FILE *file=fopen("ranking.txt", "r+b");
    if(file!=NULL) {

        for (i=0;i<10;i++){
          fprintf(file, "%s %d\n", ranking1[i].nombre, ranking1[i].puntaje);
        }

    fclose(file);
    } else {
        printf("Error al abrir el archivo\n");
    }
  }