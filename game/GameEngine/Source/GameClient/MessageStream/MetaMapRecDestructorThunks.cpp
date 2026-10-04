// cl: /DNDEBUG /MD /EHsc
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.
// Open-BFME5: MetaMapRec dtor. dual UnicodeString members @+0x1c/+0x20.

#include "../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

// Retail inlines ~UnicodeString: temporaries are released by a direct call to
// StringBase<unsigned short>::releaseBuffer (0x008881D0), not the ??1UnicodeString stub.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h
class MetaMapRec
{
public:
	~MetaMapRec();
private:
	unsigned char m_gap[0x1c];
	UnicodeString m_description;
	UnicodeString m_displayName;
};

// ??1MetaMapRec@@QAE@XZ
MetaMapRec::~MetaMapRec()
{
}

// ?forceMetaMapRecDelete@@YAXPAVMetaMapRec@@@Z absent-from-retail
// MSVC only emits ??_GMetaMapRec, the scalar deleting destructor this file also
// carries, when some `delete` in the TU asks for one.
void forceMetaMapRecDelete(MetaMapRec *rec)
{
	delete rec;
}
