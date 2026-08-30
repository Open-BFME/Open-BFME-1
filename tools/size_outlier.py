"""Find rows whose body is a FORWARDER where its siblings are implementations.

The fourth false-green detector, and the only one that catches a stub with no
E9 to follow and no second name to compare against.

`?reverseAnimateWindow@ProcessAnimateWindowSlideFromBottomTimed@@` claimed five
bytes -- `mov eax,[ecx]; jmp [eax+0x0C]`, a virtual-dispatch thunk -- while the
three other reverseAnimateWindow implementations in retail are 260 to 263 bytes.
Neither existing instrument could see it: the ILT topology test needs an E9 to
follow, and multi_name's structural comparison cannot separate two forwarders to
the same vtable slot because they genuinely are the same five bytes. What gave it
away was the family: a real implementation of that method is 260 bytes, so a
five-byte one is delegating, and the name is a claim the body does not support.

TWO CONDITIONS, AND BOTH ARE LOAD-BEARING:

  * SMALL AGAINST ITS FAMILY -- at most a quarter of the median size of the same
    method name across three or more classes, with the median itself at least 48
    bytes so a family of trivial accessors says nothing. On its own this flags
    104 rows, most of them honest: a virtual method is perfectly entitled to a
    tiny override, and `?onEnter@AIBusyState@@` really is three bytes.
  * THE BODY TAIL-JUMPS -- ends in an E9 rel32, or an FF /4 indirect jump
    (vtable dispatch, adjustor thunk). A forwarder delegates; an implementation
    returns. Adding this takes 104 to 14.

It is a CANDIDATE list. A file named `...Thunk.cpp` may hold a thunk on purpose,
and some of the fourteen will be honest. What it does is put the question in
front of someone, which nothing else here does.

FOUR DETECTORS NOW, AND NONE SUBSUMES ANOTHER. Each is blind exactly where
another sees, so a clean run from one is not a clean bill of health:

  * the ILT unique-stub test follows an E9 to ask which body a stub reaches --
    blind when there is no E9, and it cannot say whose the body is when shared;
  * multi_name compares masked bytes and reloc SITES -- blind to two forwarders
    to the same vtable slot, because they genuinely are the same bytes;
  * multi_name's FAMILY rule reasons from names -- blind when a stub carries only
    one name, which is most of them;
  * this one reasons from a method's family SIZE -- blind when a class has no
    siblings implementing the same method.

`0x0000B9CE` is the worked example: two unrelated names on a stub into a 74-byte
`?reset@NetCommandList@@`. multi_name does NOT flag it, correctly, because four
5-byte jmp thunks are structurally identical. It falls out here instead.

AND ONE THING NO DETECTOR HERE CAN DO: none of them establishes IDENTITY. A
matched caller that names the symbol outranks every inference in this file --
five re-homings were retracted for exactly that reason. Treat every verdict here
as a question to put to the call sites.
"""
import collections
import re
import statistics
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B  # noqa: E402

MIN_CLASSES = 3      # a "family" needs at least this many classes to have a median
MIN_MEDIAN = 48      # below this the family is trivial accessors and says nothing
RATIO = 4            # flag a member at or below median/RATIO


