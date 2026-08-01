// cl: /DNDEBUG /MD /EHs-c-

class AsciiString
{
public:
    ~AsciiString(void);
};

class Image;

class Anim2DTemplate
{
public:
    virtual ~Anim2DTemplate(void);

    Anim2DTemplate *m_nextTemplate;
    AsciiString m_name;
    const Image **m_images;
};

Anim2DTemplate::~Anim2DTemplate(void)
{
    if (m_images)
        delete [] m_images;
}
