local platform = class("platform")

function platform:printMetaTableFun(t) --打印原表的方法
    
       local rs_tb={}
    
       local function tmp(t)
           if t then
               for _val, _val_type in pairs(t) do
                   if type(_val_type)~="userdata" then 
                       if not string.find(_val,"_") then                   
                           table.insert(rs_tb,_val)
                       end      
                   end
               end
               local ft=getmetatable(t)
               if ft then
                   tmp(ft)    
               end          
           end
       end
       tmp(getmetatable(t))
    
       table.sort(rs_tb) 
       local rs_str=""
       for i=1,#rs_tb do
           rs_str=rs_str .. rs_tb[i] .. "\n"
       end
       print(rs_str)

       if type(t) == "table" then 

        for k,v in pairs(t) do 
            print(k,v)
        end 

       end 
end

return platform