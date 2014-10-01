/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include "GamePluginPCH.h"
#include "GameManager.h"
#include "Player.h"
#include "PickUp.h"
#include "door.h"
#include "ComponentManager.h"
#include "PlayerControlComponent.h"
#include <Vision/Runtime/Framework/VisionApp/VAppImpl.hpp>
#include <Vision/Runtime/Framework/VisionApp/Modules/VHelp.hpp>
/*#include <3rdParty\curl-7.29.0\include\curl\curl.h>
#include <3rdParty\curl-7.29.0\include\curl\curlbuild.h>
#include <3rdParty\curl-7.29.0\include\curl\easy.h>
#include <3rdParty\curl-7.29.0\include\curl\stdcheaders.h>
#include <3rdParty\curl-7.29.0\include\curl\curlrules.h>
#include <3rdParty\curl-7.29.0\include\curl\curlver.h>
#include <3rdParty\curl-7.29.0\include\curl\mprintf.h>
#include <3rdParty\curl-7.29.0\include\curl\multi.h>*/
using namespace std;

#include <Vision/Runtime/EnginePlugins/EnginePluginsImport.hpp>
#include <Vision/Runtime/EnginePlugins/VisionEnginePlugin/Scene/VPrefab.hpp>
//#include <Vision/Samples/Engine/HavokAi/HavokAiPCH.h>
//#include <Vision/Samples/Engine/HavokAi/PathPickDlg.hpp>

#include <Vision/Runtime/Framework/VisionApp/VAppImpl.hpp>
#include <Vision/Runtime/Framework/VisionApp/Modules/VHelp.hpp>

#include <Vision/Runtime/EnginePlugins/EnginePluginsImport.hpp>

#include <Vision/Runtime/EnginePlugins/Havok/HavokAiEnginePlugin/vHavokAiModule.hpp>
#include <Ai/Pathfinding/World/hkaiWorld.h>
#include <Vision/Runtime/EnginePlugins/Havok/HavokAiEnginePlugin/vHavokAiNavMeshResource.hpp>
#include <Vision/Runtime/EnginePlugins/Havok/HavokAiEnginePlugin/vHavokAiNavMeshResourceManager.hpp>
#include <Vision/Runtime/EnginePlugins/Havok/HavokAiEnginePlugin/vHavokAiNavMeshInstance.hpp>

#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokPhysicsModule.hpp>
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokSync.hpp>
#include "VisionHavokBehaviorWorldListener.h"

//animation
//Animation includes
#include <Vision/Runtime/Engine/Animation/VisApiAnimLayerMixerNode.hpp>
#include <Vision/Runtime/Engine/Animation/VisApiAnimNormalizeMixerNode.hpp>
#include <Vision/Runtime/Engine/Animation/VisApiAnimBoneModifierNode.hpp>

  
 static size_t rcvData(void *ptr, size_t size, size_t nmemb, void *userdata)
  {
	  VActionManager * pManager = Vision::GetActionManager ();
	  pManager->RegisterModule ( &g_myComponentModule );

  // Set to true to open the console at startup and print some data to the display
  Vision::GetConsoleManager()->Show(true);
  pManager->Print( "Welcome to the console!" );
   pManager->Print((char*)ptr); // up to 989 characters each time
 return size * nmemb;
 }
VString const MyGameManager::PLAYER_PREFAB_NAME = "Prefabs\\Demo_Player_Hero.vprefab";
// one global static instance
MyGameManager MyGameManager::g_GameManager;


