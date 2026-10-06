// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

class Rva005A7CF0FourStringRecord
{
public:
	Rva005A7CF0FourStringRecord(
		const AsciiString &a,
		const AsciiString &b,
		const AsciiString &c,
		const AsciiString &d);
	Rva005A7CF0FourStringRecord(const Rva005A7CF0FourStringRecord &other);

private:
	AsciiString m_a;
	AsciiString m_b;
	AsciiString m_c;
	AsciiString m_d;
};

// The four-string constructor (retail 0x005A7CF0) is emitted as an inline
// COMDAT by GameClient/MessageStream/CommandXlatVoice.cpp, whose
// pickAndPlayUnitVoiceResponse inlines it; a second, exclusive definition
// here made the link report a duplicate.

Rva005A7CF0FourStringRecord::Rva005A7CF0FourStringRecord(
	const Rva005A7CF0FourStringRecord &other) :
	m_a(other.m_a),
	m_b(other.m_b),
	m_c(other.m_c),
	m_d(other.m_d)
{
}
