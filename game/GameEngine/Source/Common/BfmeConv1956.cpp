class BfmeThingERL;

class BfmeGlobalERL
{
public:
	virtual void bfmeSlot00ERL();
	virtual void bfmeSlot01ERL();
	virtual void bfmeSlot02ERL();
	virtual void bfmeSlot03ERL();
	virtual void bfmeSlot04ERL();
	virtual void bfmeSlot05ERL();
	virtual void bfmeSlot06ERL();
	virtual void bfmeSlot07ERL();
	virtual void bfmeSlot08ERL();
	virtual void bfmeSlot09ERL();
	virtual void bfmeSlot10ERL();
	virtual void bfmeSlot11ERL();
	virtual void bfmeSlot12ERL();
	virtual void bfmeSlot13ERL();
	virtual void bfmeSlot14ERL();
	virtual void bfmeSlot15ERL();
	virtual void bfmeSlot16ERL();
	virtual void bfmeSlot17ERL();
	virtual void bfmeSlot18ERL();
	virtual void bfmeSlot19ERL();
	virtual void bfmeSlot20ERL();
	virtual void bfmeSlot21ERL();
	virtual void bfmeSlot22ERL();
	virtual void bfmeSlot23ERL();
	virtual void bfmeSlot24ERL();
	virtual void bfmeSlot25ERL();
	virtual BfmeThingERL *bfmeSlot26ERL(void *handle);
};

extern BfmeGlobalERL *g_bfmeGlobalERL;

class BfmeIfaceERL
{
public:
	virtual void bfmeIface00ERL();
	virtual void bfmeIface01ERL();
	virtual void bfmeIface02ERL();
	virtual void bfmeIface03ERL();
	virtual void bfmeIface04ERL();
	virtual void bfmeIface05ERL();
	virtual char bfmeIface06ERL();
};

class BfmeModERL;

class BfmeThingERL
{
public:
	BfmeModERL *bfmeFindERL(int key);
};

class BfmeKeyGenERL
{
public:
	int bfmeNameToKeyERL(const char *name);
};

extern BfmeKeyGenERL *g_bfmeKeyGenERL;

char __stdcall bfmeCheckERL(void *handle)
{
	BfmeThingERL *thing = g_bfmeGlobalERL->bfmeSlot26ERL(handle);

	if (thing == 0)
		return 0;

	static int s_bfmeKeyERL =
		g_bfmeKeyGenERL->bfmeNameToKeyERL("GateOpenAndCloseBehavior");

	BfmeModERL *mod = thing->bfmeFindERL(s_bfmeKeyERL);

	if (mod == 0)
		return 0;

	BfmeIfaceERL *iface = (BfmeIfaceERL *)((char *)mod - 4);

	if (iface == 0)
		return 0;

	return iface->bfmeIface06ERL();
}
