// ?removeObjectType@ObjectTypes@@QAEXABVAsciiString@@@Z
// partial score=0.90 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: ObjectTypes.cpp //////////////////////////////////////////////////////////////////////////
// Author: John McDonald, Jr.
// September 2002
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"
#include "GameLogic/ObjectTypes.h"

#include "Common/GameState.h"
#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"

// BFME's findTemplate is out of line and takes only the name; ZH's is an inline
// forwarder that passes the default check flag as a second argument.
struct BFMEThingFactory { const ThingTemplate *findTemplate(const AsciiString &name); };

//-------------------------------------------------------------------------------------------------
// ??0ObjectTypes@@ present-unmatched
ObjectTypes::ObjectTypes()
{
	// Nada
}

//-------------------------------------------------------------------------------------------------
// ??0ObjectTypes@@ present-unmatched
ObjectTypes::ObjectTypes(const AsciiString& listName) : m_listName(listName)
{
	// Nada
}

// The vector<AsciiString> COMDAT this TU reaches is the _M_insert_overflow copy
// at 0x00063700 -- the one whose element copy calls StringBase<char>'s
// constructor out of line, which 38 retail sites encode -- not the inlined-copy
// twin at 0x00757C70. No pin can bridge the two (pin_consistency:
// divergent-bodies at +0x77), so spell the element with the name the ledger
// carries at 0x00063700. Deriving keeps the layout and both string callees.
class Open2Elem063700 : public AsciiString
{
public:
	Open2Elem063700( const Open2Elem063700 &other ) : AsciiString( other ) {}
};

// The retail remove body inlines vector::erase.  Its three STL calls are
// through the ILTs below: the two find specializations and the four-byte
// __copy body at 0x000653C0.  Keep the vector's finish/begin as raw pointer
// arithmetic on the ObjectTypes layout so the erase's element-destructor call
// stays visible and the final finish store is a fresh reload of m_finish
// rather than the mid-function cached copy, matching retail+0x51.
extern void j_0004b29a();
extern void j_0004a534();
extern void j_000485ef();

static __forceinline const AsciiString *bfmeFindObjectTypeConst(
	AsciiString *first, AsciiString *last, const AsciiString &value,
	const _STL::random_access_iterator_tag &tag)
{
	typedef const AsciiString *(*Function)(AsciiString *, AsciiString *,
		const AsciiString &, const _STL::random_access_iterator_tag &);
	union { void (*raw)(void); Function call; } fn;
	fn.raw = j_0004b29a;
	return fn.call(first, last, value, tag);
}

static __forceinline AsciiString *bfmeFindObjectType(
	AsciiString *first, AsciiString *last, const AsciiString &value,
	const _STL::random_access_iterator_tag &tag)
{
	typedef AsciiString *(*Function)(AsciiString *, AsciiString *,
		const AsciiString &, const _STL::random_access_iterator_tag &);
	union { void (*raw)(void); Function call; } fn;
	fn.raw = j_0004a534;
	return fn.call(first, last, value, tag);
}

static __forceinline void bfmeCopyObjectTypes(
	AsciiString *first, AsciiString *last, AsciiString *result,
	const _STL::random_access_iterator_tag &tag)
{
	typedef AsciiString *(*Function)(AsciiString *, AsciiString *,
		AsciiString *, const _STL::random_access_iterator_tag &, int *);
	union { void (*raw)(void); Function call; } fn;
	fn.raw = j_000485ef;
	fn.call(first, last, result, tag, 0);
}

// The vendored GeneralsMD AsciiString destructor is a fully inline refcount
// decrement (Common/AsciiString.h), so calling ~AsciiString() directly here
// inlines that shape instead of retail's plain out-of-line call. Route the
// erase's element destructor through the established ??1BFMERetailAsciiString
// alias (reverse/symbols.csv, VA 0x0000D828, the same ILT retail's unwind
// funclet jumps to) so it stays a single call, matching retail+0x5c.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString();
private:
	void *m_data;
};

//-------------------------------------------------------------------------------------------------
void ObjectTypes::addObjectType(const AsciiString &objectType)
{
	if (isInSet(objectType)) {
		return;
	}

	// same +0x08 overlay as isInSet below
	struct BFMEObjectTypes { char pad[0x08]; std::vector<Open2Elem063700> m_objectTypes; };
	((BFMEObjectTypes *)this)->m_objectTypes.push_back(*(const Open2Elem063700 *)&objectType);
}

//-------------------------------------------------------------------------------------------------
// ?removeObjectType@ObjectTypes@@ present-unmatched
void ObjectTypes::removeObjectType(const AsciiString &objectType)
{
	_STL::random_access_iterator_tag tag;
	register AsciiString *finish = *(AsciiString **)((char *)this + 0x0c);
	register AsciiString *begin = *(AsciiString **)((char *)this + 0x08);
	if (bfmeFindObjectTypeConst(begin, finish, objectType, tag) == finish) {
		DEBUG_CRASH(("Attempted to remove '%s' from '%s', but it wasn't there.", objectType.str(), m_listName.str()));
		return;
	}

	AsciiString *it = bfmeFindObjectType(begin, finish, objectType, tag);
	AsciiString *next = it + 1;
	if (next != finish)
		bfmeCopyObjectTypes(next, finish, it, tag);

	char *newFinish = *(char **)((char *)this + 0x0c) - 4;
	*(char **)((char *)this + 0x0c) = newFinish;
	((BFMERetailAsciiString *)newFinish)->~BFMERetailAsciiString();
}

