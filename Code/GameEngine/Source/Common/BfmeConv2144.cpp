class BfmeDynBufXZ
{
public:
	virtual void bfmeDropXZ();

	int m_bfmeRefsXZ;
};

class BfmeDynElemXZ
{
public:
	void bfmeResetXZ(unsigned int fvf, int flag);

	unsigned char m_bfmePadXZ[0x40];
};

extern "C" BfmeDynBufXZ *_bfmeDynBufXZ[];
extern "C" unsigned int _bfmeDynFvfXZ[];
extern "C" unsigned char _bfmeDynInUseXZ[];
extern "C" unsigned short _bfmeDynSizeXZ[];
extern "C" unsigned short _bfmeDynOffsetXZ[];
extern "C" BfmeDynElemXZ _bfmeDynElemXZ[];

void bfmeResetDynXZ()
{
	int i;

	for (i = 0; i < 24; i++)
	{
		BfmeDynBufXZ *buf = _bfmeDynBufXZ[i];

		if (buf != 0)
		{
			if (--buf->m_bfmeRefsXZ == 0)
				buf->bfmeDropXZ();

			_bfmeDynBufXZ[i] = 0;
		}

		_bfmeDynInUseXZ[i] = 0;
		_bfmeDynSizeXZ[i] = 0x1388;
		_bfmeDynOffsetXZ[i] = 0;

		_bfmeDynElemXZ[i].bfmeResetXZ(_bfmeDynFvfXZ[i], 0);
	}
}
