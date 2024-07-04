// PARA COMPILAR: gcc houtou.c -o prueba.exe -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_acodec -lallegro_dialog

#include "config.h"


bool key[ALLEGRO_KEY_MAX] = { false };
bool dibujar=false;

 
/*INICIO MAIN-------------------------------------------------------------*/
int main(){

 al_init();
 al_install_keyboard();
 al_init_font_addon();
 al_init_ttf_addon();
 al_init_image_addon();
 al_init_primitives_addon();
 al_init_acodec_addon();
 al_install_audio();
 al_reserve_samples(1);

 int i=0,j=0,k=0;
 

   /*> VENTANA-------------------------*/
    ALLEGRO_DISPLAY *display = al_create_display(x_display,y_display); 
    al_set_window_title(display,"HOUTOU"); /*titulo ventana*/
    bool GameRunning=true; /*para ver si el juego se cierra o no*/
   /*---------------------------------*/
   


   /*> TIMERS, EVENTOS PRINCIPALES------------------------*/
    ALLEGRO_TIMER* fps = al_create_timer(1.0 / 60); /*fps del juego*/ 
    ALLEGRO_TIMER* timer_segundos = al_create_timer(1.0); /*contador de segundos*/
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); /*cola principal*/
    al_register_event_source(queue, al_get_keyboard_event_source()); 
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(fps));
    al_register_event_source(queue, al_get_timer_event_source(timer_segundos));
    ALLEGRO_EVENT event;
    
   /*---------------------------------------------------*/
    


   /*> IMAGENES Y FUENTES DEL JUEGO EN GENERAL-------------*/
    ALLEGRO_FONT* font = al_load_ttf_font("font.ttf", 25, 1); /*font principal*/
    ALLEGRO_BITMAP *fondo_nivel = al_load_bitmap("imagenes/fondo_nivel.png"); /*fondo del juego*/
    ALLEGRO_BITMAP *fondo_encima = al_load_bitmap("imagenes/fondoencima.png");
    int animacion_fondo=0; /*variable con la que se hará la animacion del fondo*/
    int animacion_fondo_encima=0;

    //ALLEGRO_SAMPLE* musicafondo = al_load_sample("musicafondo.mp3"); /*musica de fondo*/
    //ALLEGRO_SAMPLE_INSTANCE* musicafondoinstance = al_create_sample_instance(musicafondo);
    //al_set_sample_instance_playmode(musicafondoinstance, ALLEGRO_PLAYMODE_LOOP);
	  //al_attach_sample_instance_to_mixer(musicafondoinstance, al_get_default_mixer());

   /*-----------------------------------------------------*/



   /*> OTRAS VARIABLES IMPORTANTES--------*/
       int segundos=0; /*donde se registrarán los segundos*/
       char contador_segundos_char[10]; /*donde se pasarán los segundos a char*/

       int nivel=1;
       int inicionivelcontador=0;
       int pasarnivel=0;

   /*-------------------------------------*/
     ALLEGRO_BITMAP* stage=al_load_bitmap("imagenes/stage1.png");
     ALLEGRO_BITMAP* stage1=al_load_bitmap("imagenes/stage1.png");
     ALLEGRO_BITMAP* stage2=al_load_bitmap("imagenes/stage2.png");
     ALLEGRO_BITMAP* stage3=al_load_bitmap("imagenes/stage3.png");
     ALLEGRO_BITMAP* stage4=al_load_bitmap("imagenes/stage4.png");




