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
, out_cargar_S( addOutputPort( "out_cargar_S" ) )
, out_cargar_N( addOutputPort( "out_cargar_N" ) )
, out_descargar( addOutputPort( "out_descargar" ) )
, out_horaSalida_S( addOutputPort( "out_horaSalida_S" ) )
, out_horaSalida_N( addOutputPort( "out_horaSalida_N" ) )
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
	cout << "Barco: Init \n";
 fase = EnMarcha;
 direccion = Norte;
 cOk = 1.0;
 cSolicitar = 1.0;
 cDetener = 1.0;
 cSur = 0.0;
 cNorte = 1.0;
 
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
		    cout <<"Le dan permiso para descargar ........\n";
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
	cout <<"Barco emitiendo mensaje ................................ \n";
  if (direccion == Norte){
	   switch(fase){
	    case ComenzarDesembarque:
		         sendOutput( msg.time(), out_descargar, cNorte) ;
			break;
		case IniciarEmbarque:
		         sendOutput( msg.time(), out_cargar_N, cSolicitar) ;
			break;
		case EnSalida:
		         sendOutput( msg.time(), out_horaSalida_N, cDetener) ;
			break;
		case EnMarcha:
	             sendOutput( msg.time(), out_arribo_N, cOk);
		    break;
	    }
    }
   else {
	   switch(fase){
	    case ComenzarDesembarque:
		         sendOutput( msg.time(), out_descargar, cSur) ;
			break;
		case IniciarEmbarque:
		         sendOutput( msg.time(), out_cargar_S, cSolicitar) ;
			break;
		case EnSalida:
		         sendOutput( msg.time(), out_horaSalida_S, cDetener) ;
			break;
		case EnMarcha:
	             sendOutput ( msg.time(), out_arribo_S, cOk);
		    break;
	  }
     }
   
return *this ;
}
