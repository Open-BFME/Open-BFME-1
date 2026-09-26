// cl: /DNDEBUG /MD /EHsc
//
// Rva003C1A50::run, retail 0x003C1A50, 84 bytes.
//
// d_003b8450 reset path: clearOwned + clearTwoVec, settle +0x74/+0x80/+0x78/
// +0xC8/+0xCC, singleton go, clearSingleton, set m_at2C, tail-reset UI.

class Glo012F706CType
{
public:
	void go();
	void resetUi();
};

extern Glo012F706CType *g_bfmeGameCW;

class Rva003C1A50
{
public:
	void run();
	void clearOwned();
	void clearTwoVec();
	void clearSingleton();

private:
	char m_pad00[ 0x2C ];
	bool m_at2C;
	char m_pad2D[ 0x74 - 0x2D ];
	int m_at74;
	bool m_at78;
	char m_pad79[ 0x80 - 0x79 ];
	bool m_at80;
	char m_pad81[ 0xC8 - 0x81 ];
	bool m_atC8;
	char m_padC9[ 0xCC - 0xC9 ];
	int m_atCC;
};

// ?run@Rva003C1A50@@QAEXXZ
void Rva003C1A50::run()
{
	clearOwned();
	clearTwoVec();
	m_at74 = 1;
	m_at80 = false;
	m_at78 = false;
	m_atC8 = true;
	m_atCC = 0x78;
	g_bfmeGameCW->go();
	clearSingleton();
	m_at2C = true;
	g_bfmeGameCW->resetUi();
}
