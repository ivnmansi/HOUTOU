// PARA COMPILAR: gcc houtou.c -o prueba.exe -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_acodec -lallegro_dialog

#include "config.h"


bool key[ALLEGRO_KEY_MAX] = { false };
bool dibujar=false;

int numenemigospornivel[10] = {0};
int numenemigos = 0;
 
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
 al_reserve_samples(2);


 int i=0,j=0,k=0;
 

   /*> VENTANA-------------------------*/
    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
    ALLEGRO_DISPLAY *display = al_create_display(x_display,y_display); 
    al_set_window_title(display,"HOUTOU"); /*titulo ventana*/
    bool GameRunning=true; /*para ver si el juego se cierra o no*/
   /*---------------------------------*/
   
   /*> TIMERS, EVENTOS PRINCIPALES------------------------*/
    ALLEGRO_TIMER* fps = al_create_timer(1.0 / 60); /*fps del juego*/ 
    ALLEGRO_TIMER* timer_segundos = al_create_timer(1.0); /*contador de segundos*/
    ALLEGRO_TIMER* limitador_menu = al_create_timer(1.0/10);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); /*cola principal*/
    al_register_event_source(queue, al_get_keyboard_event_source()); 
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(fps));
    al_register_event_source(queue, al_get_timer_event_source(timer_segundos));
     al_register_event_source(queue, al_get_timer_event_source(limitador_menu));
    ALLEGRO_EVENT event;
    bool redraw;
   /*---------------------------------------------------*/

   /*> MEDIA DEL JUEGO EN GENERAL-------------*/
    ALLEGRO_FONT* font = al_load_ttf_font("font.ttf", 25, 1); /*font principal*/
    ALLEGRO_BITMAP *fondo_nivel = al_load_bitmap("imagenes/fondo_nivel.png"); /*fondo del juego*/
    ALLEGRO_BITMAP *fondo_encima = al_load_bitmap("imagenes/fondoencima.png");
    int animacion_fondo=0; /*variable con la que se hará la animacion del fondo*/
    int animacion_fondo_encima=0;

    ALLEGRO_SAMPLE* musicafondo = al_load_sample("musicafondo.mp3"); /*musica de fondo*/
    ALLEGRO_SAMPLE_INSTANCE* musicafondoinstance = al_create_sample_instance(musicafondo);
    al_attach_sample_instance_to_mixer(musicafondoinstance, al_get_default_mixer());
    al_set_sample_instance_playmode(musicafondoinstance, ALLEGRO_PLAYMODE_LOOP);
    
    ALLEGRO_SAMPLE* musicamenu=al_load_sample("musicamenu.mp3");
    ALLEGRO_SAMPLE_INSTANCE* musicamenuinstance = al_create_sample_instance(musicamenu);
    al_attach_sample_instance_to_mixer(musicamenuinstance, al_get_default_mixer());
    al_set_sample_instance_playmode(musicamenuinstance, ALLEGRO_PLAYMODE_LOOP);
   /*-----------------------------------------------------*/


   /*---------MENU Y CONTROLES---------*/
    ALLEGRO_BITMAP* controles=al_load_bitmap("imagenes/controles.png");
    ALLEGRO_BITMAP* menu=al_load_bitmap("imagenes/menu1.png");
    ALLEGRO_BITMAP* menu1=al_load_bitmap("imagenes/menu1.png");
    ALLEGRO_BITMAP* menu2=al_load_bitmap("imagenes/menu2.png");
    ALLEGRO_BITMAP* menu3=al_load_bitmap("imagenes/menu3.png");
    int opcion_menu=1;

    ALLEGRO_BITMAP* ganarperder=al_load_bitmap("imagenes/ganarperder.png");
   /*---------------------------------*/



   /*----------OTRAS VARIABLES--------*/
       int segundos=0; /*donde se registrarán los segundos*/
       char puntuacion_char[20]; /*donde se pasarán los segundos a char*/

       int nivel=-1; /*nivel*/
       int inicionivelcontador=0; /*contador para dar inicio al nivel*/
       int pasarnivel=0; /*variable para verificar si se pasa de nivel o no*/
       bool se_gano=false;

       int puntuacion=0; /*donde se registra la puntuacion mientras se juega*/
       float puntuacionfinal=0; /*puntuacion al finalizar el juego*/

       ranking ranking[10]; /*ranking*/
       ALLEGRO_USTR *nombre; /*donde se registra el nombre del jugador*/
       nombre=al_ustr_new("");
       int unichar;
       ALLEGRO_BITMAP *fondoranking = al_load_bitmap("imagenes/ranking.png");
       char rankingchar[10][50];
       
   /*--------------imagenes de inicio de nivel-----------------------*/
     ALLEGRO_BITMAP* stage=al_load_bitmap("imagenes/stage1.png");
     ALLEGRO_BITMAP* stage1=al_load_bitmap("imagenes/stage1.png");
     ALLEGRO_BITMAP* stage2=al_load_bitmap("imagenes/stage2.png");
     ALLEGRO_BITMAP* stage3=al_load_bitmap("imagenes/stage3.png");
     ALLEGRO_BITMAP* stage4=al_load_bitmap("imagenes/stage4.png");
    /*----------------------------------------------------*/






  /*>-----PERSONAJE PRINCIPAL------------------------------*/
   personaje principal;
   iniciarimagenesjugador(&principal);
   float velocidad_principal_real=1;
   ALLEGRO_BITMAP *bolainmunidad=al_load_bitmap("imagenes/sprites/inmunidad.png");
   ALLEGRO_COLOR inmunidadroja = al_map_rgba_f(112, 0, 0, 0); /*color inmunidad cuando te da una bala*/
   // INMUNIDAD
   bool inmunidad=false;
   int contadorinmunidad=0;
   // ATAQUE TRIPLE
   bool ataquetripleactivo=false;
   int contadortriple=0;

   // ATAQUE ESPECIAL
   int contadorespecial=-1;
   int contadorduracionespecial=0;
   int auxespecial_x;
   bool especialactivo=false;
   ALLEGRO_BITMAP* imagenataqueactivo=al_load_bitmap("imagenes/ataqueactivo.png");
   char elcontadordelataque[10];
      
       // >> timer del proyectil
      ALLEGRO_TIMER* timer_proyectil_principal=al_create_timer(1.0 / 8);
      al_register_event_source(queue, al_get_timer_event_source(timer_proyectil_principal));
      bool espacio_disparos=false;
    // > VIDAS
    ALLEGRO_BITMAP *vida= al_load_bitmap("imagenes/sprites/vida.png");
   /*------------------------------------------------------*/


  /*-------ENEMIGOS----------------------*/
    bool reinicio=true;
    leernumeroenemigos(numenemigospornivel, &numenemigos);
    personaje enemigos[numenemigos];
    leerenemigos(numenemigos,numenemigospornivel,enemigos);

       // >> timer proyectil
       ALLEGRO_TIMER* timer_proyectil_enemigos = al_create_timer(1.0 / 1.0);
       al_register_event_source(queue, al_get_timer_event_source(timer_proyectil_enemigos));
       bool espaciado_disparoenemigos=false;
   /*-----------------------------------------------*/

   /*-----POWERUPS--------------*/
   proyectil powerup;
   int randompowerup;
   bool powerup_activo=false;
   bool powerup_inmunidad_tomado=false;
   /*-------------------------------------*/


  /*----INICIO TIMERS----*/
    al_start_timer(fps);
    al_start_timer(timer_segundos);
    al_start_timer(timer_proyectil_principal);
    al_start_timer(timer_proyectil_enemigos);
    al_start_timer(limitador_menu);
    /*-------------------*/
    




