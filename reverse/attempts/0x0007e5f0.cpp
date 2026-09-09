// ?bfmeRegisterCH@@YAXPAVBfmeOwnerCH@@@Z
// partial score=0.96 date=2026-09-09
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *s) throw();
	__forceinline ~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

	char *m_bfmeDataCH;
};

class BfmeListCH
{
public:
	void bfmeAddCH(const BFMERetailAsciiString &s);
};

class BfmeOwnerCH
{
public:
	unsigned char m_bfmeHeadCH[4];
	BfmeListCH m_bfme04CH;
};

void bfmeRegisterCH(BfmeOwnerCH *o)
{
	BfmeListCH *l = &o->m_bfme04CH;

	{
		BFMERetailAsciiString s("TextureReduction");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("3DShadows");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("2DShadows");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("UsePixelShader");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("BuildingOcclusion");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("MaxParticleCount");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("DynamicLOD");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("FPSLimit");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("TerrainLighting");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("AnisotropicTextureFiltering");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("SmoothWaterBorder");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("ExtraAnimations");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("GrassDrawSkip");

		l->bfmeAddCH(s);
	}

	{
		BFMERetailAsciiString s("UseHighQualityVideo");

		l->bfmeAddCH(s);
	}

	BFMERetailAsciiString sLastCH("ShowProps");

	l->bfmeAddCH(sLastCH);
}
