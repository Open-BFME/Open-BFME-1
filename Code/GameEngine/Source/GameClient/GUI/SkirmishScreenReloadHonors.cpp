// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc
//
// Retail 0x0057D950: rebuild the skirmish-honors snapshot after the
// preferences username changes.  The member offsets are the retail
// BfmeAptScreenSkirmish layout.

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
	void *m_head;
	Rva005672C0Map &operator=( const Rva005672C0Map &other );
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

class SkirmishPreferences
{
public:
	virtual ~SkirmishPreferences();
	virtual void slot1();
	virtual bool load();
	virtual bool write();
	UnicodeString getUserName();

private:
	char m_unmodelled[ 0x14 ];
};

class SkirmishScreenState
{
public:
	virtual void slot0();
	virtual void reset();

private:
	char m_unmodelled[ 0x130 ];
};

class BfmeAptScreenSkirmish
{
public:
	void reloadHonors();

private:
	char m_unmodelled_25c[ 0x25c ];
	SkirmishScreenState m_state;
	char m_unmodelled_390[ 0x1c ];
	SkirmishPreferences m_preferences;
	SkirmishBattleHonors m_honors;
	int m_mode;
	char m_unmodelled_404[ 0x20 ];
};

// ?reloadHonors@BfmeAptScreenSkirmish@@QAEXXZ
void BfmeAptScreenSkirmish::reloadHonors()
{
	SkirmishBattleHonors *currentHonors = &m_honors;
	currentHonors->write();
	{
		SkirmishBattleHonors honors( m_preferences.getUserName() );
		Rva005672C0Map &currentMap = currentHonors->m_map;
		currentMap = honors.m_map;
		UnicodeString &currentName = currentHonors->m_userName;
		currentName = honors.m_userName;
		currentHonors->m_values = honors.m_values;
	}
	m_preferences.write();
	m_state.reset();
	m_mode = 5;
}
