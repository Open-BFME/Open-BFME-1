// cl: /DNDEBUG /MD /EHsc
// GameLogic::getFirstObject, retail 0x00383090 (7 bytes, ILT 0x000358BE).
//
// Identity: tools/ilt_oracle.py confirms ?getFirstObject@GameLogic@@QAEPAVObject@@XZ
// at ILT 0x000358BE (exact). The body is Zero Hour's `return m_objList;` with
// BFME's object list at GameLogic+0xA8, the offset GameLogicLoadPostProcess.cpp's
// and GameLogicPrepareObjectLoad.cpp's matched views read. GameLogic.cpp's Zero
// Hour copy keeps the Zero Hour offset.

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *getFirstObject();

private:
	unsigned char m_bfmeHead[0xA8];
	Object *m_objList;	// +0xA8
};

Object *GameLogic::getFirstObject()
{
	return m_objList;
}
