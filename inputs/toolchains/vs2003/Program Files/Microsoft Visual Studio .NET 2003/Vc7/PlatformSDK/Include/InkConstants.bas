'+-------------------------------------------------------------------------
'
'   Microsoft Windows
'   Copyright (C) Microsoft Corporation, 2002.
'
'   File: InkConstants.bas
'       Microsoft WISP API constants for VB6
' 
'--------------------------------------------------------------------------

Attribute VB_Name = "InkConstants"

'+-------------------------------------------------------------------------
'
'   Ink Factoids
'
'   The following constants are ink factoids.  A factoid provides context 
'   for recognized ink in the context of a particular field; use it to 
'   specify that an input field is of a known type, such as a date.
' 
'--------------------------------------------------------------------------
Public Const FactoidBopomofo = "BOPOMOFO"
Public Const FactoidChineseSimpleCommon = "CHS_COMMON"
Public Const FactoidChineseTraditionalCommon = "CHT_COMMON"
Public Const FactoidCurrency = "CURRENCY"
Public Const FactoidDate = "DATE"
Public Const FactoidDefault = "DEFAULT"
Public Const FactoidDigit = "DIGIT"
Public Const FactoidEmail = "EMAIL"
Public Const FactoidFilename = "FILENAME"
Public Const FactoidHangulCommon = "HANGUL_COMMON"
Public Const FactoidHangulRare = "HANGUL_RARE"
Public Const FactoidHiragana = "HIRAGANA"
Public Const FactoidJamo = "JAMO"
Public Const FactoidJapaneseCommon = "JPN_COMMON"
Public Const FactoidKanjiCommon = "KANJI_COMMON"
Public Const FactoidKanjiRare = "KANJI_RARE"
Public Const FactoidKatakana = "KATAKANA"
Public Const FactoidKoreanCommon = "KOR_COMMON"
Public Const FactoidLowerChar = "LOWERCHAR"
Public Const FactoidNone = "NONE"
Public Const FactoidNumber = "NUMBER"
Public Const FactoidNumberSimple = "NUMSIMPLE"
Public Const FactoidOneChar = "ONECHAR"
Public Const FactoidPercent = "PERCENT"
Public Const FactoidPostalCode = "POSTALCODE"
Public Const FactoidPuncChar = "PUNCCHAR"
Public Const FactoidSystemDictionary = "SYSDICT"
Public Const FactoidTelephone = "TELEPHONE"
Public Const FactoidTime = "TIME"
Public Const FactoidUpperChar = "UPPERCHAR"
Public Const FactoidWeb = "WEB"
Public Const FactoidWordList = "WORDLIST"


'+-------------------------------------------------------------------------
'
'   Packet Property GUIDs
'
'   The following constants are packet property GUIDs.  Use these GUIDs to  
'   specify which properties the ink packets should contain.
' 
'--------------------------------------------------------------------------
Public Const AltitudeOrientation = "{82DEC5C7-F6BA-4906-894F-66D68DFC456C}"
Public Const AzimuthOrientation = "{029123B4-8828-410B-B250-A0536595E5DC}"
Public Const ButtonPressure = "{8B7FEFC4-96AA-4BFE-AC26-8A5F0BE07BF5}"
Public Const NormalPressure = "{7307502D-F9F4-4E18-B3F2-2CE1B1A3610C}"
Public Const PacketStatus = "{6E0E07BF-AFE7-4CF7-87D1-AF6446208418}"
Public Const PitchRotation = "{7F7E57B7-BE37-4BE1-A356-7A84160E1893}"
Public Const RollRotation = "{5D5D5E56-6BA9-4C5B-9FB0-851C91714E56}"
Public Const SerialNumber = "{78A81B56-0935-4493-BAAE-00541A8A16C4}"
Public Const TangentPressure = "{6DA4488B-5244-41EC-905B-32D89AB80809}"
Public Const TimerTick = "{436510C5-FED3-45D1-8B76-71D3EA7A829D}"
Public Const TwistOrientation = "{0D324960-13B2-41E4-ACE6-7AE9D43D2D3B}"
Public Const X = "{598A6A8F-52C0-4BA0-93AF-AF357411A561}"
Public Const XTiltOrientation = "{A8D07B3A-8BF0-40B0-95A9-B80A6BB787BF}"
Public Const Y = "{B53F9F75-04E0-4498-A7EE-C30DBB5A9011}"
Public Const YawRotation = "{6A849980-7C3A-45B7-AA82-90A262950E89}"
Public Const YTiltOrientation = "{0E932389-1D77-43AF-AC00-5B950D6D4B2D}"
Public Const Z = "{735ADB30-0EBB-4788-A0E4-0F316490055D}"

'+-------------------------------------------------------------------------
'
'   Recognition Property GUIDs
'
'   The following constants are recognition property GUIDs.
' 
'--------------------------------------------------------------------------
Public Const ConfidenceLevel = "{7DFE11A7-FB5D-4958-8765-154ADF0D833F}"
Public Const HotPoint = "{CA6F40DC-5292-452a-91FB-2181C0BEC0DE}"
Public Const LineMetrics = "{8CC24B27-30A9-4b96-9056-2D3A90DA0727}"
Public Const LineNumber = "{DBF29F2C-5289-4BE8-B3D8-6EF63246253E}"
Public Const MaximumStrokeCount = "{BF0EEC4E-4B7D-47a9-8CFA-234DD24BD22A}"
Public Const PointsPerInch = "{7ED16B76-889C-468e-8276-0021B770187E}"
Public Const Segmentation = "{B3C0FE6C-FB51-4164-BA2F-844AF8F983DA}"
