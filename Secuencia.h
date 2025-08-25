#ifndef __SECUENCIA__H__
#define __SECUENCIA__H__
#include<iostream>
#include <vector>

class Secuencia {
  public:
    Secuencia();
    virtual ~Secuencia();
    std::string ObtenerDescripcion();
    std::vector< std::string > ObtenerLineasSecuencia();
    void FijarDescripcion(std::string ndescripcion);
    void FijarLineasSecuencia(std::vector< std::string > n_lineas_secuencia );
    void AgregarLineaSecuencia(std::string linea);

  protected:
    std::string descripcion;
    std::vector< std::string > lineas_secuencia;
};

#endif // __SISTEMA__H__

// eof - Sistema.h
