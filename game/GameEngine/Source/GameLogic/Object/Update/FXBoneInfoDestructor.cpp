// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: FXBoneInfo destructor - destroy AsciiString at +4

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureToppleUpdate.h
class FXBoneInfo
{
public:
	~FXBoneInfo();

private:
	int m_pad;
	AsciiString m_name;
};

// ??1FXBoneInfo@@QAE@XZ
FXBoneInfo::~FXBoneInfo()
{
}
