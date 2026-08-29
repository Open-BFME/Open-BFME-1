// Seven bodies recovered from byte-true dumps.  Identity is NOT recovered for
// the classes here: their names are address-derived and the padding virtuals
// exist only to place the slot each body calls.  Where a CALLEE already has a
// byte-verified row in the ledger this file spells that name, because the
// ledger's claim about the callee is evidence this body's call site does not
// add to.

// ---------------------------------------------------------------------------
// 0x007001E0 -- a refcounting handle assignment over a COM-shaped interface.
//
//     mov eax,[edi] / test eax,eax / je / mov ecx,[eax] / push eax
//     call [ecx+4] ... mov eax,[esi] / test eax,eax / je / mov edx,[eax]
//     push eax / call [edx+8] ... mov eax,[edi] / mov [esi],eax / mov eax,esi
//
// The receiver register holds the TABLE, not the object, and the object is
// PUSHED: that is a C-shaped interface (`p->lpVtbl->AddRef(p)`), not a C++
// virtual, and the callee pops its argument, so the slots are __stdcall.  Add
// before release is the self-assignment-safe order.  `mov eax,esi` returns the
// receiver, which is what an assignment operator hands back.

struct Open2Unknown;

struct Open2UnknownVtbl
{
	void ( __stdcall *QueryInterface )( Open2Unknown * );
	void ( __stdcall *AddRef )( Open2Unknown * );
	void ( __stdcall *Release )( Open2Unknown * );
};

struct Open2Unknown
{
	Open2UnknownVtbl *lpVtbl;
};

class Open2ComHandle
{
public:
	Open2ComHandle &operator=( const Open2ComHandle &other );
	Open2Unknown *m_held;
};

// @??4Open2ComHandle@@QAEAAV0@ABV0@@Z 0x007001E0
Open2ComHandle &Open2ComHandle::operator=( const Open2ComHandle &other )
{
	if( other.m_held )
		other.m_held->lpVtbl->AddRef( other.m_held );
	if( m_held )
		m_held->lpVtbl->Release( m_held );
	m_held = other.m_held;
	return *this;
}

// ---------------------------------------------------------------------------
// 0x00704AF0 -- publish this object's buffers to the device.
//
//     mov eax,[esi] / test eax,eax / je / inc word ptr [eax+4] ...
//     call Release_Ref / mov eax,[esi] / mov [GLOBAL],eax
//     push 0 / push [esi+8] / call Set_Index_Buffer
//     push 0 / push [esi+4] / call Set_Vertex_Buffer / add esp,0x10
//
// The reference is taken with `inc word ptr`, a 16-bit counter, before the
// previously published object is released -- add-then-release again.  One
// `add esp,0x10` covers both static calls, so the compiler batched two
// __cdecl frames.

class IndexBufferClass;
class VertexBufferClass;

class DX8Wrapper
{
public:
	static void Set_Index_Buffer( const IndexBufferClass *buffer, unsigned short offset );
	static void Set_Vertex_Buffer( const VertexBufferClass *buffer, unsigned int offset );
};

class TextureBaseClass
{
public:
	void Release_Ref( void );
	int m_pad;
	unsigned short m_refs;
};

extern TextureBaseClass *TheOpen2PublishedTexture;

class Rva00704AF0
{
public:
	void publish( void );
	TextureBaseClass *m_texture;
	VertexBufferClass *m_vertexBuffer;
	IndexBufferClass *m_indexBuffer;
};

// @?publish@Rva00704AF0@@QAEXXZ 0x00704AF0
void Rva00704AF0::publish( void )
{
	if( m_texture )
		++m_texture->m_refs;
	if( TheOpen2PublishedTexture )
		TheOpen2PublishedTexture->Release_Ref();
	TheOpen2PublishedTexture = m_texture;
	DX8Wrapper::Set_Index_Buffer( m_indexBuffer, 0 );
	DX8Wrapper::Set_Vertex_Buffer( m_vertexBuffer, 0 );
}

