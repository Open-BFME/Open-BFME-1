class ClientRoot4120
{
public:
	unsigned char m_bfmeHeadETH[0xbc];
	char m_bfmeFlagAETH;
	char m_bfmeFlagBETH;
};

// The 0x012F1464 global is EA's `GameClient *TheGameClient`, defined once in
// GameClient.cpp; only the pointee type may differ per TU, so it is forward
// declared here and this TU's flag view is applied at the uses.
class GameClient;
extern GameClient *TheGameClient;

class BfmeSubETH
{
public:
	int m_bfmeValETH;
};

// retail calls 0x0073A900 directly, the matched normAngle row
void __fastcall normAngle(float &angle);
#define bfmeNormAngleETH(a) normAngle(a)

// retail ILT 0x00037E16 -> 0x0045B560 is the matched
// SegLineRendererClass::Set_Merge_Abort_Factor row
class SegLineRendererClass
{
public:
	void Set_Merge_Abort_Factor(float factor);
};

// retail ILT 0x000312A0 -> 0x007423B0 is the matched private
// W3DView::setCameraTransform row
class W3DView
{
	friend class BfmeViewETH;
	void setCameraTransform();
};


class BfmeViewETH
{
public:
	void bfmeSetAngleETH(float angle);
	void bfmeApplyETH(BfmeSubETH *sub);

	unsigned char m_bfmeHeadETH[0x0c];
	BfmeSubETH m_bfmeSubETH;
	unsigned char m_bfmePadAETH[0x34];
	char m_bfmeGateETH;
	unsigned char m_bfmePadBETH[0x197];
	char m_bfmeAETH;
	unsigned char m_bfmePadCETH[0x27];
	char m_bfmeBETH;
	unsigned char m_bfmePadDETH[0x23];
	char m_bfmeCETH;
	unsigned char m_bfmePadEETH[0x53];
	char m_bfmeDETH;
	char m_bfmeEETH;
};

void BfmeViewETH::bfmeSetAngleETH(float angle)
{
	if (((ClientRoot4120 *)TheGameClient)->m_bfmeFlagAETH && m_bfmeGateETH)
		return;

	if (((ClientRoot4120 *)TheGameClient)->m_bfmeFlagBETH && m_bfmeGateETH)
		return;

	bfmeNormAngleETH(angle);
	((SegLineRendererClass *)this)->Set_Merge_Abort_Factor(angle);

	m_bfmeAETH = 0;
	m_bfmeBETH = 0;
	m_bfmeDETH = 0;
	m_bfmeCETH = 0;
	m_bfmeEETH = 0;

	((W3DView *)this)->setCameraTransform();
	bfmeApplyETH(&m_bfmeSubETH);
}