/*---------INICIO LOOP PRINCIPAL-----------------------*/
    while(GameRunning){
       // para que se cierre al presionar X 
       while (al_get_next_event(queue, &event)){
       if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        GameRunning=false;
       } else {
        
         // MECANICA JUEGO
         srand(time(0) + 10);
 
    /*--------- MENU DE PERDER Y GANAR-------*/
         if(nivel==-3){
           puntuacionfinal=(puntuacion/segundos);
           if(se_gano==true){
            puntuacionfinal=puntuacionfinal*10;
           }
           if(event.timer.source == limitador_menu){
           if(key[ALLEGRO_KEY_ENTER]){
              nivel++;
            }
           }
          }

         else
    /*----------------------------------*/

    /*-------------RANKING---------------*/
       if(nivel==-2){
        leerranking(ranking);
        ordenar_ranking(ranking);
        
        if(reinicio==false){

          // si la puntuacion obtenida entra en el ranking, ingresar nombre
          if(puntuacionfinal>ranking[9].puntaje){ 
 
               //escribir nombre
               if (event.type==ALLEGRO_EVENT_KEY_CHAR){
                 if (al_ustr_length(nombre)<9) {
                  unichar=event.keyboard.unichar;
                  if (unichar>=32&&unichar<=126) {
                    al_ustr_append_chr(nombre, unichar);
                   }
                 }
                }

               // borrar
               if (key[ALLEGRO_KEY_BACKSPACE] && al_ustr_length(nombre)>0 && event.timer.source == limitador_menu) {
                al_ustr_remove_chr(nombre, al_ustr_offset(nombre, al_ustr_length(nombre)-1));
               } else

               // nombre listo
               if(key[ALLEGRO_KEY_ENTER] && event.timer.source == limitador_menu){

                 strncpy(ranking[9].nombre, al_cstr(nombre), 9);
                 ranking[9].puntaje=puntuacionfinal;
                 ordenar_ranking(ranking);
                 reinicio=true;

               }
          } 
          // si no, mostrar ranking
          else{
           reinicio=true;
          }
        } else
        {
         
         /*-----mostrar ranking-------*/
         for(i=0;i<10;i++) {
          snprintf(rankingchar[i], sizeof(rankingchar[i]), "%d. %s - %d", i + 1, ranking[i].nombre, ranking[i].puntaje);
          }
           if(event.timer.source == limitador_menu){
               if(key[ALLEGRO_KEY_ENTER]==true){
                  nivel++;
               } 
           }
        }
       } else
    /*-------------------------*/
    

 /*----------- MENU PRINCIPAL -----------*/
         if(nivel==-1){
          /*REINICIO DEL JUEGO*/
          if(reinicio==true){
            iniciarjugador(&principal);
            iniciarenemigos(numenemigos,enemigos);
            iniciarvariables(&animacion_fondo,&animacion_fondo_encima, &opcion_menu, &segundos, &inicionivelcontador, &pasarnivel, &puntuacion, &puntuacionfinal, &inmunidad, &contadorinmunidad,&ataquetripleactivo, &contadortriple, &contadorespecial, &contadorduracionespecial,&especialactivo, &espacio_disparos);
            iniciarpowerup(&powerup);
            nombre=al_ustr_new("");           
            se_gano=false;
            reinicio=false;
          }
          /*-------*/

           if(event.timer.source == limitador_menu){
             if(opcion_menu==1){ //cuando se está en JUGAR
              menu=menu1;
              if(key[ALLEGRO_KEY_DOWN]){
                opcion_menu++;
              } else
              if(key[ALLEGRO_KEY_ENTER]){
                nivel=0;
              }


             } else
             if(opcion_menu==2){ //cuando se está en ranking
              menu=menu2;
              if(key[ALLEGRO_KEY_DOWN]){
                opcion_menu++;
              } else
              if(key[ALLEGRO_KEY_UP]){
                opcion_menu--;
              } else
              if(key[ALLEGRO_KEY_ENTER]){
                nivel=-2;
              }
              

             } else
             if(opcion_menu==3){
              menu=menu3;
              if(key[ALLEGRO_KEY_UP]){
                opcion_menu--;
              } else
              if(key[ALLEGRO_KEY_ENTER]){
                GameRunning=false;
              }
             }
           }
         } else
    /*-----------MENU DE CONTROLES--------------*/
         if(nivel==0){
          if(event.timer.source == limitador_menu){
               if(key[ALLEGRO_KEY_ENTER]==true){
                  nivel++;
               } 
          }
         } else

  /*-------------INICIO DEL JUEGO-----------*/
        if(nivel>0){  

          //segundos -------------------
          if(event.timer.source == timer_segundos){
           segundos++;
          } 
          //-----------------------------------------------


         //movimientos personaje principal--------
         movimiento_principal(&velocidad_principal_real, &principal);
         //---------------------------------------

         // lanzar proyectiles-------------------
         disparar_principal(&event, &timer_proyectil_principal, &espacio_disparos, &principal, fps, &ataquetripleactivo);
         
        //----------------------------------------

        // ataque especial------------------------
          ataque_especial(&event, timer_segundos, &contadorespecial, &contadorduracionespecial, &especialactivo, elcontadordelataque, &principal, &auxespecial_x);
        //-----------------------------------------

        // COLISIONES ----------------------------
         // >proyectil del jugador a enemigo
        if(inicionivelcontador==3){
            for(j=0;j<numenemigos;j++){
            if(enemigos[j].vida<0){
                  enemigos[j].activo=false;
              } else {


             if(event.timer.source == fps){
              //>ataque con proyectiles a enemigo
            if(colisionproyectiles(&enemigos[j],&principal)){
                enemigos[j].vida--;
                puntuacion += 1000;
            }

             //>ataque especial a enemigo
           if(colisionataqueespecial(&enemigos[j], &principal)){
              enemigos[j].vida--;
              puntuacion += 1000;
            }
             }
          
           }
          }
         }
       
           if((inmunidad)==false&&(inicionivelcontador)==3){
           // >colision proyectil enemigo a jugador
           inmunidadporproyectil(numenemigos,&principal, enemigos, &inmunidad);
           // > colision enemigo a jugador
           inmunidadporenemigo(numenemigos,&principal, enemigos, &inmunidad);
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



  /*-------------- NIVELES----------------------------------*/

      /*TITULO INICIAL DE CADA NIVEL*/
      if(inicionivelcontador!=3){
        if(event.timer.source == timer_segundos){
            inicionivelcontador++;
            }
        }
       /*--------------------------*/


/*-----------------COMPORTAMIENTO ENEMIGOS------------------*/
           if (espaciado_disparoenemigos == true) {
           espaciado_disparoenemigos = false;
           }

           if(event.timer.source == timer_proyectil_enemigos){
             espaciado_disparoenemigos=true;
           } 

           comportamientoenemigos(numenemigos,&nivel,enemigos, espaciado_disparoenemigos, &inicionivelcontador, &pasarnivel, principal, &puntuacion, &se_gano, segundos);
/*-----------------------------------------------------------*/


       /*-----------POWER UPS-----------------*/
          randompowerup=rand()%10;
          if(powerup_activo==false &&powerup_inmunidad_tomado==false&&randompowerup==1){
            powerup.x=(rand()%(x_display));
            powerup.y=-16;
            powerup_activo=true;
          }
          if(powerup_activo==true){
            poweruptirar(&powerup,&principal,nivel,&inmunidad,&powerup_activo,&powerup_inmunidad_tomado,&ataquetripleactivo);
          }
       /*---------------------------------------*/


       /*POWER UP DISPARO TRIPLE*/
       if(ataquetripleactivo==true){
        if(event.timer.source == timer_segundos){
            contadortriple++;
          }
        if(contadortriple==5){
          contadortriple=0;
          ataquetripleactivo=false;
        }
       }
       /*-------------*/



      



      //---cambio de imagenes al inicio de cada nivel
       if(nivel==1){ /*NIVEL 1*/
         stage=stage1;
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
       //-------


       
        // GANAR Y PERDER
        if(principal.vida<0){ //perder
          puntuacion=puntuacion*nivel;
          se_gano=false;
          nivel=-3;
          break;
        } else
        if(se_gano==true){ //ganar
          puntuacion=puntuacion*nivel;
          nivel=-3;
          break;
        }
        //------------


 
        /*---mostrar hitbox---*/
        if(event.type==ALLEGRO_EVENT_KEY_DOWN){
           if(event.keyboard.keycode==ALLEGRO_KEY_ENTER){
             dibujar=!dibujar;
          }
         }



   }
    /*-----FIN MECÁNICAS DEL JUEGO------*/



         
/*---------------- DIBUJO DE OBJETOS (!) ---------------------*/
       // tasa de refresco
       if(event.timer.source == fps){
        redraw=true;
        }
       //---


    if(redraw){

      if(nivel>0){
          //--------animacion fondo----------------
           animacion_fondo -= 1;
            if(animacion_fondo<-y_display){
                animacion_fondo=0;
            }
            animacion_fondo_encima -= 2;
            if(animacion_fondo_encima<-y_display){
               animacion_fondo_encima=0;
            }
            al_draw_bitmap(fondo_nivel,0,animacion_fondo,0); /*fondo*/
            al_draw_bitmap(fondo_encima,0,animacion_fondo_encima,0);
          //--------------------------------------

         
          
          //-----personaje principal------
             //>proyectiles
              for(i=0;i<maxproyectiles;i++){
                 if(principal.proyectiles[i].activo==true){
                   if(ataquetripleactivo==false){
                   al_draw_bitmap_region(principal.imagen_proyectil,0,0,16,16,principal.proyectiles[i].x,principal.proyectiles[i].y,0);
                   } 
                   else{
                     al_draw_bitmap_region(principal.imagen_proyectil,16,0,32,16,principal.proyectiles[i].x,principal.proyectiles[i].y,0);
                   }
                  }
                }
              //>ataque especial
              snprintf(elcontadordelataque, 10, "%d", (contadorespecial-20)*-1);
              for(i=0;i<maxproyectiles;i++){
                 if(principal.especial[i].activo==true){
                   al_draw_bitmap(principal.especial[i].imagen,principal.especial[i].x,principal.especial[i].y,0);
                }
               }
             //>personaje
             if(inmunidad==false){
              al_draw_bitmap(principal.imagen,principal.x,principal.y,0);
             } else if(inmunidad==true&&powerup_inmunidad_tomado==true){
               al_draw_bitmap(principal.imagen,principal.x,principal.y,0);
               al_draw_bitmap(bolainmunidad,principal.x,principal.y,0);
             } else {
              al_draw_tinted_bitmap(principal.imagen, inmunidadroja, principal.x, principal.y, 0);
             }

            //>vidas
              if(principal.vida>0){
                if(principal.vida>4){
                  al_draw_rectangle(x_display-230+71,y_display-60+25,x_display-230+71+(principal.vida*22),y_display-60+34,al_map_rgb(128, 184, 120),9);
                } else
                if(principal.vida>2){
                al_draw_rectangle(x_display-230+71,y_display-60+25,x_display-230+71+(principal.vida*22),y_display-60+34,al_map_rgb(242, 165, 97),9);
                }
                 else {
                  al_draw_rectangle(x_display-230+71,y_display-60+25,x_display-230+71+(principal.vida*22),y_display-60+34,al_map_rgb(199, 66, 79),9);
                }
              }
             


          //---------enemigos-----------
            //>proyectiles
             for(j=0;j<numenemigos;j++){
              for(i=0;i<maxproyectiles;i++){
                 if(enemigos[j].proyectiles[i].activo==true){
                   al_draw_bitmap(enemigos[j].proyectiles[i].imagen,enemigos[j].proyectiles[i].x,enemigos[j].proyectiles[i].y,0);
                  }
                 }
              }
             //> enemigos
             for(i=0;i<numenemigos;i++){
                al_draw_bitmap(enemigos[i].imagen,enemigos[i].x,enemigos[i].y,0);
             }
             //> vidas
             for(i=0;i<numenemigos;i++){
              if(enemigos[i].vida>=0&&enemigos[i].tipoenemigo==1){
                al_draw_rectangle(enemigos[i].x,enemigos[i].y,enemigos[i].x+((enemigos[i].vida/10)*57),enemigos[i].y,al_map_rgb(128, 184, 120), 4);
              } else if(enemigos[i].vida>=0&&enemigos[i].tipoenemigo==2){
                al_draw_rectangle(enemigos[i].x,enemigos[i].y,enemigos[i].x+((enemigos[i].vida/30)*59),enemigos[i].y,al_map_rgb(128, 184, 120), 4);
              } else if(enemigos[i].vida>=0&&enemigos[i].tipoenemigo==3){
                al_draw_rectangle(enemigos[i].x,enemigos[i].y,enemigos[i].x+((enemigos[i].vida/30)*60),enemigos[i].y,al_map_rgb(128, 184, 120), 4);
              } else if(enemigos[i].vida>=0&&enemigos[i].tipoenemigo==5){
                 al_draw_rectangle(enemigos[i].x,enemigos[i].y,enemigos[i].x+((enemigos[i].vida/60)*70),enemigos[i].y,al_map_rgb(128, 184, 120), 4);
              }
             } 

          //-------contadores--------
            //>contador de puntaje
             if(nivel>0){
               snprintf(puntuacion_char, 20, "%d", puntuacion);
               al_draw_text(font, al_map_rgb(0, 0, 0), 8, y_display-27, 0, puntuacion_char);
               al_draw_text(font, al_map_rgb(255, 255, 255), 5, y_display-30, 0, puntuacion_char);
              }
            //>cooldown ataque especial
              if(contadorespecial==-1){
                al_draw_bitmap(imagenataqueactivo,x_display-100,y_display-120,0);
              }
              else {
                al_draw_text(font, al_map_rgb(255, 255, 255), x_display-40, y_display-80, 0, elcontadordelataque);
              }
    

     /*-----------HITBOXS-----*/
       if(dibujar==true){
            dibujohitboxs(numenemigos,principal, enemigos, powerup);
       }
      /*------------------*/


      /*imagen que se muestra al inicio de cada nivel*/
      if(inicionivelcontador!=3){
        al_draw_bitmap(stage, 10, 150, 0);
      }


      /*POWERUPS*/
      if(powerup_activo==true){
        if(powerup.tipo==1){
        al_draw_bitmap_region(powerup.imagen,0,0,16,15,powerup.x,powerup.y,0);
        } else
        if(powerup.tipo==2){
          al_draw_bitmap_region(powerup.imagen,16,0,15,15,powerup.x,powerup.y,0);
        } else
        if(powerup.tipo==3){
          al_draw_bitmap_region(powerup.imagen,32,0,47,15,powerup.x,powerup.y,0);
        }
      }


      if(powerup_inmunidad_tomado==true){
        al_draw_arc(50,50,10,M_PI*2,0-((M_PI*2)/4)*contadorinmunidad,al_map_rgb(255,255,255),5);
      } else
      if(ataquetripleactivo==true){
        al_draw_arc(50,50,10,M_PI*2,0-((M_PI*2)/5)*contadortriple,al_map_rgb(255,255,255),5);
      }


      // barra vida
      al_draw_bitmap(vida, x_display-230,y_display-60,0);

      } else
      /*------FIN DE NIVELES------*/


      /*----PANTALLA DE CONTROLES-----*/
      if(nivel==0){
        al_draw_bitmap(controles,0,0,0);
      } else 
      /*------------------------------*/

      
      /*----PANTALLA DE MENÚ----*/
      if(nivel==-1){
         al_draw_bitmap(menu,0,0,0);
      } else
      /*-------------------------*/


      /*-------PANTALLA DE RANKING--------*/
            if(nivel==-2){
               //ingreso nombre
               if(reinicio==false){
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(255, 0, 0), 250, 240, ALLEGRO_ALIGN_CENTER, al_cstr(nombre));
                al_draw_text(font, al_map_rgb(255, 255, 255), 250, 200, ALLEGRO_ALIGN_CENTER, "Ingresa tu nombre:");
            } else
              // mostrar tabla de ranking
              if(reinicio==true){
                al_draw_bitmap(fondoranking, 0,0,0);
                for(i=0;i<10;i++){
                  al_draw_text(font, al_map_rgba(0, 0, 0, 0), 148, 148+(i * 50), 0, rankingchar[i]);
                  al_draw_text(font, al_map_rgba(244, 0, 255, 1), 152, 152+(i * 50), 0, rankingchar[i]);
                 }
               }     
             } else
        /*-----------------------------*/

        /*--PANTALLA DE PERDIDA O GANAR--*/
         if(nivel==-3){ 
             if(se_gano==false){
                al_draw_bitmap_region(ganarperder,550,0,550,900,0,0,0);
             } else
             if (se_gano==true){
               al_draw_bitmap_region(ganarperder,0,0,550,900,0,0,0);
              }
             snprintf(puntuacion_char, 20, "Tu puntaje: %.0f", puntuacionfinal);
             al_draw_text(font, al_map_rgb(255, 255, 255), x_display/2, y_display-200, ALLEGRO_ALIGN_CENTRE, puntuacion_char);
          }
        /*-------------------------------*/

      
          al_flip_display();
          redraw=false;
       }
       /*---FIN DIBUJO DE OBJETOS---*/


         /*-----MUSICA-----*/
         if(nivel<1&&nivel>-3){ // MUSICA DEL MENU
           al_play_sample_instance(musicamenuinstance);
           al_stop_sample_instance(musicafondoinstance);
         }
         else{ // MUSICA AL JUGAR
            al_stop_sample_instance(musicamenuinstance);
             al_play_sample_instance(musicafondoinstance);
        }
         //------------------------------

       }

        //verificador de que si se está presionando el teclado
        verificadorteclado(&event, &principal);
        //----------------------------------------------------

       }
    }
    // FIN LOOP DEL JUEGO
    


    
 

/*---------- DESTRUCCIÓN DE PUNTEROS --------------*/
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
    al_destroy_bitmap(powerup.destruido);
    al_destroy_bitmap(controles);
    al_destroy_bitmap(menu);
    al_destroy_bitmap(menu1);
    al_destroy_bitmap(menu2);
    al_destroy_bitmap(menu3);
    al_destroy_timer(limitador_menu);
    al_destroy_bitmap(ganarperder);
    al_destroy_sample(musicafondo);
    al_destroy_sample_instance(musicafondoinstance);
    al_destroy_sample(musicamenu);
    al_destroy_sample_instance(musicamenuinstance);
    al_ustr_free(nombre);
    al_destroy_bitmap(fondoranking);

  
    return 0;
}