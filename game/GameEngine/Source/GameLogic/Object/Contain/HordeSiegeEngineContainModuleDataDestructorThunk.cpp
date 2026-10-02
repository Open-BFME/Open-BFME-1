// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: HordeSiegeEngineContainModuleData dtor.

#include "ascii_string.h"

// The matched constructor at 0x0022CB80 identifies the handle at +0x224,
// the separate word at +0x228, and the AsciiString at +0x22C.
class AttributeHandleStandIn
{
public:
	~AttributeHandleStandIn();
private:
	unsigned int m_bfmeHandle;
};

class HordeSiegeEngineContainModuleDataBase
{
public:
	virtual ~HordeSiegeEngineContainModuleDataBase();
private:
	unsigned char m_pad[0x220];
};

class __declspec(novtable) HordeSiegeEngineContainModuleData : public HordeSiegeEngineContainModuleDataBase
{
public:
	virtual ~HordeSiegeEngineContainModuleData();
private:
	AttributeHandleStandIn m_a;
	unsigned int m_228;
	AsciiString m_b;
};

// ??1HordeSiegeEngineContainModuleData@@UAE@XZ
HordeSiegeEngineContainModuleData::~HordeSiegeEngineContainModuleData()
{
}
