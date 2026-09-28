// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?Rva009A6130PostFilterDispatch@@YAXPAURva009A6130Context@@HHHHPAE11HH@Z
// Retail 0x009A6130 (1155 bytes of code, then its 9-entry jump table): the
// VP6 decoder's per-frame post-filter dispatch.
//
// ABI: the three call sites in the anonymous codec body 0x009A51A0 push ten
// cdecl arguments; the body stores nine of them into the context (+0x00..
// +0x20) and switches on the fourth (+0x08) over 0..8.  Every level drives
// the landed plane helpers: bfmeFillZJ (per-fragment table-index fill from the
// +0x18 rows / +0x1C stride / +0x20 mask), Rva009AF200CopyPlanes,
// Rva009AF320CopyPlanes and Rva009B3800PlaneCopy, plus three generated bodies
// whose cdecl arity every call site shows: 0x009A8C50 (context, frame) and
// 0x009B2530 / 0x009B2A50 (context, source, destination).  The two indirect
// calls are the dispatch slots 0x01356E6C (source Y, destination Y, width,
// height, stride) and 0x01356E60, which holds the landed five-argument
// Rva009BA790 noise kernel.
//
// Field names follow the landed siblings' witnessed context layout (m_mode
// +0x00, m_tableIndex +0x0C, m_planeY/U/V +0x78/+0x7C/+0x80, m_width +0x90,
// m_height +0x94, m_strideY +0x98); +0x10/+0x14 are the source and
// destination frames the helpers receive.  The rest keep offset names, and
// no symbol names the function, so it keeps the address token.
//
// Shape notes: fields are read back from the context (retail reloads them
// after each call); the noise call's last argument is the parameter itself,
// held in esi.  Levels 4 and 7 share their "m_6c set" tail by cross-jumping,
// which needs the m_c0-clear branch written first.

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct BfmeGridZJ;
struct Rva009AF200Context;
struct Rva009AF320Context;
struct Rva009B3800Context;
void __cdecl bfmeFillZJ(BfmeGridZJ *);
void __cdecl Rva009AF200CopyPlanes(Rva009AF200Context *, int, int);
void __cdecl Rva009AF320CopyPlanes(Rva009AF320Context *, int, int);
void __cdecl Rva009B3800PlaneCopy(Rva009B3800Context *, int, int);

struct Rva009A6130Context;
void __cdecl Rva009A8C50(Rva009A6130Context *, unsigned char *);
void __cdecl Rva009B2530(Rva009A6130Context *, unsigned char *, unsigned char *);
void __cdecl Rva009B2A50(Rva009A6130Context *, unsigned char *, unsigned char *);

typedef void (__cdecl *Rva009A6130CopyY)(unsigned char *, unsigned char *,
	unsigned int, unsigned int, unsigned int);
typedef void (__cdecl *Rva009A6130Noise)(unsigned char *, unsigned int,
	unsigned int, unsigned int, int);
extern Rva009A6130CopyY g_rva01356E6C;
extern Rva009A6130Noise g_rva01356E60;

struct Rva009A6130Context
{
	int m_mode;
	int m_04;
	int m_level;
	int m_tableIndex;
	unsigned char *m_source;
	unsigned char *m_destination;
	unsigned char *m_18;
	int m_1c;
	int m_20;
	unsigned char m_pad24[0x6c - 0x24];
	void *m_6c;
	unsigned char m_pad70[0x78 - 0x70];
	unsigned int m_planeY;
	unsigned int m_planeU;
	unsigned int m_planeV;
	unsigned char m_pad84[0x90 - 0x84];
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_strideY;
	unsigned char m_pad9c[0xbc - 0x9c];
	unsigned char *m_bc;
	void *m_c0;
	void *m_c4;
};

// The landed helpers each declare their own view of this context.
#define FILL(c) bfmeFillZJ((BfmeGridZJ *)(c))
#define AF200(c, a, b) Rva009AF200CopyPlanes((Rva009AF200Context *)(c), (int)(a), (int)(b))
#define AF320(c, a, b) Rva009AF320CopyPlanes((Rva009AF320Context *)(c), (int)(a), (int)(b))
#define B3800(c, a, b) Rva009B3800PlaneCopy((Rva009B3800Context *)(c), (int)(a), (int)(b))

