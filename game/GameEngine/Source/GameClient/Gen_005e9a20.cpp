// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the copy constructor at retail 0x005E9A20, address-derived name.
//
// NOT GeometryInfo. That symbol is already matched at 0x003A6360 at 24 bytes as
// a plain POD block copy, and three independent retail offsets (m_isSmall at
// store+0x4 in parseGeometryIsSmall 0x0087F160, &m_geometryInfo as Object+0xac,
// m_minorRadius at Object+0xbc) are consistent only with a NON-polymorphic
// GeometryInfo in Zero Hour field order. This body stores a vftable at this+0,
// so it is a different class and the name is not asserted here.
//
// What the image does say about the class:
//   - 0x20 bytes: vftable at +0x00 and seven dwords at +0x04..+0x1C.
//   - vftable 0x011129B4 has four slots; slot 0 is the scalar-deleting
//     destructor at 0x005E9A70 (ledger ??_GGen_dtor_005e9a70), the other three
//     are 0x005E76A0, 0x005E76B0 and 0x005FF940 -- all still unnamed.
//   - the default constructor at 0x005FF910 zeroes +0x04..+0x18 and sets
//     +0x1C to 1.
//   - it appears as a sub-object at +0x0C and +0x08 of two larger classes
//     constructed at 0x005FFAC0 and 0x005FFBC0.
//   - the surrounding span is BFME's FXParticleSystem module machinery, which
//     has no Zero Hour counterpart to port from.
//
// The body is the compiler's own copy constructor: an explicit one written with
// seven member assignments, the implicit one forced through a holder, and an
// indexed loop over a seven-element array all emit these exact 57 bytes.

typedef int Int;

class Gen_005e9a20
{
public:
	Gen_005e9a20( const Gen_005e9a20 &other );
	virtual ~Gen_005e9a20();
	virtual void v1( void );
	virtual void v2( void );
	virtual void v3( void );

	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
};

Gen_005e9a20::Gen_005e9a20( const Gen_005e9a20 &other )
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field10 = other.m_field10;
	m_field14 = other.m_field14;
	m_field18 = other.m_field18;
	m_field1C = other.m_field1C;
}
