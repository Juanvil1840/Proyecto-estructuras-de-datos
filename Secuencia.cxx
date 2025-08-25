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
std::vector< std::string > Secuencia:: ObtenerLineasSecuencia(){
    return( lineas_secuencia );
}

// fijar descripcion
void Secuencia:: FijarDescripcion(std::string ndescripcion){
    this->descripcion = ndescripcion;
}

// fijar lineas_secuencia
void Secuencia:: FijarLineasSecuencia(std::vector< std::string > n_lineas_secuencia ){
    this->lineas_secuencia = n_lineas_secuencia;
}

// agregar una linea a lineas_secuencia
void Secuencia:: AgregarLineaSecuencia(std::string linea){
    std::vector<std::string> temp = this->ObtenerLineasSecuencia();
    temp.push_back(linea); 
    this->FijarLineasSecuencia(temp); 
}
