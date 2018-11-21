local actor = class("actor",cc.mvc.ModelBase)

function actor:main(target,touch,event)
    local touch_position = touch:getLocationInView()
    local retarget =  target:getChildByTag(300)
    print("retarget get touch_position",type(retarget:getPosition()),retarget:getPosition())
    local x,y = retarget:getPosition()
    print("touch x, y ",touch_position.x,touch_position.y)
    if touch_position.x > x +50  and touch_position.y > y then 
        retarget:walk_youshang()
    elseif  touch_position.x >x and touch_position.y < y+50 and touch_position.y > y -50 then 
        retarget:walk_right()
    elseif touch_position.x  > x +50 and touch_position.y < y then 
        retarget:walk_youxia()
    elseif touch_position.x < x -50 and touch_position.y < y then 
        retarget:walk_zuoxia()
    elseif touch_position.x < x and touch_position.y < y+50 and touch_position.y > y -50  then 
        retarget:walk_left()
    elseif touch_position.x < x -50 and touch_position.y > y then 
        retarget:walk_zuoshang()
    elseif touch_position.x < x+50 and touch_position.x > x -50 and touch_position.y > y then 
        retarget:walk_shang()
    elseif touch_position.x <50+ x and touch_position.x > x -50 and touch_position.y < y then 
        retarget:walk_xia()
    end 
    -- body
end


return actor