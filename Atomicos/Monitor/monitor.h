/*******************************************************************
*
*  DESCRIPCION: Modelo Monitor de Performance
*
*  AUTOR: Barberis, Angel Ruben 
*
*
*  FECHA: 04/10/2004
*
*******************************************************************/

#ifndef __PERFORMANCE_H
#define __MONITOR_H

#include "atomic.h"     // class Atomic
#include "time.h"	// class Time

class Monitor : public Atomic
{
public:
	Monitor( const string &name = "Monitor" );	//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in_SalidaSys_S;
	const Port &in_SalidaSys_N;
	const Port &in_CPS;
	const Port &in_CPN;
	const Port &in_datos;
	Port &out_tsys;
	Port &out_CPS;
	Port &out_CPN;
	Port &out_TPES;
	Port &out_TPEN;
	
	double DifTiempo;
	
	int SumECS, SumCS, SumCN, SumECN, SumEnSys;
	float tsys, CPS, CPN, TPES, TPEN;
	int CantVehic, swichC,FrCS, FrCN;
	
	float convertirTimeAMin(const Time &time);
};	// clase Monitor

// ** inline ** // 
inline
string Monitor::className() const
{
return "Monitor" ;
}
#endif   //__MONITOR_H
