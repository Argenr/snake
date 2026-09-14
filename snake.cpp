#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;
int main() {
  initscr();
  nodelay(stdscr, TRUE);
  // Var iniciales de movimiento
  int alto = 0, ancho = 0, tecla = 0, longitud = 0, i = 0, puntos = 0,
      velocidad = 200000;
  bool colisionCuerpo = false;
  getmaxyx(stdscr, alto, ancho);
  // cout << alto << " " << ancho << endl;
  int posx[100], posy[100];

  // Toma la posición central y dibuja el @ que es la cabeza
  posx[0] = ancho / 2;
  posy[0] = alto / 2;
  mvaddch(posy[0], posx[0], '@');

  /* Comida */
  srand(time(NULL));
  int poscomidax = 0;
  int poscomiday = 0;
  poscomidax = 1 + rand() % ancho - 2;
  poscomiday = 1 + rand() % alto - 2;

  char direccion = 'd';
  curs_set(0);

  while (true) {
    tecla = getch();
    if (tecla == 'x') {
      break;
    }
    erase();

    /* Bordes */
    for (int j = 0; j < ancho; j++) {
      mvaddch(0, j, '#');
      if (j == 0) {
        for (int k = 0; k < alto; k++) {
          mvaddch(k, 0, '#');
        }
      }
      if (j == ancho - 1) {
        for (int k = 0; k < alto - 1; k++) {
          mvaddch(k, ancho - 1, '#');
        }
      }
    }
    for (int k = 0; k < ancho - 1; k++) {
      mvaddch(alto - 1, k, '#');
    }

    if (tecla == 'w' && direccion != 's') {
      direccion = 'w';
    } else if (tecla == 'a' && direccion != 'd') {
      direccion = 'a';
    } else if (tecla == 's' && direccion != 'w') {
      direccion = 's';
    } else if (tecla == 'd' && direccion != 'a') {
      direccion = 'd';
    }
    /* Dibujo del cuerpo */
    for (i = longitud; i > 0; i--) {
      posx[i] = posx[i - 1];
      posy[i] = posy[i - 1];
    }

    /* Colisión con los bordes */
    if ((posx[0] == 1 && direccion == 'a') ||
        (posx[0] == ancho - 2 && direccion == 'd')) {
      usleep(2000000);
      mvprintw(alto / 2, (ancho - 9) / 2, "GAME OVER");
      mvprintw((alto / 2) + 1, (ancho - 21) / 2, "Obtuviste: %d puntos",
               puntos);
      usleep(1000000);
      flushinp();
      nodelay(stdscr, FALSE);
      getch();
      break;
    }
    if ((posy[0] == 1 && direccion == 'w') ||
        (posy[0] == alto - 2 && direccion == 's')) {
      usleep(2000000);
      mvprintw(alto / 2, (ancho - 9) / 2, "GAME OVER");
      mvprintw((alto / 2) + 1, (ancho - 21) / 2, "Obtuviste: %d puntos",
               puntos);
      usleep(1000000);
      flushinp();
      nodelay(stdscr, FALSE);
      getch();
      break;
    }

    if (direccion == 'w') {
      posy[0]--;
    } else if (direccion == 'a') {
      posx[0]--;
    } else if (direccion == 's') {
      posy[0]++;
    } else if (direccion == 'd') {
      posx[0]++;
    }
    
    /* Colisión con el cuerpo */
    for (int j = 1; j <= longitud; j++) {
      if (posx[0] == posx[j] && posy[0] == posy[j]) {
        colisionCuerpo = true;
      }
    }
    if(colisionCuerpo == true){
      usleep(2000000);
      mvprintw(alto / 2, (ancho - 9) / 2, "GAME OVER");
      mvprintw((alto / 2) + 1, (ancho - 21) / 2, "Obtuviste: %d puntos",
               puntos);
      flushinp();
      nodelay(stdscr, FALSE);
      getch();
      break;
    }

    // Aleatorizar la aparición de comida y sumar puntos, comprobando que se
    // haya comido, además de acelerar
    if (posy[0] == poscomiday && posx[0] == poscomidax) {
      longitud++;
      puntos++;
      velocidad -= 5000;
      if (velocidad < 55000) {
        velocidad = 55000;
      }
      poscomidax = (2 + rand()) % (ancho - 3);
      poscomiday = (2 + rand()) % (alto - 3);
    }

    mvaddch(posy[0], posx[0], '@');
    for (int i = 1; i <= longitud; i++) {
      mvaddch(posy[i], posx[i], '0');
    }
    mvaddch(poscomiday, poscomidax, '*');
    refresh();
    usleep(velocidad);
  }
  endwin();
  if (tecla == 'x') {
    cout << "Obtuviste: " << puntos << " puntos" << endl;
  }
  return 0;
}
