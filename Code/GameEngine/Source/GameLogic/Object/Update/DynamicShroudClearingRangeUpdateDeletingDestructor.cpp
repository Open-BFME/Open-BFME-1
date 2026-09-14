// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: DynamicShroudClearingRangeUpdate scalar-deleting destructor at
// retail RVA 0x0028EBC0 (30 bytes). The exact constructor at 0x0028E410,
// complete destructor at 0x0028E630, factories, pool, and landed grid-decal
// methods establish the class. The destructor ILT is 0x000465E7.

class DynamicShroudClearingRangeUpdate
{
public:
	virtual ~DynamicShroudClearingRangeUpdate();
};

void forceDynamicShroudClearingRangeUpdateDeletingDestructor()
{
	DynamicShroudClearingRangeUpdate value;
}
