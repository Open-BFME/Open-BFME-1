
// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
    int m_text;

public:
    AsciiString(void) : m_text(0) {}
    AsciiString(const AsciiString&);
    AsciiString& operator=(const AsciiString&);
    ~AsciiString(void);
};

class Image;

class Anim2DTemplate
{
public:
    Anim2DTemplate(AsciiString name);
    virtual ~Anim2DTemplate(void);

    Anim2DTemplate *m_nextTemplate;
    AsciiString m_name;
    const Image **m_images;
    unsigned short m_numFrames;
    unsigned short m_framesBetweenUpdates;
    int m_animMode;
    bool m_randomizeStartFrame;
};

Anim2DTemplate::Anim2DTemplate(AsciiString name)
{
    m_name = name;
    m_images = 0;
    m_numFrames = 0;
    m_framesBetweenUpdates = 0;
    m_animMode = 3;
    m_randomizeStartFrame = false;
    m_nextTemplate = 0;
}
