// cl: /DNDEBUG /MD /EHsc
// readable body of ?setRawMapHeight@W3DTerrainVisual@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
public:
	int getBorderSizeInline() const { return m_borderSize; }

	unsigned short getHeight(int x, int y) const
	{
		int index = x + y * m_width;
		if (index < 0 || index >= m_cellCount || !m_heights) {
			return 0;
		}
		return m_heights[index];
	}

	void setRawHeight(int x, int y, int height)
	{
		int index = x + y * m_width;
		if (index >= 0 && index < m_cellCount && m_heights) {
			m_heights[index] = static_cast<unsigned short>(height);
		}
	}

private:
	unsigned char m_padding0[0x08];
	int m_width;
	unsigned char m_padding0C[0x04];
	int m_borderSize;
	unsigned char m_padding14[0x0C];
	int m_cellCount;
	unsigned short *m_heights;
};

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
public:
	BFME_VIRTUAL_SLOT(0)   BFME_VIRTUAL_SLOT(1)   BFME_VIRTUAL_SLOT(2)   BFME_VIRTUAL_SLOT(3)
	BFME_VIRTUAL_SLOT(4)   BFME_VIRTUAL_SLOT(5)   BFME_VIRTUAL_SLOT(6)   BFME_VIRTUAL_SLOT(7)
	BFME_VIRTUAL_SLOT(8)   BFME_VIRTUAL_SLOT(9)   BFME_VIRTUAL_SLOT(10)  BFME_VIRTUAL_SLOT(11)
	BFME_VIRTUAL_SLOT(12)  BFME_VIRTUAL_SLOT(13)  BFME_VIRTUAL_SLOT(14)  BFME_VIRTUAL_SLOT(15)
	BFME_VIRTUAL_SLOT(16)  BFME_VIRTUAL_SLOT(17)  BFME_VIRTUAL_SLOT(18)  BFME_VIRTUAL_SLOT(19)
	BFME_VIRTUAL_SLOT(20)  BFME_VIRTUAL_SLOT(21)  BFME_VIRTUAL_SLOT(22)  BFME_VIRTUAL_SLOT(23)
	BFME_VIRTUAL_SLOT(24)  BFME_VIRTUAL_SLOT(25)  BFME_VIRTUAL_SLOT(26)  BFME_VIRTUAL_SLOT(27)
	BFME_VIRTUAL_SLOT(28)  BFME_VIRTUAL_SLOT(29)  BFME_VIRTUAL_SLOT(30)  BFME_VIRTUAL_SLOT(31)
	BFME_VIRTUAL_SLOT(32)  BFME_VIRTUAL_SLOT(33)  BFME_VIRTUAL_SLOT(34)  BFME_VIRTUAL_SLOT(35)
	BFME_VIRTUAL_SLOT(36)  BFME_VIRTUAL_SLOT(37)  BFME_VIRTUAL_SLOT(38)  BFME_VIRTUAL_SLOT(39)
	BFME_VIRTUAL_SLOT(40)  BFME_VIRTUAL_SLOT(41)  BFME_VIRTUAL_SLOT(42)  BFME_VIRTUAL_SLOT(43)
	BFME_VIRTUAL_SLOT(44)  BFME_VIRTUAL_SLOT(45)  BFME_VIRTUAL_SLOT(46)  BFME_VIRTUAL_SLOT(47)
	BFME_VIRTUAL_SLOT(48)  BFME_VIRTUAL_SLOT(49)  BFME_VIRTUAL_SLOT(50)  BFME_VIRTUAL_SLOT(51)
	BFME_VIRTUAL_SLOT(52)  BFME_VIRTUAL_SLOT(53)  BFME_VIRTUAL_SLOT(54)  BFME_VIRTUAL_SLOT(55)
	BFME_VIRTUAL_SLOT(56)  BFME_VIRTUAL_SLOT(57)  BFME_VIRTUAL_SLOT(58)  BFME_VIRTUAL_SLOT(59)
	BFME_VIRTUAL_SLOT(60)  BFME_VIRTUAL_SLOT(61)  BFME_VIRTUAL_SLOT(62)  BFME_VIRTUAL_SLOT(63)
	BFME_VIRTUAL_SLOT(64)  BFME_VIRTUAL_SLOT(65)  BFME_VIRTUAL_SLOT(66)  BFME_VIRTUAL_SLOT(67)
	BFME_VIRTUAL_SLOT(68)  BFME_VIRTUAL_SLOT(69)  BFME_VIRTUAL_SLOT(70)  BFME_VIRTUAL_SLOT(71)
	BFME_VIRTUAL_SLOT(72)  BFME_VIRTUAL_SLOT(73)  BFME_VIRTUAL_SLOT(74)  BFME_VIRTUAL_SLOT(75)
	BFME_VIRTUAL_SLOT(76)  BFME_VIRTUAL_SLOT(77)  BFME_VIRTUAL_SLOT(78)  BFME_VIRTUAL_SLOT(79)
	BFME_VIRTUAL_SLOT(80)  BFME_VIRTUAL_SLOT(81)  BFME_VIRTUAL_SLOT(82)  BFME_VIRTUAL_SLOT(83)
	BFME_VIRTUAL_SLOT(84)  BFME_VIRTUAL_SLOT(85)  BFME_VIRTUAL_SLOT(86)  BFME_VIRTUAL_SLOT(87)
	BFME_VIRTUAL_SLOT(88)  BFME_VIRTUAL_SLOT(89)  BFME_VIRTUAL_SLOT(90)  BFME_VIRTUAL_SLOT(91)
	BFME_VIRTUAL_SLOT(92)  BFME_VIRTUAL_SLOT(93)  BFME_VIRTUAL_SLOT(94)  BFME_VIRTUAL_SLOT(95)
	BFME_VIRTUAL_SLOT(96)  BFME_VIRTUAL_SLOT(97)  BFME_VIRTUAL_SLOT(98)  BFME_VIRTUAL_SLOT(99)
	BFME_VIRTUAL_SLOT(100) BFME_VIRTUAL_SLOT(101) BFME_VIRTUAL_SLOT(102) BFME_VIRTUAL_SLOT(103)
	BFME_VIRTUAL_SLOT(104) BFME_VIRTUAL_SLOT(105) BFME_VIRTUAL_SLOT(106) BFME_VIRTUAL_SLOT(107)
	BFME_VIRTUAL_SLOT(108) BFME_VIRTUAL_SLOT(109) BFME_VIRTUAL_SLOT(110) BFME_VIRTUAL_SLOT(111)
	BFME_VIRTUAL_SLOT(112) BFME_VIRTUAL_SLOT(113) BFME_VIRTUAL_SLOT(114) BFME_VIRTUAL_SLOT(115)
	BFME_VIRTUAL_SLOT(116) BFME_VIRTUAL_SLOT(117) BFME_VIRTUAL_SLOT(118) BFME_VIRTUAL_SLOT(119)
	BFME_VIRTUAL_SLOT(120) BFME_VIRTUAL_SLOT(121) BFME_VIRTUAL_SLOT(122) BFME_VIRTUAL_SLOT(123)
	BFME_VIRTUAL_SLOT(124) BFME_VIRTUAL_SLOT(125) BFME_VIRTUAL_SLOT(126) BFME_VIRTUAL_SLOT(127)
	BFME_VIRTUAL_SLOT(128) BFME_VIRTUAL_SLOT(129) BFME_VIRTUAL_SLOT(130) BFME_VIRTUAL_SLOT(131)
	BFME_VIRTUAL_SLOT(132) BFME_VIRTUAL_SLOT(133) BFME_VIRTUAL_SLOT(134) BFME_VIRTUAL_SLOT(135)
	BFME_VIRTUAL_SLOT(136) BFME_VIRTUAL_SLOT(137)
	virtual void staticLightingChanged(int partialUpdate);
};

#undef BFME_VIRTUAL_SLOT

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainVisual.h
class W3DTerrainVisual
{
public:
	virtual void setRawMapHeight(const ICoord2D *gridPos, int height);

private:
	unsigned char m_basePadding[0x0C];
	BaseHeightMapRenderObjClass *m_terrainRenderObject;
	void *m_waterRenderObject;
	WorldHeightMap *m_logicHeightMap;
};

void W3DTerrainVisual::setRawMapHeight(const ICoord2D *gridPos, int height)
{
	if (m_logicHeightMap) {
		int x = gridPos->x + m_logicHeightMap->getBorderSizeInline();
		int y = gridPos->y + m_logicHeightMap->getBorderSizeInline();
		if (m_logicHeightMap->getHeight(x, y) > height) {
			m_logicHeightMap->setRawHeight(x, y, height);
			m_terrainRenderObject->staticLightingChanged(0);
		}
	}
}
