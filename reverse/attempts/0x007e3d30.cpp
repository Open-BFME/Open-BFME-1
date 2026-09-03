// ?d_007e3d30@@YAXXZ
// partial score=0.72 date=2026-09-03
// ?decodeFrame@Rva007E3D30Vp6Stream@@QAEXXZ [retail body 0x007E3D30]
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class BfmeDev996
{
public:
    virtual void v0(void);
    virtual void v1(void);
    virtual void v2(void);
    virtual int classify(int value, int width);
};

class BfmeB996
{
public:
    char movePair(int *output, int *first, unsigned int *second,
        unsigned int limit);

private:
    char m_pad[4];
    BfmeDev996 *m_dev;
    int m_kind;
    int m_unused;
};

extern "C" void __cdecl rva007e3d30DecodePacket(int output, int *input,
    unsigned int second, int width, int height);

class Rva007E3D30Vp6Stream
{
public:
    void decodeFrame(void);

private:
    char m_pad0[0x14];
    int m_audioOutput;
    int m_videoOutput;
    BfmeB996 m_reader;
    char m_pad2c[4];
    int m_width;
    int m_height;
    unsigned char m_audioEnabled;
    char m_pad39[3];
    int m_limit;
    char m_pad40[8];
    int m_frame;
    char m_pad4c[8];
    int *m_input;
    int m_inputLimit;
};

void Rva007E3D30Vp6Stream::decodeFrame(void)
{
    int first;
    unsigned int second;
    unsigned char audioEnabled = m_audioEnabled;

    *(Rva007E3D30Vp6Stream **)0x01309840 = this;

    if (!audioEnabled)
        goto video_phase;

    {
        BfmeB996 &reader = m_reader;
        while (reader.movePair(m_input, &first, &second,
            (unsigned int)m_inputLimit)) {
            if (first == 0x4b305641 || first == 0x46305641) {
                rva007e3d30DecodePacket(m_audioOutput, m_input + 8,
                    second, m_width, m_height);
                goto video_phase;
            }
        }
        goto audio_failure;
    }

video_phase:
    {
        BfmeB996 &reader = m_reader;
        for (;;) {
            if (!reader.movePair(m_input, &first, &second,
            (unsigned int)m_inputLimit)) {
                goto video_failure;
            }

            ++*(int *)0x0130983c;
            if (first == 0x4b30564d || first == 0x4630564d) {
                rva007e3d30DecodePacket(m_videoOutput, m_input + 8,
                    second, m_width, m_height);
                ++m_frame;
                return;
            }
        }
    }

audio_failure:
    m_frame = m_limit - 1;
    return;

video_failure:
    m_frame = m_limit - 1;
    return;
}
