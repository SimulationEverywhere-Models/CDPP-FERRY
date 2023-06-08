/*******************************************************************
*
*  DESCRIPCION: Modelo Atomico de la Cola en el Ferry
*
*  AUTOR: Barberis, Angel Ruben 
*
*  FECHA: 04/10/2004
*
*******************************************************************/
#ifndef __COLAF_H
#define __COLAF_H

#include "atomic.h"     // class Atomic

class Cola_F : public Atomic
{
public:
	Cola_F( const string &name = "Cola_F" );					//Default constructor	
	virtual string className() const;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );
	
private:
	const Port &in_inicio;
	const Port &in_vehic;
	Port &out_lado_S;
	Port &out_lado_N;
	Port &out_listo;
	Port &out_Full;
	Port &out_enHoraSalida;
	
	typedef list<Value> ElementList ;
	ElementList cola;

	enum Estados {
		ColaFull,
		conCarga,
		sinCarga,
		sinDescarga,
		conDescarga,
		EnHorarioDeSalida,
		ninguno
	};
	enum TipoDireccion {
		Norte,
		Sur,
		vacio
	};
	// Parametros
	Time cte_Tiempo_de_Descenso;
	Time TiempoEnPuerto;

	// Estas variables representan el estado
	Estados fase;
	TipoDireccion direccion;
	
	// Variables auxiliares
	int MaxCapacidad;
	int cOk;
	int cfull;
};	// clase Cola_F

// ** inline ** // 
inline string Cola_F::className() const
{
	return "Cola_F" ;
}

#endif