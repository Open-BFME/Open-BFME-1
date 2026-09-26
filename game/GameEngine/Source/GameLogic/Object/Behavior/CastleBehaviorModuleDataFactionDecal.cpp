// ?parseFactionDecal@CastleBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <vector>

// The CastleBehavior FieldParse table at VA 0x010EA0B0 points its FactionDecal
// row to this parser at VA 0x007760C0. targets/game/reverse/field_names.csv places that
// field at +0x60, where CastleBehavior::getFactionDecal reads the same vector.
// The warning at VA 0x010E9C68 also names the obsolete FactionDecal field.


extern "C" unsigned int __cdecl strlen(const char *s);
#pragma intrinsic(strlen)

extern bool __cdecl _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);

class BfmeAwakenLog
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	~RetailLayoutString() { releaseBuffer(); }
	void set(const char *s, int n);

private:
	void releaseBuffer(void);
	void *m_data;
};


class INI;
#include "../../../../Include/Common/INI/INI.h"

struct Gen_t_00375ea0_p12cd
{
	const char *m_name1;
	const char *m_name2;
	float m_value;
};

struct Gen_uw_00012cbf : Gen_t_00375ea0_p12cd
{
	Gen_uw_00012cbf() { m_name1 = 0; m_name2 = 0; }
	~Gen_uw_00012cbf();
};

struct CastleBehaviorModuleDataLayout
{
	char m_unreconstructed[0x60];
	_STL::vector<Gen_t_00375ea0_p12cd> m_entries;
};

class CastleBehaviorModuleData
{
public:
	static void parseFactionDecal(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseFactionDecal@CastleBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
void CastleBehaviorModuleData::parseFactionDecal(INI *ini, void *instance, void *, const void *)
{
	if (_bfme_debugReportingEnabled())
	{
		_bfme_debugRecordCallsite(1);
		TheBfmeAwakenDebug->slot60();
		BfmeAwakenLog *log = TheBfmeAwakenDebug->slot6C(0, 0);
		log->slot38((const char *)0x010E9C68)->slot4C(2);
	}

	Gen_uw_00012cbf entry;

	const char *token1 = ini->getNextTokenOrNull();
	if (token1 != 0)
	{
		((RetailLayoutString *)&entry.m_name1)->set(token1, token1 ? (int)strlen(token1) : 0);

		const char *token2 = ini->getNextTokenOrNull();
		if (token2 != 0)
		{
			((RetailLayoutString *)&entry.m_name2)->set(token2, token2 ? (int)strlen(token2) : 0);

			const char *token3 = ini->getNextTokenOrNull();
			if (token3 != 0)
			{
				entry.m_value = INI::scanReal(token3);
				((CastleBehaviorModuleDataLayout *)instance)->m_entries.push_back(entry);
			}
		}
	}
	else
	{
		return;
	}
}
