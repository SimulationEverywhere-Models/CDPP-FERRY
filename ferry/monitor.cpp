/*******************************************************************
*
*  DESCRIPTION: Monitor
*
*  AUTOR: Barberis, Angel Ruben 
*
*
*  FECHA: 04/10/2004
*
*******************************************************************/

#include "monitor.h"      // clase Monitor
#include "message.h"   	  // class ExternalMessage, InternalMessage
#include "mainsimu.h"     // MainSimulator::Instance().getParameter( ... )

/*******************************************************************
* Function Name: Monitor
* Description: 	
* 		
********************************************************************/
Monitor::Monitor( const string &name )
: Atomic( name )
, in_SalidaSys_S( addInputPort( "in_SalidaSys_S" ) )
, in_SalidaSys_N( addInputPort( "in_SalidaSys_N" ) )
, in_CPS( addInputPort( "in_CPS" ) )
, in_CPN( addInputPort( "in_CPN" ) )
, in_datos( addInputPort( "in_datos" ) )
, out_tsys( addOutputPort( "out_tsys" ) )
, out_CPS( addOutputPort( "out_CPS" ) )
, out_CPN( addOutputPort( "out_CPN" ) )
, out_TPES( addOutputPort( "out_TPES" ) )
, out_TPEN( addOutputPort( "out_TPEN" ) )
{
}

/*******************************************************************
* Function Name: initFunction
* Description:
* 
********************************************************************/
Model& Monitor::initFunction()
{
 cout << "Monitor: Init \n";	
 SumEnSys = 0;
 SumCS = 0;
 SumECS = 0;
 SumCN = 0;
 SumECN = 0;
 tsys = 0; 
 CPS = 0; 
 CPN = 0; 
 TPES = 0; 
 TPEN = 0;
 CantVehic = 0;
 swichC = 0;
 FrCS = 0;
 FrCN = 0;

return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model& Monitor::externalFunction( const ExternalMessage &msg )
{

if ((msg.port() == in_SalidaSys_S) || (msg.port() == in_SalidaSys_N))
	{
	CantVehic++;  // Cant. de vehiculos que salen del Sistema
	DifTiempo = convertirTimeAMin(msg.time()) - msg.value();
	SumEnSys = SumEnSys + DifTiempo; 
	cout << "Tsys: " << CantVehic;
	}
else if (msg.port() == in_CPS)
	{
		if (swichC == 0)
		   swichC = 1;
		else if (swichC == 2) {
			FrCN++;
			swichC = 1;
		}
	DifTiempo = convertirTimeAMin(msg.time()) - msg.value();
	SumECS = SumECS + DifTiempo; 
	SumCS++;  //Cuenta vehiculos en la Cola Sur.
	}
else if (msg.port() == in_CPN)
	{
		if (swichC == 0)
		   swichC = 2;
		else if (swichC == 1) {
			FrCS++;
			swichC = 2;
		}
	DifTiempo = convertirTimeAMin(msg.time()) - msg.value();
	SumECN = SumECN + DifTiempo; 
	  SumCN++;  // Cuenta vehiculos en la Cola Norte.
	}
else if (msg.port() == in_datos)
	{
	cout<< "Angel: " ;
	holdIn( active, Time::Zero);
	}

return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model& Monitor::internalFunction( const InternalMessage & )
{
passivate();
return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Monitor::outputFunction( const InternalMessage &msg )
{
	if (CantVehic >0){
    tsys = SumEnSys/CantVehic;
    CPS = SumCS/FrCS;
    CPN = SumCN/FrCN;
    TPES = SumECS/SumCS;
    TPEN = SumECN/SumCN;
    
  	sendOutput( msg.time(), out_tsys, tsys);
	sendOutput( msg.time(), out_CPS, CPS);
	sendOutput( msg.time(), out_CPN, CPN);
	sendOutput( msg.time(), out_TPES, TPES);
	sendOutput( msg.time(), out_TPEN, TPEN);
	}

return *this;
}
/************************************************
* Convierte time a Minutos
*************************************************/
float Monitor::convertirTimeAMin(const Time &time)
{
int houra = 60 * time.hours();
int min = time.minutes();
int seg = time.seconds() / 60;
float mseg = (float)time.mseconds()/1000;

return houra + min + seg + mseg / 60;
}
