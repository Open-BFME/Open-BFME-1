"""What the join may name, what it must leave blank, and what it must refuse.

The offsets in reverse/field_names.csv end up in shim declarations, which the
byte gate cannot check: a wrong offset there compiles, links, matches, and
mis-models the struct for every reader afterwards. Upstream's offsets are the
one plausible-looking source of exactly that damage -- BFME moved fields, so
`AttackRange` is +0x14 here and +0x24 upstream -- which is why the missing
offset test asserts a refusal and an empty output, not a repaired row.

The tables are built as a real PE rather than mocked out. Table discovery is
the part with judgement in it (where a run starts, what closes it, which
16-byte window is really an array of 8-byte pairs), and a fixture that handed
the tool a Python list would test none of it.
"""
import importlib.util
import struct
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
REPO = TOOLS.parent
sys.path.insert(0, str(TOOLS))

BASE = 0x400000
TEXT_RVA = 0x1000
TEXT_SIZE = 0x400
RDATA_RVA = 0x2000
HEADERS = 0x400
BINARY = "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
OUT = "reverse/field_names.csv"

fieldnames = importlib.util.module_from_spec(
    importlib.util.spec_from_file_location("fieldnames", TOOLS / "fieldnames.py"))
importlib.util.spec_from_file_location(
    "fieldnames", TOOLS / "fieldnames.py").loader.exec_module(fieldnames)


# ----------------------------------------------------------------- fixture ---

def section(name, rva, size, raw_at, flags):
    return (name.encode().ljust(8, b"\0")
            + struct.pack("<IIII", size, rva, size, raw_at)
            + b"\0" * 12 + struct.pack("<I", flags))


def build_pe(tables):
    """[[(key, offset dword)]] -> (image bytes, [table rva]).

    Every table's address is also planted in .text, the way code that calls
    INI::initFromINI holds it, so a fixture table counts however short it is."""
    pool, offsets = bytearray(), {}
    for run in tables:
        for key, _offset in run:
            if key not in offsets:
                offsets[key] = RDATA_RVA + len(pool)
                pool += key.encode() + b"\0"
    pool += b"\0" * (-len(pool) % 16)

    rvas, body = [], bytearray()
    for run in tables:
        rvas.append(RDATA_RVA + len(pool) + len(body))
        for key, offset in run:
            body += struct.pack("<IIII", offsets[key] + BASE, TEXT_RVA + BASE, 0, offset)
        body += b"\0" * 16

    text = bytearray(b"\xCC" * 16)
    for rva in rvas:
        text += struct.pack("<I", rva + BASE)
    text += b"\xCC" * (TEXT_SIZE - len(text))
    rdata = bytes(pool + body)
    rdata += b"\0" * (-len(rdata) % 0x200)

    head = 0x80
    image = bytearray(b"\0" * HEADERS)
    image[:2] = b"MZ"
    struct.pack_into("<I", image, 0x3C, head)
    image[head:head + 4] = b"PE\0\0"
    struct.pack_into("<HH", image, head + 4, 0x14C, 2)          # machine, sections
    struct.pack_into("<H", image, head + 20, 224)               # optional header size
    struct.pack_into("<I", image, head + 24 + 28, BASE)         # ImageBase
    at = head + 24 + 224
    image[at:at + 40] = section(".text", TEXT_RVA, TEXT_SIZE, HEADERS, 0x60000020)
    image[at + 40:at + 80] = section(".rdata", RDATA_RVA, len(rdata),
                                     HEADERS + TEXT_SIZE, 0x40000040)
    return bytes(image) + bytes(text) + rdata, rvas


def plant(root, tables, upstream):
    """A repo root holding just the two inputs and somewhere to write."""
    image, rvas = build_pe(tables)
    binary = root / BINARY
    binary.parent.mkdir(parents=True)
    binary.write_bytes(image)
    reference = root / "reference" / "CnC_Generals_Zero_Hour"
    reference.mkdir(parents=True)
    (reference / "Fixture.cpp").write_text(upstream)
    (root / "reverse").mkdir()
    return rvas


