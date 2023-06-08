/*******************************************************************
*
*  DESCRIPCION: Modelo Barco
*
*  AUTOR: Barberis, Angel Ruben
*
*
*  FECHA: 04/10/2004
*
*******************************************************************/

#ifndef __BARCO_H
#define __BARCO_H

#include "atomic.h"     // clase Atomic

class Barco : public Atomic
{
public:
	Barco( const string &name = "Barco" );
	~Barco() {};

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in_horario;
	const Port &in_permiso;
	const Port &in_listo;
	const Port &in_capComp;
	Port &out_arribo_S;
	Port &out_arribo_N;
	Port &out_cargar_S;
	Port &out_cargar_N;
    Port &out_descargar;
    Port &out_horaSalida_S;
    Port &out_horaSalida_N;

	enum Estados {
		EnMarcha,
		Arribo,
		ComenzarDesembarque,
		Desembarque,
		IniciarEmbarque,
		Embarque,
		EnSalida
	};
	
	enum Tdireccion {
		Norte,
		Sur,
		ninguno
	};

    Time cte_Tiempo_de_Traslado;
    
	// Estas variables representan el estado
	Estados fase;
	Tdireccion direccion;
	
	// Variables auxiliares
	 double cOk, cSur, cNorte;
	 double cSolicitar;
	 double cDetener;
};	// class Barco

// ** inline ** //
inline
string Barco::className() const
{
	return "Barco" ;
}

#endif   //__BARCO_H
