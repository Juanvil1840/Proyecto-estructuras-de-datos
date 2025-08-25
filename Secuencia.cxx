#include "Secuencia.h"
#include <algorithm>

//CONSTRUCTOR
Secuencia:: Secuencia(){
descripcion = "";
lineas_secuencia.clear();
};

//LIBERAR MEMORIA
Secuencia:: ~Secuencia(){
};

// obtener descripcion
std::string& Secuencia:: ObtenerDescripcion(){
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

// obtener codigos
std::vector< char >& Secuencia:: ObtenerCodigos(){
    return( codigos );
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

// fijar codigos
void Secuencia:: FijarCodigos(std::vector< char > nCodigos){
    this->codigos = nCodigos;
}

// agregar una linea a lineas_secuencia
void Secuencia:: AgregarLineaSecuencia(std::string linea){
    std::vector<std::string> temp = this->ObtenerLineasSecuencia();
    temp.push_back(linea); 
    this->FijarLineasSecuencia(temp); 
}

// establecer codigos, numcodigos y numbases
void Secuencia:: EstablecerCodigosYBases(){
    int bases = 0, ncodigos = 0;
    std::vector< char > codigos;
    //Recorrer el vector de lineas
    std::vector< std::string >::iterator itL;
    for(itL = this->ObtenerLineasSecuencia().begin(); itL != this->ObtenerLineasSecuencia().end(); itL ++){
        //Recorrer la cadena de caracteres para contar las bases
        for(char c: *itL){
	    if(c >= 'A' && c <= 'Z') bases ++;
	    if((c >= 'A' && c <= 'Z') || (c == '-')){
	        ncodigos++;
	        if(std::find(codigos.begin(), codigos.end(), c) == codigos.end()){
 		    codigos.push_back(c);
	        }
	    }
  
        } 
    }
	    this->FijarNumbases(bases);
	    this->FijarNumcodigos(ncodigos);
	    this->FijarCodigos(codigos);
}
