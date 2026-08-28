// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?loadRoads@W3DRoadBuffer@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp
// Grok promote from masm_dumps — retail 0x007105D0 size 61
// was: Code/masm_dumps/W3DRoadBuffer_loadRoads.asm

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DRoadBuffer.h
class W3DRoadBuffer {
public:
	void loadRoadsHelper0(void);
	void loadRoadsHelper1(void);
	void loadRoadsHelper2(void);
	static void loadRoadsHelper3(void);
	void loadRoadsHelper4(void);
	void loadRoadsHelper5(void);
	void loadRoadsHelper6(void);
	void loadRoads(void);
};

// ?loadRoads@W3DRoadBuffer@@QAEXXZ
void W3DRoadBuffer::loadRoads(void)
{
	if (*(unsigned char *)((unsigned char *)this + 0x0C))
	{
		loadRoadsHelper0();
		loadRoadsHelper1();
		loadRoadsHelper2();
		loadRoadsHelper3();
		loadRoadsHelper4();
		loadRoadsHelper5();
		loadRoadsHelper6();
		*(unsigned char *)((unsigned char *)this + 0x50) = 1;
	}
}

