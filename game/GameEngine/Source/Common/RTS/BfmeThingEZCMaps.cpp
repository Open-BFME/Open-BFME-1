// cl: /O2

class BfmeMapEZC
{
public:
	int *find(void *key);
	int *insert(void *key);
	int *fetch(void *key);
	void drop1(void *key);
	void drop2(void *key);
	void erase(void **pair);

private:
	unsigned char m_bytes[0x14];
};

class BfmeThingEZC
{
public:
	void setMaps(void *key, void *val1, void *val2);
	void eraseMaps(void *key);

private:
	unsigned char m_head[0x1D8];
	BfmeMapEZC m_map0;
	BfmeMapEZC m_map1;
	BfmeMapEZC m_map2;
};

void BfmeThingEZC::setMaps(void *key, void *val1, void *val2)
{
	BfmeMapEZC *map1 = &m_map1;
	int *node = map1->find(key);
	if (!node)
	{
		node = map1->insert(key);
		*node = 0;
	}
	*m_map2.fetch(key) = (int)val2;
	*m_map0.insert(key) = (int)val1;
}

void BfmeThingEZC::eraseMaps(void *key)
{
	BfmeMapEZC *map0 = &m_map0;
	int *node = map0->find(key);
	if (node)
	{
		m_map1.drop1(key);
		m_map2.drop2(key);
		void *pair[2];
		pair[0] = node;
		pair[1] = map0;
		map0->erase(pair);
	}
}
