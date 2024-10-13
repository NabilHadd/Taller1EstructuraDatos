#include "Usuario.h"

//getters
std::string Usuario::getNombre(){return this -> nombre;}
long int Usuario::getId(){return this -> id;}
MaterialBibliografico** Usuario::getMaterialesPrestados(){return this -> materialesPrestados;}
MaterialBibliografico* Usuario::getMaterialPrestado(int i){return this -> materialesPrestados[i];}

//setters
void Usuario::setNombre(std::string nombre){this->nombre = nombre;}
void Usuario::setId(long int id){this->id = id;}
void Usuario::setMaterialesPrestados(MaterialBibliografico* materialesPrestados[5]){
  for (int i = 0; i < 5; i++) {

        this->materialesPrestados[i] = materialesPrestados[i];
    }
}
void Usuario::setMaterialPrestado(int i, MaterialBibliografico* materialPrestado){this->materialesPrestados[i] = materialPrestado;}

//constructor
Usuario::Usuario(std::string nombre, long int id, MaterialBibliografico* materialesPrestados[5]){
    this->setNombre(nombre);
    this->setId(id);
    this->setMaterialesPrestados(materialesPrestados);
}
Usuario::~Usuario() {
    std::cout << "Se ha destruido el  usuario: "<< this->getNombre() << std::endl;
}

//metodos
void Usuario::prestarMaterial(MaterialBibliografico* materialBibliografico) { 
    int i = 0;
    while (i < 5 && this->materialesPrestados[i] != nullptr) {
        i++;
    }
    if (i < 5) {
        this->materialesPrestados[i] = materialBibliografico;
        std::cout << "se entrego con exito" << std::endl;
    }
    else {
        std::cout << "no se pueden prestar mas" << std::endl;
    }
}
void Usuario::devolverMaterial(MaterialBibliografico* materialBibliografico){
    int j = 0;
  while (this->getMaterialesPrestados()[j] != nullptr && j<5) {
    j++;
  }

  for(int i = 0; i<5; i++){
    if(materialBibliografico->getIsbn() == this->materialesPrestados[i]->getIsbn()) {
      this->materialesPrestados[i] = nullptr;
      this->materialesPrestados[i] = this->getMaterialesPrestados()[j - 1];
      this->getMaterialesPrestados()[j - 1] = nullptr;

      break;
    }
  }
}

bool Usuario::poseeMateriales() {
    if (this->materialesPrestados[0] != nullptr) {
        return false;
    }
    else {
        return true;
    }
}

void Usuario::mostrarMaterialesPrestados(){
  std::cout << "===============Materiales de: " << this->getNombre() << "===============" << std::endl;
  if (!this->poseeMateriales()) {
      int i = 0;
      while (this->materialesPrestados[i] != nullptr && i < 5) {
          this->materialesPrestados[i]->mostrarInformacion();
          std::cout << "" << std::endl;
          i++;
      }
  }
  else {
      std::cout << "No posee material" << std::endl;
  }
  
  
}

