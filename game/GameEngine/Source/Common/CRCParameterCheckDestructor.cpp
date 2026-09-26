// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// CRCParameterCheck is the 16-byte vptr-plus-string-vector object constructed
// by GameEngine::init at 0x00079316.  Its constructor at 0x000659C0 installs
// vtable 0x01075520; slot zero reaches the scalar deleting destructor at
// 0x00065A10 through ILT 0x0001038E.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class CRCParameterCheck
{
public:
	virtual ~CRCParameterCheck();

private:
	std::vector<AsciiString> m_parameters;
};

CRCParameterCheck::~CRCParameterCheck()
{
}
