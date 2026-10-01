"""COFF archive (.lib) reader for ledger rows whose bytes come from a library.

A `.lib` is an `!<arch>` archive whose members are verbatim COFF objects, so a
member extracted from one feeds the same symbol/relocation reader that a
freshly compiled .obj does — see build.py's extract_lib_members.
"""
import struct

# i386 relocation types and the width of the field they patch. A lib member is
# pre-link: every one of these sites holds an addend rather than the address the
# linker later wrote, so a byte comparison against retail has to skip them.
RELOC_WIDTH = {
    0x0006: 4,  # DIR32
    0x0007: 4,  # DIR32NB
    0x000A: 2,  # SECTION
    0x000B: 4,  # SECREL
    0x000C: 4,  # SECREL7
    0x0014: 4,  # REL32
}


def read_archive(path):
    """Return [(member_name, member_bytes)] for every non-linker member."""
    return read_archive_bytes(open(path, "rb").read(), str(path))


def read_archive_bytes(data, label="archive"):
    """Parse one frozen archive payload, also usable for hash-bound verification."""
    if data[:8] != b"!<arch>\n":
        raise ValueError(f"{label}: not an ar archive")
    offset = 8
    longnames = b""
    members = []
    while offset < len(data):
        if len(data) - offset < 60:
            raise ValueError(f"{label}: truncated archive member header at {offset}")
        header = data[offset:offset + 60]
        if header[58:60] != b"`\n":
            raise ValueError(f"{label}: invalid archive member terminator at {offset}")
        name = header[0:16].decode("latin1").rstrip()
        size_text = header[48:58].strip(b" ")
        if not size_text or not size_text.isdigit():
            raise ValueError(f"{label}: invalid archive member size at {offset}")
        size = int(size_text)
        body_start = offset + 60
        body_end = body_start + size
        if body_end > len(data):
            raise ValueError(f"{label}: truncated archive member body at {offset}")
        if size & 1 and body_end == len(data):
            raise ValueError(f"{label}: missing odd archive member padding at {offset}")
        body = data[body_start:body_end]
        offset = body_end + (size & 1)  # members are 2-byte aligned
        if name == "/":
            continue  # linker symbol index
        if name == "//":
            longnames = body
            continue
        if name.startswith("/"):
            # A name too long for the 16-byte field is an offset into //.
            reference = name[1:]
            if not reference or not reference.isascii() or not reference.isdecimal():
                raise ValueError(f"{label}: invalid archive long-name offset")
            start = int(reference)
            if start >= len(longnames):
                raise ValueError(f"{label}: archive long-name offset out of range")
            end = longnames.find(b"\0", start)
            if end < 0:
                raise ValueError(f"{label}: unterminated archive long name")
            name = longnames[start:end].decode("latin1")
        members.append((name.rstrip("/"), body))
    return members
