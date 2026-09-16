// ?d_008bf100@@YAXXZ
// partial score=0.2615 date=2026-09-16
// ?d_008bf100@@YAXXZ -> address-derived APT registry initializer.
// The retail body consumes one hash-bucket count argument at [esp+4].
//
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" void *__cdecl memset(void *destination, int value,
	unsigned int count);
#pragma intrinsic(memset)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeStringData008BF100
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPool008BF100
{
	void *m_unused;
	void (__cdecl *free)(void *data);
};

struct BfmeHashNode008BF100;

extern BfmeStringData008BF100 g_bfmeDefaultString1284;
extern BfmeStringPool008BF100 *g_bfmeStringPool1284;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);
extern BfmeHashNode008BF100 **g_bfmeHashArr3AF0;
extern int g_bfmeHashCount3AF0;

class BfmeStrVKI
{
	public:
	BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}

	BfmeStrVKI(const BfmeStrVKI &other)
	{
		m_data = other.m_data;
		++m_data->m_refCount;
	}

	~BfmeStrVKI()
	{
		BfmeStringData008BF100 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeStrVKI &operator=(const BfmeStrVKI &other)
	{
		++other.m_data->m_refCount;
		BfmeStringData008BF100 *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
		m_data = other.m_data;
		return *this;
	}

	void bfmeSetVKI(const char *text);

	BfmeStringData008BF100 *m_data;
};

extern BfmeStringData008BF100 g_bfmeRouteKeysRaw008BF100[0xb2];
#define g_bfmeRouteKeys1282 (*reinterpret_cast<BfmeStrVKI (*)[0xb2]>(g_bfmeRouteKeysRaw008BF100))

