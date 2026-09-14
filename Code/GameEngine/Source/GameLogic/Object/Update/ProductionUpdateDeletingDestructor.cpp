// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME: ProductionUpdate scalar-deleting destructor at retail RVA
// 0x0029E300 (30 bytes).  The exact constructor at 0x0029C9E0 installs
// primary vtable 0x010C0F34 whose first slot reaches this wrapper through
// ILT 0x0002FEAA; the matched complete destructor at 0x0029D460 drains the
// production queue and releases the owning production-update state.

class ProductionUpdate
{
public:
	virtual ~ProductionUpdate();
};

void forceProductionUpdateDeletingDestructor()
{
	ProductionUpdate value;
}
