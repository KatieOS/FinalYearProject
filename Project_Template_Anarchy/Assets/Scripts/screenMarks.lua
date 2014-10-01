-- new script file
    -- setup screen masks
    function OnAfterSceneLoaded(self)
    local x, y = Screen:GetViewportSize()
    self.Height = y
     
    -- define some items
    local item01 = { Name="Power", Texture="Textures/key.png" }
    local item02 = { Name="HealPortion", Texture="Textures/key.png" }
    local item03 = { Name="Scroll", Texture="Textures/key.png" }
    local item04 = { Name="RuneStone", Texture="Textures/key.png" }
    -- ...
     
    local items = { item01, item02, item03, item04 }
     
    -- load all screen masks
    for i, item in ipairs(items) do
    item.ScreenMask = Game:CreateScreenMask(0,0, item.Texture, item.Name)
    item.ScreenMask:SetBlending(Vision.BLEND_ALPHA)
    item.ScreenMask:SetVisible(false)
    item.ScreenMask:SetTargetSize(60,60) --What ever size fits for you
    end
     
    self.Items = items
     
    self.Inventory = {}
    AddToInventory(self, "Power")
    end
     
    function AddToInventory(self, itemName)
    if self.Inventory[itemName]==nil then
    local itemsInInv = #self.Inventory
     
    -- find the item in our table
    for i, item in ipairs(self.Items) do
    if item.Name == itemName then
    -- display the item
    self.Inventory[itemName] = item
    item.ScreenMask:SetPos(100 + itemsInInv*60, self.Height-160) --leave 10px space (50x50)
    item.ScreenMask:SetVisible(true)
    end
    end
    end
    end
     
    function RemoveFromInventory(self, itemName)
    if self.Inventory[itemName]~=nil then
    --remove it from the inventory
    local item = self.Inventory[itemName]
    item.ScreenMask:SetVisible(false)
    self.Inventory[itemName] = nil
     
    -- re-arrange item positions if needed
    local itemsInInv = #self.Inventory
    if itemsInInv>0 then
    for i, item in ipairs(self.Items) do
    item.ScreenMask:SetPos(10 + i*60, self.Height-60) --leave 10px space (50x50)
    end
    end
    end
    end
     
    -- don't forget to remove all screenmasks
    function OnBeforeSceneUnloaded(self)
    Game:DeleteAllUnrefScreenMasks()
    end