#include "config.h"

/* VARIABLES */
bool GameRunning=true; /* Verify if the window should close */
bool key[ALLEGRO_KEY_MAX] = { false };
bool dibujar = false;
bool redraw;
int numenemigospornivel[10] = {0};
int numenemigos = 0;

int animacion_fondo=0; /*variable con la que se hará la animacion del fondo*/
int animacion_fondo_encima=0;