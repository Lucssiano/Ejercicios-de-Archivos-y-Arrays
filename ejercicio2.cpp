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
#include <stdio.h>
#include <string.h>

using namespace std;

struct Libro
{
  int codLib, cant, codEdit;
  char titLib[30], ubicacion[3], autor[25];
};

struct Editorial
{
  int codEdit;
  char nombreEdit[25];
};

struct Consulta
{
  int codLib, fechaCons;
};

struct LibrosXEditorial
{
  int cantLibrosConsultados = 0;
  char nombreEdit[25];
};

void inicializarVec(int v[], int tam);
void inicializarVecDeStructs(LibrosXEditorial vecLibXEdit[], int tam);
void inicializarMatriz(int mT[25][6]);
void armarVectorYLlenarMatriz(int mT[25][6], int v[], FILE *aCons, int &cantLibDist);
int secuencial(int v[], unsigned t, int bus);
void burbujeo(LibrosXEditorial vecLibXEdit[], unsigned t);
void mostrarTitulos();
bool tieneMasDe20ConsultasXSemestre(int mT[25][6], int posLib, int &cantCons);
void nombreEditorial(int codEdit, FILE *aEdit, LibrosXEditorial vecLibXEdit[]);
void punto1(FILE *aLib, FILE *aEdit, FILE *aCons, LibrosXEditorial vecLibXEdit[]);
void punto2(FILE *aEdit, FILE *aLibxEdit, LibrosXEditorial vecLibXEdit[]);
void mostrarArchLibXEdit(FILE *aLibxEdit);

int main()
{
  FILE *archLxEditorial, *archLibros, *archEditoriales, *archConsultas;

  archLibros = fopen("Libros.dat", "rb");
  archEditoriales = fopen("Editoriales.dat", "rb");
  archConsultas = fopen("Consultas.dat", "rb");
  archLxEditorial = fopen("LibrosPorEditorial.dat", "wb");

  LibrosXEditorial vecEditoriales[200];

  punto1(archLibros, archEditoriales, archConsultas, vecEditoriales);
  punto2(archEditoriales, archLxEditorial, vecEditoriales);

  fclose(archLibros);
  fclose(archEditoriales);
  fclose(archConsultas);
  fclose(archLxEditorial);

  mostrarArchLibXEdit(archLxEditorial);
}

void punto1(FILE *aLib, FILE *aEdit, FILE *aCons, LibrosXEditorial vecLibXEdit[])
{
  if (aLib == NULL || aEdit == NULL || aCons == NULL)
    cout << "ERROR" << endl;
  else
  {
    Libro lib;
    Consulta cons;

    int matConsultas[25][6], codLib[25], cantLibrosDistintos, cantConsultas;

    inicializarMatriz(matConsultas);
    inicializarVec(codLib, 25);
    inicializarVecDeStructs(vecLibXEdit, 200);
    armarVectorYLlenarMatriz(matConsultas, codLib, aCons, cantLibrosDistintos);
    mostrarTitulos();

    fread(&lib, sizeof(Libro), 1, aLib);
    while (!feof(aLib))
    {
      int posLibCons = secuencial(codLib, cantLibrosDistintos, lib.codLib);
      if (tieneMasDe20ConsultasXSemestre(matConsultas, posLibCons, cantConsultas))
      {
        cout << lib.codLib << "           ";
        cout << lib.titLib << "           ";
        cout << lib.autor << "           ";
        nombreEditorial(lib.codEdit, aEdit, vecLibXEdit);
        cout << cantConsultas << "           ";
        cout << endl;
      }
      fread(&lib, sizeof(Libro), 1, aLib);
    }
  }
}

void armarVectorYLlenarMatriz(int mT[25][6], int v[], FILE *aCons, int &cantLibDist)
{
  Consulta cons;
  int i = 0;

  fread(&cons, sizeof(Consulta), 1, aCons);
  while (!feof(aCons))
  {
    int mes = (cons.fechaCons - ((cons.fechaCons / 10000) * 10000)) / 100;
    int posLibCons = secuencial(v, i, cons.codLib); // La i puede ser 25
    if (posLibCons == -1)
    {
      v[i] = cons.codLib;
      mT[i][mes - 1]++;
      i++;
    }
    else
      mT[posLibCons][mes - 1]++;
    fread(&cons, sizeof(Consulta), 1, aCons);
  }

  cantLibDist = i;
}