def entries(key, owner, member):
    return f'\t{{ "{key}", INI::parseReal, NULL, offsetof({owner}, {member}) }},\n'


def run(root):
    return subprocess.run([sys.executable, str(TOOLS / "fieldnames.py"),
                           "--root", str(root)], capture_output=True, text=True)


def read_rows(root):
    lines = (root / OUT).read_text().splitlines()
    assert lines[0] == ",".join(fieldnames.COLUMNS)
    return [dict(zip(fieldnames.COLUMNS, line.split(","))) for line in lines[1:]]


# --------------------------------------------------------------------- RED ---

def test_key_two_upstream_classes_is_ambiguous_and_unnamed(tmp_path):
    """A key two classes define is named only if the table vote reaches it.

    Here the table belongs to Carrier, so neither Alpha nor Beta can claim
    `Shared` -- and picking one would be a coin toss recorded as evidence."""
    table = [("Shared", 0x10), ("One", 0x14), ("Two", 0x18), ("Three", 0x1C)]
    upstream = ("const FieldParse f[] = {\n"
                + entries("Shared", "Alpha", "m_shared")
                + entries("Shared", "Beta", "m_alsoShared")
                + entries("One", "Carrier", "m_one")
                + entries("Two", "Carrier", "m_two")
                + entries("Three", "Carrier", "m_three") + "};\n")
    plant(tmp_path, [table], upstream)

    done = run(tmp_path)
    assert done.returncode == 0, done.stderr
    rows = {row["ini_key"]: row for row in read_rows(tmp_path)}

    shared = rows["Shared"]
    assert shared["upstream_member"] == ""
    assert shared["upstream_class"] == ""
    assert shared["notes"] == "ambiguous: Alpha::m_shared|Beta::m_alsoShared"
    assert (shared["votes"], shared["margin"]) == ("3", "2")   # Carrier 3, Alpha 1
    assert rows["One"]["upstream_class"] == "Carrier"


def test_undecodable_offset_aborts_the_table_and_writes_nothing(tmp_path):
    """The abort names the table, and no row survives carrying a borrowed offset.

    `Broken`'s offset dword is unreadable as a struct offset while upstream
    happily offers 0x40 for the same key. Taking it is the one failure this
    tool cannot be allowed to have, so the run ends with no file at all rather
    than a file whose good rows lend the bad one credibility."""
    good = [("Fine", 0x08), ("AlsoFine", 0x0C), ("StillFine", 0x10)]
    broken = [("Broken", 0x123456), ("Neighbour", 0x14), ("Third", 0x18)]
    upstream = ("const FieldParse f[] = {\n"
                + entries("Broken", "Carrier", "m_broken")      # upstream says 0x40
                + entries("Neighbour", "Carrier", "m_neighbour")
                + entries("Fine", "Carrier", "m_fine") + "};\n")
    rvas = plant(tmp_path, [good, broken], upstream)

    done = run(tmp_path)
    assert done.returncode != 0
    assert f"{rvas[1]:#010x}" in done.stderr, done.stderr
    assert "Broken" in done.stderr
    assert "0x123456" in done.stderr
    assert not (tmp_path / OUT).exists(), "aborting must not leave a partial join"


def test_upstream_index_carries_no_offsets(tmp_path):
    """There is nothing to fall back TO: the join's upstream side is names only."""
    reference = tmp_path / "reference" / "CnC_Generals_Zero_Hour"
    reference.mkdir(parents=True)
    (reference / "Fixture.cpp").write_text(
        "const FieldParse f[] = {\n" + entries("Fine", "Carrier", "m_fine") + "};\n")
    index = fieldnames.upstream_index(tmp_path)
    assert index == {"Fine": [("Carrier", "m_fine")]}


# ------------------------------------------------------------------- GREEN ---

