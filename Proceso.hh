/** @file Proceso.hh
    @brief Especificació de la clase Proceso
*/
#ifndef PROCESO_HH
#define PROCESO_HH

#ifndef NO_DIAGRAM
#include <iostream>
#endif

 /** @class Proceso
    @brief Representa un proces.

    Conté 3 enters positius,l'identificador d'un proces, la seva memoria que necessita per a executar-se i el temps necessari.
*/
class Proceso {

private:
    /** @brief  identificador del proces */
    int ide;
    /** @brief  memoria del proces */
    int memo;
    /** @brief  temps del proces */
    int tiempo;


public:
    //constructores
/** @brief Constructura buida
    \pre Cert.
    \post el resultat es un proces buit amb ide=memo=tiempo=0.
*/
    Proceso();

/** @brief Constructura plena
    \pre Cert.
    \post el resultat es un proces amb ide=i, memo=m i tiempo=t.
*/
    Proceso(int i, int m, int t);

    //Modificadores

/** @brief  Decrementa el temps
    \pre t es un enter positiu.
    \post el resultat es un proces amb tiempo=tiempo-t.
*/
    void restar_tiempo_proceso(const int& t);


    //Consultores

/** @brief consulta del temps.
    \pre Cert.
    \post retorna el temps restant del proces.
*/
    int tiempoproceso() const;

/** @brief consulta de la memoria.
    \pre Cert.
    \post retorna la memoria del proces.
*/
    int memoriaproceso() const;

/** @brief consulta del temps.
    \pre Cert.
    \post retorna l'identificador del proces.
*/
    int idproceso() const;

    //Lectura i Escriptura

/** @brief Lectura d'un proces.
    \pre el proces es buit, el canal estandar d'entrada conté els elements del proces.
    \post retorna un proces amb la informacio entrada.
*/
     void leer_proceso();


/** @brief Escriptura d'un procesador.
    \pre Cert.
    \post Imprimeix els elements d'un proces.
*/
    void escribirproceso() const;


};
#endif
