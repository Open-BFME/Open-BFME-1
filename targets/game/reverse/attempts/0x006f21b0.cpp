// ?rva006F21B0@W3DDisplay@@UAEXPBVImage@@MMMMHH@Z
// partial score=0.98 date=2026-09-26
// Corrected behavioral bank; not a verified caller ABI.
// Complete extent: RVA006F21B0, 1312B = 1285B code + 3B alignment + 24B switch table.
// Restores both clipping branches, UV+14, one-word handle, and all six mode entries.
// score=0.98 is normalized code-only instruction agreement (343/350), NOT bytes.
// Native1396B vs retail1312B; frame88 vs58 and Image helper cleanup remain unresolved.
// See targets/game/reverse/identity_evidence/006f21b0-corrected-render-bank.md.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug

#include <stdlib.h>
typedef int Int;
typedef unsigned long UnsignedInt;
typedef float Real;

#include "rect.h"
#include "texture.h"

struct BfmeImageTexture
{
 TextureClass *texture;
 ~BfmeImageTexture(){if(texture)texture->Release_Ref();}
};

// Image UV starts at +14 and status at +30.
// The result is one owned pointer. Its native declaration below is still an
// EXPERIMENT: retail uses ECX=this, a stack result pointer, and caller cleanup;
// MSVC member sret instead assumes callee cleanup. Do not pin this declaration.
class Image
{
	unsigned char m_unmodelled_04[0x14];

public:
	Real m_uvLeft;
	Real m_uvTop;
	Real m_uvRight;
	Real m_uvBottom;
	unsigned char m_unmodelled_24[0x0C];
	unsigned char m_flags;

	BfmeImageTexture rva006F18F0();
};

class Render2DClass
{
private:
	Int m_mode;
	unsigned char m_unmodelled_04[0x48];
	TextureClass *m_texture;
	Int m_texturePresent;
	unsigned char m_texturingEnabled;

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

 void setTexture(const BfmeImageTexture &handle)
 {
  if(handle.texture == m_texture) return;
  if(handle.texture) handle.texture->Add_Ref();
  if(m_texture) m_texture->Release_Ref();
  m_texture = handle.texture;
  m_texturePresent = -(handle.texture != 0);
 }

};

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
		const_cast<Image *>(image)->rva006F18F0());

	RectClass screen(startX, startY, endX, endY);
	RectClass uv(image->m_uvLeft, image->m_uvTop,
		image->m_uvRight, image->m_uvBottom);

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

			if( (image->m_flags & 1) )
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

	if (image->m_flags & 1) {
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
