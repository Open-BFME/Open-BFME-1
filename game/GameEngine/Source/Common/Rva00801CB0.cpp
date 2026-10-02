// cl: /GX- /GS
// RVA 00801CB0 / 523 bytes: thiscall, four stack arguments, ret 16.
// Matched Rva00802A90Owner::go invokes this exact notify contract twice.
// The arena/record views follow matched Rva00801670FeslMeasure.cpp.
// Inline child construction follows Rva007F4DA0Ctor.cpp and the 16-byte
// Rva007F6D60Member2C view in Rva007F6D60ChildConstructor.cpp. Placement
// construction preserves retail's null receiver path and both message stores.
// The final +48 field receives the fourth argument, independently distinct
// from the key count spilled into the dead context argument during the loop.

struct Rva00802A90Query
{
	int m_lid;
	int m_gid;
	void *m_message;
	int m_ap;
	int m_jp;
	int m_qp;
	int m_mp;
	int m_p;
	int m_nf;
	bool m_flag;
	bool m_password;
	char m_name[0x80];
	char m_hostName[0x80];
	__int64 m_hostAddress;
	char m_version[0x40];
	char m_data170[0x20];
	char m_platform[0x20];
	int m_join;
};

class Rva00800290Buffer
{
public:
	void allocate();

	char *m_ptr;
	int m_size;
	int m_used;
};

class Rva00800460Arena
{
public:
	void *claim( int size, bool align );
	char *append( const char *text );

	char *m_base;
	unsigned m_capacity;
	unsigned m_used;
};

struct BfmeSlotCZ
{
	int *m_bfmePointer;
	int m_bfmeTag;
};

class BfmeVecCZ
{
public:
	BfmeSlotCZ *m_bfmeStart;
	int m_bfmeCount;
};

class Rva00801670Host
{
public:
	int *rva007F76D0( BfmeVecCZ *vector, int index );

	unsigned char m_unreconstructed00[0x2A8];
	BfmeVecCZ m_gameKeys;
};

class Rva007FBC60Game
{
public:
	char *rva007FBE70();
	bool rva007FBE80( const char *key, char *dest, unsigned destSize );

	int m_lid;
	int m_gid;
	void *m_message;
	int m_ap;
	int m_jp;
	int m_qp;
	int m_mp;
	int m_p;
	int m_nf;
	bool m_flag;
	bool m_password;
	char m_name[0x80];
	char m_hostName[0x80];
	__int64 m_hostAddress;
	char m_version[0x40];
	char m_data170[0x20];
	char m_platform[0x20];
	int m_join;
};

class BfmeThingVHW
{
public:
	void rva00801670( Rva007FBC60Game *record );

	void *m_bfmeVfptr;
	Rva00801670Host *m_host;
	char m_bfmePad08[8];
	Rva00800290Buffer m_buffer;
};

// The real base constructor at 007E86B0 is the matched SnapshotDupReplica.
class SnapshotDupReplica {
public:
    SnapshotDupReplica();
    virtual void handle();
};
class BfmeE1029 { public: void bfmeGo1029E(char *, int); };
class Rva007F4DA0 : public SnapshotDupReplica {
public:
    Rva007F4DA0() { field04 = 1; field08 = 0; field24 = 0; }
    virtual void handle();
    int field04; char field08; char gap09[0x1B]; int field24;
    void configure(char *text, int value) { ((BfmeE1029 *)this)->bfmeGo1029E(text, value); }
};
class Rva007F6D60Member2C : public SnapshotDupReplica {
public:
    Rva007F6D60Member2C() { field08 = 0; field0C = 0; field04 = 0; }
    virtual void handle();
    int field04, field08, field0C;
};
class Rva007E8760Addr { public: void parse(const char *, int); };
class Rva00801570 { public: void allocate(int); };
inline void *operator new(unsigned, void *place) { return place; }

struct Rva00802A90Elem
{
public:
	void notify( Rva00802A90Query *, void *context, int flag, int id );

	void *m_vptr;
	Rva00801670Host *m_host;
	int m_gid;
	int m_lid;
	Rva00800290Buffer m_buffer;
	char m_pad1C[0x0C];
	char *m_name;
	char *m_hostName;
	char *m_version;
	char **m_keys;
	char m_pad38[0x0C];
	int m_field44;
	int m_field48;
	char m_pad4C[4];
	int m_field50;
	int m_field54;
	int m_field58;
	int m_field5C;
	void *m_message;
	char m_field64;
	char m_field65;
	char m_pad66[2];
	int m_field68;
	char m_pad6C[4];
	int m_field70;
	int m_field74;
	int m_field78;
};

void Rva00802A90Elem::notify( Rva00802A90Query *query, void *context,
	int initialize, int id )
{
	Rva007FBC60Game *record = (Rva007FBC60Game *)query;
	m_host = (Rva00801670Host *)context;
	m_lid = query->m_lid;
	m_gid = query->m_gid;
	((BfmeThingVHW *)this)->rva00801670( record );

	// The arena is deliberately scoped to the initial strings and message.
	// Retail then addresses the element's +0x10 subobject directly for the key
	// array and append loop, allowing the arena register to be reused by the
	// message pointer and eliminating the extra spill in the prior bank.
	{
		Rva00800460Arena *arena = (Rva00800460Arena *)&m_buffer;
		((Rva00800290Buffer *)arena)->allocate();
		m_name = arena->append( record->m_name );
		m_hostName = arena->append( record->m_hostName );
		m_version = arena->append( record->m_version );

        m_field78 = record->m_join;
        char *platform = record->rva007FBE70();
        if (platform) {
            m_message = new (m_message = arena->claim(0x28, true)) Rva007F4DA0;
            ((Rva007F4DA0 *)m_message)->configure(platform, record->m_p);
        } else {
            m_message = new (m_message = arena->claim(0x10, true)) Rva007F6D60Member2C;
            ((Rva007E8760Addr *)m_message)->parse(record->m_data170, record->m_p);
        }
	}

	Rva00801670Host *host = m_host;
	BfmeVecCZ *vector = &host->m_gameKeys;
	int count = vector->m_bfmeCount;
	m_keys = (char **)((Rva00800460Arena *)&m_buffer)->claim( count * 4, true );
	for( int index = 0; index < count; ++index )
	{
		char *key = (char *)m_host->rva007F76D0( vector, index );
		char text[0x40];
		text[0] = 0;
		if( !record->rva007FBE80( key, text, sizeof(text) ) )
			m_keys[index] = 0;
		else
			m_keys[index] = ((Rva00800460Arena *)&m_buffer)->append( text );
	}

	m_field50 = record->m_mp;
	m_field54 = record->m_ap;
	m_field58 = record->m_jp;
	m_field5C = record->m_qp;
	m_field64 = record->m_password;
	m_field65 = record->m_flag;
	m_field68 = record->m_nf;
	m_field70 = *(int *)((char *)record + 0x128);
	m_field74 = *(int *)((char *)record + 0x12C);
	if( !*(unsigned char *)&initialize )
	{
		((Rva00801570 *)((char *)this + 0x3c))->allocate( m_field54 );
		m_field44 = 0;
		m_field48 = id;
	}
}
