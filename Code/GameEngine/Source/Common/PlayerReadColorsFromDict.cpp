// cl: /DNDEBUG /MD /EHsc

typedef int NameKeyType;

class StaticNameKey
{
public:
	NameKeyType key() const;
	operator NameKeyType() const { return key(); }

private:
	mutable NameKeyType m_key;
	const char *m_name;
};

class Dict
{
public:
	int getInt(NameKeyType key, bool *exists) const;
};

extern const StaticNameKey TheKey_playerColor;
extern const StaticNameKey TheKey_playerNightColor;

class Rva000C9330Player
{
public:
	void readColorsFromDict(const Dict *dict);

private:
	unsigned char m_bfmeBeforeColors[0x1c4];
	int m_color;
	int m_nightColor;
};

void Rva000C9330Player::readColorsFromDict(const Dict *dict)
{
	if (dict == 0)
		return;

	bool exists;
	int color = dict->getInt(TheKey_playerColor, &exists);
	if (exists)
	{
		m_color = color | 0xff000000;
		m_nightColor = m_color;
	}

	color = dict->getInt(TheKey_playerNightColor, &exists);
	if (exists)
		m_nightColor = color | 0xff000000;
}
