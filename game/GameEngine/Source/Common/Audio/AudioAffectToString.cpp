// cl: /DNDEBUG /MD /EHsc

class BfmeTextOutput {
public:
    virtual void reserved0() = 0;
    virtual void reserved1() = 0;
    virtual void reserved2() = 0;
    virtual void reserved3() = 0;
    virtual void reserved4() = 0;
    virtual void reserved5() = 0;
    virtual void reserved6() = 0;
    virtual void reserved7() = 0;
    virtual void reserved8() = 0;
    virtual void reserved9() = 0;
    virtual void reserved10() = 0;
    virtual void reserved11() = 0;
    virtual void reserved12() = 0;
    virtual BfmeTextOutput *append(const char *text) = 0;
    virtual BfmeTextOutput *append(int value) = 0;
};

BfmeTextOutput *bfmeAppendAudioAffect(BfmeTextOutput *output, unsigned int affect)
{
    if (affect == 0) {
        output->append("NONE");
        return output;
    }

    bool appended = false;

#define APPEND_AFFECT(bit, name) \
    if (affect & bit) { \
        if (appended) \
            output->append("|"); \
        output->append(name); \
        affect &= ~bit; \
        appended = true; \
    }

    APPEND_AFFECT(0x01, "AudioAffect_Music")
    APPEND_AFFECT(0x02, "AudioAffect_Sound")
    APPEND_AFFECT(0x04, "AudioAffect_Sound3D")
    APPEND_AFFECT(0x08, "AudioAffect_Speech")
    APPEND_AFFECT(0x10, "AudioAffect_AmbientStream")
    APPEND_AFFECT(0x20, "AudioAffect_SystemSetting")

#undef APPEND_AFFECT

    if (affect != 0) {
        if (appended)
            output->append("|");
        output->append("UKNOWN (")->append((int)affect)->append(")");
    }

    return output;
}
