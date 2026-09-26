// ?d_00244b10@@YAXXZ
// partial score=0.89 date=2026-09-23
// stlport

typedef int Int;
typedef float Real;
typedef bool Bool;

#include "../Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../reference/shims/iniexception/Common/INIException.h"
#include <new>
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#define __PRERTS_H__
#include "../Code/Libraries/Source/WWVegas/WWMath/coord.h"
#undef __PRERTS_H__

extern "C" int __cdecl strcmp(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl bfmeAtoi1027(char *);

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	const char *getSepsColon(void) const { return m_sepsColon; }
	static void parseCoord2D(INI *, void *, void *, const void *);
	static void parseReal(INI *, void *, void *, const void *);

	char m_unreconstructed_000[0x41c];
	const char *m_sepsColon;
};

struct Rva00244B10ConditionBits
{
	unsigned int m_bits;

	Rva00244B10ConditionBits() : m_bits(0) {}
	void clear() { m_bits = 0; }
};

struct Rva00244B10RankInfo
{
	Int m_rankNumber;
	AsciiString m_unitType;
	_STL::vector<Coord3D> m_positions;
	Rva00244B10ConditionBits m_grantedWeaponCondition;
	Rva00244B10ConditionBits m_revokedWeaponCondition;
	bool m_hasWeaponCondition;

	Rva00244B10RankInfo()
	{
		m_rankNumber = 0;
		m_hasWeaponCondition = false;
		m_grantedWeaponCondition.clear();
		m_revokedWeaponCondition.clear();
	}
};

class Gen008509C0;
class Gen00049A2B;
void __cdecl Rva001EB560(Gen008509C0 *, Int, Gen00049A2B *);
typedef void (__cdecl *Rva001EB560WithUserData)(INI *, Int, Gen00049A2B *, const void *);

extern Real normalizeAngle(Real);

typedef _STL::vector<Rva00244B10RankInfo *> Rva00244B10RankInfoVector;

void parseHordeContainRankInfo(INI *ini, void *instance, void *store, const void *userData)
{
	void *allocation = ::operator new(0x20);
	Rva00244B10RankInfo *entry;
	if (allocation != 0)
	{
		new (allocation) Rva00244B10RankInfo;
		entry = (Rva00244B10RankInfo *)allocation;
	}
	else
	{
		entry = 0;
	}
	Rva00244B10RankInfoVector &rankInfos = *(Rva00244B10RankInfoVector *)store;

	const char *token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token == 0 || strcmp(token, "RankNumber") != 0)
		throw INIException(3, "RankNumber expected");

	entry->m_rankNumber = bfmeAtoi1027((char *)ini->getNextToken(ini->getSepsColon()));

	token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token == 0 || strcmp(token, "UnitType") != 0)
		throw INIException(3, "UnitType expected");

	entry->m_unitType = ini->getNextToken(ini->getSepsColon());
	token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token == 0)
		goto appendAfterCondition;

checkPosition:
	if (strcmp(token, "Position") == 0)
	{
		Coord2D position2D;
		Coord3D position3D;
		INI::parseCoord2D(ini, 0, &position2D, 0);
		position3D.x = position2D.x;
		position3D.y = position2D.y;
		position3D.z = 0;
		entry->m_positions.push_back(position3D);
		token = ini->getNextTokenOrNull(ini->getSepsColon());
		if (token == 0)
			goto appendAfterCondition;
		if (strcmp(token, "Z") != 0)
			goto checkAfterToken;
		goto readNextToken;
	}

	if (strcmp(token, "Facing") == 0)
	{
		Real facing;
		INI::parseReal(ini, 0, &facing, 0);
		facing = ((volatile Real &)facing) * *(const Real *)0x010AF3F4 * *(const Real *)0x01087B10;
		Int lastPosition = (Int)entry->m_positions.size() - 1;
		Coord3D *positionsBegin = entry->m_positions.begin();
		positionsBegin[lastPosition].z = normalizeAngle(facing);
		goto readNextToken;
	}

	if (strcmp(token, "GrantedWeaponCondition") == 0)
	{
		entry->m_hasWeaponCondition = true;
		((Rva001EB560WithUserData)Rva001EB560)(ini, 0,
			(Gen00049A2B *)&entry->m_grantedWeaponCondition, 0);
		goto appendAfterCondition;
	}

	if (strcmp(token, "RevokedWeaponCondition") == 0)
	{
		entry->m_hasWeaponCondition = true;
		((Rva001EB560WithUserData)Rva001EB560)(ini, 0,
			(Gen00049A2B *)&entry->m_revokedWeaponCondition, 0);
		goto appendAfterCondition;
	}

	throw INIException(3, "'Position' expected");

readNextToken:
	const char *separators = ini->getSepsColon();
	_ReadWriteBarrier();
	token = ini->getNextTokenOrNull(separators);
checkAfterToken:
	if (token != 0)
		goto checkPosition;
	rankInfos.push_back(entry);
	return;

	appendAfterCondition:
	_ReadWriteBarrier();
	rankInfos.push_back(entry);
}
