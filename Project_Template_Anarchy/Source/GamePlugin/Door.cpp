#include "GamePluginPCH.h"
#include "GameManager.h"
#include"PluginMain.h"
#include "door.h"


V_IMPLEMENT_SERIAL(Door, PickUp, 0,&g_myComponentModule);
// Variable table
START_VAR_TABLE(Door,VisBaseEntity_cl,"Plick Up Class",0,"")
DEFINE_VAR_FLOAT(Door, mDoorRadius, "Health recovery percentage", "100", 0, 0);
DEFINE_VAR_VSTRING(Door, mPuzzleID, "Path key to follow", " ", 0, 0, NULL);
 //DEFINE_VAR_VSTRING(VFollowPathComponent, PathKey, "The object key of the path shape to follow. Obsolete if a PathObject is specified directly", "", 0,0, NULL);

 // add more parameters here
END_VAR_TABLE
Door::Door()
	:mDoorRadius(200.0f)
{

}

void Door::Initialize()
{
	 mRigidBodyComponent = static_cast<vHavokRigidBody*>(Components().GetComponentOfType(V_RUNTIME_CLASS(vHavokRigidBody)));

    if(!mRigidBodyComponent)
    {
      mRigidBodyComponent = new vHavokRigidBody();
      VASSERT(mRigidBodyComponent);
      mRigidBodyComponent->Initialize();
	  mRigidBodyComponent->Havok_MotionType = MotionType_FIXED;
      mRigidBodyComponent->Havok_Mass = 10;
      AddComponent(mRigidBodyComponent);
	  }
	//mDoorRadius= 200;
}
void Door::Serialize(VArchive& ar)
{
  Inherited::Serialize(ar);
	//VisBaseEntity_cl::Serialize(ar);
  if(ar.IsLoading())
  {
    ar >> mDoorRadius >> mPuzzleID;
	
    
  }
  else
  {
   ar << mDoorRadius <<mPuzzleID;
  }



}
void Door::ThinkFunction()
{
	//PickUp::ThinkFunction();
	CheckCanPass();
	
}

void Door::CheckCanPass()
{
	 VArray<Player*> const& characters = MyGameManager::GlobalManager().GetCharacters();


  hkvVec3 const& currentPosition = GetPosition();

  for(int index = 0; index < characters.GetSize(); ++index)
  {
    Player* character = characters.GetAt(index);

    // only target players
    if(!character->IsOfType(V_RUNTIME_CLASS(Player)))
    {
      continue;
    }

    hkvVec3 const& targetPosition = character->GetPosition();

    float currentRangeSquared = (currentPosition - targetPosition).getLengthSquared();
	//bool hit;
	mDoorRadius  = 200;
    if(currentRangeSquared <= mDoorRadius * mDoorRadius)
    {

		//check you have key 
		VString selectItem =  Inventory::InventoryManager().getCurrentItem();
		if(selectItem == mPuzzleID)
		{
           // setup this object for deletion
	       DisposeObject(); 
		   Inventory::InventoryManager().RemoveFromInventory(Inventory::InventoryManager().getCurrentSlot());
		   

		}

    }
  }
}

