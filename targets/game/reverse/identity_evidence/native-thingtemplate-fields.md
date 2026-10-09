# ThingTemplate fields at compiler-measured BFME offsets

Constructor RVA 0x00147600 (1718 bytes) is called by matched ThingFactory::newOverride for its 0x4D4-byte allocation and shares vtable 0x01094988 with the matched destructor. Assignment RVA 0x00139070 (2057 bytes) preserves that same object layout; both views and their dependent funclets are byte-gated.

The existing matched source views identify ThingTemplate; their types, bases, packing,
sizes, signatures and bodies remain unchanged. Scratch copies compiled with the
same MSVC 7.1 options add nonvirtual static address/sizeof probes, called from
extern-C wrappers. Only relocation-free constant return bodies are accepted; no
probe is shipped. This measures the layout the handwritten offset model refuses.

Names are independently joined from retail FieldParse records to the INI keys'
`offsetof(ThingTemplate, member)` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp`. The raw terminated retail tables
and exact upstream key/owner/member triples were rechecked for each field; ZH
offsets are not used. `field_names.csv` records the witnesses.

Only metric-placeholders with a unique declaration spelling are rewritten.
Spans crossing another witnessed offset and already-declared target names are
refused. The declaration denominator is unchanged.

| Source view | Original field | BFME offset | Proven field | INI key |
|---|---|---:|---|---|
| `ThingTemplateConstructor` | `m_scalar0398` | `0x398` | `m_fenceWidth` | `FenceWidth` |
| `ThingTemplateConstructor` | `m_scalar039c` | `0x39c` | `m_fenceXOffset` | `FenceXOffset` |
| `ThingTemplateConstructor` | `m_scalar03a4` | `0x3a4` | `m_visionRange` | `VisionRange` |
| `ThingTemplateConstructor` | `m_scalar03a8` | `0x3a8` | `m_shroudClearingRange` | `ShroudClearingRange` |
| `ThingTemplateConstructor` | `m_scalar03b0` | `0x3b0` | `m_placementViewAngle` | `PlacementViewAngle` |
| `ThingTemplateConstructor` | `m_scalar03b4` | `0x3b4` | `m_factoryExitWidth` | `FactoryExitWidth` |
| `ThingTemplateConstructor` | `m_scalar03b8` | `0x3b8` | `m_factoryExtraBibWidth` | `FactoryExtraBibWidth` |
| `ThingTemplateConstructor` | `m_scalar03bc` | `0x3bc` | `m_buildTime` | `BuildTime` |
| `ThingTemplateConstructor` | `m_scalar03c0` | `0x3c0` | `m_assetScale` | `Scale` |
| `ThingTemplateConstructor` | `m_scalar03c4` | `0x3c4` | `m_instanceScaleFuzziness` | `InstanceScaleFuzziness` |
| `ThingTemplateConstructor` | `m_scalar03c8` | `0x3c8` | `m_shadowSizeX` | `ShadowSizeX` |
| `ThingTemplateConstructor` | `m_scalar03cc` | `0x3cc` | `m_shadowSizeY` | `ShadowSizeY` |
| `ThingTemplateConstructor` | `m_scalar03d0` | `0x3d0` | `m_shadowOffsetX` | `ShadowOffsetX` |
| `ThingTemplateConstructor` | `m_scalar03d4` | `0x3d4` | `m_shadowOffsetY` | `ShadowOffsetY` |
| `ThingTemplateConstructor` | `m_scalar0418` | `0x418` | `m_energyProduction` | `EnergyProduction` |
| `ThingTemplateConstructor` | `m_scalar041c` | `0x41c` | `m_energyBonus` | `EnergyBonus` |
| `ThingTemplateConstructor` | `m_scalar0420` | `0x420` | `m_displayColor` | `DisplayColor` |
| `ThingTemplateConstructor` | `m_scalar0424` | `0x424` | `m_occlusionDelay` | `OcclusionDelay` |
| `ThingTemplateConstructor` | `m_short047a` | `0x47a` | `m_buildCost` | `BuildCost` |
| `ThingTemplateConstructor` | `m_short047c` | `0x47c` | `m_refundValue` | `RefundValue` |
| `ThingTemplateConstructor` | `m_short047e` | `0x47e` | `m_threatValue` | `ThreatValue` |
| `ThingTemplateConstructor` | `m_short0480` | `0x480` | `m_maxSimultaneousOfType` | `MaxSimultaneousOfType` |
| `ThingTemplateConstructor` | `m_short0482` | `0x482` | `m_shadowType` | `Shadow` |
| `ThingTemplateConstructor` | `m_byte0484` | `0x484` | `m_isPrerequisite` | `IsPrerequisite` |
| `ThingTemplateConstructor` | `m_byte0485` | `0x485` | `m_isBridge` | `IsBridge` |
| `ThingTemplateConstructor` | `m_byte0487` | `0x487` | `m_isTrainable` | `IsTrainable` |
| `ThingTemplateConstructor` | `m_byte0488` | `0x488` | `m_isForbidden` | `IsForbidden` |
| `ThingTemplateConstructor` | `m_byte0490` | `0x490` | `m_radarPriority` | `RadarPriority` |
| `ThingTemplateConstructor` | `m_byte0491` | `0x491` | `m_transportSlotCount` | `TransportSlotCount` |
| `ThingTemplateConstructor` | `m_byte0493` | `0x493` | `m_buildCompletion` | `BuildCompletion` |
| `ThingTemplateConstructor` | `m_byte0494` | `0x494` | `m_editorSorting` | `EditorSorting` |
| `ThingTemplateConstructor` | `m_byte0497` | `0x497` | `m_structureRubbleHeight` | `StructureRubbleHeight` |
| `ThingTemplateConstructor` | `m_byte0499` | `0x499` | `m_crusherLevel` | `CrusherLevel` |
| `ThingTemplateConstructor` | `m_byte049a` | `0x49a` | `m_crushableLevel` | `CrushableLevel` |
| `ThingTemplateCopyAssignment` | `m_unknownMid2d0` | `0x2d0` | `m_buildVariations` | `BuildVariations` |
| `ThingTemplateCopyAssignment` | `m_scalar0398` | `0x398` | `m_fenceWidth` | `FenceWidth` |
| `ThingTemplateCopyAssignment` | `m_scalar039c` | `0x39c` | `m_fenceXOffset` | `FenceXOffset` |
| `ThingTemplateCopyAssignment` | `m_scalar03a4` | `0x3a4` | `m_visionRange` | `VisionRange` |
| `ThingTemplateCopyAssignment` | `m_scalar03a8` | `0x3a8` | `m_shroudClearingRange` | `ShroudClearingRange` |
| `ThingTemplateCopyAssignment` | `m_scalar03b0` | `0x3b0` | `m_placementViewAngle` | `PlacementViewAngle` |
| `ThingTemplateCopyAssignment` | `m_scalar03b4` | `0x3b4` | `m_factoryExitWidth` | `FactoryExitWidth` |
| `ThingTemplateCopyAssignment` | `m_scalar03b8` | `0x3b8` | `m_factoryExtraBibWidth` | `FactoryExtraBibWidth` |
| `ThingTemplateCopyAssignment` | `m_scalar03bc` | `0x3bc` | `m_buildTime` | `BuildTime` |
| `ThingTemplateCopyAssignment` | `m_scalar03c0` | `0x3c0` | `m_assetScale` | `Scale` |
| `ThingTemplateCopyAssignment` | `m_scalar03c4` | `0x3c4` | `m_instanceScaleFuzziness` | `InstanceScaleFuzziness` |
| `ThingTemplateCopyAssignment` | `m_scalar03c8` | `0x3c8` | `m_shadowSizeX` | `ShadowSizeX` |
| `ThingTemplateCopyAssignment` | `m_scalar03cc` | `0x3cc` | `m_shadowSizeY` | `ShadowSizeY` |
| `ThingTemplateCopyAssignment` | `m_scalar03d0` | `0x3d0` | `m_shadowOffsetX` | `ShadowOffsetX` |
| `ThingTemplateCopyAssignment` | `m_scalar03d4` | `0x3d4` | `m_shadowOffsetY` | `ShadowOffsetY` |
| `ThingTemplateCopyAssignment` | `m_scalar0418` | `0x418` | `m_energyProduction` | `EnergyProduction` |
| `ThingTemplateCopyAssignment` | `m_scalar041c` | `0x41c` | `m_energyBonus` | `EnergyBonus` |
| `ThingTemplateCopyAssignment` | `m_scalar0420` | `0x420` | `m_displayColor` | `DisplayColor` |
| `ThingTemplateCopyAssignment` | `m_scalar0424` | `0x424` | `m_occlusionDelay` | `OcclusionDelay` |
| `ThingTemplateCopyAssignment` | `m_short047a` | `0x47a` | `m_buildCost` | `BuildCost` |
| `ThingTemplateCopyAssignment` | `m_short047c` | `0x47c` | `m_refundValue` | `RefundValue` |
| `ThingTemplateCopyAssignment` | `m_short047e` | `0x47e` | `m_threatValue` | `ThreatValue` |
| `ThingTemplateCopyAssignment` | `m_short0480` | `0x480` | `m_maxSimultaneousOfType` | `MaxSimultaneousOfType` |
| `ThingTemplateCopyAssignment` | `m_short0482` | `0x482` | `m_shadowType` | `Shadow` |
| `ThingTemplateCopyAssignment` | `m_byte0484` | `0x484` | `m_isPrerequisite` | `IsPrerequisite` |
| `ThingTemplateCopyAssignment` | `m_byte0485` | `0x485` | `m_isBridge` | `IsBridge` |
| `ThingTemplateCopyAssignment` | `m_byte0487` | `0x487` | `m_isTrainable` | `IsTrainable` |
| `ThingTemplateCopyAssignment` | `m_byte0488` | `0x488` | `m_isForbidden` | `IsForbidden` |
| `ThingTemplateCopyAssignment` | `m_byte0490` | `0x490` | `m_radarPriority` | `RadarPriority` |
| `ThingTemplateCopyAssignment` | `m_byte0491` | `0x491` | `m_transportSlotCount` | `TransportSlotCount` |
| `ThingTemplateCopyAssignment` | `m_byte0493` | `0x493` | `m_buildCompletion` | `BuildCompletion` |
| `ThingTemplateCopyAssignment` | `m_byte0494` | `0x494` | `m_editorSorting` | `EditorSorting` |
| `ThingTemplateCopyAssignment` | `m_byte0497` | `0x497` | `m_structureRubbleHeight` | `StructureRubbleHeight` |
| `ThingTemplateCopyAssignment` | `m_byte0499` | `0x499` | `m_crusherLevel` | `CrusherLevel` |
| `ThingTemplateCopyAssignment` | `m_byte049a` | `0x49a` | `m_crushableLevel` | `CrushableLevel` |
