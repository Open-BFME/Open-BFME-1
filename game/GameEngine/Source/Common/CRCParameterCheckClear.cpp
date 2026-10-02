// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// BFME-only CRC diagnostic accumulator. Its exact xfer body names the block
// "CRCParameterCheck" and transfers this vector of AsciiString values.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class CRCParameterList
{
public:
	void erase( AsciiString *first, AsciiString *last );

	AsciiString *m_first;
	AsciiString *m_last;
	AsciiString *m_endOfStorage;
};

class CRCParameterCheck
{
public:
	virtual ~CRCParameterCheck();
	void clear();

private:
	CRCParameterList m_parameters;
};

void CRCParameterCheck::clear()
{
	CRCParameterList &parameters = m_parameters;
	parameters.erase( parameters.m_first, parameters.m_last );
}

// GameEngine::init stores the 16-byte CRCParameterCheck constructor result
// at VA 0x012ED4FC (RVA 0x0007933A). GameLogic::getCRC loads that cell at
// 0x003831A8 and sends it to the xfer body naming "CRCParameterCheck".
// The retail .data cell is four zero bytes before initialization.
CRCParameterCheck *TheCRCParameterCheck = 0;
