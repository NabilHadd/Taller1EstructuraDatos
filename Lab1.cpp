#include "Libro.h"
#include "Revista.h"
#include "Usuario.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

MaterialBibliografico* buscarMaterialI(MaterialBibliografico** materiales, string isbn) {
    /*Funcion que busca un material bibliografico en un vector de materiales
    a partir del codigo isbn

    
    @param validador: utilizado para comprobar si el material fue encontrado
    @param i: utilizado para recorrer materiales en el while
    @param materiales: un puntero a un vector de punteros
    @param isbn: codigo isbn del material buscado

    @return: el material que coincida con el isbn, en caso de no hallarlo
    se devuelve nullptr
    */
    bool validador = false;
    int i = 0;
    while (materiales[i] != nullptr && i<100) {
        if (isbn == materiales[i]->getIsbn()) {
            validador = true;
            return materiales[i];
        }
        i++;
    }
        return nullptr;


}

MaterialBibliografico** leerMateriales(string file) {
    /*Funcion que crea objetos de tipo MaterialBibliografico a partir 
    de la informacion encontrada en file.

    @param file: direccion del archivo del cual se leeran los materiales (material.txt)
    Cabe mencionar que cada linea posee un identificador l o r, para identificar
    si la linea corresponde a un libro o revista.

    @return: un puntero hacia un vector de punteros de tipo MaterialBibliografico.
    */

    //creamos el puntero hacia el vector de punteros
    MaterialBibliografico** materiales = new MaterialBibliografico* [100];

    //lo inicializamos con nullptr, esto ayudara a la logica del programa
    for (int i = 0; i < 100; i++) {
        materiales[i] = nullptr;
    }

    ifstream archivo(file);
    archivo.imbue(locale("es_ES.UTF-8"));
    if (!archivo) {
        cout << "No se pudo abrir el archivo material." << endl;
        return materiales;
    }

    string linea;
    int i = 0;
    //while que lee las lineas del archivo hasta que ya no hayan mas
    while (getline(archivo, linea)) {
        if (i < 100) {
            istringstream stream(linea);
            string parte;

            string nombre, autor, fecha, mesPublicacion, resumen, isbn;
            int edicion;
            bool estado;

            getline(stream, parte, '/');
            string libro = "l";
            string revista = "r";

            //consultamos si es libro
            if (parte == libro) {
                getline(stream, nombre, '/');
                getline(stream, autor, '/');
                getline(stream, isbn, '/');
                getline(stream, parte, '/');
                istringstream(parte) >> estado;
                getline(stream, fecha, '/');
                getline(stream, resumen, '/');

                materiales[i] = new Libro(nombre, autor, isbn, estado, fecha, resumen);
                i++;
            }//consultamos si es revista
            else if (parte == revista) {
                getline(stream, nombre, '/');
                getline(stream, autor, '/');
                getline(stream, isbn, '/');
                getline(stream, parte, '/');
                istringstream(parte) >> estado;
                getline(stream, parte, '/');
                istringstream(parte) >> edicion;
                getline(stream, mesPublicacion, '/');

                materiales[i] = new Revista(nombre, autor, isbn, estado, edicion, mesPublicacion);
                i++;
            }
            else {//en caso de que no coincida, no la lee
                cout << "Hubo problemas con el material: " << linea << endl;

            }
        }//en caso de que se supere los 100 materiales, deja de leer
        else {
            cout << "Se supero el maximo de materiales en el datacenter" << endl;
            archivo.close();
            return materiales;
        }
        
    }
    archivo.close();
    return materiales;
}

MaterialBibliografico** agregarMaterial(MaterialBibliografico** materiales, MaterialBibliografico* material) {
    /*Funcion que agrega un material al vector de materiales

    @param materiales: un puntero a un vector de punteros
    @param material: puntero hacia un objeto de tipo materialBibliografico

    @return: devuelve un puntero hacia el vector modificado
    (no es estrictamente necesario que lo devuelva)
    */

    //confirma que el material no haya sido agregado antes
    if (buscarMaterialI(materiales, material->getIsbn()) == nullptr) {
        int i = 0;
        //recorre el vector hasta el ultimo inicializado
        while (materiales[i] != nullptr && i<100) {
            i++;
        }
        //si el vector no esta lleno, lo agrega
        if (i < 100) {
            materiales[i] = material;
        }
        else {
            cout << "no se pudo agregar el material: " << material->getNombre() << "\ndebido a que no queda espacio en la biblioteca" << endl;
        }

    }
    else {
        cout << "Ya existe el material" << endl;
    }

    return materiales;

}

