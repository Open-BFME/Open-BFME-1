// Canonical retail type of the 0x012EF1D8 singleton; pointee only, so a
// forward declaration is enough.  The definition lives in
// game_engine_subsystems.h.
class ThingFactory;

// TU-local view of the same object, kept for the member call shape.
struct Rva0020AA00Registry
{
	void *bfmeLookupZF(void *key);
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

	return ((Rva0020AA00Registry *)TheThingFactory)->bfmeLookupZF(&o->m_bfme248ZF);
}
