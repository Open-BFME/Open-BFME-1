from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import worldbuilder_mfc as m


class MfcEvidence(unittest.TestCase):
    def test_verified_code_and_data(self):
        rows = m.load_mapping()
        self.assertEqual(len(rows), 531)
        self.assertEqual(m.resolve_ordinal("MFC71.DLL", 1084), "?AfxGetModuleState@@YGPAVAFX_MODULE_STATE@@XZ")
        self.assertEqual(m.resolve_ordinal("mfc71.dll", 6305), "?WriteProfileInt@CWinApp@@QAEHPBD0H@Z")
        self.assertEqual(sum(r["kind"] == "data" for r in rows.values()), 1)

    def test_unproved_ordinal_and_wrong_dll_are_refused(self):
        with self.assertRaisesRegex(ValueError, "unverified"):
            m.resolve_ordinal("mfc71.dll", 5230)
        with self.assertRaisesRegex(ValueError, "No verified"):
            m.resolve_ordinal("mfc71u.dll", 1084)

    def test_edited_mapping_cannot_change_a_callee_identity(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "mfc71.csv"
            path.write_bytes(m.MAPPING.read_bytes().replace(b"AfxGetModuleState", b"AfxGetWrongState"))
            with patch.object(m, "MAPPING", path), self.assertRaisesRegex(ValueError, "SHA-256 mismatch"):
                m.resolve_ordinal("mfc71.dll", 1084)

    def test_pdb_format_is_explicit(self):
        with self.assertRaisesRegex(ValueError, "MSF 7"):
            m.pdb_streams(b"not a PDB")


if __name__ == "__main__":
    unittest.main()
