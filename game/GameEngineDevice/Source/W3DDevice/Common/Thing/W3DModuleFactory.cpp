// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// FILE: W3DModuleFactory.cpp /////////////////////////////////////////////////////////////////////
// Author: Colin Day, April 2001
// Desc:	 W3D specific module
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "W3DDevice/Common/W3DModuleFactory.h"
template <class T> struct BFMEW3DFactorySize { enum { VALUE = sizeof(T) }; };

class W3DDebrisDraw;
class W3DRopeDraw;
class W3DTreeDrawModuleData;
template <> struct BFMEW3DFactorySize<W3DDebrisDraw> { enum { VALUE = 0x48 }; };
template <> struct BFMEW3DFactorySize<W3DRopeDraw> { enum { VALUE = 0x54 }; };
template <> struct BFMEW3DFactorySize<W3DTreeDrawModuleData> { enum { VALUE = 0x64 }; };

template <class T, unsigned int SIZE> class BFMEW3DFactoryModuleData : public ModuleData
{
public:
	BFMEW3DFactoryModuleData();
private:
	char m_storage[SIZE - sizeof(ModuleData)];
};

template <class T> struct BFMEW3DFactoryDataChoice { typedef T Type; };
template <> struct BFMEW3DFactoryDataChoice<W3DTreeDrawModuleData>
{
	typedef BFMEW3DFactoryModuleData<W3DTreeDrawModuleData, 0x64> Type;
};

#undef MP_GLUE_ALLOCATE
#define MP_GLUE_ALLOCATE(ARGCLASS) ::operator new(BFMEW3DFactorySize<ARGCLASS>::VALUE)

#undef MAKE_STANDARD_MODULE_MACRO
#define MAKE_STANDARD_MODULE_MACRO( cls ) \
public: \
	static Module* friend_newModuleInstance( Thing *thing, const ModuleData* moduleData ) \
	{ \
		return new(cls::cls##_GLUE_NOT_IMPLEMENTED) cls(thing, moduleData); \
	} \
	virtual NameKeyType getModuleNameKey() const { static NameKeyType nk = NAMEKEY(#cls); return nk; } \
protected: \
	virtual void crc( Xfer *xfer ); \
	virtual void xfer( Xfer *xfer ); \
	virtual void loadPostProcess( void );

#undef MAKE_STANDARD_MODULE_DATA_MACRO_ABC
#define MAKE_STANDARD_MODULE_DATA_MACRO_ABC( cls, clsmd ) \
private: \
	const clsmd* get##clsmd() const { return (clsmd*)getModuleData(); } \
public: \
	static ModuleData* friend_newModuleData(INI* ini) \
	{ \
		typedef BFMEW3DFactoryDataChoice<clsmd>::Type RetailModuleDataType; \
		RetailModuleDataType* data = ::new RetailModuleDataType; \
		if (ini) ini->initFromINIMultiProc(data, clsmd::buildFieldParse); \
		return (ModuleData*)data; \
	}
#include "W3DDevice/GameClient/Module/W3DDebrisDraw.h"
#include "W3DDevice/GameClient/Module/W3DDefaultDraw.h"
#include "W3DDevice/GameClient/Module/W3DDependencyModelDraw.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/Module/W3DLaserDraw.h"
#include "W3DDevice/GameClient/Module/W3DOverlordTankDraw.h"
#include "W3DDevice/GameClient/Module/W3DOverlordTruckDraw.h"
#include "W3DDevice/GameClient/Module/W3DOverlordAircraftDraw.h"
#include "W3DDevice/GameClient/Module/W3DPoliceCarDraw.h"
#include "W3DDevice/GameClient/Module/W3DProjectileStreamDraw.h"
#include "W3DDevice/GameClient/Module/W3DRopeDraw.h"
#include "W3DDevice/GameClient/Module/W3DSupplyDraw.h"
#include "W3DDevice/GameClient/Module/W3DScienceModelDraw.h"
#include "W3DDevice/GameClient/Module/W3DTankDraw.h"
#include "W3DDevice/GameClient/Module/W3DTruckDraw.h"
#include "W3DDevice/GameClient/Module/W3DTankTruckDraw.h"
#include "W3DDevice/GameClient/Module/W3DTracerDraw.h"
#include "W3DDevice/GameClient/Module/W3DTreeDraw.h"
#include "W3DDevice/GameClient/Module/W3DPropDraw.h"

//-------------------------------------------------------------------------------------------------
/** Initialize method */
//-------------------------------------------------------------------------------------------------
// ?init@W3DModuleFactory@@ is defined by W3DModuleFactory_init.cpp.
// These private helper bodies are ledger-owned separately from the factory
// initializer. Keep their definitions reachable without defining a second
// W3DModuleFactory::init in this object.
typedef ModuleData *(*BFMEW3DNewDataProc)(INI *);
static BFMEW3DNewDataProc volatile s_keepFactoryDataProcs[] = {
	&W3DLaserDraw::friend_newModuleData,
	&W3DOverlordTankDraw::friend_newModuleData,
	&W3DTreeDraw::friend_newModuleData,
	&W3DPropDraw::friend_newModuleData,
	&W3DDependencyModelDraw::friend_newModuleData,
	&W3DProjectileStreamDraw::friend_newModuleData,
	&W3DModelDraw::friend_newModuleData,
	&W3DTruckDraw::friend_newModuleData
};

typedef Module *(*BFMEW3DNewInstanceProc)(Thing *, const ModuleData *);
static BFMEW3DNewInstanceProc volatile s_keepFactoryInstanceProcs[] = {
	&W3DDebrisDraw::friend_newModuleInstance,
	&W3DProjectileStreamDraw::friend_newModuleInstance,
	&W3DRopeDraw::friend_newModuleInstance
};

typedef Int (*BFMEW3DInterfaceMaskProc)(void);
static BFMEW3DInterfaceMaskProc volatile s_keepDrawInterfaceMask =
	&DrawModule::getInterfaceMask;
