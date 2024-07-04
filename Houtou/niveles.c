#include "niveles.h"

 void comportamientoenemigos(int *nivel, personaje enemigos[numenemigos], bool espaciado_disparoenemigos, int *inicionivelcontador, int *pasarnivel){
   int i,j,k;
   int numerocorte_abajo,numerocorte_arriba;

    *pasarnivel=0;

     if(*nivel==1){
      numerocorte_arriba=numenemigos1;
      numerocorte_abajo=0;
     } else
     if(*nivel==2){
      numerocorte_arriba=numenemigos1+numenemigos2;
      numerocorte_abajo=numenemigos1;
     } else
     if(*nivel==3){
      numerocorte_arriba=numenemigos1+numenemigos2+numenemigos3;
      numerocorte_abajo=numenemigos1+numenemigos2;
     } else
     if(*nivel==4){
      numerocorte_arriba=numenemigos;
      numerocorte_abajo=numenemigos1+numenemigos2+numenemigos3;
     }



 
    for(i=numerocorte_abajo;i<numerocorte_arriba;i++){

       //ENEMIGOS 1
        if(enemigos[i].tipoenemigo==1){

         //entrada al nivel
           if((*inicionivelcontador)!=3){
              if(enemigos[i].y<100){
              enemigos[i].y +=0.8;
            }
           } else
            //


      
           if(enemigos[i].activo==true){

            // movimiento
             enemigos[i].velocidad_angular += 0.04;
             enemigos[i].x += (1*cos(enemigos[i].velocidad_angular));
             enemigos[i].y += (2*sin(enemigos[i].velocidad_angular));
            


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
        if(enemigos[i].tipoenemigo==2){
          
           // entrada al nivel
           if((*inicionivelcontador)!=3){
               if(i<(numenemigos1+(numenemigos2/2))){
                if(enemigos[i].x<i*20)
                enemigos[i].x += enemigos[numenemigos1].velocidad;
              } else {
                if(enemigos[i].x>x_display-150){
                  enemigos[i].x -= enemigos[numenemigos1].velocidad+1;
                }
              }
           } else
           // mov principal

           if(enemigos[i].activo==true){

           /*movimiento*/

           enemigos[i].velocidad_angular += 0.1;

           enemigos[i].x += (4*(cos(enemigos[i].velocidad_angular)));
           enemigos[i].y += (1*(sin(enemigos[i].velocidad_angular)));

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
                       
                        enemigos[i].proyectiles[j].x += cos(enemigos[i].proyectiles[j].aceleracion_angular);
                        enemigos[i].proyectiles[j].y += sin(enemigos[i].proyectiles[j].aceleracion_angular);

                        if(enemigos[i].proyectiles[j].y>y_display||enemigos[i].proyectiles[j].y<0||enemigos[i].proyectiles[j].x<-16||enemigos[i].proyectiles[j].x>x_display){ /*eliminacion al salir de pantalla*/
                            enemigos[i].proyectiles[j].activo=false;
                        }
                    }

               }
             }
           


           }
           else { //cuando son eliminados
             enemigos[i].x=-50;
             enemigos[i].y=-50;
             for(j=0;j<maxproyectiles;j++){
                if(enemigos[i].proyectiles[j].activo==true){

                         enemigos[i].proyectiles[j].aceleracion_angular = atan2(enemigos[i].proyectiles[j].y-100, enemigos[i].proyectiles[j].x-(x_display/2));
                       
                        enemigos[i].proyectiles[j].x -= cos(enemigos[i].proyectiles[j].aceleracion_angular);
                        enemigos[i].proyectiles[j].y -= sin(enemigos[i].proyectiles[j].aceleracion_angular);

                        if(enemigos[i].proyectiles[j].y>y_display||enemigos[i].proyectiles[j].y<0||enemigos[i].proyectiles[j].x<-16||enemigos[i].proyectiles[j].x>x_display){ /*eliminacion al salir de pantalla*/
                            enemigos[i].proyectiles[j].activo=false;
                        } else
                        if((enemigos[i].proyectiles[j].x-(x_display/2)<10&&enemigos[i].proyectiles[j].y-100)<10){
                           enemigos[i].proyectiles[j].activo=false;
                        }
                    }
                }
             }
        }
       //FIN ENEMIGOS 2
       






       // PARA PASAR DE NIVEL
            for(j=0;j<maxproyectiles;j++){
             if(enemigos[i].activo==false&&(enemigos[i].proyectiles[j].activo==false)){
              (*pasarnivel)++;
             }
            }

      }
       if((*pasarnivel)==(numerocorte_arriba-numerocorte_abajo)*maxproyectiles){
            printf("se puede pasar de nivel");
            printf("\n%d", pasarnivel);
            (*pasarnivel)=0;
            *inicionivelcontador=0;
            (*nivel)++;
           }
    }


    void iniciarpowerup(proyectil *powerup){
       powerup->x=-16;
       powerup->y=-16;
       powerup->activo=false;
       powerup->aceleracion=1;
       powerup->imagen=al_load_bitmap("imagenes/obstaculos/powerup.png");
       //hitbox
           powerup->hitbox.x=0;
           powerup->hitbox.y=0;
           powerup->hitbox.ancho=16;
           powerup->hitbox.alto=15;
           powerup->hitbox.arreglo_x=0;
            powerup->hitbox.arreglo_y=0;
    }

// POWER UP
    void poweruptirar(proyectil *powerup, personaje principal, int nivel, bool *inmunidad,bool *powerup_activo, bool *powerup_inmunidad_tomado){

       //movimiento
       powerup->y++;
       powerup->hitbox.x=powerup->x;
       powerup->hitbox.y=powerup->y;

       if((principal.hitbox.x < powerup->hitbox.x+powerup->hitbox.ancho)&&(principal.hitbox.x+principal.hitbox.ancho > powerup->hitbox.x)&&  (principal.hitbox.y < powerup->hitbox.y+powerup->hitbox.alto)&&(principal.hitbox.y+principal.hitbox.alto > powerup->hitbox.y)){
          *inmunidad=true;
          *powerup_inmunidad_tomado=true;
           powerup->activo=false;
          *powerup_activo=false;
       }

       if(powerup->y>y_display){
         powerup->activo=false;
         *powerup_activo=false;
       }
    }

    
