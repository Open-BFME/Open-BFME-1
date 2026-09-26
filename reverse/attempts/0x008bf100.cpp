// ?d_008bf100@@YAXXZ
// partial score=0.9991959260251944 date=2026-09-26
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-derived APT registry initializer; reconstructed ABI consumes one int.
// Probe symbol: ?d_008bf100@@YAXH@Z (the dump ledger still has the no-arg name).
// Near match: 18655 bytes, 1080 relocations, 15 reported non-relocation differences,
// and one relocation-layout mismatch at the first temporary cleanup (+0x9A..+0xAD).
// EDI is saved at +0x9A instead of retail +0xAD; both streams rejoin at +0xAE.
// Preserve the fallthrough cases, independent lifetimes, forceinline releases,
// four barrier sites, and signed table+0x2CC loop bound.
// See docs/whales.md and reverse/attempt_history/0x008bf100/2026-09-26-index.md.
// These are measured reconstruction techniques, not proof of original source.

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

	__forceinline ~BfmeStrVKI()
	{
		BfmeStringData008BF100 *data = m_data;
		_ReadWriteBarrier();
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	__forceinline BfmeStrVKI &operator=(const BfmeStrVKI &other)
	{
		++other.m_data->m_refCount;
		BfmeStringData008BF100 *old = m_data;
		_ReadWriteBarrier();
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
		reinterpret_cast<BfmeStringData008BF100 **>(g_bfmeRouteKeys1282) + (0xb3 * 4));

    // Compile-only shape experiment, not a claim about the original source.
    // Constant entry; every case intentionally falls through to the next.
    switch (0)
    {
    case 0:
        g_bfmeRouteKeys1282[0] = BfmeStrVKI("__proto__");
    case 1:
        g_bfmeRouteKeys1282[1] = BfmeStrVKI("_alpha");
    case 2:
        g_bfmeRouteKeys1282[2] = BfmeStrVKI("_currentframe");
    case 3:
        g_bfmeRouteKeys1282[3] = BfmeStrVKI("_down");
    case 4:
        g_bfmeRouteKeys1282[4] = BfmeStrVKI("_droptarget");
    case 5:
        g_bfmeRouteKeys1282[5] = BfmeStrVKI("_focusrect");
    case 6:
        g_bfmeRouteKeys1282[6] = BfmeStrVKI("_framesloaded");
    case 7:
        g_bfmeRouteKeys1282[7] = BfmeStrVKI("_global");
    case 8:
        g_bfmeRouteKeys1282[8] = BfmeStrVKI("_height");
    case 9:
        g_bfmeRouteKeys1282[9] = BfmeStrVKI("_highquality");
    case 10:
        g_bfmeRouteKeys1282[10] = BfmeStrVKI("_left");
    case 11:
        g_bfmeRouteKeys1282[11] = BfmeStrVKI("_name");
    case 12:
        g_bfmeRouteKeys1282[12] = BfmeStrVKI("_quality");
    case 13:
        g_bfmeRouteKeys1282[13] = BfmeStrVKI("_right");
    case 14:
        g_bfmeRouteKeys1282[14] = BfmeStrVKI("_rotation");
    case 15:
        g_bfmeRouteKeys1282[15] = BfmeStrVKI("_soundbuftime");
    case 16:
        g_bfmeRouteKeys1282[16] = BfmeStrVKI("_target");
    case 17:
        g_bfmeRouteKeys1282[17] = BfmeStrVKI("_totalframes");
    case 18:
        g_bfmeRouteKeys1282[18] = BfmeStrVKI("_type");
    case 19:
        g_bfmeRouteKeys1282[19] = BfmeStrVKI("_up");
    case 20:
        g_bfmeRouteKeys1282[20] = BfmeStrVKI("_url");
    case 21:
        g_bfmeRouteKeys1282[21] = BfmeStrVKI("_visible");
    case 22:
        g_bfmeRouteKeys1282[22] = BfmeStrVKI("_width");
    case 23:
        g_bfmeRouteKeys1282[23] = BfmeStrVKI("_x");
    case 24:
        g_bfmeRouteKeys1282[24] = BfmeStrVKI("_xmouse");
    case 25:
        g_bfmeRouteKeys1282[25] = BfmeStrVKI("_xscale");
    case 26:
        g_bfmeRouteKeys1282[26] = BfmeStrVKI("_y");
    case 27:
        g_bfmeRouteKeys1282[27] = BfmeStrVKI("_ymouse");
    case 28:
        g_bfmeRouteKeys1282[28] = BfmeStrVKI("_yscale");
    case 29:
        g_bfmeRouteKeys1282[29] = BfmeStrVKI("aa");
    case 30:
        g_bfmeRouteKeys1282[30] = BfmeStrVKI("ab");
    case 31:
        g_bfmeRouteKeys1282[31] = BfmeStrVKI("abs");
    case 32:
        g_bfmeRouteKeys1282[32] = BfmeStrVKI("acos");
    case 33:
        g_bfmeRouteKeys1282[33] = BfmeStrVKI("Array");
    case 34:
        g_bfmeRouteKeys1282[34] = BfmeStrVKI("asin");
    case 35:
        g_bfmeRouteKeys1282[35] = BfmeStrVKI("atan");
    case 36:
        g_bfmeRouteKeys1282[36] = BfmeStrVKI("atan2");
    case 37:
        g_bfmeRouteKeys1282[37] = BfmeStrVKI("ba");
    case 38:
        g_bfmeRouteKeys1282[38] = BfmeStrVKI("bb");
    case 39:
        g_bfmeRouteKeys1282[39] = BfmeStrVKI("boolean");
    case 40:
        g_bfmeRouteKeys1282[40] = BfmeStrVKI("ceil");
    case 41:
        g_bfmeRouteKeys1282[41] = BfmeStrVKI("center");
    case 42:
        g_bfmeRouteKeys1282[42] = BfmeStrVKI("charAt");
    case 43:
        g_bfmeRouteKeys1282[43] = BfmeStrVKI("charCodeAt");
    case 44:
        g_bfmeRouteKeys1282[44] = BfmeStrVKI("Color");
    case 45:
        g_bfmeRouteKeys1282[45] = BfmeStrVKI("concat");
    case 46:
        g_bfmeRouteKeys1282[46] = BfmeStrVKI("contentType");
    case 47:
        g_bfmeRouteKeys1282[47] = BfmeStrVKI("controller");
    case 48:
        g_bfmeRouteKeys1282[48] = BfmeStrVKI("cos");
    case 49:
        g_bfmeRouteKeys1282[49] = BfmeStrVKI("Date");
    case 50:
        g_bfmeRouteKeys1282[50] = BfmeStrVKI("Error");
    case 51:
        g_bfmeRouteKeys1282[51] = BfmeStrVKI("exp");
    case 52:
        g_bfmeRouteKeys1282[52] = BfmeStrVKI("false");
    case 53:
        g_bfmeRouteKeys1282[53] = BfmeStrVKI("floor");
    case 54:
        g_bfmeRouteKeys1282[54] = BfmeStrVKI("fromCharCode");
    case 55:
        g_bfmeRouteKeys1282[55] = BfmeStrVKI("function");
    case 56:
        g_bfmeRouteKeys1282[56] = BfmeStrVKI("fXAxisValue");
    case 57:
        g_bfmeRouteKeys1282[57] = BfmeStrVKI("fYAxisValue");
    case 58:
        g_bfmeRouteKeys1282[58] = BfmeStrVKI("ga");
    case 59:
        g_bfmeRouteKeys1282[59] = BfmeStrVKI("gb");
    case 60:
        g_bfmeRouteKeys1282[60] = BfmeStrVKI("getBytesLoaded");
    case 61:
        g_bfmeRouteKeys1282[61] = BfmeStrVKI("getBytesTotal");
    case 62:
        g_bfmeRouteKeys1282[62] = BfmeStrVKI("getDate");
    case 63:
        g_bfmeRouteKeys1282[63] = BfmeStrVKI("getDay");
    case 64:
        g_bfmeRouteKeys1282[64] = BfmeStrVKI("getFullYear");
    case 65:
        g_bfmeRouteKeys1282[65] = BfmeStrVKI("getHours");
    case 66:
        g_bfmeRouteKeys1282[66] = BfmeStrVKI("getMilliseconds");
    case 67:
        g_bfmeRouteKeys1282[67] = BfmeStrVKI("getMinutes");
    case 68:
        g_bfmeRouteKeys1282[68] = BfmeStrVKI("getMonth");
    case 69:
        g_bfmeRouteKeys1282[69] = BfmeStrVKI("getRGB");
    case 70:
        g_bfmeRouteKeys1282[70] = BfmeStrVKI("getSeconds");
    case 71:
        g_bfmeRouteKeys1282[71] = BfmeStrVKI("getTime");
    case 72:
        g_bfmeRouteKeys1282[72] = BfmeStrVKI("getTimezoneOffset");
    case 73:
        g_bfmeRouteKeys1282[73] = BfmeStrVKI("getTransform");
    case 74:
        g_bfmeRouteKeys1282[74] = BfmeStrVKI("getUTCDate");
    case 75:
        g_bfmeRouteKeys1282[75] = BfmeStrVKI("getUTCDay");
    case 76:
        g_bfmeRouteKeys1282[76] = BfmeStrVKI("getUTCFullYear");
    case 77:
        g_bfmeRouteKeys1282[77] = BfmeStrVKI("getUTCHours");
    case 78:
        g_bfmeRouteKeys1282[78] = BfmeStrVKI("getUTCMilliseconds");
    case 79:
        g_bfmeRouteKeys1282[79] = BfmeStrVKI("getUTCMinutes");
    case 80:
        g_bfmeRouteKeys1282[80] = BfmeStrVKI("getUTCMonth");
    case 81:
        g_bfmeRouteKeys1282[81] = BfmeStrVKI("getUTCSeconds");
    case 82:
        g_bfmeRouteKeys1282[82] = BfmeStrVKI("getYear");
    case 83:
        g_bfmeRouteKeys1282[83] = BfmeStrVKI("indexOf");
    case 84:
        g_bfmeRouteKeys1282[84] = BfmeStrVKI("join");
    case 85:
        g_bfmeRouteKeys1282[85] = BfmeStrVKI("lastIndexOf");
    case 86:
        g_bfmeRouteKeys1282[86] = BfmeStrVKI("left");
    case 87:
        g_bfmeRouteKeys1282[87] = BfmeStrVKI("length");
    case 88:
        g_bfmeRouteKeys1282[88] = BfmeStrVKI("load");
    case 89:
        g_bfmeRouteKeys1282[89] = BfmeStrVKI("loaded");
    case 90:
        g_bfmeRouteKeys1282[90] = BfmeStrVKI("LoadVars");
    case 91:
        g_bfmeRouteKeys1282[91] = BfmeStrVKI("log");
    case 92:
        g_bfmeRouteKeys1282[92] = BfmeStrVKI("max");
    case 93:
        g_bfmeRouteKeys1282[93] = BfmeStrVKI("min");
    case 94:
        g_bfmeRouteKeys1282[94] = BfmeStrVKI("movieclip");
    case 95:
        g_bfmeRouteKeys1282[95] = BfmeStrVKI("NodeName");
    case 96:
        g_bfmeRouteKeys1282[96] = BfmeStrVKI("NodeValue");
    case 97:
        g_bfmeRouteKeys1282[97] = BfmeStrVKI("none");
    case 98:
        g_bfmeRouteKeys1282[98] = BfmeStrVKI("null");
    case 99:
        g_bfmeRouteKeys1282[99] = BfmeStrVKI("number");
    case 100:
        g_bfmeRouteKeys1282[100] = BfmeStrVKI("object");
    case 101:
        g_bfmeRouteKeys1282[101] = BfmeStrVKI("onData");
    case 102:
        g_bfmeRouteKeys1282[102] = BfmeStrVKI("onDragOut");
    case 103:
        g_bfmeRouteKeys1282[103] = BfmeStrVKI("onDragOver");
    case 104:
        g_bfmeRouteKeys1282[104] = BfmeStrVKI("onEnterFrame");
    case 105:
        g_bfmeRouteKeys1282[105] = BfmeStrVKI("onKeyDown");
    case 106:
        g_bfmeRouteKeys1282[106] = BfmeStrVKI("onKeyUp");
    case 107:
        g_bfmeRouteKeys1282[107] = BfmeStrVKI("onLoad");
    case 108:
        g_bfmeRouteKeys1282[108] = BfmeStrVKI("onMouseDown");
    case 109:
        g_bfmeRouteKeys1282[109] = BfmeStrVKI("onMouseMove");
    case 110:
        g_bfmeRouteKeys1282[110] = BfmeStrVKI("onMouseUp");
    case 111:
        g_bfmeRouteKeys1282[111] = BfmeStrVKI("onMouseWheel");
    case 112:
        g_bfmeRouteKeys1282[112] = BfmeStrVKI("onPress");
    case 113:
        g_bfmeRouteKeys1282[113] = BfmeStrVKI("onRelease");
    case 114:
        g_bfmeRouteKeys1282[114] = BfmeStrVKI("onReleaseOutside");
    case 115:
        g_bfmeRouteKeys1282[115] = BfmeStrVKI("onRollOut");
    case 116:
        g_bfmeRouteKeys1282[116] = BfmeStrVKI("onRollOver");
    case 117:
        g_bfmeRouteKeys1282[117] = BfmeStrVKI("onUnload");
    case 118:
        g_bfmeRouteKeys1282[118] = BfmeStrVKI("pop");
    case 119:
        g_bfmeRouteKeys1282[119] = BfmeStrVKI("pow");
    case 120:
        g_bfmeRouteKeys1282[120] = BfmeStrVKI("prototype");
    case 121:
        g_bfmeRouteKeys1282[121] = BfmeStrVKI("push");
    case 122:
        g_bfmeRouteKeys1282[122] = BfmeStrVKI("ra");
    case 123:
        g_bfmeRouteKeys1282[123] = BfmeStrVKI("random");
    case 124:
        g_bfmeRouteKeys1282[124] = BfmeStrVKI("rb");
    case 125:
        g_bfmeRouteKeys1282[125] = BfmeStrVKI("reverse");
    case 126:
        g_bfmeRouteKeys1282[126] = BfmeStrVKI("right");
    case 127:
        g_bfmeRouteKeys1282[127] = BfmeStrVKI("round");
    case 128:
        g_bfmeRouteKeys1282[128] = BfmeStrVKI("send");
    case 129:
        g_bfmeRouteKeys1282[129] = BfmeStrVKI("sendAndLoad");
    case 130:
        g_bfmeRouteKeys1282[130] = BfmeStrVKI("setDate");
    case 131:
        g_bfmeRouteKeys1282[131] = BfmeStrVKI("setFullYear");
    case 132:
        g_bfmeRouteKeys1282[132] = BfmeStrVKI("setHours");
    case 133:
        g_bfmeRouteKeys1282[133] = BfmeStrVKI("setMilliseconds");
    case 134:
        g_bfmeRouteKeys1282[134] = BfmeStrVKI("setMinutes");
    case 135:
        g_bfmeRouteKeys1282[135] = BfmeStrVKI("setMonth");
    case 136:
        g_bfmeRouteKeys1282[136] = BfmeStrVKI("setRGB");
    case 137:
        g_bfmeRouteKeys1282[137] = BfmeStrVKI("setSeconds");
    case 138:
        g_bfmeRouteKeys1282[138] = BfmeStrVKI("setTime");
    case 139:
        g_bfmeRouteKeys1282[139] = BfmeStrVKI("setTransform");
    case 140:
        g_bfmeRouteKeys1282[140] = BfmeStrVKI("setUTCDate");
    case 141:
        g_bfmeRouteKeys1282[141] = BfmeStrVKI("setUTCFullYear");
    case 142:
        g_bfmeRouteKeys1282[142] = BfmeStrVKI("setUTCHours");
    case 143:
        g_bfmeRouteKeys1282[143] = BfmeStrVKI("setUTCMilliseconds");
    case 144:
        g_bfmeRouteKeys1282[144] = BfmeStrVKI("setUTCMinutes");
    case 145:
        g_bfmeRouteKeys1282[145] = BfmeStrVKI("setUTCMonth");
    case 146:
        g_bfmeRouteKeys1282[146] = BfmeStrVKI("setUTCSeconds");
    case 147:
        g_bfmeRouteKeys1282[147] = BfmeStrVKI("setYear");
    case 148:
        g_bfmeRouteKeys1282[148] = BfmeStrVKI("shift");
    case 149:
        g_bfmeRouteKeys1282[149] = BfmeStrVKI("sin");
    case 150:
        g_bfmeRouteKeys1282[150] = BfmeStrVKI("slice");
    case 151:
        g_bfmeRouteKeys1282[151] = BfmeStrVKI("sort");
    case 152:
        g_bfmeRouteKeys1282[152] = BfmeStrVKI("sortOn");
    case 153:
        g_bfmeRouteKeys1282[153] = BfmeStrVKI("Sound");
    case 154:
        g_bfmeRouteKeys1282[154] = BfmeStrVKI("splice");
    case 155:
        g_bfmeRouteKeys1282[155] = BfmeStrVKI("split");
    case 156:
        g_bfmeRouteKeys1282[156] = BfmeStrVKI("sqrt");
    case 157:
        g_bfmeRouteKeys1282[157] = BfmeStrVKI("string");
    case 158:
        g_bfmeRouteKeys1282[158] = BfmeStrVKI("substr");
    case 159:
        g_bfmeRouteKeys1282[159] = BfmeStrVKI("substring");
    case 160:
        g_bfmeRouteKeys1282[160] = BfmeStrVKI("super");
    case 161:
        g_bfmeRouteKeys1282[161] = BfmeStrVKI("tan");
    case 162:
        g_bfmeRouteKeys1282[162] = BfmeStrVKI("target");
    case 163:
        g_bfmeRouteKeys1282[163] = BfmeStrVKI("TextFormat");
    case 164:
        g_bfmeRouteKeys1282[164] = BfmeStrVKI("this");
    case 165:
        g_bfmeRouteKeys1282[165] = BfmeStrVKI("toLowerCase");
    case 166:
        g_bfmeRouteKeys1282[166] = BfmeStrVKI("toString");
    case 167:
        g_bfmeRouteKeys1282[167] = BfmeStrVKI("toUpperCase");
    case 168:
        g_bfmeRouteKeys1282[168] = BfmeStrVKI("true");
    case 169:
        g_bfmeRouteKeys1282[169] = BfmeStrVKI("undefined");
    case 170:
        g_bfmeRouteKeys1282[170] = BfmeStrVKI("undefKey");
    case 171:
        g_bfmeRouteKeys1282[171] = BfmeStrVKI("unshift");
    case 172:
        g_bfmeRouteKeys1282[172] = BfmeStrVKI("UTC");
    case 173:
        g_bfmeRouteKeys1282[173] = BfmeStrVKI("xMax");
    case 174:
        g_bfmeRouteKeys1282[174] = BfmeStrVKI("xMin");
    case 175:
        g_bfmeRouteKeys1282[175] = BfmeStrVKI("XML");
    case 176:
        g_bfmeRouteKeys1282[176] = BfmeStrVKI("yMax");
    case 177:
        g_bfmeRouteKeys1282[177] = BfmeStrVKI("yMin");
        break;
    default:
        break;
    }

	g_bfmeHashArr3AF0 = (BfmeHashNode008BF100 **)Rva008C5D70Alloc(hashCount * 4);
	memset(g_bfmeHashArr3AF0, 0, hashCount * 4);
	g_bfmeHashCount3AF0 = hashCount;
}
