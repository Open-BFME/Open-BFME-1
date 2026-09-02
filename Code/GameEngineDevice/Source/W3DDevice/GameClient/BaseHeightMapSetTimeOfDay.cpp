// ?setTimeOfDay@BaseHeightMapRenderObjClass@@QAEXW4TimeOfDay@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ reconstruction of BFME terrain relighting.

enum TimeOfDay { TIME_OF_DAY_FIRST = 0 };

class W3DRoadBuffer
{
public:
	void updateLighting(void);
};

class W3DTreeBuffer
{
public:
	char m_pad[0x2a7cb4];
	bool m_needUpdate;
};

class W3DPropBuffer
{
public:
	char m_pad[0x1e1ccc];
	bool m_needUpdate;
};

class BaseHeightMapRenderObjClass
{
public:
	void setTimeOfDay(TimeOfDay tod);
private:
	char m_pad0[0xdc];
	int m_curNumScorchVertices;
	int m_curNumScorchIndices;
	char m_pad1[0x2fc8 - 0xe4];
	int m_scorchesInBuffer;
	char m_pad2[0x3009 - 0x2fcc];
	bool m_needFullUpdate;
	char m_pad3[0x3094 - 0x300a];
	W3DTreeBuffer *m_treeBuffer;
	W3DPropBuffer *m_propBuffer;
	char m_pad4[0x30ac - 0x309c];
	W3DRoadBuffer *m_roadBuffer;
};

void BaseHeightMapRenderObjClass::setTimeOfDay(TimeOfDay)
{
	m_needFullUpdate = true;
	m_scorchesInBuffer = 0;
	m_curNumScorchVertices = 0;
	m_curNumScorchIndices = 0;
	m_roadBuffer->updateLighting();
	m_treeBuffer->m_needUpdate = true;
	m_propBuffer->m_needUpdate = true;
}
