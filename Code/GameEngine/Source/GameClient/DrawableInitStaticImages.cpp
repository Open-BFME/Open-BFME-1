// cl: /DNDEBUG /MD /EHsc
// Lane 28 scratch reconstruction of retail 0x00415D50.

class AsciiString;

template <typename T>
class StringBase
{
    friend class AsciiString;

private:
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    void releaseBuffer();
    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(const char *text) : StringBase<char>(text) { }
    AsciiString(const AsciiString &other)
        : StringBase<char>(other) { }
    ~AsciiString() { releaseBuffer(); }
};

class Image;
class ImageCollection
{
public:
    const Image *findImageByName(const AsciiString &name);
};

class Anim2DTemplate;
class Anim2DCollection
{
public:
    Anim2DTemplate *findTemplate(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;
extern Anim2DCollection *TheAnim2DCollection;
extern const char *TheDrawableIconNames[];
extern "C" void *__cdecl bfmeArrayNew(unsigned int size);

class Drawable
{
private:
    static void initStaticImages();

    static bool s_staticImagesInited;
    static const Image *s_fullAmmo;
    static const Image *s_emptyAmmo;
    static const Image *s_fullContainer;
    static const Image *s_emptyContainer;
    static const Image *s_contestPipFull;
    static const Image *s_contestPipEmpty;
    static Anim2DTemplate **s_animationTemplates;
    static const Image *s_veterancyImage[4];
};

bool Drawable::s_staticImagesInited = false;
const Image *Drawable::s_fullAmmo;
const Image *Drawable::s_emptyAmmo;
const Image *Drawable::s_fullContainer;
const Image *Drawable::s_emptyContainer;
const Image *Drawable::s_contestPipFull;
const Image *Drawable::s_contestPipEmpty;
Anim2DTemplate **Drawable::s_animationTemplates;
const Image *Drawable::s_veterancyImage[4];

void Drawable::initStaticImages()
{
    if (s_staticImagesInited)
        return;

    s_fullAmmo = TheMappedImageCollection->findImageByName(
        AsciiString("SCPAmmoFull"));
    s_emptyAmmo = TheMappedImageCollection->findImageByName(
        AsciiString("SCPAmmoEmpty"));
    s_fullContainer = TheMappedImageCollection->findImageByName(
        AsciiString("SCPPipFull"));
    s_emptyContainer = TheMappedImageCollection->findImageByName(
        AsciiString("SCPPipEmpty"));
    s_contestPipFull = TheMappedImageCollection->findImageByName(
        AsciiString("SCPContestPipFull"));
    s_contestPipEmpty = TheMappedImageCollection->findImageByName(
        AsciiString("SCPContestPipEmpty"));

    s_animationTemplates = (Anim2DTemplate **)bfmeArrayNew(
        14 * sizeof(Anim2DTemplate *));
    s_animationTemplates[0] = TheAnim2DCollection->findTemplate(
        AsciiString(TheDrawableIconNames[0]));
    s_animationTemplates[1] = TheAnim2DCollection->findTemplate(
        AsciiString(TheDrawableIconNames[1]));
    s_animationTemplates[2] = TheAnim2DCollection->findTemplate(
        AsciiString(TheDrawableIconNames[2]));
    s_animationTemplates[4] = TheAnim2DCollection->findTemplate(
        AsciiString(TheDrawableIconNames[4]));
    s_animationTemplates[5] = TheAnim2DCollection->findTemplate(
        AsciiString(TheDrawableIconNames[5]));
    s_animationTemplates[6] = TheAnim2DCollection->findTemplate(
        AsciiString(TheDrawableIconNames[6]));
    s_animationTemplates[7] = TheAnim2DCollection->findTemplate(
        AsciiString(TheDrawableIconNames[7]));
    s_animationTemplates[8] = TheAnim2DCollection->findTemplate(
        AsciiString(TheDrawableIconNames[8]));
    s_animationTemplates[9] = TheAnim2DCollection->findTemplate(
        AsciiString(TheDrawableIconNames[9]));
    s_animationTemplates[10] = 0;
    s_animationTemplates[11] = TheAnim2DCollection->findTemplate(
        AsciiString(TheDrawableIconNames[11]));
    s_animationTemplates[12] = TheAnim2DCollection->findTemplate(
        AsciiString(TheDrawableIconNames[12]));
    s_animationTemplates[13] = TheAnim2DCollection->findTemplate(
        AsciiString(TheDrawableIconNames[13]));

    s_veterancyImage[0] = TheMappedImageCollection->findImageByName(
        AsciiString("Good_Vet"));
    s_veterancyImage[1] = TheMappedImageCollection->findImageByName(
        AsciiString("Good_Vet_Dot"));
    s_veterancyImage[2] = TheMappedImageCollection->findImageByName(
        AsciiString("Evil_Vet"));
    s_veterancyImage[3] = TheMappedImageCollection->findImageByName(
        AsciiString("Evil_Vet_Dot"));

    s_staticImagesInited = true;
}
