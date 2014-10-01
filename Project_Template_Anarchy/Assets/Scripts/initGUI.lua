-- new script file

function OnBeforeSceneLoaded(self)

  GUI:LoadResourceFile("Dialogs/MenuSystem.xml") 

  G.myDialog = GUI:ShowDialog("Dialogs/MainMenuLUA.xml") 

  GUI:SetCursorVisible(true) 
  --Timer:SetFrozen(true);
    

 end

function OnBeforeSceneUnloaded()

  local mode = Application:GetEditorMode()

  if mode == Vision.EDITOR_PLAY or mode == Vision.EDITOR_RUN then

     GUI:SetCursorVisible(false)

     GUI:CloseDialog( G.myDialog )
     

   end

 end