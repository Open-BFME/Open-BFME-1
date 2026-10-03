// Open-BFME5 conversions.

struct BfmeConnUMA
{
	void *m_bfmeSock;
};

extern "C" int ciInChannel(void *chat, const char *name);
extern "C" int ciGetChannelNumUsers(void *chat, const char *name);

int bfmeGoUMA(BfmeConnUMA *c, const char *name)
{
	if (!c->m_bfmeSock)
		return -1;
	if (name && *name && ciInChannel(c, name))
		return ciGetChannelNumUsers(c, name);
	return -1;
}
