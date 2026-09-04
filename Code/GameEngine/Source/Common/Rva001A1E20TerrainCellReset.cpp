// cl: /O2

class TerrainLogic
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual int normalizeCell(int value) = 0;
};

extern TerrainLogic *TheTerrainLogic;

class Rva001A1E20CellState
{
public:
	void reset(void);

private:
	char m_prefix[0x20];
	int m_cells[8];
	int m_value40;
	int m_value44;
};

void Rva001A1E20CellState::reset(void)
{
	for (int i = 0; i < 8; ++i)
	{
		int value = m_cells[i];
		if (value == 0x7fffffff)
			value = 0;
		else
			value = TheTerrainLogic->normalizeCell(value);
		m_cells[i] = value;
	}

	int value = m_value44;
	if (value == 0x7fffffff)
		value = 0;
	else
		value = TheTerrainLogic->normalizeCell(value);
	m_value44 = value;

	value = m_value40;
	if (value == 0x7fffffff)
		value = 0;
	else
		value = TheTerrainLogic->normalizeCell(value);
	m_value40 = value;
}
