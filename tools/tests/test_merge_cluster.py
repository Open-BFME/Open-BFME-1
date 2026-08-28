"""What `--apply` may move, what it must refuse, and what it may never delete.

The merge driver edits reverse/functions.csv, so the terminator test is not
decoration: the ledger legitimately mixes \\r\\r\\n, \\r\\n and bare \\n
(tools/ledger_io.py:1-14) and every naive rewrite has silently dropped or
invented rows. A row count that survives a repoint but a terminator that does
not is a whole-file diff to the union merge driver.

The refusals matter more than the happy path. 24 files in the tree carry bodies
for more than one destination (`ini_parsers.cpp` for ten), so deleting a donor
because one of its markers was drained would destroy another cluster's
un-migrated work -- the single way this tool could lose code. And two siblings
that disagree about a member's offset cannot both be right; merging them
produces a TU that byte-matches one symbol while silently mis-modelling the
other, which is exactly what ./build.sh cannot see.
"""
import importlib.util
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
DEST = "Code/GameEngine/Source/Common/RTS/Team.cpp"
OTHER = "Code/GameEngine/Source/Common/INI/ini.cpp"
MERGED = "Code/GameEngine/Source/Common/RTS/TeamPrototypeInstanceWalks.cpp"


def _load(name):
    if name not in sys.modules:
        spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
        module = importlib.util.module_from_spec(spec)
        sys.modules[name] = module
        spec.loader.exec_module(module)
    return sys.modules[name]


merge_cluster = _load("merge_cluster")
check_csv = _load("check_csv")
ledger_io = _load("ledger_io")


# --------------------------------------------------------------- fixtures ---

def sibling(symbol, dest, pad="0x274", extra_marker=None, extra_body=""):
    """One cluster member: a shim class pair plus the one body it holds."""
    plain = symbol.split("@")[0].lstrip("?")
    markers = f"// readable body of {symbol}: {dest}\n"
    if extra_marker:
        markers += f"// readable body of {extra_marker[0]}: {extra_marker[1]}\n"
    return f"""// cl: /DNDEBUG /MD /EHsc
{markers}
typedef bool Bool;

class Team
{{
public:
\tBool {plain}() const;
}};

class TeamPrototype
{{
public:
\tBool {plain}( void ) const;

private:
\tunsigned char m_unmodelled_000[ {pad} ];
\tTeam *m_teamInstanceList;\t\t// +0x274
}};

// {symbol}
Bool TeamPrototype::{plain}( void ) const
{{
\treturn m_teamInstanceList != 0;
}}
{extra_body}"""


def repo(tmp_path, sources, rows):
    """A tree merge_cluster can operate on: sources, a ledger, and a git index.

    `rows` are (name, source, terminator) so a test can choose the mix of line
    endings the real ledger carries."""
    for rel, text in sources.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    ledger = tmp_path / "reverse" / "functions.csv"
    ledger.parent.mkdir(parents=True, exist_ok=True)
    payload = (HEADER + "\r\n").encode()
    for name, source, term in rows:
        payload += f"{name},,0x000F0000,52,{source},matched,".encode() + term
    ledger.write_bytes(payload)
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True,
                   capture_output=True)
    git = ["git", "-C", str(tmp_path), "-c", "user.name=t", "-c", "user.email=t@t"]
    subprocess.run([*git, "add", "-A"], check=True, capture_output=True)
    # Committed, so `git diff --cached` has a HEAD to show a staged deletion
    # against -- which is the thing --apply has to get right.
    subprocess.run([*git, "commit", "-qm", "fixture"], check=True, capture_output=True)
    return ledger


def terminators(raw):
    return [match.group(0) for match in ledger_io.TERM.finditer(raw)]


def sources_of(ledger):
    return [ledger_io.fields(payload)[4]
            for _n, payload, _t in merge_cluster.records(ledger)][1:]


def run(*argv):
    return merge_cluster.main(list(argv))


# ------------------------------------------------- siblings that disagree ---