/*PERSONAJES-------------------------------------------------------------------*/

  /*> PERSONAJE PRINCIPAL------------------------------*/
   personaje principal;
   iniciarjugador(&principal);
   float velocidad_principal_real=1;
   ALLEGRO_BITMAP *bolainmunidad=al_load_bitmap("imagenes/sprites/inmunidad.png");
   ALLEGRO_COLOR inmunidadroja = al_map_rgba_f(112, 0, 0, 0); /*color inmunidad cuando te da una bala*/
   // INMUNIDAD
   bool inmunidad=false;
   int contadorinmunidad=0;
   // ATAQUE ESPECIAL
   int contadorespecial=-1;
   int contadorduracionespecial=0;
   int auxespecial_x;
   bool especialactivo=false;
   ALLEGRO_BITMAP* imagenataqueactivo=al_load_bitmap("imagenes/ataqueactivo.png");
   char elcontadordelataque[10];
      
       // >> timer del proyectil
      ALLEGRO_TIMER* timer_proyectil_principal = al_create_timer(1.0 / principal.espaciado_proyectiles);
      al_register_event_source(queue, al_get_timer_event_source(timer_proyectil_principal));
      bool espacio_disparos=false;
    // > VIDAS
    ALLEGRO_BITMAP *vida= al_load_bitmap("imagenes/sprites/vida.png");


    /*------------------------------------------------------*/




  /*ENEMIGOS----------------------*/
    personaje enemigos[numenemigos];
    leerenemigos(enemigos);
    iniciarenemigos(enemigos);
       // >> timer proyectil
       ALLEGRO_TIMER* timer_proyectil_enemigos = al_create_timer(1.0 / enemigos[0].espaciado_proyectiles);
       al_register_event_source(queue, al_get_timer_event_source(timer_proyectil_enemigos));
       bool espaciado_disparoenemigos=false;
    //


   /*-----------------------------------------------*/




   /*-----OBJETOS ESPECIALES--------------*/
   proyectil powerup;
   iniciarpowerup(&powerup);
   int randompowerup;
   bool powerup_activo=false;
   bool powerup_inmunidad_tomado=false;




   /*-------------------------------------*/


    //al_play_sample_instance(musicafondoinstance);

    al_start_timer(fps);
    al_start_timer(timer_segundos);
    al_start_timer(timer_proyectil_principal);
    al_start_timer(timer_proyectil_enemigos);
    




