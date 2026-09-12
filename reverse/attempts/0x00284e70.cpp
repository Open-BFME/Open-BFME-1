// ?rva00284E70ParseObjectName@BannerCarrierUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.32 date=2026-09-12
// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

#include <new>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

void *__cdecl operator new(UnsignedInt);
extern "C" int __cdecl strcmp(const char *, const char *);
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strcmp)
#pragma intrinsic(strlen)

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	~RetailLayoutString();
	void set(const char *text, int length);
	void *m_data;
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *delimiters);
	const char *getNextToken(const char *delimiters);
	static int scanInt(const char *text);
	unsigned char m_prefix[0x41c];
	const char *m_tokenDelimiters;
};

class INIException
{
public:
	INIException(int count, const char *format, ...);
};

struct BannerCarrierSubObject
{
	BannerCarrierSubObject() : m_show(false) {}
	RetailLayoutString m_name;
	Bool m_show;
	unsigned char m_pad[3];
};

struct BannerCarrierObjectNameParse
{
	BannerCarrierObjectNameParse() : m_begin(0), m_end(0), m_storageEnd(0) {}
	int m_level;
	BannerCarrierSubObject **m_begin;
	BannerCarrierSubObject **m_end;
	BannerCarrierSubObject **m_storageEnd;
};

class BannerCarrierSubObjectVector
{
public:
	void append(BannerCarrierSubObject *const *value);
};

class BannerCarrierObjectNameVector
{
public:
	void append(BannerCarrierObjectNameParse *const *value);
};

class BannerCarrierUpdateModuleData
{
public:
	static void rva00284E70ParseObjectName(INI *ini, void *instance,
		void *store, const void *userData);
};

void BannerCarrierUpdateModuleData::rva00284E70ParseObjectName(
	INI *ini, void *, void *store, const void *)
{
	void *recordStorage = operator new(sizeof(BannerCarrierObjectNameParse));
	BannerCarrierObjectNameParse *allocationResult = recordStorage != 0
		? new (recordStorage) BannerCarrierObjectNameParse : 0;
	_ReadWriteBarrier();
	BannerCarrierObjectNameParse *record = allocationResult;
	const char *token = ini->getNextTokenOrNull(ini->m_tokenDelimiters);
	if (token == 0 || strcmp(token, "Level") != 0)
		throw INIException(3, "'ModelState' expected");

	record->m_level = INI::scanInt(ini->getNextToken(ini->m_tokenDelimiters));
	token = ini->getNextTokenOrNull(ini->m_tokenDelimiters);
	while (token != 0)
	{
		if (strcmp(token, "SubObject") != 0)
			throw INIException(3, "UnitType expected");

		BannerCarrierSubObject *subObject = new BannerCarrierSubObject;
		const char *showToken = ini->getNextToken(ini->m_tokenDelimiters);
		subObject->m_show = strcmp(showToken, "Show") == 0;
		const char *name = ini->getNextToken(ini->m_tokenDelimiters);
		subObject->m_name.set(name, name ? (int)strlen(name) : 0);
		((BannerCarrierSubObjectVector *)&record->m_begin)->append(&subObject);
		token = ini->getNextTokenOrNull(ini->m_tokenDelimiters);
	}

	((BannerCarrierObjectNameVector *)store)->append(&record);
}
