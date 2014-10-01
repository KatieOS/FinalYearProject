#ifndef SAMPLEPLUGIN_SAVE_H__
#define SAMPLEPLUGIN _SAVE_H__
#include "GamePluginModule.h"



struct GameLoadData_t
{
  int iMapNumber;           // the map number
  float fTime;              // the game timer
  VBool bJustReset;         // TRUE if we just have to reset the current world and not load another one
  int iFullEntityCount;     // number of fully serialized entities
  int iRecreateEntityCount; // number of re-createable entities
};

class Save
{
   public:
	  Save();

	  void SaveMe();
	  void Load();
	  void ResetWorld();
	  void GetEntityParameters(VisBaseEntity_cl *pEnt, char *szBuf);

   protected: 
	  int m_iCurrentMap;
   float m_fInfoTime;
    bool m_bSavePending;
    int m_iGameNum;
	
};
#endif