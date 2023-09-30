#include <iostream>
#include <cstdio>
#include <string.h>
#include <iomanip>
#include <libxl.h>
#include "Funciones.h"


/// ARCHIVOS
const char *ARCHIVO_PAISES = "paises.dat";
const char *ARCHIVO_CIUDADES = "ciudades.dat";


/// --------------------------- DESARROLLO DE LAS FUNCIONES ---------------------------
using namespace std;
using namespace libxl;

///PUNTO 1
bool existeRegistro(char *codigo)
{
    Pais pais;

    FILE *pArchivo;
    pArchivo=fopen(ARCHIVO_PAISES,"rb");//abre el archivo en el bite 0 y no permite escribir.

    if(pArchivo==NULL)
    {
        cout << "Error al abrir el archivo" << endl;
        system("pause");
        exit(1);
    }

    while(fread(&pais,sizeof(Pais),1,pArchivo)==1)
    {
        if(strcmp(pais._codigo,codigo)==0)
        {
            fclose(pArchivo);
            return true;
        }

    }
    fclose(pArchivo);
    return false;
}


///-------------------------------------------------
///PUNTO 2


void cargarPais()
{
    Pais pais;

    cout<<"Ingrese el codigo de Pais: ";
    cin.ignore();
    cin.getline(pais._codigo,4);
    cout<<"Ingrese el codigo de Pais Normas ISO: ";
    cin.getline(pais._codigo2,3);
    cout<<"Ingrese el nombre del pais: ";
    cin.getline(pais._nombre,45);
    cout<<"Ingrese el continente: ";
    cin.getline(pais._continente,20);
    cout<<"Ingrese superficie del pais: ";
    cin>>pais._superficie;
    cout<<"Ingrese poblacion: ";
    cin>>pais._poblacion;
    cout<<"Ingrese año de independencia: ";
    cin>>pais._independencia;
    cout<<"Ingrese expectativa de vida: ";
    cin>>pais._expectativaDeVida;
    cout<<"Ingrese ID Capital: ";
    cin>>pais._capital;

    grabarPais(pais);
}

void grabarPais(Pais pais)
{

    FILE* pArchivo;
    pArchivo = fopen(ARCHIVO_PAISES, "ab");//abre el archivo desde el final como escritura //no admite modificar lo existente solo agregar
    if (pArchivo==NULL)
    {
        cout << "Error al crear el archivo" << endl;
        system("pause");
        return;
    }

    fwrite(&pais, sizeof(Pais), 1, pArchivo);
    cout<<"Pais agregado con exito. ";
    cout<<endl;
    fclose(pArchivo);
    system("pause");
}


///-------------------------------------------------
///PUNTO 3


void leerPaises()
{

    Pais pais;
    FILE *pArchivo;
    pArchivo=fopen(ARCHIVO_PAISES,"rb");
    if(pArchivo==NULL)
    {
        cout << "Error al abrir el archivo" << endl;
        system("pause");
        return;
    }
    cout<<"........................................................................................................................................................."<<endl;
    cout<<setw(43)<<left<<"Pais"<<setw(12)<<"| Codigo"<<setw(18)<<"|Continente "<<setw(20)<<" | Superficie |"<<setw(14)<<"Poblacion "<<setw(9)<<"| Indep |"<<setw(8)<<"E.Vida|"<<endl;
    cout<<"........................................................................................................................................................."<<endl;
    while(fread(&pais, sizeof(Pais), 1, pArchivo)==1)
    {
        mostrarPais(pais);
    }
    system("pause");
    fclose(pArchivo);

}

void mostrarPais(Pais pais)
{

    cout<<setw(45)<<left<<pais._nombre<<setw(10)<<pais._codigo2<<setw(20)<<pais._continente<<right<<setw(12)<<fixed<<setprecision(2)<<pais._superficie<<setw(15)<<pais._poblacion<<setw(12)<<pais._independencia<<setw(8)<<fixed<<setprecision(2)<<pais._expectativaDeVida<<endl;

}

///----------------------------------------------------
///PUNTO 4

