// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SkyboxTextureSet::~SkyboxTextureSet, retail 0x000B84D0.
// The owning class is proven by vtable 0x01082BE4 and its matched constructor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();
private:
	void *m_data;
};

class SkyboxTextureSet
{
public:
	virtual ~SkyboxTextureSet();
private:
	AsciiString m_morningN;
	AsciiString m_morningE;
	AsciiString m_morningS;
	AsciiString m_morningW;
	AsciiString m_morningT;
};

SkyboxTextureSet::~SkyboxTextureSet()
{
}
