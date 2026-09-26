// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef unsigned int UnsignedInt;

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual bool isLoading();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value);
	virtual Xfer &xferInt(int *value);
	virtual Xfer &xferUnsignedShort(UnsignedInt *value);
};

extern void bfmeCalcTGC(void *xfer, int *value);

class EmotionMap : public _STL::map<int, int>
{
public:
	int &operator[](const int &key);
};

class EmotionShortMap : public _STL::map<unsigned short, int>
{
public:
	int &operator[](const unsigned short &key);
};

class Emotion
{
public:
	void xfer(Xfer *xfer);

private:
	void *m_object;
	void *m_entry;
	int m_unknown08;
	unsigned short m_unknown0c;
	unsigned short m_pad0e;
	int m_unknown10;
	EmotionMap m_map;
	EmotionShortMap m_shortMap;
	int m_unknown2c;
	int m_unknown30;
};

// ?xfer@Emotion@@QAEXPAVXfer@@@Z
void Emotion::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);
	bfmeCalcTGC(xfer, &m_unknown08);
	xfer->xferUnsignedShort((UnsignedInt *)&m_unknown0c);
	xfer->xferUnsignedInt((UnsignedInt *)&m_unknown10);
	int count = m_map.size();
	xfer->xferInt(&count);

	if (xfer->isLoading())
	{
		int key = 0;
		int value = 0;
		for (int i = 0; i < count; ++i)
		{
			bfmeCalcTGC(xfer, &key);
			xfer->xferUnsignedInt((UnsignedInt *)&value);
			m_map[key] = value;
		}
	}
	else
	{
		EmotionMap::iterator it = m_map.begin();
		int value;
		int key;
		while (it != m_map.end())
		{
			key = it->first;
			value = it->second;
			bfmeCalcTGC(xfer, &key);
			xfer->xferUnsignedInt((UnsignedInt *)&value);
			++it;
		}
	}

	count = m_shortMap.size();
	xfer->xferInt(&count);
	if (xfer->isLoading())
	{
		unsigned short key = 0;
		int value = 0;
		for (int i = 0; i < count; ++i)
		{
			xfer->xferUnsignedShort((UnsignedInt *)&key);
			xfer->xferUnsignedInt((UnsignedInt *)&value);
			m_shortMap[(unsigned short)key] = value;
		}
	}
	else
	{
		EmotionShortMap::iterator it = m_shortMap.begin();
		int value;
		unsigned short key;
		while (it != m_shortMap.end())
		{
			key = it->first;
			value = it->second;
			xfer->xferUnsignedShort((UnsignedInt *)&key);
			xfer->xferUnsignedInt((UnsignedInt *)&value);
			++it;
		}
	}

	xfer->xferUnsignedInt((UnsignedInt *)&m_unknown2c);
	xfer->xferUnsignedInt((UnsignedInt *)&m_unknown30);
}
