
require("config")
require("framework.init")
require("framework.shortcodes")
require("framework.cc.init")

local MyApp = class("MyApp",cc.mvc.AppBase)

function MyApp:ctor()
    MyApp.super.ctor(self)
    print("MyApp.get it ")
    self.objects_ = {}
end

function MyApp:run()
    cc.FileUtils:getInstance():addSearchPath("res/")
    cc.SpriteFrameCache:getInstance():addSpriteFrames("res/wujiang.plist")
    self:enterScene("MainScene")
    print("MainScene into ")
end

function MyApp:setObject(id, object)
    assert(self.objects_[id] == nil, string.format("MyApp:setObject() - id \"%s\" already exists", id))
    self.objects_[id] = object
end

function MyApp:getObject(id)
    assert(self.objects_[id] ~= nil, string.format("MyApp:getObject() - id \"%s\" not exists", id))
    return self.objects_[id]
end

function MyApp:isObjectExists(id)
    return self.objects_[id] ~= nil
end

function MyApp:onEnterBackground()
    display.pause()
end

function MyApp:onEnterForeground()
    display.resume()
end


return MyApp