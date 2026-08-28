// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTemplate<0>::parse -> INI::initFromINI(this, FieldParse).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
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

extern "C" char DefaultModuleTemplate0AFieldParse;

template <int Category>
void DefaultModuleTemplate<Category>::parse(INI *ini)
{
	ini->initFromINI(this, &DefaultModuleTemplate0AFieldParse);
}

template void DefaultModuleTemplate<0>::parse(INI *);
}