// ---------------------------------------------------------------------------
// 0x00710FF0 and 0x00711050 -- store a reference into an indexed slot.
//
//     ... cmp [esi+0x15c],index+1 / <grow or bail>
//     test ebx,ebx / je / inc [ebx+4]
//     mov ecx,[esi+index*4+BASE] / test ecx,ecx / je / dec [ecx+4] / jne
//     mov eax,[ecx] / call [eax] / mov [esi+index*4+BASE],ebx
//
// The release is `dec` then a branch on the flags, so the counter is the only
// thing consulted and slot 0 is reached only when it hits zero -- a
// self-deleting virtual, entered with the object in ecx.  The counter sits at
// +4, immediately after the vptr.  The two bodies differ only in the array base
// (0x12c against 0x14c) and in what the bound check does: the first RAISES the
// stored count to fit the index, the second returns instead.

class Open2Counted
{
public:
	virtual void destroySelf();
	int m_refs;
};

inline void open2AddRef( Open2Counted *held )
{
	if( held )
		++held->m_refs;
}

inline void open2Release( Open2Counted *held )
{
	if( held && --held->m_refs == 0 )
		held->destroySelf();
}

class Rva00710FF0
{
public:
	void store( Open2Counted *value, int index );
	char m_pad[0x12c];
	Open2Counted *m_slots[ 12 ];
	int m_used;
};

// @?store@Rva00710FF0@@QAEXPAVOpen2Counted@@H@Z 0x00710FF0
void Rva00710FF0::store( Open2Counted *value, int index )
{
	if( m_used < index + 1 )
		m_used = index + 1;
	open2AddRef( value );
	open2Release( m_slots[ index ] );
	m_slots[ index ] = value;
}

class Rva00711050
{
public:
	void store( Open2Counted *value, int index );
	char m_pad[0x14c];
	Open2Counted *m_slots[ 4 ];
	int m_used;
};

// @?store@Rva00711050@@QAEXPAVOpen2Counted@@H@Z 0x00711050
void Rva00711050::store( Open2Counted *value, int index )
{
	if( m_used < index + 1 )
		return;
	open2AddRef( value );
	open2Release( m_slots[ index ] );
	m_slots[ index ] = value;
}

// ---------------------------------------------------------------------------
// 0x007110B0 -- copy a three-dword record out of a global, when it exists.

class Open2Triple
{
public:
	int m_x;
	int m_y;
	int m_z;
};

class Open27110B0Source
{
public:
	const Open2Triple *fetch( int which );
};

extern Open27110B0Source *TheOpen27110B0Source;

// @?Rva007110B0@@YGXPAVOpen2Triple@@@Z 0x007110B0
void __stdcall Rva007110B0( Open2Triple *out )
{
	if( TheOpen27110B0Source )
		*out = *TheOpen27110B0Source->fetch( 0 );
}

// ---------------------------------------------------------------------------
// 0x007118F0 and 0x00711A80 -- publish an argument in a member for the length
// of one virtual call on a sub-object at +0x108, then clear it.
//
//     lea ecx,[esi+0x108] / mov [esi+FIELD],eax / mov edx,[ecx]
//     call [edx+0x1c] / mov [esi+FIELD],0
//
// Retail materialises the sub-object's address and loads the vptr THROUGH it
// (`mov edx,[ecx]`, two bytes); reaching the member directly gives
// `mov edx,[esi+0x108]` and four bytes more.  Naming the sub-object as a
// pointer local, declared before the store, produces both the materialisation
// and the `lea`-before-store order.

class Open2Sub108
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
};

class Rva007118F0
{
public:
	void run( void *value );
	char m_pad[0x108];
	Open2Sub108 m_sub;
	char m_pad2[0x790];
	void *m_current;
};

// @?run@Rva007118F0@@QAEXPAX@Z 0x007118F0
void Rva007118F0::run( void *value )
{
	Open2Sub108 *sub = &m_sub;
	m_current = value;
	sub->slot1C();
	m_current = 0;
}

class Rva00711A80
{
public:
	void run( void *value );
	char m_pad[0x108];
	Open2Sub108 m_sub;
	char m_pad2[0x8];
	void *m_current;
};

// @?run@Rva00711A80@@QAEXPAX@Z 0x00711A80
void Rva00711A80::run( void *value )
{
	Open2Sub108 *sub = &m_sub;
	m_current = value;
	sub->slot1C();
	m_current = 0;
}
