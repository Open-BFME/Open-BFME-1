// cl: /O2 /Ob2 /G6
// BfmeCellGrid::xfer, retail 0x001B1C90 (carved boundary, 530 bytes, ret+int3).
// ILT 0x000499A9 carries the ?xfer@BfmeCellGrid@@QAE_NPAVXfer@@@Z pin and the
// matched VictorySystem::xfer (0x001E05F0) calls it there and ORs the Bool result.
// Slot names follow that caller's Xfer shim; the grid and 0x88-byte cell layout
// follow the landed BfmeCellGrid family. Loading a grid whose dimensions differ
// reads the saved cells into cell 0 and reports the mismatch to the caller.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned char UnsignedByte;

struct XferVersionFields
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

union XferVersion
{
	XferVersionFields m_fields;
	UnsignedInt m_value;
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual void slot03();
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *data, UnsignedInt size);
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(void *snapshot);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(void *value);
	virtual void xferReal(Real *value);
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
};

class BfmeCell
{
public:
	Real m_first[16];
	Real m_second[16];
	UnsignedInt m_firstMask;
	UnsignedInt m_secondMask;
};

class BfmeCellGrid
{
public:
	Bool xfer(Xfer *xfer);
	Int bfmeEvaluateCells() const;

private:
	Int m_width;
	Int m_height;
	UnsignedInt m_cellCount;
	Real m_cellSize;
	Real m_offset;
	BfmeCell *m_cells;
	UnsignedInt *m_cellValues;
};

Bool BfmeCellGrid::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_fields.m_version = 1;
	version.m_fields.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt cellCount = m_cellCount;
	UnsignedInt cellIndex;
	Bool mismatch = false;
	if (xfer->IsLoading())
	{
		Int width = m_width;
		Int height = m_height;
		Real cellSize = m_cellSize;
		Real offset = m_offset;

		xfer->xferUnsignedInt(reinterpret_cast<UnsignedInt *>(&width));
		xfer->xferUnsignedInt(reinterpret_cast<UnsignedInt *>(&height));
		xfer->xferUnsignedInt(&cellCount);
		xfer->xferReal(&cellSize);
		xfer->xferReal(&offset);

		if (m_width != width || m_height != height ||
			m_cellCount != cellCount || m_cellSize != cellSize ||
			m_offset != offset)
		{
			mismatch = true;
		}
	}
	else
	{
		xfer->xferUnsignedInt(reinterpret_cast<UnsignedInt *>(&m_width));
		xfer->xferUnsignedInt(reinterpret_cast<UnsignedInt *>(&m_height));
		xfer->xferUnsignedInt(&m_cellCount);
		xfer->xferReal(&m_cellSize);
		xfer->xferReal(&m_offset);
	}

	if (mismatch)
	{
		for (cellIndex = 0; cellIndex < cellCount; ++cellIndex)
		{
			for (Int playerIndex = 0; playerIndex < 16; ++playerIndex)
			{
				xfer->xferReal(&m_cells[0].m_first[0]);
				xfer->xferReal(&m_cells[0].m_second[0]);
			}
			xfer->xferUnsignedInt(&m_cells[0].m_firstMask);
			xfer->xferUnsignedInt(&m_cells[0].m_secondMask);
		}
	}
	else
	{
		for (cellIndex = 0; cellIndex < m_cellCount; ++cellIndex)
		{
			for (Int playerIndex = 0; playerIndex < 16; ++playerIndex)
			{
				xfer->xferReal(&m_cells[cellIndex].m_first[playerIndex]);
				xfer->xferReal(&m_cells[cellIndex].m_second[playerIndex]);
			}
			xfer->xferUnsignedInt(&m_cells[cellIndex].m_firstMask);
			xfer->xferUnsignedInt(&m_cells[cellIndex].m_secondMask);
		}

		if (xfer->IsLoading())
			bfmeEvaluateCells();
	}
	return mismatch;
}
