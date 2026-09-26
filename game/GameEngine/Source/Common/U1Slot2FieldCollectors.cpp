// Sixteen bodies, 51 to 99 bytes, that copy one or more values OUT of a
// supplied object and into `this`, asking each one of a run of null-checked
// pointer fields for it, and then hand the rest of the job to a second
// object.  Retail, the single-field arity that merges its arms:
//
//     push ebx / mov ebx,[esp+8] / push esi / push edi
//     mov edi,[esp+0x14] / mov esi,ecx
//     mov ecx,[edi+<FIELD>] / test ecx,ecx / je null
//     mov eax,[ecx] / push ebx / call dword ptr [eax+8]
//     jmp store
//     null: xor eax,eax
//     store: mov [esi+<SLOT>],eax
//     push ebx / add esi,<SLOT+4> / push esi / mov ecx,edi / call <REL32>
//     pop edi / pop esi / pop ebx / ret 8
//
// WHAT THE BYTES SHOW.  `this` in ecx, `ret 8`, no value returned:
// __thiscall with two dword parameters.  The first goes to ebx and the second
// to edi, both loaded once before anything else and neither ever written, so
// every callee sees them unchanged.
//
// EACH FIELD IS A NULL-CHECKED POINTER READ OUT OF THE SECOND PARAMETER,
// dispatching SLOT 2 with the first parameter as its only argument and
// yielding a dword that is stored into `this`.  The field is loaded straight
// into ecx and tested there, which -- as everywhere else in this drawer --
// only happens when the source binds it to a LOCAL first.  The value reaches
// the store in a REGISTER on both paths (`xor eax,eax` on the null arm, never
// an immediate store), so this is ONE assignment fed by a conditional
// expression, not an assignment in each arm: spelling it as two assignments
// emits `mov dword ptr [esi+SLOT],0` and misses.
//
// THE ARMS MERGE OR DUPLICATE PURELY BY STORE WIDTH, not by source.  When the
// last store before the tail is `mov [esi],eax` -- two bytes, displacement 0 --
// MSVC 7.1 duplicates the store, the tail call and the whole epilogue into the
// null arm instead of emitting the `jmp`; at displacement 4 or more the store
// is three bytes and it merges.  One source spelling produces both, which the
// gate confirms at 0x005CBBA0 (duplicated) and 0x005CD3D0 (merged) from the
// identical body text.
//
// THE TAIL SPLITS THE FAMILY IN TWO, and the split is what the addresses can
// prove.
//
// TAIL SHAPE A -- eight rows -- `push ebx / add esi,K / push esi / mov ecx,edi
// / call`.  The receiver is the SECOND PARAMETER and the argument is a POINTER
// INTO `this`, at the displacement just past the last slot written.  A bare
// `add esi,K` handed to a callee is the address of a member subobject, so the
// source is `second->fill( &m_rest, first )`.  The supplier drives.
//
// TAIL SHAPE B -- five rows -- `push edi / push ebx / lea ecx,[esi+K] / call`.
// Here the receiver is the member subobject itself and BOTH parameters are
// re-pushed, in the same order this function received them: `m_rest.collect(
// first, second )`.  The member drives, and it is the same signature this
// function has -- so shape B is the same operation applied to the remainder.
//
// SHAPE B PROVES SHAPE A IS NOT A TYPO.  Two shape-B rows, 0x005CEE40 and
// 0x005CF180, call 0x005CE5D0, which is a shape-A row claimed in this very
// file; its `this` is therefore a member of theirs and its second parameter is
// the same type as theirs.  That is what fixes the member type and the
// supplier type for those two rows without a pin.
//
// THE FIELD DISPLACEMENTS ARE TWO DWORD-STRIDED RUNS -- 0x3C/0x40/0x44/0x48
// and 0x54, and 0xA0/0xA8/0xB0/0xB8/0xBC -- the same two runs the null-checked
// forwarders in T1NullCheckedSlotTwoLookups.cpp read from a few thousand bytes
// earlier.  Nothing in a body says two rows read the same class, but a CALL
// TARGET does: a function belongs to one class, so the seven rows calling
// 0x005C8D40 share a supplier type and the two calling 0x005C8E90 share
// another.  Those two suppliers are spelled separately here because their
// displacement runs are disjoint and nothing joins them.  The three shape-B
// rows whose tails go to unclaimed addresses share nothing with anyone, so
// each keeps its own supplier type padded to its own field.
//
// IDENTITY IS NOT RECOVERED.  No vftable in the ledger reaches these bodies
// and no string names the fields; every name here comes from a row or callee
// address.

