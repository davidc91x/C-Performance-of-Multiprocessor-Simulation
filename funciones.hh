/** @file funciones.hh
    @brief Funcions per al programa principal de la practica.
*/

#ifndef FUNCIONES
#define FUNCIONES
#include "Procesador.hh"
#include "Pri.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <map>
#include <set>
#include <string>
#include <iostream>
#endif
using namespace std;
typedef BinTree<string> clu;
typedef map<string,Pri> Area;

/** @brief modifica un Cluster.
    \pre el canal estandar d’entrada conte les dades d'un cluster.
    \post  si el procesador amb id==s no te fills, es cambia pel cluster que esperaba a l'entrada. Sinó, s'imprimeix un missatge d'error.
*/
void modificarrecursivo(clu& Cluster, map<string,Procesador>& pr,const string& s, int ni, string iz, const string& comando);

/** @brief configura un Cluster.
    \pre el canal estandar d’entrada conté les dades d'un cluster.
    \post  es crea aquest cluster i si ja existia algun altre deixa d'existir.
*/
void configurar_cluster(clu& Cluster, map<string,Procesador>& pr, int n, string i);

/** @brief modifica un Cluster.
    \pre ja existeix un Cluster i en el canal d'entrada hi ha un identificador d'un procesador i un nou cluster.
    \post  Si el procesador no existeix al cluster, o te procesos en execució o te procesadors auxiliars, s'imprimeix un missatge d'error. Sino, modifica el Cluster amb el nou cluster a la posició del procesador.
*/
void modificar_cluster(clu& Cluster, map<string,Procesador>& pr, const string& comando);

/** @brief afegeix una prioritat a l'area d'espera.
    \pre ja existeix una area d'espera, encara que sigui buida. En el canal d'entrada hi ha un identificador de prioritat.
    \post  Si no existeix ja a l'area, s'afegeix a l'areap aquesta nova prioritat. Si existeix ja s'imprimeix un missatge d'error.
*/
void alta_prioridad(Area& areap, const string& comando);

/** @brief afegeix una prioritat a l'area d'espera.
    \pre ja existeix una area d'espera, encara que sigui buida. En el canal d'entrada hi ha un identificador de prioritat, el cual es diferent a tots els que als identificadors que hi ha ja a l'area d'espera.
    \post  S'afegeix a l'areap aquesta nova prioritat.
*/
void alta_prioridad2(Area& areap, const string& s);

/** @brief elimina una prioritat de l'area d'espera.
    \pre ja existeix una area d'espera, encara que sigui buida. En el canal d'entrada hi ha un identificador de prioritat.
    \post  Si aquest identificador es a areap i si no te procesos pendents, s'elimina la prioritat de l'areap. Sino s'imprimeix un missatge d'error.
*/
void baja_prioridad(Area& areap,const string& comando);



/** @brief afegeix un proces a l'area d'espera.
    \pre En el canal d'entrada hi ha les dades d'un proces i un identificador de prioritat.
    \post  afegeix un proces a l'area d'espera amb la seva prioritat corresponent, si la prioritat existeix i no hi ha un altre proces amb el mateix identificador en aquesta prioritat. Sino s'imprimeix un missatge d'error.
*/
void alta_proceso_espera(Area& areap,const string& comando);

/** @brief afegeix un proces a un procesador.
    \pre En el canal d'entrada hi ha un identificador d'un procesador i les dades d'un proces.
    \post  si existeix el procesador, no conté un altre procesador amb el mateix identificador i el proces cap al procesador, s'afegeix el proces en el procesador entrat,en la posició mes petita que deixa el forat més adjustat. En cas contrari s'imprimeix un missatge d'error.
*/
void alta_proceso_procesador(map<string,Procesador>& pr, const string& comando);


/** @brief elimina un proces d'un procesador.
    \pre En el canal d'entrada hi ha un identificador d'un procesador i d'un proces.
    \post  si existeix el procesador, i el proces esta en el procesador, s'elimina el proces del procesador. En cas contrari s'imprimeix un missatge d'error.
*/
void baja_proceso_procesador(map<string,Procesador>& pr, const string& comando);

/** @brief Envia n procesos al Cluster.
    \pre En el canal d'entrada hi ha un enter no negatiu n.
    \post  S'intenten colocar n procesos al cluster fins a colocar n procesos, que no quedin mes procesos o que els que quedin ja s'han intentat colocar sense èxit. Si un proces no es pot colocar es torna a posar a la seva prioritat però a l'ultim espai. Si un proces es pot colocar en més d'un procesador, s'escogirà el del lloc més adjustat.En cas d'empat, es mirarà l'espai que queda lliure, la seva distància a l'arrel  i el de més a l'esquerra, en aquest ordre.
*/
void enviar_procesos_cluster(map<string,Procesador>& pr,Area& areap);

/** @brief Avança t segons al Cluster.
    \pre En el canal d'entrada hi ha un enter positiu t.
    \post  Es resta t a tots els procesos actius del cluster i els que s'acabin s'eliminen.
*/

void avanzar_tiempo(map<string,Procesador>& pr, const int& t);

/** @brief Imprimeix una prioritat.
    \pre En el canal d'entrada hi ha un identificador de prioritat.
    \post  si existeix la prioritat a l'area d'espera,s'escriuen els seus procesos pendents, des de la seva última alta, i els procesos enviats al cluster i els rebutjats. En cas contrari s'imprimeix un missatge d'error.
*/
void imprimir_prioridad(const Area& areap, const string& comando);

/** @brief Imprimeix l'area d'espera.
    \pre Cert.
    \post  S'imprimeixen totes les prioritats com a imprimir_prioridad.
*/
void imprimir_area_espera(const Area& areap);

/** @brief Imprimeix un procesador.
    \pre En el canal d'entrada hi ha un identificador d'un procesador.
    \post si existeix aquest procesador al cluster,s'escriuen els seus procesos actius, des de la seva primera posició de memoria, i la resta de dades d'un procesador. En cas contrari s'imprimeix un missatge d'error.
*/
void imprimir_procesador(const map<string,Procesador>& pr, const string& comando);

/** @brief Imprimeix els procesadors del Cluster.
    \pre Cert.
    \post S'imprimeixen tots els procesadors com a imprimir_procesador.
*/
void imprimir_procesadores_cluster(const map<string,Procesador>& pr);

/** @brief Imprimeix l'estructura dels procesadors del Cluster.
    \pre Ja existeix un Cluster.
    \post Retorna un string amb l'estructura de procesadors del Cluster.
*/
string imprimir_estructura_cluster(const clu& Cluster);

/** @brief Compacta la memoria d'un procesador.
    \pre En el canal d'entrada hi ha un identificador d'un procesador.
    \post si existeix aquest procesador al cluster,es mouen tots els seus procesos cap a l'inici de la seva memoria, sense deixa llocs lliures i respectant l'ordre inicial. En cas contrari s'imprimeix un missatge d'error.
*/
void compactar_memoria_procesador(map<string,Procesador>& pr);

/** @brief Compacta la memoria del Cluster.
    \pre Cert.
    \post En cada procesador, es mouen tots els seus procesos cap a l'inici de la seva memoria, sense deixa llocs lliures i respectant l'ordre inicial.
*/
void compactar_memoria_cluster(map<string,Procesador>& pr);


#endif
