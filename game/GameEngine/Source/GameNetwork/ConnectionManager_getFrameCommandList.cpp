// cl: /DNDEBUG /MD /EHsc
// ConnectionManager::getFrameCommandList, RVA 0x00663450, 174 bytes.
// Matched Network::RelayCommandsToCommandList calls it at 0x00682AB6.
// Collects each player's commands and retires frames older than FRAMES_TO_KEEP.
// The retail call at 0x006634A4 queries network vtable slot +0x48 even though
// its return value is discarded. Preserve that call and the frame-ring lifetime.
class NetCommandList {
public:
    NetCommandList();
    void reset();
    void appendList(NetCommandList *other);
private:
    void *m_vptr;
    void *m_first;
    void *m_last;
    void *m_lastInserted;
};
class FrameDataManager {
public:
    NetCommandList *getFrameCommandList(unsigned int frame);
    void resetFrame(unsigned int frame, bool advancing = true);
};
class NetworkInterface {
public:
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17();
    virtual bool _bfme_isLocalPlayerInGame();
};
extern NetworkInterface *TheNetwork;
extern int FRAMES_TO_KEEP;
class ConnectionManager {
public:
    NetCommandList *getFrameCommandList(unsigned int frame);
private:
    char m_prefix[0x120e4];
    FrameDataManager *m_frameData[8];
};
NetCommandList *ConnectionManager::getFrameCommandList(unsigned int frame)
{
    NetCommandList *retlist = new NetCommandList;
    retlist->reset();
    TheNetwork->_bfme_isLocalPlayerInGame();
    for (int i = 0; i < 8; ++i) {
        if (m_frameData[i] != 0) {
            retlist->appendList(m_frameData[i]->getFrameCommandList(frame));
            if (frame > FRAMES_TO_KEEP)
                m_frameData[i]->resetFrame(frame - FRAMES_TO_KEEP);
        }
    }
    return retlist;
}
