#pragma once
#include <cstdio>
#include <iostream>
#include <cstring>

class Levels {
private:
	int _id;
	char _name[40];
	bool _status;
public:
    int getId() const;
    std::string getName() const;
    bool getStatus() const;
    void setId(int i);
    void setStatus(bool s);
    void Cargar(int i);
    void Mostrar();
};

class FileLevels {
private:
    char name[20]= "unlockedLevels.dat";
public:
    Levels read(int);
    void save(Levels);
    void edit(Levels&, int);
    void reset();
};