void d_008bf100(int hashCount)
{
	// The compiler owns one temporary per assignment; these are the retail slots.

	BfmeStringData008BF100 **slot =
		reinterpret_cast<BfmeStringData008BF100 **>(g_bfmeRouteKeys1282) + 1;
	do
	{
		BfmeStringData008BF100 *data = slot[-1];
		if (data == 0)
		{
			slot[-1] = &g_bfmeDefaultString1284;
			_ReadWriteBarrier();
			++g_bfmeDefaultString1284.m_refCount;
		}
		data = slot[0];
		if (data == 0)
		{
			slot[0] = &g_bfmeDefaultString1284;
			_ReadWriteBarrier();
			++g_bfmeDefaultString1284.m_refCount;
		}
		++slot;
		++slot;
	} while ((int)slot < (int)(void *)
		reinterpret_cast<BfmeStringData008BF100 **>(g_bfmeRouteKeys1282) + 0xb3);

g_bfmeRouteKeys1282[0] = BfmeStrVKI("__proto__");
g_bfmeRouteKeys1282[1] = BfmeStrVKI("_alpha");
g_bfmeRouteKeys1282[2] = BfmeStrVKI("_currentframe");
g_bfmeRouteKeys1282[3] = BfmeStrVKI("_down");
g_bfmeRouteKeys1282[4] = BfmeStrVKI("_droptarget");
g_bfmeRouteKeys1282[5] = BfmeStrVKI("_focusrect");
g_bfmeRouteKeys1282[6] = BfmeStrVKI("_framesloaded");
g_bfmeRouteKeys1282[7] = BfmeStrVKI("_global");
g_bfmeRouteKeys1282[8] = BfmeStrVKI("_height");
g_bfmeRouteKeys1282[9] = BfmeStrVKI("_highquality");
g_bfmeRouteKeys1282[10] = BfmeStrVKI("_left");
g_bfmeRouteKeys1282[11] = BfmeStrVKI("_name");
g_bfmeRouteKeys1282[12] = BfmeStrVKI("_quality");
g_bfmeRouteKeys1282[13] = BfmeStrVKI("_right");
g_bfmeRouteKeys1282[14] = BfmeStrVKI("_rotation");
g_bfmeRouteKeys1282[15] = BfmeStrVKI("_soundbuftime");
g_bfmeRouteKeys1282[16] = BfmeStrVKI("_target");
g_bfmeRouteKeys1282[17] = BfmeStrVKI("_totalframes");
g_bfmeRouteKeys1282[18] = BfmeStrVKI("_type");
g_bfmeRouteKeys1282[19] = BfmeStrVKI("_up");
g_bfmeRouteKeys1282[20] = BfmeStrVKI("_url");
g_bfmeRouteKeys1282[21] = BfmeStrVKI("_visible");
g_bfmeRouteKeys1282[22] = BfmeStrVKI("_width");
g_bfmeRouteKeys1282[23] = BfmeStrVKI("_x");
g_bfmeRouteKeys1282[24] = BfmeStrVKI("_xmouse");
g_bfmeRouteKeys1282[25] = BfmeStrVKI("_xscale");
g_bfmeRouteKeys1282[26] = BfmeStrVKI("_y");
g_bfmeRouteKeys1282[27] = BfmeStrVKI("_ymouse");
g_bfmeRouteKeys1282[28] = BfmeStrVKI("_yscale");
g_bfmeRouteKeys1282[29] = BfmeStrVKI("aa");
g_bfmeRouteKeys1282[30] = BfmeStrVKI("ab");
g_bfmeRouteKeys1282[31] = BfmeStrVKI("abs");
g_bfmeRouteKeys1282[32] = BfmeStrVKI("acos");
g_bfmeRouteKeys1282[33] = BfmeStrVKI("Array");
g_bfmeRouteKeys1282[34] = BfmeStrVKI("asin");
g_bfmeRouteKeys1282[35] = BfmeStrVKI("atan");
g_bfmeRouteKeys1282[36] = BfmeStrVKI("atan2");
g_bfmeRouteKeys1282[37] = BfmeStrVKI("ba");
g_bfmeRouteKeys1282[38] = BfmeStrVKI("bb");
g_bfmeRouteKeys1282[39] = BfmeStrVKI("boolean");
g_bfmeRouteKeys1282[40] = BfmeStrVKI("ceil");
g_bfmeRouteKeys1282[41] = BfmeStrVKI("center");
g_bfmeRouteKeys1282[42] = BfmeStrVKI("charAt");
g_bfmeRouteKeys1282[43] = BfmeStrVKI("charCodeAt");
g_bfmeRouteKeys1282[44] = BfmeStrVKI("Color");
g_bfmeRouteKeys1282[45] = BfmeStrVKI("concat");
g_bfmeRouteKeys1282[46] = BfmeStrVKI("contentType");
g_bfmeRouteKeys1282[47] = BfmeStrVKI("controller");
g_bfmeRouteKeys1282[48] = BfmeStrVKI("cos");
g_bfmeRouteKeys1282[49] = BfmeStrVKI("Date");
g_bfmeRouteKeys1282[50] = BfmeStrVKI("Error");
g_bfmeRouteKeys1282[51] = BfmeStrVKI("exp");
g_bfmeRouteKeys1282[52] = BfmeStrVKI("false");
g_bfmeRouteKeys1282[53] = BfmeStrVKI("floor");
g_bfmeRouteKeys1282[54] = BfmeStrVKI("fromCharCode");
g_bfmeRouteKeys1282[55] = BfmeStrVKI("function");
g_bfmeRouteKeys1282[56] = BfmeStrVKI("fXAxisValue");
g_bfmeRouteKeys1282[57] = BfmeStrVKI("fYAxisValue");
g_bfmeRouteKeys1282[58] = BfmeStrVKI("ga");
g_bfmeRouteKeys1282[59] = BfmeStrVKI("gb");
g_bfmeRouteKeys1282[60] = BfmeStrVKI("getBytesLoaded");
g_bfmeRouteKeys1282[61] = BfmeStrVKI("getBytesTotal");
g_bfmeRouteKeys1282[62] = BfmeStrVKI("getDate");
g_bfmeRouteKeys1282[63] = BfmeStrVKI("getDay");
g_bfmeRouteKeys1282[64] = BfmeStrVKI("getFullYear");
g_bfmeRouteKeys1282[65] = BfmeStrVKI("getHours");
g_bfmeRouteKeys1282[66] = BfmeStrVKI("getMilliseconds");
g_bfmeRouteKeys1282[67] = BfmeStrVKI("getMinutes");
g_bfmeRouteKeys1282[68] = BfmeStrVKI("getMonth");
g_bfmeRouteKeys1282[69] = BfmeStrVKI("getRGB");
g_bfmeRouteKeys1282[70] = BfmeStrVKI("getSeconds");
g_bfmeRouteKeys1282[71] = BfmeStrVKI("getTime");
g_bfmeRouteKeys1282[72] = BfmeStrVKI("getTimezoneOffset");
g_bfmeRouteKeys1282[73] = BfmeStrVKI("getTransform");
g_bfmeRouteKeys1282[74] = BfmeStrVKI("getUTCDate");
g_bfmeRouteKeys1282[75] = BfmeStrVKI("getUTCDay");
g_bfmeRouteKeys1282[76] = BfmeStrVKI("getUTCFullYear");
g_bfmeRouteKeys1282[77] = BfmeStrVKI("getUTCHours");
g_bfmeRouteKeys1282[78] = BfmeStrVKI("getUTCMilliseconds");
g_bfmeRouteKeys1282[79] = BfmeStrVKI("getUTCMinutes");
g_bfmeRouteKeys1282[80] = BfmeStrVKI("getUTCMonth");
g_bfmeRouteKeys1282[81] = BfmeStrVKI("getUTCSeconds");
g_bfmeRouteKeys1282[82] = BfmeStrVKI("getYear");
g_bfmeRouteKeys1282[83] = BfmeStrVKI("indexOf");
g_bfmeRouteKeys1282[84] = BfmeStrVKI("join");
g_bfmeRouteKeys1282[85] = BfmeStrVKI("lastIndexOf");
g_bfmeRouteKeys1282[86] = BfmeStrVKI("left");
g_bfmeRouteKeys1282[87] = BfmeStrVKI("length");
g_bfmeRouteKeys1282[88] = BfmeStrVKI("load");
g_bfmeRouteKeys1282[89] = BfmeStrVKI("loaded");
g_bfmeRouteKeys1282[90] = BfmeStrVKI("LoadVars");
g_bfmeRouteKeys1282[91] = BfmeStrVKI("log");
g_bfmeRouteKeys1282[92] = BfmeStrVKI("max");
g_bfmeRouteKeys1282[93] = BfmeStrVKI("min");
g_bfmeRouteKeys1282[94] = BfmeStrVKI("movieclip");
g_bfmeRouteKeys1282[95] = BfmeStrVKI("NodeName");
g_bfmeRouteKeys1282[96] = BfmeStrVKI("NodeValue");
g_bfmeRouteKeys1282[97] = BfmeStrVKI("none");
g_bfmeRouteKeys1282[98] = BfmeStrVKI("null");
g_bfmeRouteKeys1282[99] = BfmeStrVKI("number");
g_bfmeRouteKeys1282[100] = BfmeStrVKI("object");
g_bfmeRouteKeys1282[101] = BfmeStrVKI("onData");
g_bfmeRouteKeys1282[102] = BfmeStrVKI("onDragOut");
g_bfmeRouteKeys1282[103] = BfmeStrVKI("onDragOver");
g_bfmeRouteKeys1282[104] = BfmeStrVKI("onEnterFrame");
g_bfmeRouteKeys1282[105] = BfmeStrVKI("onKeyDown");
g_bfmeRouteKeys1282[106] = BfmeStrVKI("onKeyUp");
g_bfmeRouteKeys1282[107] = BfmeStrVKI("onLoad");
g_bfmeRouteKeys1282[108] = BfmeStrVKI("onMouseDown");
g_bfmeRouteKeys1282[109] = BfmeStrVKI("onMouseMove");
g_bfmeRouteKeys1282[110] = BfmeStrVKI("onMouseUp");
g_bfmeRouteKeys1282[111] = BfmeStrVKI("onMouseWheel");
g_bfmeRouteKeys1282[112] = BfmeStrVKI("onPress");
g_bfmeRouteKeys1282[113] = BfmeStrVKI("onRelease");
g_bfmeRouteKeys1282[114] = BfmeStrVKI("onReleaseOutside");
g_bfmeRouteKeys1282[115] = BfmeStrVKI("onRollOut");
g_bfmeRouteKeys1282[116] = BfmeStrVKI("onRollOver");
g_bfmeRouteKeys1282[117] = BfmeStrVKI("onUnload");
g_bfmeRouteKeys1282[118] = BfmeStrVKI("pop");
g_bfmeRouteKeys1282[119] = BfmeStrVKI("pow");
g_bfmeRouteKeys1282[120] = BfmeStrVKI("prototype");
g_bfmeRouteKeys1282[121] = BfmeStrVKI("push");
g_bfmeRouteKeys1282[122] = BfmeStrVKI("ra");
g_bfmeRouteKeys1282[123] = BfmeStrVKI("random");
g_bfmeRouteKeys1282[124] = BfmeStrVKI("rb");
g_bfmeRouteKeys1282[125] = BfmeStrVKI("reverse");
g_bfmeRouteKeys1282[126] = BfmeStrVKI("right");
g_bfmeRouteKeys1282[127] = BfmeStrVKI("round");
g_bfmeRouteKeys1282[128] = BfmeStrVKI("send");
g_bfmeRouteKeys1282[129] = BfmeStrVKI("sendAndLoad");
g_bfmeRouteKeys1282[130] = BfmeStrVKI("setDate");
g_bfmeRouteKeys1282[131] = BfmeStrVKI("setFullYear");
g_bfmeRouteKeys1282[132] = BfmeStrVKI("setHours");
g_bfmeRouteKeys1282[133] = BfmeStrVKI("setMilliseconds");
g_bfmeRouteKeys1282[134] = BfmeStrVKI("setMinutes");
g_bfmeRouteKeys1282[135] = BfmeStrVKI("setMonth");
g_bfmeRouteKeys1282[136] = BfmeStrVKI("setRGB");
g_bfmeRouteKeys1282[137] = BfmeStrVKI("setSeconds");
g_bfmeRouteKeys1282[138] = BfmeStrVKI("setTime");
g_bfmeRouteKeys1282[139] = BfmeStrVKI("setTransform");
g_bfmeRouteKeys1282[140] = BfmeStrVKI("setUTCDate");
g_bfmeRouteKeys1282[141] = BfmeStrVKI("setUTCFullYear");
g_bfmeRouteKeys1282[142] = BfmeStrVKI("setUTCHours");
g_bfmeRouteKeys1282[143] = BfmeStrVKI("setUTCMilliseconds");
g_bfmeRouteKeys1282[144] = BfmeStrVKI("setUTCMinutes");
g_bfmeRouteKeys1282[145] = BfmeStrVKI("setUTCMonth");
g_bfmeRouteKeys1282[146] = BfmeStrVKI("setUTCSeconds");
g_bfmeRouteKeys1282[147] = BfmeStrVKI("setYear");
g_bfmeRouteKeys1282[148] = BfmeStrVKI("shift");
g_bfmeRouteKeys1282[149] = BfmeStrVKI("sin");
g_bfmeRouteKeys1282[150] = BfmeStrVKI("slice");
g_bfmeRouteKeys1282[151] = BfmeStrVKI("sort");
g_bfmeRouteKeys1282[152] = BfmeStrVKI("sortOn");
g_bfmeRouteKeys1282[153] = BfmeStrVKI("Sound");
g_bfmeRouteKeys1282[154] = BfmeStrVKI("splice");
g_bfmeRouteKeys1282[155] = BfmeStrVKI("split");
g_bfmeRouteKeys1282[156] = BfmeStrVKI("sqrt");
g_bfmeRouteKeys1282[157] = BfmeStrVKI("string");
g_bfmeRouteKeys1282[158] = BfmeStrVKI("substr");
g_bfmeRouteKeys1282[159] = BfmeStrVKI("substring");
g_bfmeRouteKeys1282[160] = BfmeStrVKI("super");
g_bfmeRouteKeys1282[161] = BfmeStrVKI("tan");
g_bfmeRouteKeys1282[162] = BfmeStrVKI("target");
g_bfmeRouteKeys1282[163] = BfmeStrVKI("TextFormat");
g_bfmeRouteKeys1282[164] = BfmeStrVKI("this");
g_bfmeRouteKeys1282[165] = BfmeStrVKI("toLowerCase");
g_bfmeRouteKeys1282[166] = BfmeStrVKI("toString");
g_bfmeRouteKeys1282[167] = BfmeStrVKI("toUpperCase");
g_bfmeRouteKeys1282[168] = BfmeStrVKI("true");
g_bfmeRouteKeys1282[169] = BfmeStrVKI("undefined");
g_bfmeRouteKeys1282[170] = BfmeStrVKI("undefKey");
g_bfmeRouteKeys1282[171] = BfmeStrVKI("unshift");
g_bfmeRouteKeys1282[172] = BfmeStrVKI("UTC");
g_bfmeRouteKeys1282[173] = BfmeStrVKI("xMax");
g_bfmeRouteKeys1282[174] = BfmeStrVKI("xMin");
g_bfmeRouteKeys1282[175] = BfmeStrVKI("XML");
g_bfmeRouteKeys1282[176] = BfmeStrVKI("yMax");
g_bfmeRouteKeys1282[177] = BfmeStrVKI("yMin");

	g_bfmeHashArr3AF0 = (BfmeHashNode008BF100 **)Rva008C5D70Alloc(hashCount * 4);
	memset(g_bfmeHashArr3AF0, 0, hashCount * 4);
	g_bfmeHashCount3AF0 = hashCount;
}
