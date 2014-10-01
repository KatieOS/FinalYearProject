#ifndef SAMPLEPLUGIN_PICKUP_H__
#define SAMPLEPLUGIN_PICKUP_H__

#include "GamePluginModule.h"
#include "Player.h"
#include "Inventory.h"
#include<iostream>

using namespace std;
class Player;
typedef VSmartPtr<Player> PlayerPtr;

extern VModule g_sampleModule;


class PickUp : public SerializeBaseEntity_cl
{
	float mPickUpRadius;
	VString mPickUpID;

public:
	typedef SerializeBaseEntity_cl Inherited;
   PickUp();
   void Initialize() HKV_OVERRIDE;
//void PostInitialize();
   void ThinkFunction() HKV_OVERRIDE;
   void CheckPlayerContact();
   void CheckifPickUpSelect();
   void OnPickUp();
   void PickUpActive();
   V_DECLARE_SERIAL_DLLEXP(PickUp, SAMPLEPLUGIN_IMPEXP ) // RTTI (mandatory)
   V_DECLARE_VARTABLE( PickUp, SAMPLEPLUGIN_IMPEXP )      // Optional variable table
   SAMPLEPLUGIN_IMPEXP virtual void Serialize(VArchive &ar);// HKV_OVERRIDE;


protected:
   
  
 

    BOOL m_usePhysics;      ///< if enabled, a rigid body will be created for this pickup.

  VSmartPtr<vHavokRigidBody> mRigidBodyComponent;
  float mElapsedTime;
  PlayerPtr mPlayer;
  float mMass;
  float mMagnetMaxDistance;
  float mMagnetSpeedMultiplier;
  float mSpawnIdleTime;
  float m_verticalSpawnForceMin;
  float m_verticalSpawnForceMax;
  float m_horizontalSpawnForceMin;
  float m_horizontalSpawnForceMax;

  float m_magnetMaxDistanceInverseSquared;
  float m_currentMagnetSpeed;
  hkvVec3 m_currentMagnetVelocity;
  bool hit;

    // Sounds
  VFmodSoundObject* mPickUpSound;

private:
 // IMPLEMENT_OBJ_CLASS(PickUp);
 
  //IMPLEMENT_OBJ_CLASS(PickUp);
};
#endif;