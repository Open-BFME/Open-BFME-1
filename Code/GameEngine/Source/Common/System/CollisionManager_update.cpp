// CollisionManager's virtual update forwards to its owned collision data.
// The manager layout is fixed by its exact constructor at RVA 0x009A25B0.

class Rva009A45A0CollisionData
{
public:
	void update();
};

class CollisionManager
{
public:
	virtual void update();

private:
	char m_beforeData[8];
	Rva009A45A0CollisionData *m_data;
};

void CollisionManager::update()
{
	m_data->update();
}
