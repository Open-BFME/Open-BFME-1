// cl: /DNDEBUG /MD /EHsc
// readable body of ?createVideoBuffer@W3DDisplay@@UAEPAVVideoBuffer@@_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp

void __cdecl W3DRadarResetLock(void);
char __cdecl bfmeUnlock1179(void);

class W3DRadarResetGuard
{
public:
	W3DRadarResetGuard(void)
	{
		W3DRadarResetLock();
	}

	~W3DRadarResetGuard(void)
	{
		bfmeUnlock1179();
	}
};

enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN = 0
};

class W3DRadarFormatCaps
{
public:
	bool supportTextureFormat(WW3DFormat format);
};

extern W3DRadarFormatCaps *TheW3DRadarFormatCaps;

int Rva00903060Get(void);
int Rva00739D20(int format, bool allowAlpha);

class VideoBuffer
{
};

class W3DVideoBuffer : public VideoBuffer
{
public:
	W3DVideoBuffer(int format);

private:
	unsigned char m_pad[0x4C];
};

class W3DDisplay
{
public:
	virtual VideoBuffer *createVideoBuffer(bool allowAlpha);
};

// ?createVideoBuffer@W3DDisplay@@UAEPAVVideoBuffer@@_N@Z
VideoBuffer *W3DDisplay::createVideoBuffer(bool allowAlpha)
{
	W3DRadarResetGuard lock;
	int format = 0;

	if (allowAlpha && TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)0x15))
		format = 5;
	else
	{
		int native = Rva00903060Get();
		if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)native))
			format = Rva00739D20(native, allowAlpha);
		if (format == 0)
		{
			if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)0x16))
				format = 2;
			else if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)0x14))
				format = 1;
			else if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)0x17))
				format = 3;
			else if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)0x18))
				format = 4;
			else
				return 0;
		}
	}

	return new W3DVideoBuffer(format);
}
