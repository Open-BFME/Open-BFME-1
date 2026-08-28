// cl: /DNDEBUG /MD /EHsc
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.

// Open-BFME5: MetaMapRec default ctor zeros two dwords at +0x1c and +0x20.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h
class MetaMapRec
{
public:
	MetaMapRec();

private:
	unsigned char m_pad[0x1c];
	unsigned int m_description;
	unsigned int m_displayName;
};

// ??0MetaMapRec@@QAE@XZ
MetaMapRec::MetaMapRec()
{
	m_description = 0;
	m_displayName = 0;
}
