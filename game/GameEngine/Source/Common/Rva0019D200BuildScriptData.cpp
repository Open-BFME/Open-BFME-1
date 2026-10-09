// ?buildScriptData@Rva001A0320Owner@@AAEXPAURva001A0320Record@@PAVScriptList@@PAVRva0019A1D0Owner@@@Z
// cl: /O2 /EHsc /Igame/Libraries/Source/WWVegas/WWLib

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

#include "ascii_string.h"

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
	Rva00197AE0Temporary();
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


namespace Rva0035E510 {
class BfmeNodeEAT { public: void bfmeSwapEAT(BfmeNodeEAT *other); };
}

void Rva001A0320Owner::buildScriptData( Rva001A0320Record *record,
	ScriptList *scripts, Rva0019A1D0Owner *tree )
{
	ScriptList *stored = record->m_scripts;
	if ( stored == 0 )
	{
		stored = new ScriptList;
		record->m_scripts = stored;
	}
	((Rva0035E510::BfmeNodeEAT *)stored)->bfmeSwapEAT((Rva0035E510::BfmeNodeEAT *)scripts);

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
			entries = (char *)tree->m_member.m_entries;
			index = *(short *)(entries + offset);
		}
	}
}

