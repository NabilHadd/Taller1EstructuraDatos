#include "MaterialBibliografico.h"

std::string MaterialBibliografico::getNombre(){return this->nombre;}
std::string MaterialBibliografico::getAutor(){return this->autor;}
std::string MaterialBibliografico::getIsbn(){return this->isbn;}
bool MaterialBibliografico::getPrestado(){return this->prestado;}

void MaterialBibliografico::setNombre(std::string nombre){this->nombre = nombre;}
void MaterialBibliografico::setAutor(std::string autor){this->autor = autor;}
void MaterialBibliografico::setIsbn(std::string isbn){this->isbn = isbn;}
void MaterialBibliografico::setPrestado(bool prestado){this->prestado = prestado;}

MaterialBibliografico::MaterialBibliografico(std::string nombre, std::string autor, std::string isbn, bool prestado){
  this->setNombre(nombre);
  this->setAutor(autor);
  this->setIsbn(isbn);
  this->setPrestado(prestado);  
}

MaterialBibliografico::~MaterialBibliografico(){
  std::cout<<"se ha destruido el material: "<<this->getNombre()<<std::endl;
}

void MaterialBibliografico::mostrarInformacion(){
  std::cout<<"Nombre: "<<this->getNombre()<<std::endl;
  std::cout<<"Autor: "<<this->getAutor()<<std::endl;
  std::cout<<"Codigo ISBN: "<<this->getIsbn()<<std::endl;
  if(prestado){
    std::cout<<"Estado: prestado"<<std::endl;
  }else{
    std::cout<<"Estado: disponible"<<std::endl;
  }
}
