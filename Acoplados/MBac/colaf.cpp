/*******************************************************************
*
*  DESCRIPCION: Atomic Model Cola
*
*  AUTOR: Barberis, Angel Ruben 
*
*  FECHA: 04/10/2004
*
*******************************************************************/

#include "colaf.h"      // clase Cola_F
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Cola_F
* Description: 
********************************************************************/
Cola_F::Cola_F( const string &name )
: Atomic( name )
, in_inicio( addInputPort( "in_inicio" ) )
, in_vehic( addOutputPort( "in_vehic" ) )
, out_lado_S( addInputPort( "out_lado_S" ) )
, out_lado_N( addInputPort( "out_lado_N" ) )
, out_listo( addOutputPort( "out_listo" ) )
, out_Full( addOutputPort( "out_Full" ) )
, out_enHoraSalida( addOutputPort( "out_enHoraSalida" ) )
, cte_Tiempo_de_Descenso( 0, 1, 10, 0 )
{
};

/*******************************************************************
* Function Name: initFunction
* Description:
********************************************************************/
Model &Cola_F::initFunction()
{
	MaxCapacidad = 20;
	fase = sinCarga;
	direccion = vacio;
	cOk = 1;
	cfull = 1;
	cola.erase( cola.begin(), cola.end() ) ;
	
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
* Description: Funcion de transicion por un evento externo.
********************************************************************/
Model &Cola_F::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == in_inicio){
		TiempoEnPuerto = msg.time();
		
		if (cola.size() > 0) {
			fase = conDescarga;
			if (msg.value() > 0)
			    direccion = Sur;
			else 
			   direccion = Norte;
			   
			holdIn( active, cte_Tiempo_de_Descenso);
		}
		else { 
			fase = sinDescarga;
			holdIn( active, Time::Zero );
		}
	} 
	if (msg.port() == in_vehic){
	 if ((fase != ColaFull) && (fase != EnHorarioDeSalida)) {
		cola.push_back( msg.value() ) ;
		
		if ((cola.size() == 1) && (fase = sinCarga)) {
				fase = conCarga;
				holdIn( active, Time::Zero );
		}
		else if (cola.size() == MaxCapacidad) {
			fase = ColaFull;
			holdIn( active, Time::Zero ) ;
		}
		else if ((fase = conCarga)&& ((msg.time()-TiempoEnPuerto) >= Time(0,30,0,0))) {
			fase = EnHorarioDeSalida;
			holdIn( active, Time::Zero);
	    }
	 }
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Cola_F::internalFunction( const InternalMessage & )
{
	if ((cola.size() > 0) && (fase == conDescarga)) {
		cola.pop_front();
		if (cola.size() == 0) {
			fase = sinDescarga;
			holdIn( active, Time::Zero );
		}
		else holdIn( active, cte_Tiempo_de_Descenso );
	} 
	if ((fase == ColaFull) || (fase == EnHorarioDeSalida)) {
		direccion = vacio;
	}
	if ((cola.size() == 0) && (fase == sinDescarga)) {
		 fase = sinCarga;
	}
	passivate();
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Cola_F::outputFunction( const InternalMessage &msg )
{
	if ((cola.size() > 0) && (fase == conDescarga)) {
		if (direccion = Sur)
		     sendOutput( msg.time(), out_lado_S, cola.front() );
		else
		     sendOutput( msg.time(), out_lado_N, cola.front() );
	} else if (fase == ColaFull) {
			sendOutput( msg.time(), out_Full, cfull );
	} else if ((cola.size() == 0) && (fase == sinDescarga)) {
		sendOutput( msg.time(), out_listo, cOk );
	} else if (fase == EnHorarioDeSalida)
	    sendOutput( msg.time(), out_enHoraSalida, cOk);
	
	return *this ;
}
