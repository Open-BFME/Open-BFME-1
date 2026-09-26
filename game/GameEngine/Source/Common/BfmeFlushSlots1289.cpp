struct BfmeSlotState1289
{
	void bfmeSetAxis1289(int axis, float value, int enabled);

	void *m_unused00;
	unsigned int m_flags;
};

extern int g_bfmeFallbackDB;

class BfmeSlotDispatcher1281
{
public:
	void bfmeRouteEncoded1281(unsigned int encoded);
	void bfmeFlushSlots1289();
	void bfmeApplyPosition1291();

private:
	char m_padding00[0x1238];
	int m_count1238;
	unsigned int *m_entries123c;
	BfmeSlotState1289 *m_state1240;
	float m_minX1244;
	float m_minY1248;
	float m_maxX124c;
	float m_maxY1250;
	float m_offsetX1254;
	float m_offsetY1258;
	int m_value125c;
	char m_padding1260[4];
	unsigned char m_reset1264;
	char m_padding1265[0x1274 - 0x1265];
	int m_positionX1274;
	int m_positionY1278;
};

void BfmeSlotDispatcher1281::bfmeFlushSlots1289()
{
	if ((((unsigned char)~(unsigned char)(m_state1240->m_flags >> 15)) & 1) == 0) {
		float x = m_positionX1274 - m_offsetX1254;
		float y = m_positionY1278 - m_offsetY1258;
		const float unset = -9999.0f;

		if (m_minX1244 != unset && x < m_minX1244)
			x = m_minX1244;
		if (m_maxX124c != unset && x > m_maxX124c)
			x = m_maxX124c;
		if (m_minY1248 != unset && y < m_minY1248)
			y = m_minY1248;
		if (m_maxY1250 != unset && y > m_maxY1250)
			y = m_maxY1250;

		m_state1240->bfmeSetAxis1289(0, x, 1);
		m_state1240->bfmeSetAxis1289(1, y, 1);
	}

	for (int i = 0; i < m_count1238; ++i)
		bfmeRouteEncoded1281(m_entries123c[i]);

	if (m_reset1264 == 1) {
		m_value125c = g_bfmeFallbackDB;
		m_reset1264 = 0;
	}
	m_count1238 = 0;
}

void BfmeSlotDispatcher1281::bfmeApplyPosition1291()
{
	float x = m_positionX1274 - m_offsetX1254;
	float y = m_positionY1278 - m_offsetY1258;
	const float unset = -9999.0f;

	if (m_minX1244 != unset && x < m_minX1244)
		x = m_minX1244;
	if (m_maxX124c != unset && x > m_maxX124c)
		x = m_maxX124c;
	if (m_minY1248 != unset && y < m_minY1248)
		y = m_minY1248;
	if (m_maxY1250 != unset && y > m_maxY1250)
		y = m_maxY1250;

	m_state1240->bfmeSetAxis1289(0, x, 1);
	m_state1240->bfmeSetAxis1289(1, y, 1);
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
