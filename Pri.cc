#include "Pri.hh"
#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <map>
#include <list>
#include <iostream>
#endif
using namespace std;

Pri::Pri(){
    colocados=0;
    rechazos=0;
}


void Pri::incrementarcolocados(){
    ++colocados;
}

void Pri::incrementarrechazos(){
    ++rechazos;
}

bool Pri::push(const Proceso& p){
    set<int>::iterator it=seta.find(p.idproceso());
    if(it!=seta.end()) return false;
    seta.insert(p.idproceso());
    lista.push_back(p);
    return true;

}

bool Pri::pop(){
    if (not lista.empty()) {
        seta.erase(lista.front().idproceso());
        lista.pop_front();
        return true;
    }
    else return false;
}

void Pri::juntarprocesos(Pri b){
    while(not b.empty()) {
    seta.insert(b.front().idproceso());
    lista.push_back(b.front());
    b.pop();
    }
}

bool Pri::empty() const{
    return seta.empty();
}

Proceso  Pri::front() const {
    return lista.front();
}


void Pri::escribirPri() const{
    list<Proceso>::const_iterator it=lista.begin();
    while(it!=lista.end()) {
        (*it).escribirproceso();
        ++it;
    }
    cout<<colocados<<' '<<rechazos<<'\n';
}

