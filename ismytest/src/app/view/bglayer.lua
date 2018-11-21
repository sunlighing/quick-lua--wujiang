local playtform = import("app.platform")
local hero = import("app.view.hero")
local Actor = import("app.model.actor")
local bglayer = class("bglayer",function ()
    return display.newLayer()
end)

function bglayer:ctor()
   -- bglayer:setLayertSize(display.width,display.height)
   playtform:printMetaTableFun(self)
   self:ctor_sc()
end 

function bglayer:ctor_sc()
    local particle =  cc.ParticleFire:create()
    particle:setStartColor(cc.c3b(255, 122, 122))
    particle:setPosition(0,320)
    local sequence1 = cc.Sequence:create(
        cc.MoveTo:create(1,cc.p(480,0)),
        cc.MoveTo:create(1,cc.p(960,320)),
        cc.MoveTo:create(1,cc.p(480,640)),
        cc.MoveTo:create(1,cc.p(0,320))
    )
    particle:runAction(cc.RepeatForever:create(sequence1))
    self:addChild(particle)
end


return bglayer