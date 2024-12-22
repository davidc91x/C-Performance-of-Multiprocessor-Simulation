
#include "funciones.hh"
#include "Procesador.hh"
#include "Proceso.hh"
#include "Pri.hh"
#include "BinTree.hh"
#ifndef NO_DIAGRAM
#include <map>
#include <string>
#include <set>
#include <iostream>
#endif
using namespace std;
typedef BinTree<string> clu;
typedef map<string,Pri> Area;
// Vaig decidir no crear classes de cluster i area d'espera ja que utilitzen només 1 o 2 tipus de dades i no em semblava suficients. El que em va semblar més apropiat va ser crear un document per a les funcions i no embrutar el main // del programa. A continuació es troban primer les funcions respectives a l'area d'espera, després les respectives al cluster i per últim la de enviar procesos al cluster que es respectiva als dos.

void alta_prioridad(Area& areap,const string& comando){
    string s;
    cin>>s;
        //lo mismo que areap.insert(make_pair(s, Pri())); pero sin crear el par para ver si baja eficiencia
    map<string, Pri>::iterator it = areap.find(s);
    if(it!=areap.end()) cout<<'#'<<comando<<' '<<s<<'\n' << "error: ya existe prioridad" << '\n';
    else{
        areap.emplace(s,Pri());
        cout<<'#'<<comando<<' '<<s<<'\n';
    }
}

void alta_prioridad2(Area& areap, const string& s){
    areap.emplace(s, Pri());
}

void baja_prioridad(Area& areap, const string& comando){
    string s;
    cin>>s;
    map<string,Pri>::iterator it=areap.find(s);
    if(it==areap.end()) cout<<'#'<<comando<<' '<<s<<'\n'<<"error: no existe prioridad"<<'\n';
    else if((it->second).empty()){
        areap.erase(it);
        cout<<'#'<<comando<<' '<<s<<'\n';
    }
    else cout<<'#'<<comando<<' '<<s<<'\n'<<"error: prioridad con procesos"<<'\n';
}

void alta_proceso_espera(Area& areap,const string& comando){
    string s;
    cin>>s;
    Proceso p;
    p.leer_proceso();
    map<string,Pri>::iterator it=areap.find(s);
    if(it==areap.end()) cout<<'#'<<comando<<' '<<s<<' '<<p.idproceso()<<'\n'<<"error: no existe prioridad"<<'\n';
    else {
        if(areap[s].push(p)==false) cout<<'#'<<comando<<' '<<s<<' '<<p.idproceso()<<'\n'<<"error: ya existe proceso"<<'\n';
        else cout<<'#'<<comando<<' '<<s<<' '<<p.idproceso()<<'\n';
    }
}

void imprimir_prioridad(const Area& areap, const string& comando) {
    string s;
    cin>>s;
    map<string,Pri>::const_iterator it=areap.find(s);
    if(it==areap.end()) cout<<'#'<<comando<<' '<<s<<'\n'<<"error: no existe prioridad"<<'\n';
    else {
        cout<<'#'<<comando<<' '<<s<<'\n';
        it->second.escribirPri();
    }
}

void imprimir_area_espera(const Area& areap) {
    map<string,Pri>::const_iterator it=areap.begin();
    while(it!=areap.end()) {
        cout<<it->first<<'\n';
        it->second.escribirPri();
        ++it;
    }
}

void configurar_cluster(clu& Cluster, map<string,Procesador>& pr, int ni, string i){
    string s;
    cin>>s;
    if(s!="*") {
        int n;
        cin>>n;
        Procesador p(n);
        p.assignarnivel(ni);
        p.assignarizq(i);
        pr.emplace(s,p);
        clu l,r;
        configurar_cluster(l,pr,ni+1,i+'0');
        configurar_cluster(r,pr,ni+1,i+'1');
        Cluster=clu(s,l,r);
    }
    // Cluster=clu();
}

void modificarrecursivo(clu& Cluster, map<string,Procesador>& pr,const string& s, int ni, string iz,const string& comando){
    if(not Cluster.empty()) {
        clu l=Cluster.left();
        clu r=Cluster.right();
        if(Cluster.value()==s){
            if(not r.empty() or not l.empty()){
                cout<<'#'<<comando<<' '<<s<<'\n'<<"error: procesador con auxiliares"<<'\n';
                Cluster=clu(Cluster.value(), l,r);
            }
            else{
                cout<<'#'<<comando<<' '<<s<<'\n';
                clu a;
                map<string,Procesador> b;
                configurar_cluster(a,b,ni,iz);
                Cluster=clu(a);
                pr.erase(s);
                pr.insert(b.begin(), b.end());
            }
        }
        else {
            modificarrecursivo(l,pr,s,ni,iz,comando);
            modificarrecursivo(r,pr,s,ni,iz,comando);
            Cluster=clu(Cluster.value(), l,r);
        }
    }
}

void modificar_cluster(clu& Cluster, map<string,Procesador>& pr,const string& comando){
    string s;
    cin>>s;
    map<string,Procesador>::iterator it=pr.find(s);
    if(it==pr.end()) cout<<'#'<<comando<<' '<<s<<'\n'<<"error: no existe procesador"<<'\n';
    else if(not it->second.empty()) cout<<'#'<<comando<<' '<<s<<'\n'<<"error: procesador con procesos"<<'\n';
    else modificarrecursivo(Cluster,pr,s,it->second.nivel(),it->second.izquierda(),comando);
    }