def test_a_member_declared_at_two_offsets_is_reported_and_blocks_apply(tmp_path, capsys):
    """Two shims cannot both be right about where m_unmodelled_000 ends, and a
    merged TU that picks one silently mis-models the other body."""
    a = "Code/GameEngine/Source/Common/RTS/TeamPrototype_hasAnyUnits.cpp"
    b = "Code/GameEngine/Source/Common/RTS/TeamPrototype_countBuildings.cpp"
    ledger = repo(tmp_path, {
        a: sibling("?hasAnyUnits@TeamPrototype@@QBE_NXZ", DEST, pad="0x274"),
        b: sibling("?countBuildings@TeamPrototype@@QAEHXZ", DEST, pad="0x280"),
        MERGED: "// merged\n",
    }, [("?hasAnyUnits@TeamPrototype@@QBE_NXZ", a, b"\r\n"),
        ("?countBuildings@TeamPrototype@@QAEHXZ", b, b"\r\n")])
    before = ledger.read_bytes()

    run("--plan", DEST, "--root", str(tmp_path))
    plan = capsys.readouterr().out
    assert "members declared differently by two siblings" in plan
    assert "TeamPrototype::m_unmodelled_000" in plan, plan
    assert "0x274" in plan and "0x280" in plan, plan

    with pytest.raises(SystemExit) as exc:
        run("--apply", DEST, "--into", MERGED, "--only", a, b, "--root", str(tmp_path))

    assert exc.value.code == 1
    assert "m_unmodelled_000" in capsys.readouterr().err
    assert ledger.read_bytes() == before, "a refusal must not touch the ledger"
    assert (tmp_path / a).exists() and (tmp_path / b).exists()


def test_a_const_overload_is_a_reconciliation_not_a_contradiction(tmp_path, capsys):
    """The real Team.cpp merge turns on this: `iterate_TeamInstanceList()` and its
    const twin are legal in one TU, so they are reported and not refused."""
    a = "Code/GameEngine/Source/Common/RTS/TeamPrototype_hasAnyUnits.cpp"
    b = "Code/GameEngine/Source/Common/RTS/TeamPrototype_countBuildings.cpp"
    walk = "\n\tBfmeIterator walk() const\n\t{\n\t\treturn BfmeIterator( 0 );\n\t}\n"
    ledger = repo(tmp_path, {
        a: sibling("?hasAnyUnits@TeamPrototype@@QBE_NXZ", DEST, extra_body=walk),
        b: sibling("?countBuildings@TeamPrototype@@QAEHXZ", DEST,
                   extra_body=walk.replace(" const\n", "\n")),
        MERGED: "// merged\n",
    }, [("?hasAnyUnits@TeamPrototype@@QBE_NXZ", a, b"\r\n"),
        ("?countBuildings@TeamPrototype@@QAEHXZ", b, b"\r\n")])

    run("--plan", DEST, "--root", str(tmp_path))
    plan = capsys.readouterr().out
    assert "BfmeIterator walk() const" in plan, "the difference must still be reported"
    assert "must be reconciled before --apply): 0" in plan, plan

    assert run("--apply", DEST, "--into", MERGED, "--only", a, b,
               "--root", str(tmp_path)) == 0
    assert sources_of(ledger) == [MERGED, MERGED]


# ------------------------------------------------------------ terminators ---

