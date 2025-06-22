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



/*----------
CONSTANTS
-----------*/
#define WINDOW_TITLE "HOUTOU" /* Window title */

#define x_display 550 /*tamaño x de la pantalla*/
#define y_display 900 /*tamaño y de la pantalla*/

/*
VARIABLES
*/
extern bool GameRunning; /* Verify if the window should close */
extern bool key[ALLEGRO_KEY_MAX]; /* Keyboard */
extern bool redraw;
extern bool dibujar;
extern int numenemigospornivel[10];
extern int numenemigos;

extern int animacion_fondo; /*variable con la que se hará la animacion del fondo*/
extern int animacion_fondo_encima;

/*----------------funciones--------------------------------*/
void verificadorteclado(ALLEGRO_EVENT *event, personaje *principal); 


#endif 