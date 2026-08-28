// cl: /DNDEBUG /MD /EHsc
// readable body of ?repairStructure@Player@@UAEXW4ObjectID@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp
// Open-BFME5: Player::repairStructure, retail 0x000C9720, 20 bytes.
//
// The Zero Hour body verbatim -- forward to the AI player when there is one.
// The AI pointer is at this+0x220 and the forwarded method is vftable slot
// 0x3C, so the whole function is a null test and a tail jump.

enum ObjectID { OBJECT_ID_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	virtual void aiSlot00();
	virtual void aiSlot04();
	virtual void aiSlot08();
	virtual void aiSlot0c();
	virtual void aiSlot10();
	virtual void aiSlot14();
	virtual void aiSlot18();
	virtual void aiSlot1c();
	virtual void aiSlot20();
	virtual void aiSlot24();
	virtual void aiSlot28();
	virtual void aiSlot2c();
	virtual void aiSlot30();
	virtual void aiSlot34();
	virtual void aiSlot38();
	virtual void repairStructure(ObjectID structureID);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	virtual void repairStructure(ObjectID structureID);

private:
	unsigned char m_unmodelled_004[0x21c];
	AIPlayer *m_ai;						// this+0x220
};

// ?repairStructure@Player@@UAEXW4ObjectID@@@Z
void Player::repairStructure(ObjectID structureID)
{
	if (m_ai)
	{
		m_ai->repairStructure(structureID);
	}
}
