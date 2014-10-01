
#ifndef COMPONANTMANAGER_H_INCLUDED
#define COMPONANTMANAGER_H_INCLUDED

#include "GamePluginModule.h"
class ComponentManager : public IVisCallbackHandler_cl
{
public:
	 void OneTimeInit();
	 void OneTimeDeInit();
	 virtual  void OnHandleCallback(IVisCallbackDataObject_cl *pData) HKV_OVERRIDE;
	 // holds the collection of all instances of MyComponent
      VRefCountedCollection<PlayerComponent> m_Components;

     // one global instance of our manager
     static ComponentManager g_GlobalManager;
};
#endif