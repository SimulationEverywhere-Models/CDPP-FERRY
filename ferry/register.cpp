/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#include "modeladm.h"
#include "mainsimu.h"
#include "bander.h"	 // clase Banderillero
#include "barco.h"	 // clase Barco
#include "cola.h"        // clase Cola
#include "colaf.h"       // clase Cola_F
#include "generar.h"     // clase Generador
#include "monitor.h"     // class Performance


void MainSimulator::registerNewAtomics()
{
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Banderillero>() , "Banderillero" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Barco>() , "Barco" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Cola>() , "Cola" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Cola_F>() , "Cola_F" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generador>() , "Generador" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Monitor>() , "Monitor" ) ;
}