bool tieneMasDe20ConsultasXSemestre(int mT[25][6], int posLib, int &cantCons)
{
  int cantConsultas = 0;
  bool condicion = false;

  for (int c = 0; c < 6; c++)
    cantConsultas += mT[posLib][c];

  if (cantConsultas >= 12)
  {
    condicion = true;
    cantCons = cantConsultas;
  }

  return condicion;
}

void nombreEditorial(int codEdit, FILE *aEdit, LibrosXEditorial vecLibXEdit[])
{
  char nombreEditorial[25];
  Editorial edit;
  int i = 0;

  fread(&edit, sizeof(Editorial), 1, aEdit);
  while (!feof(aEdit))
  {
    if (codEdit == edit.codEdit)
    {
      strcpy(nombreEditorial, edit.nombreEdit);
      vecLibXEdit[i].cantLibrosConsultados++;
      fseek(aEdit, 0, SEEK_END);
    }
    else
      fread(&edit, sizeof(Editorial), 1, aEdit);
    i++;
  }

  cout << nombreEditorial << "          ";
}

void punto2(FILE *aEdit, FILE *aLibxEdit, LibrosXEditorial vecLibXEdit[])
{
  if (aLibxEdit == NULL || aEdit == NULL)
    cout << "ERROR" << endl;
  else
  {
    Editorial edit;
    LibrosXEditorial libXEdit;
    int i = 0;

    fseek(aEdit, 0, SEEK_SET);
    fread(&edit, sizeof(Editorial), 1, aEdit);
    while (!feof(aEdit))
    {
      strcpy(vecLibXEdit[i].nombreEdit, edit.nombreEdit);
      fread(&edit, sizeof(Editorial), 1, aEdit);
      i++;
    }
    burbujeo(vecLibXEdit, 200);
    fwrite(&libXEdit, sizeof(LibrosXEditorial), 200, aLibxEdit);
  }
}

void mostrarTitulos()
{
  cout << "Codigo del Libro       "
       << "Titulo       "
       << "Autor       "
       << "Editorial       "
       << "Consultas en el Semestre      " << endl;
}

void inicializarMatriz(int mT[25][6])
{
  for (int f = 0; f < 25; f++)
    for (int c = 0; c < 6; c++)
      mT[f][c] = 0;

  for (int f = 0; f < 25; f++)
  {
    for (int c = 0; c < 6; c++)
    {
      cout << mT[f][c] << "   ";
    }
    cout << endl;
  }
}

void inicializarVec(int v[], int tam)
{
  for (int f = 0; f < tam; f++)
    v[f] = 0;
}

void inicializarVecDeStructs(LibrosXEditorial vecLibXEdit[], int tam)
{
  for (int f = 0; f < tam; f++)
  {
    vecLibXEdit[f].cantLibrosConsultados = 0;
    strcpy(vecLibXEdit[f].nombreEdit, "");
  }
}

int secuencial(int v[], unsigned t, int bus)
{
  unsigned i = 0;
  while (i < t && v[i] != bus)
    i++;
  if (i == t)
    return -1;
  else
    return i;
}

void burbujeo(LibrosXEditorial vecLibXEdit[], unsigned t)
{
  unsigned i = 0, j; // la profe le puso i = 0 , en el burbujeo original dice con 1;
  LibrosXEditorial aux;
  bool cambio;
  do
  {
    cambio = false;
    for (j = 0; j < t - i; j++)
    {
      if (vecLibXEdit[j].cantLibrosConsultados > vecLibXEdit[j + 1].cantLibrosConsultados)
      {
        aux = vecLibXEdit[j];
        vecLibXEdit[j] = vecLibXEdit[j + 1];
        vecLibXEdit[j + 1] = aux;
        cambio = true;
      }
    }
    i++;
  } while (i < t && cambio);
}

void mostrarArchLibXEdit(FILE *aLibxEdit)
{
  aLibxEdit = fopen("Editoriales.dat", "rb");
  if (aLibxEdit == NULL)
    cout << "ERROR" << endl;
  else
  {
    LibrosXEditorial libXEdit;

    fread(&libXEdit, sizeof(LibrosXEditorial), 1, aLibxEdit);
    while (!feof(aLibxEdit))
    {
      cout << "ARCHIVO LIBROS X EDITORIAL";
      cout << endl;
      cout << "Nombre de la editorial:        ";
      cout << libXEdit.nombreEdit;
      cout << "Cantidad de libros consultados:        ";
      cout << libXEdit.cantLibrosConsultados;
      cout << endl;
      fread(&libXEdit, sizeof(LibrosXEditorial), 1, aLibxEdit);
    }
    fclose(aLibxEdit);
  }
}
