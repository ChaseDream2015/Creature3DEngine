/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/
//Modified by Wucaihua
#include <CRCore/crLineStipple.h>

using namespace CRCore;


crLineStipple::crLineStipple()
{
  m_factor = 1;
  m_pattern = 0xffff;
}


crLineStipple::~crLineStipple()
{
}

void crLineStipple::setFactor(int factor)
{
    m_factor = factor;
}
  
void crLineStipple::setPattern(unsigned short pattern)
{
    m_pattern = pattern;
}

#include <Driver/GLDrv/crLineStippleDrv.h>