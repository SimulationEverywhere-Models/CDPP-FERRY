/*******************************************************************
*
*  DESCRIPCION: clase Generador
*
*  AUTOR: Barberis, Angel Rubén 
*
*
*  FECHA: 04/10/2004
*
*******************************************************************/

#ifndef __GENERADOR_H
#define __GENERADOR_H

/** Archivos de inclucion **/
#include "atomic.h"     // clase Atomic
#include "except.h"     // clase InvalidMessageException

class Distribution ;

/** declaraciones **/
class Generador : public Atomic
{
public:
	Generador( const string &name = "Generador" );	

	~Generador();

	virtual string className() const
		{return "Generador";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & )
			{throw InvalidMessageException();}

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	Port &out_vehic ;
	Distribution *dist ;
	double vehiculo, Hora; 
	Time Llega;
	
	Distribution &distribution()
			{return *dist;}
			
};	// clase Generador


#endif   //__GENERADOR_H 
