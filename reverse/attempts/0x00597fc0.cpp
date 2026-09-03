// ??0GameClient@@QAE@XZ
// partial score=0.9 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWMath
// stlport

#define _STLP_NO_EXCEPTIONS 1

#include <deque>
#include <list>
#include <map>
#include "../../../../Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../../Code/Libraries/Source/WWVegas/WWMath/coord2d.h"

struct GameClientCoordValues
{
	float x;
	float y;
};

struct GameClientStateFields
{
	volatile unsigned int m_18;
	volatile unsigned short m_1c;
	unsigned char m_pad[2];
};

extern void j_0002c2a5();
extern void j_00020473();
extern void j_00030283();
extern void j_00039d33();
extern void j_000191aa();
extern void j_00048e96();
extern void j_000176a7();

typedef void (*GameClientCoord2DFunction)(void *);
extern void __stdcall rva00906340VecCtor(void *ptr, unsigned size, int count,
	GameClientCoord2DFunction ctor, GameClientCoord2DFunction dtor);

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() {}

	private:
	void *m_name;
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc() {}
	virtual void xfer() {}
	virtual void loadPostProcess() {}
};

typedef AsciiString BFMERetailAsciiString;

struct Gen_t_0058f2f0_p12cd
{
	char m_body[12];
};

typedef _STL::deque<Gen_t_0058f2f0_p12cd> GameClientDeque;

class GameClientMember936a0
{
public:
	GameClientMember936a0()
	{
		((void (__fastcall *)(GameClientMember936a0 *))j_00020473)(this);
	}
	~GameClientMember936a0() { m_pad[0] = 0; }

private:
	unsigned char m_pad[0xec];
};

class GameClientMember93980
{
public:
	GameClientMember93980()
	{
		((void (__fastcall *)(GameClientMember93980 *))j_00030283)(this);
	}
	~GameClientMember93980() { m_pad[0] = 0; }

private:
	unsigned char m_pad[0x28];
};

class GameClientMember97790
{
public:
	GameClientMember97790()
	{
		((void (__fastcall *)(GameClientMember97790 *))j_00039d33)(this);
	}
	~GameClientMember97790() { m_pad[0] = 0; }

private:
	unsigned char m_pad[0x13c];
};

class GameClientMember95ac0
{
public:
	GameClientMember95ac0()
	{
		((void (__fastcall *)(GameClientMember95ac0 *))j_000191aa)(this);
	}
	~GameClientMember95ac0() { m_pad[0] = 0; }

private:
	unsigned char m_pad[0x1a8];
};

class GameClientMember92280
{
public:
	GameClientMember92280()
	{
		((void (__fastcall *)(GameClientMember92280 *))j_00048e96)(this);
	}
	~GameClientMember92280() { m_pad[0] = 0; }

private:
	unsigned char m_pad[0x28];
};

class GameClientMember92640
{
public:
	GameClientMember92640()
	{
		((void (__fastcall *)(GameClientMember92640 *))j_000176a7)(this);
	}
	~GameClientMember92640() { m_pad[0] = 0; }
	void clearTail()
	{
		unsigned char *point = m_pad + 0x30;
		unsigned char *end = m_pad + 0x3c;
		while (point != end)
			*point++ = 0;
	}

private:
	unsigned char m_pad[0x3c];
};

class GameClientTailFields
{
public:
	__forceinline GameClientTailFields()
		: m_4c4(0), m_4c5(0), m_4c8(0), m_4cc(0),
		  m_4d0(0xffffffff), m_4d4(0) {}
	~GameClientTailFields()
	{
		::operator delete(m_4cc);
	}

	unsigned char m_4c4;
	unsigned char m_4c5;
	unsigned char m_pad[2];
	unsigned int m_4c8;
	void *m_4cc;
	unsigned int m_4d0;
	unsigned char m_4d4;
	unsigned char m_tailPad[3];
};

struct GameClientTreePayload
{
	int m_value;
};

typedef _STL::pair<const int, GameClientTreePayload> GameClientTreePair;
typedef _STL::_Rb_tree<int, GameClientTreePair,
	_STL::_Select1st<GameClientTreePair>, _STL::less<int>,
	_STL::allocator<GameClientTreePair> > GameClientList;

class GameClientCoordArray
{
public:
	Coord2D *data()
	{
		return m_data;
	}

	private:
	Coord2D m_data[4];
};

class __multiple_inheritance GameClientFunctorTarget;

class GameClientCallbackSourceBase0
{
public:
	virtual ~GameClientCallbackSourceBase0();

private:
	char m_body[0x254];
};

