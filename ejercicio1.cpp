/* 1) Dado el archivo “ALUMNOS.dat” con los datos personales de alumnos ordenado por legajo, con el siguiente
diseño:
a.1 Legajo                          a.2 Apellido y nombre ( 30 caracteres)
a.3 Domicilio (20 caracteres)       a.4 Código postal
a.5 Teléfono (10 caracteres)         a.6 Año de ingreso

Y otro archivo sin orden llamado “NOVEDADES.dat”, con cantidad máxima de registros es 100. Posee las
actualizaciones (altas, bajas, y modificaciones) a ser aplicadas, donde cada registro contiene además de todos los
campos de Alumnos.dat un código de operación (‘A’= Alta, ‘B’= Baja, ‘M’= Modificación).

Se pide desarrollar todos los pasos necesarios para realizar un programa que genere un archivo actualizado
“ALUMACTU.dat” con el mismo diseño.  */

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void generarArchivoAlumnos();

struct DatosAlumnos
{
  char nombreYApellido[30], domicilio[20], telefono[10];
  int leg, codPostal, añoDeIngreso;
};

int main()
{
  generarArchivoAlumnos();
  return 0;
}

void generarArchivoAlumnos()
{
  FILE *archAlumnos;
  archAlumnos = fopen("“ALUMNOS.dat", "wb");
  if (archAlumnos == NULL)
    cout << "ERROR" << endl;
  else
  {
    DatosAlumnos alumno;
    int i = 1;
    while (i <= 20)
    {
      alumno.leg = i;
      alumno.añoDeIngreso = 200 + i;
      strcat(alumno.domicilio, "Jarana 222" + i);
      alumno.codPostal = 99 + i;
      strcat(alumno.nombreYApellido, "Lucho Riente " + i);
      strcat(alumno.telefono, "234643234" + i);
      fwrite(&alumno, sizeof(DatosAlumnos), 1, archAlumnos);
      i++;
    }
    fclose(archAlumnos);
  }