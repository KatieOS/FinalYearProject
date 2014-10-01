#ifndef INVENTORY_H__INCLUDED
#define INVENTORY_H__INCLUDED
#include "GamePluginModule.h"
#include <iostream>
#include <list>
#include "Vision\Runtime\Engine\SceneElements\VisApiScreenMask.hpp"
using namespace std;



class Inventory : public IVObjectComponent
{
  public:
	  
    
	  Inventory();
	   void OneTimeInit();
	 void  OneTimeDeInit();
	  void AddToInventory(VString myKey);
	  void RemoveFromInventory(int slotNo);
	  VisScreenMaskPtr  m_pScreenMask;
	  list<VisScreenMaskPtr> mScreenMasks;
	  list<VisScreenMaskPtr>::iterator iter;
	 float nextSpace;
	 bool usingInventory;
	 void CheckTouch(hkvVec2 pos);
	 //get position
	 hkvVec2 getSlotPos(float x ,float y, float *z);
	 bool getIsUsingInventory();
	 void setIsUsingInvertory(bool inInvert);
	 void SelectItem(int itemPos);
	 void ThinkFunction();
	 void rePosition(int slotGone);
	 VString getCurrentItem();
	 int getCurrentSlot();
	  
	   // access one global instance of the Game manager
  static Inventory& InventoryManager() {return s_inventory;}

private:
   //one global instance
	static Inventory s_inventory;
	VString currentItem;
	int currentSlot;



};
#endif
