// ??0UserPreferences@@QAE@ABV0@@Z
// partial score=0.96 date=2026-09-02
// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc
//
// Retail 0x0057D2D0: compiler-shaped UserPreferences copy constructor.

class PreferenceTreeShim
{
public:
	PreferenceTreeShim( const PreferenceTreeShim &other );
	~PreferenceTreeShim();

	private:
	unsigned int m_tree[ 3 ];
};

class PreferenceMapShim
{
public:
	PreferenceMapShim( const PreferenceMapShim &other ) : m_tree( other.m_tree ) {}
	~PreferenceMapShim() {}

	private:
	PreferenceTreeShim m_tree;
};

class UnicodeStringShim
{
public:
	UnicodeStringShim( const UnicodeStringShim &other );
	~UnicodeStringShim();

	private:
	void *m_data;
};

class UserPreferences : public PreferenceMapShim
{
public:
	UserPreferences( const UserPreferences &other );
	virtual ~UserPreferences();

private:
	UnicodeStringShim m_filename;
};

UserPreferences::UserPreferences( const UserPreferences &other ) :
	PreferenceMapShim( other ),
	m_filename( other.m_filename )
{
}