class U1Slot2Field
{
public:
	virtual void fieldPad0();
	virtual void fieldPad1();
	virtual void *get( void *first );
};

// ------------------------------------------------------- tail shape A, group 1

class U1FillTargetLow;

class U1SupplierLow
{
public:
	void fill( U1FillTargetLow *rest, void *first );

	char m_pad3C[ 0x3c ];
	U1Slot2Field *m_f3C;
	U1Slot2Field *m_f40;
	U1Slot2Field *m_f44;
	U1Slot2Field *m_f48;
	char m_pad4C[ 8 ];
	U1Slot2Field *m_f54;
};

class U1FillTargetLow
{
};

// ------------------------------------------------------- tail shape A, group 2

class U1FillTargetHigh;

class U1SupplierHigh
{
public:
	void fill( U1FillTargetHigh *rest, void *first );

	char m_padB8[ 0xb8 ];
	U1Slot2Field *m_fB8;
	U1Slot2Field *m_fBC;
};

class U1FillTargetHigh
{
};

#define U1_COLLECT_A1( ROW, SUPPLIER, FIELD, GAP, TARGET )                    \
	class U1Collect_##ROW                                                     \
	{                                                                         \
	public:                                                                   \
		void collect( void *first, SUPPLIER *second );                        \
                                                                              \
		char m_gap[ GAP ];                                                    \
		void *m_v0;                                                           \
		TARGET m_rest;                                                        \
	};                                                                        \
	void U1Collect_##ROW::collect( void *first, SUPPLIER *second )            \
	{                                                                         \
		U1Slot2Field *f0 = second->FIELD;                                     \
		m_v0 = f0 ? f0->get( first ) : 0;                                     \
		second->fill( &m_rest, first );                                       \
	}

#define U1_COLLECT_A2( ROW, SUPPLIER, FIELD0, FIELD1, GAP, TARGET )           \
	class U1Collect_##ROW                                                     \
	{                                                                         \
	public:                                                                   \
		void collect( void *first, SUPPLIER *second );                        \
                                                                              \
		void *m_v0;                                                           \
		char m_gap[ GAP ];                                                    \
		void *m_v1;                                                           \
		TARGET m_rest;                                                        \
	};                                                                        \
	void U1Collect_##ROW::collect( void *first, SUPPLIER *second )            \
	{                                                                         \
		U1Slot2Field *f0 = second->FIELD0;                                    \
		m_v0 = f0 ? f0->get( first ) : 0;                                     \
		U1Slot2Field *f1 = second->FIELD1;                                    \
		m_v1 = f1 ? f1->get( first ) : 0;                                     \
		second->fill( &m_rest, first );                                       \
	}

