// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x0071DAF0 rebuilds the shrub texture collections and copies their handles.
// The owner is witnessed by W3DShrubBuffer's constructor layout and the two
// "Combined shrub ... texture" diagnostic literals. The BFME method spelling is
// not known, so retain its address. See targets/game/reverse/identity_evidence/0071daf0.md.

#include "ascii_string.h"
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

class TextureClass { public: void Release_Ref(); };
class BFMEWaterTrackTextureHandle {
public:
	TextureClass *m_texture;
	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
	BFMEWaterTrackTextureHandle &operator=(const BFMEWaterTrackTextureHandle &other)
	{
		if (other.m_texture)
			++*(unsigned short *)((char *)other.m_texture + 4);
		if (m_texture)
			m_texture->Release_Ref();
		m_texture = other.m_texture;
		return *this;
	}
};
BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char*,int,int);
class BfmeVec2EY { public: float x,y; };
class BfmeHostEY { public: char bfmeLookupEY(void *,BfmeVec2EY*,BfmeVec2EY*); };
class BfmeThingEF { public: int bfmeAskEF(); };
class BfmeThingGN { public: int bfmeAskGN(); };
class Rva0094D1E0List {
public:
 unsigned char body[0x28];
 void clear(bool);
 void rva0094D250(const BFMEWaterTrackTextureHandle&);
 BFMEWaterTrackTextureHandle rva0094D9F0();
 void lookup(const BFMEWaterTrackTextureHandle &key, BfmeVec2EY *size, BfmeVec2EY *origin) { ((BfmeHostEY*)this)->bfmeLookupEY((void*)&key,size,origin); }
};
// ABI adapters to existing ledger bodies. 0x0094D250 takes ECX plus a reference
// to the one-pointer handle and returns with RET 4. 0x0094D9F0 takes ECX plus
// the hidden result pointer, fills it, and returns that pointer in EAX.

class BfmeAwakenLog
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual BfmeAwakenLog *v38(const char *message);
	virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
	virtual void v4c(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
	virtual void v60();
	virtual void v64(); virtual void v68();
	virtual BfmeAwakenLog *v6c(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);


struct Rva00720D10Data { char prefix[0xc]; AsciiString nameC; };

struct Rva0071DAF0Type {
 char prefix[0x20];
 const Rva00720D10Data *data;
 BfmeVec2EY coord24,coord2c,coord34,coord3c;
 bool doShadow;
 AsciiString textureName;
 char suffix[0x10];
};
class W3DShrubBuffer {
public:
 void rva0071DAF0();
 char prefix[0x1450];
 BFMEWaterTrackTextureHandle	texture1450,texture1454;
 Rva0094D1E0List list1458,list1480;
 char gap14a8[0x1e1cd4-0x14a8];
 Rva0071DAF0Type types[64];
 int numTypes;
};
typedef char Rva0071DAF0TypeSize[(sizeof(Rva0071DAF0Type) == 0x5c) ? 1 : -1];

void W3DShrubBuffer::rva0071DAF0()
{
	list1458.clear(false);
	list1480.clear(false);
	int i;
	for (i = 0; i < numTypes; ++i) {
		list1458.rva0094D250(BFMEGetWaterTrackTexture((char*)types[i].data->nameC.str(),0,0));
		if (types[i].doShadow)
			list1480.rva0094D250(BFMEGetWaterTrackTexture((char*)types[i].textureName.str(),0,0));
	}
	for (i = 0; i < numTypes; ++i) {
		list1458.lookup(BFMEGetWaterTrackTexture((char*)types[i].data->nameC.str(),0,0),&types[i].coord24,&types[i].coord34);
		if (types[i].doShadow)
			list1480.lookup(BFMEGetWaterTrackTexture((char*)types[i].textureName.str(),0,0),&types[i].coord2c,&types[i].coord3c);
	}
	texture1450 = list1458.rva0094D9F0();
	texture1454 = list1480.rva0094D9F0();
	if ((unsigned)((BfmeThingEF*)&texture1450)->bfmeAskEF() > 1024 ||
		(unsigned)((BfmeThingGN*)&texture1450)->bfmeAskGN() > 1024) {
		if (_bfme_debugReportingEnabled()) {
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->v60();
			TheBfmeAwakenDebug->v6c(0, 0)->v38(
				"Combined shrub texture is bigger than 1024x1024. This will cause errors and significant slowdown on most graphics cards and has to be fixed!")->v4c(2);
		}
	}
	if ((unsigned)((BfmeThingEF*)&texture1454)->bfmeAskEF() > 1024 ||
		(unsigned)((BfmeThingGN*)&texture1454)->bfmeAskGN() > 1024) {
		if (_bfme_debugReportingEnabled()) {
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->v60();
			TheBfmeAwakenDebug->v6c(0, 0)->v38(
				"Combined shrub shadow texture is bigger than 1024x1024. This will cause errors and significant slowdown on most graphics cards and has to be fixed!")->v4c(2);
		}
	}
}