def test_every_terminator_survives_a_repoint(tmp_path):
    """functions.csv mixes all three; a rewrite that normalises them hands the
    union merge driver a brand-new line for every row it did not change."""
    a = "Code/GameEngine/Source/Common/RTS/TeamPrototype_hasAnyUnits.cpp"
    keep = "Code/GameEngine/Source/Common/RTS/Untouched.cpp"
    ledger = repo(tmp_path, {
        a: sibling("?hasAnyUnits@TeamPrototype@@QBE_NXZ", DEST),
        keep: "// nothing to see\n",
        MERGED: "// merged\n",
    }, [("?alpha@@YAXXZ", keep, b"\r\r\n"),
        ("?hasAnyUnits@TeamPrototype@@QBE_NXZ", a, b"\r\r\n"),
        ("?beta@@YAXXZ", keep, b"\r\n"),
        ("?gamma@@YAXXZ", keep, b"\n")])
    before = ledger.read_bytes()

    assert run("--apply", DEST, "--into", MERGED, "--only", a,
               "--root", str(tmp_path)) == 0

    after = ledger.read_bytes()
    assert terminators(after) == terminators(before)
    assert set(terminators(after)) == {b"\r\n", b"\r\r\n", b"\n"}, "fixture lost its mix"
    assert sources_of(ledger) == [keep, MERGED, keep, keep]
    problems = []
    check_csv.check_functions(after, problems, {keep, MERGED})
    assert problems == []


# --------------------------------------------------------------- refusals ---

def test_apply_refuses_an_into_that_does_not_exist(tmp_path, capsys):
    a = "Code/GameEngine/Source/Common/RTS/TeamPrototype_hasAnyUnits.cpp"
    ledger = repo(tmp_path, {a: sibling("?hasAnyUnits@TeamPrototype@@QBE_NXZ", DEST)},
                  [("?hasAnyUnits@TeamPrototype@@QBE_NXZ", a, b"\r\n")])
    before = ledger.read_bytes()

    with pytest.raises(SystemExit) as exc:
        run("--apply", DEST, "--into", MERGED, "--only", a, "--root", str(tmp_path))

    assert exc.value.code == 1
    assert "does not exist on disk" in capsys.readouterr().err
    assert ledger.read_bytes() == before
    assert (tmp_path / a).exists(), "the donor must survive a refusal"


def test_apply_requires_only(tmp_path, capsys):
    """A whole-cluster merge would repoint rows for bodies the TU does not hold."""
    a = "Code/GameEngine/Source/Common/RTS/TeamPrototype_hasAnyUnits.cpp"
    ledger = repo(tmp_path, {a: sibling("?hasAnyUnits@TeamPrototype@@QBE_NXZ", DEST),
                             MERGED: "// merged\n"},
                  [("?hasAnyUnits@TeamPrototype@@QBE_NXZ", a, b"\r\n")])
    before = ledger.read_bytes()

    with pytest.raises(SystemExit) as exc:
        run("--apply", DEST, "--into", MERGED, "--root", str(tmp_path))

    assert exc.value.code == 1
    assert "required, not optional" in capsys.readouterr().err
    assert ledger.read_bytes() == before


def test_apply_refuses_a_file_with_no_marker_for_this_destination(tmp_path, capsys):
    a = "Code/GameEngine/Source/Common/RTS/TeamPrototype_hasAnyUnits.cpp"
    stray = "Code/GameEngine/Source/Common/RTS/TeamPrototype_hasAnyObjects.cpp"
    ledger = repo(tmp_path, {
        a: sibling("?hasAnyUnits@TeamPrototype@@QBE_NXZ", DEST),
        stray: "// cl: /DNDEBUG /MD /EHsc\n// no marker, so not in the cluster\n",
        MERGED: "// merged\n",
    }, [("?hasAnyUnits@TeamPrototype@@QBE_NXZ", a, b"\r\n"),
        ("?hasAnyObjects@TeamPrototype@@QBE_NXZ", stray, b"\r\n")])
    before = ledger.read_bytes()

    with pytest.raises(SystemExit) as exc:
        run("--apply", DEST, "--into", MERGED, "--only", a, stray, "--root", str(tmp_path))

    assert exc.value.code == 1
    assert "carries no" in capsys.readouterr().err
    assert ledger.read_bytes() == before


# --------------------------------------- a donor bound for two destinations ---

