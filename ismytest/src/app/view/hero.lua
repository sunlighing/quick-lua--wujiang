local hero = class("hero",function ()
   return  display.newSprite()
    -- body
end)
local spriteframe = cc.SpriteFrameCache:getInstance()

function hero:ctor()
    self:setSpriteFrame(spriteframe:getSpriteFrame("you.png"))
end 

function hero:walk_right()
    self:setSpriteFrame(spriteframe:getSpriteFrame("you.png"))
    self:runAction(cc.MoveTo:create(0.5,cc.p(self:getPositionX()+50,self:getPositionY())))
end 

function hero:walk_left()
    self:setSpriteFrame(spriteframe:getSpriteFrame("zuo.png"))
    self:runAction(cc.MoveTo:create(0.5,cc.p(self:getPositionX()-50,self:getPositionY())))
end 

function hero:walk_xia()
    self:setSpriteFrame(spriteframe:getSpriteFrame("xia.png"))
    self:runAction(cc.MoveTo:create(0.5,cc.p(self:getPositionX(),self:getPositionY()-50)))
end 

function hero:walk_zuoxia()
    self:setSpriteFrame(spriteframe:getSpriteFrame("zuoxia.png"))
    self:runAction(cc.MoveTo:create(0.5,cc.p(self:getPositionX()-50,self:getPositionY()-50)))
end 

function hero:walk_youxia()
    self:setSpriteFrame(spriteframe:getSpriteFrame("youxia.png"))
    self:runAction(cc.MoveTo:create(0.5,cc.p(self:getPositionX()+50,self:getPositionY()-50)))
end 

function hero:walk_shang()
    self:setSpriteFrame(spriteframe:getSpriteFrame("shang.png"))
    self:runAction(cc.MoveTo:create(0.5,cc.p(self:getPositionX(),self:getPositionY()+50)))
end 

function hero:walk_youshang()
    self:setSpriteFrame(spriteframe:getSpriteFrame("youshang.png"))
    self:runAction(cc.MoveTo:create(0.5,cc.p(self:getPositionX()+50,self:getPositionY()+50)))
end 

function hero:walk_zuoshang()
    self:setSpriteFrame(spriteframe:getSpriteFrame("zuoshang.png"))
    self:runAction(cc.MoveTo:create(0.5,cc.p(self:getPositionX()-50,self:getPositionY()+50)))
end 

return hero 
