// CollisionManager's virtual update forwards to its owned collision data.
// The manager layout is fixed by its exact constructor at RVA 0x009A25B0.

struct Rva009A2FE0Node;

class BfmeThingCGD
{
public:
	void bfmeOneCGD();
	void bfmeTwoCGD();
	void bfmeGoCGD();
	void *m_bfmeFirst;
	unsigned char m_bfmeGap[0xae10 - 4];
	Rva009A2FE0Node *m_buckets[0x493];
	Rva009A2FE0Node *m_active;
	int m_index;
	Rva009A2FE0Node *m_cur;
	unsigned char m_bfmeGap1[0xc06d - 0xc068];
	bool m_bfmeBusy;
};

class CollisionManager
{
public:
	virtual void update();

private:
	char m_beforeData[8];
	BfmeThingCGD *m_data;
};

void CollisionManager::update()
{
	m_data->bfmeGoCGD();
}
