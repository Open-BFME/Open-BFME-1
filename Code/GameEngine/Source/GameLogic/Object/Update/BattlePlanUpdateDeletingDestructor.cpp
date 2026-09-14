// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: BattlePlanUpdate scalar-deleting destructor at retail RVA
// 0x00285D00 (30 bytes).  The instance constructor at 0x00286260 installs
// vtable 0x010BBF8C, whose first slot reaches this wrapper through ILT
// 0x00009E0D.  The complete virtual destructor at 0x00285650 is the matching
// body, and the recovered BattlePlanUpdate method family independently fixes
// the class identity.

class BattlePlanUpdate
{
public:
	virtual ~BattlePlanUpdate();
};

void forceBattlePlanUpdateDeletingDestructor()
{
	BattlePlanUpdate value;
}
