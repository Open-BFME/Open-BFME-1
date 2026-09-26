// cl: /EHsc
//
// Seven 94-byte destructors of a polymorphic class over a polymorphic base:
//
//     mov [esi],<DERIVED VFTABLE>              (compiler-emitted, not source)
//     EH state 1
//     push 0 / push 0 / call <NOTIFY>          (__thiscall, two arguments)
//     mov [esi+0x18],0
//     EH state 0 / lea ecx,[esi+8] / call <SUBOBJECT DTOR>
//     mov [esi],<BASE VFTABLE>                 (the base destructor, inlined)
//
// WHAT THE BYTES SHOW.  Two stores of .rdata addresses to offset 0 of the same
// object.  Both targets are vftables -- 0x00D36058 and 0x00D35D68 each hold six
// dwords that are .text addresses once the image base is taken off, and they
// agree in the first three slots and differ in the last three, which is what a
// derived table looks like next to its base's.  (Reading those dwords as if
// they were already RVAs makes them land in .rdata and disassemble as string
// fragments; that near-miss is what nearly turned this family into a
// "string-table pointer" model.)
//
// THE FIRST STORE IS COMPILER-EMITTED AND THAT IS WHAT FIXES THE SHAPE.  It
// sits BEFORE the EH-state store and before the two argument pushes.  Spelling
// it as a source assignment (`m_names = <table>;`) puts it AFTER them in every
// statement order tried -- three orderings, all wrong at the same offset --
// because the scheduler hoists the pushes past an ordinary store but codegen
// pins a vptr store to the top of the destructor.  So offset 0 is a vptr, the
// class is polymorphic, and its base is too.
//
// THE CLASS IS FLAT.  Inserting an intermediate class -- derived : middle :
// base, with the body in either one -- changes the unwind state numbering from
// retail's 1 then 0 to 0 then 1, and if the middle class's destructor is user
// written the outer destructor degenerates to `store vptr; jmp`.  Retail's 1
// then 0 is two cleanup actions counted down from the body: the subobject at
// +8, then the base.  The base's destructor is INLINE AND NON-TRIVIAL -- it
// compiles to nothing but its own vptr store, which is the last instruction
// before the epilogue; declaring it without a body emits a call instead, and
// omitting it entirely loses the store.
//
// NOTHING VARIES BETWEEN THE SEVEN except the EH handler stub address, a DIR32
// operand copied from retail.  Same vftables, same callees, same offsets.
// WHAT THAT COSTS, STATED PLAINLY: seven distinct function symbols are needed,
// so seven classes are declared, and all seven of their vftable symbols resolve
// to the ONE retail address 0x00D36058.  That is only possible if the seven
// tables were byte-identical and the linker folded them.  The bytes cannot
// distinguish that from some arrangement in which the seven share a table
// outright; what they DO rule out is the derived-reuses-base's-table reading,
// because that is the intermediate-class shape the state numbering refutes.
// Declaring one class instead would be worse -- it could not name seven rows.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived.  `notify` and the
// subobject destructor are each called at one address by all seven, so each is
// pinned once and `notify` is placed in the shared base rather than duplicated
// seven times.  The six virtuals are placeholders sized to the retail tables;
// the three overrides exist only so each class owns a table at all.

class Q4Sub00C9CC70
{
public:
	~Q4Sub00C9CC70();
};

class Q4Base00D35D68
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	void notify( int a, int b );
	~Q4Base00D35D68() { }
};

#define Q4_TABLE_DTOR( NAME )                                             	class NAME : public Q4Base00D35D68                                    	{                                                                     	public:                                                               		virtual void v3();                                                		virtual void v4();                                                		virtual void v5();                                                		~NAME();                                                          		char m_gap0[ 8 - 4 ];                                             		Q4Sub00C9CC70 m_sub;                                              		char m_gap1[ 0x18 - 9 ];                                          		int m_flag;                                                       	};                                                                    	NAME::~NAME()                                                         	{                                                                     		notify( 0, 0 );                                                   		m_flag = 0;                                                       	}

Q4_TABLE_DTOR( Rva0089A010 )
Q4_TABLE_DTOR( Rva0089A4E0 )
Q4_TABLE_DTOR( Rva008A5500 )
Q4_TABLE_DTOR( Rva008B58E0 )
Q4_TABLE_DTOR( Rva008CBA20 )
Q4_TABLE_DTOR( Rva008CBAD0 )
Q4_TABLE_DTOR( Rva008D5F70 )

class __declspec( novtable ) Q4NotifyItem
{
	public:
	virtual void retain();
	virtual void release();
};

extern void (*Rva008A30A0ReleasePtr)( void * );

struct Q4NotifyState
{
	char m_gap[ 0x18 ];
	Q4NotifyItem **m_items;
	unsigned char m_count;
};

void Q4Base00D35D68::notify( int a, int b )
{
	Q4NotifyState *state = (Q4NotifyState *)this;
	unsigned int index;
	for ( index = 0; index < ( (*(unsigned int *)&state->m_count) & 0xff ); ++index )
	{
		state->m_items[ index ]->release();
	}

	Rva008A30A0ReleasePtr( state->m_items );
	state->m_count = (unsigned char)b;
	state->m_items = (Q4NotifyItem **)a;

	for ( index = 0; index < ( (*(unsigned int *)&state->m_count) & 0xff ); ++index )
	{
		state->m_items[ index ]->retain();
	}
}
