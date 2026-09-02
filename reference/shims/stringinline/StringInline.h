// Canonical by-value string models for BFME bodies -- the shape that byte-matches.
//
// Use this when a body takes or builds an AsciiString / UnicodeString BY VALUE
// (in-place construction: `mov ecx,esp` + call). Two rules it encodes, both
// proven byte-exact (docs/lessons.md):
//   1. The string class must NOT be trivially copyable, or MSVC builds a local
//      and pushes a copy instead of constructing in the argument slot.
//   2. Its copy ctor and dtor must be INLINE FORWARDERS to a StringBase<T> base
//      that owns the out-of-line bodies. Declaring them out of line on the
//      string class transposes the EH saved-esp store and the ctor `this`
//      (`mov [esp+N],esp` / `mov ecx,esp`) on every flag combination.
// Retail callees: char  copy ctor 0x00887B60, dtor 0x00887940 (StringBase<char>);
//                 wide  StringBase<unsigned short> bodies are pinned likewise.
// Add only the members the body needs; keep the layout a single data pointer.

#ifndef BFME_STRING_INLINE_H
#define BFME_STRING_INLINE_H

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	const char *str( void ) const { return m_data ? m_data->m_text : ""; }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	const unsigned short *str( void ) const;
};

#endif