#define U1_COLLECT_A3( ROW, SUPPLIER, FIELD0, FIELD1, FIELD2, GAP, TARGET )   \
	class U1Collect_##ROW                                                     \
	{                                                                         \
	public:                                                                   \
		void collect( void *first, SUPPLIER *second );                        \
                                                                              \
		void *m_v0;                                                           \
		void *m_v1;                                                           \
		char m_gap[ GAP ];                                                    \
		void *m_v2;                                                           \
		TARGET m_rest;                                                        \
	};                                                                        \
	void U1Collect_##ROW::collect( void *first, SUPPLIER *second )            \
	{                                                                         \
		U1Slot2Field *f0 = second->FIELD0;                                    \
		m_v0 = f0 ? f0->get( first ) : 0;                                     \
		U1Slot2Field *f1 = second->FIELD1;                                    \
		m_v1 = f1 ? f1->get( first ) : 0;                                     \
		U1Slot2Field *f2 = second->FIELD2;                                    \
		m_v2 = f2 ? f2->get( first ) : 0;                                     \
		second->fill( &m_rest, first );                                       \
	}

#define U1_COLLECT_A1_0( ROW, SUPPLIER, FIELD, TARGET )                       	class U1Collect_##ROW                                                     	{                                                                         	public:                                                                   		void collect( void *first, SUPPLIER *second );                                                                                                      		void *m_v0;                                                           		TARGET m_rest;                                                        	};                                                                        	void U1Collect_##ROW::collect( void *first, SUPPLIER *second )            	{                                                                         		U1Slot2Field *f0 = second->FIELD;                                     		m_v0 = f0 ? f0->get( first ) : 0;                                     		second->fill( &m_rest, first );                                       	}

#define U1_COLLECT_A2_0( ROW, SUPPLIER, FIELD0, FIELD1, TARGET )              	class U1Collect_##ROW                                                     	{                                                                         	public:                                                                   		void collect( void *first, SUPPLIER *second );                                                                                                      		void *m_v0;                                                           		void *m_v1;                                                           		TARGET m_rest;                                                        	};                                                                        	void U1Collect_##ROW::collect( void *first, SUPPLIER *second )            	{                                                                         		U1Slot2Field *f0 = second->FIELD0;                                    		m_v0 = f0 ? f0->get( first ) : 0;                                     		U1Slot2Field *f1 = second->FIELD1;                                    		m_v1 = f1 ? f1->get( first ) : 0;                                     		second->fill( &m_rest, first );                                       	}

U1_COLLECT_A1_0( 005CBBA0, U1SupplierLow, m_f54, U1FillTargetLow )
U1_COLLECT_A1_0( 005CC2E0, U1SupplierLow, m_f54, U1FillTargetLow )
U1_COLLECT_A1( 005CD3D0, U1SupplierLow, m_f54, 4, U1FillTargetLow )
U1_COLLECT_A1( 005CD8A0, U1SupplierLow, m_f54, 8, U1FillTargetLow )
U1_COLLECT_A1_0( 005CBC00, U1SupplierHigh, m_fBC, U1FillTargetHigh )

U1_COLLECT_A2( 005CDD20, U1SupplierLow, m_f48, m_f54, 8, U1FillTargetLow )
U1_COLLECT_A2_0( 005CC340, U1SupplierHigh, m_fB8, m_fBC, U1FillTargetHigh )

U1_COLLECT_A3( 005CE5D0, U1SupplierLow, m_f44, m_f48, m_f54, 8, U1FillTargetLow )

// ------------------------------------------------------------- tail shape B

class U1Supplier_005CD8E0
{
public:
	char m_pad[ 0xb0 ];
	U1Slot2Field *m_field;
	U1Slot2Field *m_fB4;
	U1Slot2Field *m_fB8;
	U1Slot2Field *m_fBC;
};

class U1Supplier_005CE640
{
public:
	char m_pad[ 0xa8 ];
	U1Slot2Field *m_field;
	U1Slot2Field *m_fAC;
	U1Slot2Field *m_fB0;
};

class U1Supplier_005CF1F0
{
public:
	char m_pad[ 0xa0 ];
	U1Slot2Field *m_field;
	U1Slot2Field *m_fA4;
	U1Slot2Field *m_fA8;
};

class U1Rest_005CD8E0
{
public:
	void collect( void *first, U1Supplier_005CD8E0 *second );

