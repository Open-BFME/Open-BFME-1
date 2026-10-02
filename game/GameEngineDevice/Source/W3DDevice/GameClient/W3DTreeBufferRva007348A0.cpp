// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x007348A0 rebuilds the tree texture collections and copies their handles.
// The owner is witnessed by W3DTreeBuffer's constructor layout and the two
// "Combined tree ... texture" diagnostic literals. The BFME method spelling is
// not known, so retain its address. See targets/game/reverse/identity_evidence/007348a0.md.

#include "ascii_string.h"

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

// Retail diagnostic loads use VA 0x01336E5C, owned by this shared pointer cell.
// See targets/game/reverse/identity_evidence/rva00f36e5c-pointer-provider.md.
extern void *g_Rva00F36E5C;
extern bool _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);

struct Rva007348A0Type {
 char prefix[0x24];
 BfmeVec2EY coord24,coord2c,coord34,coord3c;
 bool doShadow;
 AsciiString textureName;
 AsciiString name4c, nameC, name54;
 int field58;
};
class W3DTreeBuffer {
public:
 void rva007348A0();
 char prefix[0xb8];
 BFMEWaterTrackTextureHandle	textureB8,textureBC;
 Rva0094D1E0List listC0,listE8;
 char gap110[0x2a7cbc-0x110];
 Rva007348A0Type types[64];
 int numTypes;
};
typedef char Rva007348A0TypeSize[(sizeof(Rva007348A0Type) == 0x5c) ? 1 : -1];

void W3DTreeBuffer::rva007348A0()
{
	listC0.clear(false);
	listE8.clear(true);
	int i;
	for (i = 0; i < numTypes; ++i) {
		listC0.rva0094D250(BFMEGetWaterTrackTexture((char*)types[i].nameC.str(),0,0));
		if (types[i].doShadow)
			listE8.rva0094D250(BFMEGetWaterTrackTexture((char*)types[i].textureName.str(),0,0));
	}
	for (i = 0; i < numTypes; ++i) {
		listC0.lookup(BFMEGetWaterTrackTexture((char*)types[i].nameC.str(),0,0),&types[i].coord24,&types[i].coord34);
		if (types[i].doShadow)
			listE8.lookup(BFMEGetWaterTrackTexture((char*)types[i].textureName.str(),0,0),&types[i].coord2c,&types[i].coord3c);
	}
	textureB8 = listC0.rva0094D9F0();
	textureBC = listE8.rva0094D9F0();
	if ((unsigned)((BfmeThingEF*)&textureB8)->bfmeAskEF() > 1024 ||
		(unsigned)((BfmeThingGN*)&textureB8)->bfmeAskGN() > 1024) {
		if (_bfme_debugReportingEnabled()) {
			_bfme_debugRecordCallsite(1);
			static_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->v60();
			static_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->v6c(0, 0)->v38(
				"Combined tree texture is bigger than 1024x1024. This will cause errors and significant slowdown on most graphics cards and has to be fixed!")->v4c(2);
		}
	}
	if ((unsigned)((BfmeThingEF*)&textureBC)->bfmeAskEF() > 1024 ||
		(unsigned)((BfmeThingGN*)&textureBC)->bfmeAskGN() > 1024) {
		if (_bfme_debugReportingEnabled()) {
			_bfme_debugRecordCallsite(1);
			static_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->v60();
			static_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->v6c(0, 0)->v38(
				"Combined tree shadow texture is bigger than 1024x1024. This will cause errors and significant slowdown on most graphics cards and has to be fixed!")->v4c(2);
		}
	}
}
