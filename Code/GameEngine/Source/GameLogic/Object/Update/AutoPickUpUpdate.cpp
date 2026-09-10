// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/stringinline
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
*/

// AutoPickUpUpdateModuleData::iniParseEatObjectEntry, retail RVA 0x00282B40.
// The 12-byte local record is a filter handle followed by two parsed percents.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef float Real;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);
	const char *getSepsColon() const
	{
		return *(const char **)((const char *)this + 0x41c);
	}
	static void parsePercentToReal(INI *ini, void *instance, void *store,
		const void *userData);
};

// reverse/symbols.csv pins __imp___stricmp to the retail IAT VA 0x0135933c.
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char *, const char *);
extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

class INIException
{
public:
	INIException(int code, const char *format, ...);
	INIException(const INIException &other);

private:
	char *m_failureMessage;
	int m_argCount;
};

// Keep the genuine throw expression: with this eight-byte ABI MSVC 7.1 emits
// the observed direct _CxxThrowException sequence and the pinned
// __TI1?AVINIException@@ metadata, including each retail cold path.

// This is the established four-byte attribute-handle ABI.  Its constructor
// and destructor are shared ICF bodies pinned at 0x0003747A and 0x0001A401.
class Rva002DC6D0Filter
{
public:
	Rva002DC6D0Filter();
	~Rva002DC6D0Filter();

private:
	unsigned int m_handle;
};

struct AutoPickUpEatObjectEntry
{
	AutoPickUpEatObjectEntry() : m_myHealth(0), m_targetHealth(1.0f) {}

	Rva002DC6D0Filter m_filter;
	Real m_myHealth;
	Real m_targetHealth;
};

typedef char AutoPickUpFilterMustBeFourBytes[
	(sizeof(Rva002DC6D0Filter) == 4) ? 1 : -1];
typedef char AutoPickUpEatObjectEntryMustBeTwelveBytes[
	(sizeof(AutoPickUpEatObjectEntry) == 12) ? 1 : -1];

// The retail vector member is the existing 12-byte POD specialization.  The
// local record is layout-compatible but keeps its real non-trivial handle
// lifetime for the parser's constructor/destructor sequence.
struct Gen_t_00282af0_p12pod
{
	int a[3];
};

void iniParseObjectFilter(INI *ini, void *instance, void *store,
	const void *userData);

class AutoPickUpUpdateModuleData
{
public:
	static void iniParseEatObjectEntry(INI *ini, void *instance, void *store,
		const void *userData);
};

#define THROW_EAT_OBJECT_ENTRY_ERROR(format, token) \
	do { \
		throw INIException(3, format, token); \
	} while (0)

void AutoPickUpUpdateModuleData::iniParseEatObjectEntry(
	INI *ini, void *instance, void *store, const void *)
{
	AutoPickUpEatObjectEntry entry;

	const char *token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token == 0 || _stricmp(token, "MyHealth") != 0)
		THROW_EAT_OBJECT_ENTRY_ERROR(
			"AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- Expecting 'MyHealth' entry. You specified %s.",
			token);
	if (strcmp(token, "MyHealth") != 0)
		THROW_EAT_OBJECT_ENTRY_ERROR(
			"AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- Entry for 'MyHealth' is case sensitive. You specified %s.",
			token);
	INI::parsePercentToReal(ini, instance, &entry.m_myHealth, 0);

	token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token == 0 || _stricmp(token, "TargetHealth") != 0)
		THROW_EAT_OBJECT_ENTRY_ERROR(
			"AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- Expecting 'TargetHealth' entry. You specified %s.",
			token);
	if (strcmp(token, "TargetHealth") != 0)
		THROW_EAT_OBJECT_ENTRY_ERROR(
			"AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- Entry for 'TargetHealth' is case sensitive. You specified %s.",
			token);
	INI::parsePercentToReal(ini, instance, &entry.m_targetHealth, 0);

	token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token == 0 || _stricmp(token, "Filter") != 0)
		THROW_EAT_OBJECT_ENTRY_ERROR(
			"AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- Expecting 'Filter' entry. You specified %s.",
			token);
	if (strcmp(token, "Filter") != 0)
		THROW_EAT_OBJECT_ENTRY_ERROR(
			"AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- Entry for 'Filter' is case sensitive. You specified %s.",
			token);
	iniParseObjectFilter(ini, instance, &entry.m_filter, 0);

	((_STL::vector<Gen_t_00282af0_p12pod> *)store)->push_back(
		(const Gen_t_00282af0_p12pod &)entry);
}
