#!/usr/bin/env python3
"""Read and edit an EA APT movie (`<Name>.apt`).

An `.apt` is a **memory image addressed by file offset**: every internal
reference is an absolute offset into the file, and the loader fixes them up
against the load address. So anything that changes a length moves every
following offset, and a naive rewrite silently corrupts the movie.

This editor never moves a byte. New structures are appended past the end and
the only existing bytes it touches are fixed-size scalar fields patched in
place. That makes a no-op edit byte-identical by construction, keeps every
offset in the original valid, and means a mistake is a visibly wrong screen
rather than a subtly corrupt one.

    Apt Data:6\x1a\0                     12-byte magic
    import table   count x { u32 movie name, u32 symbol name, u32 char id, u32 }
    string pool
    character table  count x u32 offset -- 0 where the character is imported
    movie header (the type-9 character), immediately after the table
      +0x08 u32 frame count      +0x0c u32 frames offset
      +0x14 u32 character count  +0x18 u32 character table offset
      +0x1c u32 width            +0x20 u32 height
      +0x28 u32 import count     +0x2c u32 import table offset

    each character   { u32 type, u32 0x09876543, ... }
      1 shape   2 text   3 font   4 button   5 sprite   7 image   9 movie
    frames         count x { u32 op count, u32 ops offset }
    ops            op count x u32 offset, each to a type-tagged op struct
      1 DoAction (bytecode)  2 FrameLabel  3 PlaceObject  4 RemoveObject
      5 SetBackgroundColor

Nothing in the file says where the movie header is: it holds the character table
offset, and the character table is what would otherwise tell you where the movie
is. So the root is found by scanning for the single `{9, 0x09876543}` a movie
contains, and `Apt` refuses to open a file that does not have exactly one.

Run this file on any `.apt` to self-check: it parses, re-emits with no edit and
compares, then prints the movie's structure.
"""
import re
import struct
import sys

MAGIC = b"Apt Data:6\x1a\0"
SIG = 0x09876543

# Character types, by the tag every character carries in its first word.
SHAPE, TEXT, FONT, BUTTON, SPRITE, IMAGE, MOVIE = 1, 2, 3, 4, 5, 7, 9

# Frame op types.
DO_ACTION, FRAME_LABEL, PLACE_OBJECT, REMOVE_OBJECT, SET_BG_COLOR = 1, 2, 3, 4, 5

# A PlaceObject whose character is 0xffffffff names no new character: it edits
# whatever already occupies its depth (a move, a recolour, a removal).
NO_CHAR = 0xFFFFFFFF

PLACE_SIZE = 0x40

# A type-2 text character, 0x3c bytes. The two fields that decide whether a
# string looks native are the font id and the size: the Options screen's panel
# labels are font 0xa at 18pt, its BUTTON labels are font 0x1e at 16pt, and
# placing one where the other belongs is immediately visible.
TEXT_SIZE = 0x3C
FONT_LABEL, FONT_BUTTON = 0x0A, 0x1E
ALIGN_LEFT, ALIGN_CENTER = 0, 2


