// ?gatherDebugStats@W3DDisplay@@IAEXXZ
// partial score=0.7837416481069043 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/displaystring /Iinputs/reference/shims/displaystringmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// Native bank for W3DDisplay::gatherDebugStats, RVA 006F0300, 4490 bytes.
// Complete BFME diagnostic sections recovered from retail and the original twin.
// Probe: native 4490 bytes, 322 relocations, 971 differing masked positions;
// normalized instruction shape .988. Strict resolver: zero unresolved symbols.
// Remaining drift: AsciiString temporary homes; draw kept in EBX instead of
// retail's EBP + stack home; selected Object is spilled instead of retained in
// EBX; status-any loop induction; several inline accessor register cycles.
// Nested selected-object guards and moving the body getter after the position
// copy improve normalized shape to .990, but produce 4474B (not this best-score
// bank). Native STLport _Unchecked_test recovers the exact flag-test operations.
// Outer-object reuse, declaration order, direct receiver ABI view, accessor
// forwarding, and separate hovered/selected pointers did not remove residue.
// Caller: 006F3FC0+45 -> ILT 00022BEC -> 006F0300, guarded by callback pointer
// 0002F9F0. This caller follows the reference draw's StatDebugDisplay guard.
// The old incomplete name/byte lift is left intact; this file is evidence only.
// t=25 model=GPT-6; no new pins or production-source edits.
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

// FILE: W3DDisplay.cpp ///////////////////////////////////////////////////////
//
// W3D Implementation for the Game Display which is responsible for creating
// and maintaning the entire visual display
//
// Author: Colin Day, April 2001
//
///////////////////////////////////////////////////////////////////////////////

static void drawFramerateBar(void);

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <windows.h>
#include <io.h>
#include <time.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/ThingFactory.h"
#include "Common/GameEngine.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/FileSystem.h"
#include "Common/LocalFileSystem.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingTemplate.h"
#include "Common/GameLOD.h"
#include "Common/DrawModule.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"

#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"
#include "GameClient/GraphDraw.h"
#include "GameClient/Line2D.h"
#include "GameClient/Mouse.h"
#include "GameClient/GlobalLanguage.h"
#include "GameClient/Water.h"

#include "GameNetwork/NetworkInterface.h"
#include "Common/ModelState.h"
#include "Lib/BaseType.h"
#include "W3DDevice/Common/W3DConvert.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "GameClient/Display.h"
#include "WW3D2/lightenvironment.h"
#define protected protected: void saveScreenShot(char *image, UnsignedInt width, UnsignedInt height); void captureScreen(char *image, UnsignedInt rowBytes); protected
#include "W3DDevice/GameClient/W3DDisplay.h"
#undef protected
#include "W3DDevice/GameClient/W3DGameClient.h"
#include "W3DDevice/GameClient/W3DFileSystem.h"
#include "W3DDevice/GameClient/W3DDynamicLight.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DTerrainTracks.h"
#include "W3DDevice/GameClient/W3DWater.h"
#include "W3DDevice/GameClient/W3DVideoBuffer.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "W3DDevice/GameClient/W3DDebugDisplay.h"
#include "W3DDevice/GameClient/W3DProjectedShadow.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "WWMath/WWMath.h"
#include "WWLib/Registry.h"
#include "WW3D2/WW3D.h"
#include "WW3D2/PredLod.h"
#include "WW3D2/Part_Emt.h"
#include "WW3D2/Part_Ldr.h"
#include "WW3D2/DX8Caps.h"
#include "WW3D2/WW3DFormat.h"
#include "WW3D2/agg_def.h"
#include "WW3D2/Render2DSentence.h"
#include "WW3D2/SortingRenderer.h"
#include "WW3D2/Textureloader.h"
#include "WW3D2/DX8WebBrowser.h"
#include "WW3D2/Mesh.h"
#include "WW3D2/HLOD.h"
#include "WW3D2/Meshmatdesc.h"
#include "WW3D2/Meshmdl.h"
#include "WW3D2/rddesc.h"
#include "targa.h"
#include "Lib/BaseType.h"

#include "GameLogic/ScriptEngine.h"		// For TheScriptEngine - jkmcd
#include "GameLogic/GameLogic.h"
#ifdef DUMP_PERF_STATS
#include "GameLogic/PartitionManager.h"
#endif

#include "WinMain.h"


inline Int64 getPerformanceCounter()
{
	Int64 tmp;
	QueryPerformanceCounter((LARGE_INTEGER*)&tmp);
	return tmp;
}

inline Int64 getPerformanceCounterFrequency()
{
	Int64 tmp;
	QueryPerformanceFrequency((LARGE_INTEGER*)&tmp);
	return tmp;
}

class FontLibraryBFMERetail {
public: GameFont *getFont(AsciiString *name, Real size, unsigned char style);
};
struct Rva006F0300Language {
    char m_prefix[0xc4];
    AsciiString m_nativeDebugDisplayName;
    int m_nativeDebugDisplaySize;
    bool m_nativeDebugDisplayBold;
};
struct Rva006F0300Display {
    char m_prefix[0x18c];
    DisplayString *m_displayStrings[15];
    char m_gap1c8[0xa8];
    DisplayString *m_benchmarkDisplayString;
};
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t> *)this)->releaseBuffer(); }

