#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include <iostream>
#include <string>
#include "MaterialBibliografico.h"

class Usuario{
private:
  std::string nombre;
  long int id;
  MaterialBibliografico* materialesPrestados[5];

public:
  std::string getNombre();
  long int getId();
  MaterialBibliografico** getMaterialesPrestados();
  MaterialBibliografico* getMaterialPrestado(int i);

  void setNombre(std::string nombre);
  void setId(long int id);
  void setMaterialesPrestados(MaterialBibliografico* materialesPrestados[5]);
  void setMaterialPrestado(int i, MaterialBibliografico* materialPrestado);

  Usuario(std::string nombre, long int id, MaterialBibliografico* materialesPrestados[5]);
  ~Usuario();

  void prestarMaterial(MaterialBibliografico* materialBibliografico);
  void devolverMaterial(MaterialBibliografico* materialBibliografico);
  void mostrarMaterialesPrestados();
  bool poseeMateriales();

};


#endif // USUARIO_H_INCLUDED
