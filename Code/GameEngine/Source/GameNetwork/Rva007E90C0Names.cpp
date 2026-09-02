// cl: /GS
// 0x007E90C0 / 0x007E91D0 / 0x007E9240 / 0x007E9130 / 0x007E8F20:
// sprintf indexed keys then getString/getInt on a FESL message.

class Rva007E8810Message
{
public:
	bool getString(const char *key, char *dest, int destSize);
	int getInt(const char *key, int defaultValue);
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

class Rva007E9130Errors
{
public:
	bool get(char *fieldError, int *fieldName, int destSize);

private:
	Rva007E8810Message *m_msg;
	int m_count;
};

bool Rva007E9130Errors::get(char *fieldError, int *fieldName, int destSize)
{
	char key[0x40];
	sprintf(key, "errorContainer.%d.fieldName", m_count);
	if (m_msg->getString(key, fieldError, destSize))
	{
		sprintf(key, "errorContainer.%d.fieldError", m_count);
		*fieldName = m_msg->getInt(key, -1);
		m_count++;
		return true;
	}
	m_count = 0;
	return false;
}

class Rva007E8F20Country
{
public:
	bool load(Rva007E8810Message *msg, int index);

	char m_description[0x80];
	char m_isoCode[4];
	int m_registrationAgeLimit;
	int m_parentalControlAgeLimit;
};

bool Rva007E8F20Country::load(Rva007E8810Message *msg, int index)
{
	char key[0x40] = {0};
	sprintf(key, "countryList.%d.description", index);
	if (!msg->getString(key, m_description, 0x80))
		return false;
	sprintf(key, "countryList.%d.ISOCode", index);
	msg->getString(key, m_isoCode, 4);
	sprintf(key, "countryList.%d.parentalControlAgeLimit", index);
	m_registrationAgeLimit = msg->getInt(key, 18);
	sprintf(key, "countryList.%d.registrationAgeLimit", index);
	m_parentalControlAgeLimit = msg->getInt(key, 13);
	return true;
}
