// cl: /O2 /DNDEBUG /MD /EHsc
//
// Retail 0x0025E880: GloriousChargeUpdateModuleData's complete destructor.
// The matched ??_G (0x0025E850) reaches it through ILT 0x00048C11, pinned
// as ??1GloriousChargeUpdateModuleData@@UAE@XZ; ilt_oracle CONFIRMS that
// name at 0x0025E880. The class adds nothing to destroy and the base
// destructor re-seats the vptr at once, so retail drops this class's own
// store (novtable here): the body is a single tail jump to the
// SpecialAbilityUpdateModuleData destructor (ILT 0x0001980D -> matched
// 0x002A5CC0).

class SpecialAbilityUpdateModuleData
{
public:
	virtual ~SpecialAbilityUpdateModuleData();
};

class __declspec(novtable) GloriousChargeUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	virtual ~GloriousChargeUpdateModuleData();
};

GloriousChargeUpdateModuleData::~GloriousChargeUpdateModuleData()
{
}
