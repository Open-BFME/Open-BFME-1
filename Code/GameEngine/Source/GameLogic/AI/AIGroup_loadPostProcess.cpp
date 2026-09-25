// cl: /DNDEBUG /MD /EHsc
// AIGroup::loadPostProcess, retail 0x00151CF0: slot 1 of AIGroup's vftable
// 0x01095F24, BFME's Snapshot loadPostProcess slot. Zero Hour's body is empty;
// AI.h declares it in AIGroup's public section, overriding Snapshot's virtual.
class AIGroup
{
public:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@AIGroup@@UAEXXZ
void AIGroup::loadPostProcess(void)
{
}  // end loadPostProcess
