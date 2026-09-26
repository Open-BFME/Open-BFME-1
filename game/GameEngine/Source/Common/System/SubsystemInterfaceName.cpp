// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}
};

// GameLogic::init names TheLargeGroupAudio through ILT 0x0001CE9A;
// the by-value argument and member at +4 both use narrow string bodies.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	void setName(AsciiString name);

private:
	AsciiString m_name;
};

// ?setName@SubsystemInterface@@QAEXVAsciiString@@@Z
void SubsystemInterface::setName(AsciiString name)
{
	m_name = name;
}