template<class T> inline bool StringBase<T>::isEmpty() const { return !m_data || !m_data->length; }
template<class T> inline bool StringBase<T>::isNotEmpty() const { return !isEmpty(); }
inline int rva006F0300Length(const char *p) { return strlen(p); }
inline int rva006F0300Length(const wchar_t *p) { return wcslen(p); }
template<class T> inline void StringBase<T>::set(const T *text) { set(text, text ? rva006F0300Length(text) : 0); }
template<class T> inline void StringBase<T>::concat(const T *text) { concat(text, text ? (int)wcslen((const wchar_t *)text) : 0); }
template<class T, int Offset> inline T &rva006F0300Field(void *object) { return *(T *)((char *)object + Offset); }
template<class T, int Offset> inline T rva006F0300Value(void *object) { return rva006F0300Field<T,Offset>(object); }
class Rva00937140 { public: static void store(int); };
int Rva00937160Get(); int Rva00937220Get(); int Rva00937230Get();
int Rva00937260Get(); int Rva00937270Get(); int Rva009372B0Get(); int Rva009372D0Get();
int Rva00751F30Get(); int Rva00751F40Get();
class Rva000C7BF0Holder { public: int get(int) const; };
class Rva000C7C30Holder { public: int get(int) const; };
class Gen_000c7c10 { public: int m(); };
class Gen_003837A0 { public: int bfmeDepth() const; };
struct Rva006F0300View {
virtual void slot0() = 0;
virtual void slot4() = 0;
virtual void slot8() = 0;
virtual void slotC() = 0;
virtual void slot10() = 0;
virtual void slot14() = 0;
virtual void slot18() = 0;
virtual void slot1C() = 0;
virtual void slot20() = 0;
virtual void slot24() = 0;
virtual void slot28() = 0;
virtual void slot2C() = 0;
virtual void slot30() = 0;
virtual void slot34() = 0;
virtual void slot38() = 0;
virtual void slot3C() = 0;
virtual void slot40() = 0;
virtual void slot44() = 0;
virtual void slot48() = 0;
virtual void slot4C() = 0;
virtual void slot50() = 0;
virtual void slot54() = 0;
virtual void slot58() = 0;
virtual void slot5C() = 0;
virtual void slot60() = 0;
virtual void slot64() = 0;
virtual void slot68() = 0;
virtual void slot6C() = 0;
virtual void slot70() = 0;
virtual void slot74() = 0;
virtual void slot78() = 0;
virtual void slot7C() = 0;
virtual void slot80() = 0;
virtual void slot84() = 0;
virtual void slot88() = 0;
virtual void slot8C() = 0;
virtual void slot90() = 0;
virtual void slot94() = 0;
virtual void slot98() = 0;
virtual void slot9C() = 0;
virtual void slotA0() = 0;
virtual void slotA4() = 0;
virtual void slotA8() = 0;
virtual void slotAC() = 0;
virtual void slotB0() = 0;
virtual void slotB4() = 0;
virtual void slotB8() = 0;
virtual void slotBC() = 0;
virtual void slotC0() = 0;
virtual void slotC4() = 0;
virtual void slotC8() = 0;
virtual void slotCC() = 0;
virtual void slotD0() = 0;
virtual void slotD4() = 0;
virtual void slotD8() = 0;
virtual void slotDC() = 0;
virtual void slotE0() = 0;
virtual void slotE4() = 0;
virtual void slotE8() = 0;
virtual void slotEC() = 0;
virtual void slotF0() = 0;
virtual void slotF4() = 0;
virtual void slotF8() = 0;
virtual float getAngle() = 0;
virtual void slot100() = 0;
virtual void slot104() = 0;
virtual void slot108() = 0;
virtual void slot10C() = 0;
virtual void slot110() = 0;
virtual void getPosition(Coord3D *) = 0;
virtual void slot118() = 0;
virtual void slot11C() = 0;
virtual float getZoom() = 0;
virtual void slot124() = 0;
virtual void slot128() = 0;
virtual void slot12C() = 0;
virtual void slot130() = 0;
virtual void slot134() = 0;
virtual void slot138() = 0;
virtual void slot13C() = 0;
virtual void slot140() = 0;
virtual float getTerrainHeightUnderCamera() = 0;
virtual void slot148() = 0;
virtual float getCurrentHeightAboveGround() = 0;
virtual void slot150() = 0;
virtual void slot154() = 0;
virtual float getFieldOfView() = 0;
virtual void slot15C() = 0;
virtual void slot160() = 0;
virtual void screenToTerrain(const ICoord2D *, Coord3D *, int) = 0;
virtual void slot168() = 0;
virtual void slot16C() = 0;
virtual void slot170() = 0;
virtual void slot174() = 0;
virtual void slot178() = 0;
virtual void slot17C() = 0;
virtual void slot180() = 0;
virtual void slot184() = 0;
virtual void slot188() = 0;
virtual void slot18C() = 0;
virtual void slot190() = 0;
virtual void slot194() = 0;
virtual void slot198() = 0;
virtual void slot19C() = 0;
virtual void slot1A0() = 0;
virtual void slot1A4() = 0;
virtual void slot1A8() = 0;
virtual float getFXPitch() = 0;
virtual void slot1B0() = 0;
virtual void slot1B4() = 0;
virtual void slot1B8() = 0;
virtual void slot1BC() = 0;
virtual void slot1C0() = 0;
virtual void slot1C4() = 0;
virtual void slot1C8() = 0;
virtual void slot1CC() = 0;
virtual void slot1D0() = 0;
virtual void slot1D4() = 0;
virtual void slot1D8() = 0;
virtual void slot1DC() = 0;
virtual void slot1E0() = 0;
virtual void slot1E4() = 0;
virtual void slot1E8() = 0;
virtual void slot1EC() = 0;
virtual void slot1F0() = 0;
virtual void slot1F4() = 0;
virtual void slot1F8() = 0;
virtual void slot1FC() = 0;
virtual void slot200() = 0;
virtual void slot204() = 0;
virtual void slot208() = 0;
virtual void slot20C() = 0;
virtual void slot210() = 0;
virtual void slot214() = 0;
virtual void slot218() = 0;
virtual void slot21C() = 0;
virtual void slot220() = 0;
virtual void slot224() = 0;
virtual float getPitch() = 0;
};
struct Rva006F0300Terrain {
virtual void slot0() = 0;
virtual void slot4() = 0;
virtual void slot8() = 0;
virtual void slotC() = 0;
virtual void slot10() = 0;
virtual void slot14() = 0;
virtual void slot18() = 0;
virtual void slot1C() = 0;
virtual void slot20() = 0;
virtual void slot24() = 0;
virtual void slot28() = 0;
virtual void slot2C() = 0;
virtual void slot30() = 0;
virtual void slot34() = 0;
virtual void slot38() = 0;
virtual void slot3C() = 0;
virtual void slot40() = 0;
virtual void slot44() = 0;
virtual void slot48() = 0;
virtual void slot4C() = 0;
virtual void slot50() = 0;
virtual void slot54() = 0;
virtual void slot58() = 0;
virtual void slot5C() = 0;
virtual void slot60() = 0;
virtual void slot64() = 0;
virtual void slot68() = 0;
virtual void slot6C() = 0;
virtual void slot70() = 0;
virtual void slot74() = 0;
virtual void slot78() = 0;
virtual void slot7C() = 0;
virtual void slot80() = 0;
virtual void slot84() = 0;
virtual void slot88() = 0;
virtual void slot8C() = 0;
virtual void slot90() = 0;
virtual void slot94() = 0;
virtual void slot98() = 0;
virtual void slot9C() = 0;
virtual void slotA0() = 0;
virtual void slotA4() = 0;
virtual void slotA8() = 0;
virtual void slotAC() = 0;
virtual void slotB0() = 0;
virtual void slotB4() = 0;
virtual void slotB8() = 0;
virtual void slotBC() = 0;
virtual void slotC0() = 0;
virtual void slotC4() = 0;
virtual void slotC8() = 0;
virtual void slotCC() = 0;
virtual void slotD0() = 0;
virtual void slotD4() = 0;
virtual void slotD8() = 0;
virtual void slotDC() = 0;
virtual void slotE0() = 0;
virtual void slotE4() = 0;
virtual void slotE8() = 0;
virtual void slotEC() = 0;
virtual void slotF0() = 0;
virtual void slotF4() = 0;
virtual void slotF8() = 0;
virtual void slotFC() = 0;
virtual void slot100() = 0;
virtual void slot104() = 0;
virtual void slot108() = 0;
virtual void slot10C() = 0;
virtual void slot110() = 0;
virtual void slot114() = 0;
virtual void slot118() = 0;
virtual void slot11C() = 0;
virtual void slot120() = 0;
virtual void slot124() = 0;
virtual void slot128() = 0;
virtual void slot12C() = 0;
virtual void slot130() = 0;
virtual void slot134() = 0;
virtual void slot138() = 0;
virtual void slot13C() = 0;
virtual void slot140() = 0;
virtual void slot144() = 0;
virtual void slot148() = 0;
virtual void slot14C() = 0;
virtual void slot150() = 0;
virtual void slot154() = 0;
virtual void slot158() = 0;
virtual void slot15C() = 0;
virtual void slot160() = 0;
virtual void slot164() = 0;
virtual void slot168() = 0;
virtual void slot16C() = 0;
virtual void slot170() = 0;
virtual void slot174() = 0;
virtual void slot178() = 0;
virtual void slot17C() = 0;
virtual void slot180() = 0;
virtual void slot184() = 0;
virtual void slot188() = 0;
virtual void slot18C() = 0;
virtual void slot190() = 0;
virtual void slot194() = 0;
virtual void slot198() = 0;
virtual void slot19C() = 0;
virtual void slot1A0() = 0;
virtual void slot1A4() = 0;
virtual void slot1A8() = 0;
virtual void slot1AC() = 0;
virtual void slot1B0() = 0;
virtual void slot1B4() = 0;
virtual void slot1B8() = 0;
virtual void slot1BC() = 0;
virtual void slot1C0() = 0;
virtual void slot1C4() = 0;
virtual void slot1C8() = 0;
virtual void slot1CC() = 0;
virtual void slot1D0() = 0;
virtual void slot1D4() = 0;
virtual void slot1D8() = 0;
virtual void slot1DC() = 0;
virtual void slot1E0() = 0;
virtual void slot1E4() = 0;
virtual void slot1E8() = 0;
virtual void slot1EC() = 0;
virtual void slot1F0() = 0;
virtual void slot1F4() = 0;
virtual void slot1F8() = 0;
virtual void slot1FC() = 0;
virtual void slot200() = 0;
virtual void slot204() = 0;
virtual void slot208() = 0;
virtual void slot20C() = 0;
virtual void slot210() = 0;
virtual void slot214() = 0;
virtual void slot218() = 0;
virtual void slot21C() = 0;
virtual void slot220() = 0;
virtual void slot224() = 0;
virtual void slot228() = 0;
virtual void slot22C() = 0;
virtual void slot230() = 0;
virtual void slot234() = 0;
virtual void slot238() = 0;
virtual void slot23C() = 0;
virtual void slot240() = 0;
virtual int getNumExtraBlendTiles() = 0;
};
struct Rva006F0300Client {
virtual void slot0() = 0;
virtual void slot4() = 0;
virtual void slot8() = 0;
virtual void slotC() = 0;
virtual void slot10() = 0;
virtual void slot14() = 0;
virtual void slot18() = 0;
virtual void slot1C() = 0;
virtual void slot20() = 0;
virtual void slot24() = 0;
virtual void slot28() = 0;
virtual Drawable *findDrawableByID(DrawableID) = 0;
};
struct Rva006F0300UI {
virtual void slot0() = 0;
virtual void slot4() = 0;
virtual void slot8() = 0;
virtual void slotC() = 0;
virtual void slot10() = 0;
virtual void slot14() = 0;
virtual void slot18() = 0;
virtual void slot1C() = 0;
virtual void slot20() = 0;
virtual void slot24() = 0;
virtual void slot28() = 0;
virtual void slot2C() = 0;
virtual void slot30() = 0;
virtual void slot34() = 0;
virtual void slot38() = 0;
virtual void slot3C() = 0;
virtual void slot40() = 0;
virtual void slot44() = 0;
virtual void slot48() = 0;
virtual void slot4C() = 0;
virtual void slot50() = 0;
virtual void slot54() = 0;
virtual void slot58() = 0;
virtual void slot5C() = 0;
virtual void slot60() = 0;
virtual void slot64() = 0;
virtual void slot68() = 0;
virtual void slot6C() = 0;
virtual void slot70() = 0;
virtual void slot74() = 0;
virtual void slot78() = 0;
virtual void slot7C() = 0;
virtual void slot80() = 0;
virtual void slot84() = 0;
virtual void slot88() = 0;
virtual void slot8C() = 0;
virtual void slot90() = 0;
virtual void slot94() = 0;
virtual void slot98() = 0;
virtual void slot9C() = 0;
virtual void slotA0() = 0;
virtual void slotA4() = 0;
virtual void slotA8() = 0;
virtual void slotAC() = 0;
virtual void slotB0() = 0;
virtual void slotB4() = 0;
virtual void slotB8() = 0;
virtual void slotBC() = 0;
virtual void slotC0() = 0;
virtual void slotC4() = 0;
virtual void slotC8() = 0;
virtual void slotCC() = 0;
virtual void slotD0() = 0;
virtual void slotD4() = 0;
virtual void slotD8() = 0;
virtual void slotDC() = 0;
virtual void slotE0() = 0;
virtual void slotE4() = 0;
virtual void slotE8() = 0;
virtual void slotEC() = 0;
virtual int getSelectCount() = 0;
virtual void slotF4() = 0;
virtual void slotF8() = 0;
virtual void slotFC() = 0;
virtual void slot100() = 0;
virtual Drawable *getFirstSelectedDrawable() = 0;
virtual void slot108() = 0;
virtual void slot10C() = 0;
virtual void slot110() = 0;
virtual void slot114() = 0;
virtual void slot118() = 0;
virtual void slot11C() = 0;
virtual void slot120() = 0;
virtual void slot124() = 0;
virtual void slot128() = 0;
virtual void slot12C() = 0;
virtual void slot130() = 0;
virtual void slot134() = 0;
virtual void slot138() = 0;
virtual void slot13C() = 0;
virtual void slot140() = 0;
virtual void slot144() = 0;
virtual void slot148() = 0;
virtual DrawableID getMousedOverDrawableID() = 0;
};
struct Rva006F0300Particle {
virtual void slot0() = 0;
virtual void slot4() = 0;
virtual void slot8() = 0;
virtual void slotC() = 0;
virtual void slot10() = 0;
virtual void slot14() = 0;
virtual void slot18() = 0;
virtual void slot1C() = 0;
virtual void slot20() = 0;
virtual int getOnScreenParticleCount() = 0;
};
struct Rva006F0300Network {
virtual void slot0() = 0;
virtual void slot4() = 0;
virtual void slot8() = 0;
virtual void slotC() = 0;
virtual void slot10() = 0;
virtual void slot14() = 0;
virtual void slot18() = 0;
virtual void slot1C() = 0;
virtual void slot20() = 0;
virtual void slot24() = 0;
virtual void slot28() = 0;
virtual void slot2C() = 0;
virtual void slot30() = 0;
virtual void slot34() = 0;
virtual void slot38() = 0;
virtual void slot3C() = 0;
virtual void slot40() = 0;
virtual void slot44() = 0;
virtual void slot48() = 0;
virtual void slot4C() = 0;
virtual void slot50() = 0;
virtual void slot54() = 0;
virtual void slot58() = 0;
virtual void slot5C() = 0;
virtual void slot60() = 0;
virtual void slot64() = 0;
virtual void slot68() = 0;
virtual void slot6C() = 0;
virtual void slot70() = 0;
virtual void slot74() = 0;
virtual void slot78() = 0;
virtual void slot7C() = 0;
virtual void slot80() = 0;
virtual void slot84() = 0;
virtual void slot88() = 0;
virtual void slot8C() = 0;
virtual void slot90() = 0;
virtual void slot94() = 0;
virtual void slot98() = 0;
virtual void slot9C() = 0;
virtual void slotA0() = 0;
virtual void slotA4() = 0;
virtual void slotA8() = 0;
virtual void slotAC() = 0;
virtual void slotB0() = 0;
virtual void slotB4() = 0;
virtual void slotB8() = 0;
virtual void slotBC() = 0;
virtual void slotC0() = 0;
virtual void slotC4() = 0;
virtual void slotC8() = 0;
virtual void slotCC() = 0;
virtual void slotD0() = 0;
virtual int slotD4(int) = 0;
};
struct Rva006F0300TerrainLogic {
virtual void slot0() = 0;
virtual void slot4() = 0;
virtual void slot8() = 0;
virtual void slotC() = 0;
virtual void slot10() = 0;
virtual void slot14() = 0;
virtual void slot18() = 0;
virtual float getLayerHeight(float,float,PathfindLayerEnum,void *,bool) = 0;
};
struct Rva006F0300Body {
virtual void slot0() = 0;
virtual void slot4() = 0;
virtual void slot8() = 0;
virtual void slotC() = 0;
virtual float getHealth() = 0;
};

