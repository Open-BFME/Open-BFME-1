// cl: /DNDEBUG /MD /EHsc
// Ported from EA Generals Zero Hour W3DWater.cpp (Copyright 2025 Electronic Arts Inc.).
// Distributed under GNU GPL version 3 or later, as the reference source.
// Retail 0x0079E700. ZH W3DWater.cpp initBumpMap donor, BFME init caller
// 0x007A5200, and the complete grayscale-gradient loop prove the identity.
// BFME's SurfaceClass methods operate on a four-byte COM handle; the local
// ABI view is intentional: surfaceclass.h has the incompatible ZH refcount
// layout and lacks the bool-discard Lock overload used by this body.
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef long LONG;
typedef int Int;
struct LockedRect0079E700 { int Pitch; void *pBits; };
class SurfaceClass { public:
 struct SurfaceDescription { unsigned Format, Width, Height; };
 void Get_Description(SurfaceDescription &);
 void *Lock(int *,bool=false);
 void Unlock();
};
struct SurfaceCOM0079E700 { virtual void __stdcall slot00(); virtual unsigned long __stdcall AddRef(); virtual unsigned long __stdcall Release(); };
class W3DRadarResetSurface : public SurfaceClass { public:
 SurfaceCOM0079E700 *m_surface;
 W3DRadarResetSurface():m_surface(0){}
 ~W3DRadarResetSurface();
 W3DRadarResetSurface &operator=(const W3DRadarResetSurface &v) {
  if(v.m_surface)v.m_surface->AddRef();
  if(m_surface)m_surface->Release();
  m_surface=v.m_surface; return *this;
 }
};
class W3DRadarResetTexture { public:
 W3DRadarResetSurface getSurfaceLevel();
 W3DRadarResetSurface getSurfaceLevel(unsigned);
};
// The historical Peek_D3D_Base_Texture symbol names D3D8, but the retail
// object dispatches through the witnessed COM slots below (LockRect +0x4C).
// Keep the symbol signature and use an address-derived view of that interface.
struct IDirect3DBaseTexture8;
struct TextureCOM0079E700 { public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c(); virtual void slot30();
 virtual unsigned __stdcall GetLevelCount();
 virtual void slot38(); virtual void slot3c(); virtual void slot40(); virtual void slot44(); virtual void slot48();
 virtual long __stdcall LockRect(unsigned,LockedRect0079E700 *,void *,unsigned);
 virtual long __stdcall UnlockRect(unsigned);
};
class TextureBaseClass { public: IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const; };
class BFMEWaterTrackTextureHandle {};
struct Rva00904BE0Texture;
Rva00904BE0Texture *Rva00904BE0CreateTexture(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
class WaterRenderObjClass { public: long initBumpMap(void **, const BFMEWaterTrackTextureHandle &); };
long WaterRenderObjClass::initBumpMap(void **output,const BFMEWaterTrackTextureHandle &source) {
 SurfaceClass::SurfaceDescription d3dsd;
 W3DRadarResetSurface surf;
 LockedRect0079E700 d3dlr;
 DWORD dwSrcPitch;
 BYTE *pSrc;
 Int numLevels;
 W3DRadarResetTexture *pBumpSource=(W3DRadarResetTexture *)&source;
 TextureCOM0079E700 **pTex=(TextureCOM0079E700 **)output;
 surf=pBumpSource->getSurfaceLevel();
 surf.Get_Description(d3dsd);
 if(d3dsd.Format!=21)return 0;
 if(((TextureBaseClass*)pBumpSource)->Peek_D3D_Base_Texture())
  numLevels=((TextureCOM0079E700*)((TextureBaseClass*)pBumpSource)->Peek_D3D_Base_Texture())->GetLevelCount();
 else return 0;
 pTex[0]=(TextureCOM0079E700*)Rva00904BE0CreateTexture(d3dsd.Width,d3dsd.Height,60,0,1,0);
 for(Int level=0;level<numLevels;level++) {
  surf=pBumpSource->getSurfaceLevel(level);
  surf.Get_Description(d3dsd);
  pSrc=(BYTE*)surf.Lock((int*)&dwSrcPitch);
  pTex[0]->LockRect(level,&d3dlr,0,0);
  DWORD dwDstPitch=(DWORD)d3dlr.Pitch;
  BYTE *pDst=(BYTE*)d3dlr.pBits;
  for(DWORD y=0;y<d3dsd.Height;y++) {
   BYTE *pDstT=pDst;
   BYTE *pSrcB0=pSrc;
   BYTE *pSrcB1=pSrcB0+dwSrcPitch;
   BYTE *pSrcB2=pSrcB0-dwSrcPitch;
   if(y==d3dsd.Height-1)pSrcB1=pSrcB0;
   if(y==0)pSrcB2=pSrcB0;
   for(DWORD x=0;x<d3dsd.Width;x++) {
    LONG v00=256-*(pSrcB0+0);
    LONG v01=256-*(pSrcB0+4);
    LONG vM1=256-*(pSrcB0-4);
    LONG v10=256-*(pSrcB1+0);
    LONG v1M=256-*(pSrcB2+0);
    LONG iDu=vM1-v01;
    LONG iDv=v1M-v10;
    if(v00<vM1 && v00<v01) { iDu=vM1-v00; if(iDu<v00-v01)iDu=v00-v01; }
    *pDstT++=(BYTE)iDu;
    *pDstT++=(BYTE)iDv;
    pSrcB0+=4; pSrcB1+=4; pSrcB2+=4;
   }
   pSrc+=dwSrcPitch; pDst+=dwDstPitch;
  }
  pTex[0]->UnlockRect(level);
  surf.Unlock();
 }
 return 0;
}
