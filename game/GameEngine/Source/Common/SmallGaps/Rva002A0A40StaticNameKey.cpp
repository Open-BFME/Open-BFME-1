// ?getKey@Rva002A0A40@@SAIXZ
// cl: /DNDEBUG /MD /EHsc
class NameKeyGenerator { public: unsigned int nameToKey(const char* name); };
extern NameKeyGenerator* TheNameKeyGenerator;
struct Rva002A0A40 { static unsigned int getKey(); };
unsigned int Rva002A0A40::getKey()
{
	static unsigned int key = TheNameKeyGenerator->nameToKey("RainOfFireUpdate");
	return key;
}