class GameClientCallbackSourceBase1 {};

class __multiple_inheritance GameClientCallbackSource
	: public GameClientCallbackSourceBase0,
	  public GameClientCallbackSourceBase1
{
public:
	void onMinLOD();
	void onPlayerMagicButtonClip();
	void onOptions();
	void onObjectivesButtonClip();
	void onPlayerPowerCap();
	void onNextPlayerButton();
	void onPriorPlayerButton();
	void onButtonObjectives();
	void onButtonMovie();
	void onObserveNextPlayer();
	void onObservePriorPlayer();
};

typedef void (GameClientFunctorTarget::*GameClientFunctorMethod)();

struct GameClientFunctorBinding
{
	GameClientFunctorBinding(GameClientFunctorMethod method,
		GameClientFunctorTarget *target)
		: m_target(target), m_method(method) {}

	GameClientFunctorTarget *m_target;
	unsigned int m_unmodelled;
	GameClientFunctorMethod m_method;
};

class GameClientFunctorWrapperHead
{
public:
	GameClientFunctorWrapperHead() : m_refCount(0) {}
	virtual void anchor();

	unsigned int m_refCount;
};

class GameClientFunctorWrapper0 : public GameClientFunctorWrapperHead
{
public:
	GameClientFunctorWrapper0(const GameClientFunctorBinding &binding)
		: m_binding(binding) {}

	GameClientFunctorBinding m_binding;
};

class GameClientFunctorWrapper1 : public GameClientFunctorWrapperHead
{
public:
	GameClientFunctorWrapper1(const GameClientFunctorBinding &binding)
		: m_binding(binding) {}

	GameClientFunctorBinding m_binding;
};

class GameClientFunctorHolder0
{
public:
	__forceinline GameClientFunctorHolder0(GameClientFunctorBinding binding)
	{
		m_ptr = new GameClientFunctorWrapper0(binding);
		if (m_ptr != 0)
			m_ptr->m_refCount++;
	}

	GameClientFunctorWrapper0 *m_ptr;
};

class GameClientFunctorHolder1Middle
{
public:
	__forceinline GameClientFunctorHolder1Middle(GameClientFunctorBinding binding)
	{
		m_ptr = new GameClientFunctorWrapper1(binding);
		if (m_ptr != 0)
			m_ptr->m_refCount++;
	}

	GameClientFunctorWrapper1 *m_ptr;
};

class GameClientFunctorHolder1Last
{
public:
	__forceinline GameClientFunctorHolder1Last(GameClientFunctorBinding binding)
	{
		m_ptr = new GameClientFunctorWrapper1(binding);
		if (m_ptr != 0)
			m_ptr->m_refCount++;
	}

	GameClientFunctorWrapper1 *m_ptr;
};

class WindowManager
{
public:
	void registerPalantirPlayerSide(const BFMERetailAsciiString &name,
		int unknown, GameClientFunctorHolder0 callback);
	void registerPalantirCallback(const BFMERetailAsciiString &name,
		GameClientFunctorHolder1Middle callback);
	void registerAptCallback(const BFMERetailAsciiString &name,
		GameClientFunctorHolder1Last callback);
};

extern WindowManager *g_theWindowManager;

class GameClient : public SubsystemInterface, public Snapshot
{
public:
	GameClient();
	virtual ~GameClient();

private:
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
	GameClientStateFields m_state;
	GameClientDeque m_deque;

	unsigned char m_48;
	unsigned char m_49;
	unsigned char m_4a;
	unsigned char m_4b;
	unsigned char m_4c;
	unsigned char m_4d[3];
	unsigned int m_50;
	unsigned int m_54;
	unsigned char m_58;
	unsigned char m_59[3];
	unsigned int m_5c;
	unsigned int m_60;
	unsigned int m_64;

	GameClientMember936a0 m_68;
	GameClientMember93980 m_154;
	GameClientMember97790 m_17c;
	GameClientMember95ac0 m_2b8;
	GameClientMember92280 m_460;
	GameClientMember92640 m_488;

	GameClientTailFields m_tail;
	BFMERetailAsciiString m_4d8;
	Coord2D m_4dc[4];
	GameClientList m_4fc;
	unsigned int m_508;
	unsigned char m_50c;
};