inline const ThingTemplate *Rva006F0300Template(void *thing) {
    const ThingTemplate *t=rva006F0300Field<const ThingTemplate *,4>(thing);
    if (t) t = (const ThingTemplate *)t->getFinalOverride();
    return t;
}
inline int Rva006F0300OwnedCount(void *player) {
    int count=0;
    if (player) count=rva006F0300Field<int,0x3d4>(player)-rva006F0300Field<int,0x3d8>(player);
    return count;
}
class BFMERopeDrawable { public: const Coord3D *getPosition() const; };
extern const char g_bfmeTokA450[];
extern const char *const Rva00209130StatusNames[];
struct Rva006F0300Drawable {
    char m_prefix[0xfc]; Object *m_object;
    char m_gap100[0x150]; std::bitset<304> m_modelFlags;
    Object *getObject() { return m_object; }
    const std::bitset<304> &getModelFlags() const { return m_modelFlags; }
};
struct Rva006F0300Object {
    char m_prefix[0x74]; int m_id; char m_gap78[0xc]; AsciiString m_name;
    char m_gap88[8]; std::bitset<86> m_status;
    char m_gap9c[0x164]; Rva006F0300Body *m_body;
    const AIUpdateInterface *m_ai;
    int getID() const { return m_id; }
    const AsciiString &getName() const { return m_name; }
    const std::bitset<86> &getStatus() const { return m_status; }
    Rva006F0300Body *getBody() const { return m_body; }
    const AIUpdateInterface *getAI() const { return m_ai; }
};
void W3DDisplay::gatherDebugStats( void )
{
	Rva006F0300Display *bfme = (Rva006F0300Display *)this;
	static UnsignedInt s_framesRenderedSinceLastUpdate = 0;
	static Int64 s_lastUpdateTime64 = 0;
	static double s_timeSinceLastUpdateInSecs = 0.0;
	static Int s_drawCallsSinceLastUpdate = 0;
	static Int s_sortedPolysSinceLastUpdate = 0;

	// allocate the display strings if needed
	if( bfme->m_displayStrings[0] == NULL )
	{
		GameFont *font;
		if (TheGlobalLanguageData && ((Rva006F0300Language *)TheGlobalLanguageData)->m_nativeDebugDisplayName.isNotEmpty())
		{
			font=((FontLibraryBFMERetail *)TheFontLibrary)->getFont(
				&((Rva006F0300Language *)TheGlobalLanguageData)->m_nativeDebugDisplayName,
				((Rva006F0300Language *)TheGlobalLanguageData)->m_nativeDebugDisplaySize,
				((Rva006F0300Language *)TheGlobalLanguageData)->m_nativeDebugDisplayBold);
		}
		else
			font = ((FontLibraryBFMERetail *)TheFontLibrary)->getFont( &AsciiString("FixedSys"), 8.0f, FALSE );

		for (int i = 0; i < 15; i++)
		{
			if (bfme->m_displayStrings[i] == NULL)
			{
				bfme->m_displayStrings[i] = TheDisplayStringManager->newDisplayString();
				DEBUG_ASSERTCRASH( bfme->m_displayStrings[i], ("Failed to create DisplayString") );
				bfme->m_displayStrings[i]->setFont( font );
			}
		}

	}  // end if

	if (bfme->m_benchmarkDisplayString == NULL)
	{
		GameFont *thisFont = ((FontLibraryBFMERetail *)TheFontLibrary)->getFont( &AsciiString("FixedSys"), 8.0f, FALSE );
		bfme->m_benchmarkDisplayString = TheDisplayStringManager->newDisplayString();
		DEBUG_ASSERTCRASH( bfme->m_benchmarkDisplayString, ("Failed to create DisplayString") );
		bfme->m_benchmarkDisplayString->setFont( thisFont );
	}

	++s_framesRenderedSinceLastUpdate;
  s_drawCallsSinceLastUpdate += Rva009372D0Get();
	s_sortedPolysSinceLastUpdate += Rva009372B0Get();

	Int64 freq64 = getPerformanceCounterFrequency();
	Int64 time64 = getPerformanceCounter();

	s_timeSinceLastUpdateInSecs = ((double)(time64 - s_lastUpdateTime64) / (double)(freq64));


	// we update stats on a delay
	const Real UPDATE_RATE_SECS = 2.0;
	if( s_timeSinceLastUpdateInSecs >= UPDATE_RATE_SECS || (rva006F0300Field<bool,0xa96>(TheWritableGlobalData)) )
	{	
		UnicodeString unibuffer, unibuffer2;
		UnicodeString fpsString;
			
		// setup texture stats
		Rva00937140::store(1);

		// frames per second	
		double fps = (Real)s_framesRenderedSinceLastUpdate / s_timeSinceLastUpdateInSecs;
		double drawsPerFrame = Rva009372D0Get(); //(Real)s_drawCallsSinceLastUpdate / (Real)s_framesRenderedSinceLastUpdate;
		double sortPolysPerFrame = Rva009372B0Get();  //(Real)s_sortedPolysSinceLastUpdate / (Real)s_framesRenderedSinceLastUpdate;
		double skinDrawsPerFrame = Rva00937220Get();
 double skinPolysPerFrame = Rva00937230Get();

		if (fps<0.1) fps = 0.1;

		double ms = 1000.0f/fps;


		//Int LOD = TheGlobalData->m_terrainLOD;
		//unibuffer.format( UnicodeString(L"FPS: %.2f, %.2fms mapLOD=%d draws: %.2f sort %.2f"), fps, ms, LOD, drawsPerFrame,sortPolysPerFrame);
		unibuffer.format( UnicodeString(L"FPS: %.2f, %.2fms draws: %.2f skins: %.2f(%.2f) sort %.2f"), fps, ms, drawsPerFrame,skinPolysPerFrame,skinDrawsPerFrame,sortPolysPerFrame);
		if ((rva006F0300Field<bool,0x1e>(TheWritableGlobalData))) 
		{
			unibuffer2.format( UnicodeString(L", FPSLock %d"),(rva006F0300Field<int,0x24>(TheWritableGlobalData)));
			unibuffer.concat(unibuffer2);
		}

		fpsString.format( UnicodeString(L"FPS: %.2f"), fps);
		bfme->m_benchmarkDisplayString->setText( fpsString );

		Int polyPerFrame = Rva00937260Get();

		// check for debug D3D
		Bool debugD3D=false;
		RegistryClass registry ("Software\\Microsoft\\Direct3d");
		if (registry.Is_Valid ()) {
			if (registry.Get_Int ("LoadDebugRuntime", 0) == 1) {
				debugD3D = true;
			}
		}
		if (debugD3D) {
			unibuffer.concat(L", DEBUG D3D");
		}

		bfme->m_displayStrings[FPS]->setText( unibuffer );

		// Actual GameLogic frame number
		unibuffer.format( UnicodeString(L"Frame: %d"), (rva006F0300Value<unsigned,0x3c>(TheGameLogic)));
		bfme->m_displayStrings[Frame]->setText( unibuffer );

		// polygons this frame	
		unibuffer.format( UnicodeString(L"Polygons: per frame %d, per second %d"), polyPerFrame,
				(Int)(polyPerFrame*fps));
		bfme->m_displayStrings[Polygons]->setText( unibuffer );

		// vertices this frame
		unibuffer.format( UnicodeString(L"Vertices: %d"), Rva00937270Get() );
		bfme->m_displayStrings[Vertices]->setText( unibuffer );		

        unibuffer.format(UnicodeString(L"Models w/ shareable skins: %d, groups: %d, avg models/group: %.2f"),
            Rva00751F30Get(), Rva00751F40Get(), (double)Rva00751F30Get() / (Rva00751F40Get() ? Rva00751F40Get() : 1));
        bfme->m_displayStrings[12]->setText(unibuffer);
        if (ThePlayerList && rva006F0300Field<void *,0xc>(ThePlayerList)) {
            char *points = (char *)rva006F0300Field<void *,0xc>(ThePlayerList) + 0x30;
            unibuffer.format(UnicodeString(L"CmdPoints Total:%d, Used:%d (allies:%d), Available:%d (allies:%d)"),
                ((Gen_000c7c10 *)points)->m(), ((Rva000C7BF0Holder *)points)->get(0), ((Rva000C7BF0Holder *)points)->get(1),
                ((Rva000C7C30Holder *)points)->get(0), ((Rva000C7C30Holder *)points)->get(1));
        } else unibuffer.set(L"");
        bfme->m_displayStrings[13]->setText(unibuffer);
        if (TheScriptEngine) unibuffer.format(UnicodeString(L"Campaign AI: %d"),rva006F0300Value<int,0x17620>(TheScriptEngine));
        else unibuffer.set(L"");
        bfme->m_displayStrings[14]->setText(unibuffer);
        unibuffer.format(UnicodeString(L"Video RAM: %d"),Rva00937160Get());
        bfme->m_displayStrings[VideoRam]->setText(unibuffer);

		s_lastUpdateTime64 = time64;
		s_timeSinceLastUpdateInSecs = 0.0f;
		s_framesRenderedSinceLastUpdate = 0;
		s_drawCallsSinceLastUpdate = 0;
		s_sortedPolysSinceLastUpdate = 0;

		// terrain stats
        unibuffer.format(UnicodeString(L"3-Way Blends: %d, Shoreline Blends: %d"),
            ((Rva006F0300Terrain *)TheTerrainRenderObject)->getNumExtraBlendTiles(),
            rva006F0300Value<int,0x30c4>(TheTerrainRenderObject));
        bfme->m_displayStrings[11]->setText(unibuffer);

		// misc debug info
		Coord3D camPos;
		((Rva006F0300View *)TheTacticalView)->getPosition(&camPos);
		Real zoom = ((Rva006F0300View *)TheTacticalView)->getZoom();
		Real pitch = ((Rva006F0300View *)TheTacticalView)->getPitch();
		Real FXPitch = ((Rva006F0300View *)TheTacticalView)->getFXPitch();
		Real angle = ((Rva006F0300View *)TheTacticalView)->getAngle();
		Real FOV = ((Rva006F0300View *)TheTacticalView)->getFieldOfView();
		//Real desiredHeight = ((Rva006F0300View *)TheTacticalView)->getHeightAboveGround();
		Real terrainHeight = ((Rva006F0300View *)TheTacticalView)->getTerrainHeightUnderCamera();
		Real actualHeightAboveGround = ((Rva006F0300View *)TheTacticalView)->getCurrentHeightAboveGround();

		unibuffer.format( UnicodeString(L"Camera zoom: %g, pitch: %g/%g, yaw: %g, pos: %g, %g, %g, FOV: %g\n       Height above ground: %g Terrain height: %g"),
												zoom,
												pitch,
												FXPitch,
												angle,
												camPos.x, camPos.y, camPos.z,
												FOV,
												/*
												zoom,
												pitch * 180.0f / PI,
												FXPitch * 180.0f / PI,
												angle * 180.0f / PI,
												camPos.x, camPos.y, camPos.z,
												FOV * 180.0f / PI,
												*/
												actualHeightAboveGround, terrainHeight );
		bfme->m_displayStrings[DebugInfo]->setText( unibuffer );

		// display the keyboard modifier and mouse states.
		unibuffer.format( UnicodeString(L"States: ") );
		if( TheKeyboard->isShift() )
		{
			unibuffer.concat( L"Shift(" );
			if( TheKeyboard->getModifierFlags() & KEY_STATE_LSHIFT )
			{
				unibuffer.concat( L"L" );
			}
			if( TheKeyboard->getModifierFlags() & KEY_STATE_RSHIFT )
			{
				unibuffer.concat( L"R" );
			}
			unibuffer.concat( L") " );
		}
		if( TheKeyboard->isCtrl() )
		{
			unibuffer.concat( L"Ctrl(" );
			if( TheKeyboard->getModifierFlags() & KEY_STATE_LCONTROL )
			{
				unibuffer.concat( L"L" );
			}
			if( TheKeyboard->getModifierFlags() & KEY_STATE_RCONTROL )
			{
				unibuffer.concat( L"R" );
			}
			unibuffer.concat( L") " );
		}
		if( TheKeyboard->isAlt() )
		{
			unibuffer.concat( L"Alt(" );
			if( TheKeyboard->getModifierFlags() & KEY_STATE_LALT )
			{
				unibuffer.concat( L"L" );
			}
			if( TheKeyboard->getModifierFlags() & KEY_STATE_RALT )
			{
				unibuffer.concat( L"R" );
			}
			unibuffer.concat( L") " );
		}

		const MouseIO *mouseStatus = &rva006F0300Field<MouseIO,0x4d10>(TheMouse);

		if( mouseStatus->leftState )
		{
			unibuffer.concat( L"LMB " );
		}
		if( mouseStatus->middleState )
		{
			unibuffer.concat( L"MMB " );
		}
		if( mouseStatus->rightState )
		{
			unibuffer.concat( L"RMB " );
		}

		Object *object = NULL;
		Drawable *draw = ((Rva006F0300Client *)TheGameClient)->findDrawableByID( ((Rva006F0300UI *)TheInGameUI)->getMousedOverDrawableID() );
		if( draw  )
			object = ((Rva006F0300Drawable *)draw)->getObject();
		if( object )
		{
			unibuffer2.format( UnicodeString(L"Moused over object: %S (%d) "), rva006F0300Field<AsciiString,0x20>((void *)Rva006F0300Template(object)).str(), ((Rva006F0300Object *)object)->getID() );
            unibuffer.concat(unibuffer2);
            if (rva006F0300Field<bool,0x487>((void *)Rva006F0300Template(object))) {
                unibuffer2.format(UnicodeString(L"Level %d. "),rva006F0300Field<int,0x28>(rva006F0300Field<void *,0x210>(object)));
                unibuffer.concat(unibuffer2);
            }
        }
        else
        {
            unibuffer.concat( L"Moused over object: TERRAIN " );
		}
		
		bfme->m_displayStrings[ KEY_MOUSE_STATES ]->setText( unibuffer );

		//display the x and y mouse coordinates
		const MouseIO *mouseIO = &rva006F0300Field<MouseIO,0x4d10>(TheMouse);
		Coord3D worldPos;
		((Rva006F0300View *)TheTacticalView)->screenToTerrain(&mouseIO->pos, &worldPos, 0);
		unibuffer.format( UnicodeString(L"Mouse position: screen: (%d, %d), world: (%g, %g, %g)"), mouseIO->pos.x, mouseIO->pos.y,
			worldPos.x, worldPos.y, worldPos.z);
		bfme->m_displayStrings[MousePosition]->setText( unibuffer );
		
		//display the number of particles in the world and being displayed on screen
		Int totalParticles = rva006F0300Field<int,0x84>(TheParticleSystemManager);
		Int onScreenParticleCount = ((Rva006F0300Particle *)TheParticleSystemManager)->getOnScreenParticleCount();
		unibuffer.format( UnicodeString(L"Particles: %d in world, %d being displayed"), totalParticles, onScreenParticleCount );
		bfme->m_displayStrings[Particles]->setText( unibuffer );

		//display the number of objects in the world
		UnsignedInt objCount = ((Gen_003837A0 *)TheGameLogic)->bfmeDepth();
		UnsignedInt objScreenCount = rva006F0300Field<unsigned,0xc0>(TheGameClient);

		unibuffer.format( UnicodeString(L"Objects: %d in world, %d being displayed, %d owned by local player"), objCount, objScreenCount, Rva006F0300OwnedCount(rva006F0300Field<void *,0xc>(ThePlayerList)) );
		bfme->m_displayStrings[Objects]->setText( unibuffer );

        if (TheNetwork) {
            unibuffer.set(L"SequentialBuffers: ");
            for (int i=0; i<9; ++i) {
                unibuffer2.format(UnicodeString(L"%d "),((Rva006F0300Network *)TheNetwork)->slotD4(i));
                unibuffer.concat(unibuffer2);
            }
            bfme->m_displayStrings[DebugInfo]->setText(unibuffer);
        }
		// selected object info stats
		unibuffer.format( UnicodeString(L"Select Info: '%d' drawables selected"), ((Rva006F0300UI *)TheInGameUI)->getSelectCount() );
		


		//Sorry, guys. I need a special kluge here to get constantdebug results for angry mob.
		//Do no be cross with me.
		//if there is not exactly one drawable selected it will report on the moused-over drawable
		if (((Rva006F0300UI *)TheInGameUI)->getSelectCount() == 1)
			draw = ((Rva006F0300UI *)TheInGameUI)->getFirstSelectedDrawable();


        if (draw && ((Rva006F0300Drawable *)draw)->getObject()) {
            Object *obj = ((Rva006F0300Drawable *)draw)->getObject();
            AsciiString objectName;
            objectName.set("No-Name");
            if (!((Rva006F0300Object *)obj)->getName().isEmpty()) objectName = ((Rva006F0300Object *)obj)->getName();
            Rva006F0300Body *body = ((Rva006F0300Object *)obj)->getBody();
            Coord3D pos = *((BFMERopeDrawable *)draw)->getPosition();
            PathfindLayerEnum layer = TheTerrainLogic->getHighestLayerForDestination(&pos,false);
            float groundZ = ((Rva006F0300TerrainLogic *)TheTerrainLogic)->getLayerHeight(pos.x,pos.y,layer,0,true);
            unibuffer.format(UnicodeString(L"Select Info: '%S'(%S)[%d][%d] at (%.3f,%.3f,%.3f) groundZ@pos: %.3f Health: %.3f"),
                rva006F0300Field<AsciiString,0x20>((void *)Rva006F0300Template(draw)).str(), objectName.str(), draw->getID(),
                ((Rva006F0300Drawable *)draw)->getObject() ? ((Rva006F0300Object *)((Rva006F0300Drawable *)draw)->getObject())->getID() : 0,
                ((BFMERopeDrawable *)draw)->getPosition()->x,((BFMERopeDrawable *)draw)->getPosition()->y,((BFMERopeDrawable *)draw)->getPosition()->z,
                groundZ,body->getHealth());
            unibuffer.concat(L"\nModelFlags: ");
            int lineCount=0;
            for (int i=0; i<304; ++i) {
                if (((Rva006F0300Drawable *)draw)->getModelFlags()._Unchecked_test(i)) {
                    unibuffer2.format(UnicodeString(L"%S "),((const char *const *)g_bfmeTokA450)[i]);
                    unibuffer.concat(unibuffer2);
                    if (++lineCount==6) { lineCount=0; unibuffer.concat(L"\n"); }
                }
            }
            unibuffer.concat(L"\nStatus: ");
            if (((Rva006F0300Object *)obj)->getStatus().any()) {
                int lineCount=0;
                for (int i=0;i<86;++i) {
                    if (((Rva006F0300Object *)obj)->getStatus()._Unchecked_test(i)) {
                        unibuffer2.format(UnicodeString(L"%S "),Rva00209130StatusNames[i]);
                        unibuffer.concat(unibuffer2);
                        if (++lineCount==6) { lineCount=0; unibuffer.concat(L"\n"); }
                    }
                }
            }
            unibuffer.concat(L"\nAIStateType: ");
            const AIUpdateInterface *ai = ((Rva006F0300Object *)obj)->getAI();
            if (ai) {
                unibuffer2.format(UnicodeString(L"%d \n"),ai->getAIStateType());
                unibuffer.concat(unibuffer2);
            }
        }
        bfme->m_displayStrings[10]->setText(unibuffer);
    }
}
