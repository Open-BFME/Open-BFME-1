// ?xferSaveData@GameState@@AAEXPAVXfer@@W4SnapshotType@@@Z
// partial score=0.63 date=2026-09-02
// Banked attempt for GameState::xferSaveData at 0x0010FBD0 (550 bytes).
// The save branch is exact after applying the native BFME Xfer/StringBase ABI.
// The load branch remains a register/inline-comparison mismatch; this file is
// evidence for the next reconstruction and is not compiled by the project.

template <typename T> class StringBase
{
    struct Header {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };
    friend class GameState;
    StringBase() : m_data( 0 ) {}
    StringBase( const T *str );
    StringBase( const StringBase<T> &src );
    ~StringBase();
public:
    StringBase<T> &operator=( const StringBase<T> &src );
    void set( const StringBase<T> &src );
    int compareNoCase( const T *str ) const;
    const T *str() const;
private:
    Header *m_data;
    void releaseBuffer();
};

class BfmeGameStateXfer
{
public:
    virtual void slot00() = 0;
    virtual Bool isLoading() = 0;
    virtual Bool isStoring() = 0;
    virtual Bool isCRC() = 0;
    virtual Bool isLightCRC() = 0;
    virtual void beginBlock( const Char *name ) = 0;
    virtual void endBlock() = 0;
    virtual void skipBlock( const Char *name ) = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void xferSnapshot( Snapshot *snapshot ) = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void xferAsciiString( AsciiString *value ) = 0;
};

void GameState::xferSaveData( Xfer *xfer, SnapshotType which )
{
    BfmeGameStateXfer *bfmeXfer = reinterpret_cast<BfmeGameStateXfer *>( xfer );
    if( bfmeXfer->isStoring() )
    {
        StringBase<char> blockName;
        SnapshotBlock *blockInfo;
        SnapshotBlockListIterator it;
        for( it = m_snapshotBlockList[which].begin(); it != m_snapshotBlockList[which].end(); ++it )
        {
            blockInfo = &(*it);
            blockName.set( *reinterpret_cast<const StringBase<char> *>( &blockInfo->blockName ) );
            if( getSaveGameInfo()->saveFileType != SAVE_FILE_TYPE_MISSION ||
                blockName.compareNoCase( GAME_STATE_BLOCK_STRING ) == 0 ||
                blockName.compareNoCase( CAMPAIGN_BLOCK_STRING ) == 0 ||
                blockName.compareNoCase( "CHUNK_LivingWorldLogic" ) == 0 ||
                blockName.compareNoCase( "CHUNK_Palantir" ) == 0 ||
                blockName.compareNoCase( "CHUNK_Audio" ) == 0 )
            {
                bfmeXfer->xferAsciiString( reinterpret_cast<AsciiString *>( &blockName ) );
                try {
                    bfmeXfer->beginBlock( "Snapshot" );
                    bfmeXfer->xferSnapshot( blockInfo->snapshot );
                    bfmeXfer->endBlock();
                } catch( ... ) {
                    bfmeXfer->endBlock();
                    throw;
                }
            }
            blockInfo = 0;
        }
        StringBase<char> eofToken = SAVE_FILE_EOF;
        bfmeXfer->xferAsciiString( reinterpret_cast<AsciiString *>( &eofToken ) );
    }
    else
    {
        StringBase<char> token;
        Bool done = FALSE;
        SnapshotBlock *blockInfo;
        while( done == FALSE )
        {
            bfmeXfer->xferAsciiString( reinterpret_cast<AsciiString *>( &token ) );
            if( token.compareNoCase( SAVE_FILE_EOF ) == 0 )
                done = TRUE;
            else
            {
                blockInfo = findBlockInfoByToken( *reinterpret_cast<AsciiString *>( &token ), which );
                if( blockInfo == NULL ) {
                    bfmeXfer->skipBlock( "Snapshot" );
                    continue;
                }
                try {
                    bfmeXfer->beginBlock( "Snapshot" );
                    bfmeXfer->xferSnapshot( blockInfo->snapshot );
                    bfmeXfer->endBlock();
                } catch( ... ) {
                    bfmeXfer->endBlock();
                    throw;
                }
            }
        }
    }
}
