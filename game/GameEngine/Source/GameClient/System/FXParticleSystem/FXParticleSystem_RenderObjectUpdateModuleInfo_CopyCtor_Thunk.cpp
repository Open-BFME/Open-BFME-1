// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class Xfer;

namespace FXParticleSystem {

// Stand-in for the GameClientRandomVariable this class really holds twelve of
// (DoXfer in fx_particle_system_bulk.cpp xfers each slot through
// xferRandomVariable): the real class declares an out-of-line operator=, and
// retail copies these slots inline, so this TU keeps a trivially-copyable
// twelve-byte aggregate instead of pulling that header in.
struct VariableBlock {
    unsigned int value0;
    unsigned int value1;
    unsigned int value2;
};

class RenderObjectUpdateModuleInfo {
public:
    RenderObjectUpdateModuleInfo(const RenderObjectUpdateModuleInfo &that);
    virtual ~RenderObjectUpdateModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    RenderObjectUpdateModuleInfo &operator=(const RenderObjectUpdateModuleInfo &that);

private:
    VariableBlock m_blocks[12];
    unsigned int m_94;
};

// ??0RenderObjectUpdateModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
RenderObjectUpdateModuleInfo::RenderObjectUpdateModuleInfo(const RenderObjectUpdateModuleInfo &that)
{
    m_blocks[0] = that.m_blocks[0];
    m_blocks[1] = that.m_blocks[1];
    m_blocks[2] = that.m_blocks[2];
    m_blocks[3] = that.m_blocks[3];
    m_blocks[4] = that.m_blocks[4];
    m_blocks[5] = that.m_blocks[5];
    m_blocks[6] = that.m_blocks[6];
    m_blocks[7] = that.m_blocks[7];
    m_blocks[8] = that.m_blocks[8];
    m_blocks[9] = that.m_blocks[9];
    m_blocks[10] = that.m_blocks[10];
    m_blocks[11] = that.m_blocks[11];
    m_94 = that.m_94;
}

}
