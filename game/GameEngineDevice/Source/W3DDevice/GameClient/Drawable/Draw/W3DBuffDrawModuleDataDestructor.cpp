// cl: /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// W3DBuffDrawModuleData's adjacent exact constructor initializes the owning
// AsciiString at +0x08 and a flag at +0x0C.  The retail destructor tears down
// that string under an EH guard and restores its module-data base vptr.

#include "ascii_string.h"

// The restored base vptr is retail 0x01073744, ??_7BfmeBaseVUQ@@6B@ (symbols.csv).
class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() {}
};

class W3DBuffDrawModuleData : public BfmeBaseVUQ
{
public:
	virtual ~W3DBuffDrawModuleData();

private:
	unsigned int m_word;
	AsciiString m_modelName;
	bool m_flag;
};

W3DBuffDrawModuleData::~W3DBuffDrawModuleData()
{
}
