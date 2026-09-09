// cl: /O2 /Oy /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

typedef int Int;

enum ScienceType
{
	SCIENCE_VALUE = 0
};

struct ICoord2D
{
	int value;
};

namespace _STL
{

template <class Type> class allocator {};

template <class Type, class Allocator = allocator<Type> >
class vector
{
public:
	typedef Type *iterator;
	typedef const Type *const_iterator;

	iterator begin() { return m_start; }
	const_iterator begin() const { return m_start; }
	iterator end() { return m_finish; }
	const_iterator end() const { return m_finish; }

	vector &operator=( const vector &other );

	void clear()
	{
		erase( begin(), end() );
	}

	iterator erase( iterator first, iterator last )
	{
		iterator result = copy( last, m_finish, first );
		m_finish = result;
		return result;
	}

private:
	template <class Value>
	static Value *copy( Value *first, Value *last, Value *result )
	{
		int count = (int)( last - first );
		while ( count > 0 )
		{
			*result = *first;
			++first;
			++result;
			--count;
		}
		return result;
	}

	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};

}

typedef _STL::vector<ICoord2D> ScienceVec;

class PlayerTemplate
{
public:
	const ScienceVec &getCampaignSciences() const
	{
		return m_campaignSciences;
	}

	const ScienceVec &getIntrinsicSciences() const
	{
		return m_intrinsicSciences;
	}

private:
	unsigned char m_padding00[ 0x8c ];
	ScienceVec m_campaignSciences;
	ScienceVec m_intrinsicSciences;
};

class GameLogicPortraitShim
{
public:
	bool isInMultiplayerOrSkirmishGame();
};

class RankInfo
{
private:
	unsigned char m_padding00[ 0x2c ];

public:
	ScienceVec m_sciencesGranted;
};

class RankInfoStore
{
public:
	const RankInfo *getRankInfo( Int level ) const;
};

class ScriptEngine
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void notifyOfAcquiredScience( Int playerIndex, ScienceType science );
};

extern GameLogicPortraitShim *TheBfmeGameLogic;
extern RankInfoStore *TheRankInfoStore;
extern ScriptEngine *TheScriptEngine;

class Player
{
public:
	void resetSciences();

private:
	bool addScience( ScienceType science );

	unsigned char m_vtable[ 4 ];
	PlayerTemplate *m_playerTemplate;
	unsigned char m_padding08[ 0x1c ];
	Int m_playerIndex;
	unsigned char m_padding28[ 0x20c ];
	ScienceVec m_sciences;
	unsigned char m_padding240[ 0x18 ];
	Int m_rankLevel;
};

void Player::resetSciences()
{
	m_sciences.clear();

	if ( m_playerTemplate != 0 )
	{
		if ( TheBfmeGameLogic->isInMultiplayerOrSkirmishGame() )
			m_sciences = m_playerTemplate->getIntrinsicSciences();
		else
			m_sciences = m_playerTemplate->getCampaignSciences();
	}

	for ( Int i = 1; i <= m_rankLevel; ++i )
	{
		const RankInfo *rank = TheRankInfoStore->getRankInfo( i );
		if ( rank != 0 )
		{
			ScienceVec::const_iterator it = rank->m_sciencesGranted.begin();
			while ( it != rank->m_sciencesGranted.end() )
			{
				addScience( (ScienceType)(*it).value );
				++it;
			}
		}
	}

	ScienceVec::const_iterator it = m_sciences.begin();
	while ( it != m_sciences.end() )
	{
		TheScriptEngine->notifyOfAcquiredScience( m_playerIndex, (ScienceType)(*it).value );
		++it;
	}
}