	void *m_v0;
	void *m_v1;
	void *m_v2;
	U1FillTargetHigh m_rest;
};

class U1Rest_005CE640
{
public:
	void collect( void *first, U1Supplier_005CE640 *second );

	void *m_v0;
	void *m_v1;
	U1Rest_005CD8E0 m_rest;
};

class U1Rest_005CF1F0
{
public:
	void collect( void *first, U1Supplier_005CF1F0 *second );

	void *m_v0;
	void *m_v1;
	U1Rest_005CE640 m_rest;
};

#define U1_COLLECT_B1( ROW )                                                  \
	class U1Chain_##ROW                                                       \
	{                                                                         \
	public:                                                                   \
		void collect( void *first, U1Supplier_##ROW *second );                \
                                                                              \
		void *m_v0;                                                           \
		U1Rest_##ROW m_rest;                                                  \
	};                                                                        \
	void U1Chain_##ROW::collect( void *first, U1Supplier_##ROW *second )      \
	{                                                                         \
		U1Slot2Field *f0 = second->m_field;                                   \
		m_v0 = f0 ? f0->get( first ) : 0;                                     \
		m_rest.collect( first, second );                                      \
	}

U1_COLLECT_B1( 005CD8E0 )
U1_COLLECT_B1( 005CE640 )
U1_COLLECT_B1( 005CF1F0 )

void U1Rest_005CD8E0::collect( void *first, U1Supplier_005CD8E0 *second )
{
	U1Slot2Field *f0 = second->m_fB4;
	m_v0 = f0 ? f0->get( first ) : 0;
	U1Slot2Field *f1 = second->m_fB8;
	m_v1 = f1 ? f1->get( first ) : 0;
	U1Slot2Field *f2 = second->m_fBC;
	m_v2 = f2 ? f2->get( first ) : 0;
	reinterpret_cast<U1SupplierHigh *>( second )->fill( &m_rest, first );
}

void U1Rest_005CE640::collect( void *first, U1Supplier_005CE640 *second )
{
	U1Slot2Field *f0 = second->m_fAC;
	m_v0 = f0 ? f0->get( first ) : 0;
	U1Slot2Field *f1 = second->m_fB0;
	m_v1 = f1 ? f1->get( first ) : 0;
	m_rest.collect( first, reinterpret_cast<U1Supplier_005CD8E0 *>( second ) );
}

void U1Rest_005CF1F0::collect( void *first, U1Supplier_005CF1F0 *second )
{
	U1Slot2Field *f0 = second->m_fA4;
	m_v0 = f0 ? f0->get( first ) : 0;
	U1Slot2Field *f1 = second->m_fA8;
	m_v1 = f1 ? f1->get( first ) : 0;
	m_rest.collect( first, reinterpret_cast<U1Supplier_005CE640 *>( second ) );
}

// The two rows whose tail lands on 0x005CE5D0, a shape-A row above: the member
// type and the supplier type are both forced by that signature.

class U1Chain_005CEE40
{
public:
	void collect( void *first, U1SupplierLow *second );

	void *m_v0;
	U1Collect_005CE5D0 m_rest;
};

void U1Chain_005CEE40::collect( void *first, U1SupplierLow *second )
{
	U1Slot2Field *f0 = second->m_f40;
	m_v0 = f0 ? f0->get( first ) : 0;
	m_rest.collect( first, second );
}

class U1Chain_005CF180
{
public:
	void collect( void *first, U1SupplierLow *second );

	void *m_v0;
	void *m_v1;
	U1Collect_005CE5D0 m_rest;
};

void U1Chain_005CF180::collect( void *first, U1SupplierLow *second )
{
	U1Slot2Field *f0 = second->m_f3C;
	m_v0 = f0 ? f0->get( first ) : 0;
	U1Slot2Field *f1 = second->m_f40;
	m_v1 = f1 ? f1->get( first ) : 0;
	m_rest.collect( first, second );
}
