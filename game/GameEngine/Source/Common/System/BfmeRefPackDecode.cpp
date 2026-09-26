// cl: /DNDEBUG /MD /EHsc

// BFME's archive path carries the two-argument RefPack decoder directly in
// the engine.  The shipped EAC REF_decode API has a different ABI (stdcall,
// three arguments, and a returned unpacked length), so this remains a
// TU-local engine helper rather than changing that vendor implementation.

typedef unsigned char UnsignedByte;

int bfmeRefPackDecode(const UnsignedByte *compressedData,
                      UnsignedByte *destination)
{
    UnsignedByte *s;
    UnsignedByte *d;
    UnsignedByte *ref;
    UnsignedByte first;
    UnsignedByte second;
    UnsignedByte third;
    UnsignedByte forth;
    unsigned int run;
    unsigned int type;
    int ulen;

    s = (UnsignedByte *)compressedData;
    d = destination;
    ulen = 0L;

    if (s)
    {
        type = *s++;
        type = (type << 8) + *s++;

        if (type == 0x11fb)
        {
            s += 3;
        }

        ulen = *s++;
        ulen = (ulen << 8) + *s++;
        ulen = (ulen << 8) + *s++;

        if ((type == 0x15fb) || (type == 0x16fb))
        {
            ulen = (ulen << 8) + *s++;
        }

        for (;;)
        {
            first = *s++;
            if (!(first & 0x80))
            {
                second = *s++;
                run = first & 3;
                while (run--)
                {
                    *d++ = *s++;
                }

                ref = d - 1 - (((first & 0x60) << 3) + second);
                run = ((first & 0x1c) >> 2) + 3 - 1;
                do
                {
                    *d++ = *ref++;
                } while (run--);
                continue;
            }

            if (!(first & 0x40))
            {
                second = *s++;
                third = *s++;
                run = second >> 6;
                while (run--)
                {
                    *d++ = *s++;
                }

                ref = d - 1 - (((second & 0x3f) << 8) + third);
                run = (first & 0x3f) + 4 - 1;
                do
                {
                    *d++ = *ref++;
                } while (run--);
                continue;
            }

            if (!(first & 0x20))
            {
                second = *s++;
                third = *s++;
                forth = *s++;
                run = first & 3;
                while (run--)
                {
                    *d++ = *s++;
                }

                ref = d - 1 - (((first & 0x10) >> 4 << 16)
                               + (second << 8) + third);
                run = ((first & 0x0c) >> 2 << 8) + forth + 5 - 1;
                do
                {
                    *d++ = *ref++;
                } while (run--);
                continue;
            }

            run = ((first & 0x1f) << 2) + 4;
            if (run <= 112)
            {
                while (run--)
                {
                    *d++ = *s++;
                }
                continue;
            }

            run = first & 3;
            while (run--)
            {
                *d++ = *s++;
            }
            break;
        }
    }

    return ulen;
}
