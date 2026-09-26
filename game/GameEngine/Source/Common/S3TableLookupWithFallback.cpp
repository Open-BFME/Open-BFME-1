// Five 59-byte __thiscall members that ask a per-field global for a key, use it
// to look a float up in a shared global table, and fall back to a field of a
// third global when the lookup reports failure:
//
//     push ecx                      ; the four bytes of locals
//     lea eax,[esp+7] / push eax    ; &found -- the last byte of that slot
//     mov ecx,OFFSET <key global> / call <REL32>   ; returns a dword
//     push eax / mov ecx,OFFSET <table global> / call <REL32>
//     fstp [this+FIELD]                             ; st0 -- a float result
//     mov al,[esp+7] / test al,al / jne .1
//     mov ecx,[<fallback pointer global>] / mov edx,[ecx+SLOT] /
//     mov [this+FIELD],edx
//  .1 pop esi / pop ecx / ret
//
// WHAT THE BYTES SHOW.  `mov ecx,imm32` -- not `mov ecx,[imm32]` -- means the
// receiver of the first two calls is a global OBJECT, taken by address, while
// the fallback IS dereferenced first and so is a global POINTER.  The flag is
// passed BY ADDRESS to the first call and read back after the second, so the
// first callee writes it; it lives in the single `push ecx` of local space.
// The lookup returns in st0 and is stored with `fstp`, which fixes it as float;
// the fallback copy is a plain dword move, which is how MSVC copies one float
// to another when no arithmetic touches it.
//
// TWO AXES MOVING IN LOCKSTEP: the key global (five addresses eight bytes
// apart) with the destination field (+4, +8, +0xC, +0x10, +0x14) and the
// fallback slot (+0x184 .. +0x194).  Because the destination fields differ but
// nothing else does, these are landed as FIVE MEMBERS OF ONE CLASS -- five
// separate classes would assert five layouts the bytes show to be one.
//
// The five key globals are declared SEPARATELY rather than as one array, even
// though their eight-byte spacing invites the array reading: one symbol
// standing at five addresses is exactly what verify_dir32_consistency exists to
// catch, and the bytes cannot tell an array from five neighbours anyway.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the key
// type's two words are declared only to give it the eight-byte size its
// neighbours imply, and nothing reads them.

class GenKey
{
public:
	int fetch( bool *found );
	int m_a, m_b;
};

class GenTable
{
public:
	float lookup( int key );
};

class GenFallback
{
public:
	char m_pad[ 0x184 ];
	float m_f0, m_f1, m_f2, m_f3, m_f4;
};

extern GenKey GenKey0012A79B8;
extern GenKey GenKey0012A79C0;
extern GenKey GenKey0012A79C8;
extern GenKey GenKey0012A79D0;
extern GenKey GenKey0012A79D8;
extern GenTable GenTable0012ED5E0;
extern GenFallback *GenFallback0012ED5C8;

class Rva006DF290
{
public:
	void load0();
	void load1();
	void load2();
	void load3();
	void load4();
	int m_00;
	float m_04, m_08, m_0c, m_10, m_14;
};

#define S3_LOAD( NAME, KEY, FIELD, FB )                                   \
	void Rva006DF290::NAME()                                              \
	{                                                                     \
		bool found;                                                       \
		FIELD = GenTable0012ED5E0.lookup( KEY.fetch( &found ) );          \
		if( !found )                                                      \
			FIELD = GenFallback0012ED5C8->FB;                             \
	}

S3_LOAD( load0, GenKey0012A79B8, m_04, m_f0 )
S3_LOAD( load1, GenKey0012A79C0, m_08, m_f1 )
S3_LOAD( load2, GenKey0012A79C8, m_0c, m_f2 )
S3_LOAD( load3, GenKey0012A79D0, m_10, m_f3 )
S3_LOAD( load4, GenKey0012A79D8, m_14, m_f4 )
