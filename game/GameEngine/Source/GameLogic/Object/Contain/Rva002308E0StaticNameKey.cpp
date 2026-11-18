// ?getKey@Rva002308E0@@SAIXZ
// cl: /DNDEBUG /MD /EHsc
#include "../../../../Include/Common/NameKeyType.h"
class NameKeyGenerator { public: NameKeyType nameToKey(const char* name); };
extern NameKeyGenerator* TheNameKeyGenerator;
struct Rva002308E0 { static unsigned int getKey(); };
unsigned int Rva002308E0::getKey()
{
	static unsigned int key = TheNameKeyGenerator->nameToKey("AODHordeContain");
	return key;
}
