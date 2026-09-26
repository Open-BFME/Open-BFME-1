// cl: /DNDEBUG /MD
// Retail 0x0021D4A0: ContestableContain state helper.
//
// ContestableContain's constructor at 0x0021BEE0 initializes the list and tree
// members used below.  The method name is not recovered, so the address keeps
// the source identity explicit while the surrounding layout supplies the
// class identity.

class Rva0021D4A0
{
public:
	int check();

private:
	unsigned char m_pad000[0x28];
};

void j_0001b8c4();
void j_0002f919();
void j_000480cc();

class Rva0021D4A0Secondary
{
public:
#define RVA_SLOT(n) virtual void slot##n();
	RVA_SLOT(00) RVA_SLOT(01) RVA_SLOT(02) RVA_SLOT(03) RVA_SLOT(04)
	RVA_SLOT(05) RVA_SLOT(06) RVA_SLOT(07) RVA_SLOT(08) RVA_SLOT(09)
	RVA_SLOT(10) RVA_SLOT(11) RVA_SLOT(12) RVA_SLOT(13) RVA_SLOT(14)
	RVA_SLOT(15) RVA_SLOT(16) RVA_SLOT(17) RVA_SLOT(18) RVA_SLOT(19)
	RVA_SLOT(20) RVA_SLOT(21) RVA_SLOT(22) RVA_SLOT(23) RVA_SLOT(24)
	RVA_SLOT(25) RVA_SLOT(26) RVA_SLOT(27) RVA_SLOT(28) RVA_SLOT(29)
	RVA_SLOT(30) RVA_SLOT(31) RVA_SLOT(32) RVA_SLOT(33) RVA_SLOT(34)
	RVA_SLOT(35) RVA_SLOT(36) RVA_SLOT(37) RVA_SLOT(38) RVA_SLOT(39)
	RVA_SLOT(40) RVA_SLOT(41) RVA_SLOT(42) RVA_SLOT(43) RVA_SLOT(44)
	RVA_SLOT(45) RVA_SLOT(46) RVA_SLOT(47) RVA_SLOT(48)
	virtual bool predicate();
#undef RVA_SLOT
};

int Rva0021D4A0::check()
{
	void *result = reinterpret_cast<void *(*)()>(j_0001b8c4)();
	Rva0021D4A0Secondary *secondary = reinterpret_cast<Rva0021D4A0Secondary *>(reinterpret_cast<char *>(this) + 0x10);

	if (!secondary->predicate())
		goto done;

	void *logic = *reinterpret_cast<void **>(0x012F0898);
	if (*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(logic) + 0x3c) >=
		*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(this) + 0x9c4))
	{
		reinterpret_cast<void (__fastcall *)(void *)>(j_0002f919)(reinterpret_cast<char *>(this) - 0x10);
	}

	void *list = *reinterpret_cast<void **>(reinterpret_cast<char *>(this) + 0x9ac);
	if (*reinterpret_cast<void **>(list) != list)
	{
		list = *reinterpret_cast<void **>(reinterpret_cast<char *>(this) + 0x28);
		if (*reinterpret_cast<void **>(list) != list)
			return true;
	}

	reinterpret_cast<void (__fastcall *)(void *)>(j_000480cc)(reinterpret_cast<char *>(this) - 0x10);
done:
	return reinterpret_cast<int>(result);
}
