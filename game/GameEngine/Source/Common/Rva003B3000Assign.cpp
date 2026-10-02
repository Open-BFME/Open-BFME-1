// cl: /O2 /Ob0 /Igame/Libraries/Source/WWVegas/WWLib

#include "string_base.h"

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva003B3000
{
	virtual void handle();
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	int m_10;
	int m_14;
	Rva0036CA00Str m_18;
	char m_1C;
	char m_1D;
	int m_20;
	int m_24;

public:
	Rva003B3000 &operator=(const Rva003B3000 &other);
};

Rva003B3000 &Rva003B3000::operator=(const Rva003B3000 &other)
{
	((StringBase<char> &)m_04).set((const StringBase<char> &)other.m_04);
	((StringBase<char> &)m_08).set((const StringBase<char> &)other.m_08);
	((StringBase<char> &)m_0C).set((const StringBase<char> &)other.m_0C);
	m_10 = other.m_10;
	m_14 = other.m_14;
	((StringBase<char> &)m_18).set((const StringBase<char> &)other.m_18);
	m_1C = other.m_1C;
	m_1D = other.m_1D;
	m_20 = other.m_20;
	m_24 = other.m_24;
	return *this;
}
