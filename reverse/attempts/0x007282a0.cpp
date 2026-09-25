// ?setFlipRecursive@W3DTerrainBackground@@IAEXHHHH@Z
// partial score=0.14 date=2026-09-25
// Scratch reconstruction for retail 0x007282A0..0x007285D5 (821 bytes).
// Caller, pin, and matched source establish the W3D member identity.
//
// cl: /DNDEBUG /MD /EHsc

class BfmeMaskAX
{
public:
    void bfmeMarkAX(int x, int y, unsigned char value);
};

class Rva007282A0Map
{
public:
    int width(void) const
    {
        return *(const int *)((const char *)this + 0x08);
    }

    int height(void) const
    {
        return *(const int *)((const char *)this + 0x0c);
    }

    int count(void) const
    {
        return *(const int *)((const char *)this + 0x20);
    }

    unsigned short *heights(void) const
    {
        return *(unsigned short * const *)((const char *)this + 0x24);
    }

    int *cliffArray(void) const
    {
        return *(int * const *)((const char *)this + 0x94);
    }

    int drawOriginX(void) const
    {
        return *(const int *)((const char *)this + 0x120E0);
    }

    int drawOriginY(void) const
    {
        return *(const int *)((const char *)this + 0x120E4);
    }

    unsigned short heightAt(int x, int y) const
    {
        int index = y * width() + x;
        if (index < 0 || index >= count())
            return 0;
        unsigned short *data = heights();
        if (data == 0)
            return 0;
        return data[index];
    }

    bool cliffAt(int x, int y) const
    {
        int index = (drawOriginY() + y) * width() + drawOriginX() + x;
        if (index < 0)
            return false;
        if (index >= count())
            return false;
        return cliffArray()[index] != 0;
    }
};

class W3DTerrainBackground
{
protected:
    void setFlipRecursive(int xOffset, int yOffset, int width,
        int errorToleranceBits);

private:
    int xOrigin(void) const
    {
        return *(const int *)((const char *)this + 0x40);
    }

    int yOrigin(void) const
    {
        return *(const int *)((const char *)this + 0x44);
    }

    Rva007282A0Map *map(void) const
    {
        return *(Rva007282A0Map * const *)((const char *)this + 0x4c);
    }
};

// ?setFlipRecursive@W3DTerrainBackground@@IAEXHHHH@Z
void W3DTerrainBackground::setFlipRecursive(int xOffset, int yOffset, int width,
    int errorToleranceBits)
{

    int limitX = map()->width() - 1;
    int limitY = map()->height() - 1;
    bool match = true;
    int minX = xOrigin() + xOffset;
    int minY = yOrigin() + yOffset;
    int maxX = minX + width;
    if (maxX >= limitX)
        maxX = limitX;
    int maxY = minY + width;
    if (maxY >= limitY)
        maxY = limitY;

    int cornerA = map()->heightAt(minX, minY);
    int cornerB = map()->heightAt(maxX, minY);
    int cornerC = map()->heightAt(maxX, maxY);
    int cornerD = map()->heightAt(minX, maxY);

    int i;
    int j;
    for (i = 0; i <= width; ++i)
    {
        for (j = 0; j <= width; ++j)
        {
            int k = minX + j;
            if (k >= limitX)
                k = limitX;
            int l = minY + i;
            if (l >= limitY)
                l = limitY;

            if (map()->cliffAt(k, l))
            {
                match = false;
                break;
            }

            float u = (float)j / (float)width;
            float v = (float)i / (float)width;
            float predicted;
            if (v > (1.0f - u))
            {
                predicted = ((cornerB - cornerC) *
                    (1.0f - v) +
                    (cornerD - cornerC) *
                    (1.0f - u) + cornerC) *
                    0.0390625f;
            }
            else
            {
                predicted = ((cornerD - cornerA) * v +
                    (cornerB - cornerA) * u + cornerA) *
                    0.0390625f;
            }

            int currentHeight = map()->heightAt(k, l);
            float delta = predicted - currentHeight * 0.0390625f;
            if (delta < 0.0f)
                delta = -delta;
            if (delta > *(const float *)&errorToleranceBits)
            {
                match = false;
                break;
            }
        }
    }

    if (width == 1 || match)
    {
        int cornerMaxX = minX + width;
        if (cornerMaxX >= limitX)
            cornerMaxX = limitX;
        int cornerMaxY = minY + width;
        if (cornerMaxY >= limitY)
            cornerMaxY = limitY;

        ((BfmeMaskAX *)map())->bfmeMarkAX(minX, minY, 1);
        ((BfmeMaskAX *)map())->bfmeMarkAX(cornerMaxX, minY, 1);
        ((BfmeMaskAX *)map())->bfmeMarkAX(cornerMaxX, cornerMaxY, 1);
        ((BfmeMaskAX *)map())->bfmeMarkAX(minX, cornerMaxY, 1);
        return;
    }

    int halfWidth = width / 2;
    setFlipRecursive(xOffset, yOffset, halfWidth, errorToleranceBits);
    setFlipRecursive(xOffset, yOffset + halfWidth, halfWidth, errorToleranceBits);
    setFlipRecursive(xOffset + halfWidth, yOffset, halfWidth, errorToleranceBits);
    setFlipRecursive(xOffset + halfWidth, yOffset + halfWidth, halfWidth,
        errorToleranceBits);
}