GameClient::GameClient()
	: m_0c(0), m_10(0), m_14(0),
	  m_48(0), m_49(0), m_4b(1), m_4c(1), m_50(0), m_54(0),
	  m_58(m_58 & 4), m_5c(0xffffffff), m_60(0), m_64(1),
	  m_tail(), m_4d8(), m_508(0), m_50c(0)
{
	GameClientFunctorMethod callback;
	j_0002c2a5();
	m_state.m_18 = 0;
	m_state.m_1c = 0;
	{
		callback =
			(GameClientFunctorMethod)&GameClientCallbackSource::onMinLOD;
		BFMERetailAsciiString name("PalantirMinLOD");
		g_theWindowManager->registerPalantirPlayerSide(name,
			0, GameClientFunctorBinding(callback,
				(GameClientFunctorTarget *)this));
	}

	{
		callback =
			(GameClientFunctorMethod)&GameClientCallbackSource::onPlayerMagicButtonClip;
		BFMERetailAsciiString name(
			"Palantir/PalantirButtons/Buttons/PlayerMagic/ButtonClip/");
		g_theWindowManager->registerPalantirCallback(name,
			GameClientFunctorBinding(callback,
				(GameClientFunctorTarget *)this));
	}

	{
		callback =
			(GameClientFunctorMethod)&GameClientCallbackSource::onOptions;
		BFMERetailAsciiString name(
			"Palantir/PalantirButtons/Buttons/Options");
		g_theWindowManager->registerPalantirCallback(name,
			GameClientFunctorBinding(callback,
				(GameClientFunctorTarget *)this));
	}

	{
		callback =
			(GameClientFunctorMethod)&GameClientCallbackSource::onObjectivesButtonClip;
		BFMERetailAsciiString name(
			"Palantir/PalantirButtons/Buttons/Objectives/ButtonClip/");
		g_theWindowManager->registerPalantirCallback(name,
			GameClientFunctorBinding(callback,
				(GameClientFunctorTarget *)this));
	}

	{
		callback =
			(GameClientFunctorMethod)&GameClientCallbackSource::onPlayerPowerCap;
		BFMERetailAsciiString name(
			"Palantir/PalantirButtons/Buttons/PlayerPowerCap/");
		g_theWindowManager->registerPalantirCallback(name,
			GameClientFunctorBinding(callback,
				(GameClientFunctorTarget *)this));
	}

	{
		callback =
			(GameClientFunctorMethod)&GameClientCallbackSource::onNextPlayerButton;
		BFMERetailAsciiString name(
			"Palantir/ObserverStuff/NextPlayerBttn");
		g_theWindowManager->registerPalantirCallback(name,
			GameClientFunctorBinding(callback,
				(GameClientFunctorTarget *)this));
	}

	{
		callback =
			(GameClientFunctorMethod)&GameClientCallbackSource::onPriorPlayerButton;
		BFMERetailAsciiString name(
			"Palantir/ObserverStuff/PriorPlayerBttn");
		g_theWindowManager->registerPalantirCallback(name,
			GameClientFunctorBinding(callback,
				(GameClientFunctorTarget *)this));
	}

	{
		callback =
			(GameClientFunctorMethod)&GameClientCallbackSource::onButtonObjectives;
		BFMERetailAsciiString name("AptPalantir::OnBttnObjectives");
		g_theWindowManager->registerAptCallback(name,
			GameClientFunctorBinding(callback,
				(GameClientFunctorTarget *)this));
	}

	{
		callback =
			(GameClientFunctorMethod)&GameClientCallbackSource::onButtonMovie;
		BFMERetailAsciiString name("AptPalantir::OnBttnMovie");
		g_theWindowManager->registerAptCallback(name,
			GameClientFunctorBinding(callback,
				(GameClientFunctorTarget *)this));
	}

	{
		callback =
			(GameClientFunctorMethod)&GameClientCallbackSource::onObserveNextPlayer;
		BFMERetailAsciiString name(
			"AptPalantir::OnBttnObserveNextPlayer");
		g_theWindowManager->registerAptCallback(name,
			GameClientFunctorBinding(callback,
				(GameClientFunctorTarget *)this));
	}

	{
		callback =
			(GameClientFunctorMethod)&GameClientCallbackSource::onObservePriorPlayer;
		BFMERetailAsciiString name(
			"AptPalantir::OnBttnObservePriorPlayer");
		g_theWindowManager->registerAptCallback(name,
			GameClientFunctorBinding(callback,
				(GameClientFunctorTarget *)this));
	}

	m_488.clearTail();

	Coord2D *point = m_4dc;
	Coord2D *end = (Coord2D *)&m_4fc;
	volatile GameClientCoordValues zero;
	zero.x = 0.0f;
	zero.y = 0.0f;
	while (point != end)
	{
		point->x = zero.x;
		point->y = zero.y;
		++point;
	}
}
