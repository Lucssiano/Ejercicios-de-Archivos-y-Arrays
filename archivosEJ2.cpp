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

void armarArchivoDeLibros(FILE *aLibros);
void armarArchivoDeEditoriales(FILE *aEdit);
void armarArchivoDeConsultas(FILE *aConsultas);
void mostrarArchLibros(FILE *aLibros);
void mostrarArchEditoriales(FILE *aLibros);
void mostrarArchConsultas(FILE *aLibros);

int main()
{
  FILE *archLibros, *archEditoriales, *archConsultas;

  // armarArchivoDeLibros(archLibros);
  // armarArchivoDeEditoriales(archEditoriales);
  // armarArchivoDeConsultas(archConsultas);

  mostrarArchLibros(archLibros);
  mostrarArchEditoriales(archEditoriales);
  mostrarArchConsultas(archConsultas);

  return 0;
}

void armarArchivoDeLibros(FILE *aLibros)
{
  aLibros = fopen("Libros.dat", "wb");
  if (aLibros == NULL)
    cout << "ERROR" << endl;
  else
  {
    Libro lib;
    int i = 1;
    while (i <= 10)
    {
      cout << "Codigo del libro: ";
      cin >> lib.codLib;
      cout << "Titulo del libro: ";
      fflush(stdin);
      cin.getline(lib.titLib, 30);
      lib.cant = i + 20;
      strcpy(lib.ubicacion, "4A");
      cout << "Codigo de la editorial (1 a 200): ";
      cin >> lib.codEdit;
      strcpy(lib.autor, "Garcia Marquez");
      fwrite(&lib, sizeof(Libro), 1, aLibros);
      i++;
    }
    fclose(aLibros);
  }
}

void armarArchivoDeEditoriales(FILE *aEdit)
{
  aEdit = fopen("Editoriales.dat", "wb");
  if (aEdit == NULL)
    cout << "ERROR" << endl;
  else
  {
    Editorial edit;
    int i = 1;
    while (i <= 10)
    {
      cout << "Nombre de la editorial: ";
      fflush(stdin);
      cin.getline(edit.nombreEdit, 25);
      cout << "Codigo de la editorial (1 a 200): ";
      cin >> edit.codEdit;
      fwrite(&edit, sizeof(Editorial), 1, aEdit);
      i++;
    }
    fclose(aEdit);
  }
}

void armarArchivoDeConsultas(FILE *aConsultas)
{
  aConsultas = fopen("Consultas.dat", "wb");
  if (aConsultas == NULL)
    cout << "ERROR" << endl;
  else
  {
    Consulta cons;
    int i = 1;
    while (i <= 15)
    {
      cout << "Codigo del libro consultado: ";
      cin >> cons.codLib;
      cout << "Fecha de consulta (aaaammdd): ";
      cin >> cons.fechaCons;
      fwrite(&cons, sizeof(Consulta), 1, aConsultas);
      i++;
    }
    fclose(aConsultas);
  }
}

void mostrarArchLibros(FILE *aLibros)
{
  aLibros = fopen("Libros.dat", "rb");
  if (aLibros == NULL)
    cout << "ERROR" << endl;
  else
  {
    Libro lib;

    fread(&lib, sizeof(Libro), 1, aLibros);
    while (!feof(aLibros))
    {
      cout << endl;
      cout << "Codigo del libro: ";
      cout << lib.codLib;
      cout << "         ";
      cout << "Titulo del libro: ";
      cout << lib.titLib;
      cout << endl;
      cout << "Cantidad de ejemplares: ";
      cout << lib.cant;
      cout << "         ";
      cout << "Ubicacion: ";
      cout << lib.ubicacion;
      cout << endl;
      cout << "Codigo de la editorial: ";
      cout << lib.codEdit;
      cout << "         ";
      cout << "Autor: ";
      cout << lib.autor;
      cout << endl;
      fread(&lib, sizeof(Libro), 1, aLibros);
    }
  }
  fclose(aLibros);
}

void mostrarArchEditoriales(FILE *aEdit)
{
  aEdit = fopen("Editoriales.dat", "rb");
  if (aEdit == NULL)
    cout << "ERROR" << endl;
  else
  {
    Editorial edit;

    fread(&edit, sizeof(Editorial), 1, aEdit);
    cout << endl;
    cout << "---------------------------------";
    cout << endl;
    while (!feof(aEdit))
    {
      cout << endl;
      cout << "Nombre de la editorial: ";
      cout << edit.nombreEdit;
      cout << "         ";
      cout << "Codigo de la editorial: ";
      cout << edit.codEdit;
      cout << endl;
      fread(&edit, sizeof(Editorial), 1, aEdit);
    }
    fclose(aEdit);
  }
}

void mostrarArchConsultas(FILE *aConsultas)
{
  aConsultas = fopen("Consultas.dat", "rb");
  if (aConsultas == NULL)
    cout << "ERROR" << endl;
  else
  {
    Consulta cons;

    fread(&cons, sizeof(Consulta), 1, aConsultas);
    cout << endl;
    cout << "---------------------------------";
    cout << endl;
    while (!feof(aConsultas))
    {
      cout << endl;
      cout << "Codigo del libro consultado: ";
      cout << cons.codLib;
      cout << "         ";
      cout << "Fecha de consulta: ";
      cout << cons.fechaCons;
      cout << endl;
      fread(&cons, sizeof(Consulta), 1, aConsultas);
    }
    fclose(aConsultas);
  }
}
