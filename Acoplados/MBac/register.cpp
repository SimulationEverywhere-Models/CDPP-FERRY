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
#include "colaf.h"      // clase Cola_F
#include "barco.h"	 // clase Barco


void MainSimulator::registerNewAtomics()
{
 SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Cola_F>() , "Cola_F" ) ;
 SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Barco>() , "Barco" ) ;
}
