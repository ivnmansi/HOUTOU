// personajes.h
#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
 
#define maxproyectiles 40
#define numenemigos1 5
#define numenemigos2 2
#define numenemigos3 3
#define numenemigos4 1

#define numenemigos (numenemigos1+numenemigos2+numenemigos3+numenemigos4)


#define n 9 //prueba disparo circular

/*DEFINICION DE ESTRUCTURAS--------------*/
// > HITBOX
typedef struct {
    float x, y, ancho, alto;
    float arreglo_x, arreglo_y; /*para centrar la hitbox*/
} hitbox;

// > PROYECTILES
typedef struct {
    float x, y; /*posición x,y*/
    bool activo; /*si el proyectil se encuentra activo o no*/
    hitbox hitbox; /*hitbox*/
    double aceleracion;
    double aceleracion_angular;
    ALLEGRO_BITMAP* imagen;
    ALLEGRO_BITMAP* destruido;
} proyectil;

// > PERSONAJES
typedef struct {
    int tipoenemigo;
    float x, y; /*posición x,y*/
    float velocidad; /*velocidad de movimiento*/
    double velocidad_angular; /*velocidad angular de movimiento*/
    ALLEGRO_BITMAP* imagen; /*imagen que se mostrará*/
    ALLEGRO_BITMAP* estatico; /*imagen estática*/
    ALLEGRO_BITMAP* izquierda; /*imagen al moverse a la izquierda*/
    ALLEGRO_BITMAP* derecha; /*imagen al moverse a la derecha*/
    proyectil proyectiles[maxproyectiles]; /*proyectiles*/
    proyectil especial[maxproyectiles]; /*ataque especial*/
    int velocidad_proyectiles; /*velocidad de movimiento de los proyectiles*/
    double espaciado_proyectiles; /*cantidad de proyectiles por segundo*/
    ALLEGRO_BITMAP* imagen_proyectil; /*imagen de su proyectil*/
    hitbox hitbox; /*hitbox*/
    int vida; /*vida*/
    bool activo;
    int choqueborde;
} personaje;
/*--------------------------------------------------------------------*/



/*------------FUNCIONES-----------------------------------------------*/
//   > personaje principal:

     void iniciarjugador(personaje *principal); /*para inicializar el jugador*/
     void movimiento_principal(float *velocidad_principal_real, personaje *principal); /*movimiento del jugador*/
     void disparar_principal(ALLEGRO_EVENT *event, ALLEGRO_TIMER **timer_proyectil_principal, bool *espacio_disparos, personaje *principal); /*ataque jugador*/
     void inmunidadporproyectil(personaje *principal, personaje enemigo[numenemigos], bool *inmunidad);
     void inmunidadporenemigo(personaje *principal,personaje enemigo1[numenemigos], bool *inmunidad);
     void inmunidadactiva(ALLEGRO_EVENT *event, ALLEGRO_TIMER *timer_segundos, int *contadorinmunidad, bool *inmunidad,bool *powerup_inmunidad_tomado);
     void ataque_especial(ALLEGRO_EVENT *event, ALLEGRO_TIMER **timer_segundos, int *contadorespecial, int *contadorduracionespecial, bool *especialactivo, char *elcontadordelataque, personaje *principal, int *auxespecial_x); /*ataque especial*/

//   > generales:
     void movimiento_hitbox(personaje *personaje); /*movimiento hitbox personaje*/
     void movimiento_hitbox_proyectiles(personaje *personaje); /*movimiento hitbox proyectiles*/
     bool colisionproyectiles(personaje *personaje1 ,personaje *enemigo); /*verificador de colisiones entre personaje-proyectil*/
     bool colisionpersonajes(personaje *personaje1 ,personaje *enemigo); /*verificador de colisiones personaje-personaje*/
     bool colisionataqueespecial(personaje *personaje1, personaje *enemigo);
     
    
//   > enemigos:
       void leerenemigos(personaje enemigos[numenemigos]);
       void iniciarenemigos(personaje enemigos[numenemigos]);


/*------DEPURACION-----------*/
//     > dibujar hitboxs
       void dibujohitboxs(personaje principal, personaje enemigos1[numenemigos],proyectil powerup);

#endif // PERSONAJES_H