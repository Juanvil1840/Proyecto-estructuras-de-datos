#include<fstream>
#include<string>
#include<vector>
#include<list>
#include "Sistema.h"

// obtener comandos
const std::vector<Comando>& Sistema :: ObtenerComandos() const{
    return( comandos );
}

// fijar comandos
void Sistema::FijarComandos(std::vector<Comando> ncomandos) {
  this->comandos = ncomandos;
}

// obtener secuencias
std::list< Secuencia > Sistema:: ObtenerSecuencias(){
    return( secuencias );
}

// fijar secuencias
void Sistema:: FijarSecuencias (std::list< Secuencia > secs){
    this->secuencias = secs;
}

//COMANDO CARGAR
std::list< Secuencia > Sistema :: cargar(std:: string nombre_archivo){

    std::list<Secuencia> lista;
    std::ifstream file(nombre_archivo);
    
    if (!file.is_open()) {
        std::cout << "(archivo erróneo) " << nombre_archivo << " no se encuentra o no puede leerse." << std::endl;
        return lista; // lista vacia
    }

    std::string linea;
    Secuencia actual;

    while (std::getline(file, linea)) {
        if (!linea.empty() && linea[0] == '>') {
            // Si ya había una secuencia en construcción
            if (!actual.ObtenerDescripcion().empty()) {
                lista.push_back(actual);
                actual = Secuencia(); // reiniciamos
            }
            actual.FijarDescripcion(linea.substr(1)); // quitar '>'
        } else if (!linea.empty()) {
            actual.AgregarLineaSecuencia(linea); 
        }
    }    

    // Guardar la última secuencia
    if (!actual.ObtenerDescripcion().empty()) {
        lista.push_back(actual);
    }

    file.close();

    // muestra en pantalla cuantas cadenas se cargaron
    if (lista.empty()) {
        std::cout << "(archivo vacío) " << nombre_archivo 
                  << " no contiene ninguna secuencia." << std::endl;
    } else if (lista.size() == 1) {
        std::cout << "(una sola secuencia) 1 secuencia cargada correctamente desde " 
                  << nombre_archivo << "." << std::endl;
    } else {
        std::cout << "(varias secuencias) " << lista.size() 
                  << " secuencias cargadas correctamente desde " 
                  << nombre_archivo << "." << std::endl;
    }

    return lista;
}

//COMANDO LISTAR_SECUENCIAS
void Sistema :: listar_secuencias(){

    std::cout<<"Exito listar_secuencias \n";
}

//COMANDO HISTOGRAMA
void Sistema :: histograma(std::string descripcion_secuencia){

    std::cout<<"Exito histograma " << descripcion_secuencia << "\n";
}

//COMANDO ES SUBSECUENCIA
void Sistema :: es_subsecuencia(std::string subsecuencia){

    std::cout<<"Exito es_subsecuencia " << subsecuencia << "\n";
}

//COMANDO ENMASCARAR
void Sistema :: enmascarar(std::string subsecuencia){

    std::cout<<"Exito enmascarar " << subsecuencia << "\n";
}

//COMANDO GUARDAR
void Sistema :: guardar(std::string nombre_archivo){

    std::cout<<"Exito guardar " << nombre_archivo << "\n";
}

//COMANDO CODIFICAR
void Sistema :: codificar(std::string nombre_archivo){

 std::cout<<"Exito codificar " << nombre_archivo << "\n";
}

//COMANDO DECODIFICAR
void Sistema :: decodificar(std::string nombre_archivo){

  std::cout<<"Exito decodificar " << nombre_archivo << "\n";

}

//COMANDO RUTA_MAS_CORTA
void Sistema :: ruta_mas_corta(std::string descripcion_secuencia, int i, int j, int x, int y){

    std::cout<<"Exito ruta_mas_corta"<<descripcion_secuencia<<" i= "<<i<<" j= "<<j<<" x= "<<x<<" y= "<<y<<"\n";

}

//COMANDO BASE REMOTA
void Sistema :: base_remota(std::string base_remota, int i, int j){

    std::cout<<"Exito base_remota"<<base_remota<<" i= "<<i<<" j= "<<j<<"\n";

}
