// cl: /DNDEBUG /MD /EHsc

// Object::unidentified_001BFE20, retail 0x001BFE20. The name is address-derived
// and this tree's; only the shape is claimed.
//
// The contain module at +0x1FC is asked through its virtual slot +0x68, as a
// tail jump, and a missing module answers null without asking anything.

class Player;

class ObjectContain
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void _bfme_pad_08() = 0;
	virtual void _bfme_pad_0C() = 0;
	virtual void _bfme_pad_10() = 0;
	virtual void _bfme_pad_14() = 0;
	virtual void _bfme_pad_18() = 0;
	virtual void _bfme_pad_1C() = 0;
	virtual void _bfme_pad_20() = 0;
	virtual void _bfme_pad_24() = 0;
	virtual void _bfme_pad_28() = 0;
	virtual void _bfme_pad_2C() = 0;
	virtual void _bfme_pad_30() = 0;
	virtual void _bfme_pad_34() = 0;
	virtual void _bfme_pad_38() = 0;
	virtual void _bfme_pad_3C() = 0;
	virtual void _bfme_pad_40() = 0;
	virtual void _bfme_pad_44() = 0;
	virtual void _bfme_pad_48() = 0;
	virtual void _bfme_pad_4C() = 0;
	virtual void _bfme_pad_50() = 0;
	virtual void _bfme_pad_54() = 0;
	virtual void _bfme_pad_58() = 0;
	virtual void _bfme_pad_5C() = 0;
	virtual void _bfme_pad_60() = 0;
	virtual void _bfme_pad_64() = 0;
	virtual Player *getControllingPlayer() = 0;		// +0x68
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *unidentified_001BFE20( void ) const;

private:
	unsigned char m_unmodelled_00[ 0x1FC ];
	ObjectContain *m_contain;				// +0x1FC
};

// ?unidentified_001BFE20@Object@@QBEPAVPlayer@@XZ
Player *Object::unidentified_001BFE20( void ) const
{
	// Read once into a local. Testing the member and then calling through it
	// again loads it twice, into eax and then ecx; retail loads it straight into
	// ecx and tests that.
	ObjectContain *contain = m_contain;

	if( contain == 0 )
		return 0;

	return contain->getControllingPlayer();
}
