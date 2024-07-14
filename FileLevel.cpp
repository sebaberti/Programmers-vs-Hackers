#include <cstdio>
#include <iostream>
#include <cstring>
#include "FileLevel.h"

void cargarCadena(char* pal, int tam) {
    int i;
    fflush(stdin); ///limpia el buffer de entrada para que la carga se haga sin caracteres que hayan quedado sin usar
    for (i = 0; i < tam;i++) {
        pal[i] = std::cin.get();
        if (pal[i] == '\n')break;
    }
    pal[i] = '\0';
    fflush(stdin); ///vuelve a limpiar el buffer para eliminar los caracteres sobrantes
}

int Levels::getId() const { return _id; }
std::string Levels::getName() const { return _name; }
bool Levels::getStatus() const { return _status; }
void Levels::setId(int i) { _id = i; }
void Levels::setStatus(bool s) { _status = s; }

void Levels::Cargar(int i) {
    std::cout << "NOMBRE: ";
    cargarCadena(_name, 39);
    _id=i;
    i == 0 ? _status = true : _status = false;
}

void Levels::Mostrar() {
    std::cout << "NOMBRE: " << _name << std::endl;
    std::cout << "ID: " << _id << std::endl;
    std::cout << "ESTADO: " << _status << std::endl << std::endl;
}

//LEER EL ARCHIVO
Levels FileLevels::read(int pos) {
    Levels reg;
    FILE* p;
    fopen_s(&p, name, "rb");
    if (p != nullptr) {
        fseek(p, pos * sizeof reg, 0);
        fread(&reg, sizeof reg, 1, p);
        fclose(p);
        return reg;
    }
    else {
        reg.setId(-1);
        return reg;
    }
}

//GUARDAR EL ARCHIVO - AGREGA REGISTROS
void FileLevels::save(Levels reg) {
    FILE* p;
    fopen_s(&p, name, "ab");
    if (p != nullptr) {
        fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
    }
    else return;
}

//MODIFICAR EL ARCHIVO
void FileLevels::edit(Levels& reg, int pos) {
    FILE* p;
    fopen_s(&p, name, "rb+");
    if (p != nullptr) {
        fseek(p, pos * sizeof(Levels), 0);
        fwrite(&reg, sizeof(Levels), 1, p);
        fclose(p);
    }
    else return;
}



void FileLevels::reset() {
    Levels reg;
    FILE* p;
    fopen_s(&p, name, "rb+");
    if (p != nullptr) {
        int pos = 0;        
        for (int i = 0; i < 5; i++) {
            fread(&reg, sizeof(Levels), 1, p);
            if (reg.getId() > 0) {  //resetea todos menos el primero
                reg.setStatus(false);
            }
                fseek(p, pos * sizeof(Levels), SEEK_SET); // Mover el puntero del archivo a la posición correcta
                fwrite(&reg, sizeof(Levels), 1, p);
                // Volver a mover el puntero para la próxima lectura
                fseek(p, (pos + 1) * sizeof(Levels), SEEK_SET);

            pos++;
        }
        fclose(p);
    }
    
}

