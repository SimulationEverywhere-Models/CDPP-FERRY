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

#include "barco.h"        // clase Barco
#include "message.h"   	   // clase ExternalMessage, InternalMessage
#include "mainsimu.h"      // MainSimulator::Instance().getParameter( ... )

/*******************************************************************
* Function Name: Barco
* Description:
*
********************************************************************/
Barco::Barco( const string &name )
: Atomic( name )
, in_horario( addInputPort( "in_horario" ) )
, in_permiso( addInputPort( "in_permiso" ) )
, in_listo( addInputPort( "in_listo" ) )
, in_capComp( addInputPort( "in_capComp" ) )
, out_arribo_S( addOutputPort( "out_arribo_S" ) )
, out_arribo_N( addOutputPort( "out_arribo_N" ) )
, out_cargar( addOutputPort( "out_cargar" ) )
, out_descargar( addOutputPort( "out_descargar" ) )
, out_horaSalida( addOutputPort( "out_horaSalida" ) )
, cte_Tiempo_de_Traslado( 0, 15, 30, 0 )
{
}

/*******************************************************************
* Function Name: initFunction
* Description:
*
********************************************************************/
Model& Barco::initFunction()
{
 fase = EnMarcha;
 direccion = Norte;
 cOk = 1.0;
 cSolicitar = 1.0;
 cDetener = 1.0;
 
 holdIn(active, Time::Zero) ;
return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model& Barco::externalFunction( const ExternalMessage &msg )
{
	switch(fase){
		case Arribo:
			if (msg.port() == in_permiso){
				fase = ComenzarDesembarque;
				holdIn( active, Time::Zero ) ;
			}
			break;
		case Desembarque:
			if (msg.port() == in_listo){
				fase = IniciarEmbarque;
			} 
			holdIn( active, Time::Zero ) ;
			break;
		case Embarque:
			if ((msg.port() == in_capComp) || (msg.port() == in_horario)){
				fase = EnSalida;
			} 
			holdIn( active, Time::Zero ) ;
			break;
	}

return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model& Barco::internalFunction( const InternalMessage & )
{
	switch(fase){
		case ComenzarDesembarque:
	          fase = Desembarque;
	          passivate();
			break;
		case IniciarEmbarque:
	          fase = Embarque;
			  passivate() ;
			break;
		case EnSalida:
	          fase = EnMarcha;
	          if (direccion == Norte)  
	             direccion = Sur;
	          else direccion = Norte;
			  holdIn( active, cte_Tiempo_de_Traslado) ;
			break;
		case EnMarcha:
	          fase = Arribo;
			  passivate() ;
			break;
	}

return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Barco::outputFunction( const InternalMessage &msg )
{
	switch(fase){
		case ComenzarDesembarque:
		         sendOutput( msg.time(), out_descargar, cOk) ;
			break;
		case IniciarEmbarque:
		         sendOutput( msg.time(), out_cargar, cSolicitar) ;
			break;
		case EnSalida:
		         sendOutput( msg.time(), out_horaSalida, cDetener) ;
			break;
		case EnMarcha:
		         if (direccion == Norte)
		             sendOutput( msg.time(), out_arribo_N, cOk);
		         else
		             sendOutput ( msg.time(), out_arribo_S, cOk);
		    break;
	}
	
return *this ;
}
