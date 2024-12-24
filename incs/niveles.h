#ifndef NIVELES_H
#define NIVELES_H

  #include "config.h"

  typedef struct{
   char nombre[20];
   int puntaje;
  } ranking;

   void dispararleproyectiles(personaje *personaje1 ,personaje *enemigo, int *puntuacion);
  void comportamientoenemigos(int numenemigos, int *nivel, personaje enemigos[numenemigos], bool espaciado_disparoenemigos, int *inicionivelcontador, int *pasarnivel, personaje principal, int *puntuacion, bool *se_gano, int segundos);
  void poweruptirar(proyectil *powerup, personaje *principal, int nivel, bool *inmunidad,bool *powerup_activo, bool *powerup_inmunidad_tomado, bool *ataquetripleactivo);
  void iniciarpowerup(proyectil *powerup);
  void iniciarvariables(int *animacion_fondo,int *animacion_fondo_encima, int *opcion_menu, int *segundos, int *inicionivelcontador, int *pasarnivel, int *puntuacion, float *puntuacionfinal, bool *inmunidad, int *contadorinmunidad, bool *ataquetripleactivo, int *contadortriple, int *contadorespecial, int *contadorduracionespecial, bool *especialactivo, bool *espacio_disparos);
 
  void leerranking(ranking ranking1[10]);
  void ordenar_ranking(ranking ranking1[10]);

#endif  