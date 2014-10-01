
#pragma once
#include "GamePluginModule.h"

#include <Vision/Runtime/EnginePlugins/VisionEnginePlugin/GUI/VMenuIncludes.hpp>
#include <Vision/Runtime/EnginePlugins/VisionEnginePlugin/GUI/VDialog.hpp>


///////////////////////////////////////////////////////////////////////////////
// Sub dialog class
///////////////////////////////////////////////////////////////////////////////
extern VModule g_sampleModule;


class SubDialog : public VDialog
{
public:
  // get the item click event
  VOVERRIDE void OnItemClicked(VMenuEventDataObject *pEvent);

protected:
  V_DECLARE_SERIAL_DLLEXP( SubDialog, SAMPLEPLUGIN_IMPEXP )
  VOVERRIDE void Serialize( VArchive &ar ) {}
};
class MainMenu : public VDialog
{
public:
  MainMenu() : VDialog(), m_pExitDialog(NULL) {}

  // overridden function to prompt a dialog before actually closing
  VOVERRIDE void SetDialogResult(int iResult);

  // get the item click event
  VOVERRIDE void OnItemClicked(VMenuEventDataObject *pEvent);

  // override this function to get the ESC key
  VOVERRIDE void OnKeyPressed(int iKey, int iKeyModifier)
  {
   // VDialog::OnKeyPressed(iKey,iKeyModifier);
   // if (iKey==VGLK_ESC)
      //SetDialogResult(VGUIManager::ID_OK); // if we use ID_CANCEL here, it pops up the request dialog, so we use OK
  }

  VOVERRIDE void OnTick(float dtime);

protected:
  V_DECLARE_SERIAL_DLLEXP( MainMenu, SAMPLEPLUGIN_IMPEXP )
  VOVERRIDE void Serialize( VArchive &ar ) {}

  VDialog* m_pExitDialog;
};
class ControlDialog : public SubDialog
{
public:
  VOVERRIDE void OnItemClicked(VMenuEventDataObject *pEvent);

protected:
  V_DECLARE_SERIAL_DLLEXP( ControlDialog, SAMPLEPLUGIN_IMPEXP  )
  VOVERRIDE void Serialize( VArchive &ar ) {}
};
