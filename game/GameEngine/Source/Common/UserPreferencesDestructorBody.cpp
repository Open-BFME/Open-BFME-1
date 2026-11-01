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

// The map base around the tree: its implicit destructor is inlined on the
// normal path (the tree destructor call through ILT 0x0000B992) and emitted
// out of line for the unwind funclet 0x00BF75F0, which retail reaches through
// ILT 0x000301D9 -> the 5-byte jmp body at 0x00080800.
class UserPreferencesMap00080800
{
private:
	UserPreferencesMap m_tree;
};
class UserPreferencesBodyShim : public UserPreferencesMap00080800
{
public:
	virtual ~UserPreferencesBodyShim();

private:
	UserPreferencesFilename m_filename;
};

UserPreferencesBodyShim::~UserPreferencesBodyShim()
{
}
