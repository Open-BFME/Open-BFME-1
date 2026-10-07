// cl: /DNDEBUG /MD /EHsc
//
// AITNGuardAttackAggressorState complete destructor at retail 0x0018B390
// (5 bytes). ??_GAITNGuardAttackAggressorState (0x0018B360, its own TU)
// calls it through ILT 0x00046D30; the body is one tail jump through ILT
// 0x00016725 into the base destructor 0x000A1B30, ledgered as
// ??1Rva000A1B30Holder@@QAE@XZ, with no vptr re-seat of its own. novtable
// reproduces the missing re-seat; it lives apart from the ??_G TU because a
// novtable class there would no longer emit its vftable and ??_G.

class Rva000A1B30Holder { public: ~Rva000A1B30Holder(); };

class __declspec(novtable) OwnedPtrBase000A1B30
{
public:
	virtual ~OwnedPtrBase000A1B30() { reinterpret_cast<Rva000A1B30Holder *>(this)->Rva000A1B30Holder::~Rva000A1B30Holder(); }
};

class __declspec(novtable) AITNGuardAttackAggressorState : public OwnedPtrBase000A1B30
{
public:
	virtual ~AITNGuardAttackAggressorState();
};

AITNGuardAttackAggressorState::~AITNGuardAttackAggressorState()
{
}
