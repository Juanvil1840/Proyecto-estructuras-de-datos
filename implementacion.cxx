#include "secuencias.h"
#include<fstream>
#include<string>

//CONSTRUCTOR
Secuencias::Secuencias(){
descripcion = "";
linea_secuencia.clear();
};

//LIBERAR MEMORIA
Secuencias::~Secuencias(){
};
//COMANDO BASE REMOTA
void Secuencias::base_remota(std::string base_remota, int i, int j){

    std::cout<<"Exito2 "<<base_remota<<" i= "<<i<<" j= "<<j<<"\n";

}

//COMANDO CARGAR
std::list< Secuencias > Secuencias::cargar(std::string nombre_archivo){

   std::list<Secuencias> lista;
    std::ifstream file(nombre_archivo);

    if (!file.is_open()) {
        std::cout << "(archivo erróneo) " << nombre_archivo << " no se encuentra o no puede leerse." << std::endl;
        return lista; // lista vacia
    }

    std::string linea;
    Secuencias actual;

    while (std::getline(file, linea)) {
        if (!linea.empty() && linea[0] == '>') {
            // Si ya había una secuencia en construcción
            if (!actual.descripcion.empty()) {
                lista.push_back(actual);
                actual = Secuencias(); // reiniciamos
            }
            actual.descripcion = linea.substr(1); // quitar '>'
        } else if (!linea.empty()) {
            actual.linea_secuencia.push_back(linea);
        }
    }

    // Guardar la última secuencia
    if (!actual.descripcion.empty()) {
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

//COMANDO CODIFICAR
void Secuencias::codificar(std::string nombre_archivo){

 std::cout<<"exito2"<<nombre_archivo<<"\n";
}

//COMANDO DECODIFICAR
void Secuencias::decodificar(std::string nombre_archivo){

std::cout<<"Exito 2"<<nombre_archivo<<"\n";

}

//COMANDO ENMASCARAR
void Secuencias::enmascarar(std::string subsecuencia){

    std::cout<<"Exito enmascarar " << subsecuencia << "\n";
}

//COMANDO ES SUBSECUENCIA
void Secuencias::es_subsecuencia(std::string subsecuencia){

    std::cout<<"Exito es_subsecuencia " << subsecuencia << "\n";
}

//COMANDO GUARDAR
void Secuencias::guardar(std::string nombre_archivo){

    std::cout<<"Exito guardar " << nombre_archivo << "\n";
}

//COMANDO HISTOGRAMA
void Secuencias::histograma(std::string descripcion_secuencia){

    std::cout<<"Exito histograma " << descripcion_secuencia << "\n";
}

//COMANDO LISTAR_SECUENCIAS
void Secuencias::listar_secuencias(){

    std::cout<<"Exito listar_secuencias \n";
}

//COMANDO RUTA_MAS_CORTA
void Secuencias::ruta_mas_corta(std::string descripcion_secuencia, int i, int j, int x, int y){

    std::cout<<"Exito2 "<<descripcion_secuencia<<" i= "<<i<<" j= "<<j<<" x= "<<x<<" y= "<<y<<"\n";

}
