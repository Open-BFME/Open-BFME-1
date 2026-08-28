// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??1UserPreferences@@UAE@XZ: Code/GameEngine/Source/Common/UserPreferences.cpp

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
