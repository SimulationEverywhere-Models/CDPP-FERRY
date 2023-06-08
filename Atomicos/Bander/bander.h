/*******************************************************************
*
*  DESCRIPCION: Modelo Baderillero
*
*  AUTOR: Barberis, Angel Rub‚n
*
*
*  FECHA: 04/10/2004
*
*******************************************************************/

#ifndef __BANDERILLERO_H
#define __BANDERILLERO_H

#include "atomic.h"     // clase Atomic

class Banderillero : public Atomic
{
public:
	Banderillero( const string &name = "Banderillero" );
	~Banderillero() {};

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in_ferry;
	const Port &in_solic;
	const Port &in_cerrarPaso;
	Port &out_descargar;
	Port &out_solic;
    Port &out_parar;

	enum Estados {
		EsperaDeFerry,
		ArriboDeFerry,
		AperturaDeBarrera,
		FerryEnMuelle,
		CierreDeBarrera
	};
	
	enum EstadoMuelle {
		conEmbarque,
		conDesembarque,
		ninguno
	};
	// Parametros
	Time cte_Tiempo_de_apertura;
	Time cte_Tiempo_de_arribo;

	// Estas variables representan el estado
	Estados fase;
	EstadoMuelle muelle;
	
	// Variables auxiliares
	 double cOk;
	 double cSolicitar;
	 double cDetener;
};	// class Banderillero

// ** inline ** //
inline
string Banderillero::className() const
{
	return "Banderillero" ;
}

#endif   //__BANDERILLERO_H
