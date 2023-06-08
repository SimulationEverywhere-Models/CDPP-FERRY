/*******************************************************************
*
*  DESCRIPCION: Modelo Atomico de Cola
*
*  AUTOR: Barberis, Angel Rub‚n
*
*  FECHA: 04/10/2004
*
*******************************************************************/

#include "cola.h"      // clase Cola
#include "message.h"    // clase ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include <stdlib.h>

/*******************************************************************
* Function Name: Cola
* Description:
********************************************************************/
Cola::Cola( const string &name )
: Atomic( name )
, in_vehic( addInputPort( "in_vehic" ) )
, in_solic( addInputPort( "in_solic" ) )
, in_parar( addInputPort( "in_parar" ) )
, out_ferry( addOutputPort( "out_ferry" ) )
, out_perf( addOutputPort( "out_perf" ) )
{
}

/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &Cola::initFunction()
{
Solicitud = 0;
elementos.erase( elementos.begin(), elementos.end() ) ;
cout << "cola: init \n";
return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Cola::externalFunction( const ExternalMessage &msg )
{
if( msg.port() == in_vehic )
	{
		cout <<"Entró el: "<< msg.value()<<"\n";
	elementos.push_back( msg.value() ) ;
      	if (Solicitud > 0)
	  	   holdIn( active, Time::Zero);
	    else passivate();
	}

if( (msg.port() == in_solic ) && (msg.value() > 0) )
	{
	  Solicitud = 1;
     cout <<"hay una solicitud ...\n";
	if (elementos.size() > 0)
		holdIn( active, Time(0,1,10,0)); //lo que demora un vehiculo en subir

	else if (elementos.size() == 0)
		passivate();
	}
if( (msg.port() == in_parar ) && (msg.value() > 0) )
	{
		cout <<"Detener Cola\n";
           Solicitud = 0;
           passivate();
    }

return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Cola::internalFunction( const InternalMessage & )
{

elementos.pop_front();

if ((Solicitud >0) && (elementos.size() > 0))
	holdIn( active, Time(0,1,10,0));
else
	passivate();

return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Cola::outputFunction( const InternalMessage &msg )
{
double vehiculo;

if ((elementos.size() > 0) && (Solicitud > 0) )
	{
        vehiculo = elementos.front();
	    sendOutput( msg.time(), out_ferry, vehiculo);
	    sendOutput( msg.time(), out_perf, vehiculo);
	}

return *this ;
}
