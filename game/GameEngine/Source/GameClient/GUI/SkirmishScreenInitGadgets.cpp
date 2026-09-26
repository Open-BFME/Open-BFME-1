// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc
//
// Retail 0x0057D110: AptSkirmish::InitGadgets.

template <typename T> class StringBase
{
friend class UnicodeString;

private:
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	UnicodeString &operator=( const UnicodeString &other );
};

class Rva005672C0Map
{
public:
	virtual void slot0();
	Rva005672C0Map &operator=( const Rva005672C0Map &other );
	void *m_head;
};

class Rva005673A0Vec
{
public:
	Rva005673A0Vec &operator=( const Rva005673A0Vec &other );

private:
	void *m_head;
};

class MpGameSetup
{
public:
	void GadgetInit();
};

class Rva0009F090WideList
{
public:
	UnicodeString first() const;
	int findNoCase( UnicodeString value );
};

class Gen0009FBB0Owner
{
public:
	void Rva0009FBB0( UnicodeString value );
};

class SkirmishPreferences
{
public:
	virtual ~SkirmishPreferences();
	virtual void slot1();
	virtual bool load();
	virtual bool write();
	UnicodeString getUserName();
	SkirmishPreferences();

	Rva005672C0Map m_map;
	char m_unmodelled_0c[ 4 ];
	UnicodeString m_userName;
	Rva005673A0Vec m_userNames;
};

struct SkirmishBattleHonorsValues
{
	int m_value[ 10 ];
};

class SkirmishBattleHonors
{
public:
	virtual ~SkirmishBattleHonors();
	virtual void slot1();
	virtual bool load();
	virtual bool write();
	SkirmishBattleHonors( UnicodeString userName );

	Rva005672C0Map m_map;
	char m_unmodelled_0c[ 4 ];
	UnicodeString m_userName;
	SkirmishBattleHonorsValues m_values;
};

class BfmeAptScreenSkirmish
{
public:
	void initGadgets();
	void _bfme_updateProfileDisplay();

private:
	char m_unmodelled_00[ 0x3ac ];
	SkirmishPreferences m_preferences;
	SkirmishBattleHonors m_honors;
	int m_mode;
	char m_unmodelled_404[ 4 ];
	bool m_profileOpen;
};

// ?initGadgets@BfmeAptScreenSkirmish@@QAEXXZ
void BfmeAptScreenSkirmish::initGadgets()
{
	( (MpGameSetup *)( (char *)this + 0x25c ) )->GadgetInit();

	if( m_mode == 9 )
		m_mode = 7;

	if( !m_profileOpen )
	{
		SkirmishPreferences preferences;
		Rva005672C0Map &currentMap = m_preferences.m_map;
		currentMap = preferences.m_map;
		UnicodeString &currentName = m_preferences.m_userName;
		currentName = preferences.m_userName;
		m_preferences.m_userNames = preferences.m_userNames;
	}

	{
		if( ( (Rva0009F090WideList *)&m_preferences )->findNoCase( m_preferences.getUserName() ) < 0 )
		{
			( (Gen0009FBB0Owner *)&m_preferences )->Rva0009FBB0( ( (Rva0009F090WideList *)&m_preferences )->first() );
			m_preferences.write();
		}
	}

	if( !m_profileOpen )
	{
		SkirmishBattleHonors *currentHonors = &m_honors;
		SkirmishBattleHonors honors( m_preferences.getUserName() );
		Rva005672C0Map &currentMap = currentHonors->m_map;
		currentMap = honors.m_map;
		UnicodeString &currentName = currentHonors->m_userName;
		currentName = honors.m_userName;
		currentHonors->m_values = honors.m_values;
		_bfme_updateProfileDisplay();
	}

	m_profileOpen = false;
}
