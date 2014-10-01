-- new script file
function OnItemClicked(self, item, buttons, x, y)

  if (item:GetID() == GUI:GetID("QUIT")) then

    self:SetVisible(false)

    GUI:SetCursorVisible(false)
    Timer:SetFrozen(false);

  end

end