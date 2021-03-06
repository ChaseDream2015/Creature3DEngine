#include "rbody/AnimationDegree.h"

using namespace rbody;

/*----------------------------------------------------------------------------
  Constructor
  ----------------------------------------------------------------------------*/
AnimationDegree::AnimationDegree()
{

    m_type = AnimationBase::DEGREE;

}


/*----------------------------------------------------------------------------
  Destructor
  ----------------------------------------------------------------------------*/
AnimationDegree::~AnimationDegree()
{
}


/*----------------------------------------------------------------------------
  Get degree that animation at given index is representing
  Throws exception out_of_range if nr isn't in range 0 <= nr < size
  -----------------------------------------------------------------------------*/
float AnimationDegree::getAnimationDegreeAt(int nr)
{

    return getAnimationFloatAt(nr);

}

/*------------------------------------------

 * $Source: /cvsroot/replicantbody/replicantbody/src/rbody/AnimationDegree.cpp,v $
 * $Revision: 1.1.1.1 $ 
 * $Date: 2005/02/06 06:52:59 $
 * $Author: deepone $ 
 * $Locker:  $

 * Description: 

 Copyright (C) Peter Sunna, VRlab, Ume?University 2001

Created: 2001-12-12

 * $Log: AnimationDegree.cpp,v $
 * Revision 1.1.1.1  2005/02/06 06:52:59  deepone
 * initial sourceforge checkin
 *
 * Revision 1.1  2002/06/20 13:23:11  sunna
 * no message
 *
 * Revision 1.2  2002/03/15 08:55:08  andersb
 * no message
 *
 * Revision 1.1.1.1  2002/03/14 20:48:40  andersb
 * First import as ReplicantBody
 *
 * Revision 1.2  2002/02/19 15:46:16  andersb
 * *** empty log message ***
 *
 * Revision 1.1.1.1  2002/01/04 08:22:40  andersb
 * Initial version
 *
 ----------------------------------------------------------------------------*/


