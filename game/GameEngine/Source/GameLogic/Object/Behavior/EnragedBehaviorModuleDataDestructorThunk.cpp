// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: EnragedBehaviorModuleData dtor. PropagandaTower SEH pattern.

#include <vector>
#include "ascii_string.h"

extern template _STL::vector<AsciiString>::~vector();

class EnragedBehaviorModuleDataBase
{
public:
	virtual ~EnragedBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) EnragedBehaviorModuleData : public EnragedBehaviorModuleDataBase
{
public:
	virtual ~EnragedBehaviorModuleData();
private:
	_STL::vector<AsciiString> m_member;
};

// ??1EnragedBehaviorModuleData@@UAE@XZ
EnragedBehaviorModuleData::~EnragedBehaviorModuleData()
{
}
