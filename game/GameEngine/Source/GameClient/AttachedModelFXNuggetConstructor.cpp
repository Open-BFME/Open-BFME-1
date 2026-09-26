// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: clean C++ conversion of the BFME AttachedModel FX constructor.

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	FXNugget();
	virtual ~FXNugget();

private:
	unsigned char m_bfmeBaseData[0xB0];
};

class AttachedModelFXNugget : public FXNugget
{
public:
	AttachedModelFXNugget();
	virtual ~AttachedModelFXNugget();

private:
	AsciiString m_modelName;
	bool m_randomlyRotate;
	unsigned char m_padding[3];
	int m_expireTimer;
};

AttachedModelFXNugget::AttachedModelFXNugget() :
	m_randomlyRotate(false),
	m_expireTimer(0x28)
{
}
