// cl: /vd0
// Two more classes of the virtual-base destructor family whose first four
// members landed in T2VirtualBaseDeletingDtors.cpp, found by the same tell:
// a 22-byte ??_D that steps `this` UP by the non-virtual size and tail jumps
// to a virtual base destructor, paired with a 51-byte ??_G entered ON the
// virtual base that steps DOWN by the same amount before calling operator
// delete on the complete object.
//
//   0x0084B6C0 / 0x0084B7C0   non-virtual size 0xC0, virtual base destructor
//                             reached through the ILT thunk at 0x000414BB
//   0x0084B720 / 0x0084B880   non-virtual size 0x98, virtual base destructor
//                             at 0x0083F810
//
// Each body has two non-virtual branches that virtually share one T2 base: the
// primary branch has a four-byte lead, while the secondary branch contributes
// only its vbptr.  That shared virtual-base layout is what produces the guarded
// secondary-vptr reset between the two primary-branch stores after the member
// destructor.  The A and B bodies use the same layout with different virtual
// base/member types.
//
// The class destructors these stubs call are NOT the ones T2 claimed -- they
// are the 138-byte bodies at 0x0084B480 and 0x0084B5F0, still unnamed dumps
// elsewhere, pinned by name here.  A body that long clobbers ecx, which is why
// each stub reloads the adjusted pointer before the virtual base call; the
// four-byte member is what makes the compiler assume that.
//
// Layout is re-derived from the non-virtual size alone, exactly as in T2: a
// primary vbptr, a secondary vbptr, the four-byte member at offset 0xC and tail
// padding summing to 0xC0 / 0x98.  `/vd0` for the same reason.  Identity is not
// recovered; both names are derived from the class destructor's address.

struct T2VBaseA
{
	virtual ~T2VBaseA();
	virtual void handle();
};

struct T2VBaseB
{
	virtual ~T2VBaseB();
	virtual void handle();
};

struct Gen008427F0 { char m_body[4]; Gen008427F0(); ~Gen008427F0(); };
struct Gen00842970 { char m_body[4]; Gen00842970(); ~Gen00842970(); };

struct U2BaseA_Gap : virtual T2VBaseA
{
	char m_lead[4];
	virtual void handle();
	~U2BaseA_Gap() {}
};

struct U2SecondaryA : virtual T2VBaseA
{
	~U2SecondaryA() {}
};

struct U2MidA_Gap : public U2BaseA_Gap, public U2SecondaryA
{
	~U2MidA_Gap() {}
};

struct U2BaseB_Gap : virtual T2VBaseB
{
	char m_lead[4];
	virtual void handle();
	~U2BaseB_Gap() {}
};

struct U2SecondaryB : virtual T2VBaseB
{
	~U2SecondaryB() {}
};

struct U2MidB_Tight : public U2BaseB_Gap, public U2SecondaryB
{
	~U2MidB_Tight() {}
};

struct U2Vb0084B480 : public U2MidA_Gap
{
	Gen008427F0 m_member;
	char m_tail[0xB0];
	~U2Vb0084B480();
};
U2Vb0084B480::~U2Vb0084B480() {}

struct U2Vb0084B5F0 : public U2MidB_Tight
{
	Gen00842970 m_member;
	char m_tail[0x88];
	~U2Vb0084B5F0();
};
// ??1U2Vb0084B5F0@@UAE@XZ present-unmatched
U2Vb0084B5F0::~U2Vb0084B5F0() {}

// A complete object on the stack is what makes the compiler emit the ??_D
// stub; without a use it has nothing to emit.
void u2_force_vbase_dtors()
{
	U2Vb0084B480 a;
	U2Vb0084B5F0 b;
}
