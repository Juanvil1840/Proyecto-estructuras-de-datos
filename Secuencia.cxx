#include "Secuencia.h"

//CONSTRUCTOR
Secuencia:: Secuencia(){
descripcion = "";
lineas_secuencia.clear();
};

//LIBERAR MEMORIA
Secuencia:: ~Secuencia(){
};

// obtener descripcion
std::string Secuencia:: ObtenerDescripcion(){
    return( descripcion );
}

// obtener lineas_secuencia
std::vector< std::string >& Secuencia:: ObtenerLineasSecuencia(){
    return( lineas_secuencia );
}

// obtener numbases
int Secuencia:: ObtenerNumbases(){
    return( numbases );
}

// obtener numcodigos
int Secuencia:: ObtenerNumcodigos(){
    return( numcodigos );
}

// fijar descripcion
void Secuencia:: FijarDescripcion(std::string ndescripcion){
    this->descripcion = ndescripcion;
}

// fijar lineas_secuencia
void Secuencia:: FijarLineasSecuencia(std::vector< std::string > n_lineas_secuencia ){
    this->lineas_secuencia = n_lineas_secuencia;
}

// fijar numbases
void Secuencia:: FijarNumbases(int n_numbases ){
    this->numbases = n_numbases;
}

// fijar numcodigos
void Secuencia:: FijarNumcodigos(int n_numcodigos ){
    this->numcodigos = n_numcodigos;
}

// agregar una linea a lineas_secuencia
void Secuencia:: AgregarLineaSecuencia(std::string linea){
    std::vector<std::string> temp = this->ObtenerLineasSecuencia();
    temp.push_back(linea); 
    this->FijarLineasSecuencia(temp); 
}
