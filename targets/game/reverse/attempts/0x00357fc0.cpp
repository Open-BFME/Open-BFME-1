// ?ReadParameter@Parameter@@SAPAV1@AAVDataChunkInput@@@Z
// partial score=0.992 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ?ReadParameter@Parameter@@SAPAV1@AAVDataChunkInput@@@Z
// readable ZH body: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp
//
// BFME Parameter::ReadParameter for retail 0x00357FC0 (748 B). Identity: the
// matched ScriptAction::ParseAction (0x00358370) and
// Condition::ParseConditionDataChunk call it through the link thunk, and the
// body carries Zero Hour's heal-old-files literals ("Upgrade_*CaptureBuilding",
// "CRUSHER", "CRUSHABLE", "OVERLAPPABLE", "MISSILE", "SMALL_MISSILE").
//
// Differences from Zero Hour, all read off the retail bytes: plain operator
// new for the 0x28-byte Parameter (no memory pool, no vtable, so ZH's members
// sit 4 bytes lower); no OBJECT_TYPE "Fundamentalist" rename; OBJECT_STATUS
// stores the single bit index from the 0x001C09C0 name lookup in m_int
// instead of building a status mask; and KIND_OF_PARAM also renames
// CASH_GENERATOR to SUPPLY_GATHERING_CENTER. Parameter type values keep their
// ZH ordinals (COORD3D 0x10, KIND_OF_PARAM 0x1B, UPGRADE 0x21,
// OBJECT_STATUS 0x29).

#include <string.h>
#include "ascii_string.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

// Retail inlines these StringBase<char> members at every site in this body.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template <> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }

static inline int stringLength(const char *str)
{
	return str ? strlen(str) : 0;
}

template <> inline void StringBase<char>::set(const char *str)
{
	set(str, stringLength(str));
}

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Errors.h
enum ErrorCode { ERROR_BUG = 0xDEAD0001 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkInput
{
public:
	Int readInt();
	Real readReal();
	AsciiString readAsciiString();
};

// ZH ObjectStatusMaskType: the matched 0x001C09C0 lookup walks the object
// status names at 0x012A6670.
template <int NUMBITS> class BitFlags
{
public:
	BitFlags() { m_bits[0] = 0; m_bits[1] = 0; }
	static Int getSingleBitFromName(const char *token);

private:
	unsigned int m_bits[2];
};
typedef BitFlags<45> ObjectStatusMaskType;

// ZH KindOfMaskType::getBitNames(); the same retail array 0x012AA068 that
// Parameter::WriteParameter indexes (Parameter_WriteParameter_Thunk.cpp).
extern const char *TheKindOfBitNames[0xB5];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	enum ParameterType
	{
		COORD3D = 0x10,
		KIND_OF_PARAM = 0x1B,
		UPGRADE = 0x21,
		OBJECT_STATUS = 0x29
	};

	Parameter(ParameterType type, Int val = 0) :
		m_paramType(type),
		m_initialized(false),
		m_int(val),
		m_real(0)
	{
		m_coord.x = 0; m_coord.y = 0; m_coord.z = 0;
	}

	ParameterType getParameterType(void) const { return m_paramType; }
	static Parameter *ReadParameter(DataChunkInput &file);

protected:
	void setInt(Int i) { m_int = i; }
	void setCoord3D(const Coord3D *pLoc)
	{
		if (m_paramType == COORD3D) {
			m_coord = *pLoc;
		}
	}

private:
	ParameterType m_paramType;				///< retail this+0x00
	Bool m_initialized;						///< retail this+0x04
	Int m_int;								///< retail this+0x08
	Real m_real;							///< retail this+0x0C
	AsciiString m_string;					///< retail this+0x10
	Coord3D m_coord;						///< retail this+0x14
	ObjectStatusMaskType m_objectStatus;	///< retail this+0x20
};

Parameter *Parameter::ReadParameter(DataChunkInput &file)
{
	Parameter *pParm = new Parameter((ParameterType)file.readInt());
	pParm->m_initialized = true;
	if (pParm->getParameterType() == COORD3D) {
		Coord3D pos;
		pos.x = file.readReal();
		pos.y = file.readReal();
		pos.z = file.readReal();
		pParm->setCoord3D(&pos);
	}
	else
	{
		pParm->m_int = file.readInt();
		pParm->m_real = file.readReal();
		pParm->m_string = file.readAsciiString();
	}

	if (pParm->getParameterType() == UPGRADE)
	{
		// quick hack to make obsolete capture building upgrades switch to the new one. jba.
		if (pParm->m_string.compare("Upgrade_AmericaRangerCaptureBuilding") == 0 ||
			pParm->m_string.compare("Upgrade_ChinaRedguardCaptureBuilding") == 0 ||
			pParm->m_string.compare("Upgrade_GLARebelCaptureBuilding") == 0)
		{
			((StringBase<char> *)&pParm->m_string)->set("Upgrade_InfantryCaptureBuilding");
		}
	}

	if (pParm->getParameterType() == OBJECT_STATUS)
	{
		pParm->setInt(ObjectStatusMaskType::getSingleBitFromName(((const StringBase<char> *)&pParm->m_string)->str()));
	}

	if (pParm->getParameterType() == KIND_OF_PARAM)
	{
		// Need to change the string to an integer
		const char **kindofNames = TheKindOfBitNames;
		if (!((const StringBase<char> *)&pParm->m_string)->isEmpty())
		{
			Bool found = false;
			for (int i = 0; kindofNames[i]; ++i)
			{
				if (pParm->m_string.compareNoCase(kindofNames[i]) == 0)
				{
					pParm->setInt(i);
					found = true;
					break;
				}
				if( !pParm->m_string.compareNoCase( "CRUSHER" ) )
				{
					pParm->setInt(i);
					found = true;
					break;
				}
				else if( !pParm->m_string.compareNoCase( "CRUSHABLE" ) )
				{
					pParm->setInt(i);
					found = true;
					break;
				}
				else if( !pParm->m_string.compareNoCase( "OVERLAPPABLE" ) )
				{
					pParm->setInt(i);
					found = true;
					break;
				}
				else if( !pParm->m_string.compareNoCase( "CASH_GENERATOR" ) )
				{
					pParm->m_string.format( "SUPPLY_GATHERING_CENTER" );
					found = true;
					break;
				}
				else if( !pParm->m_string.compareNoCase( "MISSILE" ) )
				{
					//MISSILE was split into two kinds -- SMALL_MISSILE and BALLISTIC_MISSILE.
					pParm->m_string.format( "SMALL_MISSILE" );
					for( i = 0; kindofNames[i]; ++i )
					{
						if (pParm->m_string.compareNoCase("SMALL_MISSILE") == 0)
						{
							pParm->setInt(i);
							found = true;
							break;
						}
					}
				}
			}
			if (!found)
			{
				throw ERROR_BUG;
			}
		}
		else
		{
			// Seems weird, but this is so WB will load them into the proper format.
			pParm->m_string = kindofNames[pParm->m_int];
		}
	}

	return pParm;
}
