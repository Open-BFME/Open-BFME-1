#pragma once

#include <string.h>
#include "../../../../game/Libraries/Source/WWVegas/WWLib/string_base.h"

class UnicodeString;

class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	AsciiString(char c);
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}
	AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}
	AsciiString(const char *s, int len);
	AsciiString(const AsciiString &that, int start, int len);
	AsciiString(const UnicodeString &that);
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
		return *this;
	}
	AsciiString &operator=(char c);
	AsciiString &operator=(const char *s)
	{
		((StringBase<char> *)this)->set(s, s ? (int)strlen(s) : 0);
		return *this;
	}
	AsciiString &operator=(const UnicodeString &that);
	AsciiString &operator+=(const AsciiString &that);
	AsciiString &operator+=(char c);
	AsciiString &operator+=(const char *s);
	AsciiString &operator+=(const UnicodeString &that);

	void __cdecl format(AsciiString fmt, ...);
	void translate(const UnicodeString &that);
	const char *str() const { return m_text ? m_text + 8 : ""; }
	int getLength() const { return ((const StringBase<char> *)this)->getLength(); }
	char getCharAt(int i) const { return ((const StringBase<char> *)this)->getCharAt(i); }
	// Inline in BFME, like str() above. INI::parseAudioEventRTS at 0x000BBB60
	// emits it as  mov eax,[..]; test eax,eax; je; cmp word ptr [eax+4],0; je
	// -- that is m_data == NULL || m_data->length == 0 against StringBase's
	// Header {int ref_count; unsigned short length; unsigned short capacity;},
	// which is the same header str()'s +8 comes from.
	bool isEmpty() const { return m_text == 0 || *(const unsigned short *)(m_text + 4) == 0; }
	bool isNotEmpty() const { return ((const StringBase<char> *)this)->isNotEmpty(); }
	bool isNone() const { return ((const StringBase<char> *)this)->isNone(); }
	bool isNotNone() const { return ((const StringBase<char> *)this)->isNotNone(); }
	const char *reverseFind(char c) const { return ((const StringBase<char> *)this)->reverseFind(c); }
	bool nextToken(AsciiString *tok, const char *delims = 0)
	{
		return ((StringBase<char> *)this)->nextToken((StringBase<char> *)tok, delims);
	}
	void clear() { ((StringBase<char> *)this)->clear(); }
	void set(const char *s) { ((StringBase<char> *)this)->set(s); }
	void set(const AsciiString &s) { ((StringBase<char> *)this)->set(*(const StringBase<char> *)&s); }
	void concat(const char *s) { ((StringBase<char> *)this)->concat(s); }
	void concat(char c) { ((StringBase<char> *)this)->concat(c); }
	void concat(const AsciiString &s) { ((StringBase<char> *)this)->concat(*(const StringBase<char> *)&s); }
	void toLower() { ((StringBase<char> *)this)->toLower(); }
	void toUpper() { ((StringBase<char> *)this)->toUpper(); }
	void trim() { ((StringBase<char> *)this)->trim(); }
	void removeLastChar() { ((StringBase<char> *)this)->removeLastChar(); }
	const char *find(char c) const { return ((const StringBase<char> *)this)->find(c); }
	bool startsWith(const char *p) const { return ((const StringBase<char> *)this)->startsWith(p); }
	bool startsWithNoCase(const char *p) const { return ((const StringBase<char> *)this)->startsWithNoCase(p); }
	bool endsWith(const char *p) const { return ((const StringBase<char> *)this)->endsWith(p); }
	bool endsWithNoCase(const char *p) const { return ((const StringBase<char> *)this)->endsWithNoCase(p); }
	int compare(const char *p) const { return ((const StringBase<char> *)this)->compare(p); }
	int compareNoCase(const char *p) const { return ((const StringBase<char> *)this)->compareNoCase(p); }
	int compare(const AsciiString &s) const { return ((const StringBase<char> *)this)->compare(*(const StringBase<char> *)&s); }
	int compareNoCase(const AsciiString &s) const { return ((const StringBase<char> *)this)->compareNoCase(*(const StringBase<char> *)&s); }

	static AsciiString TheEmptyString;

private:
	char *m_text;
};

inline bool operator==(const AsciiString &a, const AsciiString &b) { return a.compare(b) == 0; }
inline bool operator!=(const AsciiString &a, const AsciiString &b) { return a.compare(b) != 0; }
inline bool operator<(const AsciiString &a, const AsciiString &b) { return a.compare(b) < 0; }
