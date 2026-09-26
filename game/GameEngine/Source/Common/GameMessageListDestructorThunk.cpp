// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class __declspec(novtable) GameMessageList
{
public:
	virtual ~GameMessageList();
};

class GameMessageListDestructorShim
{
public:
	void destroy();
};

GameMessageList::~GameMessageList()
{
	((GameMessageListDestructorShim *)this)->destroy();
}