MyGameManager::MyGameManager()
	:m_characters(),
	 mStaticsSynced(false)
{
}
void MyGameManager::OneTimeInit()
{

  //In case the Havok Physics plugin is already loaded, synchronize the statics now.
  vHavokPhysicsModule* pPhysicsModule = vHavokPhysicsModule::GetInstance();
  if (pPhysicsModule != NULL)
  {
    VISION_HAVOK_SYNC_STATICS();
    VISION_HAVOK_SYNC_PER_THREAD_STATICS(pPhysicsModule);
  }
  
  m_bPlayingTheGame = false;

  // the game manager should listen to the following callbacks:
  Vision::Callbacks.OnEditorModeChanged += this;
  Vision::Callbacks.OnBeforeSceneLoaded += this;
  Vision::Callbacks.OnAfterSceneLoaded += this;
  Vision::Callbacks.OnUpdateSceneBegin += this;
  Vision::Callbacks.OnWorldDeInit += this;

   // Set-up the physics callbacks
  vHavokPhysicsModule::OnBeforeInitializePhysics += this;
  vHavokPhysicsModule::OnUnsyncHavokStatics += this;
  vHavokPhysicsModule::OnBeforeWorldCreated += this;
  vHavokPhysicsModule::OnAfterDeInitializePhysics += this;
  vHavokVisualDebugger::OnCreatingContexts += this;


}

void MyGameManager::OneTimeDeInit()
{
  Vision::Callbacks.OnEditorModeChanged -= this;
  Vision::Callbacks.OnBeforeSceneLoaded -= this;
  Vision::Callbacks.OnAfterSceneLoaded -= this;  
  vHavokVisualDebugger::OnCreatingContexts -= this;
  Vision::Callbacks.OnUpdateSceneBegin -= this;
  Vision::Callbacks.OnWorldDeInit -= this;

   // Cancel the physics callbacks


  vHavokPhysicsModule::OnAfterDeInitializePhysics -= this;
  vHavokPhysicsModule::OnBeforeWorldCreated -= this;
  vHavokPhysicsModule::OnBeforeInitializePhysics -= this;
  vHavokPhysicsModule::OnUnsyncHavokStatics -= this;
  vHavokVisualDebugger::OnCreatingContexts -= this;
}
void MyGameManager::AddCharacter(Player* character)
{
  if(character &&
     m_characters.Find(character) < 0)
  {
    m_characters.Add(character);
  }
}
void MyGameManager::RemoveCharacter(Player* character)
{
  int foundIndex = m_characters.Find(character);

  if(foundIndex >= 0)
  {
    m_characters.RemoveAt(foundIndex);
  }
}

VArray<Player*> const& MyGameManager::GetCharacters() const
{
  return m_characters;
}


VisBaseEntity_cl* MyGameManager::SpawnPlayer(const VString& prefabName, hkvVec3 const& position, hkvVec3 const& orientation)
{
	
  VisBaseEntity_cl* playerEntity = CreateEntityFromPrefab(prefabName, position, orientation);
	  //Vision::Game.CreateEntity(Player,position);//
  playerEntity->InitFunction();

  if(playerEntity)
  {
    PlayerComponent *const playerController = static_cast<PlayerComponent*>
      (playerEntity->Components().GetComponentOfBaseType(V_RUNTIME_CLASS(PlayerComponent)));

    //VASSERT(playerController);
   if(playerController)
    {
      spGUIContext = new VGUIMainContext(NULL);
	  // Create a GUI context
    mDialog = new PlayerDialog(playerController);
    mDialog->InitDialog(spGUIContext, NULL, NULL);
    spGUIContext->ShowDialog(mDialog);
    spGUIContext->SetActivate(true);
    }
  
    m_playerEntity = playerEntity->GetWeakReference();
	//AddCharacter(m_playerEntity);

	//Vision::Message.Add(1, "Spawn");
  }

  return playerEntity;
}

/// Creates an entity from a prefab file.
VisBaseEntity_cl* MyGameManager::CreateEntityFromPrefab(const VString& prefabName, const hkvVec3& position, const hkvVec3& orientation)
{
  if(!prefabName.IsEmpty())
  {
    VPrefab* prefab = VPrefabManager::GlobalManager().LoadPrefab(prefabName);

    VPrefabInstanceInfo info;
    {
      info.m_bOutputInstances = true;
      info.m_vInstancePos = position;
      info.m_vInstanceEuler = orientation;
    }

    prefab->Instantiate(info);

    VisBaseEntity_cl* entity = vstatic_cast<VisBaseEntity_cl*>(info.m_Instances[0]);

    return entity;
  }

  return NULL;
}