def test_a_donor_holding_a_second_destinations_body_is_never_deleted(tmp_path, capsys):
    """ini_parsers.cpp is claimed by ten destinations. Draining one of them must
    leave the other nine's bodies exactly where they are."""
    shared = "Code/GameEngine/Source/Common/RTS/INIParseSoundsListThunk.cpp"
    ledger = repo(tmp_path, {
        shared: sibling("?hasAnyUnits@TeamPrototype@@QBE_NXZ", DEST,
                        extra_marker=("?parseSoundsList@INI@@", OTHER),
                        extra_body="\n// ?parseSoundsList@INI@@\n"
                                   "void parseSoundsList( void )\n{\n}\n"),
        MERGED: "// merged\n",
    }, [("?hasAnyUnits@TeamPrototype@@QBE_NXZ", shared, b"\r\n"),
        ("?parseSoundsList@INI@@SAXPAV1@PAX1PBX@Z", shared, b"\r\n")])

    assert run("--apply", DEST, "--into", MERGED, "--only", shared,
               "--root", str(tmp_path)) == 0

    assert "kept 1 donor(s)" in capsys.readouterr().out
    assert (tmp_path / shared).exists(), "deleting it would destroy the ini.cpp body"
    text = (tmp_path / shared).read_text()
    assert f"// readable body of ?parseSoundsList@INI@@: {OTHER}" in text
    assert "void parseSoundsList( void )" in text
    assert f": {DEST}" not in text, "the drained marker must go, or the cluster lies"
    assert sources_of(ledger) == [MERGED, shared]


# ------------------------------------------------------------------ green ---

def test_only_moves_and_deletes_exactly_the_named_files(tmp_path, capsys):
    """Five siblings, three named: a cluster is drained over several commits."""
    names = ["hasAnyUnits", "countBuildings", "hasAnyBuildFacility",
             "updateState", "teamAboutToBeDeleted"]
    files = {f"Code/GameEngine/Source/Common/RTS/TeamPrototype_{n}.cpp": f"?{n}@TeamPrototype@@QBE_NXZ"
             for n in names}
    sources = {rel: sibling(symbol, DEST) for rel, symbol in files.items()}
    chosen = list(files)[:3]
    untouched = list(files)[3:]
    # The merged TU carries the drained bodies' markers, so it joins the cluster
    # it is draining -- which is what lets the next commit merge into it again.
    sources[MERGED] = "".join(f"// readable body of {files[rel]}: {DEST}\n"
                              for rel in chosen)
    ledger = repo(tmp_path, sources,
                  [(symbol, rel, b"\r\n") for rel, symbol in files.items()])

    assert run("--apply", DEST, "--into", MERGED, "--only", *chosen,
               "--root", str(tmp_path)) == 0

    out = capsys.readouterr().out
    assert out.count("  repointed ") == 3, out
    assert sources_of(ledger) == [MERGED, MERGED, MERGED, *untouched]
    for rel in chosen:
        assert not (tmp_path / rel).exists()
    for rel in untouched:
        assert (tmp_path / rel).exists()
    assert "cluster now: 3 file(s) still carry a marker" in out, out
    staged = subprocess.run(["git", "-C", str(tmp_path), "diff", "--cached",
                             "--name-status"], capture_output=True, text=True).stdout
    assert sorted(line.split("\t")[1] for line in staged.splitlines()
                  if line.startswith("D")) == sorted(chosen)


def test_the_merged_file_may_not_be_its_own_donor(tmp_path, capsys):
    a = "Code/GameEngine/Source/Common/RTS/TeamPrototype_hasAnyUnits.cpp"
    ledger = repo(tmp_path, {a: sibling("?hasAnyUnits@TeamPrototype@@QBE_NXZ", DEST)},
                  [("?hasAnyUnits@TeamPrototype@@QBE_NXZ", a, b"\r\n")])
    before = ledger.read_bytes()

    with pytest.raises(SystemExit) as exc:
        run("--apply", DEST, "--into", a, "--only", a, "--root", str(tmp_path))

    assert exc.value.code == 1
    assert "its own donor" in capsys.readouterr().err
    assert ledger.read_bytes() == before
