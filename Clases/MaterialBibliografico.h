#ifndef MATERIALBIBLIOGRAFICO_H_INCLUDED
#define MATERIALBIBLIOGRAFICO_H_INCLUDED

#include <iostream>
#include <string>
class MaterialBibliografico{

private:
  std::string nombre, autor, isbn;
  bool prestado;

public:
  std::string getNombre();
  std::string getAutor();
  std::string getIsbn();
  bool getPrestado();

  void setNombre(std::string nombre);
  void setAutor(std::string autor);
  void setIsbn(std::string isbn);
  void setPrestado(bool prestado);

  MaterialBibliografico(std::string nombre, std::string autor, std::string isbn, bool prestado);
  virtual ~MaterialBibliografico();
  virtual void mostrarInformacion();

};



#endif // MATERIALBIBLIOGRAFICO_H_INCLUDED
