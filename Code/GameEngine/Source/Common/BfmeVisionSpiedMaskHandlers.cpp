// cl: /DNDEBUG /MD /EHsc
// BFME's vision-spied edge handlers update the aggregate mask, notify the
// partition cell, then maintain the per-player reference bit selected by the
// retail player-index table.

typedef int Int;
typedef unsigned int UnsignedInt;

class BfmeVisionPartition
{
public:
	void handlePartitionCellMaintenance(void *object);
};

class BfmeBlockVKP
{
};

class BfmeNotifyVKP
{
public:
	void bfmeNotifyVKP( BfmeBlockVKP *counts, Int unused1, Int unused2 );
};

class BfmeUpdVKP
{
public:
	void bfmeUpdateVKP();
};

extern Int g_bfmeVisionPlayerMap[];

class Gen001C9A10
{
public:
	void handle( Int player );

private:
	char m_pad00[0x80];
	BfmeNotifyVKP *m_drawable;
	char m_pad84[0x8c];
	Int m_visionSpiedBy[16];
	char m_pad150[0x114];
	BfmeVisionPartition m_partition;
	char m_pad268[0x34];
	UnsignedInt m_visionSpiedMask;
};

class Gen001C9AC0
{
public:
	void handle( Int player );

private:
	char m_pad00[0x80];
	BfmeNotifyVKP *m_drawable;
	char m_pad84[0x8c];
	Int m_visionSpiedBy[16];
	char m_pad150[0x114];
	BfmeVisionPartition m_partition;
	char m_pad268[0x34];
	UnsignedInt m_visionSpiedMask;
};

static BfmeNotifyVKP *visionDrawable( void *self )
{
	return *(BfmeNotifyVKP **)((char *)self + 0x80);
}

static BfmeUpdVKP *visionUpdate( void *self )
{
	return *(BfmeUpdVKP **)((char *)self + 0x204);
}

static void refreshVision( Gen001C9A10 *self )
{
	BfmeNotifyVKP *drawable = visionDrawable( self );
	if( drawable )
		drawable->bfmeNotifyVKP( (BfmeBlockVKP *)((char *)self + 0x110), 0, 0 );

	BfmeUpdVKP *update = visionUpdate( self );
	if( update )
		update->bfmeUpdateVKP();
}

void Gen001C9A10::handle( Int player )
{
	UnsignedInt bit = 1 << (player & 0x1f);
	m_visionSpiedMask |= bit;
	m_partition.handlePartitionCellMaintenance( this );

	UnsignedInt mapped = (UnsignedInt)g_bfmeVisionPlayerMap[player];
	if( mapped == -1 )
		return;

	if( (1 << (mapped & 0x1f)) & m_visionSpiedBy[mapped >> 5] )
		return;
	m_visionSpiedBy[mapped >> 5] |= (1 << (mapped & 0x1f));
	refreshVision( this );
}

static void refreshVision( Gen001C9AC0 *self )
{
	BfmeNotifyVKP *drawable = visionDrawable( self );
	if( drawable )
		drawable->bfmeNotifyVKP( (BfmeBlockVKP *)((char *)self + 0x110), 0, 0 );

	BfmeUpdVKP *update = visionUpdate( self );
	if( update )
		update->bfmeUpdateVKP();
}

void Gen001C9AC0::handle( Int player )
{
	UnsignedInt bit = 1 << (player & 0x1f);
	m_visionSpiedMask &= ~bit;
	m_partition.handlePartitionCellMaintenance( this );

	UnsignedInt mapped = (UnsignedInt)g_bfmeVisionPlayerMap[player];
	if( mapped == -1 )
		return;

	if( (m_visionSpiedBy[mapped >> 5] & (1 << (mapped & 0x1f))) == 0 )
		return;
	m_visionSpiedBy[mapped >> 5] &= ~(1 << (mapped & 0x1f));
	refreshVision( this );
}
