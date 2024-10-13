#include "Libro.h"

std::string Libro::getFechaPublicacion(){return this->fechaPublicacion;}
std::string Libro::getResumen(){return this->resumen;}

void Libro::setFechaPublicacion(std::string fechaPublicacion){this->fechaPublicacion = fechaPublicacion;}
void Libro::setResumen(std::string resumen){this->resumen = resumen;}

Libro::Libro(std::string nombre, std::string autor, std::string isbn, bool prestado, std::string fechaPublicacion, std::string resumen) : MaterialBibliografico(nombre, autor, isbn, prestado){
  this->setFechaPublicacion(fechaPublicacion);
  this->setResumen(resumen);
}

Libro::~Libro(){}

void Libro::mostrarInformacion(){
  MaterialBibliografico::mostrarInformacion();
  std::cout<<"Fecha de publicacion: "<<this->getFechaPublicacion()<<std::endl;
  std::cout<<"Resumen: "<<this->getResumen()<<std::endl;
}
