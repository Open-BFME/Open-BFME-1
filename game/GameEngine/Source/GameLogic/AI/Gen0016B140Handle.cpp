// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Gen0016B140::handle is the extended flag-pair hand-off used by the
// client-update seeders around retail 0x0016B140.

struct FlagPair
{
	bool m_first;
	bool m_second;
};

class FlagPairTarget
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual void applyFlags( const FlagPair &flags );
	virtual void slot2C(); virtual void slot30();
	virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40();
	virtual void slot44(); virtual void slot48();
	virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58();
	virtual void slot5C();
	virtual void takeAt24( void *item );
	virtual void slot64(); virtual void takeAt68( void *item );
	virtual void takeAt6C( void *item );
	virtual void slot70(); virtual void takeAt74( void *item );
	virtual void takeAt78( void *item ); virtual void takeAt7C( void *item );
	virtual void slot80(); virtual void slot84();
	virtual void slot88(); virtual void takeAt8C( void *item );
};

class ClientSubsystem
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual void slot6C(); virtual void slot70(); virtual void slot74();
	virtual void slot78(); virtual void slot7C(); virtual void slot80();
	virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98();
	virtual void slot9C(); virtual void slotA0(); virtual void slotA4();
	virtual void slotA8(); virtual void slotAC(); virtual void slotB0();
	virtual void slotB4(); virtual void slotB8(); virtual void slotBC();
	virtual void slotC0(); virtual void slotC4(); virtual void slotC8();
	virtual void slotCC(); virtual void slotD0(); virtual void slotD4();
	virtual void slotD8(); virtual void slotDC(); virtual void slotE0();
	virtual void slotE4(); virtual void slotE8(); virtual void slotEC();
	virtual void slotF0(); virtual void slotF4(); virtual void slotF8();
	virtual void slotFC(); virtual void slot100(); virtual void slot104();
	virtual void slot108(); virtual void slot10C(); virtual void slot110();
	virtual void slot114(); virtual void slot118(); virtual void slot11C();
	virtual void slot120(); virtual void slot124(); virtual void slot128();
	virtual void slot12C(); virtual void slot130(); virtual void slot134();
	virtual void slot138(); virtual void slot13C(); virtual void slot140();
	virtual void slot144();
	virtual void update( FlagPairTarget *target, void *item );
};

extern ClientSubsystem *TheAudioClientUpdate;
extern void j_000394be();

class Gen0016B140
{
public:
	void handle( FlagPairTarget *target );

private:
	char m_pad00[0x24];
	char m_item24;
	char m_pad25[0x0B];
	char m_item30;
	char m_pad31[0x03];
	char m_item34;
	char m_pad35[0x0B];
	char m_item40;
	char m_pad41[0x03];
	char m_item44;
	char m_pad45[0x03];
	char m_item48;
	char m_pad49[0x03];
	char m_item4C;
	char m_item4D;
	char m_pad4E[0x02];
};

// ?handle@Gen0016B140@@QAEXPAVFlagPairTarget@@@Z
void Gen0016B140::handle( FlagPairTarget *target )
{
	FlagPair flags;
	flags.m_first = true;
	flags.m_second = true;
	target->applyFlags( flags );
	target->takeAt24( &m_item24 );
	reinterpret_cast<void (*)( FlagPairTarget *, void * )>( j_000394be )( target, &m_item30 );
	target->takeAt8C( &m_item4D );
	target->takeAt24( &m_item34 );
	target->takeAt74( &m_item44 );
	target->takeAt74( &m_item48 );
	target->takeAt8C( &m_item4C );

	if ( TheAudioClientUpdate != 0 )
		TheAudioClientUpdate->update( target, &m_item40 );
}
