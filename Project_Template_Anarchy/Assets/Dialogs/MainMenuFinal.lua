function OnItemClicked(self, item, buttons, x, y)
  if (item:GetID() == GUI:GetID("QUIT")) then
    self:SetVisible(false)
    GUI:SetCursorVisible(false)
  elseif (item:GetID() == GUI:GetID("CHECKBOX1")) then
    local switchlight = Game:GetLight("switchlight")
    if switchlight:IsVisible() then
      switchlight:SetVisible(false)
    else
      switchlight:SetVisible(true)
    end
  end
end