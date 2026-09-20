// ?h005143D0@Glo00EF4988@@QAEXXZ
// partial score=0.66 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;

class GameWindow;

struct Rva00579160Manager
{
	void fire( void *target, const char *name, Int a, Int b, Int c, Int d,
		Int e, Int f );
};
extern Rva00579160Manager *Rva00579160TheManager;
extern char g_bfmeFmtC1064[];

namespace _STL
{
template <bool threads, Int instance>
class __node_alloc
{
public:
	static void _M_deallocate( void *p, unsigned int bytes );
};
}

void operator delete( void *p );

struct Rva005143D0Vector
{
	Rva005143D0Vector() : m_begin( 0 ), m_finish( 0 ), m_end( 0 ) {}

	~Rva005143D0Vector()
	{
		int *begin = m_begin;
		if (begin != 0)
		{
			unsigned int bytes = static_cast<unsigned int>((m_end - begin) * 4);
			if (bytes > 0x80)
				::operator delete( begin );
			else
				_STL::__node_alloc<true, 0>::_M_deallocate( begin, bytes );
		}
	}

	int *m_begin;
	int *m_finish;
	int *m_end;
};

extern void Rva004EF980AcceptBuddyRequest( Int profileID );

class BfmeAptScreenInGameChat
{
public:
	Int rva00513BF0( GameWindow *list, void *values, Int mode, Bool selected );
};

class Glo00EF4988
{
public:
	void h005143D0();

private:
	unsigned char m_before250[0x250];
	void *m_target;
	unsigned char m_between254And264[0x10];
	GameWindow *m_list;
	unsigned char m_between268And292[0x2a];
	Bool m_addDirty;
	Bool m_addEnabled;
	Bool m_removeDirty;
	Bool m_removeEnabled;
	unsigned char m_after296[0x0c];
};

#pragma comment(linker, "/alternatename:?rva00513BF0@BfmeAptScreenInGameChat@@QAEHPAVGameWindow@@PAXH_N@Z=?j_00017373@@YAXXZ")

void Glo00EF4988::h005143D0()
{
	Rva005143D0Vector values;

	if (m_addDirty || m_addEnabled)
	{
		m_addDirty = false;
		m_addEnabled = false;
		Rva00579160TheManager->fire( m_target, "DisableAddButton", 0, 0, 0, 0, 0, 0 );
	}

	if (m_removeDirty || m_removeEnabled)
	{
		void *target = m_target;
		m_removeDirty = false;
		m_removeEnabled = false;
		Rva00579160TheManager->fire( target, g_bfmeFmtC1064, 0, 0, 0, 0, 0, 0 );
	}

	GameWindow *list = m_list;
	Int count = ((BfmeAptScreenInGameChat *)this)->rva00513BF0(
		list, &values, 7, true );
	if (count)
	{
		int *begin = values.m_begin;
		int *it = begin;
		int *end = values.m_finish;
		if (it != end)
		{
			do
			{
				Rva004EF980AcceptBuddyRequest( *it );
				++it;
			}
			while (it != end);
		}
	}
}
