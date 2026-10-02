// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0036CA00Str
{
private:
	void *m_item;
};

class Rva003ACF60
{
	virtual void handle();
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	int m_10;
	int m_14;
	char m_18;
	char m_19;
	Rva0036CA00Str m_1C;
	Rva0036CA00Str m_20;
	Rva0036CA00Str m_24;
	Rva0036CA00Str m_28;
	char m_2C;

public:
	Rva003ACF60 &operator=(const Rva003ACF60 &other);
};

Rva003ACF60 &Rva003ACF60::operator=(const Rva003ACF60 &other)
{
	reinterpret_cast<StringBase<char> &>(m_04).set(
		reinterpret_cast<const StringBase<char> &>(other.m_04));
	reinterpret_cast<StringBase<char> &>(m_08).set(
		reinterpret_cast<const StringBase<char> &>(other.m_08));
	reinterpret_cast<StringBase<char> &>(m_0C).set(
		reinterpret_cast<const StringBase<char> &>(other.m_0C));
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_19 = other.m_19;
	reinterpret_cast<StringBase<char> &>(m_1C).set(
		reinterpret_cast<const StringBase<char> &>(other.m_1C));
	reinterpret_cast<StringBase<char> &>(m_20).set(
		reinterpret_cast<const StringBase<char> &>(other.m_20));
	reinterpret_cast<StringBase<char> &>(m_24).set(
		reinterpret_cast<const StringBase<char> &>(other.m_24));
	reinterpret_cast<StringBase<char> &>(m_28).set(
		reinterpret_cast<const StringBase<char> &>(other.m_28));
	m_2C = other.m_2C;
	return *this;
}
