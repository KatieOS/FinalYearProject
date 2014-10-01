#include "GamePluginPCH.h"
#include "MainMenu.h"



VModule &GUIModule = VGUIManager::GUIModule();
V_IMPLEMENT_SERIAL( SubDialog, VDialog, 0, &GUIModule );
V_IMPLEMENT_SERIAL( MainMenu, VDialog, 0, &GUIModule );
V_IMPLEMENT_SERIAL( ControlDialog, VDialog, 0, &GUIModule );

void SubDialog::OnItemClicked(VMenuEventDataObject *pEvent)
{
  VDialog::OnItemClicked(pEvent);

/*  int iDlgResult = GetDialogResult();
  if ((iDlgResult == VGUIManager::ID_CANCEL) || (iDlgResult == VGUIManager::ID_OK))
  {
    GetContext()->CloseDialog(this);
  }*/
}

// Override this function to prompt a message box before actually closing the dialog
void MainMenu::SetDialogResult(int iResult)
{
 /* #if !defined(_VISION_ANDROID) && !defined(_VISION_TIZEN)
  // When the main dialog wants to quit, prompt a modal message box
  if (iResult==VGUIManager::ID_CANCEL)
  {
    m_pExitDialog = GetContext()->ShowDialog("GUI\\Dialogs\\MessageBox_Abort.xml");
    return;
  }
  #endif

  VDialog::SetDialogResult(iResult);*/
}
void MainMenu::OnItemClicked(VMenuEventDataObject *pEvent)
{
  /*VDialog::OnItemClicked(pEvent); // important: forward this event to the base class

  IVGUIContext* pContext = GetContext();

  for (int i=0; i<pContext->GetOpenDialogs().Count(); ++i) 
  {
    if (pContext->GetOpenDialogs().GetAt(i) == this)
      continue;

    if ((m_pExitDialog != NULL) && (pContext->GetOpenDialogs().GetAt(i) == m_pExitDialog))
      continue;
    
    pContext->CloseDialog(pContext->GetOpenDialogs().GetAt(i));
  }

  // Open push buttons dialog
  if (pEvent->m_pItem->GetID()==VGUIManager::GetID("DLG_PUSHBUTTONS"))
  {
    GetContext()->ShowDialog("GUI\\Dialogs\\Dialog_PushButtons.xml");
    return;
  }

  // Open list control dialog
  if (pEvent->m_pItem->GetID()==VGUIManager::GetID("DLG_LISTCONTROL"))
  {
    #if defined(_VISION_PSP2) || defined(_VISION_MOBILE) || defined(HK_ANARCHY)
       GetContext()->ShowDialog("GUI\\Dialogs\\Dialog_ListControl_Mobile.xml");
    #else
       GetContext()->ShowDialog("GUI\\Dialogs\\Dialog_ListControl.xml");
    #endif
    return;
  }*/
}
void MainMenu::OnTick(float dtime)
{
  VDialog::OnTick(dtime);

 /* if (m_pExitDialog)
  {
    int iDlgResult = m_pExitDialog->GetDialogResult();

    if (iDlgResult != 0)
    {
      GetContext()->CloseDialog(m_pExitDialog);
      m_pExitDialog = NULL;

      if (iDlgResult == VGUIManager::ID_YES)
        VDialog::SetDialogResult(VGUIManager::ID_CANCEL);
    }
  }*/
}

void ControlDialog::OnItemClicked(VMenuEventDataObject *pEvent)
{
  SubDialog::OnItemClicked(pEvent); // important: forward this event to the base class

 /* if (pEvent->m_pItem->GetID()==VGUIManager::GetID("ADD_LISTITEM"))
  {
    VListControl *pListCtrl = (VListControl *)Items().FindItem(VGUIManager::GetID("LISTCTRL"));
    VASSERT(pListCtrl);
    char szItemName[512];
    sprintf(szItemName,"New item #%i",pListCtrl->Items().Count()+1);
    VListControlItem *pNewItem = pListCtrl->AddItem(szItemName, -1); // add (to the end)

    pListCtrl->EnsureVisible(pNewItem); // make sure the new item is visible
    return;
  }

  if (pEvent->m_pItem->GetID()==VGUIManager::GetID("CLEAR_LISTITEMS"))
  {
    VListControl *pListCtrl = (VListControl *)Items().FindItem(VGUIManager::GetID("LISTCTRL"));
    VASSERT(pListCtrl);
    pListCtrl->Reset();
    return;
  }*/
}


