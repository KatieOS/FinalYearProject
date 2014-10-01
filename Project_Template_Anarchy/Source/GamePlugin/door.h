#ifndef SAMPLEPLUGIN_DOOR_H__
#define SAMPLEPLUGIN_DOOR_H__

#include "GamePluginModule.h"
#include "Player.h"
#include "Inventory.h"
#include"PickUp.h"
#include<iostream>
//class Player;
//typedef VSmartPtr<Player> PlayerPtr;

class Door : public PickUp
{

	 float mDoorRadius;
	 VString mPuzzleID;

public:
   Door();
   void Initialize() HKV_OVERRIDE;
   void ThinkFunction() HKV_OVERRIDE;
   void CheckCanPass();
   V_DECLARE_SERIAL_DLLEXP(Door, SAMPLEPLUGIN_IMPEXP ) // RTTI (mandatory)
   V_DECLARE_VARTABLE( Door, SAMPLEPLUGIN_IMPEXP )      // Optional variable table
   SAMPLEPLUGIN_IMPEXP virtual void Serialize(VArchive &ar);// HKV_OVERRIDE;

protected:

	VSmartPtr<vHavokRigidBody> mRigidBodyComponent;
   BOOL m_usePhysics;  


};
#endif
