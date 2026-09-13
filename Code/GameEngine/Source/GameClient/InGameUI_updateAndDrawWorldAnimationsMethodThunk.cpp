// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_NO_EXCEPTIONS
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
typedef int Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR
};

class BfmeGameLogicPause
{
public:
	bool isGamePaused();

	Int m_beforeFrame[ 0x3c / sizeof( Int ) ];
	Int m_frame;
};

#define TheGameLogic (*(BfmeGameLogicPause **)0x012F0898)
#define LOGICSECONDS_PER_FRAME (*(const Real *)0x01080BBC)
#define BfmeZeroRange (*(const Real *)0x01075350)

class Player
{
public:
	Int m_beforePlayerIndex[ 0x24 / sizeof( Int ) ];
	Int m_playerIndex;
};

class PlayerList
{
public:
	Int m_beforeLocalPlayer[ 0x0c / sizeof( Int ) ];
	Player *m_localPlayer;
};

#define ThePlayerList (*(PlayerList **)0x012ED748)

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer( Int playerIndex, const Coord3D *position ) const;
};

#define TheShroudManager (*(PartitionManager **)0x012ED5BC)

class TacticalView
{
public:
#define BFME_TACTICAL_SLOT(n) virtual void tacticalSlot##n();
	BFME_TACTICAL_SLOT(0)
	BFME_TACTICAL_SLOT(1)
	BFME_TACTICAL_SLOT(2)
	BFME_TACTICAL_SLOT(3)
	BFME_TACTICAL_SLOT(4)
	BFME_TACTICAL_SLOT(5)
	BFME_TACTICAL_SLOT(6)
	BFME_TACTICAL_SLOT(7)
	BFME_TACTICAL_SLOT(8)
	BFME_TACTICAL_SLOT(9)
	BFME_TACTICAL_SLOT(10)
	BFME_TACTICAL_SLOT(11)
	BFME_TACTICAL_SLOT(12)
	BFME_TACTICAL_SLOT(13)
	BFME_TACTICAL_SLOT(14)
	BFME_TACTICAL_SLOT(15)
	BFME_TACTICAL_SLOT(16)
	BFME_TACTICAL_SLOT(17)
	BFME_TACTICAL_SLOT(18)
	BFME_TACTICAL_SLOT(19)
	BFME_TACTICAL_SLOT(20)
	BFME_TACTICAL_SLOT(21)
	BFME_TACTICAL_SLOT(22)
	BFME_TACTICAL_SLOT(23)
	BFME_TACTICAL_SLOT(24)
	BFME_TACTICAL_SLOT(25)
	BFME_TACTICAL_SLOT(26)
	BFME_TACTICAL_SLOT(27)
	BFME_TACTICAL_SLOT(28)
	BFME_TACTICAL_SLOT(29)
	BFME_TACTICAL_SLOT(30)
	BFME_TACTICAL_SLOT(31)
	BFME_TACTICAL_SLOT(32)
	BFME_TACTICAL_SLOT(33)
	BFME_TACTICAL_SLOT(34)
	BFME_TACTICAL_SLOT(35)
	BFME_TACTICAL_SLOT(36)
	BFME_TACTICAL_SLOT(37)
	BFME_TACTICAL_SLOT(38)
	BFME_TACTICAL_SLOT(39)
	BFME_TACTICAL_SLOT(40)
	BFME_TACTICAL_SLOT(41)
	BFME_TACTICAL_SLOT(42)
	BFME_TACTICAL_SLOT(43)
	BFME_TACTICAL_SLOT(44)
	BFME_TACTICAL_SLOT(45)
	BFME_TACTICAL_SLOT(46)
	BFME_TACTICAL_SLOT(47)
	BFME_TACTICAL_SLOT(48)
	BFME_TACTICAL_SLOT(49)
	BFME_TACTICAL_SLOT(50)
	BFME_TACTICAL_SLOT(51)
	BFME_TACTICAL_SLOT(52)
	BFME_TACTICAL_SLOT(53)
	BFME_TACTICAL_SLOT(54)
	BFME_TACTICAL_SLOT(55)
	BFME_TACTICAL_SLOT(56)
	BFME_TACTICAL_SLOT(57)
	BFME_TACTICAL_SLOT(58)
	BFME_TACTICAL_SLOT(59)
	BFME_TACTICAL_SLOT(60)
	BFME_TACTICAL_SLOT(61)
	BFME_TACTICAL_SLOT(62)
	BFME_TACTICAL_SLOT(63)
	BFME_TACTICAL_SLOT(64)
	BFME_TACTICAL_SLOT(65)
	BFME_TACTICAL_SLOT(66)
	BFME_TACTICAL_SLOT(67)
	BFME_TACTICAL_SLOT(68)
	BFME_TACTICAL_SLOT(69)
	BFME_TACTICAL_SLOT(70)
	BFME_TACTICAL_SLOT(71)
	virtual Real getZoom() const;
	BFME_TACTICAL_SLOT(73)
	BFME_TACTICAL_SLOT(74)
	BFME_TACTICAL_SLOT(75)
	BFME_TACTICAL_SLOT(76)
	BFME_TACTICAL_SLOT(77)
	BFME_TACTICAL_SLOT(78)
	virtual Real getMaxZoom() const;
	BFME_TACTICAL_SLOT(80)
	BFME_TACTICAL_SLOT(81)
	BFME_TACTICAL_SLOT(82)
	BFME_TACTICAL_SLOT(83)
	BFME_TACTICAL_SLOT(84)
	BFME_TACTICAL_SLOT(85)
	BFME_TACTICAL_SLOT(86)
	virtual Bool worldToScreen( const Coord3D *world, ICoord2D *screen );
#undef BFME_TACTICAL_SLOT
};

