
#include "GamePluginPCH.h"
#include "BaseEntity.hpp"


V_IMPLEMENT_SERIAL( SerializeBaseEntity_cl, VisBaseEntity_cl, 0,&g_myComponentModule);


// ---------------------------------------------------------------------------------
// Method: Serialize
// Author: Trinigy
// Notes: 
// ---------------------------------------------------------------------------------
void SerializeBaseEntity_cl::Serialize( VArchive& ar )
{
  // call base class Serialize
  Inherited::Serialize( ar );
}


START_VAR_TABLE(SerializeBaseEntity_cl, VisBaseEntity_cl, "SerializeBaseEntity_cl", 0, "")
END_VAR_TABLE

/*
 * Havok SDK - Base file, BUILD(#20131218)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2013
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available from salesteam@havok.com.
 * 
 */