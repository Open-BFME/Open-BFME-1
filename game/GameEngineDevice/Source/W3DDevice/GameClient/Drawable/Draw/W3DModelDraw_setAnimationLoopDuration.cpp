// cl: /DNDEBUG /MD /EHsc
// W3DModelDraw::setAnimationLoopDuration at retail 0x0075C760.

#include "../../../../../../GameEngine/Include/Common/ScalarTypes.h"

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern const Real g_bfmeScaleGI;

class BfmePrimaryGI
{
public:
	void bfmeApplyGI(Real value);
};

class W3DModelDraw
{
public:
	virtual void setAnimationLoopDuration(unsigned int amount);
};

void W3DModelDraw::setAnimationLoopDuration(unsigned int amount)
{
	Real result = (Real)ceil((Real)amount * g_bfmeScaleGI);
	BfmePrimaryGI *primary = (BfmePrimaryGI *)((char *)this - 0xc);
	Real *resultPtr = &result;
	primary->bfmeApplyGI(*resultPtr);
}