void mostrarCiudadesxPais()
{

    FILE *pCiudades;
    pCiudades = fopen(ARCHIVO_CIUDADES, "rb");

    Ciudad ciudad;

    if (pCiudades==NULL)
    {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    char codigoPais[4];
    cout<<"Ingrese codigo de Pais: ";
    cin.ignore();
    cin.getline(codigoPais,4 );

    Pais pais= obtenerRegistroPais(codigoPais);

    if(strcmp(pais._codigo,"0")!=0)
    {
        cout<<"*******************************************************"<<endl;
        cout<<"Ciudad \t\t\t\t\t Poblacion"<<endl;
        cout<<"*******************************************************"<<endl;
        while (fread(&ciudad, sizeof(Ciudad), 1, pCiudades)==1)
        {
            if (strcmp(ciudad._idpais,pais._codigo) == 0)
            {
                cout <<setw(30)<<left<<ciudad._nombre << "      \t\t" << ciudad._poblacion << endl;
            }
        }

        rewind(pCiudades);

        while (fread(&ciudad, sizeof(Ciudad), 1, pCiudades)==1)
            if(pais._capital==ciudad._ID)
            {
                cout<<"*******************************************************"<<endl;
                cout << "Capital del pais: " << ciudad._nombre << endl;
                cout<<"*******************************************************"<<endl;
            }
    }


    fclose(pCiudades);


    system("pause");
}

Pais obtenerRegistroPais (char *codigoPais)
{


    FILE* pArchivo;
    pArchivo = fopen(ARCHIVO_PAISES, "rb");
    Pais pais;

    if (pArchivo==NULL)
    {
        cout << "Error al abrir el archivo" << endl;


        strcpy(pais._codigo,"0");
        return pais;
    }

    while (fread(&pais, sizeof(Pais), 1, pArchivo)==1)
    {
        if (strcmp(pais._codigo, codigoPais) == 0)
        {
            fclose(pArchivo);
            return pais;
        }
    }

    fclose(pArchivo);
    cout << "No se encontro el pais" << endl;
    strcpy(pais._codigo,"0");
    return pais;


}


///-----------------------------
///PUNTO 5



void listarPaises_Superficies()
{
    int cantPaises;

    cantPaises= contarPaises();

    FILE* pArchivo;
    pArchivo = fopen(ARCHIVO_PAISES, "rb");

    if (pArchivo==NULL)
    {
        cout << "Error al abrir el archivo"<<endl;
        return;
    }

    Pais pais;
    float superficieTotal = 0;

    while (fread(&pais, sizeof(Pais), 1, pArchivo))
    {
        superficieTotal += pais._superficie;

    }

    // memoria dinámica, creamos un puntero  a un  vector del tamaño de la cantidad de países.
    Pais* paises = new Pais[cantPaises];


    rewind(pArchivo);
    for (int i = 0; i < cantPaises; i++)
    {
        fread(&pais, sizeof(Pais), 1, pArchivo);
        paises[i] = pais;
    }

    float porcentaje;

    cout<<" Pais \t\t\t\t\t  Superficie en km2 \t Porc del Total Mundial"<<endl;
    for (int i = 0; i < cantPaises; i++)
    {

        porcentaje = (paises[i]._superficie / superficieTotal) * 100;

        cout<<setw(45)<<left<< paises[i]._nombre<<setw(20)<<right<<fixed<<setprecision(2)<< paises[i]._superficie<<setw(20)<<fixed<<setprecision(6)<< porcentaje <<" %"<< endl;
    }

    delete[] paises;   //liberar memoria dinámica
    fclose(pArchivo);
    system("pause");

}

int contarPaises()
{
    FILE *pArchivo;
    pArchivo=fopen(ARCHIVO_PAISES,"rb");
    if(pArchivo==NULL)
    {
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);    //archivo, deplazamiento,origen.SEEK END 0 BYTES DESDE EL FINAL DEL ARCH
    int t = ftell(pArchivo);         //nro de bytes desde el inicio del archivo hasta la posicion actual
    int cr = t / sizeof(Pais);       // cr divido el tamaño total sobre el tamaño de un solo registro
    fclose(pArchivo);
    return cr;
}


///------------------------------------------
///PUNTO 6

void totalesxContinente()
{
    int cantPaises=contarPaises();

    FILE* pArchivo;
    pArchivo = fopen(ARCHIVO_PAISES, "rb");

    if (pArchivo==NULL)
    {
        cout << "Error al abrir el archivo"<<endl;
        return;
    }


    Pais pais;
    Pais *paises = new Pais[cantPaises];

    for (int i = 0; i < cantPaises; i++)
    {
        fread(&pais, sizeof(Pais), 1, pArchivo);
        paises[i] = pais;
    }

    char nombrePais[45];
    cout<<"Ingrese el nombre del pais: "<<endl;
    cin.ignore();
    cin.getline(nombrePais,45);

    bool existe=false;
    char continente[20];
    for (int i = 0; i < cantPaises; i++)
    {
        if(strcmp(paises[i]._nombre,nombrePais)==0)
        {
            strcpy(continente,paises[i]._continente);
            existe=true;
        }

    }
    if (existe==false){
            cout<<"El nombre de pais no existe"<<endl;
            fclose(pArchivo);
            delete[] paises;
            system("pause");
            return;

    }


    long long poblacionTotal=0;
    float superficieTotal=0;
    float densidadPoblacion;
    for (int i = 0; i < cantPaises; i++)
    {

        if(strcmp(paises[i]._continente,continente)==0)
        {

            superficieTotal += paises[i]._superficie;
            poblacionTotal += paises[i]._poblacion;

        }
    }
    densidadPoblacion=poblacionTotal/superficieTotal;

    fclose(pArchivo);
    delete[] paises;
    cout<<"Continente: "<<continente<<endl;
    cout<<"Poblacion:  "<<poblacionTotal<<endl;
    cout<<"Superficie: "<<fixed<<setprecision(2)<<superficieTotal<<endl;
    cout<<"Densidad Poblacional: "<<densidadPoblacion<<endl;
    system("pause");
}

///----------------------------------------------------------------
///PUNTO 7

void modificarPais()
{
    char codigoPais[4];
    cout<<"Ingrese codigo de Pais: ";
    cin.ignore();
    cin.getline(codigoPais,4 );
    bool r=existeRegistro(codigoPais);

    if(r==false)
    {

        cout<<"El codigo de pais no existe en el archivo"<<endl;
        system("pause");

        return;
    }
    Pais pais=obtenerRegistroPais(codigoPais);

    if(strcmp(pais._codigo,"0")!=0)
    {
        cin.ignore();
        cout<<"Ingrese el nombre del pais: ";
        cin.getline(pais._nombre,45);
        cout<<"Ingrese el continente: ";
        cin.getline(pais._continente,20);
        cout<<"Ingrese poblacion: ";
        cin>>pais._poblacion;
        cout<<"Ingrese ID Capital: ";
        cin>>pais._capital;
        grabarModificado(pais);
    }


}


void grabarModificado(Pais pais)
{
    FILE* pArchivo;
    pArchivo = fopen(ARCHIVO_PAISES, "rb+");


    if (pArchivo==NULL)
    {

        cout<<"Error al abrir el archivo"<<endl;
        return;
    }
    Pais pais2;
    while (fread(&pais2, sizeof(Pais), 1, pArchivo)==1)
    {
        if (strcmp(pais2._codigo, pais._codigo) == 0)
        {

            fseek(pArchivo, -sizeof(Pais), SEEK_CUR);
            fwrite(&pais, sizeof(Pais), 1, pArchivo);
            fclose(pArchivo);
            cout << "Pais Modificado con exito" << endl;
        }

    }

    system("pause");

}



///--------------------------------------------------------------
///PUNTO 8

void modificarCiudad()
{
    // Pido el codigo de la ciudad a modificar.
    int id;
    cout<<"Ingrese codigo de ciudad a modificar: "<<endl;
    cin>>id;

    int e=existeRegistro(id);// Verifico si existe Registro. (SOBRECARGA DE FUNCIONES)

    if(e==false)
    {

        cout<<"El codigo de ciudad ingresado no existe "<<endl;
        return;
    }

    char codigoPais[4];                    // Ingreso codigo pais y verifico si existe
    cout<<"Ingrese nuevo codigo de Pais: ";
    cin.ignore();
    cin.getline(codigoPais,4 );
    bool r=existeRegistro(codigoPais);
    if(r==false)
    {

        cout<<"El codigo de pais no existe en el archivo"<<endl;
        system("pause");

        return;
    }

    FILE* pArchivo;
    pArchivo = fopen(ARCHIVO_CIUDADES, "rb+");

    if (pArchivo==NULL)
    {

        cout<<"Error al abrir el archivo"<<endl;
        return;
    }
    Ciudad ciudad;

    while(fread(&ciudad,sizeof(Ciudad),1,pArchivo))
    {
        if(id==ciudad._ID)
        {
            strcpy(ciudad._idpais,codigoPais);
            fclose(pArchivo);
            grabarModificado(ciudad);
        }
    }
}

bool existeRegistro(int id)
{
    Ciudad ciudad;

    FILE *pArchivo;
    pArchivo=fopen(ARCHIVO_CIUDADES,"rb");//

    if(pArchivo==NULL)
    {
        cout << "Error al abrir el archivo" << endl;
        system("pause");
        exit(1);
    }

    while(fread(&ciudad,sizeof(Ciudad),1,pArchivo))
    {
        if(id==ciudad._ID)
        {
            return true;
        }

    }
    return false;

}
void grabarModificado(Ciudad ciudad)
{
    FILE* pArchivo;
    pArchivo = fopen(ARCHIVO_CIUDADES, "rb+");
    Ciudad ciudad2;

    if (pArchivo==NULL)
    {

        cout<<"Error al abrir el archivo"<<endl;
        return;
    }

    while (fread(&ciudad2, sizeof(Ciudad), 1, pArchivo)==1)
    {
        if (strcmp(ciudad2._idpais, ciudad._idpais) == 0)
        {

            fseek(pArchivo, -sizeof(Ciudad), SEEK_CUR);
            fwrite(&ciudad, sizeof(Ciudad), 1, pArchivo);
            fclose(pArchivo);
            cout << "Ciudad modificada con exito" << endl;

        }
    }


    system("pause");

}


///--------------------------------------------------------------
///PUNTO 9
void totalesPais_Poblacion()
{

    int cantPaises;
    cantPaises= contarPaises();

    FILE* pArchivo;
    pArchivo = fopen(ARCHIVO_PAISES, "rb");

    if (pArchivo==NULL)
    {

        cout<<"Error al abrir el archivo"<<endl;
        return;
    }

    Pais pais;
    Pais *paises = new Pais[cantPaises];

    for (int i = 0; i < cantPaises; i++)
    {
        fread(&pais, sizeof(Pais), 1, pArchivo);
        paises[i] = pais;
    }


    int poblacionAcumulada=0;
    for (int i = 0; i < cantPaises; i++)
    {
        poblacionAcumulada+=paises[i]._poblacion;
    }
    cout<<"La cantidad de paises existentes es: "<<cantPaises<<"  y el total de la poblacion mundial es: "<<poblacionAcumulada<<" habitantes"<<endl;

    delete[] paises;
    fclose(pArchivo);

    system("pause");

}

///----------------------------------------------------------
///PUNTO 10

int contarCiudades()
{

    FILE *pArchivo;
    pArchivo=fopen(ARCHIVO_CIUDADES,"rb");
    if(pArchivo==NULL)
    {
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);    //archivo, deplazamiento,origen.SEEK END 0 BYTES DESDE EL FINAL DEL ARCH
    int t = ftell(pArchivo);         //nro de bytes desde el inicio del archivohasta la posicion actual
    int cr = t / sizeof(Ciudad);       // cr divido el tamaño total sobre el tamaño de un solo registro
    fclose(pArchivo);
    return cr;


}

void buscarMayorPoblacion()
{
    int cantCiudades;
    cantCiudades=contarCiudades();

    FILE *pArchivo;
    pArchivo=fopen(ARCHIVO_CIUDADES,"rb");
    if(pArchivo==NULL)
    {
        cout<<"Error al abrir el archivo"<<endl;
        return;
    }
    Ciudad ciudad;
    Ciudad *ciudades = new Ciudad[cantCiudades];

    for (int i=0; i<cantCiudades; i++)
    {

        fread(&ciudad,sizeof(Ciudad),1,pArchivo);
        ciudades[i]=ciudad;

    }

    int mayorpoblacion=0, mayorciudad;

    for (int i=0; i<cantCiudades; i++)
    {

        if (ciudades[i]._poblacion>mayorpoblacion)
        {

            mayorpoblacion=ciudades[i]._poblacion;
            mayorciudad=i;
        }
    }

    cout<<"--Ciudad de mayor Poblacion-- "<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<"Ciudad: "<<ciudades[mayorciudad]._nombre<<endl;
    cout<<endl;
    cout<<"Poblacion: "<<mayorpoblacion<<endl;
    cout<<endl;

    Pais pais= obtenerRegistroPais(ciudades[mayorciudad]._idpais);

    cout<<"Pais: "<<pais._nombre<<endl;
    cout<<endl;
    cout<<"Continente: "<<pais._continente<<endl;
    cout<<"-----------------------------"<<endl;


    delete[]ciudades;
    fclose(pArchivo);
    system("pause");
}

///ADICIONALES
///---------------------------------------------
///PUNTO 11
void realizarBackUp()
{

    Pais pais;
    FILE *pOrigen, *pDestino;

    pOrigen=fopen(ARCHIVO_PAISES,"rb");
    if(pOrigen==NULL)
    {
        return;
    }

    pDestino=fopen("paises.bak","ab+");
    if(pDestino==NULL)
    {
        return;
    }

    while(fread(&pais,sizeof(Pais),1,pOrigen)==1)
    {
        fwrite(&pais,sizeof(Pais),1,pDestino);
    }

    fclose(pOrigen);
    fclose(pDestino);

    Ciudad ciudad;
    FILE *pOrigenC, *pDestinoC;

    pOrigenC=fopen(ARCHIVO_CIUDADES,"rb");
    if(pOrigenC==NULL)
    {
        return;
    }

    pDestinoC=fopen("ciudades.bak","ab+");
    if(pDestinoC==NULL)
    {
        return;
    }

    while(fread(&ciudad,sizeof(Ciudad),1,pOrigenC)==1)
    {
        fwrite(&ciudad,sizeof(Ciudad),1,pDestinoC);
    }

    cout<<"Backup realizado con exito"<<endl;
    system("pause");
    fclose(pOrigenC);
    fclose(pDestinoC);;

}


void restaurarArchivos()
{

    Pais pais;

    FILE *pOrigen, *pDestino;
    pOrigen = fopen("paises.bak","rb");
    if(pOrigen == NULL)
    {
        return;
    }

    pDestino = fopen(ARCHIVO_PAISES,"wb");
    if(pDestino == NULL)
    {
        return;
    }

    while(fread(&pais, sizeof(Pais), 1, pOrigen)==1)
    {
        fwrite(&pais, sizeof(Pais), 1, pDestino);
    }

    fclose(pOrigen);
    fclose(pDestino);

    Ciudad ciudad;

    FILE *pOrigenC, *pDestinoC;

    pOrigenC = fopen("ciudades.bak","rb");

    if(pOrigenC == NULL)
    {
        return;
    }

    pDestinoC = fopen(ARCHIVO_CIUDADES,"wb");

    if(pDestinoC == NULL)
    {
        return;
    }

    while(fread(&ciudad, sizeof(Ciudad), 1, pOrigenC)==1)
    {
        fwrite(&pais, sizeof(Ciudad), 1, pDestinoC);
    }

    fclose(pOrigenC);
    fclose(pDestinoC);
}

///---------------------------------------------------------------------
///PUNTO 12
void cargarPaisesExcel(Sheet*,Book* );
void cargarCiudadesExcel(Sheet*,Book*);


void crearExcel()
{

    // Crea un objeto 'LIBRO' que representa un libro de Excel
    Book* libro = xlCreateBook(); // xlCreateXMLBook() para formato xlsx

    if (libro)   // Verifica si se creó correctamente el Libro
    {
        // Crea una hoja en el libro de Excel
        Sheet* hojaPaises = libro->addSheet("Paises");
        Sheet* hojaCiudades = libro->addSheet("Ciudades");



        hojaPaises->setCol(0, 0, 2);
        hojaPaises->setCol(1, 1, 10);
        hojaPaises->setCol(2, 2, 10);
        hojaPaises->setCol(3, 3, 20);
        hojaPaises->setCol(4, 4, 15);
        hojaPaises->setCol(5, 5, 13);
        hojaPaises->setCol(6, 6, 13);
        hojaPaises->setCol(7, 7, 18);
        hojaPaises->setCol(8, 8, 25);
        hojaPaises->setCol(9, 9, 25);

        Font* fuente;
        fuente=libro->addFont();
        fuente->setName("Times New Roman");
        fuente->setSize(12);
        fuente->setBold(true);

        Format* formato;
        formato=libro->addFormat();
        formato->setFont(fuente);
        formato->setFillPattern(FILLPATTERN_SOLID);
        formato->setPatternForegroundColor(COLOR_GRAY25);
        formato->setAlignH(ALIGNH_CENTER);
        formato->setAlignV(ALIGNV_CENTER);
        formato->setBorder(BORDERSTYLE_THIN);



        if (hojaPaises)   // Verifica si se creó correctamente la hoja pais
        {



            hojaPaises->writeStr(1, 1, "CODIGO",formato);
            hojaPaises->writeStr(1, 2, "CODIGO 2",formato);
            hojaPaises->writeStr(1, 3, "NOMBRE",formato);
            hojaPaises->writeStr(1, 4, "CONTINENTE",formato);
            hojaPaises->writeStr(1, 5, "SUPERFICIE",formato);
            hojaPaises->writeStr(1, 6, "POBLACION",formato);
            hojaPaises->writeStr(1, 7, "INDEPENDENCIA",formato);
            hojaPaises->writeStr(1, 8, "EXP DE VIDA",formato);
            hojaPaises->writeStr(1, 9, "CAPITAL",formato);

            cargarPaisesExcel(hojaPaises,libro);
        }

        if (hojaCiudades)
        {
            cargarCiudadesExcel(hojaCiudades, libro);
        }


        libro->save("PaisesyCiudades.xls");

        // Libera los recursos asociados al objeto 'libro'
        libro->release();

    }


}



void cargarPaisesExcel(Sheet* hojaPaises,Book *libro)
{


    int cantP=contarPaises();

    FILE *pArchivo;
    pArchivo=fopen(ARCHIVO_PAISES,"rb");

    if(pArchivo==NULL)
    {
        cout << "Error al abrir el archivo" << endl;
        system("pause");
        return;
    }

    FILE *pCiudades;
    pCiudades=fopen(ARCHIVO_CIUDADES,"rb");
    if(pCiudades==NULL)
    {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    Pais pais;
    Ciudad ciudad;
    int y=2;

    Font* fuente2 = libro->addFont();
    fuente2->setName("Arial");
    fuente2->setSize(10);

    Format* formato2 = libro->addFormat();
    formato2->setFont(fuente2);
    formato2->setBorder(BORDERSTYLE_THIN);
    formato2->setAlignV(ALIGNV_CENTER);
    formato2->setNumFormat(NUMFORMAT_NUMBER_SEP_NEGBRA);

    Format* formato3=libro->addFormat();
    formato3->setFont(fuente2);
    formato3->setBorder(BORDERSTYLE_THIN);
    formato3->setAlignV(ALIGNV_CENTER);
    formato3->setNumFormat(NUMFORMAT_NUMBER_D2);


    for (int i = 0; i < cantP; i++)
    {
        fread(&pais, sizeof(Pais), 1, pArchivo);


        hojaPaises->writeStr(y, 1, pais._codigo,formato2);
        hojaPaises->writeStr(y, 2, pais._codigo2,formato2);
        hojaPaises->writeStr(y, 3, pais._nombre,formato2);
        hojaPaises->writeStr(y, 4, pais._continente,formato2);
        hojaPaises->writeNum(y, 5, pais._superficie,formato2);
        hojaPaises->writeNum(y, 6, pais._poblacion,formato2);
        hojaPaises->writeNum(y, 7, pais._independencia,formato2);
        hojaPaises->writeNum(y, 8, pais._expectativaDeVida,formato3);



        while(fread(&ciudad,sizeof(Ciudad),1,pCiudades)==1)
        {

            if(pais._capital==0)
            {

                hojaPaises->writeStr(y, 9,"No informada", formato2);
            }

            if (pais._capital==ciudad._ID)
            {


                hojaPaises->writeStr(y, 9, ciudad._nombre, formato2);

            }
        }


        y++;
        rewind(pCiudades);

        //
    }
    fclose(pCiudades);
    fclose(pArchivo);

}

void cargarCiudadesExcel(Sheet *hojaCiudades,Book *libro) //funcion que carga la hoja ciudades
{

    int cantC=contarCiudades();

    FILE *pArchivo;
    pArchivo=fopen(ARCHIVO_CIUDADES,"rb");

    if(pArchivo==NULL)
    {
        cout << "Error al abrir el archivo" << endl;
        system("pause");
        exit(1);
    }



    Pais pais;
    Ciudad ciudad;

    //ancho de columnas
    hojaCiudades->setCol(0, 0, 2);
    hojaCiudades->setCol(1, 1, 10);
    hojaCiudades->setCol(2, 2, 30);
    hojaCiudades->setCol(3, 3, 20);
    hojaCiudades->setCol(4, 4, 20);

    //FORMATO DE LA 1ERA FILA
    Font* fuente;
    fuente=libro->addFont();
    fuente->setName("Arial");
    fuente->setSize(12);
    fuente->setBold(true);


    Format* formato;
    formato=libro->addFormat();
    formato->setFont(fuente);
    formato->setFillPattern(FILLPATTERN_GRAY12P5);
    formato->setPatternBackgroundColor(COLOR_AQUA);
    formato->setFillPattern(FILLPATTERN_DIAGCROSSHATCH);
    formato->setAlignH(ALIGNH_CENTER);
    formato->setAlignV(ALIGNV_CENTER);
    formato->setBorder(BORDERSTYLE_THICK);


    hojaCiudades->writeStr(1, 1, "CODIGO",formato);
    hojaCiudades->writeStr(1, 2, "NOMBRE",formato);
    hojaCiudades->writeStr(1, 3, "PAIS",formato);
    hojaCiudades->writeStr(1, 4, "POBLACION",formato);


    //FORMATO DE LOS DATOS
    Font* fuente2 = libro->addFont();
    fuente2->setName("Arial");
    fuente2->setSize(12);

    Format* formato2 = libro->addFormat();
    formato2->setFont(fuente2);
    formato2->setBorder(BORDERSTYLE_THIN);
    formato2->setFillPattern(FILLPATTERN_SOLID);
    formato2->setPatternForegroundColor(COLOR_AQUA);
    formato2->setNumFormat(NUMFORMAT_NUMBER_SEP_NEGBRA);

    char nombrePais[45];
    int y=2;

    for (int i=0; i<cantC; i++)
    {

        while(fread(&ciudad,sizeof(Ciudad),1,pArchivo)==1)
        {

            hojaCiudades->writeNum(y, 1, ciudad._ID,formato2);
            hojaCiudades->writeStr(y, 2, ciudad._nombre,formato2);

            FILE *pPaises;
            pPaises=fopen(ARCHIVO_PAISES,"rb");

            if(pPaises==NULL)
            {
                cout << "Error al abrir el archivo" << endl;
                system("pause");
                return;
            }

            while(fread(&pais, sizeof(Pais), 1, pPaises)==1)
            {

                if(strcmp(pais._codigo,ciudad._idpais)==0)
                {


                    strcpy(nombrePais,pais._nombre);

                }

            }

            hojaCiudades->writeStr(y, 3, nombrePais,formato2);
            hojaCiudades->writeNum(y, 4, ciudad._poblacion,formato2);

            y++;
            fclose(pPaises);

        }
    }

    fclose(pArchivo);
}


void exportarExcel()
{

    crearExcel();
    cout << "Creacion Exitosa!" << endl;

    system("pause");
    return;

}



