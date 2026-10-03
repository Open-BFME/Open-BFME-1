// ?d_00bf75f0@@YAXXZ
// partial score=0.0 date=2026-10-02
// cl: /DNDEBUG /MD /EHsc

class UserPreferencesMap
{
public:
	~UserPreferencesMap();

private:
	unsigned int m_tree[ 3 ];
};

class UserPreferencesFilename
{
public:
	~UserPreferencesFilename();

private:
	void *m_data;
};

class UserPreferencesBodyShim : public UserPreferencesMap
{
public:
	virtual ~UserPreferencesBodyShim();

private:
	UserPreferencesFilename m_filename;
};

UserPreferencesBodyShim::~UserPreferencesBodyShim()
{
}
