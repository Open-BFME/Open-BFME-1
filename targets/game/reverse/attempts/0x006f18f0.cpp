// ?rva006F18F0@@YA?AVBFMEWaterTrackTextureHandle@@PBVImage@@@Z
// partial score=1.0 date=2026-09-26
// Full native helper371B is exact modulo21 independently audited relocations.
// D4 renderer1312/1312B,171 differing positional bytes; no game-source claim.
// ABI recovered by static-helper visibility; native Add_Tri visibility restores frame58.
// See identity_evidence/006f21b0-private-helper-and-frame.md.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug

// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include "ascii_string.h"
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
#include <stdlib.h>
typedef int Int;
typedef unsigned long UnsignedInt;
typedef float Real;

#include "rect.h"
#include "texture.h"

class ShroudFilter { public: unsigned char pad[0x0c]; int field0c; int field10; };
class ShroudTexture { public: ShroudFilter *getFilter(); };
class Gen_0090E810 { public: void bfmeSetFlag(unsigned char); };
class BFMEWaterTrackTextureHandle
{
public:
 TextureClass *texture;
 BFMEWaterTrackTextureHandle(const BFMEWaterTrackTextureHandle &o):texture(o.texture){if(texture)texture->Add_Ref();}
 ~BFMEWaterTrackTextureHandle(){if(texture)texture->Release_Ref();}
 ShroudFilter *getFilter(){return ((ShroudTexture*)this)->getFilter();}
 void setFlag(unsigned char value){((Gen_0090E810*)this)->bfmeSetFlag(value);}
};
extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char*,int,int);
struct Rva001408C0Target;
class AssetList
{
 _STL::set<Rva001408C0Target*> prototypes;
 unsigned int field0c;
 bool changed;
public:
 AssetList();
 AssetList &operator<<(const AsciiString&);
};
// AssetList ctor at143B20: same20B layout as operator141D00 and dtor140950.
// A future landing needs the independently supported ctor pin; no pin is banked.
extern void Rva009EBAC0(int);
struct Rva006F18F0Region { struct Coord { float x,y; }; Coord lo,hi; };
class Image
{
 unsigned char pad00[0x14];
public:
 Rva006F18F0Region m_UVCoords;
 const Rva006F18F0Region *getUV()const{return &m_UVCoords;}
 unsigned char pad24[8];
 BFMEWaterTrackTextureHandle *m_rawTextureData;
 UnsignedInt m_status;
 UnsignedInt getStatus() const {return m_status;}
 AsciiString getFilename()const;
};
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
static BFMEWaterTrackTextureHandle rva006F18F0(const Image *image)
{
 if(image->getStatus() & 2)
 {
  BFMEWaterTrackTextureHandle texture(*image->m_rawTextureData);
  texture.getFilter()->field10=1;
  texture.getFilter()->field0c=1;
  return texture;
 }
 else
 {
  if(Rva0134FAA0)
  {
   AssetList assets;
   assets << image->getFilename();
   Rva009EBAC0((int)&assets);
  }
  BFMEWaterTrackTextureHandle texture(BFMEGetWaterTrackTexture((char*)image->getFilename().str(),1,0));
  texture.getFilter()->field10=1;
  texture.getFilter()->field0c=1;
  texture.setFlag(1);
  return texture;
 }
}

typedef unsigned long BfmeUInt32;

struct BfmeRenderVertex
{
	float x;
	float y;
	float z;
	unsigned char m_unmodelled_0C[0x0C];
	BfmeUInt32 color;
	float u;
	float v;
	unsigned char m_unmodelled_24[0x08];
};

typedef BfmeUInt32(__cdecl *BfmeColorConverter)(BfmeUInt32 color);

extern "C" float g_BfmeRender2DZ;
extern "C" BfmeColorConverter g_BfmeColorConverter;