// LOOP PRINCIPAL
    while(GameRunning){
       // para que se cierre al presionar X 
       while (al_get_next_event(queue, &event)){
       if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        GameRunning=false;
       } else {

        
         // MECANICA JUEGO
         srand(time(0));

         





          //prueba (tiempo transcurrido)-------------------
          if(event.timer.source == timer_segundos){
           segundos++;
          } snprintf(contador_segundos_char, 10, "%d", segundos);
          //-----------------------------------------------

          //animacion fondo----------
           animacion_fondo -= 1;
            if(animacion_fondo<-900){
                animacion_fondo=0;
            }
            animacion_fondo_encima -= 2;
            if(animacion_fondo_encima<-900){
               animacion_fondo_encima=0;
            }
          //--------------------------


         


    
         //movimientos personaje principal--------
         movimiento_principal(&velocidad_principal_real, &principal);
         //---------------------------------------

         // lanzar proyectiles-------------------
         disparar_principal(&event, &timer_proyectil_principal, &espacio_disparos, &principal);
        //----------------------------------------

        // ataque especial------------------------
          ataque_especial(&event, &timer_segundos, &contadorespecial, &contadorduracionespecial, &especialactivo, elcontadordelataque, &principal, &auxespecial_x);
        //-----------------------------------------

        // COLISIONES ----------------------------
         // >proyectil del jugador a enemigo
         if(inicionivelcontador==3){
            for(j=0;j<numenemigos;j++){
            if(enemigos[j].vida<0){
                  enemigos[j].activo=false;
              } else {

              //>ataque con proyectiles a enemigo
            if(colisionproyectiles(&enemigos[j],&principal)){
                enemigos[j].vida--;
            }

             //>ataque especial a enemigo
           if(colisionataqueespecial(&enemigos[j], &principal)){
              enemigos[j].vida--;
              //printf("\ncolision ataque especial");
            }
          
          
           }
          }
         }
       

           if((inmunidad)==false&&(inicionivelcontador)==3){
           // >colision proyectil enemigo a jugador
           inmunidadporproyectil(&principal, enemigos, &inmunidad);
           // > colision enemigo a jugador
           inmunidadporenemigo(&principal, enemigos, &inmunidad);
          } 
       
       else if(inmunidad==true){
          // > inmunidad
           inmunidadactiva(&event, timer_segundos, &contadorinmunidad, &inmunidad,&powerup_inmunidad_tomado);
        }
        //----------------------------------------
      

        // HITBOX ENEMIGOS ------------------------
        for(i=0;i<numenemigos;i++){
        movimiento_hitbox_proyectiles(&enemigos[i]);
        movimiento_hitbox(&enemigos[i]);
        }
        //-----------------------------------------


       // espaciado de los disparos de los enemigos-----
         if (espaciado_disparoenemigos == true) {
           espaciado_disparoenemigos = false;
           }
        //-------------------------------------------

        



  /*-------------- NIVELES----------------------------------*/

      /*TITULO INICIAL DE CADA NIVEL*/
      if(inicionivelcontador!=3){
        if(event.timer.source == timer_segundos){
            inicionivelcontador++;
            }
        }
       /*--------------------------*/

       /*TIMER DISPARO DE LOS ENEMIGOS*/
       if(event.timer.source == timer_proyectil_enemigos){
             espaciado_disparoenemigos=true;
         } 
       /*------------------------------*/



/*-----------------COMPORTAMIENTO ENEMIGOS------------------*/

           comportamientoenemigos(&nivel,enemigos, espaciado_disparoenemigos, &inicionivelcontador, &pasarnivel);
           
/*-----------------------------------------------------------*/


       /*-----------POWER UPS-----------------*/
          randompowerup=rand()%10;
          if(powerup_activo==false &&powerup_inmunidad_tomado==false&&randompowerup==1){
            powerup.x=(rand()%(x_display));
            powerup.y=-16;
            powerup_activo=true;
            printf("\npowerup tirado");
          }
          
          if(powerup_activo==true){
            poweruptirar(&powerup,principal,nivel,&inmunidad,&powerup_activo,&powerup_inmunidad_tomado);
          }
       /*---------------------------------------*/







      
       if(nivel==1){ /*NIVEL 1*/
       //-------------------------------
       } else /*fin nivel 1*/

       if(nivel==2){ /*NIVEL 2*/
          stage=stage2;
       } else /*fin nivel 2*/
    
       if(nivel==3){
         stage=stage3;
       } else
       if(nivel==4){
        stage=stage4;
       }


 
        /*DEPURACION--------*/
     if(event.type==ALLEGRO_EVENT_KEY_DOWN){
        if(event.keyboard.keycode==ALLEGRO_KEY_ENTER){
          dibujar=!dibujar;
        }
       }

       // DIBUJO DE OBJETOS------------
       if(event.timer.source == fps){
          
       al_draw_bitmap(fondo_nivel,0,animacion_fondo,0); /*fondo*/
       al_draw_bitmap(fondo_encima,0,animacion_fondo_encima,0);


             //>proyectiles (principal)
              for(i=0;i<maxproyectiles;i++){
                 if(principal.proyectiles[i].activo==true){
                   al_draw_bitmap(principal.imagen_proyectil,principal.proyectiles[i].x,principal.proyectiles[i].y,0);
                }
               }

              //>ataque especial (principal)
              for(i=0;i<maxproyectiles;i++){
                 if(principal.especial[i].activo==true){
                   al_draw_bitmap(principal.especial[i].imagen,principal.especial[i].x,principal.especial[i].y,0);
                }
               }

             //>personaje principal
             if(inmunidad==false){
              al_draw_bitmap(principal.imagen,principal.x,principal.y,0);
             } else if(inmunidad==true&&powerup_inmunidad_tomado==true){
               al_draw_bitmap(principal.imagen,principal.x,principal.y,0);
               al_draw_bitmap(bolainmunidad,principal.x,principal.y,0);
             } else {
              
              al_draw_tinted_bitmap(principal.imagen, inmunidadroja, principal.x, principal.y, 0);
             }
            

            //>proyectiles (enemigos)
             for(j=0;j<numenemigos1+numenemigos2;j++){
              for(i=0;i<maxproyectiles;i++){
                 if(enemigos[j].proyectiles[i].activo==true){
                   al_draw_bitmap(enemigos[j].proyectiles[i].imagen,enemigos[j].proyectiles[i].x,enemigos[j].proyectiles[i].y,0);
                }
               }
             }

             //------
             //> enemigos
             for(i=0;i<numenemigos1+numenemigos2;i++){
                al_draw_bitmap(enemigos[i].imagen,enemigos[i].x,enemigos[i].y,0);
             }

             

       //>contador de tiempo
       al_draw_text(font, al_map_rgb(255, 255, 255), 5, y_display-30, 0, contador_segundos_char);
       //>si el ataque está activo
       if(contadorespecial==-1){
        al_draw_bitmap(imagenataqueactivo,x_display-100,y_display-120,0);
       } else {
        al_draw_text(font, al_map_rgb(255, 255, 255), x_display-40, y_display-80, 0, elcontadordelataque);
       }

       // vidas del personaje----
       if(principal.vida>0){
        if(principal.vida>4){
          al_draw_rectangle(x_display-230+71,y_display-60+25,x_display-230+71+(principal.vida*22),y_display-60+34,al_map_rgb(128, 184, 120),9);
        } else
        if(principal.vida>2){
          al_draw_rectangle(x_display-230+71,y_display-60+25,x_display-230+71+(principal.vida*22),y_display-60+34,al_map_rgb(242, 165, 97),9);
        } else {
          al_draw_rectangle(x_display-230+71,y_display-60+25,x_display-230+71+(principal.vida*22),y_display-60+34,al_map_rgb(199, 66, 79),9);
        }
       
       }
       al_draw_bitmap(vida, x_display-230,y_display-60,0);
       //------------------------
    


     /*-----------HITBOXS-----*/
       if(dibujar==true){
            dibujohitboxs(principal, enemigos, powerup);
       }

      /*------------------*/

      /*VIDA ENEMIGOS*/
      for(i=0;i<numenemigos1+numenemigos2;i++){
        if(enemigos[i].vida>=0&&enemigos[i].tipoenemigo==1){
        al_draw_rectangle(enemigos[i].x,enemigos[i].y,enemigos[i].x+(enemigos[i].vida*5),enemigos[i].y,al_map_rgb(128, 184, 120), 4);
        } else if(enemigos[i].vida>=0&&enemigos[i].tipoenemigo==2){
          al_draw_rectangle(enemigos[i].x,enemigos[i].y,enemigos[i].x+(enemigos[i].vida*1.5),enemigos[i].y,al_map_rgb(128, 184, 120), 4);
         }
      }

      

      /*NIVEL INICIO*/
      if(inicionivelcontador!=3){
        al_draw_bitmap(stage, 10, 150, 0);
      }


      /*POWERUP*/

      if(powerup_activo==true){
        al_draw_bitmap(powerup.imagen,powerup.x,powerup.y,0);
      }


      al_flip_display();
       }
      
       




        
       //------------------------------

       }
       
    

        
        //verificador de que si se está presionando el teclado
        verificadorteclado(&event, &principal);
        //----------------------------------------------------



        // cerrar al perder todas las vidas
        //if(principal.vida==0){
          //  GameRunning=false;
        //}
        //----------
 

    // FIN LOOP!! NO TOCAR
       }
    }
    // FIN LOOP!! NO TOCAR
    


    
 

