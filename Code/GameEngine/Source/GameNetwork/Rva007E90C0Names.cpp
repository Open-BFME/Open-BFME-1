// cl: /GS
// 0x007E90C0 / 0x007E91D0 / 0x007E9240: sprintf indexed key then getString
// on the message at +0. Success increments the count at +4.

class Rva007E8810Message
{
public:
	bool getString(const char *key, char *dest, int destSize);
};

extern "C" int __cdecl sprintf(char *buf, const char *fmt, ...);

class Rva007E90C0Names
{
public:
	bool get(char *dest, int destSize);

private:
	Rva007E8810Message *m_msg;
	int m_count;
};

bool Rva007E90C0Names::get(char *dest, int destSize)
{
	char key[0x40];
	sprintf(key, "names.%d", m_count);
	if (!m_msg->getString(key, dest, destSize))
		return false;
	m_count++;
	return true;
}

class Rva007E91D0Names
{
public:
	bool get(char *dest, int destSize);

private:
	Rva007E8810Message *m_msg;
	int m_count;
};

bool Rva007E91D0Names::get(char *dest, int destSize)
{
	char key[0x40];
	sprintf(key, "names.%d", m_count);
	if (!m_msg->getString(key, dest, destSize))
		return false;
	m_count++;
	return true;
}

class Rva007E9240SubAccounts
{
public:
	bool get(char *dest, int destSize);

private:
	Rva007E8810Message *m_msg;
	int m_count;
};

bool Rva007E9240SubAccounts::get(char *dest, int destSize)
{
	char key[0x40];
	sprintf(key, "subAccounts.%d", m_count);
	if (!m_msg->getString(key, dest, destSize))
		return false;
	m_count++;
	return true;
}
