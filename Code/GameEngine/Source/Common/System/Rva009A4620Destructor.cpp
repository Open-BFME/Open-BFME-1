// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0x009A4620, 127 bytes. Address-derived owner; the list nodes
// have the existing CollisionData destructor identity at 0x009A2390.
// The two embedded table clear bodies (0x009A3200 and 0x009A4290)
// only unlink nodes and call scalar operator delete at 0x00881EB0.
// Their non-throwing release contract lets normal member destruction
// reproduce the retail EH state without artificial state manipulation.

class Rva009A36F0Param;

class Rva009A36F0Owner
{
public:
	void apply(Rva009A36F0Param *param);
};

class Rva009A4620Param
{
public:
	unsigned char m_pad00[4];
	void *m_child;
};

class Rva009A45A0CollisionData
{
public:
	~Rva009A45A0CollisionData();
};

class BfmeTableVMN
{
public:
	void bfmeClearVMN() throw();
};

class BfmeThingVDB
{
public:
	void bfmeClearVDB() throw();
};

class Rva009A4620VMNView
{
public:
	~Rva009A4620VMNView()
	{
		((BfmeTableVMN *)this)->bfmeClearVMN();
	}

private:
	unsigned char m_storage[0xADF8];
};

class Rva009A4620VDBView
{
public:
	~Rva009A4620VDBView()
	{
		((BfmeThingVDB *)this)->bfmeClearVDB();
	}

private:
	unsigned char m_storage[0x1258];
};

class Rva009A4620CollisionData
{
public:
	~Rva009A4620CollisionData();

	Rva009A45A0CollisionData *m_root;
	unsigned char m_pad04[0x14];
	Rva009A4620VMNView m_vmn;
	Rva009A4620VDBView m_vdb;
};

Rva009A4620CollisionData::~Rva009A4620CollisionData()
{
	while (m_root != 0)
	{
		Rva009A4620Param *param = (Rva009A4620Param *)m_root;
		if (param->m_child != 0)
			((Rva009A36F0Owner *)this)->apply((Rva009A36F0Param *)param->m_child);

		Rva009A45A0CollisionData *root = m_root;
		if (root != 0)
			delete root;
	}
}
