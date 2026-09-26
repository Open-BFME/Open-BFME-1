// ?Rva00191110WritePolygonTriggersFiltered@@YAXPAVRva00191110Trigger@@AAVDataChunkOutput@@PAVRva00191110Filter@@@Z
// partial score=0.30 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// address-derived; no caller or emitter names this body

class AsciiString
{
public:
	void releaseBuffer(void);
	~AsciiString(void) { releaseBuffer(); }

private:
	void *m_data;
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void closeDataChunk();
	void writeAsciiString(const AsciiString &string);
	void writeByte(char value);
	void writeInt(int value);
	void writeReal(float value);
};

class BfmeOtherDOA;

class BfmeThingDOA
{
public:
	BfmeOtherDOA *bfmeGoDOA(BfmeOtherDOA *other, int index);
};

class Rva00191110Filter
{
public:
	virtual ~Rva00191110Filter() {}
	virtual bool bfmeTest(void *node) = 0;
};

struct Rva00191110Point
{
	int x;
	int y;
	int z;
};

class Rva00191110Trigger
{
public:
	Rva00191110Trigger *getNext() const { return m_next; }

private:
	char m_head[4];
	Rva00191110Trigger *m_next;
	AsciiString m_name;
	int m_id;
	Rva00191110Point *m_points;
	int m_numPoints;
	char m_gap18[0x1A];
	char m_flag32;
	char m_gap33;
	AsciiString m_layerName;
	char m_gap38[8];
	char m_flag40;
	char m_gap41[3];
	int m_field44;
	char m_itemsGap[0x18];
	char m_flag60;
	char m_gap61[3];
	float m_colorR;
	float m_colorG;
	float m_colorB;
	float m_field70;
	char m_gap74[8];
	float m_field7c;

	friend void Rva00191110WritePolygonTriggersFiltered(
		Rva00191110Trigger *head, DataChunkOutput &output, Rva00191110Filter *filter);
};

void Rva00191110WritePolygonTriggersFiltered(
	Rva00191110Trigger *head, DataChunkOutput &output, Rva00191110Filter *filter)
{
	output.openDataChunk("PolygonTriggers", 5);

	int count = 0;
	for (Rva00191110Trigger *node = head; node; node = node->getNext())
	{
		if (filter->bfmeTest(node))
			count++;
	}
	output.writeInt(count);

	for (Rva00191110Trigger *node = head; node; node = node->getNext())
	{
		if (!filter->bfmeTest(node))
			continue;

		output.writeAsciiString(node->m_name);
		output.writeAsciiString(node->m_layerName);
		output.writeInt(node->m_id);
		output.writeByte(node->m_flag32);
		output.writeByte(node->m_flag40);
		output.writeInt(node->m_field44);

		for (int i = 0; i < 6; i++)
		{
			BfmeOtherDOA *item;
			AsciiString tmp;
			item = reinterpret_cast<BfmeThingDOA *>(node)->bfmeGoDOA(
				reinterpret_cast<BfmeOtherDOA *>(&tmp), i);
			output.writeAsciiString(*reinterpret_cast<AsciiString *>(item));
		}

		output.writeByte(node->m_flag60);

		int r = (int)(node->m_colorR * 255.0);
		int g = (int)(node->m_colorG * 255.0);
		int b = (int)(node->m_colorB * 255.0);
		output.writeInt((r << 16) | (g << 8) | b);

		output.writeReal(node->m_field70);
		output.writeReal(node->m_field70);
		output.writeReal(node->m_field7c);

		output.writeInt(node->m_numPoints);
		for (int j = 0; j < node->m_numPoints; j++)
		{
			int ndx = j;
			if (ndx < 0)
				ndx = 0;
			if (ndx >= node->m_numPoints)
				ndx = node->m_numPoints - 1;
			Rva00191110Point &pt = node->m_points[ndx];
			output.writeInt(pt.x);
			output.writeInt(pt.y);
			output.writeInt(pt.z);
		}
	}

	output.closeDataChunk();
}
