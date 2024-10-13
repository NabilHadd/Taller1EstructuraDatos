#include "Revista.h"

int Revista::getNumeroEdicion(){return this->numeroEdicion;}
std::string Revista::getMesPublicacion(){return this->mesPublicacion;}

void Revista::setNumeroEdicion(int numeroEdicion){this->numeroEdicion = numeroEdicion;}
void Revista::setMesPublicacion(std::string mesPublicacion){this->mesPublicacion = mesPublicacion;}

Revista::Revista(std::string nombre, std::string autor, std::string isbn, bool prestado, int numeroEdicion, std::string mesPublicacion) : MaterialBibliografico(nombre, autor, isbn, prestado){
  this->setNumeroEdicion(numeroEdicion);
  this->setMesPublicacion(mesPublicacion);
}

Revista::~Revista(){};

void Revista::mostrarInformacion(){
  MaterialBibliografico::mostrarInformacion();
  std::cout<<"Edicion n°: "<<this->getNumeroEdicion()<<std::endl;
  std::cout<<"Mes Publicacion: "<<this->getMesPublicacion()<<std::endl;
}

