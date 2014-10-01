#include "GamePluginPCH.h"
#include "PickUp.h"
#include "GameManager.h"
#include"PluginMain.h"

#include <Vision/Runtime/EnginePlugins/VisionEnginePlugin/GUI/VMenuIncludes.hpp>
#include <Vision/Runtime/Base/System/Memory/VMemDbg.hpp>
V_IMPLEMENT_SERIAL( PickUp, SerializeBaseEntity_cl, 0,&g_myComponentModule);

// Variable table
START_VAR_TABLE(PickUp,VisBaseEntity_cl,"Plick Up Class",0,"")
DEFINE_VAR_FLOAT(PickUp, mPickUpRadius, "Health recovery percentage", "100", 0, 0);
DEFINE_VAR_VSTRING(PickUp, mPickUpID, "Path key to follow", " ", 0, 0, NULL);
 //DEFINE_VAR_VSTRING(VFollowPathComponent, PathKey, "The object key of the path shape to follow. Obsolete if a PathObject is specified directly", "", 0,0, NULL);

 // add more parameters here
END_VAR_TABLE


PickUp::PickUp()
	:hit(false)
{
}


void PickUp::Initialize()
{

	Inherited::InitFunction();
	SetTraceAccuracy(VIS_TRACEACC_POLYGONS);
	//set rigid body
    mRigidBodyComponent = static_cast<vHavokRigidBody*>(Components().GetComponentOfType(V_RUNTIME_CLASS(vHavokRigidBody)));

    if(!mRigidBodyComponent)
    {
      mRigidBodyComponent = new vHavokRigidBody();
      VASSERT(mRigidBodyComponent);
      mRigidBodyComponent->Initialize();
     // mRigidBodyComponent->Shape_Type = ShapeType_BOX;
	 //  mRigidBodyComponent->Shape_BoxSize;
     // mRigidBodyComponent->Havok_QualityType = QualityType_MOVING;
     // mRigidBodyComponent->Havok_CollisionLayer = vHavokPhysicsModule::HK_LAYER_COLLIDABLE_CUSTOM4; // this pickup should only collide with static geometry and terrain
      mRigidBodyComponent->Havok_Mass = 10;

      AddComponent(mRigidBodyComponent);
	  }

	mPickUpSound = VFmodManager::GlobalManager().LoadSoundResource("Sounds//score.wav", VFMOD_RESOURCEFLAG_2D)->CreateInstance(GetPosition(),!VFMOD_FLAG_LOOPED);
	mPickUpSound->SetPaused(true);
	
	
}
void PickUp::ThinkFunction()
{
	CheckPlayerContact();
	CheckifPickUpSelect();
	
	


	//{
	  

	/*hkvVec2 pCursor = hkvVec2(Vision::Mouse.GetX(), Vision::Mouse.GetY());
	Vision::Camera.GetCurrentCameraPosition();
	hkvVec3 traceStart = Vision::Camera.GetCurrentCameraPosition();
   hkvVec3 traceDir;
   VisRenderContext_cl *pContext = Vision::Renderer.GetRendererNode(0)->GetReferenceContext();
	   //::GetRendererNode(0)->GetReferenceContext();
	pContext->GetTraceDirFromScreenPos(Vision::Mouse.GetX(),Vision::Mouse.GetY(),traceDir,1000.f);
	//pushDir = Screen:Project3D(x, y, 500) - Screen:Project3D(x,y, 10);
	// mRigidBodyComponent->SetLinearVelocity(traceDir);
	SetPosition(Vision::Mouse.GetX(),Vision::Mouse.GetY(),GetPosition().z);*/
	//}





}

void PickUp::OnPickUp()
{
	//do when picked up
	//add to inventory
	VString keycheck = mPickUpID;
	Inventory::InventoryManager().AddToInventory(mPickUpID);
	mPickUpSound->SetPaused(false);
	
    

}

void PickUp::Serialize(VArchive& ar)
{
  Inherited::Serialize(ar);
	//VisBaseEntity_cl::Serialize(ar);
  if(ar.IsLoading())
  {
    ar >> mPickUpRadius >> mPickUpID;
	
    
  }
  else
  {
   ar << mPickUpRadius <<mPickUpID;
  }



}


void PickUp::CheckPlayerContact()
{
  VArray<Player*> const& characters = MyGameManager::GlobalManager().GetCharacters();


  hkvVec3 const& currentPosition = GetPosition();

  for(int index = 0; index < characters.GetSize(); ++index)
  {
    Player* character = characters.GetAt(index);

    // only target players
//    if(!character->IsOfType(V_RUNTIME_CLASS(Player)))
   // {
  //    continue;
  //  }

    hkvVec3 const& targetPosition = character->GetPosition();

    float currentRangeSquared = (currentPosition - targetPosition).getLengthSquared();
	bool hit;

    if(currentRangeSquared <= mPickUpRadius * mPickUpRadius)
    {
      // call OnPickup for subclasses
       OnPickUp();

      // play the pickup effect
      //CreateEffect(PKFX_Pickup, GetPosition(), GetOrientation());

      // setup this object for deletion
	   DisposeObject();
//	   SetMesh("");
	   hit = true;

	   //SetVisable(false);
	   
	   

    }
  }





}

void PickUp::CheckifPickUpSelect()
{
	VString PickUpSelect =  Inventory::InventoryManager().getCurrentItem();
	//if(PickUpSelect == mPickUpID)
	//{
		//PickUpActive();
	//}
}

void PickUp::PickUpActive()
{

}
