#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include "secuencias.h"
#include <list>

//-------------------------------------------------------------------------------------
typedef Secuencias sec;
typedef std::list< sec > secu;
//-------------------------------------------------------------------------------------

struct Command {
    std::string name;
    int argc;
    std::string usage;
};

static const std::vector<Command> commands = {
    {"cargar",            1, "cargar <nombre_archivo>"},
    {"listar_secuencias", 0, "listar_secuencias"},
    {"histograma",        1, "histograma <descripcion_secuencia>"},
    {"es_subsecuencia",   1, "es_subsecuencia <subsecuencia>"},
    {"enmascarar",        1, "enmascarar <subsecuencia>"},
    {"guardar",           1, "guardar <nombre_archivo>"},
    {"salir",             0, "salir"},
    {"codificar",         1, "codificar <nombre_archivo.fabin>"},
    {"decodificar",       1, "decodificar <nombre_archivo.fabin>"},
    {"ruta_mas_corta",    5, "ruta_mas_corta <descripcion_secuencia> <i> <j> <x> <y>"},
    {"base_remota",       3, "base_remota <descripcion_secuencia> <i> <j>"},
    {"ayuda",             0, "ayuda [<comando>]"}
};

bool isInteger(const std::string &s) {
    if (s.empty()) return false;
    size_t pos = (s[0] == '+' || s[0] == '-') ? 1 : 0;
    for (; pos < s.size(); ++pos) {
        if (!std::isdigit(s[pos])) return false;
    }
    return true;
}

template <typename T>
const T* findByName(const std::vector<T> &vec, const std::string &name) {
    typename std::vector<T>::const_iterator it = vec.begin();
    for (; it != vec.end(); ++it) {
        if (it->name == name) return &(*it);
    }
    return NULL;
}

template <typename T>
void printCommands(const std::vector<T> &vec) {
    typename std::vector<T>::const_iterator it = vec.begin();
    for (; it != vec.end(); ++it) {
        std::cout << "  " << it->usage << "\n";
    }
}

int main() {

    sec temp;
    secu ListSecuencias;
    
    std::string line;
    while (true) {
        std::cout << "$ ";
        if (!std::getline(std::cin, line)) break;

        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string tok;
        while (iss >> tok) tokens.push_back(tok);
        if (tokens.empty()) continue;

        const std::string cmd = tokens[0];
        // Comando 'ayuda'
        if (cmd == "ayuda") {
            if (tokens.size() == 1) {
                std::cout << "Comandos disponibles:\n";
                printCommands(commands);
            } else if (tokens.size() == 2) {
                const Command *c = findByName(commands, tokens[1]);
                if (c != NULL) std::cout << "Uso: " << c->usage << "\n";
                else           std::cout << "Error: comando desconocido para ayuda\n";
            } else {
                std::cout << "Error: uso incorrecto de ayuda. Uso: ayuda [<comando>]\n";
            }
            continue;
        }

       
        const Command *command = findByName(commands, cmd);
        if (command == NULL) {
            std::cout << "Error: comando desconocido\n";
            continue;
        }

        int provided = static_cast<int>(tokens.size()) - 1;
        if (provided != command->argc) {
            std::cout << "Error: numero de argumentos incorrecto. Uso: "
                      << command->usage << "\n";
            continue;
        }

        bool valid = true;
        if (cmd == "ruta_mas_corta") {
            for (int i = 2; i < static_cast<int>(tokens.size()); ++i) {
                if (!isInteger(tokens[i])) {
                    std::cout << "Error: argumentos invalidos. i, j, x y y deben ser enteros.\n";
                    valid = false;
                    break;
                }
            }
        } else if (cmd == "base_remota") {
            for (int i = 2; i < static_cast<int>(tokens.size()); ++i) {
                if (!isInteger(tokens[i])) {
                    std::cout << "Error: argumentos invalidos. i y j deben ser enteros.\n";
                    valid = false;
                    break;
                }
            }
        }
        if (!valid) continue;

                if (!valid) continue;

	    if(cmd=="cargar"){
	        ListSecuencias = temp.cargar(tokens[1]); 	
	    }

	    if(cmd=="listar_secuencias"){
	        temp.listar_secuencias();
	    }

	    if(cmd=="histograma"){
	        temp.histograma(tokens[1]);
	    }
	
	    if(cmd=="es_subsecuencia"){
	        temp.es_subsecuencia(tokens[1]);
	    }
	
	    if(cmd=="enmascarar"){
           temp.enmascarar(tokens[1]);
	    }
        
        if(tokens[0]=="guardar"){
            temp.guardar(tokens[1]);
        }
        else if(tokens[0]=="codificar"){
            temp.codificar(tokens[1]);
        }
        else if(tokens[0]=="decodificar"){
            temp.decodificar(tokens[1]);
        }
        else if(tokens[0]=="ruta_mas_corta"){
            temp.ruta_mas_corta(tokens[1], std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]),std::stoi(tokens[5]));
        }
       else if (tokens[0] == "base_remota") {
            temp.base_remota(tokens[1], std::stoi(tokens[2]), std::stoi(tokens[3]));
        }

        if (cmd == "salir") break;
    }
    return 0;
}

