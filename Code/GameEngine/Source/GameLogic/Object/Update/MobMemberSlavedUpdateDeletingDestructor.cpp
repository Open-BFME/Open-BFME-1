// cl: /DNDEBUG /MD /EHsc

// Open-BFME: MobMemberSlavedUpdate scalar-deleting destructor at retail
// 0x001FB900 (30 bytes).  The unique matched constructor at 0x001FB5D0 and
// complete virtual destructor at 0x001FB0C0 establish the class identity;
// the complete destructor owns the eight MobMemberSlave links and base
// teardown.

class MobMemberSlavedUpdate
{
public:
	__declspec(noinline) virtual ~MobMemberSlavedUpdate();
};

MobMemberSlavedUpdate::~MobMemberSlavedUpdate()
{
}

void Force_MobMemberSlavedUpdate_Deleting_Destructor(
	MobMemberSlavedUpdate *value)
{
	delete value;
}
