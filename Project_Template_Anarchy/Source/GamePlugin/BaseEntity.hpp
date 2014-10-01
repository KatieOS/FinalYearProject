
#ifndef _SerializeBaseEntity_cl_H_
#define _SerializeBaseEntity_cl_H_

#define MSG_SER_CLEANUP VIS_MSG_USER + 1

extern VModule g_sampleModule;

//#define SERIALIZEDEMO_DLLEXP _declspec( dllexport )
#include "GamePluginModule.h"

enum SerializeType_e
{
  SERIALIZE_FULL,       // full object serialization
  SERIALIZE_RECREATE    // just store entity params and re-create entity on load
};

//
// *** SerializeBaseEntity_cl  ***
//
// Synopsis:
//    - 
//
// Description:
//    - 
//
class SerializeBaseEntity_cl : public VisBaseEntity_cl
{
  typedef VisBaseEntity_cl Inherited;
  V_DECLARE_SERIAL( SerializeBaseEntity_cl, SAMPLEPLUGIN_IMPEXP)
private:
  // private variables
public:
  // serialization support functions
  virtual SerializeType_e GetSerializeType() { return SERIALIZE_FULL; }
  SAMPLEPLUGIN_IMPEXP virtual void Serialize( VArchive& ar );
  
IMPLEMENT_OBJ_CLASS(SerializeBaseEntity_cl);
};

#endif

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