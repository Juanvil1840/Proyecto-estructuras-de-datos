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
std::list< Secuencia >& Sistema:: ObtenerSecuencias(){
    return( secuencias );
}

// fijar secuencias
void Sistema:: FijarSecuencias (std::list< Secuencia > secs){
    this->secuencias = secs;
}

//COMANDO CARGAR
void Sistema :: cargar(std:: string nombre_archivo){

   std::list<Secuencia> lista;
    
    std::ifstream file(nombre_archivo);
    // en caso de que el archivo no se abra
    if (!file.is_open()) {
        std::cout << "(archivo erróneo) " << nombre_archivo << " no se encuentra o no puede leerse." << std::endl;
        file.close();
    }
    else{
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

    this->FijarSecuencias(lista);

    //Establecer codigos y bases en cada secuencia recien cargada
        std::list<Secuencia>::iterator itS;
        for(itS = secuencias.begin(); itS != secuencias.end(); itS ++){
	    itS -> EstablecerCodigosYBases();
        }
    }
}

//COMANDO LISTAR_SECUENCIAS
void Sistema :: listar_secuencias(){
    std::list<Secuencia>& secuencias = this->ObtenerSecuencias();

    if(secuencias.empty()){
        std:: cout << "No hay secuencias cargadas en memoria" << std::endl;
    }else{	
	std::cout << "Hay " << this->ObtenerSecuencias().size() << " secuencias cargadas en memoria" << std::endl;
	//Imprimir cuantas bases tiene cada secuencia
	std::list<Secuencia>::iterator itS;
	for(itS = this->ObtenerSecuencias().begin(); itS != this->ObtenerSecuencias().end(); itS ++){
	    std::string descripcion = itS->ObtenerDescripcion();	    
descripcion.erase(descripcion.find_last_not_of(" \n\r\t")+1);
	    std:: cout << "Secuencia " << descripcion << " contiene ";
	    if(itS->ObtenerNumcodigos() == itS->ObtenerNumbases()){
		std:: cout << itS->ObtenerNumbases() << " bases." << std::endl;
	    }else{
		std:: cout << "al menos " << itS->ObtenerNumbases() << " bases" << std::endl;
	    }
	}
    }
}


//COMANDO HISTOGRAMA
void Sistema :: histograma(std::string descripcion_secuencia){
    std::list<Secuencia>& secuencias = this->ObtenerSecuencias();
    bool encontrado = false;

    //buscar descripcion_secuencia
    std::list<Secuencia>::iterator itS;
    for(itS = secuencias.begin(); itS != secuencias.end(); itS ++){
	std::string descripcion = itS->ObtenerDescripcion();
	descripcion.erase(descripcion.find_last_not_of(" \n\r\t")+1);
	if( descripcion_secuencia == descripcion){
	    encontrado = true;
	    int* contadorCodigos = new int[itS->ObtenerCodigos().size()]();
	  
	    //Contar cuantos codigos hay de cada uno
	    std::vector< std::string >::iterator itL;
	    for(itL = itS->ObtenerLineasSecuencia().begin(); itL != itS->ObtenerLineasSecuencia().end(); itL ++){
		for(char c: *itL){
		    for(int i = 0 ; i < itS -> ObtenerCodigos().size() ; i++){
			if( c == itS -> ObtenerCodigos()[i] ){
			    contadorCodigos[i]++;
			}
		    }
		} 
            }

	    //Imprimir histograma
	    for(int i = 0 ; i < itS -> ObtenerCodigos().size() ; i++){
		std :: cout << itS -> ObtenerCodigos()[i] << " : " << contadorCodigos[i] << std::endl;
	    }
	    delete[] contadorCodigos;
	}
    }

    if(!encontrado) std::cout<< "Secuencia invalida" << std::endl;
}

