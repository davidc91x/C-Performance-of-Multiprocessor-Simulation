/** @file Procesador.hh
    @brief Especificació de la clase Procesador
*/

#ifndef PROCESADOR_HH
#define PROCESADOR_HH

#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <string>
#include <map>
#include <set>
#include <iostream>
#endif
using namespace std;
     /** @class Procesador
    @brief Representa un procesador.

    Conte la seva memoria total, l'espai que queda lliure i 3 mapas, un que conte els procesos que s'estan efectuant amb la seva posicio a la memoria, un que conte els identificadors de cada proces i la seva posicio al procesador; i l'últim conté el tamany dels espais lliures que hi ha a la memoria del procesador i les seves posicions. Tambe conte un int que indica el seu nivell al cluster i un string que indica quant a l'esquerra esta en el cluster per a futures comparacions.
*/
class Procesador {


private:

    /** @brief  memoria del procesador */
    int mem;
    /** @brief  espai lliure del procesador */
    int espaciol;
    /** @brief  nivell del procesador */
    int ni;
    /** @brief  indicador de quant a l'esquerra esta en el cluster del procesador */
    string iz;
    /** @brief  mapa dels espais lliures del procesador */
    map<int,set<int>> espacioslibres;
    /** @brief  mapa dels espais ocupats del procesador */
    map<int,Proceso> espacios;
    /** @brief  mapa dels identificadors dels procesos i de la seva posicio al procesador */
    map<int,int> mapa2;


public:
    //constructores
/** @brief Constructura buida
    \pre Cert.
    \post el resultat es un buit.
*/
    Procesador();

/** @brief Constructura plena
    \pre Cert.
    \post el resultat es un procesador amb mem=espaciol=memo, un mapa espacios buit, un mapa2 buit i un espacioslibre amb un element amb el tamany de memo i la posicio 0.
*/
    Procesador(int memo);

    //Modificadores
/** @brief afegeix un proces.
    \pre pos i tam son enters positius.
    \post retorna un procesador amb el proces p guardat en espacios i mapa2 i amb el nou espaciol corresponent i els nou mapa d'espais lliures.
*/
    void añadir_proceso(const Proceso& p, int pos, int tam);

/** @brief elimina un proces.
    \pre s es un enter positiu.
    \post retorna un procesador amb el proces p guardat en espacios i mapa2 i amb el nou espaciol corresponent i els nou mapa d'espais lliures.
*/
    void quitar_proceso(int s,string r ,const string& comando);

/** @brief avança el temps en un procesador.
    \pre t es un enter positiu.
    \post Es resta t a tots els procesos actius del procesador i els que s'acabin s'eliminen.
*/
    void avanzartprocesador(const int& t);

/** @brief compacta la memoria d'un procesador.
    \pre Cert.
    \post es mouen tots els seus procesos cap a l'inici de la seva memoria, sense deixa llocs lliures i respectant l'ordre inicial.
*/
    void compact();

/** @brief modifica el nivell d'un procesador.
    \pre niv es un enter positiu.
    \post ni agafa el valor de niv.
*/
    void assignarnivel(int niv);

/** @brief modifica el string que ens permet veure quan a l'esquerra està dins del cluster.
    \pre Cert.
    \post iz agafa el valor de s.
*/
    void assignarizq(string s);




    //Consultores
/** @brief consulta si el procesador es buit.
    \pre Cert.
    \post retorna si el procesador buit.
*/
    bool empty() const;

/** @brief busca un proces.
    \pre i es un enter positiu.
    \post retorna true si hi ha un proces amb id==i en aquest procesador, sinó retorna false.
*/
    bool buscarProceso(int i) const;

/** @brief busca el lloc més adjustat.
    \pre memo es un enter positiu.
    \post el bool de retorn indica si un procés amb memo de memoria cap al procesador. Si cap, pos és la posició més petita on el procés encaixa de forma més ajustada i tam es el tamany d'aquest espai on encaixa millor.
*/
    bool huecoajustado(int memo, int& pos, int& tam) const;

/** @brief consulta de l'espai lliure.
    \pre Cert.
    \post retorna l'espai lliure del procesador.
*/
    int espaciolibre() const;

/** @brief consulta del nivell.
    \pre Cert.
    \post retorna el nivell del procesador.
*/
    int nivel() const;

/** @brief consulta de l'esquerra.
    \pre Cert.
    \post retorna el string que indica quant a l'esquerra és el procesador al cluster.
*/
    string izquierda() const;

    // Lectura i escriptura

/** @brief Lectura d'un procesador.
    \pre el procesador es buit, el canal estandar d'entrada conte els elements del procesador.
    \post retorna un procesador amb la informacio entrada.
*/
    void leer_procesador();


/** @brief Escriptura d'un procesador.
    \pre Cert.
    \post Imprimeix els elements d'un procesador.
*/
    void escribirprocesador() const;



};
#endif