def test_weapon_template_attack_range(tmp_path):
    """AttackRange -> +0x14 -> WeaponTemplate::m_attackRange.

    Both upstream classes really do define AttackRange, so this is the case the
    table vote exists for; the offset is the binary's and differs from
    upstream's, which is the case the offset rule exists for."""
    table = [("PrimaryDamage", 0x08), ("PrimaryDamageRadius", 0x0C),
             ("AttackRange", 0x14), ("MinimumAttackRange", 0x18),
             ("ScatterRadius", 0x28), ("DamageType", 0x2C)]
    upstream = ("const FieldParse WeaponTemplate::TheWeaponTemplateFieldParseTable[] = {\n"
                + entries("PrimaryDamage", "WeaponTemplate", "m_primaryDamage")
                + entries("PrimaryDamageRadius", "WeaponTemplate", "m_primaryDamageRadius")
                + entries("AttackRange", "WeaponTemplate", "m_attackRange")
                + entries("MinimumAttackRange", "WeaponTemplate", "m_minimumAttackRange")
                + entries("ScatterRadius", "WeaponTemplate", "m_scatterRadius")
                + entries("DamageType", "WeaponTemplate", "m_damageType")
                + entries("AttackRange", "SlavedUpdateModuleData", "m_attackRange")
                + "};\n")
    plant(tmp_path, [table], upstream)

    done = run(tmp_path)
    assert done.returncode == 0, done.stderr
    row = {r["ini_key"]: r for r in read_rows(tmp_path)}["AttackRange"]
    assert row["bfme_offset"] == "0x14"
    assert row["upstream_class"] == "WeaponTemplate"
    assert row["upstream_member"] == "m_attackRange"
    assert (row["votes"], row["margin"]) == ("6", "5")
    assert row["notes"] == "vote picked from SlavedUpdateModuleData::m_attackRange"


def test_weapon_cpp_still_says_what_the_fixture_says():
    """The fixture is only evidence while the reference tree still reads this way."""
    weapon = (REPO / "reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine"
              "/Source/GameLogic/Object/Weapon.cpp")
    line = weapon.read_text("utf-8", "replace").splitlines()[176]      # :177
    assert '"AttackRange"' in line
    assert "offsetof(WeaponTemplate, m_attackRange)" in line


# --------------------------------------------------------------- discovery ---

def test_a_pointer_in_the_offset_slot_is_not_a_table(tmp_path):
    """The 8-byte `{name, proc}` pair arrays read at 16-byte stride are not tables.

    Each window's third and fourth dwords are the NEXT pair, so the offset slot
    holds a function pointer -- which is how lua's `getlocal`/`setlocal` table
    in .rdata otherwise arrives here as a field table with three named keys."""
    real = [("Real", 0x08), ("AlsoReal", 0x0C), ("Last", 0x10)]
    pairs = [("getlocal", BASE + TEXT_RVA), ("setlocal", BASE + TEXT_RVA),
             ("setcallhook", BASE + TEXT_RVA)]
    plant(tmp_path, [real, pairs],
          "const FieldParse f[] = {\n" + entries("Real", "Carrier", "m_real") + "};\n")

    done = run(tmp_path)
    assert done.returncode == 0, done.stderr
    keys = [row["ini_key"] for row in read_rows(tmp_path)]
    assert keys == ["Real", "AlsoReal", "Last"]


def test_adjacent_tables_stay_apart(tmp_path):
    """Two runs, two votes: a terminator is what separates one table from the next."""
    first = [("One", 0x08), ("Two", 0x0C), ("Three", 0x10)]
    second = [("Four", 0x08), ("Five", 0x0C)]
    upstream = ("const FieldParse f[] = {\n"
                + entries("One", "Alpha", "m_one") + entries("Two", "Alpha", "m_two")
                + entries("Three", "Alpha", "m_three")
                + entries("Four", "Beta", "m_four") + entries("Five", "Beta", "m_five")
                + "};\n")
    rvas = plant(tmp_path, [first, second], upstream)

    done = run(tmp_path)
    assert done.returncode == 0, done.stderr
    rows = read_rows(tmp_path)
    assert [row["table_rva"] for row in rows] == [f"{rvas[0]:#010x}"] * 3 \
        + [f"{rvas[1]:#010x}"] * 2
    assert {row["upstream_class"] for row in rows} == {"Alpha", "Beta"}


if __name__ == "__main__":
    sys.exit(pytest.main([__file__, "-v"]))
