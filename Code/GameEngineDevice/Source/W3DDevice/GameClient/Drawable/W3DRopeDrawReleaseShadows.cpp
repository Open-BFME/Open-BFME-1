// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DRopeDraw.h
class W3DRopeDraw
{
public:
	virtual void releaseShadows();
};

// W3DRopeDraw's primary vtable slot points through ILT 0x0000EDBD to
// 0x0075A560. Rope lines have no shadow resources to release.
void W3DRopeDraw::releaseShadows()
{
}
