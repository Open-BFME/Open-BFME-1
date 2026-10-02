// Canonical retail type of the 0x012EF1D8 singleton; pointee only, so a
// forward declaration is enough.  The definition lives in
// game_engine_subsystems.h.
class ThingFactory;

class AsciiString;
class ThingTemplate;

// TU-local BFME factory view; its matched lookup body is in
// ThingFactoryFindTemplate.cpp.
class BfmeThingFactory
{
	public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

// Canonical global at 0x012EF1D8 (?TheThingFactory@@3PAVThingFactory@@A),
// defined once in game/GameEngine/Source/Common/Thing/ThingFactory.cpp.
extern ThingFactory *TheThingFactory;

class BfmeOwnerZF
{
public:
	unsigned char m_bfmeHeadZF[0x248];
	int m_bfme248ZF;
};

class BfmeHostZF
{
public:
	void *bfmeFindZF();
};

void *BfmeHostZF::bfmeFindZF()
{
	BfmeOwnerZF *o = *(BfmeOwnerZF **)((char *)this - 0xe0);

	return const_cast<ThingTemplate *>(
		reinterpret_cast<BfmeThingFactory *>(TheThingFactory)->findTemplate(
			*reinterpret_cast<const AsciiString *>(&o->m_bfme248ZF)));
}
