// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTemplate<7>::parse -> INI::initFromINI(this, FieldParse).

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

namespace FXParticleSystem
{

template <int Category>
class DefaultModuleTemplate
{
public:
	void parse(INI *ini);
};

extern "C" char DefaultModuleTemplate06FieldParse;

template <int Category>
void DefaultModuleTemplate<Category>::parse(INI *ini)
{
	ini->initFromINI(this, &DefaultModuleTemplate06FieldParse);
}

template void DefaultModuleTemplate<7>::parse(INI *);

}
