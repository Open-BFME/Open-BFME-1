// cl: /O2
// 0x007E93C0: FESL 'acct' request -- TXN from a global then name/password/
// email/DOB/country/parentalEmail/mail flags.

class Rva007E8810Message
{
public:
	void reset(void);
	void addString(const char *key, const char *value);
	void addInt(const char *key, int value);
	void addBool(const char *key, bool value);

	char m_head[0x1C];
	unsigned int m_category;
};

extern const char *g_Rva0130A4F4Txn;

void __stdcall Rva007E93C0(Rva007E8810Message *msg, const char *name,
	const char *password, const char *email, int dobDay, int dobMonth,
	int dobYear, const char *countryCode, const char *parentalEmail,
	bool eaMailFlag, bool thirdPartyMailFlag)
{
	const char *txn = g_Rva0130A4F4Txn;
	msg->reset();
	msg->m_category = 'acct';
	msg->addString("TXN", txn);
	msg->addString("name", name);
	msg->addString("password", password);
	msg->addString("email", email);
	msg->addInt("DOBDay", dobDay);
	msg->addInt("DOBMonth", dobMonth);
	msg->addInt("DOBYear", dobYear);
	msg->addString("countryCode", countryCode);
	if (parentalEmail && *parentalEmail)
		msg->addString("parentalEmail", parentalEmail);
	msg->addBool("eaMailFlag", eaMailFlag);
	msg->addBool("thirdPartyMailFlag", thirdPartyMailFlag);
}