void __cdecl Rva009A6130PostFilterDispatch(Rva009A6130Context *ctx, int mode, int a3,
	int level, int tableIndex, unsigned char *source, unsigned char *destination,
	unsigned char *a8, int a9, int a10)
{
	ctx->m_mode = mode;
	ctx->m_04 = a3;
	ctx->m_level = level;
	ctx->m_tableIndex = tableIndex;
	ctx->m_source = source;
	ctx->m_destination = destination;
	ctx->m_18 = a8;
	ctx->m_1c = a9;
	ctx->m_20 = a10;

	switch (ctx->m_level)
	{
	case 8:
		FILL(ctx);
		if (ctx->m_mode < 2)
		{
			AF200(ctx, ctx->m_source, ctx->m_destination);
		}
		else if (ctx->m_6c && ctx->m_c0)
		{
			B3800(ctx, ctx->m_source, ctx->m_bc);
			unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
			memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_bc + ctx->m_planeU, bytes);
			memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_bc + ctx->m_planeV, bytes);
			g_rva01356E6C(ctx->m_bc + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
				ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
		}
		else
		{
			B3800(ctx, ctx->m_source, ctx->m_destination);
		}
		break;

	case 6:
	case 5:
		if (ctx->m_mode < 5)
			FILL(ctx);
		else if (ctx->m_6c)
		{
			if (!ctx->m_c0)
			{
				AF320(ctx, ctx->m_source, ctx->m_destination);
				Rva009A8C50(ctx, ctx->m_destination);
				Rva009B2A50(ctx, ctx->m_destination, ctx->m_destination);
			}
			else
			{
				AF320(ctx, ctx->m_source, ctx->m_bc);
				Rva009A8C50(ctx, ctx->m_bc);
				Rva009B2A50(ctx, ctx->m_bc, ctx->m_bc);
				unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
				memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_bc + ctx->m_planeU, bytes);
				memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_bc + ctx->m_planeV, bytes);
				g_rva01356E6C(ctx->m_bc + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
					ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
			}
			break;
		}
		AF200(ctx, ctx->m_source, ctx->m_destination);
		Rva009A8C50(ctx, ctx->m_destination);
		Rva009B2530(ctx, ctx->m_destination, ctx->m_destination);
		if (ctx->m_c4)
			g_rva01356E60(ctx->m_destination + ctx->m_planeY, ctx->m_width << 3,
				ctx->m_height << 3, ctx->m_strideY, tableIndex);
		break;

	case 7:
		if (ctx->m_mode >= 5)
		{
			if (ctx->m_6c)
			{
				if (!ctx->m_c0)
				{
					AF320(ctx, ctx->m_source, ctx->m_destination);
				}
				else
				{
					AF320(ctx, ctx->m_source, ctx->m_bc);
					unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
					memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_bc + ctx->m_planeU, bytes);
					memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_bc + ctx->m_planeV, bytes);
					g_rva01356E6C(ctx->m_bc + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
						ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
				}
				break;
			}
		}
		else
			FILL(ctx);
		AF200(ctx, ctx->m_source, ctx->m_destination);
		Rva009A8C50(ctx, ctx->m_destination);
		Rva009B2530(ctx, ctx->m_destination, ctx->m_destination);
		break;

	case 4:
		if (ctx->m_mode >= 5)
		{
			if (ctx->m_6c)
			{
				if (!ctx->m_c0)
				{
					AF320(ctx, ctx->m_source, ctx->m_destination);
				}
				else
				{
					AF320(ctx, ctx->m_source, ctx->m_bc);
					unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
					memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_bc + ctx->m_planeU, bytes);
					memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_bc + ctx->m_planeV, bytes);
					g_rva01356E6C(ctx->m_bc + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
						ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
				}
				break;
			}
		}
		else
			FILL(ctx);
		AF200(ctx, ctx->m_source, ctx->m_destination);
		break;

	case 1:
		FILL(ctx);
		break;

	case 0:
		if (ctx->m_6c && ctx->m_c0)
		{
			unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
			memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_source + ctx->m_planeU, bytes);
			memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_source + ctx->m_planeV, bytes);
			g_rva01356E6C(ctx->m_source + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
				ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
		}
		break;

	case 2:
	case 3:
	default:
		AF200(ctx, ctx->m_source, ctx->m_destination);
		Rva009A8C50(ctx, ctx->m_destination);
		Rva009B2530(ctx, ctx->m_destination, ctx->m_destination);
		break;
	}
}
