// cl: /EHs-c-
// Open-BFME5: two __thiscall assignment operators over a texture reference,
// 140 and 208 bytes.  Retail:
//
//     cmp esi,edi ; je end                     ; the 140-byte row ONLY
//     mov eax,[edi] ; test eax,eax ; je +
//     inc word ptr [eax+4]                     ; the source's refcount
//     mov ecx,[esi] ; test ecx,ecx ; je +
//     call ?Release_Ref@TextureBaseClass@@QAEXXZ   ; this's old reference
//     <every dword from 0 to <LAST> copied>
//   end:
//     pop edi ; mov eax,esi ; pop esi ; ret 4
//
// WHAT THE BYTES SHOW.  `mov eax,esi` and `ret 4` make these one-argument
// members returning this, and add-ref-before-release is the canonical
// assignment-operator body, not a constructor: a constructor has no old
// reference to release.
//
// ONLY ONE OF THE TWO GUARDS AGAINST SELF-ASSIGNMENT.  0x0095C860 opens with
// `cmp esi,edi / je` and 0x00933C60 does not, so the guard is in one source and
// not the other; adding it to both puts a four-byte test in front of the
// 208-byte row and every following byte moves.
//
// THE REFCOUNT IS A SIXTEEN-BIT FIELD AT +4 of whatever the first member points
// at, raised with a bare `inc word ptr` and never with an interlocked
// operation, and the pointee's release entry point at 0x009EB7A0 is already a
// ledger row: ?Release_Ref@TextureBaseClass@@QAEXXZ.  So the member at 0 is a
// TextureBaseClass pointer and Add_Ref is inline while Release_Ref is not.
//
// EVERY OTHER FIELD IS A PLAIN DWORD -- bare displacements on both sides, no
// pointer pairs and no calls -- so the two classes are 0x44 and 0x74 wide with
// nothing but scalars past the texture pointer.
//
// IDENTITY IS NOT RECOVERED beyond TextureBaseClass: the two classes and their
// fields are address-derived.

typedef int Int;
typedef unsigned short UnsignedShort;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Add_Ref( void ) { ++m_numRefs; }
	void Release_Ref( void );

	Int m_unreconstructed_00;
	UnsignedShort m_numRefs;
	UnsignedShort m_unreconstructed_06;
};

class Rva0095C860
{
public:
	Rva0095C860 &operator=( const Rva0095C860 &other );

	TextureBaseClass *m_texture;
	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	Int m_field20;
	Int m_field24;
	Int m_field28;
	Int m_field2C;
	Int m_field30;
	Int m_field34;
	Int m_field38;
	Int m_field3C;
	Int m_field40;
};

Rva0095C860 &Rva0095C860::operator=( const Rva0095C860 &other )
{
	if ( this != &other )
	{
		if ( other.m_texture )
			other.m_texture->Add_Ref();
		if ( m_texture )
			m_texture->Release_Ref();

		m_texture = other.m_texture;
		m_field04 = other.m_field04;
		m_field08 = other.m_field08;
		m_field0C = other.m_field0C;
		m_field10 = other.m_field10;
		m_field14 = other.m_field14;
		m_field18 = other.m_field18;
		m_field1C = other.m_field1C;
		m_field20 = other.m_field20;
		m_field24 = other.m_field24;
		m_field28 = other.m_field28;
		m_field2C = other.m_field2C;
		m_field30 = other.m_field30;
		m_field34 = other.m_field34;
		m_field38 = other.m_field38;
		m_field3C = other.m_field3C;
		m_field40 = other.m_field40;
	}

	return *this;
}

class Rva00933C60
{
public:
	Rva00933C60 &operator=( const Rva00933C60 &other );

	TextureBaseClass *m_texture;
	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	Int m_field20;
	Int m_field24;
	Int m_field28;
	Int m_field2C;
	Int m_field30;
	Int m_field34;
	Int m_field38;
	Int m_field3C;
	Int m_field40;
	Int m_field44;
	Int m_field48;
	Int m_field4C;
	Int m_field50;
	Int m_field54;
	Int m_field58;
	Int m_field5C;
	Int m_field60;
	Int m_field64;
	Int m_field68;
	Int m_field6C;
	Int m_field70;
};

Rva00933C60 &Rva00933C60::operator=( const Rva00933C60 &other )
{
	if ( other.m_texture )
		other.m_texture->Add_Ref();
	if ( m_texture )
		m_texture->Release_Ref();

	m_texture = other.m_texture;
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field10 = other.m_field10;
	m_field14 = other.m_field14;
	m_field18 = other.m_field18;
	m_field1C = other.m_field1C;
	m_field20 = other.m_field20;
	m_field24 = other.m_field24;
	m_field28 = other.m_field28;
	m_field2C = other.m_field2C;
	m_field30 = other.m_field30;
	m_field34 = other.m_field34;
	m_field38 = other.m_field38;
	m_field3C = other.m_field3C;
	m_field40 = other.m_field40;
	m_field44 = other.m_field44;
	m_field48 = other.m_field48;
	m_field4C = other.m_field4C;
	m_field50 = other.m_field50;
	m_field54 = other.m_field54;
	m_field58 = other.m_field58;
	m_field5C = other.m_field5C;
	m_field60 = other.m_field60;
	m_field64 = other.m_field64;
	m_field68 = other.m_field68;
	m_field6C = other.m_field6C;
	m_field70 = other.m_field70;

	return *this;
}

