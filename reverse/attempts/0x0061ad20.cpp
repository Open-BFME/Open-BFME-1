// ?parseRoomVector@Rva0061AD20@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.3 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

// Open-BFME7: INI field parser at 0x0061AD20 (188 B): loops
// getNextTokenOrNull(ini->m_sepsAt0x41c) building an AsciiString from each
// token and copy-constructing a GameSpyGroupRoom(const AsciiString&) at the
// tail of the instance's vector at +0x30 (matches the landed sibling
// vector<T> reallocating overflow thunk j_0003827b). Names are
// address-derived; the room class is opaque past its copy constructor.

class INI
{
public:
	char m_pad[ 0x41c ];
	const char *m_seps;			// +0x41c

	const char *getNextTokenOrNull(const char *seps);
};

class AsciiString
{
public:
	AsciiString(const char *s);
	~AsciiString();
};

class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom(const AsciiString &name);
	~GameSpyGroupRoom();
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type>
void __cdecl _Construct(Type *destination, const Type &value);

template <class Type, class Allocator>
class vector
{
public:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;

	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );
};
}

class Rva0061AD20Store
{
public:
	char m_bfmeHead[ 0x30 ];
	_STL::vector<GameSpyGroupRoom, _STL::allocator<GameSpyGroupRoom> > m_bfmeItems;
};

class Rva0061AD20
{
public:
	static void parseRoomVector( INI *ini, void *instance, void *, const void * );
};

// ?parseRoomVector@Rva0061AD20@@SAXPAVINI@@PAX1PBX@Z
void Rva0061AD20::parseRoomVector( INI *ini, void *instance, void *, const void * )
{
	Rva0061AD20Store *self = (Rva0061AD20Store *)instance;

	for( const char *token = ini->getNextTokenOrNull( ini->m_seps ); token != 0;
		 token = ini->getNextTokenOrNull( ini->m_seps ) )
	{
		AsciiString name( token );
		GameSpyGroupRoom room( name );

		_STL::vector<GameSpyGroupRoom, _STL::allocator<GameSpyGroupRoom> > &items = self->m_bfmeItems;
		if( items._M_finish != items._M_end_of_storage )
		{
			_STL::_Construct( items._M_finish, room );
			++items._M_finish;
		}
		else
		{
			items._M_insert_overflow( items._M_finish, room,
				_STL::__false_type(), 1, true );
		}
	}
}
