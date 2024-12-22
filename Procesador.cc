#include "Proceso.hh"
#include "Procesador.hh"
#ifndef NO_DIAGRAM
#include <map>
#include <string>
#include <iostream>
#endif
using namespace std;

Procesador::Procesador(){
    espaciol=mem=0;
}

Procesador::Procesador(int memo){
    espaciol=mem=memo;
    espacioslibres[mem].insert(0);
}
void Procesador::assignarnivel(int niv){
    ni=niv;
}

void Procesador::assignarizq(string s){
    iz=s;
}

void Procesador::añadir_proceso(const Proceso& p, int pos, int tam){
    espacios[pos] = p;
    mapa2[p.idproceso()]=pos;
    espaciol=espaciol-p.memoriaproceso();
    if(tam-p.memoriaproceso()>0) espacioslibres[tam-p.memoriaproceso()].insert(pos+p.memoriaproceso());
    espacioslibres[tam].erase(pos);
    if(espacioslibres[tam].empty()) espacioslibres.erase(tam);
}

bool Procesador::huecoajustado(int memo, int& pos, int& tam) const{
     // if(espaciol<memo) return false;
     map<int,set<int>>::const_iterator it=espacioslibres.lower_bound(memo);
     if(it!=espacioslibres.end()) {
         tam=(it)->first;
        pos=*(it->second.begin());
        return true;
    }
    else return false;
}

bool Procesador::buscarProceso(int i) const{
    return mapa2.find(i)!=mapa2.end();
}


void Procesador::quitar_proceso(int s, string r,const string& comando) {
    try {
         map<int,Proceso>::iterator it1=espacios.find(mapa2.at(s));
         cout<<'#'<<comando<<' '<<r<<' '<<s<<'\n';
        espaciol=espaciol+it1->second.memoriaproceso();
        int pos,tam;
        pos=it1->first;
        tam=it1->second.memoriaproceso();
        if(it1==espacios.begin() and it1->first>0 ) {
            espacioslibres[it1->first].erase(0);
            if(espacioslibres[it1->first].empty()) espacioslibres.erase(it1->first);
            tam=tam+it1->first;
            pos=0;
        }
        else if(it1!=espacios.begin()) {
            map<int,Proceso>:: iterator it2=it1;
            --it2;
            if(-((it2)->first+it2->second.memoriaproceso())+(it1)->first>0){
             espacioslibres[-((it2)->first+it2->second.memoriaproceso())+(it1)->first].erase(it2->first+it2->second.memoriaproceso());
            if(espacioslibres[-((it2)->first+it2->second.memoriaproceso())+(it1)->first].empty()) espacioslibres.erase(-((it2)->first+it2->second.memoriaproceso())+(it1)->first);
            tam=tam-((it2)->first+it2->second.memoriaproceso())+(it1)->first;

            pos=(it2->first+it2->second.memoriaproceso());
        }}
        if(it1==(--espacios.end()) and it1->first+it1->second.memoriaproceso()<mem) {
            espacioslibres[mem-(it1->first+it1->second.memoriaproceso())].erase(it1->first+it1->second.memoriaproceso());
            if(mem-(it1->first+it1->second.memoriaproceso())) espacioslibres.erase(mem-(it1->first+it1->second.memoriaproceso()));
            tam=tam+mem-(it1->first+it1->second.memoriaproceso());
        }

        else if(it1!=(--espacios.end())) {
            map<int,Proceso>:: iterator it2=it1;
            ++it2;
            if(-(it1->first+it1->second.memoriaproceso())+(it2)->first>0) {
            espacioslibres[-(it1->first+it1->second.memoriaproceso())+(it2)->first].erase((it1)->first+it1->second.memoriaproceso());
            if(espacioslibres[-(it1->first+it1->second.memoriaproceso())+(it2)->first].empty()) espacioslibres.erase(-(it1->first+it1->second.memoriaproceso())+(it2)->first);

            tam=tam-(it1->first+it1->second.memoriaproceso())+(it2)->first;
        }}
        espacioslibres[tam].insert(pos);


         it1=espacios.erase(it1);
         mapa2.erase(s);

    } catch (const out_of_range& e) {
        cout<<'#'<<comando<<' '<<r<<' '<<s<<'\n'<<"error: no existe proceso"<<'\n';
    }


}