void alta_proceso_procesador(map<string,Procesador>& pr,const string& comando) {
    string s;
    cin>>s;
    map<string,Procesador>::iterator it=pr.find(s);
    Proceso p;
    p.leer_proceso();

    if(it==pr.end()) cout<<'#'<<comando<<' '<<s<<' '<<p.idproceso()<<'\n'<<"error: no existe procesador"<<'\n';
    else {
        if(it->second.buscarProceso(p.idproceso())) cout<<'#'<<comando<<' '<<s<<' '<<p.idproceso()<<'\n'<<"error: ya existe proceso"<<'\n';
        else {
            int pos,tam;
            if(it->second.huecoajustado(p.memoriaproceso(),pos,tam)) {
                cout<<'#'<<comando<<' '<<s<<' '<<p.idproceso()<<'\n';
                it->second.añadir_proceso(p,pos,tam);
            }
            else cout<<'#'<<comando<<' '<<s<<' '<<p.idproceso()<<'\n'<<"error: no cabe proceso"<<'\n';
        }
    }
}


void baja_proceso_procesador(map<string,Procesador>& pr, const string& comando){
    string s;
    int r;
    cin>>s>>r;
    map<string,Procesador>::iterator it;
    it=pr.find(s);
    if(it==pr.end()) cout<<'#'<<comando<<' '<<s<<' '<<r<<'\n'<<"error: no existe procesador"<<'\n';
    else it->second.quitar_proceso(r,s,comando);
}


void avanzar_tiempo(map<string,Procesador>& pr, const int& t){
for(map<string,Procesador>::iterator it=pr.begin(); it!=pr.end(); ++it) it->second.avanzartprocesador(t);
}


void imprimir_procesador(const map<string,Procesador>& pr, const string& comando){
    string s;
    cin>>s;
    map<string,Procesador>::const_iterator it=pr.find(s);
    if(it==pr.end()) cout<<'#'<<comando<<' '<<s<<'\n'<<"error: no existe procesador"<<'\n';
    else{
        cout<<'#'<<comando<<' '<<s<<'\n';
        it->second.escribirprocesador();
    }
}

void imprimir_procesadores_cluster(const map<string,Procesador>& pr){
   for(map<string,Procesador>::const_iterator it=pr.begin(); it!=pr.end(); ++it) {
        cout<<it->first<<'\n';
        it->second.escribirprocesador();
    }
}


// void imprimir_estructura_cluster(const clu& Cluster){
//     if(not Cluster.empty()) {
//         cout<<'('<<Cluster.value();
//         if(Cluster.left().empty()) cout<<' ';
//         else imprimir_estructura_cluster(Cluster.left());
//         if(Cluster.right().empty()) cout<<' ';
//         else imprimir_estructura_cluster(Cluster.right());
//         cout<<')';
//     }
// }
string imprimir_estructura_cluster(const clu& Cluster){
    if(not Cluster.empty()) {
        string s;
        s="("+Cluster.value();
        if(Cluster.left().empty()) s=s+" ";
        else s=s+imprimir_estructura_cluster(Cluster.left());
        if(Cluster.right().empty()) s=s+" ";
        else s=s+imprimir_estructura_cluster(Cluster.right());
        s=s+")";
        return s;
    }
    return "";
}



void compactar_memoria_procesador(map<string,Procesador>& pr){
    string s;
    cin>>s;
    cout<<' '<<s<<'\n';
    map<string,Procesador>::iterator it=pr.find(s);
    if(it==pr.end()) cout<<"error: no existe procesador"<<'\n';
    else it->second.compact();
}

void compactar_memoria_cluster(map<string,Procesador>& pr){
    for(map<string,Procesador>::iterator it=pr.begin();it!=pr.end();++it) it->second.compact();
    }




bool envio(map<string,Procesador>& pr, Proceso p){
    bool b=false;
    int mpos=0;
    int mtam=2147483647;
    int mespaciol=p.memoriaproceso()-1;
    int mnivel=2147483647;
    string mizquierda="2";
    map<string,Procesador>::iterator it=pr.begin();
    int tam,pos;
    map<string,Procesador>::iterator mit;
    while(it!=pr.end()){
        if(not it->second.buscarProceso(p.idproceso()) and it->second.huecoajustado(p.memoriaproceso(), pos,tam) and (tam<mtam or (tam==mtam and it->second.espaciolibre()>mespaciol) or (tam==mtam and it->second.espaciolibre()==mespaciol and it->second.nivel()<mnivel) or (tam==mtam and it->second.espaciolibre()==mespaciol and it->second.nivel()==mnivel and it->second.izquierda()<mizquierda) ) ) {
            mtam=tam;
            mpos=pos;
            mespaciol=it->second.espaciolibre();
            mnivel=it->second.nivel();
            mizquierda=it->second.izquierda();
            b=true;
            mit=it;
        }
        ++it;
    }
    if(not b) return b;
    else {

        mit->second.añadir_proceso(p,mpos,mtam);
        return b;
    }
}

void enviar_procesos_cluster(map<string,Procesador>& pr,Area& areap){
    int n;
    cin>>n;
    cout<<n<<'\n';
    int i=0;
    Pri b;
    map<string,Pri>::iterator it=areap.begin();
    while(i<n and it!=areap.end()) {
        if(not it->second.empty()){
            if(envio(pr,it->second.front())){
                ++i;
                it->second.incrementarcolocados();
            }
            else{
                b.push(it->second.front());
                it->second.incrementarrechazos();
            }
            it->second.pop();
        }
        if(it->second.empty() or i==n){
            it->second.juntarprocesos(b);
            b=Pri();
            ++it;
        }

}
}





