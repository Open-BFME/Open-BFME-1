// ?getKey@Rva002308E0@@SAIXZ
// cl: /DNDEBUG /MD /EHsc
enum NameKeyType { NAMEKEY_INVALID = 0, FORCE_NAMEKEYTYPE_LONG = 0x7fffffff };
class NameKeyGenerator { public: NameKeyType nameToKey(const char* name); };
extern NameKeyGenerator* TheNameKeyGenerator;
struct Rva002308E0 { static unsigned int getKey(); };
unsigned int Rva002308E0::getKey()
{
	static unsigned int key = TheNameKeyGenerator->nameToKey("AODHordeContain");
	return key;
}
