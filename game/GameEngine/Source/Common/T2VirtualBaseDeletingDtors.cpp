// cl: /vd0
// The deleting and vbase destructors that go with the four virtual-base
// destructors already landed in R4VirtualBaseDestructors.cpp (0x0084B3A0,
// 0x0084B410, 0x0084B510, 0x0084B580).  Those rows are the ??1 bodies, entered
// with `this` already pointing at the virtual base; these rows are the two
// stubs the compiler wraps around each one:
//
//   ??_D (22 bytes, entered on the COMPLETE object): step `this` up by the
//   non-virtual size to reach the virtual base, run the ??1 there, then TAIL
//   JUMP to the virtual base's own destructor.  The step is `lea esi,[ecx+NV]`
//   with NV positive, which is the mirror of the negative offsets the ??1
//   bodies use and is what ties each stub to its class.
//
//   ??_G (51 bytes, entered ON the virtual base like the ??1): step DOWN by NV
//   to recover the complete object for `operator delete`, run ??1 and the
//   virtual base destructor on the unadjusted pointer, then delete the complete
//   object if the caller passed the flag.
//
// TWO virtual bases, not one.  Rows at NV 0xBC and 0xB8 end in the destructor
// reached through 0x000414BB; rows at NV 0x94 and 0x90 end in the one at
// 0x0083F810.  The ??1 bodies cannot see this difference -- they never touch
// the virtual base -- so it is these stubs that split the family in two.
//
// The layouts are R4's, re-derived from the NV each stub encodes: vbptr, an
// optional four-byte lead, a four-byte member, and tail padding, summing to
// 0xBC / 0xB8 / 0x94 / 0x90.  `/vd0` for the same reason R4 needs it.
// Identity is not recovered; every name is derived from an address.

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

struct T2Member4 { char m_body[4]; T2Member4(); ~T2Member4(); };

struct T2MidA_Gap : virtual T2VBaseA
{
	char m_lead[4];
	virtual void handle();
	~T2MidA_Gap() {}
};

struct T2MidA_Tight : virtual T2VBaseA
{
	virtual void handle();
	~T2MidA_Tight() {}
};

struct T2MidB_Gap : virtual T2VBaseB
{
	char m_lead[4];
	virtual void handle();
	~T2MidB_Gap() {}
};

struct T2MidB_Tight : virtual T2VBaseB
{
	virtual void handle();
	~T2MidB_Tight() {}
};

#define T2_VBASE_DTOR( NAME, MID, TAIL )                                      \
	struct NAME : public MID                                                  \
	{                                                                         \
		T2Member4 m_member;                                                   \
		char m_tail[ TAIL ];                                                  \
		virtual void handle();                                                \
		~NAME();                                                              \
	};                                                                        \
	NAME::~NAME() {}

T2_VBASE_DTOR( T2Vb0084B3A0, T2MidA_Gap,   0xB0 )
T2_VBASE_DTOR( T2Vb0084B410, T2MidA_Tight, 0xB0 )
T2_VBASE_DTOR( T2Vb0084B510, T2MidB_Gap,   0x88 )
T2_VBASE_DTOR( T2Vb0084B580, T2MidB_Tight, 0x88 )

// A complete object on the stack is what makes the compiler emit the ??_D
// stub; without a use it has nothing to emit.
void t2_force_vbase_dtors()
{
	T2Vb0084B3A0 a;
	T2Vb0084B410 b;
	T2Vb0084B510 c;
	T2Vb0084B580 d;
}

// 0x0084AB20 is the same ??_G stub over a non-virtual size of 0xC, entered on
// the virtual base and calling the class destructor at 0x0084A620 (still an
// unnamed dump elsewhere, pinned by name here) and then the virtual base
// destructor.
//
// WHAT THE LAYOUT IS AND WHERE THE EVIDENCE PULLS TWO WAYS.  The ??1 at
// 0x0084A620 stores the derived vftable through the vbtable, then does a
// NULL-GUARDED adjust to this-4 storing 0x0112F304 and finally 0x0112F2F4 --
// by the usual reading that is a SECOND BASE at offset 8, i.e. the gap
// intermediate at 0 and the tight one at 8, filling 0xC exactly.  But a class
// built that way compiles this stub to 41 bytes, not 45: with both bases`
// destructors doing nothing but vptr stores the compiler sees that ??1 leaves
// ecx alone and reuses it across both calls.  Retail spends the extra register,
// which is the shape a class whose ??1 CLOBBERS ecx produces -- one with a
// member to destroy.  Only the second reading reproduces the bytes, so that is
// what is written here; the vftable evidence in the ??1 is recorded above and
// is not explained by it.  Nothing in this row is a DIR32, so no data address
// is being claimed either way.
struct T2Vb0084A620 : public T2MidA_Gap
{
	T2Member4 m_member;
	virtual void handle();
	~T2Vb0084A620();
};
// ??1T2Vb0084A620@@UAE@XZ present-unmatched
T2Vb0084A620::~T2Vb0084A620() {}
