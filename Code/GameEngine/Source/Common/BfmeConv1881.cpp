extern "C" char g_bfmeNameZO[];
extern "C" char g_bfmeNameItemZO[];

class AsciiString
{
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void writeByte(char value);
	void writeInt(int value);
	void writeAsciiString(const AsciiString &value);
	void closeDataChunk();
};

typedef AsciiString BfmeStringZO;

struct BfmeTreeNodeZO
{
	unsigned char m_color;
	BfmeTreeNodeZO *m_parent;
	BfmeTreeNodeZO *m_left;
	BfmeTreeNodeZO *m_right;
	BfmeStringZO m_value;
};

struct BfmeTreeZO
{
	unsigned char m_pad[8];
	BfmeTreeNodeZO *m_root;
};

namespace _STL
{
struct _Rb_tree_node_base;

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};
}

class BfmeChunkZO
{
public:
	void bfmeOpenZO(char *name, unsigned short version)
	{
		((DataChunkOutput *)this)->openDataChunk(name, version);
	}
	void bfmeWriteByteZO(char value)
	{
		((DataChunkOutput *)this)->writeByte(value);
	}
	void bfmeWriteIntZO(int value)
	{
		((DataChunkOutput *)this)->writeInt(value);
	}
	void bfmeWriteStringZO(const BfmeStringZO &value)
	{
		((DataChunkOutput *)this)->writeAsciiString(value);
	}
	void bfmeCloseZO()
	{
		((DataChunkOutput *)this)->closeDataChunk();
	}
};

class BfmeItemZO
{
public:
	void bfmeWriteZO(BfmeChunkZO *out);

	unsigned char m_bfmeFlag0ZO;
	unsigned char m_bfmeFlag1ZO;
	unsigned char m_bfmeFlag2ZO;
	unsigned char m_bfmePadZO;
	int m_bfmeInt4ZO;
	BfmeTreeZO *m_bfmeTreeZO;
	int m_bfmeIntCZO;
	int m_bfmePad10ZO;
};

void BfmeItemZO::bfmeWriteZO(BfmeChunkZO *out)
{
	out->bfmeOpenZO(g_bfmeNameItemZO, 1);
	out->bfmeWriteByteZO(m_bfmeFlag0ZO != 0);
	out->bfmeWriteByteZO(m_bfmeFlag1ZO != 0);
	out->bfmeWriteByteZO(m_bfmeFlag2ZO != 0);
	out->bfmeWriteIntZO(m_bfmeInt4ZO);
	out->bfmeWriteIntZO(m_bfmeIntCZO);

	BfmeTreeNodeZO *node = m_bfmeTreeZO->m_root;
	while (node != (BfmeTreeNodeZO *)m_bfmeTreeZO)
	{
		out->bfmeWriteStringZO(node->m_value);
		node = (BfmeTreeNodeZO *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)node);
	}

	out->bfmeCloseZO();
}

class BfmeOwnerZO
{
public:
	void bfmeSaveZO(BfmeChunkZO *out);

	BfmeItemZO m_bfmeItemsZO[8];
};

void BfmeOwnerZO::bfmeSaveZO(BfmeChunkZO *out)
{
	out->bfmeOpenZO(g_bfmeNameZO, 0);

	for (int i = 0; i < 8; i++)
		m_bfmeItemsZO[i].bfmeWriteZO(out);

	out->bfmeCloseZO();
}
