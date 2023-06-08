/*******************************************************************
*
*  DESCRIPCION: clase Generador
*
*  AUTOR: Barberis, Angel Rubén 
*
*  FECHA: 04/10/2004
*
*******************************************************************/

/** Archivos de incluciones **/
#include "generar.h"       // Header base
#include "message.h"       // clase InternalMessage 
#include "mainsimu.h"      // clase Simulator
#include "distri.h"        // clase Distribution 
#include "strutil.h"       // str2Value( ... )
#include <stdio.h>

/*******************************************************************
* Function Name: Generador
* Description: constructor
********************************************************************/
Generador::Generador( const string &name )
: Atomic( name )
, out_vehic( addOutputPort( "out_vehic" ) )
{
try
{
dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );
MASSERT( dist ) ;
for ( register int i = 0; i < dist->varCount(); i++ )
	{
	string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar( i ) ) ) ;
	dist->setVar( i, str2Value( parameter ) ) ;
	}

} catch( InvalidDistribution &e )
	{
	e.addText( "El modelo " + description() + " es una distribucion con problemas!" ) ;
	e.print(cerr);
	MTHROW( e ) ;
} catch( MException &e )
	{
	MTHROW( e ) ;
	}
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Generador::initFunction()
{
	cout << "Generador: Init\n";
Hora = 0.0;
vehiculo = 0.0;
holdIn( active, Time(0, 0, 0, 100));

return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Generador::internalFunction( const InternalMessage & )
{
static double TiempoEntreLlegada;

static int min;
static int seg;
static float mseg;

//	printf("<Llega>: auto <- %1.5f\n", vehiculo); 

	TiempoEntreLlegada = fabs( distribution().get() );
	Hora = Hora + TiempoEntreLlegada;
	printf("<Llega>: Sur <- %1.5f :  %1.5f\n", TiempoEntreLlegada,Hora); 
//	printf("<Tiempo>: min <- %1.8f\n", Llega.minutes()); 
//	printf("<Tiempo>: seg <- %1.8f\n", Llega.seconds()); 
//	printf("<Tiempo>: msg <- %1.8f\n", Llega.mseconds()); 
	
//	Llega = Time(static_cast< float >( TiempoEntreLlegada));

if (TiempoEntreLlegada > 0) {
	vehiculo = 1;
	TiempoEntreLlegada = TiempoEntreLlegada * 60000;
	holdIn( active, Time(0,0,0, TiempoEntreLlegada));
}
else 
	holdIn( active, Time(0,0,1,0) );  // Se duerme hasta la llegada de otro vehic.

return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Generador::outputFunction( const InternalMessage &msg )
{

if (vehiculo > 0)
	{
//	 Llega = msg.time();
    vehiculo = Hora;
  	sendOutput( msg.time(), out_vehic, vehiculo);
  	vehiculo = 0.0;
	} 

return *this ;
}
/*******************************************************************
* Function Name:
********************************************************************/
Generador::~Generador()
{
delete dist;
}

