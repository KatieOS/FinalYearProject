
#include "GamePluginPCH.h"
#include "Inventory.h"


Inventory Inventory::s_inventory;
Inventory::Inventory()
	:nextSpace(0),
	currentItem(" "),
	usingInventory(false)
{
	//InitInventory();
}

void Inventory::AddToInventory(VString myKey)
{
	 std::string folder = "Textures/";
	 std::string extention = ".png";
	 std::string filename = "";
	 filename.append(folder).append(myKey).append(extention);
	 int k = 0;
	// string to char array
   char tab2[1024];
   strncpy(tab2, filename.c_str(), sizeof(tab2));
   tab2[sizeof(tab2) - 1] = 0;

   //iter
   for(iter = mScreenMasks.begin();iter != mScreenMasks.end();iter++)
   {
	  
		   if(k == nextSpace)
		   {

			   iter->GetPtr()->LoadFromFile(tab2);
			   iter->GetPtr()->SetKey(myKey);
			   nextSpace ++; 
			   k=0;
			   break;

		   }
		 k++;

   }
	
}
void Inventory::CheckTouch(hkvVec2 pos)
{
	//set up touch input for Inventory in  ios/android
	int k = 0;
	for(iter = mScreenMasks.begin();iter != mScreenMasks.end();iter++)
   {

	  float x = 100 + k*100;
	  float y = (Vision::Video.GetYRes() - 160);
	  if(pos.x > x && pos.x <(x+60))
	  {
		  if(pos.y < y +60 && pos.y >y)
		  {
	        SelectItem(k);
			
		  }

	  }
	  else
	  {
	  }
	    k++;
   }
}
hkvVec2 Inventory::getSlotPos(float x ,float y, float *z)
{
	// mScreenMasks.Get(nextSpace)->GetPos(x,y,z);
		  // hkvVec2(100 + 0*100,(Vision::Video.GetYRes() - 160));
	return hkvVec2(x,y);
		
}
void Inventory::RemoveFromInventory(int slotNo)
{
	//currentItem = " ";
   // mScreenMasks.Get(slotNo)->RemoveFromElementManager();
	int k = 0;
	for(iter = mScreenMasks.begin();iter != mScreenMasks.end();iter++)
   {
	  
		   if(k == slotNo)
		   {
			 iter =  mScreenMasks.erase(iter);
			   nextSpace--;
			   currentItem = " ";
			   //add to end
			   //rearage pass slotno
			   rePosition(slotNo);
			   break;
		   }
		   k++;
	}
	
	
}
void Inventory::OneTimeInit()
{

	for(int i = 0; i < 4; i++)
	{
	 m_pScreenMask = new VisScreenMask_cl(); // create screen mask object
     m_pScreenMask->SetTransparency(VIS_TRANSP_ALPHA); // set alpha transparency
     m_pScreenMask->LoadFromFile("Textures/colors/White.png"); // load texture
     m_pScreenMask->SetPos(100 + i*100,(Vision::Video.GetYRes() - 160)); // upper left corner
     m_pScreenMask->SetTargetSize(60,60); // size of the screen
     m_pScreenMask->SetZVal(0.0f); // not in the front - nice effect because the screen mask is clipped 
	 m_pScreenMask->SetVisible(true);
	 mScreenMasks.push_back(m_pScreenMask);
	}

}

void Inventory::OneTimeDeInit()
{
	for(int i = 0; i < 4; i++)
	{
		//mScreenMasks.Get(i)->DeleteThis();
		//iter->GetPtr()->
		
	}
}

void Inventory::setIsUsingInvertory(bool inInvent)
{
	usingInventory = inInvent;
}

bool Inventory::getIsUsingInventory()
{
	return usingInventory;
}

void Inventory::SelectItem(int itemPos)
{

	currentSlot = itemPos;
	setIsUsingInvertory(true);
	int k = 0;
	//border on screen mark?
	for(iter = mScreenMasks.begin();iter != mScreenMasks.end();iter++)
   {
	  
		   if(k == itemPos)
		   {
	          iter->GetPtr()->SetColor(VColorRef(50,255,50,50));// set alpha transparency
	          currentItem = iter->GetPtr()->GetKey();

			  break;
		   }
		   k++;
	}

	

}
void Inventory::ThinkFunction()
{

#ifdef SUPPORTS_MOUSE
	//if in inventory on windows
	if (Vision::Key.IsPressed(VGLK_1))

	{
		SelectItem(0);

	}
	else if (Vision::Key.IsPressed(VGLK_2))

	{
		SelectItem(1);

	}
	else if (Vision::Key.IsPressed(VGLK_3))

	{
		SelectItem(2);

	}
	else if (Vision::Key.IsPressed(VGLK_4))

	{
		SelectItem(3);

	}
#endif;

	//
	//#if defined(_VISION_MOBILE)
	// if(mInputMap()->GetTrigger(PI_SLOT1) >0.0f)
   // {
   //     SelectItem(0);
	//}

  //  #endif
	
}

VString Inventory::getCurrentItem()
{
	return currentItem;
}
int Inventory::getCurrentSlot()
{
	return currentSlot;
}

void Inventory::rePosition(int slotGone)
{
	int k = 0;
	bool found = false;
	//move slots
	for(iter = mScreenMasks.begin();iter != mScreenMasks.end();iter++)
   {
      if(k == slotGone)
	  {
		  found = true;
	  }
	  if(found== true)
	  {
		  iter->GetPtr()->SetPos(100 + k*100,(Vision::Video.GetYRes() - 160)); 
	  }
	  k++;
   }
	//add new slot to end of list
	 m_pScreenMask = new VisScreenMask_cl(); // create screen mask object
     m_pScreenMask->SetTransparency(VIS_TRANSP_ALPHA); // set alpha transparency
     m_pScreenMask->LoadFromFile("Textures/colors/White.png"); // load texture
     m_pScreenMask->SetPos(100 + 3*100,(Vision::Video.GetYRes() - 160)); // upper left corner
     m_pScreenMask->SetTargetSize(60,60); // size of the screen
     m_pScreenMask->SetZVal(0.0f); // not in the front - nice effect because the screen mask is clipped 
	 m_pScreenMask->SetVisible(true);
	mScreenMasks.push_back(m_pScreenMask);
}

