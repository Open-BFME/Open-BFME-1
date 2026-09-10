// ?rva006F21B0@W3DDisplay@@UAEXPBVImage@@MMMMHH@Z
// partial score=0.64 date=2026-09-10
// Retail RVA 0x006F21B0, complete 1285-byte body.
//
// The body is the W3DDisplay vtable slot 53 entry (vtable VA 0x0111EDD0,
// +0xD4).  The original method spelling is not established by a named
// caller, so the source and ledger retain an address-derived method name.
// The slot ABI is independently established by the GUI display declaration:
// Image*, four Real coordinates, Color, and an image-mode Int.  The renderer
// calls below use the already matched Render2D and TextureClass ABIs; the
// image helper is retained as an address-derived declaration because its body
// is a separate retail function.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct BfmeV1207
{
	BfmeV1207(Real x, Real y) : X(x), Y(y) {}
	Real X;
	Real Y;
};

struct BfmeFloatRect
{
	BfmeFloatRect(Real left, Real top, Real right, Real bottom)
		: Left(left), Top(top), Right(right), Bottom(bottom) {}

	Real Left;
	Real Top;
	Real Right;
	Real Bottom;
};

class TextureClass
{
public:
	virtual void unused00();
	unsigned short m_referenceCount;
	unsigned short m_unmodelled_06;

	void Add_Ref()
	{
		++m_referenceCount;
	}
	void Release_Ref();
};

struct BfmeImageTexture
{
	TextureClass *texture;
};

// Only the fields and helper ABI witnessed by 0x006F21B0 are named.  The
// helper returns the image's texture wrapper and writes a second owned
// texture reference through its out parameter.
class Image
{
	unsigned char m_unmodelled_04[0x10];

public:
	Real m_uvLeft;
	Real m_uvTop;
	Real m_uvRight;
	Real m_uvBottom;
	unsigned char m_unmodelled_24[0x0C];
	unsigned char m_flags;

	void *rva006F18F0(void **releasedTexture);
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
	void Add_Quad(const BfmeFloatRect &screen, const BfmeFloatRect &uv,
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

	void setTexture(TextureClass *texture)
	{
		if (texture == m_texture)
			return;

		if (texture)
			texture->Add_Ref();
		if (m_texture)
			m_texture->Release_Ref();

		m_texture = texture;
		m_texturePresent = texture != 0;
	}
};

class BfmeA1207 : public Render2DClass
{
public:
	void bfmeDo1207(const BfmeV1207 &a1, const BfmeV1207 &a2,
		const BfmeV1207 &a3, const BfmeV1207 &a4,
		const BfmeV1207 &a5, const BfmeV1207 &a6, Int color);
};

class W3DDisplay
{
private:
	unsigned char m_unmodelled_04[0x160];
	BfmeA1207 *m_render2D;
	Int m_clipLeft;
	Int m_clipTop;
	Int m_clipRight;
	Int m_clipBottom;
	unsigned char m_isClippedEnabled;

public:
	virtual void rva006F21B0(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Int color, Int mode);
};

// ?rva006F21B0@W3DDisplay@@UAEXPBVImage@@MMMMHI@Z
void W3DDisplay::rva006F21B0(const Image *image, Real startX, Real startY,
	Real endX, Real endY, Int color, Int mode)
{
	if (image == 0)
		return;

	m_render2D->enableTexturing();
	switch (mode) {
	case 0:
		m_render2D->setMode(3);
		break;
	case 1:
		m_render2D->setMode(1);
		break;
	case 2:
		m_render2D->setMode(0);
		break;
	case 3:
		m_render2D->setMode(4);
		break;
	case 4:
		m_render2D->setMode(6);
		break;
	default:
		break;
	}

	void *releasedTexture = 0;
	BfmeImageTexture *imageTexture = static_cast<BfmeImageTexture *>(
		const_cast<Image *>(image)->rva006F18F0(&releasedTexture));
	m_render2D->setTexture(imageTexture->texture);
	if (releasedTexture)
		static_cast<TextureClass *>(releasedTexture)->Release_Ref();

	BfmeFloatRect screen(startX, startY, endX, endY);
	BfmeFloatRect uv(image->m_uvLeft, image->m_uvTop,
		image->m_uvRight, image->m_uvBottom);

	if (m_isClippedEnabled) {
		if (endX <= static_cast<Real>(m_clipLeft) ||
			endY <= static_cast<Real>(m_clipTop))
			return;

		if (startX < static_cast<Real>(m_clipLeft)) {
			Real percent = (static_cast<Real>(m_clipLeft) - startX) /
				(endX - startX);
			screen.Left = static_cast<Real>(m_clipLeft);
			uv.Left += (uv.Right - uv.Left) * percent;
		}
		if (endX > static_cast<Real>(m_clipRight)) {
			Real percent = (static_cast<Real>(m_clipRight) - startX) /
				(endX - startX);
			screen.Right = static_cast<Real>(m_clipRight);
			uv.Right = uv.Left + (uv.Right - uv.Left) * percent;
		}
		if (startY < static_cast<Real>(m_clipTop)) {
			Real percent = (static_cast<Real>(m_clipTop) - startY) /
				(endY - startY);
			screen.Top = static_cast<Real>(m_clipTop);
			uv.Top += (uv.Bottom - uv.Top) * percent;
		}
		if (endY > static_cast<Real>(m_clipBottom)) {
			Real percent = (static_cast<Real>(m_clipBottom) - startY) /
				(endY - startY);
			screen.Bottom = static_cast<Real>(m_clipBottom);
			uv.Bottom = uv.Top + (uv.Bottom - uv.Top) * percent;
		}
	}

	if (image->m_flags & 1) {
		m_render2D->bfmeDo1207(
			BfmeV1207(screen.Left, screen.Top),
			BfmeV1207(screen.Left, screen.Bottom),
			BfmeV1207(screen.Right, screen.Top),
			BfmeV1207(uv.Right, uv.Top),
			BfmeV1207(uv.Left, uv.Top),
			BfmeV1207(uv.Right, uv.Bottom), color);
		m_render2D->bfmeDo1207(
			BfmeV1207(screen.Right, screen.Bottom),
			BfmeV1207(screen.Right, screen.Top),
			BfmeV1207(screen.Left, screen.Bottom),
			BfmeV1207(uv.Left, uv.Bottom),
			BfmeV1207(uv.Right, uv.Bottom),
			BfmeV1207(uv.Left, uv.Top), color);
	} else {
		m_render2D->Add_Quad(screen, uv, color, color, color, color);
	}

	if (mode != 2)
		m_render2D->setMode(2);
}