class Render2DClass
{
private:
	Int m_mode;
	float m_coordinateScaleX,m_coordinateScaleY,m_biasedCoordinateOffsetX,m_biasedCoordinateOffsetY;
 unsigned char m_unmodelled_14[0x38];
	struct Pair { TextureClass *texture; int flags; };
 Pair m_pair;
	unsigned char m_texturingEnabled;
	BfmeRenderVertex *allocateGeometry006e(
		unsigned int vertexCount,
		unsigned int indexCount,
		BfmeUInt32 **indices,
		BfmeUInt32 *baseVertexPair);

	void convertPosition006e(BfmeRenderVertex &vertex, const Vector2 &v)
	{
		vertex.x = v.X * m_coordinateScaleX + m_biasedCoordinateOffsetX;
		vertex.y = v.Y * m_coordinateScaleY + m_biasedCoordinateOffsetY;
	}

public:
	
 void Add_Tri(const Vector2&,const Vector2&,const Vector2&,const Vector2&,const Vector2&,const Vector2&,UnsignedInt);

 void Add_Quad(const RectClass &screen, const RectClass &uv,
		UnsignedInt color0, UnsignedInt color1, UnsignedInt color2,
		UnsignedInt color3);

	void setMode(Int mode)
	{
		m_mode = mode;
	}

	void enableTexturing()
	{
		m_texturingEnabled = 1;
	}

 void setTexture(const BFMEWaterTrackTextureHandle &handle)
 {
  if(handle.texture == m_pair.texture)return;
  if(handle.texture)handle.texture->Add_Ref();
  if(m_pair.texture)m_pair.texture->Release_Ref();
  Pair updated={handle.texture,handle.texture ? -1:0};
  m_pair=updated;
 }

};

// ?Add_Tri@Render2DClass@@QAEXABVVector2@@00000K@Z
void Render2DClass::Add_Tri(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2,
	const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2,
	BfmeUInt32 color)
{
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(
		3, 3, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], v0);
	vertices[0].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[1], v1);
	vertices[1].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[2], v2);
	vertices[2].z = g_BfmeRender2DZ;

	vertices[0].u = uv0.X;
	vertices[0].v = uv0.Y;
	vertices[1].u = uv1.X;
	vertices[1].v = uv1.Y;
	vertices[2].u = uv2.X;
	vertices[2].v = uv2.Y;

	BfmeUInt32 convertedColor = g_BfmeColorConverter(color);
	vertices[2].color = convertedColor;
	vertices[1].color = convertedColor;
	vertices[0].color = convertedColor;

	reinterpret_cast<unsigned short *>(indices)[0] = (unsigned short)baseVertexPair;
	reinterpret_cast<unsigned short *>(indices)[1] = (unsigned short)baseVertexPair + 1;
	reinterpret_cast<unsigned short *>(indices)[2] = (unsigned short)baseVertexPair + 2;
}

class W3DDisplay
{
private:
	unsigned char m_unmodelled_04[0x160];
	Render2DClass *m_render2D;
	Int m_clipLeft;
	Int m_clipTop;
	Int m_clipRight;
	Int m_clipBottom;
	unsigned char m_isClippedEnabled;

public:
	virtual void rva006F21B0(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Int color, Int mode);
};