// COMANDO ES_SUBSECUENCIA
void Sistema::es_subsecuencia(std::string subsecuencia) {
    std::list<Secuencia>& secs = this->ObtenerSecuencias();
    if (secs.empty()) {
        std::cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }
    if (subsecuencia.empty()) {
        std::cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria.\n";
        return;
    }

    long long total = 0;
    for (std::list<Secuencia>::iterator it = secs.begin(); it != secs.end(); ++it) {
        Secuencia& s = *it;

        const std::vector<std::string>& lineas = s.ObtenerLineasSecuencia();
        size_t len_total = 0;
        for (size_t i = 0; i < lineas.size(); ++i) len_total += lineas[i].size();

        std::string concat;
        concat.reserve(len_total);
        for (size_t i = 0; i < lineas.size(); ++i) concat += lineas[i];

        size_t pos = 0;
        while (true) {
            pos = concat.find(subsecuencia, pos);
            if (pos == std::string::npos) break;
            ++total;
            ++pos; // solapamientos
        }
    }

    if (total == 0) {
        std::cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria.\n";
    } else {
        std::cout << "La subsecuencia dada se repite " << total
                  << " veces dentro de las secuencias cargadas en memoria.\n";
    }
}


//  enmascarar
void Sistema::enmascarar(std::string subsecuencia) {

    std::list<Secuencia>& secs = this->ObtenerSecuencias();
    if (secs.empty()) {
        std::cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }
    if (subsecuencia.empty()) {
        std::cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada.\n";
        return;
    }

    long long total_enmascaradas = 0;

    for (std::list<Secuencia>::iterator it = secs.begin(); it != secs.end(); ++it) {
        Secuencia& s = *it;
        std::vector<std::string>& lineas = s.ObtenerLineasSecuencia();
        if (lineas.empty()) continue;

        // Guardar longitudes de cada línea
        std::vector<size_t> largos;
        largos.reserve(lineas.size());
        size_t len_total = 0;
        for (size_t i = 0; i < lineas.size(); ++i) {
            largos.push_back(lineas[i].size());
            len_total += lineas[i].size();
        }

        // Concatenar todas las líneas
        std::string concat;
        concat.reserve(len_total);
        for (size_t i = 0; i < lineas.size(); ++i) concat += lineas[i];

        // Buscar y enmascarar (permite solapamientos)
        size_t pos = 0;
        long long en_esta_secuencia = 0;
        while (true) {
            pos = concat.find(subsecuencia, pos);
            if (pos == std::string::npos) break;
            for (size_t k = 0; k < subsecuencia.size(); ++k) {
                concat[pos + k] = 'X';
            }
            ++en_esta_secuencia;
            ++total_enmascaradas;
            ++pos; // solapamientos
        }

        // Si hubo cambios, reconstruir con los mismos anchos y recalcular métricas
        if (en_esta_secuencia > 0) {
            std::vector<std::string> nuevas;
            nuevas.reserve(largos.size());
            size_t idx = 0;
            for (size_t i = 0; i < largos.size(); ++i) {
                nuevas.push_back(concat.substr(idx, largos[i]));
                idx += largos[i];
            }
            s.FijarLineasSecuencia(nuevas);
            s.EstablecerCodigosYBases();
        }
    }

    if (total_enmascaradas == 0) {
        std::cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada.\n";
    } else {
        std::cout << total_enmascaradas
                  << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.\n";
    }
}


//COMANDO GUARDAR
void Sistema :: guardar(std::string nombre_archivo){
 if(!secuencias.empty()){
     //Crear/abrir archivo 
     std::ofstream archivo(nombre_archivo+".fa");
     if(!archivo){
       std::cout<<"(problemas en archivo) Error guardando en "<<nombre_archivo<<".\n";
     }
     
     std::vector< std::string >::iterator itCod; //iterador para cada linea 
     std::list< Secuencia >::iterator itSec; //iterador que me recorrera la lista de secuencias
     for(itSec = secuencias.begin(); itSec != secuencias.end();  ++itSec){
        //primero guarda la descripción
        archivo << ">" << itSec->ObtenerDescripcion() <<"\n";
        //luego recorre linea por linea el vector que contiene la linea de secuencia
        for(itCod = itSec->ObtenerLineasSecuencia().begin(); itCod != itSec->ObtenerLineasSecuencia().end(); ++itCod){
        archivo << *itCod << "\n";
        }
     }
     archivo.close();
     std::cout<<"(escritura exitosa) Las secuencias han sido guardadas en "<<nombre_archivo<<".fa\n";


    }else{
     std::cout<<"(no hay secuencias cargadas) No hay secuencias cargadas en memoria. \n";
    }
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
