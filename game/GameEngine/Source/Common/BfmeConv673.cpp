struct BfmeThingDBE
{
	void *m_bfmeX;
};

extern "C" int ciGetUserBasicInfoA(void *, const char *, const char **, const char **);

extern "C" int chatGetBasicUserInfoNoWaitA(void *chat, const char *nick,
	const char **user, const char **address)
{
	BfmeThingDBE *a = (BfmeThingDBE *)chat;
	if (a == 0)
		return 0;
	if (a->m_bfmeX == 0)
		return 0;
	return ciGetUserBasicInfoA(a, nick, user, address);
}
