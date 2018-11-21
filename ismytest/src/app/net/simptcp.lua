local socket = import("socket")
local pl = import("app.platform")
if not socket then return end 

local SimpleTcp =class("SimpleTcp")
function SimpleTcp:main()
    print("[[in to scoket]]",type(socket))
    -- pl.printMetaTableFun(socket)
    -- for k,v in pairs(socket) do 
    --     print(k,v)
    -- end 
    -- body
    self.tcp = socket.tcp()
    local __succ, __status = self.tcp:connect("192.168.172.129",8001)
    print("_succ->",__succ,"__status",__status)
    self.tcp:send("hello")
    --  local tp = self.tcp:receive()
    --  print(type(tp),"tp")
    
end


return SimpleTcp