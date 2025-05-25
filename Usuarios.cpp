#include "Header.h"

Usuario::Usuario(string nombre, string clave, bool root)
{
    this -> nombre = nombre;
    this -> clave = clave;
    esRoot = root;
}

Usuario::Usuario() : nombre(""), clave(""), esRoot(false) {}

Usuario CrearUsuarioRoot() 
{
    string nombre, clave;
    cout << "---- Creando Usuario Root ----\n";

    cout << "Ingese el nombre: ";
    getline(cin, nombre);
    cout << "Ingese el la contraseña: ";
    getline(cin, clave);

    Usuario UsuarioRoot(nombre, clave, true);

    return UsuarioRoot;
}

Usuario CrearUsuario() 
{
    string nombre, clave;
    cout << "\n---- Creando Usuario ----\n";

    cout << "Ingese el nombre: ";
    getline(cin, nombre);
    cout << "Ingese el la contraseña: ";
    getline(cin, clave);

    Usuario UsuarioNormal(nombre, clave, false);

    return UsuarioNormal;
}