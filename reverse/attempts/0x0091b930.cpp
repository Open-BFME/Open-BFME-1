// ?Check_Texture_Compression_Support@DX8Caps@@AAEXABU_D3DCAPS8@@@Z
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Banked near-miss for Check_Texture_Compression_Support @ 0x0091B930.
// Size 98 exact. Format/+= tail matches Check_Bumpmap_Support. OR of the
// five DXT bytes at +0x1A2 uses al/dl/cl instead of retail's ebx-preloaded
// bl,al,dl,cl then memory OR of +0x1A4.

class StringClass
{
public:
	void Format(const char *format, ...);
	StringClass &operator+=(const StringClass &that);
};

extern StringClass CapsWorkString;

class DX8Caps
{
	void Check_Texture_Compression_Support(const void *caps);
};

struct BFME_DX8Caps_CheckCompressionFields
{
	char pad[0x139];
	bool supportDXTC;
	char padAfterDxtc[0x1a2 - 0x13a];
	bool supportTextureFormatDxt[5];
	char padAfterFormats[0x2a4 - 0x1a7];
	StringClass capsLog;
};

void DX8Caps::Check_Texture_Compression_Support(const void *caps)
{
	BFME_DX8Caps_CheckCompressionFields *retail = (BFME_DX8Caps_CheckCompressionFields *)this;
	retail->supportDXTC = retail->supportTextureFormatDxt[0] |
		retail->supportTextureFormatDxt[1] |
		retail->supportTextureFormatDxt[2] |
		retail->supportTextureFormatDxt[3] |
		retail->supportTextureFormatDxt[4];
	CapsWorkString.Format("Texture compression support: %s\r\n", retail->supportDXTC ? "Yes" : "No");
	retail->capsLog += CapsWorkString;
}
