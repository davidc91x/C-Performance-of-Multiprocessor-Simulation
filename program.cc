/** @file main.cc
    @brief Programa principal de la practica.
*/


/** @mainpage Practica:  Simulacion del rendimiento de procesadores interconectados.

En esta practica se construye un programa modular que ofrece un menú de opciones para un Cluster de procesadores. Se introducen las clases <em>Procesador</em>, <em>Proceso</em> y <em>Pri</em>.

*/


// para que el diagrama modular quede bien se han escrito includes redundantes;
// en los ficheros .hh de la documentación de las clases ocurre lo mismo.
#include "Procesador.hh"
#include "Pri.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#include "funciones.hh"

using namespace std;
#endif
/** @brief Programa principal para la <em>Practica de Pro2</em>.
*/
int main(){
    //incicializamos cluster
    BinTree<string> Cluster;
    map<string,Procesador> pr;
    configurar_cluster(Cluster, pr,0,"0");
    //incicializamos area de espera
    int n;
    cin>>n;
    map<string,Pri> areap;
    for(int i=0;i<n;++i){
        string s;
        cin>>s;
        alta_prioridad2(areap,s);
    }
    string comando;
    cin>>comando;
    while (comando != "fin") {

        if(comando=="configurar_cluster" or comando=="cc"){
            //intenté cambiar los endl a '\n' para mejorar la eficiencia en la fase intermedia.
            cout<<'#'<<comando<<'\n';
            pr.clear();
            configurar_cluster(Cluster,pr,0,"0");
        }
        else if(comando=="modificar_cluster" or comando=="mc") {

            modificar_cluster(Cluster,pr,comando);
        }
        else if(comando=="alta_prioridad" or comando=="ap"){

            alta_prioridad(areap,comando);
        }
        else if(comando=="baja_prioridad" or comando=="bp"){

            baja_prioridad(areap,comando);
        }
        else if(comando=="alta_proceso_espera" or comando=="ape"){

            alta_proceso_espera(areap,comando);
        }
        else if(comando=="alta_proceso_procesador" or comando=="app") {

            alta_proceso_procesador(pr,comando);
        }
        else if(comando=="baja_proceso_procesador" or comando=="bpp") {

            baja_proceso_procesador(pr, comando);
        }
        else if(comando=="enviar_procesos_cluster" or comando=="epc") {
            cout<<'#'<<comando<<' ';
            enviar_procesos_cluster(pr,areap);
        }
        else if(comando=="avanzar_tiempo" or comando=="at"){
            int t;
            cin>>t;
            cout<<'#'<<comando<<' '<<t<<'\n';
            avanzar_tiempo(pr, t);
        }
        else if(comando=="imprimir_prioridad" or comando=="ipri") {

            imprimir_prioridad(areap, comando);
        }
        else if(comando=="imprimir_area_espera" or comando=="iae") {
            cout<<'#'<<comando<<'\n';
            imprimir_area_espera(areap);
        }
        else if(comando=="imprimir_procesador" or comando=="ipro") {

            imprimir_procesador(pr, comando);
        }
        else if(comando=="imprimir_procesadores_cluster" or comando=="ipc") {
            cout<<'#'<<comando<<'\n';
            imprimir_procesadores_cluster(pr);
        }
        else if(comando=="imprimir_estructura_cluster" or comando=="iec"){

            cout<<'#'<<comando<<'\n'<<imprimir_estructura_cluster(Cluster)<<'\n';
        }
        else if(comando=="compactar_memoria_procesador" or comando=="cmp") {
             cout<<'#'<<comando;
             compactar_memoria_procesador(pr);
        }
        else if(comando=="compactar_memoria_cluster" or comando=="cmc") {
             cout<<'#'<<comando<<'\n';
             compactar_memoria_cluster(pr);
        }
        cin>>comando;
    }
}
