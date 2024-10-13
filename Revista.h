#ifndef REVISTA_H_INCLUDED
#define REVISTA_H_INCLUDED

#include <iostream>
#include <string>
#include "MaterialBibliografico.h"

class Revista : public MaterialBibliografico {

private:
  int numeroEdicion;
  std::string mesPublicacion;

public:
  int getNumeroEdicion();
  std::string getMesPublicacion();

  void setNumeroEdicion(int numeroEdicion);
  void setMesPublicacion(std::string mesPublicacion);

  Revista(std::string nombre, std::string autor, std::string isbn, bool prestado, int numeroEdicion, std::string mesPublicacion);
  ~Revista();

  virtual void mostrarInformacion();

};



#endif // REVISTA_H_INCLUDED
