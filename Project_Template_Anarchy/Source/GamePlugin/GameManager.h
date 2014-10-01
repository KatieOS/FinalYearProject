/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


//  This class show how to use the vForge "play the Game" mode

#ifndef PLUGINMANAGER_H_INCLUDED
#define PLUGINMANAGER_H_INCLUDED

#include <Vision/Samples/Engine/SimpleFont/SimpleFontPCH.h>
#include "GamePluginModule.h"
#include"Player.h"
//#include "save.h"
#include "door.h"
#include "PickUp.h"
#include "PlayerDialog.h"
#include "Inventory.h"


class RPG_Character;

class MyGameManager : public IVisCallbackHandler_cl
{
public:
  virtual void OnHandleCallback(IVisCallbackDataObject_cl *pData) HKV_OVERRIDE;
  MyGameManager();
  // called when plugin is loaded/unloaded
  void OneTimeInit();
  void OneTimeDeInit();
  void getCurl();
  void postCurl();
  void AddCharacter(Player* character);
  void RemoveCharacter(Player* character);
  VArray<Player*> const& GetCharacters() const;

  VisBaseEntity_cl* SpawnPlayer(const VString& prefabName, hkvVec3 const& position, hkvVec3 const& orientation);

  VisBaseEntity_cl* CreateEntity(const char* className, const hkvVec3& position);
 // VisBaseEntity_cl* CreateEntityFromScript(const VString& scriptName, const hkvVec3& position, const hkvVec3& orientation);
  VisBaseEntity_cl* CreateEntityFromPrefab(const VString& prefabName, const hkvVec3& position, const hkvVec3& orientation);

  // switch to play-the-game mode. When not in vForge, this is default
  void SetPlayTheGame(bool bStatus);

  // access one global instance of the Game manager
  static MyGameManager& GlobalManager() {return g_GameManager;}

private:
  bool m_bPlayingTheGame;
  bool mStaticsSynced;
  VArray<Player*> m_characters;
  VWeakPtr<VisBaseEntity_cl> m_playerEntity;
  hkvVec3 m_playerRespawnPosition;
  static VString const PLAYER_PREFAB_NAME;
  static MyGameManager g_GameManager;
  //PlayerDialog* mDialog;
  VSmartPtr<PlayerDialog> mDialog;
  //VSmartPtr<PickUp> mPickUp;
  VWeakPtr<VisBaseEntity_cl> mPickUpEntity;
    VisBaseEntity_cl *pMyEntity;
	
  
	//save test
	//Save savetest;
  
  VSmartPtr<PlayerComponent> mplayerController;
  // VSmartPtr<ComponentManager> mComponentManager;
  VSmartPtr<VGUIMainContext> spGUIContext;//gui Context

};


#endif // PLUGINMANAGER_H_INCLUDED

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
