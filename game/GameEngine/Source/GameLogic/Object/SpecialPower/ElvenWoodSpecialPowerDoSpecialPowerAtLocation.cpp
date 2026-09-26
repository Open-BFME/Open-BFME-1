// cl: /DNDEBUG /MD /EHsc
//
// ElvenWoodSpecialPowerInterface::doSpecialPowerAtLocation, retail RVA
// 0x0025CAA0 -- what casting Elven Wood on a spot does.
//
// Identity: ??0ElvenWoodSpecialPower@@ stores vftable 0x00CB4A60 at object
// offset +0x10 and this body is that table's doSpecialPowerAtLocation slot,
// the slot the shared base body 0x0026A620 fills for powers that do not
// override it; no other power's table points here.  `this` is therefore the
// SpecialPowerModuleInterface sub-object: -0x08 is the Object, -0x0C the module
// data, -0x10 the ElvenWoodSpecialPower module.
//
// The override refuses while the object is disabled, without a location, or
// while the module data's name token at +0x21C is absent or empty, then runs
// the base doSpecialPowerAtLocation and one further module call at 0x0025C220
// that has no identity yet.  The opaque SpecialPowerLocation and
// SpecialPowerCommandOptions stand in for the base argument types; only their
// pointer width is proven here.


class ObjectFields
{
public:
	unsigned char m_lead[ 0x1a4 ];
	int m_disabledMask;
};

struct ElvenWoodNameToken
{
	unsigned char m_lead[ 4 ];
	unsigned short m_count;
};

class ElvenWoodNameTokenSlot
{
public:
	ElvenWoodNameToken *get() { return m_token; }
private:
	ElvenWoodNameToken *m_token;
};

struct ElvenWoodSpecialPowerModuleData
{
};

class SpecialPowerLocation;
class SpecialPowerCommandOptions;

class ElvenWoodSpecialPower
{
public:
	void finish( SpecialPowerLocation *subject );
};

class SpecialPowerModuleInterface
{
public:
	void doSpecialPowerAtLocation( SpecialPowerLocation *subject,
		SpecialPowerCommandOptions *context );
};

class ElvenWoodSpecialPowerInterface : public SpecialPowerModuleInterface
{
public:
	void doSpecialPowerAtLocation( SpecialPowerLocation *subject,
		SpecialPowerCommandOptions *context );
};

void ElvenWoodSpecialPowerInterface::doSpecialPowerAtLocation(
	SpecialPowerLocation *subject, SpecialPowerCommandOptions *context )
{
	ObjectFields *owner = *(ObjectFields **)( (char *)this - 8 );
	if ( owner->m_disabledMask != 0 )
		return;
	if ( subject == 0 )
		return;
	ElvenWoodNameToken * volatile *tokenSlot =
		(ElvenWoodNameToken * volatile *)(
			(char *)*(ElvenWoodSpecialPowerModuleData **)( (char *)this - 0x0c ) + 0x21c );
	ElvenWoodNameToken *token = *tokenSlot;
	if ( token == 0 || token->m_count == 0 )
		return;
	SpecialPowerModuleInterface::doSpecialPowerAtLocation( subject, context );
	( (ElvenWoodSpecialPower *)( (char *)this - 0x10 ) )->finish( subject );
}
