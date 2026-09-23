// ?parseUpgradeTexture@SubObjectsUpgradeModuleData@@SAXPAVINI@@PAX1PBX@Z
// partial score=1.0 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oi
// stlport
// SubObjectsUpgradeModuleData::parseUpgradeTexture (BFME-only; not in ZH).
// Identity: SubObjectsUpgrade::friend_newModuleData (0x0012B7F0) hands the
// builder 0x002D9310 to INI::initFromINIMultiProc; that builder adds the
// field table at VA 0x010CE0A8 whose "UpgradeTexture" row names ILT thunk
// 0x00033839 -> this body, storing into the vector at ModuleData +0x94.
// The record type is not named by any witness, so it keeps an address name.

#pragma intrinsic(strlen)
extern "C" unsigned int __cdecl strlen(const char *text);

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	void set(const char *text, int length);
	void set(const char *text) { set(text, text ? (int)strlen(text) : 0); }

private:
	void *m_data;
};

class BFMERetailAsciiString : public RetailLayoutString
{
public:
	BFMERetailAsciiString(const char *text);
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *separators = 0);
	static int scanInt(const char *text);
};

struct Rva002D8C10Record
{
	BFMERetailAsciiString m_first;
	RetailLayoutString m_second;
	int m_number;

	Rva002D8C10Record() : m_first(""), m_second(), m_number(0) {}
};

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class SubObjectsUpgradeModuleData
{
public:
	static void parseUpgradeTexture(INI *ini, void *instance, void *store, const void *userData);
};

void SubObjectsUpgradeModuleData::parseUpgradeTexture(INI *ini, void *, void *store, const void *)
{
	Rva002D8C10Record *record = new Rva002D8C10Record;

	const char *token = ini->getNextTokenOrNull();
	if (token)
		record->m_first.set(token);
	else
		record->m_first.set("");

	token = ini->getNextTokenOrNull();
	if (token)
		record->m_number = INI::scanInt(token);
	else
		record->m_number = 0;

	token = ini->getNextTokenOrNull();
	if (token)
		record->m_second.set(token);
	else
		record->m_second.set((const char *)0);

	((_STL::vector<Rva002D8C10Record *> *)store)->push_back(record);
}
