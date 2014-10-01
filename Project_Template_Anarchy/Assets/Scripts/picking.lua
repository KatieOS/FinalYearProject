function OnAfterSceneLoaded(self)
  self.map = Input:CreateMap("InputMap")
  local w, h = Screen:GetViewportSize()

  -- touch input setup
  self.map:MapTrigger("X", {0, 0, w, h}, "CT_TOUCH_ABS_X")
  self.map:MapTrigger("Y", {0, 0, w, h}, "CT_TOUCH_ABS_Y")
  self.map:MapTrigger("Pick", {0, 0, w, h}, "CT_TOUCH_ANY", {once = false}) 

  -- mouse input setup (windows)
  self.map:MapTrigger("X", "MOUSE", "CT_MOUSE_ABS_X")
  self.map:MapTrigger("Y", "MOUSE", "CT_MOUSE_ABS_Y")
  self.map:MapTrigger("Pick", "MOUSE", "CT_MOUSE_LEFT_BUTTON", {once = false})
end-- new script file

function OnBeforeSceneUnloaded(self)
  Input:DestroyMap(self.map);
end
 function OnThink(self)
  -- pixel coordinates
  local x = self.map:GetTrigger("X")
  local y = self.map:GetTrigger("Y")   

  if self.map:GetTrigger("Pick")>0 then 
    -- when starting clicking/touch, try to pick an object
    if self.picked == nil then
      local picked = Screen:PickEntity(x,y, 50000, true)     
      if picked ~= nil then
        self.picked = picked
      end
    end   
  else   

    if self.picked ~= nil then
      -- when we quit clicking/touch, push picked object in current picking direction
      local pushDir = Screen:Project3D(x, y, 500) - Screen:Project3D(x,y, 10);
      pushDir:normalize();
      self.picked:GetComponentOfType("vHavokRigidBody"):SetLinearVelocity(pushDir * 2000)
    end
    self.picked = nil
    self.point = nil
  end 

  if self.picked ~= nil then
    -- while an object is picked (but not released yet) keep pushing it up
    self.picked:GetComponentOfType("vHavokRigidBody"):SetLinearVelocity(Vision.hkvVec3(0, 0, 5000 * Timer:GetTimeDiff()))
  end

  if Application:GetPlatformName() == "WIN32DX9" or Application:GetPlatformName() == "WIN32DX11" then
    -- draw cursor
    Debug.Draw:Line2D(x,y,x+10,y+5, Vision.V_RGBA_GREEN)
    Debug.Draw:Line2D(x,y,x+5,y+10, Vision.V_RGBA_GREEN)
    Debug.Draw:Line2D(x+10,y+5,x+5,y+10, Vision.V_RGBA_GREEN)
  end
end