#define TheTacticalView (*(TacticalView **)0x012F1600)

static Bool bfmeWorldToScreen( TacticalView *view, const Coord3D *world, ICoord2D *screen )
{
	return view->worldToScreen( world, screen );
}

class Rva005BA9E0Anim2D
{
public:
	virtual ~Rva005BA9E0Anim2D();
	char m_beforeStatus[ 0x0c ];
	UnsignedByte m_status;
	char m_beforeAlpha[ 0x0b ];
	Real m_alpha;

	UnsignedInt getCurrentFrameWidth() const;
	UnsignedInt getCurrentFrameHeight() const;
	void draw( Int x, Int y, Int width, Int height );
	void setAlpha( Real alpha ) { m_alpha = alpha; }
};

class Anim2D
{
public:
	UnsignedInt getCurrentFrameWidth() const;
	UnsignedInt getCurrentFrameHeight() const;
};

struct WorldAnimationData
{
	Rva005BA9E0Anim2D *m_anim;
	Coord3D m_worldPos;
	UnsignedInt m_expireFrame;
	UnsignedInt m_options;
	Real m_zRisePerSecond;
};

struct WorldAnimationNode
{
	WorldAnimationNode *m_next;
	WorldAnimationNode *m_previous;
	WorldAnimationData *m_value;
};

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate( void *address, UnsignedInt size );
};
}

class WorldAnimationList
{
public:
	WorldAnimationNode *m_node;
	WorldAnimationNode *begin() { return m_node->m_next; }
	WorldAnimationNode *end() { return m_node; }
};

typedef WorldAnimationNode *WorldAnimationListIterator;

class InGameUI
{

	protected:
	void updateAndDrawWorldAnimations();

private:
	char m_beforeWorldAnimationList[ 0x12c0 ];
	WorldAnimationList m_worldAnimationList;
};

// ?updateAndDrawWorldAnimations@InGameUI@@IAEXXZ
void InGameUI::updateAndDrawWorldAnimations()
{
	static const UnsignedInt framesBeforeExpireToFade = 5;
	WorldAnimationListIterator it = m_worldAnimationList.begin();
	WorldAnimationData *wad;

	while( it != m_worldAnimationList.end() )
	{
		wad = it->m_value;
		if( TheGameLogic->isGamePaused() == false )
		{
			if( TheGameLogic->m_frame >= wad->m_expireFrame ||
				((wad->m_options & 2) && (wad->m_anim->m_status & 4)) )
			{
				delete wad->m_anim;
				delete wad;
				WorldAnimationNode *next = it->m_next;
				WorldAnimationNode *previous = it->m_previous;
				previous->m_next = next;
				next->m_previous = previous;
				_STL::__node_alloc<true, 0>::_M_deallocate( it, 0xc );
				it = next;
				continue;
			}

			if( wad->m_zRisePerSecond != BfmeZeroRange )
				wad->m_worldPos.z += (*(volatile Real *)&wad->m_zRisePerSecond) * LOGICSECONDS_PER_FRAME;
		}

		Int playerIndex = ThePlayerList->m_localPlayer->m_playerIndex;
		if( TheShroudManager->getShroudStatusForPlayer( playerIndex, &wad->m_worldPos ) != CELLSHROUD_CLEAR )
		{
			it = it->m_next;
			continue;
		}

		if( wad->m_options & 1 )
		{
			UnsignedInt framesTillExpire = wad->m_expireFrame - TheGameLogic->m_frame;
			if( framesTillExpire < (Int)framesBeforeExpireToFade )
			{
				Real alpha = (Real)framesTillExpire;
				Rva005BA9E0Anim2D *anim = wad->m_anim;
				alpha *= LOGICSECONDS_PER_FRAME;
				anim->setAlpha( alpha );
			}
		}

		ICoord2D screen;
		if( bfmeWorldToScreen( TheTacticalView, &wad->m_worldPos, &screen ) == false )
		{
			UnsignedInt width = ((Anim2D *)wad->m_anim)->getCurrentFrameWidth();
			UnsignedInt height = ((Anim2D *)wad->m_anim)->getCurrentFrameHeight();
			TacticalView *camera = TheTacticalView;
			Real maxZoom = camera->getMaxZoom();
			Real zoomScale = maxZoom / TheTacticalView->getZoom();
			width *= zoomScale;
			height *= zoomScale;
			screen.x -= width / 2;
			screen.y -= height / 2;
			wad->m_anim->draw( screen.x, screen.y, width, height );
		}

		it = it->m_next;
	}
}
