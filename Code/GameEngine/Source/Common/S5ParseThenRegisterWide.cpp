// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: three more bodies of the INI definition-parsing family that
// S4ParseThenRegisterWithFields.cpp describes (allocate a derived record whose
// constructor is inlined after the shared base constructor 0x00489210, fill it
// through INI::initFromINI, copy +0x14 into +4 again, hand it to the sink at
// 0x00489270).  These three allocate 0x28..0x38 bytes and write more fields;
// each constructor repeats retail's store order .  Identity of the derived
// classes, their +0 pointers and their tables is not recovered: every name is
// address-derived and the data objects are extern declarations.

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI( void *what, const FieldParse *table );
};

struct Gen_00489270
{
	void m( int a );
};

class Rva00489210
{
public:
	Rva00489210();
	int *m_00;
	int m_04;
	char m_08, m_09, m_0A;
	int m_0C;
};

#define S5_PARSE( NAME, INIT, BODY, FIELDS )                                         \
	extern int g_s5Head##NAME;                                                 \
	extern const FieldParse s5Table##NAME;                                     \
	struct S5Built##NAME : public Rva00489210                                  \
	{                                                                          \
		FIELDS                                                                 \
		S5Built##NAME() INIT { BODY }                                          \
	};                                                                         \
	void s5parse##NAME( INI *ini, Gen_00489270 *sink )                         \
	{                                                                          \
		S5Built##NAME *t = new S5Built##NAME;                                  \
		ini->initFromINI( t, &s5Table##NAME );                                 \
		t->m_04 = t->m_14;                                                     \
		sink->m( (int)t );                                                     \
	}

#define S5_PARSE_TWO( NAME, MIDBODY, BODY, FIELDS )                            	extern int g_s5Head##NAME;                                                 	extern const FieldParse s5Table##NAME;                                     	struct S5Mid##NAME : public Rva00489210                                    	{                                                                          		FIELDS                                                                 		S5Mid##NAME() { MIDBODY }                                              	};                                                                         	struct S5Built##NAME : public S5Mid##NAME                                  	{                                                                          		S5Built##NAME() { BODY }                                               	};                                                                         	void s5parse##NAME( INI *ini, Gen_00489270 *sink )                         	{                                                                          		S5Built##NAME *t = new S5Built##NAME;                                  		ini->initFromINI( t, &s5Table##NAME );                                 		t->m_04 = t->m_14;                                                     		sink->m( (int)t );                                                     	}

// 0x0059D9E0 160 B, 0x38 bytes
S5_PARSE( 0059D9E0, ,
	m_00 = &g_s5Head0059D9E0; m_10 = 0; m_14 = 30; m_04 = m_14; m_0C = 0; m_28 = 0; m_2C = -1; m_09 = 1; m_30 = 0; m_34 = 0;,
	int m_10; int m_14; int m_18; int m_1C; int m_20; int m_24; int m_28; int m_2C; int m_30; int m_34; )

// 0x0059DE10 157 B, 0x34 bytes
S5_PARSE( 0059DE10, ,
	m_00 = &g_s5Head0059DE10; m_10 = 0; m_14 = 30; m_04 = m_14; m_0C = 0; m_28 = 0; m_2C = -1; m_09 = 1; m_30 = 0;,
	int m_10; int m_14; int m_18; int m_1C; int m_20; int m_24; int m_28; int m_2C; int m_30; )

// 0x0059FB50 157 B, 0x28 bytes
S5_PARSE( 0059FB50, ,
	m_00 = &g_s5Head0059FB50; m_10 = 0; m_14 = 30; m_18 = 7; m_1C = 0; m_20 = 1.0f; m_24 = 0; m_04 = m_14;,
	int m_10; int m_14; int m_18; char m_1C; float m_20; char m_24; )
