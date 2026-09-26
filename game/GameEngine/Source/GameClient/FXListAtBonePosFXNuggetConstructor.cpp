// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Clean C++ reconstruction of the BFME FX-at-bone-position nugget constructor.

#include "ascii_string.h"

class FXList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	FXNugget();
	virtual ~FXNugget();

protected:
	int m_nuggetType;

private:
	unsigned char m_bfmeBaseData[0xAC];
};

class FXListAtBonePosFXNugget : public FXNugget
{
public:
	FXListAtBonePosFXNugget();
	virtual ~FXListAtBonePosFXNugget();

private:
	const FXList *m_fx;
	AsciiString m_boneName;
};

FXListAtBonePosFXNugget::FXListAtBonePosFXNugget()
{
	m_fx = 0;
	m_boneName.clear();
	m_nuggetType = 10;
}
