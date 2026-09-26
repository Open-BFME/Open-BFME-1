// cl: /DNDEBUG /MD /EHsc /DWIN32 /D_STLP_USE_STATIC_LIB /D__PLACEMENT_VEC_NEW_INLINE
// stlport
// BFME AIGroup centroid, RVA 0x00151E50, 222 bytes.
// Based on GeneralsMD AIGroup.cpp; BFME additionally requires isMobile() in
// the AI-only pass. If that pass is empty, include all non-held members.
// Keep the actual STLport list/iterator: a raw-node replica changes EBX/EBP
// assignment despite having the same pointer layout and traversal behavior.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <list>

struct Coord3D { float x, y, z; };
class AIUpdateInterface;

class Object {
public:
    bool isMobile() const;
    bool isDisabledByType(int type) const { return (m_disabledMask & (1 << type)) != 0; }
    AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
    const Coord3D *getPosition() const { return &m_position; }
private:
    unsigned char m_beforePosition[0x38];
    Coord3D m_position;
    unsigned char m_beforeDisabled[0x1a4 - 0x44];
    unsigned char m_disabledMask;
    unsigned char m_beforeAI[0x204 - 0x1a5];
    AIUpdateInterface *m_ai;
};

class AIGroup {
public:
    bool getCenter(Coord3D *center);
private:
    unsigned char m_beforeMembers[4];
    _STL::list<Object *> m_memberList;
};

bool AIGroup::getCenter( Coord3D *center )
{
	int count = 0;
	center->x = 0.0f;
	center->y = 0.0f;
	center->z = 0.0f;

	std::list<Object *>::iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{													 
		if( (*i)->isDisabledByType( 3) ) 
		{
			continue; // don't bother counting riders in the center calculation.
		}
		if (!(*i)->isMobile()) continue;
 AIUpdateInterface *ai = (*i)->getAIUpdateInterface();
		if (ai)
		{
			const Coord3D *objPos = (*i)->getPosition();
			center->x += objPos->x;
			center->y += objPos->y;
			center->z += objPos->z;
			++count;
		}
	}

	if (count == 0 && !m_memberList.empty())
	{
		/*
			if there are no AIs (eg, the team consists of a faction bldg), we can get here.

			This was originally used to offset the centers of objects moving (still used for that) and non-ais can't move.  
			So if you have a mix of ai's & not ai's, you want just the ais.
			But it seems reasonable that if there are no ai's, it returns the center of the other stuff.  Cause they won't be moving anyway.
		*/
		for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
		{
			if( (*i)->isDisabledByType( 3) ) 
			{
				continue; // don't bother counting riders in the center calculation.
			}
			const Coord3D *objPos = (*i)->getPosition();
			center->x += objPos->x;
			center->y += objPos->y;
			center->z += objPos->z;
			++count;
		}
	}

	center->x /= count;
	center->y /= count;
	center->z /= count;

	return count > 0;
}

