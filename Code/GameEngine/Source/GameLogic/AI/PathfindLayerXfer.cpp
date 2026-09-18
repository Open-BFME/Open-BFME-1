// cl: /O2 /DNDEBUG /MD

typedef int Int;

struct ICoord2D
{
	Int x;
	Int y;
};

class Xfer
{
public:
	class Version
	{
	public:
		unsigned char data[2];
	};

	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual bool IsCRC();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual Xfer &slot09(void *, unsigned int);
	virtual Xfer &xferVersion(Version &);
	virtual Xfer &slot11();
	virtual Xfer &slot12();
	virtual Xfer &slot13();
	virtual Xfer &slot14();
	virtual Xfer &slot15();
	virtual Xfer &slot16();
	virtual Xfer &slot17();
	virtual Xfer &slot18();
	virtual Xfer &xferICoord2D(ICoord2D &);
	virtual Xfer &slot20();
	virtual Xfer &slot21();
	virtual Xfer &slot22();
	virtual Xfer &slot23();
	virtual Xfer &slot24();
	virtual Xfer &slot25();
	virtual Xfer &slot26();
	virtual Xfer &slot27();
	virtual Xfer &slot28();
	virtual Xfer &slot29();
	virtual Xfer &xferInt(Int &);
	virtual Xfer &slot31();
	virtual Xfer &slot32();
	virtual Xfer &slot33();
	virtual Xfer &slot34();
	virtual Xfer &xferBool(bool &);
};

class PathfindCell
{
public:
	void xfer(Xfer *xfer);

	char m_pad[0x10];
};

class PathfindLayer
{
public:
	void xfer(Xfer *xfer);

	void *m_blockOfMapCells;
	PathfindCell **m_layerCells;
	Int m_width;
	Int m_height;
	Int m_xOrigin;
	Int m_yOrigin;
	ICoord2D m_startCell;
	ICoord2D m_endCell;
	Int m_field28;
	Int m_field2c;
	Int m_field30;
	bool m_destroyed;
	char m_pad35[0xb];
	Int m_field40;
};

void PathfindLayer::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 1;
	xfer->xferVersion(version);

	if (m_layerCells != 0)
	{
		Int x = 0;
		if (m_width > 0)
		{
			while (x < m_width)
			{
				Int y = 0;
				if (m_height > 0)
				{
					do
					{
						m_layerCells[x][y].xfer(xfer);
						++y;
					}
					while (y < m_height);
				}
				++x;
			}
		}
	}

	xfer->xferInt(m_width);
	xfer->xferInt(m_height);
	xfer->xferInt(m_xOrigin);
	xfer->xferInt(m_yOrigin);
	xfer->xferICoord2D(m_startCell);
	xfer->xferICoord2D(m_endCell);
	Int field28 = m_field28;
	xfer->xferInt(field28);
	xfer->xferInt(m_field2c);
	xfer->xferInt(m_field30);
	xfer->xferBool(m_destroyed);
	xfer->xferInt(m_field40);
}
