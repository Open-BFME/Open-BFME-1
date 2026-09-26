// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// BfmeThingDGD constructor, retail 0x007F7FA0, 228 bytes. The matched
// allocator wrapper at 0x007F86A0 allocates 0x6E0 bytes and calls this body,
// and the scalar deleting destructor at 0x007F86D0 frees the same 0x6E0 after
// calling the destructor at 0x007F8090. The layout matches the destructor
// source beside this one.
//
// The two base levels are what order the five vftable stores. Retail writes
// the pair at +4 and +8 first, then all three again, which is what a base
// constructor followed by a derived one produces. The four child records and
// the two small members construct themselves, so the compiler places the edi
// save between them the way retail does. The root pair writes through a
// volatile cast, because the derived constructor overwrites both words and
// the optimiser drops a plain store it can see overwritten. The derived
// three stay plain, which is what lets the zero constant materialise ahead
// of them.

class Rva007F6BA0
{
public:
	Rva007F6BA0()
	{
		m_00 = 0;
		m_04 = 0;
	}

private:
	unsigned m_00;
	unsigned m_04;
};

class Rva007F6C60
{
public:
	Rva007F6C60()
	{
		m_00 = 0;
		m_04 = 0;
	}

private:
	unsigned m_00;
	unsigned m_04;
};

class Rva007F78E0Block
{
public:
	Rva007F78E0Block()
	{
		m_00 = 0;
		m_04 = 0;
	}

private:
	unsigned m_00;
	unsigned m_04;
};

// One 0x94-byte record of the four the holder owns at this+0x58. Its
// constructor is the still unnamed body at retail 0x007F6D60.
class Rva007F6D60Child
{
public:
	Rva007F6D60Child();

private:
	unsigned char m_unmodelled[ 0x94 ];
};

class BfmeThingECKb
{
public:
	void *bfmeGoECKb( void );
};

class Rva007F8090Root
{
public:
	Rva007F8090Root()
	{
		*(volatile unsigned *)&m_v4 = 0x01118e58;
		*(volatile unsigned *)&m_v8 = 0x0112b680;
	}

	unsigned m_v0;
	unsigned m_v4;
	unsigned m_v8;
};

class Rva007F8090Base : public Rva007F8090Root
{
public:
	Rva007F8090Base()
	{
		m_v0 = 0x0112b800;
		m_v4 = 0x0112b7f8;
		m_v8 = 0x0112b7f0;
	}
};

class BfmeThingDGD : public Rva007F8090Base
{
public:
	BfmeThingDGD( void *owner );

	void *m_0c;											///< retail this+0x0c
	void *m_10;
	unsigned m_14;
	unsigned m_18;
	unsigned m_1c;
	unsigned m_20;
	unsigned m_24;
	unsigned m_28;
	unsigned m_2c;
	unsigned m_30;
	unsigned char m_34;
	unsigned char m_35;
	unsigned char m_36;
	unsigned char m_37;
	Rva007F6BA0 m_38;									///< retail this+0x38
	unsigned m_40;
	unsigned m_44;
	Rva007F6C60 m_48;									///< retail this+0x48
	unsigned m_50;
	unsigned m_54;
	Rva007F6D60Child m_children[ 4 ];					///< retail this+0x58
	Rva007F78E0Block m_2a8;								///< retail this+0x2a8
	Rva007F78E0Block m_2b0;								///< retail this+0x2b0
	Rva007F78E0Block m_2b8;								///< retail this+0x2b8
	unsigned m_2c0;
	unsigned m_2c4;
	unsigned m_2c8;
	unsigned m_2cc;
	unsigned m_2d0;
	unsigned m_2d4;
	unsigned m_2d8;
	unsigned char m_tail[ 0x400 ];
	unsigned m_6dc;										///< retail this+0x6dc
};

// ??0BfmeThingDGD@@QAE@PAX@Z
BfmeThingDGD::BfmeThingDGD( void *owner )
{
	m_2c0 = 0;
	m_2c4 = 0;
	m_2c8 = 0;
	m_2cc = 0;
	m_2d0 = 0;
	m_2d4 = 0;
	m_0c = owner;
	m_10 = ((BfmeThingECKb *)m_0c)->bfmeGoECKb();
	m_14 = 0;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_50 = 0;
	m_2c = 0;
	m_28 = 0;
	m_2d8 = 0;
	m_36 = 0;
	m_44 = 0;
	m_54 = 0;
	m_24 = 0;
	m_30 = 0;
	m_6dc = 0x2710;
}

typedef char BfmeThingDGDSize[ ( sizeof( BfmeThingDGD ) == 0x6e0 ) ? 1 : -1 ];
