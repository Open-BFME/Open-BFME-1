struct BfmeSlotState1289
{
	void bfmeSetAxis1289(int axis, float value, int enabled);

	void *m_unused00;
	unsigned int m_flags;
};

class AptValue;
extern AptValue *g_bfmeFallbackDB;

class BfmeSlotDispatcher1281
{
public:
	void bfmeRouteEncoded1281(unsigned int encoded);
	void bfmeFlushSlots1289();
	void applyPosition();

private:
	char m_padding00[0x1238];
	int m_count1238;
	unsigned int *m_entries123c;
	BfmeSlotState1289 *m_state;
	float m_minX;
	float m_minY;
	float m_maxX;
	float m_maxY;
	float m_offsetX;
	float m_offsetY;
	int m_value125c;
	char m_padding1260[4];
	unsigned char m_reset1264;
	char m_padding1265[0x1274 - 0x1265];
	int m_xPos;
	int m_yPos;
};

void BfmeSlotDispatcher1281::bfmeFlushSlots1289()
{
	if ((((unsigned char)~(unsigned char)(m_state->m_flags >> 15)) & 1) == 0) {
		float x = m_xPos - m_offsetX;
		float y = m_yPos - m_offsetY;
		const float unset = -9999.0f;

		if (m_minX != unset && x < m_minX)
			x = m_minX;
		if (m_maxX != unset && x > m_maxX)
			x = m_maxX;
		if (m_minY != unset && y < m_minY)
			y = m_minY;
		if (m_maxY != unset && y > m_maxY)
			y = m_maxY;

		m_state->bfmeSetAxis1289(0, x, 1);
		m_state->bfmeSetAxis1289(1, y, 1);
	}

	for (int i = 0; i < m_count1238; ++i)
		bfmeRouteEncoded1281(m_entries123c[i]);

	if (m_reset1264 == 1) {
		m_value125c = reinterpret_cast<int>(g_bfmeFallbackDB);
		m_reset1264 = 0;
	}
	m_count1238 = 0;
}

void BfmeSlotDispatcher1281::applyPosition()
{
	float x = m_xPos - m_offsetX;
	float y = m_yPos - m_offsetY;
	const float unset = -9999.0f;

	if (m_minX != unset && x < m_minX)
		x = m_minX;
	if (m_maxX != unset && x > m_maxX)
		x = m_maxX;
	if (m_minY != unset && y < m_minY)
		y = m_minY;
	if (m_maxY != unset && y > m_maxY)
		y = m_maxY;

	m_state->bfmeSetAxis1289(0, x, 1);
	m_state->bfmeSetAxis1289(1, y, 1);
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
