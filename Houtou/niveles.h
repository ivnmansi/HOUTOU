#ifndef NIVELES_H
#define NIVELES_H


  #include "config.h"


  void comportamientoenemigos(int *nivel, personaje enemigos[numenemigos], bool espaciado_disparoenemigos, int *inicionivelcontador, int *pasarnivel);
  void poweruptirar(proyectil *powerup, personaje principal, int nivel, bool *inmunidad,bool *powerup_activo, bool *powerup_inmunidad_tomado);
  void iniciarpowerup(proyectil *powerup);
 

#endif  