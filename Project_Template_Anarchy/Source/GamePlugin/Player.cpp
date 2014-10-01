

#include "GamePluginPCH.h"
#include"Player.h"
#include"PluginMain.h"
#include "VisionSerializer.h"
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokCharacterController.hpp>
#include <Vision/Samples/Engine/HavokAi/HavokAiPCH.h>
#include <Vision/Samples/Engine/HavokAi/PathPickDlg.hpp>
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokConversionUtils.hpp>

#include <Vision/Runtime/EnginePlugins/Havok/HavokAiEnginePlugin/vHavokAiModule.hpp>
#include <Ai/Pathfinding/World/hkaiWorld.h>
#include <Vision/Runtime/EnginePlugins/Havok/HavokAiEnginePlugin/vHavokAiNavMeshResource.hpp>




V_IMPLEMENT_SERIAL( Player, SerializeBaseEntity_cl, 0,&g_myComponentModule);

// Variable table
START_VAR_TABLE(Player,VisBaseEntity_cl,"Player Class",0,"")
DEFINE_VAR_FLOAT(Player, iHealth, "Health recovery percentage", "50", 0, 0);
 // add more parameters here
END_VAR_TABLE

Player::Player()
   :m_spNormalizeMixerNode(NULL)
  , m_spLayerMixerNode(NULL)
  , m_spSingleAnimControl(NULL)
  , m_spBoneModifierNode(NULL)
  , m_iHeadBoneIndex(-1)
  , m_iNeckBoneIndex(-1)
  , m_iMixerInputWalk(-1), m_iMixerInputRun(-1)
  , m_sHighlightedBoneName()
  , m_fBoneHighlightDuration(0.0f)
  , m_iAnimEventFootStepLeft(-1)
  , m_iAnimEventFootStepRight(-1)
{
	mCollisionRadius = 40.0f;
    mCollisionHeight = 160.0f;
    m_sensorSize =128.0f;
    m_desiredSpeed =200.0f;
	
	 

}

void Player::CalcPositionForTargeting(hkvVec3& targetOut) const
{
  //targetOut = 0.5f * (GetEyePosition() + GetPosition());
}

void Player::InitFunction()
{
  Inherited::InitFunction();
  this->SetMesh("Models/ElfWarrior/ElfWarrior.model");

  m_iAnimEventFootStepLeft = Vision::Animations.RegisterEvent("footstep_left");
  m_iAnimEventFootStepRight = Vision::Animations.RegisterEvent("footstep_right");

  IncOrientation(-90.0f, 0.0f, 0.0f);

  
  PostInitialize();
  m_fVal = 12.34f;
  //m_vPosition = GetPosition();
 // BaseInit();
  //sound first then animation to stop aceess violation 
  mWalkSound = VFmodManager::GlobalManager().LoadSoundResource("Sounds//Footstep_Run_Stone_Left_01_Sound.wav", VFMOD_RESOURCEFLAG_2D)->CreateInstance(GetPosition(),VFMOD_FLAG_LOOPED);
	//mWalkSound->SetPaused(true);
  StartIdleAnimation(true);

}
void Player::InitInputMap()
{
		
}
void Player::ThinkFunction()
{
	
	//VisBaseEntity_cl::DrawBoundingBox(false,VColorRef(255, 255, 255),1.0f);
	
	
	

  
}
void Player::PostInitialize()
{
	MyGameManager::GlobalManager().AddCharacter(this);
	
}


void Player::MessageFunction(int id, INT_PTR paramA, INT_PTR paramB)
{
  VisBaseEntity_cl::MessageFunction(id, paramA, paramB);
 
 /*  switch(id)
  {
  case VisionUserMessages::kHavokAnimationEvent:
    OnHavokAnimationEvent(*(hkbEvent*)(paramA), paramB != 0);
    break;
  }*/
 
}

void Player::BaseInit()
{
	
	SetPosition(20,20,100);
}
void Player::Serialize(VArchive& ar)
{
  Inherited::Serialize(ar);
  if(ar.IsLoading())
  {
    ar >>iHealth;
    BaseInit();
  }
  else
  {
    ar << iHealth;
  }



}


hkvVec2 Player::GetCursorPosition()
{
	

	return pCursor;

}
void Player::SetCursorPosition()
{
    pCursor = hkvVec2(Vision::Mouse.GetX(), Vision::Mouse.GetY());

}

hkvVec3 Player::GetPlayerPosition()
{
	

	return mPosition;

}
void Player::SetPlayerPosition()
{
    mPosition =  hkvVec3(GetPosition());

}
void Player::GetTargetPosition()
{
}
float Player::GetCollisionRadius() const
{
  return mCollisionRadius;
}

float Player::GetCollisionHeight() const
{
  return mCollisionHeight;
}
VType* Player::GetControllerComponentType()
{
  return V_RUNTIME_CLASS(PlayerComponent);
}
void Player::StartIdleAnimation(bool bLooped) 
{
	 
  // start a simple skeletal animation
  int iFlags = VSKELANIMCTRL_DEFAULTS;
  if (bLooped)
    iFlags |= VANIMCTRL_LOOP;
  m_spSingleAnimControl = VisAnimConfig_cl::StartSkeletalAnimation(this, "Stand", iFlags);
  mWalkSound->SetPaused(true);
 
}
void Player::StartWalkAnimation(bool bLooped) 
{
  // start a simple skeletal animation
  int iFlags = VSKELANIMCTRL_DEFAULTS;
  if (bLooped)
    iFlags |= VANIMCTRL_LOOP;
  m_spSingleAnimControl = VisAnimConfig_cl::StartSkeletalAnimation(this, "Walk", iFlags);
  mWalkSound->SetPaused(false);
  //play walk sound
  //Footstep_Run_Stone_Left_01_Sound
}

