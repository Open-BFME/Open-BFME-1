// ?getKey@Rva002A0A40@@SAIXZ
// cl: /DNDEBUG /MD /EHsc
#include "../../../Include/Common/NameKeyType.h"
class NameKeyGenerator { public: NameKeyType nameToKey(const char* name); };
extern NameKeyGenerator* TheNameKeyGenerator;
struct Rva002A0A40 { static unsigned int getKey(); };
unsigned int Rva002A0A40::getKey()
{
	static unsigned int key = TheNameKeyGenerator->nameToKey("RainOfFireUpdate");
	return key;
}
