// ?buildScriptData@Rva001A0320Owner@@AAEXPAURva001A0320Record@@PAVScriptList@@PAVRva0019A1D0Owner@@@Z
// partial score=0.78 date=2026-09-10
// cl: /O2 /EHsc

typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

namespace _STL
{

class __new_alloc
{
public:
	static void *allocate( unsigned int bytes );
};

}

class AsciiString
{
public:
	void releaseBuffer();
	~AsciiString()
	{
		releaseBuffer();
	}
};

class Dict
{
public:
	AsciiString getAsciiString( NameKeyType key, Bool *exists ) const;

	char m_body[4];
};

class GenKey
{
public:
	int fetch();
};

extern GenKey GenKey0012A7988;

struct Rva001A0320Record
{
	void *m_buildList;
	Dict m_dict;
	class ScriptList *m_scripts;
	char m_tail[0x0c];
};

struct Rva0019A7D0Element
{
	int m_a;
	int m_b;
};

class Rva0019A7D0Vector
{
public:
	Rva0019A7D0Element *m_begin;
	Rva0019A7D0Element *m_end;
	Rva0019A7D0Element *m_capacity;
};

class Rva00197AE0Temporary
{
public:
	__forceinline Rva00197AE0Temporary()
		: m_header( 0 )
	{
		m_header = _STL::__new_alloc::allocate( 0x14 );
		m_count = 0;
		*(unsigned char *)m_header = 0;
		*(void **)((char *)m_header + 4) = 0;
		*(void **)((char *)m_header + 8) = m_header;
		*(void **)((char *)m_header + 12) = m_header;
	}
	~Rva00197AE0Temporary();

	void *m_header;
	int m_count;
	int m_compare;
};

class Rva0019A1D0Tree
{
public:
	~Rva0019A1D0Tree();

private:
	char m_body[0x0c];
};

class Rva0019A1D0Member
{
public:
	~Rva0019A1D0Member();

	void *m_entries;
	char m_body[8];
};

class Rva0019A1D0Owner
{
public:
	Rva0019A1D0Owner();

	Rva0019A1D0Tree m_tree;
	Rva0019A1D0Member m_member;
	short m_a;
	short m_b;
};

class ScriptList
{
public:
	ScriptList();
	~ScriptList();
	ScriptList &operator=( const ScriptList &that );

private:
	char m_body[0x4c];
};

class Rva0019BE80TeamRec
{
public:
	int append( const Dict *dict );

private:
	char m_body[0x1c];
};

class BfmeStructuredSwapRecord
{
public:
	void bfmeSwap( BfmeStructuredSwapRecord &other );
};

struct Rva0019A7988Entry
{
	char m_prefix[4];
	void *m_data;
	char m_tail[8];
};

class PlayerAITypeSet
{
public:
	int find( AsciiString *name );

	char m_prefix[8];
	Rva0019A7988Entry *m_entries;
};

extern PlayerAITypeSet *ThePlayerAITypeSet;

class Rva001A0320Owner
{
public:
	void fill( int index, Rva0019A7D0Vector *out );

private:
	char m_prefix[0x28];
	int m_count;
	Rva001A0320Record m_records[1];

	void fillHelper( int index, Rva0019A7D0Vector *out, void *entry,
		Rva00197AE0Temporary *temporary, ScriptList *scripts,
		Rva0019A1D0Owner *tree );
	void buildScriptData( Rva001A0320Record *record, ScriptList *scripts,
		Rva0019A1D0Owner *tree );
};

#pragma comment(linker, "/alternatename:?getAsciiString@Dict@@QBE?AVAsciiString@@W4NameKeyType@@PA_N@Z=?j_0002ff6d@@YAXXZ")
#pragma comment(linker, "/alternatename:?fetch@GenKey@@QAEHXZ=?j_00009304@@YAXXZ")
#pragma comment(linker, "/alternatename:?find@PlayerAITypeSet@@QAEHPAVAsciiString@@@Z=?j_0000336e@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00197AE0Temporary@@QAE@XZ=?j_000124db@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva0019A1D0Tree@@QAE@XZ=?j_0001a910@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva0019A1D0Member@@QAE@XZ=?j_0002d6a5@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva0019A1D0Owner@@QAE@XZ=?j_00008792@@YAXXZ")
#pragma comment(linker, "/alternatename:??0ScriptList@@QAE@XZ=?j_0002fe7d@@YAXXZ")
#pragma comment(linker, "/alternatename:??1ScriptList@@QAE@XZ=?j_0003b7ff@@YAXXZ")
#pragma comment(linker, "/alternatename:??4ScriptList@@QAEAAV0@ABV0@@Z=?j_000081b6@@YAXXZ")
#pragma comment(linker, "/alternatename:?append@Rva0019BE80TeamRec@@QAEHPBVDict@@@Z=?j_00045dc7@@YAXXZ")
#pragma comment(linker, "/alternatename:?fillHelper@Rva001A0320Owner@@AAEXHPAVRva0019A7D0Vector@@PAXPAVRva00197AE0Temporary@@PAVScriptList@@PAVRva0019A1D0Owner@@@Z=?j_00008634@@YAXXZ")
#pragma comment(linker, "/alternatename:?buildScriptData@Rva001A0320Owner@@AAEXPAURva001A0320Record@@PAVScriptList@@PAVRva0019A1D0Owner@@@Z=?j_0003dc0d@@YAXXZ")

void Rva001A0320Owner::buildScriptData( Rva001A0320Record *record,
	ScriptList *scripts, Rva0019A1D0Owner *tree )
{
	ScriptList *stored = record->m_scripts;
	if ( stored == 0 )
	{
		stored = new ScriptList;
		record->m_scripts = stored;
	}
	*stored = *scripts;

	if ( tree->m_a > 0 )
	{
		Rva0019BE80TeamRec *teams =
			(Rva0019BE80TeamRec *)((char *)this + 0x630);
		((BfmeStructuredSwapRecord *)teams)->bfmeSwap(
			*(BfmeStructuredSwapRecord *)tree);
		char *entries = (char *)tree->m_member.m_entries;
		int index = *(short *)entries;
		while ( index != 0 )
		{
			int offset = index << 4;
			teams->append( (Dict *)(entries + offset + 0x0c) );
			index = *(short *)(entries + offset);
		}
	}
}

void Rva001A0320Owner::fill( int index, Rva0019A7D0Vector *out )
{
	Rva001A0320Record *record;
	if ( index < 0 || index >= m_count )
		record = 0;
	else
		record = (Rva001A0320Record *)((char *)this + 0x2c + index * 0x18);

	Rva00197AE0Temporary temporary;
	ScriptList scripts;
	Rva0019A1D0Owner tree;
	Bool exists;
	AsciiString name = record->m_dict.getAsciiString(
		(NameKeyType)GenKey0012A7988.fetch(), &exists );
	if ( exists )
	{
		int type = ThePlayerAITypeSet->find( &name );
		if ( type != -1 )
		{
			Rva0019A7988Entry *entries = ThePlayerAITypeSet->m_entries;
			fillHelper( index, out,
				&entries[type].m_data, &temporary,
				&scripts, &tree );
		}
	}
	fillHelper( index, out, (char *)record + 0x0c, &temporary,
		&scripts, &tree );
	buildScriptData( record, &scripts, &tree );
}
