// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// The two string members are retail's StringBase<T>::set bodies, reached through
// their shared narrow/wide addresses 0x00887C90 / 0x00888530 (the same calls
// Rva000F96A0Assign.cpp makes), so they are spelled with the real STLport names
// StringBase.cpp defines rather than with a private class of our own.
//
// This file still cannot link: ScienceInfoBase::operator= and
// Rva0039C830Mid::operator= are declared-only callees pinned at 0x00048725 and
// 0x000163BA, and both of those RVAs are five-byte ILT thunks (?j_00048725,
// ?j_000163ba) whose targets FUN_00494900 / FUN_0079c590 have no ledger row.

class ScienceInfoBase
{
public:
	ScienceInfoBase &operator=(const ScienceInfoBase &other);

private:
	char m_head[0x0C];
};

class Rva0039C830Mid
{
public:
	Rva0039C830Mid &operator=(const Rva0039C830Mid &other);

private:
	int m_00;
};

class Rva0039C830 : public ScienceInfoBase
{
	StringBase<char> m_0C;
	StringBase<unsigned short> m_10;
	Rva0039C830Mid m_14;

public:
	Rva0039C830 &operator=(const Rva0039C830 &other);
};

Rva0039C830 &Rva0039C830::operator=(const Rva0039C830 &other)
{
	ScienceInfoBase::operator=(other);
	((StringBase<char> *)&m_0C)->set(*(const StringBase<char> *)&other.m_0C);
	((StringBase<unsigned short> *)&m_10)->set(
		*(const StringBase<unsigned short> *)&other.m_10);
	m_14 = other.m_14;
	return *this;
}