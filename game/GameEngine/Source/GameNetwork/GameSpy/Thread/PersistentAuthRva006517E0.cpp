// cl: /DNDEBUG /MD /EHsc
// BFME PersistentStorageThread callback; BFME login flags are eight bytes earlier than Zero Hour.
struct Rva006517E0PersistentLogin
{
	char m_beforeLoginFlags[0x50];
	bool m_loginOK;
	bool m_doneTryingToLogin;
};

void rva006517E0PersAuthCallback(int localID, int profileID, int authenticated,
	char *error, void *instance)
{
	Rva006517E0PersistentLogin *thread = (Rva006517E0PersistentLogin *)instance;
	if (thread) {
		thread->m_loginOK = authenticated != 0;
		thread->m_doneTryingToLogin = true;
	}
}