// destroys
    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_timer(fps);
    al_destroy_timer(timer_proyectil_principal);
    al_destroy_timer(timer_segundos);
    al_destroy_timer(timer_proyectil_enemigos);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(principal.imagen);
    al_destroy_bitmap(principal.estatico);
    al_destroy_bitmap(principal.derecha);
    al_destroy_bitmap(principal.izquierda);
    al_destroy_bitmap(principal.imagen_proyectil);
    for(i=0;i<numenemigos;i++){al_destroy_bitmap(enemigos[i].imagen);};

    for(i=0;i<numenemigos;i++){
      for(j=0;j<maxproyectiles;j++){
        al_destroy_bitmap(enemigos[i].proyectiles[j].imagen);
      }
    }

    for(i=0;i<maxproyectiles;i++){
      al_destroy_bitmap(principal.especial[i].imagen);
    }

    for(i=0;i<numenemigos;i++){
      for(j=0;j<maxproyectiles;j++){
        al_destroy_bitmap(enemigos[i].proyectiles[j].destruido);
      }
    }
    
    al_destroy_bitmap(fondo_nivel);
    al_destroy_bitmap(fondo_encima);
    al_destroy_bitmap(vida);
    al_destroy_bitmap(bolainmunidad);
    al_destroy_bitmap(stage);
    al_destroy_bitmap(stage1);
    al_destroy_bitmap(stage2);
    al_destroy_bitmap(stage3);
    al_destroy_bitmap(stage4);
    al_destroy_bitmap(imagenataqueactivo);
    al_destroy_bitmap(powerup.imagen);
    //al_destroy_sample(musicafondo);
    //al_destroy_sample_instance(musicafondoinstance);

    

    return 0;
}