//-------------------------------------------------------------------------------------------------
// ?getListName@ObjectTypes@@ present-unmatched
const AsciiString& ObjectTypes::getListName() const
{
	return m_listName;
}

//-------------------------------------------------------------------------------------------------
// ?setListName@ObjectTypes@@ present-unmatched
void ObjectTypes::setListName(const AsciiString& listName)
{
	m_listName = listName;
}

//-------------------------------------------------------------------------------------------------
Bool ObjectTypes::isInSet(const AsciiString& objectType) const
{
	// m_objectTypes starts at ObjectTypes+0x08 in BFME; this tree lands it at
	// +0x0c -- one base vtable pointer fewer, the same pattern PlayerRelationMap
	// and Module show. The overlay has to be function-local: AsciiStringVec is a
	// nested typedef and does not name at file scope.
	struct BFMEObjectTypes { char pad[0x08]; AsciiStringVec m_objectTypes; };
	const BFMEObjectTypes *self = (const BFMEObjectTypes *)this;
	return (std::find(self->m_objectTypes.begin(), self->m_objectTypes.end(), objectType) != self->m_objectTypes.end());

}

//-------------------------------------------------------------------------------------------------
Bool ObjectTypes::isInSet(const ThingTemplate* objectType) const
{
	if (!objectType) {
		return FALSE;
	}

	// ThingTemplate::m_name is at +0x20 in BFME; this tree lands it at +0x10.
	return isInSet(*(const AsciiString *)((const char *)objectType + 0x20));
}

//-------------------------------------------------------------------------------------------------
Int ObjectTypes::prepForPlayerCounting( std::vector<const ThingTemplate *>& templates, std::vector<Int>& counts)
{
	// same +0x08 overlay as isInSet above
	struct BFMEObjectTypes { char pad[0x08]; AsciiStringVec m_objectTypes; };
	BFMEObjectTypes *self = (BFMEObjectTypes *)this;

	AsciiStringVecIt it;
	for (it = self->m_objectTypes.begin(); it != self->m_objectTypes.end(); ++it) {
		const ThingTemplate *templ = ((BFMEThingFactory *)TheThingFactory)->findTemplate(*it);
		if (templ) {
			templates.push_back(templ);
		}
	}

	Int retVal = templates.size();
	counts.resize(retVal);

	return retVal;
}

//-------------------------------------------------------------------------------------------------
// ?canBuildAny@ObjectTypes@@ present-unmatched
Bool ObjectTypes::canBuildAny(Player *player)
{
	AsciiStringVecIt it;
	for (it = m_objectTypes.begin(); it != m_objectTypes.end(); ++it) {
		const ThingTemplate *templ = TheThingFactory->findTemplate(*it);
		if (templ && player->canBuild(templ)) {
			return TRUE;
		}
	}

	return FALSE;
}

// ------------------------------------------------------------------------------------------------
// ?crc@ObjectTypes@@ present-unmatched
void ObjectTypes::crc(Xfer *xfer)
{

}

// ------------------------------------------------------------------------------------------------
/** Version Info:
	* 1: Initial version
	*/
// ------------------------------------------------------------------------------------------------
// ?xfer@ObjectTypes@@ present-unmatched
void ObjectTypes::xfer(Xfer *xfer)
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// list name
	xfer->xferAsciiString( &m_listName );

	// size of object types vector
	UnsignedShort objectTypesCount = m_objectTypes.size();
	xfer->xferUnsignedShort( &objectTypesCount );

	// object types data
	if( xfer->getXferMode() == XFER_SAVE )
	{

		// iterate vector
		AsciiStringVecIt it;
		for( it = m_objectTypes.begin(); it != m_objectTypes.end(); ++it )
		{

			// write type name
			xfer->xferAsciiString( &(*it) );

		}  // end for, it

	}  // end if, save
	else
	{

		// sanity, the vector should be empty when loading
		if( m_objectTypes.empty() == FALSE )
		{

			DEBUG_CRASH(( "ObjectTypes::xfer - m_objectTypes vector should be emtpy but is not!\n" ));
			throw SC_INVALID_DATA;

		}  // end if

		// read all data
		AsciiString typeName;
		for( UnsignedShort i = 0; i < objectTypesCount; ++i )
		{

			// read name
			xfer->xferAsciiString( &typeName );

			// put on vector
			m_objectTypes.push_back( typeName );

		}  // end for, i

	}  // end else, load

}

// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@ObjectTypes@@ present-unmatched
void ObjectTypes::loadPostProcess()
{

}
