// ?bfmeProcess1279@BfmeWrapper1279@@QAEXPAX@Z
//
// Processing for the node returned by the BfmeQuery1279 forwarding path.

class BfmeQuery1279
{
public:
	void bfmeQuery1279(void *value, int zero, void **other, void **result);
};

struct BfmeInput1279
{
	void *m_value;
};

class BfmeWrapper1279
{
public:
	void bfmeProcess1279(void *value);
	void bfmeForwardValue1279(void *value);
	void bfmeForward1279(BfmeInput1279 *input);

private:
	BfmeQuery1279 *m_query;
};

struct BfmeKey1279
{
	void *m_vtable;
};

class BfmeLookup1279;

class BfmeProvider1279
{
public:
	virtual void reserved0() = 0;
	virtual void reserved1() = 0;
	virtual void reserved2() = 0;
	virtual void reserved3() = 0;
	virtual void reserved4() = 0;
	virtual void reserved5() = 0;
	virtual BfmeLookup1279 *bfmeGetLookup1279() = 0;
};

class BfmeNode1279
{
public:
	void bfmeFinish1279();
	void *m_vtable;
	unsigned int m_flags;
	int m_bfme08;
	BfmeKey1279 m_key;
	char m_padding10[0x4c - 0x10];
	BfmeProvider1279 *m_provider;
};

class BfmeLookup1279
{
public:
	BfmeNode1279 *bfmeLookup1279(BfmeKey1279 &key);
	void bfmeErase1279(BfmeKey1279 &key);
};

extern char g_bfmeSpecialKeyVtable1279;

void BfmeWrapper1279::bfmeProcess1279(void *value)
{
	BfmeNode1279 *node = (BfmeNode1279 *)value;
	if (node) {
		if (!((unsigned char)(~(node->m_flags >> 15)) & 1)) {
			BfmeProvider1279 *provider = node->m_provider;
			if (provider) {
				BfmeLookup1279 *lookup = provider->bfmeGetLookup1279();
				BfmeKey1279 &key = node->m_key;
				if (key.m_vtable != &g_bfmeSpecialKeyVtable1279 && lookup) {
					if (lookup->bfmeLookup1279(key) == node)
						lookup->bfmeErase1279(key);
				}
			}
			node->bfmeFinish1279();
		}
	}
}