Usuario** leerUsuarios(string file, MaterialBibliografico** materiales) {
    /*Funcion que crea objetos de tipo Usuario a partir
    de la informacion encontrada en file.

    @param file: direccion del archivo del cual se leeran los usuarios (usuarios.txt)
    Debido a que cada usuario posee materiales prestados, cada linea del archivo posee el nombre
    de usuario, su id y los isbn correspondientes a cada libro prestado
    @param materiales: puntero hacia un vector de punteros de tipo MaterialBibliografico.

    @return: un puntero hacia un vector de punteros de tipo Usuario
    */

    //creamos el puntero hacia el vector de punteros
    Usuario** usuarios = new Usuario * [10];

    //inicializamos el vector con nullptr
    for (int i = 0; i < 10; i++) {
        usuarios[i] = nullptr;
    }

    ifstream archivo(file);
    if (!archivo) {
        cout << "No se pudo abrir el archivo usuarios." << endl;
    }

    string linea;
    int i = 0;
    //leemos las 10 primeras lineas del archivo, debido a que 10 es el maximo de usuarios permitido
    while (getline(archivo, linea) && i < 10) {


        istringstream stream(linea);
        string parte;

        string nombre;
        long int id;

        //inicializamos vectores auxiliares
        string* ibsn[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
        MaterialBibliografico* materialesPrestados[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };

        getline(stream, nombre, '/');
        getline(stream, parte, '/');
        istringstream(parte) >> id;

        //rellenamos el vector de isbn´s con los codigos presentes en la linea del usuario
        int k = 0;
        while (getline(stream, parte, '/')) {
            ibsn[k] = new string(parte);
            k++;
        }

        //buscamos los materiales asociados a dichos isbn´s y
        //los agregamos al vector "materialesPrestados"
        int j = 0;
        while (ibsn[j] != nullptr && j<5) {
            materialesPrestados[j] = buscarMaterialI(materiales, *ibsn[j]);
        j++;
        }
        //se rellena el vector de usuarios con los usuarios leidos
        usuarios[i] = new Usuario(nombre, id, materialesPrestados);
        i++;
    }
    return usuarios;
}

Usuario** agregarUsuario(Usuario** usuarios, string nombre, long int id) {
    /*Funcion que crea objetos de tipo Usuario y los agrega al vector de usuarios

    @param nombre: nombre del nuevo usuario
    @param id: codigo id del nuevo usuario
    @param usuarios: puntero hacia un vector de punteros de tipo Usuario.

    @return: un puntero hacia el vector de punteros de tipo Usuario modificado
    */

    //el usuario se creara con un vector sin materiales, debido a que al ser nuevo 
    // no deberia poseer libros prestados
    MaterialBibliografico* materialesAux[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
    Usuario* usuario = new Usuario(nombre, id, materialesAux);
    
    //se busca la siguiente posicion disponible en el vector
    int i = 0;
    while (usuarios[i] != nullptr && i<10) {
        i++;
    }
    //se comprueba que haya espacio
    if (i < 10) {
        usuarios[i] = usuario;
    }
    else {
        cout << "Se alcanzo el maximo de usuarios" << endl;
    }
    

    return usuarios;
}

void escribirUsuarios(Usuario** usuarios, string file) {
    /*Funcion que escribe los usuarios presentes en el vector 
    de usuarios en el archivo de usuarios

    @param file: archivo en el que se escribiran los usuarios (usuarios.txt)
    @param usuarios: puntero hacia un vector de punteros de tipo Usuario.
    */

    //abrimos el archivo
    ofstream archivo(file);

    //por cada uno de los usuarios, creamos un puntero hacia un vector de punteros 
    // apuntando a los materiales prestados correspondientes a cada usuario
    int i = 0;
    while (usuarios[i] != nullptr && i < 10 ) {
        MaterialBibliografico** materialesPrestados = usuarios[i]->getMaterialesPrestados();

        if (i != 0) {
            archivo << "\n";
        }//al principio de cada linea, damos un salto de la linea anterior (excepto la primera linea)


        //escribimos el nombre y el id
        archivo << usuarios[i]->getNombre() << '/';
        archivo << usuarios[i]->getId() << '/';

        //escribimos los codigos isbn correspondiente a cada uno de los materiales prestados
        int j = 0;
        while (materialesPrestados[j] != nullptr && j < 5) {
            archivo << materialesPrestados[j]->getIsbn() << '/';
            j++;
        }
        i++;
    }
    //se cierra el archivo
    archivo.close();
}

void escribirMaterial(MaterialBibliografico** materiales, string file) {
    /*Funcion que escribe los materiales presentes en el vector
    de materiales en el archivo de materiales

    @param file: archivo en el que se escribiran los materiales (materiales.txt)
    @param materiales: puntero hacia un vector de punteros de tipo MaterialBibliografico.
    */


    //se abre el archivo
    ofstream archivo(file);

    int i = 0;
    //se recorre el vector de materiales
    while (materiales[i] != nullptr && i<100) {

        if (i != 0) {
            archivo << '\n';
        }//al principio de cada linea, damos un salto de la linea anterior (excepto la primera linea)

        //comprueba que se trate de un objeto de tipo revista
        if (dynamic_cast<Revista*>(materiales[i])){
            //para poder acceder a los metodos de revista, 
            // debe ser una revista y para poder inicializarlo como 
            // revista C debe tener certeza de que lo es
            Revista* aux = dynamic_cast<Revista*>(materiales[i]);
            archivo << "r/";//escribe el identificador
            archivo << aux->getNombre() << '/';
            archivo << aux->getAutor() << '/';
            archivo << aux->getIsbn() << '/';
            archivo << aux->getPrestado() << '/';
            archivo << aux->getNumeroEdicion() << '/';
            archivo << aux->getMesPublicacion() << '/';
        }
        else {//en caso contrario, obvia que es un libro
            Libro* aux = dynamic_cast<Libro*>(materiales[i]);
            archivo << "l/";//escribe el identificador
            archivo << aux->getNombre() << '/';
            archivo << aux->getAutor() << '/';
            archivo << aux->getIsbn() << '/';
            archivo << aux->getPrestado() << '/';
            archivo << aux->getFechaPublicacion() << '/';
            archivo << aux->getResumen() << '/';
        }
        i++;
    }

    //cierra el archivo
    archivo.close();
}

void listarMateriales(MaterialBibliografico** materiales) {
    /*Funcion que lista todos los materiales del vector materiales 
    junto a su informacion mas imporante
    
    @param materiales: puntero hacia un vector de punteros de tipo MaterialBibliografico
    */

    int i = 0;
    while (materiales[i] != nullptr && i <100) {
        //hace uso de la funcion mostrarInformacion de la clase base, debido a que esta muestra
        //menos informacion y es menos engorroso
        materiales[i]->MaterialBibliografico::mostrarInformacion();
        cout << "" << endl;
        i++;
    }
}

void listarMaterialUsuarios(Usuario** usuarios) {
    /*Funcion que lista todos los materiales prestados correspondientes a cada usuario 
    del vector usuarios

    @param usuarios: puntero hacia un vector de punteros de tipo usuarios
    */
    int i = 0;
    //recorre el vector mosntrando los materiales prestados de cada usuario
    while (usuarios[i] != nullptr && i < 10) {
        usuarios[i]->mostrarMaterialesPrestados();
        i++;
    }
}

void listarUsuarios(Usuario** usuarios) {
    /*Funcion que lista todos los usuarios pertenecientes al vector usuarios

    @param usuarios: puntero hacia un vector de punteros de tipo Usuario
    */
    int i = 0;
    //lista cada usuario junto a su id
    while (usuarios[i] != nullptr && i < 10) {
        cout << "(" << i + 1 << ") " << usuarios[i]->getNombre() << ", "<< usuarios[i]->getId() << endl;
        i++;
    }
}

void buscarMaterialA(MaterialBibliografico** materiales, string autor) {
    /*Funcion que busca un material en funcion de su autor

    @param materiales: puntero hacia un vector de punteros de tipo MaterialBibliografico
    @param autor: autor del cual se buscan libros
    */
    

    int i = 0;
    bool vali = false;
    //recorre el vector de materiales mostrando por pantalla cada 
    // uno de aquellos que coincidan con el autor
    while (materiales[i] != nullptr && i < 100) {
        if (autor == materiales[i]->getAutor()) {
            cout << "\nIndice :" << i << endl;
            vali = true;
            materiales[i]->MaterialBibliografico::mostrarInformacion();
            cout << "" << endl;
        }
        i++;
    }
    //en caso de no encontrar ninguna coincidencia, lo indica
    if (!vali) {
        cout << "No se encontro el material: " << autor << endl;
    }
}

void buscarMaterialT(MaterialBibliografico** materiales, string titulo) {
    /*Funcion que busca un material en funcion de su titulo

    @param materiales: puntero hacia un vector de punteros de tipo MaterialBibliografico
    @param titulo: titulo del libro buscado
    */

    int i = 0;
    bool vali = false;
    //recorre el vector de materiales mostrando por pantalla cada 
    // uno de aquellos que coincidan con el titulo
    while (materiales[i] != nullptr && i<100) {
        if ( titulo == materiales[i]->getNombre()) {
            cout << "\nIndice :" << i<<endl;
            vali = true;
            materiales[i]->MaterialBibliografico::mostrarInformacion();
            cout << "" << endl;
        }
        i++;
    }
    //en caso de no coincidir con ningun material, lo indica
    if (!vali) {
        cout << "No se encontro el material: " << titulo << endl;
    }
}

Usuario* buscarUsuario(Usuario** usuarios, long int id) {
    /*Funcion que busca un usuario en funcion de su id

    @param usuarios: puntero hacia un vector de punteros de tipo Usuario
    @param id: id del usuario buscado

    @return: devuelve el usuario en caso de encontrarlo, en caso contrario devuelve nullptr
    */
    int i = 0;
    while (usuarios[i] != nullptr) {
        if (id == usuarios[i]->getId()) {
            return usuarios[i];
        }
        i++;
    }
    return nullptr;
}

Usuario** eliminarUsuario(Usuario** usuarios, Usuario* u) {
    /*Funcion que elimina el usuario indicado del vector de usuarios

    @param usuarios: puntero hacia un vector de punteros de tipo Usuario
    @param u: usuario que se desea eliminar

    @return: devuelve el puntero hacia el vector usuarios modificado
    */

    int i = 0;
    //recorre el vector de usuarios, si coincide con el usuario u, se elimina
    while (usuarios[i] != nullptr) {
        if (usuarios[i]->getId() == u->getId()) {
            delete usuarios[i];
            usuarios[i] = nullptr;
            break;
        }
        i++;
    }

    //se reacomoda el vector de usuarios para que no afecte a la logica
    for (int j = i; j < 8; j++) {
        if (usuarios[j + 1] != nullptr) {
            usuarios[j] = usuarios[j + 1];
        }
        else {
            usuarios[j] = nullptr;
        }
    }
    usuarios[9] = nullptr;

    return usuarios;
}

void prestarMaterial(MaterialBibliografico** materiales,Usuario** usuarios, MaterialBibliografico* m, Usuario* u) {
    /*Funcion que gestiona la logica para prestar un material

    @param usuarios: puntero hacia un vector de punteros de tipo Usuario
    @param u: usuario que pidio el libro
    @param materiales: puntero hacia un vector de punteros de tipo materialBibliografico
    @param m: material que pidio el usuario
    */
    

    //si el material esta prestado no puede prestarse
    if (buscarMaterialI(materiales, m->getIsbn())->getPrestado()) {
        cout << "El material esta prestado en estos momentos, lo sentimos" << endl;
    }

    //en caso de no estarlo, se presta y se setea el atributo prestado del material el true
    else {
        buscarMaterialI(materiales, m->getIsbn())->setPrestado(true);
        buscarUsuario(usuarios, u->getId())->prestarMaterial(m);
    }
    
}

void devolverMaterial(MaterialBibliografico** materiales, Usuario** usuarios, MaterialBibliografico* m, Usuario* u) {
    /*Funcion que gestiona la logica para devolver un material

    @param usuarios: puntero hacia un vector de punteros de tipo Usuario
    @param u: usuario que pidio el libro
    @param materiales: puntero hacia un vector de punteros de tipo materialBibliografico
    @param m: material que pidio el usuario
    */

    
    bool aux = false;
    //recorre los materiales prestados del usuario, lo elimina de los materiales prestados 
    //del usuario y setea el atributo prestado del material en false
    for (int i = 0; i < 5; i++) {
        if (u->getMaterialesPrestados()[i] != nullptr) {
            if (u->getMaterialesPrestados()[i]->getIsbn() == m->getIsbn()) {
                aux = true;
                buscarMaterialI(materiales, m->getIsbn())->setPrestado(false);
                buscarUsuario(usuarios, u->getId())->devolverMaterial(m);
                break;
            }
        }
        else {
            break;
        }
        
    }//en caso de que el libro no se encuentre entre los materiales prestados del usuario, se indica
    if (aux == false) {
        cout << "El usuario no posee el libro" << endl;
    }
}

static void LiberarMemoria(MaterialBibliografico** materiales, Usuario** usuarios) {
    /*Funcion que destruye todos los objetos creados en tiempo de ejecucion

    @param usuarios: puntero hacia un vector de punteros de tipo Usuario
    @param materiales: puntero hacia un vector de punteros de tipo materialBibliografico
    */
    
    //recorre todos los materiales y los destruye
    int i = 0;
    while (materiales[i] != nullptr && i<100) {
        delete materiales[i];
        materiales[i] = nullptr;
        i++;
    }

    //recorre todos los usuarios y los destruye
    i = 0;
    while (usuarios[i] != nullptr && i < 10) {
        delete usuarios[i];
        usuarios[i] = nullptr;
        i++;
    }

}

int main() {

    

    //Se crea un puntero hacia punteros de tipo materialBibliografico, esto se usara luego 
    // para dirigirlo a un vector de punteros de tipo MaterialBibliografico.
    MaterialBibliografico** materiales;
    //se leen los materiales del archivo material.txt
    materiales = leerMateriales("material.txt");

    //se repite el proceso con los usuarios.
    Usuario** usuarios;
    usuarios = leerUsuarios("usuarios.txt", materiales);


    //Se crea un menu para seleccionar el usuario que usara el sistema
    cout << "Seleccione un usuario\n" << endl;
    listarUsuarios(usuarios);
    cout << endl;

    //este while es quien recibe el numero del usuario seleccionado
    int z;
    while (true) {
        int indice;
        cin >> indice;
        //en caso de que el indice aportado por el usuario no sea un numero entrara 
        //en un while pidiendo entradas hasta que corresponda a un numero
        while (cin.fail()) {
            cout << "Solo puede ingresar numeros." << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cin >> indice;
            cin.clear();
        }
        //revisa que el usuario asociado al indice indicado exista y se almacena el 
        // indice en una variable z que usaremos de ahora en adelante para acceder al usuario
        if (usuarios[indice - 1] != nullptr) {
            z = indice - 1;
            cout << "" << endl;
            break;
        }//en caso de que no exista se indica y termian el programa
        else {
            cout << "Al parecer no hay ningun usuario asociado a esa entrada." << endl;
        }
    }


    //Inicia el ciclo correspondiente al segundo menu,
    //este menu consulta las acciones que desea llevar a 
    //cabo el usuario seleccionado anteriormente
    cout << usuarios[z]->getNombre() << "; ¿Que desea hacer? (seleccione un numero)\n" << endl;
    
    while (true) {

        cout << "\n(1) Agregar un material." << endl;
        cout << "(2) Agregar un Usuario." << endl;
        cout << "(3) Prestar un material." << endl;
        cout << "(4) Devolver un material." << endl;
        cout << "(5) Listar materiales." << endl;
        cout << "(6) Listar materiales prestados." << endl;
        cout << "(7) Buscar material." << endl;
        cout << "(8) Listar Usuarios." << endl;
        cout << "(9) Eliminar un Usuario.\n" << endl;
        cout << "(0) Salir del sistema\n" << endl;


        //se exige un indice tal cual como en el caso anterior con los usuarios
        int indice;
        cin >> indice;
        while (cin.fail()) {
            cout << "Solo puede ingresar numeros." << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cin >> indice;
            cin.clear();
        }


        //se declaran diferentes variables auxiliares que seran utiles mas adelante
        string nombreAux, autorAux, mesPublicacionAux, fechaPublicacionAux, resumenAux;
        MaterialBibliografico* mAux;
        bool aux;
        int edicionAux;
        long long int isbnAux;
        long int idAux;
        int i = 0;
        int j = 0;

        //un switch que en funcion del indice que reciba ejecutara la accion.
        switch (indice)
        {
        case 1:
            //primer caso; agregar un material bibliografico

            cout << "\n(1) Agregar un material.\n" << endl;
            cout << "Libro (0) o Revista(1)" << endl;
            //primero consultamos si se agregara una revista o un libro
            // pidiendo un 1 para libro y un 0 para revista
            cin >> aux;
            //while que se preocupa de que la entrada sea coherente
            while (cin.fail()) {
                cout << "Solo puede ingrear un 1 o 0." << endl;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cin >> aux;
            }
            cin.clear();//limpiamos cin
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

            //pedimos el nombre del material
            cout << "Ingrese el nombre: " << endl;
            getline(cin, nombreAux);

            //pedimos el autor del material
            cout << "Ingrese el autor: " << endl;
            getline(cin, autorAux);

            //pedimos el codigo isbn del material
            cout << "Ingrese el ISBN: " << endl;
            cin >> isbnAux;
            //while que se preocupa de que la entrada sea coherente
            while (cin.fail()) {
                cout << "Solo puede ingrear numeros." << endl;
                cin.clear();//limpiamos cin
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cin >> isbnAux;
            }

            //Consultamos el valor de aux para saber si es un libro o una revista
            if (aux) {
                //en caso de ser una revista pedimos el numero de edicion
                cout << "Ingrese el numero de edicion: " << endl;
                cin >> edicionAux;
                //while que se preocupa de que la entrada sea coherente
                while (cin.fail()) {
                    cout << "Solo puede ingresar numeros." << endl;
                    cin.clear();//limpiamos cin
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cin >> edicionAux;
                }
                cin.clear();//limpiamos cin
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                
                //pedimos el mes de publicacion
                cout << "Ingrese el mes de publicacion: " << endl;
                getline(cin, mesPublicacionAux);

                //e instanciamos el material bibliografico en base al constructor Revista
                MaterialBibliografico* r = new Revista(nombreAux, autorAux, to_string(isbnAux), 0, edicionAux, mesPublicacionAux);

                cout << "Se ha agregado: " << endl;
                r->mostrarInformacion();


                //agregamos el material al vector de materiales;
                materiales = agregarMaterial(materiales, r);
                cout << "" << endl;
            }
            //en caso de que aux indique que es un libro
            else {
                cin.clear();//limpiamos cin
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

                //pedimos la fecha de publicacion
                cout << "Ingrese la fecha de publicacion: " << endl;
                getline(cin, fechaPublicacionAux);

                //pedimos un breve resumen
                cout << "Ingrese un breve resumen: " << endl;
                getline(cin, resumenAux);
                cin.clear();

                //y en este caso instanciamos un material bibliografico con el constructor Libro
                MaterialBibliografico* l = new Libro(nombreAux, autorAux, to_string(isbnAux), 0, fechaPublicacionAux, resumenAux);

                cout << "Se ha agregado: " << endl;
                l->mostrarInformacion();

                //por ultimo agregamos el material al vector
                materiales = agregarMaterial(materiales, l);
                cout << "" << endl;
            }

            //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
            break;
            
        case 2:
            //segundo caso; agregar un usuario
            cout << "\n(2) Agregar un Usuario.\n" << endl;

            cin.clear();//limpiamos cin
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

            //pedimos el nombre del usuario
            cout << "Ingrese el nombre: " << endl;
            getline(cin, nombreAux);

            //pedimos el numero de id
            cout << "Ingrese el numero de ID: " << endl;
            cin >> idAux;
            //while encargado de que solo se ingresen numero
            while (cin.fail()) {
                cout << "Solo puede ingresar numeros." << endl;
                cin.clear();//se limpia el cin
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cin >> idAux;
            }
            //agregamos el nuevo usuario al vector usuarios
            agregarUsuario(usuarios, nombreAux, idAux);

            //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
            break;


        case 3:
            //tercer caso; prestar un material

            cout << "\n(3) Prestar material.\n" << endl;

            //pedimos el codigo del libro que desea prestar
            cout << usuarios[z]->getNombre() << "; Ingrese el codigo del libro: ";
            cin >> isbnAux;
            //while encargado de que la entrada sea valida
            while (cin.fail()) {
                cout << "Solo puede ingresar numeros." << endl;
                cin.clear();//se limpia cin
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cin >> isbnAux;
                cin.clear();
            }

            //buscamos el material correspondiente al isbn recibico, se comprueba que exista y que no 
            //haya sido prestado para llamar a la funcion prestarMaterial, caso contrario se indica que el libro no esta disponible
            mAux = buscarMaterialI(materiales, to_string(isbnAux));
            if (mAux != nullptr) {
                if (!mAux->getPrestado()) {
                    prestarMaterial(materiales, usuarios, mAux, usuarios[z]);
                }
                else {
                    cout << "El material: " << mAux->getNombre() << " no esta dispoible" << endl;
                }

                //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
                break;
            }
            //en caso de que no se encuentre el material se indica
            else {
                cout << "No se encontro el material con el codigo: " << isbnAux << endl;

                //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
                break;
            }

        case 4:
            //cuarto caso; devolver un material
            i = 0;
            cout << "\n(4) Devolver Material.\n" << endl;
            //mostramos por pantalla todos los libros que posee el usuario
            while (usuarios[z]->getMaterialesPrestados()[i] != nullptr && i < 5) {
                usuarios[z]->getMaterialesPrestados()[i]->MaterialBibliografico::mostrarInformacion();
                cout << "" << endl;
                i++;
            }

            //pedimos el isbn del libro que desea devolver
            cout << usuarios[z]->getNombre() << "; Ingrese el codigo del libro: ";
            cin >> isbnAux;
            //while encargado de que se ingrese una entrada coherente
            while (cin.fail()) {
                cout << "Solo puede ingresar numeros." << endl;
                cin.clear();//limpiamos cin
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cin >> isbnAux;
                cin.clear();
            }

            //buscamos el material en funcion del isbn recibido, comprobamos que exista y lo devolvemos
            mAux = buscarMaterialI(materiales, to_string(isbnAux));
            if (mAux != nullptr) {
                devolverMaterial(materiales, usuarios, mAux, usuarios[z]);
                //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
                break;
            }
            else {// en caso de no encontrarse el material, se indica
                cout << "No se encontro el material con el codigo: " << isbnAux << endl;

                //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
                break;
            }

            //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
            break;

        case 5:
            //quinto caso: Listar los materiales que posee la biblioteca
            cout << "\n(5) Listar Materiales.\n" << endl;
            //se llama a la funcion listarMateriales
            listarMateriales(materiales);

            //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
            break;


        case 6:
            //sexto caso: listar los materiales que posee el usuario
            cout << "\n(6) Listar Materiales Prestados.\n" << endl;
            //se llama al metodo de la clase usuarios mostrarMaterialesPrestados 
            usuarios[z]->mostrarMaterialesPrestados();

            //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
            break;


        case 7:
            //septimo caso: Buscar un material

            cout << "\n(7) Buscar material.\n" << endl;

            //debido a que hay 2 metodos para buscarlo (disponibles para el usuario)
            //Se crea un submenu para que seleccione una opcion
            cout << usuarios[z]->getNombre() << "; ¿Como desea buscarlo? (seleccione un numero)\n" << endl;
            while (true) {
                cout << "(1) Busqueda por nombre." << endl;
                cout << "(2) Busqueda por autor.\n" << endl;
                cout << "(0) Volver.\n" << endl;
                //pedimos el indice
                cin >> indice;
                //while encargado de que el indice sea valido
                while (cin.fail()) {
                    cout << "Solo puede ingresar numeros." << endl;
                    cin.clear();//limpiamos cin
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cin >> indice;
                    cin.clear();
                }

                //swithc en funcion del indice recibido
                switch (indice)
                {
                case 1:
                    //en primer caso buscaremos el material en funcion del nombre del libro
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Indique el titulo que busca:" << endl;
                    getline(cin, nombreAux);
                    buscarMaterialT(materiales, nombreAux);
                    break;

                case 2:
                    //en segundo caso buscaremos el material en funcion del autor
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Indique el autor que busca:" << endl;
                    getline(cin, autorAux);
                    buscarMaterialA(materiales, autorAux);
                    break;

                case 0:
                    //en tercer caso se quiebra el switch
                    break;
                default:
                    break;
                }
                if (!indice) {
                    break;
                }
            }

            //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
            break;
            

        case 8:
            //octavo caso: listar usuarios
            cout << "\n(8) Listar Usuarios.\n" << endl;
            //se llama a la funcion listarUsuarios
            listarUsuarios(usuarios);

            //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
            break;

        case 9:
            //noveno caso; Eliminar un usuario
            cout << "\n(79) Eliminar un Usuario.\n" << endl;
            //listamos los usuarios disponibles para eliminar e indicamos que si se elimina el usuario actual, el programa se cierra
            cout << "Seleccione el usuario a eliminar\nNota: Si elimina el usuario actual, se cerrara automaticamente el programa\n" << endl;
            listarUsuarios(usuarios);
            while (true) {
                int indice;
                //pedimos el indice del usuario que se desea eliminar
                cin >> indice;
                //while encargado de que la entrada sea coherente
                while (cin.fail()) {
                    cout << "Solo puede ingresar numeros." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cin >> indice;
                    cin.clear();
                }

                if (usuarios[indice - 1] != nullptr) {
                    j = indice - 1;
                    cout << "" << endl;
                }
                else {
                    cout << "Al parecer no hay ningun usuario asociado a esa entrada." << endl;
                }
                //Si el usuario actual es igual al usuario que se selecciono, se elimina y a su vez se cierra el programa
                if (j == z) {
                    usuarios = eliminarUsuario(usuarios, usuarios[j]);
                    LiberarMemoria(materiales, usuarios);
                    escribirMaterial(materiales, "material.txt");
                    escribirUsuarios(usuarios, "usuarios.txt");
                    return 0;
                }//en caso contrario simplemente se elimina el usuario
                else {
                    usuarios = eliminarUsuario(usuarios, usuarios[j]);

                    //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
                    break;
                }


            }

            //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
            break;

        case 0:
            //decimo caso; se cierra el programa, se escriben los materiales y los usuarios en sus correspondientes archivos 
            // y se libera la memoria 

            escribirMaterial(materiales, "material.txt");
            escribirUsuarios(usuarios, "usuarios.txt");
            LiberarMemoria(materiales, usuarios);
            return 0;
            break;

        default:
            cout << "El indice no correspondia a ninguna opcion, intentelo denuevo" << endl;

            //Se quiebra el switch de manera que empieza un nuevo ciclo while para ejecutar una nueva accion
            break;

        }

    }
    LiberarMemoria(materiales, usuarios);
    return 0;

}



