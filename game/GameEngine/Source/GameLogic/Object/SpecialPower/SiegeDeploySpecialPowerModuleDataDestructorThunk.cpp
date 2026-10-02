// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeDeploySpecialPowerModuleData dtor.
// Four same-type members @+0xc/+0x7c/+0xec/+0x15c.

// All four members are released through the ILT at 0x00026F35, which jumps
// to the AudioEventRTS destructor at 0x000B31F0, so they share that class's
// name.  The destructor is declared non-virtual because that call site is the
// SCALAR AudioEventRTS destructor the ledger names at 0x000B31F0; the 77-byte
// virtual body is a different address.  m_pad stays 4 bytes: the 0x6C gaps
// carry the rest of the 0x70-byte retail footprint and carry the offsets.
class AudioEventRTS
{
public:
	~AudioEventRTS();
private:
	unsigned char m_pad[4];
};

class SiegeDeploySpecialPowerModuleDataBase
{
public:
	virtual ~SiegeDeploySpecialPowerModuleDataBase() {}
private:
	unsigned char m_pad[0x8];
};

class __declspec(novtable) SiegeDeploySpecialPowerModuleData
	: public SiegeDeploySpecialPowerModuleDataBase
{
public:
	virtual ~SiegeDeploySpecialPowerModuleData();
private:
	AudioEventRTS m_a;
	unsigned char m_gap1[0x6c];
	AudioEventRTS m_b;
	unsigned char m_gap2[0x6c];
	AudioEventRTS m_c;
	unsigned char m_gap3[0x6c];
	AudioEventRTS m_d;
};

// ??1SiegeDeploySpecialPowerModuleData@@UAE@XZ
SiegeDeploySpecialPowerModuleData::~SiegeDeploySpecialPowerModuleData()
{
}
