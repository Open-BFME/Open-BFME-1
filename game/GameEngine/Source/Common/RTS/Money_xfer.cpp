// cl: /DNDEBUG /MD /EHsc
// Money::DoXfer (ZH Money::xfer), retail RVA 0x000C8830, 48 bytes (ret 4 at
// +0x2D).
// Identity: Money's vftable 0x01083D18 (installed by the copy constructor
// 0x000E1540) holds ??_GMoney 0x000CD530 in slot 0, loadPostProcess
// 0x000CBAC0 in slot 1, and in slot 3, the BFME Snapshot DoXfer slot, ILT
// 0x00035594, which jumps to this body. tools/ilt_oracle.py check confirms
// ?DoXfer@Money@@MAEXAAVXfer@@@Z (exact). The body is GeneralsMD Money.cpp
// Money::xfer: version 1, then the unsigned money amount at +0x04 (Xfer
// slot 29). It was previously claimed by the opaque placeholder
// ?bfmeSeed@Gen_000C8830@@QAEXPAVBfmeSeedTarget@@@Z in S3SeedPairsShort.cpp.

#include "../System/xfer.h"

#include "../../../Include/Common/ScalarTypes.h"

class Money
{
protected:
	virtual void DoXfer(Xfer &xfer);

private:
	UnsignedInt m_money;
};

struct XferVersion : public Xfer::Version
{
	XferVersion(unsigned char v)
	{
		data[0] = v;
		data[1] = v;
	}
};

// ?DoXfer@Money@@MAEXAAVXfer@@@Z
void Money::DoXfer(Xfer &xfer)
{
	XferVersion version(1);
	xfer == version;

	xfer.xferUnsignedInt(&m_money);
}
