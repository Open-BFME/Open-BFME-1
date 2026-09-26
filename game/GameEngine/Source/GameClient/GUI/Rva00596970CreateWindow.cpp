// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00596970, 286 bytes. The owner class has no name in the image, so
// the class keeps its address. The body creates a window through
// GameWindowManager virtual slot 29, allocates a 0x38-byte
// Rva004948B0OwnedSubsystem around the callback bfmeGoVLF 0x005892D0 and runs
// its init, resets six flag bytes at this+0x18 through bfmeGo1071A, and
// clears the deque at this+0x20.

namespace _STL
{
	template <class T> class allocator
	{
	};

	template <class T, class Alloc = allocator<T> > class deque
	{
	public:
		void clear();

	private:
		unsigned char m_data[ 40 ];
	};
}

struct Gen_t_005914e0_p12cd
{
	int a[ 3 ];
	Gen_t_005914e0_p12cd();
	Gen_t_005914e0_p12cd( const Gen_t_005914e0_p12cd & );
	~Gen_t_005914e0_p12cd();
	Gen_t_005914e0_p12cd &operator=( const Gen_t_005914e0_p12cd & );
};

class GameWindow
{
public:
	unsigned char m_head[ 0x1f4 ];
	void *m_field1F4;
};

class WinInstanceData
{
public:
	WinInstanceData();
	virtual ~WinInstanceData();

private:
	unsigned char m_data[ 0x1a4 ];
};

// The creation record handed to slot 29 as one pointer: 0x34 bytes, with the
// draw callback at +0x20.
struct Rva00596970WindowDesc
{
	GameWindow *m_parent;
	unsigned int m_status;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	int m_field18;
	int m_field1C;
	void *m_callback;
	int m_field24;
	int m_field28;
	int m_field2C;
	int m_field30;
};

#define WINDOW_MANAGER_SLOT( n ) virtual void _bfme_slot##n( void ) = 0
class GameWindowManager
{
public:
	WINDOW_MANAGER_SLOT( 0 ); WINDOW_MANAGER_SLOT( 1 ); WINDOW_MANAGER_SLOT( 2 );
	WINDOW_MANAGER_SLOT( 3 ); WINDOW_MANAGER_SLOT( 4 ); WINDOW_MANAGER_SLOT( 5 );
	WINDOW_MANAGER_SLOT( 6 ); WINDOW_MANAGER_SLOT( 7 ); WINDOW_MANAGER_SLOT( 8 );
	WINDOW_MANAGER_SLOT( 9 ); WINDOW_MANAGER_SLOT( 10 ); WINDOW_MANAGER_SLOT( 11 );
	WINDOW_MANAGER_SLOT( 12 ); WINDOW_MANAGER_SLOT( 13 ); WINDOW_MANAGER_SLOT( 14 );
	WINDOW_MANAGER_SLOT( 15 ); WINDOW_MANAGER_SLOT( 16 ); WINDOW_MANAGER_SLOT( 17 );
	WINDOW_MANAGER_SLOT( 18 ); WINDOW_MANAGER_SLOT( 19 ); WINDOW_MANAGER_SLOT( 20 );
	WINDOW_MANAGER_SLOT( 21 ); WINDOW_MANAGER_SLOT( 22 ); WINDOW_MANAGER_SLOT( 23 );
	WINDOW_MANAGER_SLOT( 24 ); WINDOW_MANAGER_SLOT( 25 ); WINDOW_MANAGER_SLOT( 26 );
	WINDOW_MANAGER_SLOT( 27 ); WINDOW_MANAGER_SLOT( 28 );
	virtual GameWindow *_bfme_slot29( Rva00596970WindowDesc *desc ) = 0;
};
#undef WINDOW_MANAGER_SLOT

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

class Rva004948B0Resource;

class Rva004948B0OwnedSubsystem : public SubsystemInterface
{
public:
	Rva004948B0OwnedSubsystem( void *factory );
	virtual ~Rva004948B0OwnedSubsystem();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	Rva004948B0Resource *m_resource;
	void *m_field0C;
	void *m_field10;
	void *m_field14;
	void *m_field18;
	void *m_field1C;
	unsigned char m_bits : 3;
	int m_field24;
	void *m_field28;
	void *m_field2C;
	void *m_factory;
	void *m_field34;
};

struct Rva00579160Manager;
extern Rva00579160Manager *Rva00579160TheManager;
extern GameWindowManager *TheWindowManager;

void bfmeGo1071A( int index, char value );
void bfmeGoVLF( void );
void b_004bffe0( void );

class Rva00596970
{
public:
	void create( void );

private:
	unsigned char m_head[ 0x0c ];
	GameWindow *m_window;
	Rva004948B0OwnedSubsystem *m_subsystem;
	int m_field14;
	char m_flags[ 6 ];
	char m_pad1E[ 2 ];
	_STL::deque<Gen_t_005914e0_p12cd> m_queue;
};

void Rva00596970::create( void )
{
	if( Rva00579160TheManager == 0 )
		return;

	WinInstanceData inst;

	Rva00596970WindowDesc desc;
	desc.m_parent = 0;
	desc.m_field18 = 0;
	desc.m_field1C = 0;
	desc.m_field24 = 0;
	desc.m_field28 = 0;
	desc.m_field2C = 0;
	desc.m_field30 = 0;
	desc.m_status = 0x8000408;
	desc.m_x = -0x80;
	desc.m_y = -0x80;
	desc.m_width = -0x80;
	desc.m_height = -0x80;
	desc.m_callback = (void *)b_004bffe0;

	GameWindow *window = TheWindowManager->_bfme_slot29( &desc );
	m_window = window;
	window->m_field1F4 = 0;

	Rva004948B0OwnedSubsystem *subsystem =
		new Rva004948B0OwnedSubsystem( (void *)bfmeGoVLF );
	m_subsystem = subsystem;
	subsystem->init();

	for( int i = 0; i < 6; ++i )
	{
		bfmeGo1071A( i, 0 );
		m_flags[ i ] = 0;
	}

	m_queue.clear();
}
