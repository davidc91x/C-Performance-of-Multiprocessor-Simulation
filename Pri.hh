/** @file Pri.hh
    @brief Especificació de la clase Pri
*/

#ifndef Pri_HH
#define Pri_HH
#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#include <set>
#include <list>
#endif
using namespace std;
        /** @class Pri
    @brief Representa una prioritat.

    Conté una llista de procesos, un set de ints amb els seus identificadors i 2 enters positius, el nombre de procesos colocats al cluster i el nombre de rebujtats pel cluster.
*/
class Pri {


private:
    /** @brief llista dels procesos de la prioritat */
    list<Proceso> lista;
    /** @brief set dels identificadors dels procesos de la prioritat */
    set<int> seta;
    /** @brief la quantitat de procesos colocats al cluster per part d'aquesta prioritat*/
    int colocados;
    /** @brief la quantitat de procesos rebutjats pel cluster per part d'aquesta prioritat */
    int rechazos;

public:
    //constructores
/** @brief Constructura buida.
    \pre Cert.
    \post el resultat es un Pri buit.
*/
    Pri();

    //Modificadores
/** @brief Incrementa els colocados.
    \pre Cert.
    \post el resultat es un Pri amb colocados=colacados+1
*/
    void incrementarcolocados();

/** @brief Incrementa els rechazos.
    \pre Cert.
    \post el resultat es un Pri amb rechazos=rechazos+1
*/
    void incrementarrechazos();

 /** @brief Afegeix un Proceso a area.
    \pre Cert.
    \post retorna true i el resultat es un Pri amb el proceso afegit a la seva llista i el id del proces afegit al seu set si el proces no era ja a la prioritat. Si no retorna false i no modifica el proces.
*/
    bool push(const Proceso& p);

 /** @brief Elimina un Proceso de l'area.
    \pre Cert.
    \post retorna true i el resultat es un Pri sense el primer proces entrat a la prioritat si no es buida. Si no retorna false i no es modifica el proces.
*/
    bool pop();

 /** @brief Posa els procesos de la prioritat b en la prioritat en la que cridem la funció.
    \pre Els procesos de b no poden tenir el mateix identificador que els procesos de la prioritat en la que cridem la funció.
    \post el resultat es un Pri amb els procesos que ja tenia i els de b.
*/
    void juntarprocesos(Pri b);


    //Consultores

/** @brief Consulta si la prioritat es buida.
    \pre Cert.
    \post retorna si la prioritat es buida.
*/
    bool empty() const;

/** @brief Consulta l'element més antic de la prioritat.
    \pre Cert.
    \post retorna l'element més antic de la prioritat.
*/
    Proceso  front() const;


//Lectura i Escriptura



/** @brief Escriptura d'un Pri.
    \pre Cert.
    \post Imprimeix els elements d'un Pri.
*/
    void escribirPri() const;


};
#endif
