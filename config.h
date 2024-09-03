#ifndef CONFIG_H
#define CONFIG_H


#define _USE_MATH_DEFINES
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
 




#include "personajes.h"
#include "niveles.h"




extern bool key[ALLEGRO_KEY_MAX]; /*teclado*/
#define x_display 550 /*tamaño x de la pantalla*/
#define y_display 900 /*tamaño y de la pantalla*/


/*----------------funciones--------------------------------*/
void verificadorteclado(ALLEGRO_EVENT *event, personaje *principal); 








#endif 