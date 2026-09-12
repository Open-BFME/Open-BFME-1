// ?probe@Gen003BFB20Owner@@QAE_NPAX@Z
// partial score=0.97 date=2026-09-12
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib

#define _STLP_NO_EXCEPTIONS 1
#include "../reference/shims/stringinline/StringInline.h"

extern "C" __declspec(dllimport) void *__cdecl memmove( void *destination, const void *source, unsigned int count );

struct BfmeObj923GState
{
	char m_pad00[ 0x18 ];
	unsigned char m_active;
};

class BfmeObj923G
{
public:
	char m_pad00[ 0x3C ];
	AsciiString m_name;
	char m_pad40[ 0x40 ];
	int m_value80;
	char m_pad84[ 0x28 ];
	int m_handleAC;
	char m_padB0[ 0x4 ];
	void *m_createdB4;
	AsciiString m_messageB8;
	char m_padBC[ 0x30 ];
	BfmeObj923GState *m_stateEC;
};

extern BfmeObj923G *__stdcall bfmeFind923G( void *key );
extern void *__cdecl bfmeMakeBNG( void *one, void *two );

class BfmeGameCW
{
public:
	void removeEntry( int handle );
};

#pragma comment(linker, "/alternatename:?removeEntry@BfmeGameCW@@QAEXH@Z=?j_00010ffa@@YAXXZ")

extern BfmeGameCW *g_bfmeGameCW;

class Glo012F1028Type
{
public:
	void addValue( int amount )
	{
		m_valueA0 += amount;
	}

	void enterSelectedIlt( AsciiString *name );
	char m_pad00[ 0xA0 ];
	volatile int m_valueA0;
};

#pragma comment(linker, "/alternatename:?enterSelectedIlt@Glo012F1028Type@@QAEXPAVAsciiString@@@Z=?j_00025720@@YAXXZ")

extern Glo012F1028Type *TheLivingWorldCampaignManager;

struct BfmeStringInlineData
{
	int m_refCount;
	unsigned short m_length;
};

class BfmePointerVector
{
public:
	unsigned int size() const
	{
		return (unsigned int)( m_finish - m_start );
	}

	BfmeObj923G **begin() const
	{
		return m_start;
	}

	void erase( BfmeObj923G **position )
	{
		BfmeObj923G **next = position + 1;
		if ( m_finish != next )
			memmove( position, next, (unsigned int)( (char *)m_finish - (char *)next ) );
		--m_finish;
	}

	BfmeObj923G **m_start;
	BfmeObj923G **m_finish;
};

class Gen003BFB20Storage
{
public:
	void *m_vtable;
	char m_pad04[ 0x10 ];
	BfmePointerVector m_objects;
};

class Gen003BFB20Owner : public Gen003BFB20Storage
{
public:
	bool probe( void *key );
	void recomputeIlt();
};

#pragma comment(linker, "/alternatename:?recomputeIlt@Gen003BFB20Owner@@QAEXXZ=?j_000349f5@@YAXXZ")

bool Gen003BFB20Owner::probe( void *key )
{
	BfmeObj923G *object = bfmeFind923G( key );
	if ( object != 0 )
	{
		char *owner = (char *)this;
		void *created = bfmeMakeBNG( (void *)1, (void *)1 );
		object->m_createdB4 = created;
		BfmeObj923GState *state = object->m_stateEC;
		state->m_active = 1;
		object->m_messageB8.~AsciiString();

		for ( unsigned int index = 0; index < ((BfmePointerVector *)( owner + 0x14 ))->size(); ++index )
		{
			if ( ((BfmePointerVector *)( owner + 0x14 ))->begin()[ index ] == object )
			{
				((BfmePointerVector *)( owner + 0x14 ))->erase(
					((BfmePointerVector *)( owner + 0x14 ))->begin() + index );
				break;
			}
		}

		int handle = object->m_handleAC;
		g_bfmeGameCW->removeEntry( handle );
		TheLivingWorldCampaignManager->addValue( object->m_value80 );
		recomputeIlt();

		AsciiString name = object->m_name;
		if ( *(BfmeStringInlineData **)&name != 0 && (*(BfmeStringInlineData **)&name)->m_length != 0 )
		{
			TheLivingWorldCampaignManager->enterSelectedIlt( &name );
			return false;
		}
	}

	return true;
}
