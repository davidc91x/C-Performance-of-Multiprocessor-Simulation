#include "Proceso.hh"
#ifndef NO_DIAGRAM

#include <iostream>
#endif
using namespace std;

Proceso::Proceso(){
    ide=memo=tiempo=0;
}

Proceso::Proceso(int i, int m, int t){
    ide=i;
    memo=m;
    tiempo=t;
}


void Proceso::restar_tiempo_proceso(const int& t){
    tiempo=tiempo-t;
}


int Proceso::tiempoproceso() const{
    return tiempo;
}

int Proceso::memoriaproceso() const{
    return memo;
}

int Proceso::idproceso() const{
    return ide;
}

void Proceso::leer_proceso() {
    cin>>ide>>memo>>tiempo;
}

void Proceso::escribirproceso() const {
    cout<<ide<<' '<<memo<<' '<<tiempo<<'\n';
}