void Procesador::leer_procesador(){
    cin>>mem;
    espaciol=mem;
    espacioslibres[mem].insert(0);
}

void Procesador::avanzartprocesador(const int& t){
    map<int, Proceso>::iterator it1=espacios.begin();
    while(it1!=espacios.end()) {
        it1->second.restar_tiempo_proceso(t);
        if(it1->second.tiempoproceso()<=0){
         int pos,tam;
        pos=it1->first;
        tam=it1->second.memoriaproceso();
        if(it1==espacios.begin() and it1->first>0 ) {
            espacioslibres[it1->first].erase(0);
            if(espacioslibres[it1->first].empty()) espacioslibres.erase(it1->first);
            tam=tam+it1->first;
            pos=0;
        }
        else if(it1!=espacios.begin()) {
            map<int,Proceso>:: iterator it2=it1;
            --it2;
            if(-((it2)->first+it2->second.memoriaproceso())+(it1)->first>0){
             espacioslibres[-((it2)->first+it2->second.memoriaproceso())+(it1)->first].erase(it2->first+it2->second.memoriaproceso());
            if(espacioslibres[-((it2)->first+it2->second.memoriaproceso())+(it1)->first].empty()) espacioslibres.erase(-((it2)->first+it2->second.memoriaproceso())+(it1)->first);
            tam=tam-((it2)->first+it2->second.memoriaproceso())+(it1)->first;

            pos=(it2->first+it2->second.memoriaproceso());
        }}
        if(it1==(--espacios.end()) and it1->first+it1->second.memoriaproceso()<mem) {
            espacioslibres[mem-(it1->first+it1->second.memoriaproceso())].erase(it1->first+it1->second.memoriaproceso());
            if(mem-(it1->first+it1->second.memoriaproceso())) espacioslibres.erase(mem-(it1->first+it1->second.memoriaproceso()));
            tam=tam+mem-(it1->first+it1->second.memoriaproceso());
        }

        else if(it1!=(--espacios.end())) {
            map<int,Proceso>:: iterator it2=it1;
            ++it2;
            if(-(it1->first+it1->second.memoriaproceso())+(it2)->first>0) {
            espacioslibres[-(it1->first+it1->second.memoriaproceso())+(it2)->first].erase((it1)->first+it1->second.memoriaproceso());
            if(espacioslibres[-(it1->first+it1->second.memoriaproceso())+(it2)->first].empty()) espacioslibres.erase(-(it1->first+it1->second.memoriaproceso())+(it2)->first);

            tam=tam-(it1->first+it1->second.memoriaproceso())+(it2)->first;
        }}
        espacioslibres[tam].insert(pos);
            espaciol=espaciol+it1->second.memoriaproceso();
            mapa2.erase(it1->second.idproceso());
            it1=espacios.erase(it1);
        }
        else if(it1!=espacios.end()) ++it1;
    }
}


void Procesador::escribirprocesador() const{
    for (map<int,Proceso>::const_iterator it = espacios.begin(); it != espacios.end(); ++it) {
        cout << it->first << " ";
        it->second.escribirproceso();
}
}

int Procesador::nivel() const{
    return ni;
}
string Procesador::izquierda() const{
    return iz;
}
int Procesador::espaciolibre() const{
    return espaciol;
}

bool Procesador::empty() const{
    return espacios.empty();
}

void Procesador::compact(){
    if(not espacios.empty()){
        map<int, Proceso>::iterator it=espacios.begin();

        if(it->first!=0){
            espacios.emplace(0,it->second);
            mapa2[it->second.idproceso()]=0;
            it=espacios.erase(it);
        }
        it=espacios.begin();
        map<int, Proceso>::iterator it2=it;
        if(it2!=espacios.end()) ++it2;
        while(it2!=espacios.end()){
            if(it2->first!=it->first+it->second.memoriaproceso()){
                espacios.emplace(it->first+it->second.memoriaproceso(),it2->second);
                mapa2[it2->second.idproceso()]=it->first+it->second.memoriaproceso();
                it2=espacios.erase(it2);
                ++it;
            }
            else if(it2!=espacios.end()){
                ++it;
                ++it2;
            }
        }
        espacioslibres.clear();
        espacioslibres[mem-(it->first+it->second.memoriaproceso())].insert(it->first+it->second.memoriaproceso());
    }
}
