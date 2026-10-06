// ?getKey@Rva002A0A40@@SAIXZ
// cl: /DNDEBUG /MD /EHsc
enum NameKeyType { NAMEKEY_INVALID = 0, FORCE_NAMEKEYTYPE_LONG = 0x7fffffff };
class NameKeyGenerator { public: NameKeyType nameToKey(const char* name); };
extern NameKeyGenerator* TheNameKeyGenerator;
struct Rva002A0A40 { static unsigned int getKey(); };
unsigned int Rva002A0A40::getKey()
{
	static unsigned int key = TheNameKeyGenerator->nameToKey("RainOfFireUpdate");
	return key;
}