// ?rva006F21B0@W3DDisplay@@UAEXPBVImage@@MMMMHH@Z
void W3DDisplay::rva006F21B0(const Image *image, Real startX, Real startY,
	Real endX, Real endY, Int color, Int mode)
{
	if (image == 0)
		return;

	const Rva006F18F0Region *imageUV=image->getUV();
	m_render2D->enableTexturing();
	switch (mode) {
	case 1:
		m_render2D->setMode(3);
		break;
	case 3:
		m_render2D->setMode(1);
		break;
	case 0:
		m_render2D->setMode(0);
		break;
	case 4:
		m_render2D->setMode(4);
		break;
	case 5:
		m_render2D->setMode(6);
		break;
	case 2:
		goto afterMode;
	default:
		goto afterMode;
	}

afterMode:
	m_render2D->setTexture(
		rva006F18F0(image));

	RectClass screen(startX, startY, endX, endY);
	RectClass uv(imageUV->lo.x, imageUV->lo.y,
		imageUV->hi.x, imageUV->hi.y);

	if (m_isClippedEnabled)
	{	//need to clip this quad to clip rectangle

		//
		//	Check for completely clipped
		//
		if (	endX <= m_clipLeft ||
				endY <= m_clipTop)
		{
			return;	//nothing to render
		} else {
			RectClass clipped_rect;
			RectClass clipped_uv;

			if( (image->getStatus() & 1) )
			{

	
				//
				//	Clip the polygons to the specified area
				//
				
				clipped_rect.Left		= __max (screen.Left, m_clipLeft);
				clipped_rect.Right	= __min (screen.Right, m_clipRight);
				clipped_rect.Top		= __max (screen.Top, m_clipTop);
				clipped_rect.Bottom	= __min (screen.Bottom, m_clipBottom);

				//
				//	Clip the texture to the specified area
				//
				
				float percent				= ((clipped_rect.Left - screen.Left) / screen.Width ());
				clipped_uv.Top		= uv.Top + (uv.Height () * percent);

				percent						= ((clipped_rect.Right - screen.Left) / screen.Width ());
				clipped_uv.Bottom	= uv.Top + (uv.Height () * percent);

				percent						= ((clipped_rect.Top - screen.Top) / screen.Height ());
				clipped_uv.Right	= uv.Right - (uv.Width () * percent);

				percent						= ((clipped_rect.Bottom - screen.Top) / screen.Height ());
				clipped_uv.Left		= uv.Right - (uv.Width () * percent);
			}
			else

			{
			
				//
				//	Clip the polygons to the specified area
				//
				
				clipped_rect.Left		= __max (screen.Left, m_clipLeft);
				clipped_rect.Right	= __min (screen.Right, m_clipRight);
				clipped_rect.Top		= __max (screen.Top, m_clipTop);
				clipped_rect.Bottom	= __min (screen.Bottom, m_clipBottom);

				//
				//	Clip the texture to the specified area
				//
				
				float percent				= ((clipped_rect.Left - screen.Left) / screen.Width ());
				clipped_uv.Left		= uv.Left + (uv.Width () * percent);

				percent						= ((clipped_rect.Right - screen.Left) / screen.Width ());
				clipped_uv.Right	= uv.Left + (uv.Width () * percent);

				percent						= ((clipped_rect.Top - screen.Top) / screen.Height ());
				clipped_uv.Top		= uv.Top + (uv.Height () * percent);

				percent						= ((clipped_rect.Bottom - screen.Top) / screen.Height ());
				clipped_uv.Bottom	= uv.Top + (uv.Height () * percent);
			}

			//
			//	Use the clipped rectangles to render
			//
			screen = clipped_rect;
			uv		= clipped_uv;
		}
	}

	if (image->getStatus() & 1) {
		m_render2D->Add_Tri(
			Vector2(screen.Left, screen.Top),
			Vector2(screen.Left, screen.Bottom),
			Vector2(screen.Right, screen.Top),
			Vector2(uv.Right, uv.Top),
			Vector2(uv.Left, uv.Top),
			Vector2(uv.Right, uv.Bottom), color);
		m_render2D->Add_Tri(
			Vector2(screen.Right, screen.Bottom),
			Vector2(screen.Right, screen.Top),
			Vector2(screen.Left, screen.Bottom),
			Vector2(uv.Left, uv.Bottom),
			Vector2(uv.Right, uv.Bottom),
			Vector2(uv.Left, uv.Top), color);
	} else {
		m_render2D->Add_Quad(screen, uv, color, color, color, color);
	}

	if (mode != 2)
		m_render2D->setMode(2);
}
