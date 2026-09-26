// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ??1UserPreferences@@UAE@XZ: game/GameEngine/Source/Common/UserPreferences.cpp

class __declspec(novtable) UserPreferences
{
public:
	virtual ~UserPreferences();
};

class UserPreferencesDestructorShim
{
public:
	void destroy();
};

UserPreferences::~UserPreferences()
{
	((UserPreferencesDestructorShim *)this)->destroy();
}
