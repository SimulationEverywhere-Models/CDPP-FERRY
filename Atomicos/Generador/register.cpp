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
#include "generar.h"     // clase Generador


void MainSimulator::registerNewAtomics()
{
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generador>() , "Generador" ) ;
}
