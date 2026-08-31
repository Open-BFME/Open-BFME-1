// ?d_0010eee0@@YAXXZ
// partial score=0.87 date=2026-08-31
// cl: /DNDEBUG /D_STLP_USE_STATIC_LIB /MD /EHsc
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva0010EEE0AuxiliaryValue
{
	unsigned first;
	unsigned second;
};

class Rva0010EEE0GameState
{
public:
	void reset();

private:
	void clearAvailableGamesViaThunk();
	char m_pad0[0x48];
	_STL::list<void *> m_snapshotList;
	_STL::list<Rva0010EEE0AuxiliaryValue> m_auxiliaryList;
	void *m_availableGames;
	bool m_isInLoadGame;
};

void Rva0010EEE0GameState::reset()
{
	m_snapshotList.clear();
	m_auxiliaryList.clear();
	clearAvailableGamesViaThunk();
	m_isInLoadGame = false;
}
