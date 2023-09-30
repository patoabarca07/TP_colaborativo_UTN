#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

// Colocar las Librerías que se utilizarán

#include "Structs.h"



/// --------------------------- PROTOTIPOS DE LAS FUNCIONES ---------------------------
// 1) --------------------------------------------------------------
bool existeRegistro(char *codigo);  // Verifico si existe Registro.

// 2) --------------------------------------------------------------
void cargarPais();          // Cargo un registro de Struct.
void grabarPais(Pais pais);  // Grabo en Archivo.

// 3) --------------------------------------------------------------
void leerPaises();          // Leo el Archivo.
void mostrarPais(Pais pais); // Recibo el Registro leido del archivo y lo muestro. Registro x Registro, sin uso de Vectores.

// 4) --------------------------------------------------------------
void mostrarCiudadesxPais();                  // Leo el archivo Ciudades. Dentro de la función se debe pedir al
                                            //Usuario que ingrese el nombre del Pais.
struct Pais obtenerRegistroPais(char *pais);  // Recibe el nombre del Pais y busca su registro.
                                              // Revisar la opción de pedir primero el ingreso para obtener el Registro
                                              //y luego leer el archivo Ciudades.

// 5) --------------------------------------------------------------
void listarPaises_Superficies();    // Leer y guardar los Registros en un Vector.
                                    // Calcular el Total de Superficie Mundial.
                                    // Mostrar dentro de la función misma,
                                    //NOMBRE - SUPERFICIE - PORCENTAJE %

// 6) --------------------------------------------------------------
void totalesxContinente();          // Leo el archivo Paises. Dentro de la función se debe pedir al Usuario que ingrese el nombre del Pais.
                                    // Guardo en un vector los registros.
                                    // Calculo los totales y promedios. Muestro.

// 7) --------------------------------------------------------------
void modificarPais();               // Pido el codigo de pais a modificar.
                                    // Verificar que exista.
                                    // Buscar registro (usar función respectiva).
                                    // Ingresar los nuevos valores y reemplazar.
void grabarModificado(Pais reg);    // Guardar Pais Modificado.


// 8) --------------------------------------------------------------
void modificarCiudad();             // Pido el codigo de la ciudad a modificar.
bool existeRegistro(int id);        // Verifico si existe Registro. (SOBRECARGA DE FUNCIONES)
                                    // Ingreso codigo pais y verifico si existe
void grabarModificado(Ciudad reg);  // Guardar Ciudad Modificada. (SOBRECARGA DE FUNCIONES)

// 9) --------------------------------------------------------------
void totalesPais_Poblacion();

// 10) --------------------------------------------------------------
void buscarMayorPoblacion();

    /// ADICIONALES IMPORTANTES
int contarPaises();     // Contar Registros Archivo Paises
int contarCiudades();   // Contar Registros Archivo Ciudades

/// PUNTOS 11 y 12 (OPCIONALES)
/// COLOCAR AQUÍ LOS PROTOTIPOS DE LAS FUNCIONES

//11)------------------------------------------------------------------
void realizarBackUp();

void restaurarArchivos();



//12)------------------------------------------------------------------
void exportarExcel();



#endif // FUNCIONES_H_INCLUDED
