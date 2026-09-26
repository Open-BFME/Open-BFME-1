// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: WaterTracksObj scalar-deleting destructor at retail RVA
// 0x007ABA70 (30 bytes). The exact constructor at 0x007AB180, matched complete
// destructor at 0x007AB150, and recovered water-track allocation, binding, and
// shutdown paths establish the object. The wrapper calls the non-virtual
// destructor through ILT 0x0003DD2F before conditionally invoking delete.

class WaterTracksObj
{
public:
	~WaterTracksObj();
};

void forceWaterTracksObjDelete(WaterTracksObj *object)
{
	delete object;
}