class Apt:
    def __init__(self, data):
        if isinstance(data, str):
            data = open(data, "rb").read()
        if not data.startswith(MAGIC):
            raise ValueError(f"not an APT movie (magic {data[:12]!r})")
        self.d = bytearray(data)
        hits = [m.start() for m in
                re.finditer(re.escape(struct.pack("<2I", MOVIE, SIG)), data)]
        if len(hits) != 1:
            raise ValueError(f"expected exactly one type-9 movie character, found {len(hits)}")
        self.hdr = hits[0]

    # -- reading -------------------------------------------------------------

    def u32(self, off):
        return struct.unpack_from("<I", self.d, off)[0]

    def f32(self, off):
        return struct.unpack_from("<f", self.d, off)[0]

    def string(self, off):
        """The NUL-terminated string at `off`, or None for a null pointer."""
        if off == 0 or off >= len(self.d):
            return None
        end = self.d.index(b"\0", off)
        return self.d[off:end].decode("latin1")

    @property
    def frame_count(self):
        return self.u32(self.hdr + 0x08)

    @property
    def frames_off(self):
        return self.u32(self.hdr + 0x0C)

    @property
    def char_count(self):
        return self.u32(self.hdr + 0x14)

    @property
    def char_table(self):
        return self.u32(self.hdr + 0x18)

    @property
    def imports(self):
        """-> [(movie, symbol, char_id)], the characters other packages supply."""
        n, off = self.u32(self.hdr + 0x28), self.u32(self.hdr + 0x2C)
        return [(self.string(self.u32(off + 16 * i)),
                 self.string(self.u32(off + 16 * i + 4)),
                 self.u32(off + 16 * i + 8)) for i in range(n)]

    def char_off(self, cid):
        """Where character `cid` is defined, or 0 when it is imported."""
        if cid == NO_CHAR:
            raise ValueError("NO_CHAR names no character -- the op edits a depth")
        if not 0 <= cid < self.char_count:
            raise ValueError(f"character {cid} is outside the table of {self.char_count}")
        return self.u32(self.char_table + 4 * cid)

    def char_type(self, cid):
        """The character's type tag, or None when another package supplies it."""
        off = self.char_off(cid)
        return self.u32(off) if off else None

    def frames_of(self, cid=None):
        """-> [(op_count, ops_off)] for the movie, or for sprite `cid`."""
        if cid is None:
            n, off = self.frame_count, self.frames_off
        else:
            off = self.char_off(cid)
            if not off or self.u32(off) != SPRITE:
                raise ValueError(f"character {cid} is not a sprite")
            n, off = self.u32(off + 8), self.u32(off + 12)
        return [(self.u32(off + 8 * i), self.u32(off + 8 * i + 4)) for i in range(n)]

    def ops(self, frame, cid=None):
        """-> [op offset] for one frame."""
        n, off = self.frames_of(cid)[frame]
        return [self.u32(off + 4 * i) for i in range(n)]

    def place_info(self, off):
        """-> dict for the PlaceObject op at `off`."""
        if self.u32(off) != PLACE_OBJECT:
            raise ValueError(f"op at {off:#x} is type {self.u32(off)}, not PlaceObject")
        char = self.u32(off + 0x0C)
        return dict(flags=self.u32(off + 4), depth=self.u32(off + 8),
                    char=None if char == NO_CHAR else char,
                    x=self.f32(off + 0x20), y=self.f32(off + 0x24),
                    name=self.string(self.u32(off + 0x34)))

    def labels(self, cid=None):
        """-> {label: frame}, what gotoAndPlay can name."""
        out = {}
        for f in range(len(self.frames_of(cid))):
            for o in self.ops(f, cid):
                if self.u32(o) == FRAME_LABEL:
                    out[self.string(self.u32(o + 4))] = f
        return out

    # -- appending -----------------------------------------------------------

    def _append(self, blob):
        while len(self.d) % 4:
            self.d += b"\0"
        at = len(self.d)
        self.d += blob
        return at

    def _append_string(self, text):
        return self._append(text.encode("latin1") + b"\0")

    def place(self, frame, char, depth, x, y, name=None, cid=None,
              flags=None, scale=(1.0, 0.0, 0.0, 1.0), color=0xFFFFFFFF):
        """Add a PlaceObject to `frame` of the movie (or of sprite `cid`).

        Appends the op, then a fresh op-pointer array one entry longer, then
        repoints the frame at it. The frame's old array is left where it is --
        orphaned, but nothing else refers to it and leaving it costs a few bytes
        against moving every offset after it."""
        if self.char_off(char) == 0 and char not in {c for _, _, c in self.imports}:
            raise ValueError(f"character {char} is neither defined here nor imported")
        name_off = self._append_string(name) if name else 0
        # 0xa6 is what the authored widget placements carry; 0x1e is a plain
        # nested clip. The difference is the name, so pick by whether we have one.
        if flags is None:
            flags = 0xA6 if name else 0x1E
        op = struct.pack("<4I4f2f4I", PLACE_OBJECT, flags, depth, char,
                         *scale, x, y, color, 0, 0, name_off) + \
            struct.pack("<2I", 0xFFFFFFFF, 0)
        assert len(op) == PLACE_SIZE, len(op)
        op_off = self._append(op)

        old = self.ops(frame, cid)
        arr = self._append(struct.pack(f"<{len(old) + 1}I", *old, op_off))
        self._set_frame(frame, len(old) + 1, arr, cid)
        return op_off

    def _set_frame(self, frame, count, ops_off, cid=None):
        if cid is None:
            base = self.frames_off
        else:
            base = self.u32(self.char_off(cid) + 12)
        struct.pack_into("<2I", self.d, base + 8 * frame, count, ops_off)

    def add_character(self, blob):
        """Append a character and give it a new id.

        The character table is an array the movie header points at, so growing
        it means appending a fresh copy one entry longer and repointing the
        header. The old table is orphaned; nothing else refers to it."""
        if len(blob) < 8 or struct.unpack_from("<I", blob, 4)[0] != SIG:
            raise ValueError("a character must carry the 0x09876543 signature")
        at = self._append(blob)
        n = self.char_count
        old = [self.u32(self.char_table + 4 * i) for i in range(n)]
        table = self._append(struct.pack(f"<{n + 1}I", *old, at))
        struct.pack_into("<2I", self.d, self.hdr + 0x14, n + 1, table)
        return n

    def add_text(self, text, font=FONT_LABEL, size=18.0, color=0xFFFFFFFF,
                 align=ALIGN_LEFT, width=230.0, height=23.5):
        """Append a text character showing `text`, and return its id.

        A string with no leading `$` renders literally -- the runtime only goes
        to the string table for `$`-prefixed tokens -- so our own words need no
        CSF entry and no lang/english.big edit."""
        blob = struct.pack("<2I4f3If3I2I", TEXT, SIG,
                           -2.0, -2.0, width, height,
                           font, align, color, size,
                           1, 0, 0,
                           self._append_string(text), self._append_string(""))
        if len(blob) != TEXT_SIZE:
            raise ValueError(f"text character is {len(blob)} bytes, expected {TEXT_SIZE}")
        return self.add_character(blob)

    # -- patching in place ---------------------------------------------------

    def set_place_char(self, op_off, char):
        """Retarget an existing PlaceObject at another character."""
        if self.u32(op_off) != PLACE_OBJECT:
            raise ValueError(f"op at {op_off:#x} is not a PlaceObject")
        struct.pack_into("<I", self.d, op_off + 0x0C, char)

    def set_text_string(self, cid, text):
        """Replace a text character's initial string.

        The new string is appended and the character repointed at it, rather
        than the old bytes being overwritten -- a string may be shared, and
        editing one in place would change every character that reads it."""
        off = self.char_off(cid)
        if not off or self.u32(off) != TEXT:
            raise ValueError(f"character {cid} is not a text character")
        struct.pack_into("<I", self.d, off + 0x34, self._append_string(text))

    def set_place_pos(self, op_off, x, y):
        if self.u32(op_off) != PLACE_OBJECT:
            raise ValueError(f"op at {op_off:#x} is not a PlaceObject")
        struct.pack_into("<2f", self.d, op_off + 0x20, x, y)

    def bytes(self):
        return bytes(self.d)


def _selfcheck(path):
    src = open(path, "rb").read()
    a = Apt(src)
    if a.bytes() != src:
        raise SystemExit("FAIL: re-emit with no edit is not byte-identical")
    print(f"{path}: round-trip byte-identical ({len(src):,} B)")
    print(f"  {a.frame_count} frames, {a.char_count} characters, "
          f"{len(a.imports)} imports, {a.u32(a.hdr+0x1c)}x{a.u32(a.hdr+0x20)}")
    kinds = {}
    for c in range(a.char_count):
        t = a.char_type(c)
        kinds[t] = kinds.get(t, 0) + 1
    names = {SHAPE: "shape", TEXT: "text", FONT: "font", BUTTON: "button",
             SPRITE: "sprite", IMAGE: "image", MOVIE: "movie", None: "imported"}
    print("  " + ", ".join(f"{v} {names.get(k, k)}" for k, v in sorted(
        kinds.items(), key=lambda kv: -kv[1])))
    lab = a.labels()
    if lab:
        print("  labels: " + ", ".join(f"{k}@{v}" for k, v in sorted(lab.items(),
                                                                    key=lambda kv: kv[1])))


if __name__ == "__main__":
    for p in sys.argv[1:] or ["Options.apt"]:
        _selfcheck(p)
