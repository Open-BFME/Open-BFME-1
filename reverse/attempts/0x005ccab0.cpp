// ?writeINI@ParticleSystemTemplate@FXParticleSystem@@QBEXAAVFile@@I@Z
// partial score=0.8 date=2026-09-09
// ?writeINI@ParticleSystemTemplate@FXParticleSystem@@QBEXAAVFile@@I@Z
void ParticleSystemTemplate::writeINI(File &file, unsigned int flags) const
{
    typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > StreamText;
    class StringStorage
    {
    public:
        ~StringStorage()
        {
            const unsigned int bytes =
                (unsigned int)(m_storageEnd - m_start) * sizeof(char);
            if (m_start)
            {
                if (bytes > 128)
                    ::operator delete(m_start);
                else
                    _STL::__node_alloc<true, 0>::_M_deallocate(m_start, bytes);
            }
        }

        char *m_start;
        char *m_finish;
        char *m_storageEnd;
    };
    typedef StringStorage *(__cdecl *StringCharConcat)(
        StringStorage *result, StringStorage *source, int character);
    typedef StringStorage *(__cdecl *StringNameConcat)(
        StringStorage *result, StringStorage *prefix, const char *name);
    typedef void (__cdecl *WriteLineFunction)(
        const char *text, File *file, unsigned int *flags);
    typedef void (__cdecl *EnumWriter)(
        void *ini, void *instance, void *store, void **value);
    typedef void (__cdecl *ByteWriter)(
        void *ini, void *instance, void *store, U1ByteFlagged *value);
    typedef void (__cdecl *CountedWriter)(
        void *ini, void *instance, void *store, U1CountedHolder *value);
    typedef void (__cdecl *PairWriter)(
        void *ini, void *instance, void *store, U1Pair *value);
    typedef void (__cdecl *DwordWriter)(
        void *ini, void *instance, void *store, void *value);
    typedef void (__cdecl *VectorWriter)(
        INI *ini, void *instance, void *store, const void *value);
    typedef void (__cdecl *FinishWriter)(File *file, unsigned int *flags);

    // These ILT names are the retail routes.  The first four are anonymous
    // STL/string helpers; their argument roles are established by the complete
    // call sequence and their returned string objects, not by a guessed name.
    extern void j_0003f41d();
    extern void j_0002f98c();
    extern void j_00010631();
    extern void j_00020103();
    extern void j_000014ab();
    extern void j_000355f3();
    extern void j_00033384();
    extern void j_00021aa8();
    extern void j_000382e4();
    extern void j_0001ca26();
    extern void j_0004618c();

    _STL::allocator<char> allocator;
    StreamText initial("FXParticleSystem", allocator);

    StringStorage prefix;
    StringStorage *prefixResult =
        reinterpret_cast<StringCharConcat>(j_0003f41d)(
            (StringStorage *)&prefix, (StringStorage *)&initial, 0x20);

    const char *name = *(const char **)((const unsigned char *)this + 0x98);
    if (name)
        name += 8;
    else
        name = (const char *)0x0107388b;

    StringStorage line;
    StringStorage *lineResult =
        reinterpret_cast<StringNameConcat>(j_0002f98c)(&line, prefixResult, name);
    reinterpret_cast<WriteLineFunction>(j_00010631)(
        lineResult->m_start, &file, &flags);

    reinterpret_cast<WriteLineFunction>(j_00010631)(
        "System", &file, &flags);

    _STL::basic_ofstream<char, _STL::char_traits<char> > stream(0x10);

    unsigned int priority = *(const unsigned int *)((const unsigned char *)this + 0x7c);
    if (priority != 1)
        reinterpret_cast<EnumWriter>(j_00020103)(
            (void *)&stream, (void *)flags, (void *)0x01081640,
            (void **)(0x01110208 + priority * 4));

    U1ByteFlagged *oneShot =
        (U1ByteFlagged *)((unsigned char *)this + 0x04);
    if (oneShot->m_flag)
        reinterpret_cast<ByteWriter>(j_000014ab)(
            (void *)&stream, (void *)flags, (void *)0x0110fb38, oneShot);

    unsigned int shader = *(const unsigned int *)((const unsigned char *)this + 0x08);
    if (shader != 1)
        reinterpret_cast<EnumWriter>(j_00020103)(
            (void *)&stream, (void *)flags, (void *)0x010f2790,
            (void **)(0x01110180 + shader * 4));

    unsigned int type = *(const unsigned int *)((const unsigned char *)this + 0x0c);
    if (type != 1)
        reinterpret_cast<EnumWriter>(j_00020103)(
            (void *)&stream, (void *)flags, (void *)0x01080ddc,
            (void **)(0x011101b0 + type * 4));

    U1CountedHolder *particleName =
        (U1CountedHolder *)((unsigned char *)this + 0x10);
    U1Counted *particleNameItem = particleName->m_item;
    if (particleNameItem != 0 && particleNameItem->m_count != 0)
        reinterpret_cast<CountedWriter>(j_000355f3)(
            (void *)&stream, (void *)flags, (void *)0x0110fb28, particleName);

    U1CountedHolder *slaveSystem =
        (U1CountedHolder *)((unsigned char *)this + 0x68);
    U1Counted *slaveSystemItem = slaveSystem->m_item;
    if (slaveSystemItem != 0 && slaveSystemItem->m_count != 0)
        reinterpret_cast<CountedWriter>(j_000355f3)(
            (void *)&stream, (void *)flags, (void *)0x0110fb18, slaveSystem);

    reinterpret_cast<VectorWriter>(j_000382e4)(
        (INI *)&stream, (void *)flags, (void *)0x0110fb04,
        (const void *)((unsigned char *)this + 0x6c));

    U1CountedHolder *attachedSystem =
        (U1CountedHolder *)((unsigned char *)this + 0x78);
    U1Counted *attachedSystemItem = attachedSystem->m_item;
    if (attachedSystemItem != 0 && attachedSystemItem->m_count != 0)
        reinterpret_cast<CountedWriter>(j_000355f3)(
            (void *)&stream, (void *)flags, (void *)0x0110fae4, attachedSystem);

    U1Pair *lifetime = (U1Pair *)((unsigned char *)this + 0x14);
    if (lifetime->m_x != BfmeZeroRange || lifetime->m_y != BfmeZeroRange)
        reinterpret_cast<PairWriter>(j_00033384)(
            (void *)&stream, (void *)flags, (void *)0x010f26ec, lifetime);

    void **systemLifetime = (void **)((unsigned char *)this + 0x20);
    if (*systemLifetime)
        reinterpret_cast<DwordWriter>(j_00021aa8)(
            (void *)&stream, (void *)flags, (void *)0x0110fad0, systemLifetime);

    void **sortLevel = (void **)((unsigned char *)this + 0x24);
    if (*sortLevel)
        reinterpret_cast<DwordWriter>(j_00021aa8)(
            (void *)&stream, (void *)flags, (void *)0x0110fac4, sortLevel);

    U1Pair *size = (U1Pair *)((unsigned char *)this + 0x28);
    if (size->m_x != BfmeZeroRange || size->m_y != BfmeZeroRange)
        reinterpret_cast<PairWriter>(j_00033384)(
            (void *)&stream, (void *)flags, (void *)0x010ee308, size);

    U1Pair *startSizeRate = (U1Pair *)((unsigned char *)this + 0x34);
    if (startSizeRate->m_x != BfmeZeroRange ||
        startSizeRate->m_y != BfmeZeroRange)
        reinterpret_cast<PairWriter>(j_00033384)(
            (void *)&stream, (void *)flags, (void *)0x0110fab4, startSizeRate);

    U1Pair *burstDelay = (U1Pair *)((unsigned char *)this + 0x44);
    if (burstDelay->m_x != BfmeZeroRange ||
        burstDelay->m_y != BfmeZeroRange)
        reinterpret_cast<PairWriter>(j_00033384)(
            (void *)&stream, (void *)flags, (void *)0x0110faa4, burstDelay);

    U1Pair *burstCount = (U1Pair *)((unsigned char *)this + 0x50);
    if (burstCount->m_x != BfmeZeroRange ||
        burstCount->m_y != BfmeZeroRange)
        reinterpret_cast<PairWriter>(j_00033384)(
            (void *)&stream, (void *)flags, (void *)0x010f3188, burstCount);

    U1Pair *initialDelay = (U1Pair *)((unsigned char *)this + 0x5c);
    if (initialDelay->m_x != BfmeZeroRange ||
        initialDelay->m_y != BfmeZeroRange)
        reinterpret_cast<PairWriter>(j_00033384)(
            (void *)&stream, (void *)flags, (void *)0x01082de8, initialDelay);

    U1ByteFlagged *groundAligned =
        (U1ByteFlagged *)((unsigned char *)this + 0x80);
    if (groundAligned->m_flag)
        reinterpret_cast<ByteWriter>(j_000014ab)(
            (void *)&stream, (void *)flags, (void *)0x0110fa90, groundAligned);

    U1ByteFlagged *aboveGround =
        (U1ByteFlagged *)((unsigned char *)this + 0x81);
    if (aboveGround->m_flag)
        reinterpret_cast<ByteWriter>(j_000014ab)(
            (void *)&stream, (void *)flags, (void *)0x0110fa74, aboveGround);

    U1ByteFlagged *upTowardsEmitter =
        (U1ByteFlagged *)((unsigned char *)this + 0x82);
    if (upTowardsEmitter->m_flag)
        reinterpret_cast<ByteWriter>(j_000014ab)(
            (void *)&stream, (void *)flags, (void *)0x0110fa54, upTowardsEmitter);

    U1ByteFlagged *maximumHeight =
        (U1ByteFlagged *)((unsigned char *)this + 0x83);
    if (maximumHeight->m_flag)
        reinterpret_cast<ByteWriter>(j_000014ab)(
            (void *)&stream, (void *)flags, (void *)0x0110fa40, maximumHeight);

    writeStreamText(file,
        ((Rva005CB9F0StreamText *)((unsigned char *)&stream))->getText());

    reinterpret_cast<FinishWriter>(j_0004618c)(&file, &flags);

    class ModuleWriter
    {
    public:
        virtual void slot0();
        virtual void slot1();
        virtual void slot2();
        virtual void writeINI(File &file, unsigned int flags) const;
    };

    ModuleWriter *module0 =
        *(ModuleWriter **)((unsigned char *)this + 0xa0);
    if (module0)
        module0->writeINI(file, flags);

    ModuleWriter *module1 =
        *(ModuleWriter **)((unsigned char *)this + 0xa4);
    if (module1)
        module1->writeINI(file, flags);

    ModuleWriter *module2 =
        *(ModuleWriter **)((unsigned char *)this + 0xa8);
    if (module2)
        module2->writeINI(file, flags);

    ((U1Tail_005C97A0 *)((unsigned char *)this + 0xac))->broadcast(
        &file, (void *)flags);

    reinterpret_cast<FinishWriter>(j_0004618c)(&file, &flags);
}
