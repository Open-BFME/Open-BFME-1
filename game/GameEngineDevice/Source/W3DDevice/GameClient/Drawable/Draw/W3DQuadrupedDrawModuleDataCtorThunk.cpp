// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: W3DQuadrupedDrawModuleData constructor.

class W3DQuadrupedElement
{
public:
	W3DQuadrupedElement();
	~W3DQuadrupedElement();

private:
	unsigned int m_value;
};

class W3DQuadrupedDrawModuleDataBase
{
public:
	W3DQuadrupedDrawModuleDataBase();
	virtual ~W3DQuadrupedDrawModuleDataBase();

private:
	unsigned char m_pad[0x158];
};

class W3DQuadrupedDrawModuleData : public W3DQuadrupedDrawModuleDataBase
{
public:
	W3DQuadrupedDrawModuleData();
	virtual ~W3DQuadrupedDrawModuleData();

private:
	W3DQuadrupedElement m_elements[4];
};

// ??0W3DQuadrupedDrawModuleData@@QAE@XZ
W3DQuadrupedDrawModuleData::W3DQuadrupedDrawModuleData()
{
}
