/*******************************************************************
*
*  DESCRIPCION: Modelo Atomico de Cola
*
*  AUTOR: Barberis, Angel Rubén
*
*
*  FECHA: 04/10/2004
*
*******************************************************************/

#ifndef __COLA_H
#define __COLA_H

#include <list>
#include "atomic.h"     // clase Atomic

class Cola : public Atomic
{
public:
	Cola( const string &name = "Cola" );
	virtual ~Cola() { }
	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	    const Port &in_vehic;
        const Port &in_solic;
        const Port &in_parar;
	Port &out_ferry;
	Port &out_perf;
	typedef list<Value> ElementList ;
	ElementList elementos;
	int Solicitud;

};	// clase COLA

// ** inline ** //
inline
string Cola::className() const
{
	return "Cola" ;
}

#endif   //__COLA_H
