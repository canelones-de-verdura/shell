/*
 * Funciones varias, principalmente auxiliares.
 * Vamos a intentar evitar tirar todo para acá, así
 * el programa no queda como un laberinto de funciones.
 */
#ifndef UTILS_H
#define UTILS_H

/*
 * Auxiliar de shell_setup()
 * Devuelve el directorio del usuario, o NULL si no lo encuentra.
 */
char *get_home();

/*
 * Auxiliar de shell_loop().
 * Devuelve un string que mostramos como promt.
 */
char *get_promt();

/*
 * Auxiliar de shell_loop().
 * Separa la línea leída en tokens para ser procesados.
 */
char **split_line(char *);

#endif
