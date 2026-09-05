// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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
