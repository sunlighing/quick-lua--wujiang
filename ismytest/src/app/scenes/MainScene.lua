local bg = import("app.view.bglayer")
local playtform = import("app.platform")
local hero = import("app.view.hero")
local Actor = import("app.model.actor")
local sc = import("app.net.simptcp")--"framework.cc.net.SocketTCP")

local MainScene = class("MainScene",function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    display.newColorLayer(cc.c4b(155, 155, 255, 255)):addTo(self)
    print("display.newColorLayer addto self")
    bg:new():addTo(self)
  --  sc:main()
    self:main(bg)
    playtform:printMetaTableFun(bg)
--    sc:connect("192.168.172.129",8888,true)
    --self:addChild(bg)
   -- print("bg:ctor().addto")
   local hero_a = hero:new()
   print("type hero ->",type(hero),type(hero_a))
   hero_a:ctor()
   self:addChild(hero_a)
   hero_a:setTag(300)
   hero_a:setPosition(200,200)
 
end 


function MainScene:main(bg)
    local lisetener = cc.EventListenerMouse:create()
    lisetener:registerScriptHandler(function (Touch,event)
         Actor:main(self,Touch,event)
        -- body
    end,cc.Handler.EVENT_MOUSE_DOWN)
    playtform:printMetaTableFun(bg)
    local eventDispathcher = self:getEventDispatcher()
    eventDispathcher:addEventListenerWithSceneGraphPriority(lisetener, self)  
 end

function MainScene:onEnter()

end 

function MainScene:onExit()

end 

return MainScene