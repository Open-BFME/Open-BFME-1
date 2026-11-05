// ?Rva00191110WritePolygonTriggersFiltered@@YAXPAVRva00191110Trigger@@AAVDataChunkOutput@@PAVRva00191110Filter@@@Z
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Filtered version-5 polygon writer; owner identities remain address-derived.

#include "ascii_string.h"

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

class Rva00190560
{
public:
	AsciiString rva00190560(int index);
};

class Rva00191110Filter
{
public:
	virtual ~Rva00191110Filter();
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
	// ?getNext@Rva00191110Trigger@@QBEPAV1@XZ absent-from-retail
	Rva00191110Trigger *getNext() const { return m_next; }
	// ?getField44@Rva00191110Trigger@@QBEHXZ absent-from-retail
	int getField44() const { return m_field44; }
	// ?getID@Rva00191110Trigger@@QBEHXZ absent-from-retail
	int getID() const { return m_id; }
	// ?getFlag32@Rva00191110Trigger@@QBE_NXZ absent-from-retail
	bool getFlag32() const { return m_flag32; }
	// ?getFlag40@Rva00191110Trigger@@QBE_NXZ absent-from-retail
	bool getFlag40() const { return m_flag40; }

private:
	char m_head[4];
	Rva00191110Trigger *m_next;
	AsciiString m_name;
	int m_id;
	Rva00191110Point *m_points;
	int m_numPoints;
	char m_gap18[0x1A];
	bool m_flag32;
	char m_gap33;
	AsciiString m_layerName;
	char m_gap38[8];
	bool m_flag40;
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

// ?Rva00191110WritePolygonTriggersFiltered@@YAXPAVRva00191110Trigger@@AAVDataChunkOutput@@PAVRva00191110Filter@@@Z
void Rva00191110WritePolygonTriggersFiltered(Rva00191110Trigger *head, DataChunkOutput &output, Rva00191110Filter *filter)
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
		output.writeInt(node->getID());
		output.writeByte(node->getFlag32());
		output.writeByte(node->getFlag40());
		output.writeInt(node->getField44());

		for (int i = 0; i < 6; i++)
		{
			output.writeAsciiString(reinterpret_cast<Rva00190560 *>(node)->rva00190560(i));
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
			Rva00191110Point pt = node->m_points[ndx];
			output.writeInt(pt.x);
			output.writeInt(pt.y);
			output.writeInt(pt.z);
		}
	}

	output.closeDataChunk();
}
