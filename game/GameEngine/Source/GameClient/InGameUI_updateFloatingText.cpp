// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_NO_EXCEPTIONS
// BFME InGameUI floating-text updater.  The BFME class moved the list and
// rate fields from the Zero Hour layout, so this TU keeps the retail view
// local to the recovered body.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef int Color;

inline Color GameMakeColor( UnsignedByte red, UnsignedByte green,
	UnsignedByte blue, UnsignedByte alpha )
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

extern void GameGetColorComponents( Color color, UnsignedByte *red,
	UnsignedByte *green, UnsignedByte *blue, UnsignedByte *alpha );
extern Real g_bfmeUint32Scale;

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate( void *address, UnsignedInt size );
};
}

class Rva0043F110ClientRoot4120
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual UnsignedInt getFrame();
};

class Rva0043F110GameEngine
{
public:
	unsigned char m_beforeFrame[ 0x34 ];
	Int m_frame;
};

extern Rva0043F110ClientRoot4120 *TheGameClient;
#define TheGameEngine (*(Rva0043F110GameEngine **)0x012ED524)

class Rva0043F110FloatingTextData
{
public:
	virtual ~Rva0043F110FloatingTextData();

	Color m_color;
	unsigned char m_beforeFrameTimeOut[ 0x14 ];
	Int m_frameTimeOut;
	Int m_frameCount;
};

struct Rva0043F110FloatingTextNode
{
	Rva0043F110FloatingTextNode *m_next;
	Rva0043F110FloatingTextNode *m_previous;
	Rva0043F110FloatingTextData *m_value;
};

class Rva0043F110FloatingTextList
{
public:
	Rva0043F110FloatingTextNode *begin()
	{
		return m_node->m_next;
	}

	Rva0043F110FloatingTextNode *end()
	{
		return m_node;
	}

	Rva0043F110FloatingTextNode *erase( Rva0043F110FloatingTextNode *it )
	{
		Rva0043F110FloatingTextNode *next = it->m_next;
		Rva0043F110FloatingTextNode *previous = it->m_previous;
		previous->m_next = next;
		next->m_previous = previous;
		_STL::__node_alloc<true, 0>::_M_deallocate( it, 0xc );
		return next;
	}

private:
	Rva0043F110FloatingTextNode *m_node;
};

typedef Rva0043F110FloatingTextNode *Rva0043F110FloatingTextListIt;

class Rva0043F110InGameUI
{
public:
	void updateFloatingText( void );

private:
	unsigned char m_beforeFloatingTextList[ 0x1298 ];
	Rva0043F110FloatingTextList m_floatingTextList;
	UnsignedInt m_floatingTextTimeOut;
	Real m_floatingTextMoveUpSpeed;
	Real m_floatingTextMoveVanishRate;
};

// ?updateFloatingText@InGameUI@@IAEXXZ
void Rva0043F110InGameUI::updateFloatingText( void )
{
	register Rva0043F110InGameUI *self = this;
	Rva0043F110FloatingTextData *ftd;
	Rva0043F110FloatingTextList &floatingTextList = self->m_floatingTextList;
	UnsignedInt currLogicFrame = TheGameClient->getFrame();
	UnsignedByte r, g, b, a;
	Int amount;
	static UnsignedInt lastLogicFrameUpdate = currLogicFrame;

	if( lastLogicFrameUpdate == currLogicFrame )
		return;

	lastLogicFrameUpdate = currLogicFrame;

	for( Rva0043F110FloatingTextListIt it = floatingTextList.begin();
		it != floatingTextList.end(); )
	{
		ftd = it->m_value;
		++ftd->m_frameCount;

		if( currLogicFrame > ftd->m_frameTimeOut )
		{
			GameGetColorComponents( ftd->m_color, &r, &g, &b, &a );
			amount = (Int)((self->m_floatingTextMoveVanishRate /
				(Real)TheGameEngine->m_frame) *
				(currLogicFrame - ftd->m_frameTimeOut));
			if( a - amount < 0 )
				a = 0;
			else
				a -= amount;
			ftd->m_color = GameMakeColor( r, g, b, a );

			if( a <= 0 )
			{
				it = floatingTextList.erase( it );
				delete ftd;
				continue;
			}
		}

		it = it->m_next;
	}
}
