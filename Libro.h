#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED

#include <iostream>
#include <string>
#include "MaterialBibliografico.h"

class Libro : public MaterialBibliografico {

private:
  std::string fechaPublicacion,resumen;

public:
  std::string getFechaPublicacion();
  std::string getResumen();

  void setFechaPublicacion(std::string fechaPublicacion);
  void setResumen(std::string resumen);

  Libro(std::string nombre, std::string autor, std::string isbn, bool prestado, std::string fechaPublicacion, std::string resumen);
  ~Libro();

  virtual void mostrarInformacion();

};



#endif // LIBRO_H_INCLUDED
