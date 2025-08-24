#ifndef __SECUENCIAS__H__
#define __SECUENCIAS__H__
#include<iostream>
#include<vector>
#include<list>

//para primera entrega todas las funciones no cuentan con retorno

class Secuencias{

    
protected:
    std::string descripcion;
    std::vector< std::string >linea_secuencia;
public:
    //constructor
    Secuencias();
    // Destructor
    virtual ~Secuencias();
    std::list< Secuencias > cargar(std::string nombre_archivo);
    void listar_secuencias();
    void histograma(std::string descripcion_secuencia);
    void es_subsecuencia(std::string subsecuencia);
    void enmascarar(std::string subsecuencia);
    void guardar(std:: string nombre_archivo);
    void codificar(std:: string nombre_archivo);
    void decodificar(std::string nombre_archivo);
    void ruta_mas_corta(std::string descripcion_secuencia, int i, int j, int x, int y);
    void base_remota(std::string base_remota, int i, int j);

};

#endif // __SECUENCIAS__H__
