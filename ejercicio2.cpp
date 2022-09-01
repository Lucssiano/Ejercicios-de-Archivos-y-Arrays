/* 2) Una biblioteca maneja la siguiente información:
a) un archivo de libros “Libros.dat”, ordenado por código de libro y con el siguiente diseño:
a.1 Código del libro                  a.2 título del libro (30 caract)
a.3 cantidad de ejemplares            a.4 ubicación (3 caract)
a.5 código de la editorial (1..200)   a.6 autor (25 caract)
b) un archivo de editoriales “Editoriales.dat” ordenado alfabéticamente por nombre de la editorial, con el
siguiente diseño.
b.1 nombre de la editorial (25 caracteres)    b.2 código de la editorial (1..200)
c) un archivo, ”Consultas.dat”, de consultas realizadas durante el primer semestre del año. Los diferentes libros
consultados no superan los 1000, y el diseño del registro es el siguiente:
c.1 código del libro    c.2 fecha de consulta (aaaammdd)

Se pide realizar la metodología necesaria para obtener un programa que:
1) Emita un listado con los libros que tuvieron como mínimo 20 consultas en cada mes del semestre, con el
siguiente diseño, ordenado por código:

Código del Libro       Título          Autor         Editorial        Consultas en el Semestre
                                                                       1   2   3   4   5   6
    999999            xxxxxxxxx      xxxxxxxxx       xxxxxxxxx        999 999 999 999 999 999
    999999            xxxxxxxxx      xxxxxxxxx       xxxxxxxxx        999 999 999 999 999 999

2) Grabe un archivo ordenado de mayor a menor por cantidad de libros consultados por editorial, con el siguiente
diseño:
2.1 nombre de la editorial (25 caracteres)
2.2 cantidad de libros que fueron consultados en el semestre  */

#include <iostream>

using namespace std;

int main()
{
  punto1();
  punto2();
  return 0;
}