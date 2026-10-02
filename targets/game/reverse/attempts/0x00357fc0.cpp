// ?ReadParameter@Parameter@@SAPAV1@AAVDataChunkInput@@@Z
// partial score=0.992 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// The readable Zero Hour twin appears in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp`.
// Matched callers `ScriptAction::ParseAction` at 0x00358370 and `Condition::ParseConditionDataChunk` at 0x0035A510 reach this body through an ILT.
// The body retains the `Upgrade_*CaptureBuilding`, `CRUSHER`, `CRUSHABLE`, `OVERLAPPABLE`, `MISSILE`, and `SMALL_MISSILE` literals.
//
// Retail allocates a 0x28-byte `Parameter` with plain `operator new` and no vptr, so its members sit four bytes above their Zero Hour offsets.
// Retail stores the single bit index from 0x001C09C0 in `m_int` for `OBJECT_STATUS`; Zero Hour builds a mask.
// Retail also maps `CASH_GENERATOR` to `SUPPLY_GATHERING_CENTER` for `KIND_OF_PARAM`.
// The four parameter values keep the Zero Hour ordinals: `COORD3D` 0x10, `KIND_OF_PARAM` 0x1B, `UPGRADE` 0x21, and `OBJECT_STATUS` 0x29.

#include <string.h>
#include "ascii_string.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

// Retail inlines these StringBase<char> members at every site in this body.
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
			pParm->m_string = kindofNames[pParm->m_int];
		}
	}

	return pParm;
}
