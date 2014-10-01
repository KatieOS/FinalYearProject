local move = "Up"

function OnThink(self)
    if self:GetPosition().z <= 0 then
       move = "Up"
    elseif self:GetPosition().z >= 300 then
       move ="Down"
    end
 
  -- move around...
  if move == "Up"then
    self:IncPosition(0,0,1)
  elseif move == "Down" then
    self:IncPosition(0,0,-1)
  --elseif move == "stop" then
   -- self:IncPosition(0,0,0)
   
  end
 
end 
