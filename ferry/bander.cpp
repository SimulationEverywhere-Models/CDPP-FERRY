/*******************************************************************
*
*  DESCRIPCION: Modelo Banderillero
*
*  AUTOR: Barberis, Angel Rub‚n
*
*
*  FECHA: 04/10/2004
*
*******************************************************************/

#include "bander.h"        // clase Banderillero
#include "message.h"   	   // clase ExternalMessage, InternalMessage
#include "mainsimu.h"      // MainSimulator::Instance().getParameter( ... )

/*******************************************************************
* Function Name: Banderillero
* Description:
*
********************************************************************/
Banderillero::Banderillero( const string &name )
: Atomic( name )
, in_ferry( addInputPort( "in_ferry" ) )
, in_solic( addInputPort( "in_solic" ) )
, in_cerrarPaso( addInputPort( "in_cerrarPaso" ) )
, out_descargar( addOutputPort( "out_descargar" ) )
, out_solic( addOutputPort( "out_solic" ) )
, out_parar( addOutputPort( "out_parar" ) )
, cte_Tiempo_de_arribo( 0, 1, 10, 10 )
, cte_Tiempo_de_apertura( 0, 0, 30, 0 )
{
}

/*******************************************************************
* Function Name: initFunction
* Description:
*
********************************************************************/
Model& Banderillero::initFunction()
{
 fase = CierreDeBarrera;
 muelle = ninguno;
 cOk = 1.0;
 cZona = 0.0;
 cSolicitar = 1.0;
 cDetener = 1.0;
 cout << "Bander: Init\n";
 holdIn(active, Time::Zero) ;
return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model& Banderillero::externalFunction( const ExternalMessage &msg )
{
	if (cZona >0.0)
	   cout <<"Puerto: Norte ....\n";
	else
	   cout <<"Pureto: Sur ......\n";
	   
	cout <<"Bander:  Se recibió un mensaje ................... \n";
	switch (fase){
		case EsperaDeFerry:
		    cout <<"Fase: Espera de Ferry .......\n";
		    break;
		case ArriboDeFerry:
		    cout <<"Fase: ArriboDeFerry .......\n";
		    break;
		case AperturaDeBarrera:
		    cout <<"Fase: Apertura de Barrera .......\n";
		    break;
		case FerryEnMuelle:
		    cout <<"Fase: Ferry en Muelle .......\n";
		    break;
		case CierreDeBarrera:
		    cout <<"Fase: CierreDeBarrera .......\n";
		    break;
	}
	
  if (msg.port() == in_ferry){
  	  cout <<" ..... puerto in_ferry \n";
  } else if (msg.port() == in_solic){
  	   cout<<"    .... puerto in_solic|n";
  } else if (msg.port() == in_cerrarPaso){
  	    cout <<"  ...... puerto in_cerrarPaso ,, \n";
  }
		
	switch(fase){
		case EsperaDeFerry:
			// Si el mensaje llego por el puerto in_ferry
			if (msg.port() == in_ferry){
				cZona = msg.value();
				fase = ArriboDeFerry;
				if (cZona >0)
				   cout <<"Arribo en Norte\n"; 
				else cout <<"Arribo en Sur\n";
				holdIn( active, cte_Tiempo_de_arribo ) ;
			}
			break;
		case FerryEnMuelle:
			// Si el mensaje llego por el puerto in_solic
			if ((muelle == conDesembarque) && (msg.port() == in_solic)){
				fase = AperturaDeBarrera;
			// Si el mensaje llego por el puerto in_cerrarPaso
			} else if (msg.port() == in_cerrarPaso) {
				fase = CierreDeBarrera;
				}
			holdIn( active, cte_Tiempo_de_apertura ) ;
			break;
	}

return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model& Banderillero::internalFunction( const InternalMessage & )
{
	switch(fase){
		case ArriboDeFerry:
				fase = FerryEnMuelle;
				muelle = conDesembarque;
				holdIn( active, Time::Zero ) ;
			break;
		case AperturaDeBarrera:
	          fase = FerryEnMuelle;
	          muelle = conEmbarque;		   
			holdIn( active, Time::Zero ) ;
			break;
		case CierreDeBarrera:
	          fase = EsperaDeFerry;
	          muelle = ninguno;		   
	          cout <<"Cerrando la Barrera ...................\n";
			  passivate() ;
			break;
	}

return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Banderillero::outputFunction( const InternalMessage &msg )
{
	switch(fase){
		case ArriboDeFerry:
		         sendOutput( msg.time(), out_descargar, cOk) ;
			break;
		case AperturaDeBarrera:
		         sendOutput( msg.time(), out_solic, cSolicitar) ;
			break;
		case CierreDeBarrera:
		         cout <<"Detener subida ... Cierre de Barrera ...\n";
		         sendOutput( msg.time(), out_parar, cDetener) ;
			break;
	}
	
return *this ;
}
