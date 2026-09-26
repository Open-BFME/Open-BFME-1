// Open-BFME5 conversions.

struct BfmeConnUMA
{
	void *m_bfmeSock;
};

int bfmeInChannelUMA(BfmeConnUMA *c, const char *name);
int bfmeGetUsersUMA(BfmeConnUMA *c, const char *name);

int bfmeGoUMA(BfmeConnUMA *c, const char *name)
{
	if (!c->m_bfmeSock)
		return -1;
	if (name && *name && bfmeInChannelUMA(c, name))
		return bfmeGetUsersUMA(c, name);
	return -1;
}