def _image():
    data = (B.ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe").read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    nsec = struct.unpack_from("<H", data, pe + 6)[0]
    opt = struct.unpack_from("<H", data, pe + 20)[0]
    secs = []
    for i in range(nsec):
        o = pe + 24 + opt + i * 40
        vsz, va, rsz, ptr = struct.unpack_from("<IIII", data, o + 8)
        secs.append((va, vsz, ptr, rsz))
    return data, secs


def reader(data, secs):
    def read(rva, size):
        for va, vsz, ptr, rsz in secs:
            if va <= rva < va + max(vsz, rsz):
                o = ptr + (rva - va)
                return data[o:o + size]
        return None
    return read


def tail_jumps(body):
    """Does this body END in a tail jump -- E9 rel32, or FF /4 indirect?

    Only the last few bytes count. A jump in the middle is control flow; a jump
    at the end is delegation."""
    if body is None or len(body) < 2:
        return False
    if len(body) >= 5 and body[len(body) - 5] == 0xE9:
        return True
    for i in range(max(0, len(body) - 8), len(body) - 1):
        if body[i] == 0xFF and (body[i + 1] >> 3) & 7 == 4:
            return True
    return False


def families(rows):
    by = collections.defaultdict(list)
    for row in rows:
        m = re.match(r"^\?([A-Za-z_0-9]+)@([A-Za-z_0-9]+)@@", row["name"])
        if m:
            by[m.group(1)].append((int(row["target_size"]), m.group(2), row))
    return by


def outliers(rows, read):
    """Yield (median, size, method, cls, row) for each forwarder-shaped outlier."""
    for method, members in sorted(families(rows).items()):
        if len({c for _, c, _ in members}) < MIN_CLASSES:
            continue
        median = statistics.median(sorted(s for s, _, _ in members))
        if median < MIN_MEDIAN:
            continue
        for size, cls, row in members:
            if size * RATIO <= median and tail_jumps(read(int(row["target_rva"], 16), size)):
                yield median, size, method, cls, row


def method_and_class(name):
    m = re.match(r"^\?([A-Za-z_0-9]+)@([A-Za-z_0-9]+)@@", name)
    if m:
        return m.group(1), m.group(2)
    m = re.match(r"^\?\?[01]([A-Za-z_0-9]+)@@", name)   # ctor/dtor name the class directly
    if m:
        return "~ctor/dtor", m.group(1)
    return None, None


def callers_of(rows, addresses, data, secs):
    """address -> [names of matched rows containing a direct call to it]."""
    def off(rva):
        for va, vsz, ptr, rsz in secs:
            if va <= rva < va + max(vsz, rsz):
                return ptr + (rva - va)
    found = collections.defaultdict(list)
    for row in rows:
        try:
            rva, size = int(row["target_rva"], 16), int(row["target_size"])
        except ValueError:
            continue
        o = off(rva)
        if o is None or size > 4000:
            continue
        body = data[o:o + size]
        for i in range(len(body) - 4):
            if body[i] == 0xE8:
                t = (rva + i + 5 + struct.unpack_from("<i", body, i + 1)[0]) & 0xFFFFFFFF
                if t in addresses:
                    found[t].append(row["name"])
    return found


def verdict(method, cls, caller_names):
    """A CALL SITE OUTRANKS THE SIZE HEURISTIC, and it clears far more than it
    confirms. The dominant false positive is base-class delegation: Pipe::Flush
    is 17 bytes precisely BECAUSE Base64Pipe::Flush is 299 and does the work, so
    the family median -- which counts the derived implementations -- makes every
    base look like an outlier. A caller with the SAME method name in a DIFFERENT
    class is a derived override calling its base, and that clears it."""
    same_method, own_class = [], []
    for name in caller_names:
        m, k = method_and_class(name)
        if m == method and k != cls:
            same_method.append(name)
        elif k == cls:
            own_class.append(name)
    if same_method:
        return "CLEARED - a derived override delegates to this base"
    if own_class:
        return "CLEARED - called by its own class"
    if caller_names:
        return "callers exist, none same-method or same-class"
    return "UNDECIDED - no matched caller"


def main(argv):
    rows = [r for r in B.load_function_rows() if r["status"] == "matched"]
    data, secs = _image()
    found = sorted(outliers(rows, reader(data, secs)), key=lambda t: (-t[0], t[1]))
    calls = callers_of(rows, {int(r["target_rva"], 16) for *_, r in found}, data, secs)
    tally = collections.Counter()
    print("forwarder-shaped size outliers: %d" % len(found))
    for median, size, method, cls, row in found:
        names = sorted(set(calls.get(int(row["target_rva"], 16), [])))
        v = verdict(method, cls, names)
        tally[v.split(" - ")[0]] += 1
        print("  %4dB vs family median %5.0fB  %-26s %-22s %s"
              % (size, median, method[:26], cls[:22], v))
    print("\n" + ", ".join("%s=%d" % kv for kv in sorted(tally.items())))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
