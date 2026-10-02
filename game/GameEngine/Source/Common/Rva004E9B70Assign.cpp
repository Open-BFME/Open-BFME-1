// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva00630D00UStr
{
public:
	Rva00630D00UStr &operator=(const Rva00630D00UStr &other);

private:
	void *m_item;
};

class Rva004E9B70
{
	int m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	int m_10;
	Rva00630D00UStr m_14;
	Rva00630D00UStr m_18;

public:
	Rva004E9B70 &operator=(const Rva004E9B70 &other);
};

Rva004E9B70 &Rva004E9B70::operator=(const Rva004E9B70 &other)
{
	m_00 = other.m_00;
	reinterpret_cast<StringBase<char> *>(&m_04)->set(
		*reinterpret_cast<const StringBase<char> *>(&other.m_04));
	reinterpret_cast<StringBase<char> *>(&m_08)->set(
		*reinterpret_cast<const StringBase<char> *>(&other.m_08));
	reinterpret_cast<StringBase<char> *>(&m_0C)->set(
		*reinterpret_cast<const StringBase<char> *>(&other.m_0C));
	m_10 = other.m_10;
	reinterpret_cast<StringBase<unsigned short> *>(&m_14)->set(
		*reinterpret_cast<const StringBase<unsigned short> *>(&other.m_14));
	reinterpret_cast<StringBase<unsigned short> *>(&m_18)->set(
		*reinterpret_cast<const StringBase<unsigned short> *>(&other.m_18));
	return *this;
}