VisBaseEntity_cl* MyGameManager::CreateEntity(const char* className, const hkvVec3& position)
{
  VisBaseEntity_cl* entity = Vision::Game.CreateEntity(className, position);
    Vision::Message.Print(1, 200, 100, "create entity");
  VASSERT(entity);
  
  return entity;
}

void MyGameManager::OnHandleCallback(IVisCallbackDataObject_cl *pData)
{
	//physics callbacks
	if (pData->m_pSender == &vHavokPhysicsModule::OnBeforeInitializePhysics)
  {
    vHavokPhysicsModuleCallbackData* pHavokData = static_cast<vHavokPhysicsModuleCallbackData*>(pData);
    VISION_HAVOK_SYNC_STATICS();
    VISION_HAVOK_SYNC_PER_THREAD_STATICS(pHavokData->GetHavokModule());
    // hkaiCharacter created by this dll will have a different vtable than the one expected by the AI module (for vdb viewer)
    // The vtable-class(?) mapping is apparently many-to-one, so re-register here with our vtable
    // (Actually the vtables in this module and the vtables elsewhere are unique, so being many-to-one is a happy accident)
    // TODO redundant in the statically linked case
    hkVtableClassRegistry::getInstance().registerList(hkBuiltinTypeRegistry::StaticLinkedTypeInfos, hkBuiltinTypeRegistry::StaticLinkedClasses);
	mStaticsSynced = true;
  }
 else if(pData->m_pSender == &vHavokPhysicsModule::OnBeforeWorldCreated)
  {
    vHavokPhysicsModule *const havok_module = static_cast<vHavokBeforeWorldCreateDataObject_cl *>(pData)->GetHavokModule();
    {
      havok_module->SetUseAsynchronousPhysics(false);

      havok_module->SetEnabledVisualDebugger(true);
    }

	// Disable validation checks (that are also performed in dev build)
    vHavokAiModule::GetInstance()->GetAiWorld()->getNavMeshCutter()->m_performValidationChecks = false;
  }
  else if (pData->m_pSender == &vHavokPhysicsModule::OnAfterDeInitializePhysics)
  {

	vHavokAiModule::GetInstance()->getCharacterBehaviors().clearAndDeallocate();
    vHavokPhysicsModuleCallbackData* pHavokData = static_cast<vHavokPhysicsModuleCallbackData*>(pData);
    VISION_HAVOK_UNSYNC_STATICS();
    VISION_HAVOK_UNSYNC_PER_THREAD_STATICS(pHavokData->GetHavokModule());
	 mStaticsSynced = false;

  }

	//vision callbacks
 if (pData->m_pSender==&Vision::Callbacks.OnUpdateSceneBegin)
  {
      //This callback will be triggered at the beginning of every frame
	  Inventory::InventoryManager().ThinkFunction();
	  //check key press
	  if (Vision::Key.IsPressed(VGLK_P))
	  {
		Vision::GetTimer()->SetFrozen(true);
		  
	  }
	  else if (Vision::Key.IsPressed(VGLK_R))
	  {
		 Vision::GetTimer()->SetFrozen(false);
	  }
    
	  	 
      if (m_bPlayingTheGame)
      {
      }
      return;
  }

  if(pData->m_pSender==&Vision::Callbacks.OnWorldInit)
  {
	  vHavokPhysicsModule* pPhysicsModule = vHavokPhysicsModule::GetInstance();
    if (pPhysicsModule != NULL && !mStaticsSynced)
    {
      // Havok Physics Plugin has already been initialized.
      // Reinitialize the physics integration to be able to synchronize static variables properly.
      pPhysicsModule->OnDeInitPhysics();
      pPhysicsModule->OnInitPhysics();
	  	    // Add our own Havok Behavior world listener in order to listen to Behavior events
       vHavokBehaviorModule *const havok_behavior_module = vHavokBehaviorModule::GetInstance();
       havok_behavior_module->getBehaviorWorld()->addListener(&MyHavokBehaviorWorldListener::s_instance);
    }
  }
  if (pData->m_pSender==&Vision::Callbacks.OnEditorModeChanged)
  {
    // when vForge switches back from EDITORMODE_PLAYING_IN_GAME, turn off our play the game mode
    if (((VisEditorModeChangedDataObject_cl *)pData)->m_eNewMode != VisEditorManager_cl::EDITORMODE_PLAYING_IN_GAME)
      SetPlayTheGame(false);
    return;
  }

  if (pData->m_pSender==&Vision::Callbacks.OnBeforeSceneLoaded)
  {
	  
	   // Add our own Havok Behavior world listener in order to listen to Behavior events
      // vHavokBehaviorModule *const havok_behavior_module = vHavokBehaviorModule::GetInstance();
      // havok_behavior_module->getBehaviorWorld()->addListener(&MyHavokBehaviorWorldListener::s_instance);
    return;
  }

  if (pData->m_pSender==&Vision::Callbacks.OnAfterSceneLoaded)
  {


	  //spawn player charecter from prefab
	SpawnPlayer(PLAYER_PREFAB_NAME,hkvVec3(10,50,30) , hkvVec3::ZeroVector());

	//Inventory *inven = new Inventory();
	//inven->InitInventory();
	//ONLY LOAD AFTER SCENE ELSE TEXTURE ERROR
	  Inventory::InventoryManager().OneTimeInit();

	  //create save file

	  
	  hkvVec3 vStart;
	  vStart = hkvVec3(100,100,100);
	 // Vision::Game.CreateEntity("SerializePlayer_cl", vStart);

	//postCurl();


    if (Vision::Editor.IsPlayingTheGame()) 
      SetPlayTheGame(true);
    return;
  //}
  }
  

  if (pData->m_pSender==&Vision::Callbacks.OnWorldDeInit) 
  {
     // this is important when running outside vForge
    SetPlayTheGame(false);
    return;
  }
 if (pData->m_pSender==&Vision::Callbacks.OnBeforeSceneUnloaded)
  {
	  Inventory::InventoryManager().OneTimeDeInit();
	  Inventory::InventoryManager().DeleteThis();
	  return;
  }
   if (pData->m_pSender==&Vision::Callbacks.OnAfterSceneUnloaded)
  {
	   // Only try to remove the listener if a scene was actually loaded
    vHavokBehaviorModule *const havok_behavior_module = vHavokBehaviorModule::GetInstance();
    havok_behavior_module->getBehaviorWorld()->removeListener(&MyHavokBehaviorWorldListener::s_instance);
	  return;
  }
}

void MyGameManager::getCurl()
{
	/* CURL *curl;
   curl = curl_easy_init();
   curl_easy_setopt(curl, CURLOPT_URL, "http://54.186.99.234:8000/version");//put ec2 url here
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, rcvData);

  curl_easy_perform(curl);
   curl_easy_cleanup(curl);*/
}
void MyGameManager::postCurl()
{
  /* CURL *curl;
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curl, CURLOPT_URL, "http://54.186.99.234:8000/save");
  curl_easy_setopt(curl, CURLOPT_POST, 1);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "foo=bar&foz=baz");
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);*/
}

// switch to play-the-game mode
void MyGameManager::SetPlayTheGame(bool bStatus)
{
  if (m_bPlayingTheGame==bStatus)
    return;

  m_bPlayingTheGame = bStatus;

  if (m_bPlayingTheGame)
  {
     // Play the game mode is started
    // Vision::Message.Add(1, "Play the game mode has been started");
  } 
  else
  {
    //the play the game mode has been stopped.
    //clean up all your game specific instances, like e.g. particle effects
    //VisParticleGroupManager_cl::GlobalManager().Instances().Purge();
	   

  }
}

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
