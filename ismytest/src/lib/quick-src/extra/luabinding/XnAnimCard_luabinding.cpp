#include "XnAnimCard_luabinding.h"
#include "animcard/XnAnimCard.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "cocos2d/LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"

int lua_AnimCard_AnimCard_getHitTEstEdgeSizeScale(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimCard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimCard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AnimCard_AnimCard_getHitTEstEdgeSizeScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_getHitTEstEdgeSizeScale'", nullptr);
            return 0;
        }
        double ret = cobj->getHitTEstEdgeSizeScale();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimCard:getHitTEstEdgeSizeScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_getHitTEstEdgeSizeScale'.",&tolua_err);
#endif

    return 0;
}
int lua_AnimCard_AnimCard_setAutoFixDistance(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimCard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimCard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AnimCard_AnimCard_setAutoFixDistance'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.AnimCard:setAutoFixDistance");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_setAutoFixDistance'", nullptr);
            return 0;
        }
        cobj->setAutoFixDistance(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimCard:setAutoFixDistance",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_setAutoFixDistance'.",&tolua_err);
#endif

    return 0;
}
int lua_AnimCard_AnimCard_clearTurnPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimCard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimCard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AnimCard_AnimCard_clearTurnPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_clearTurnPoint'", nullptr);
            return 0;
        }
        cobj->clearTurnPoint();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimCard:clearTurnPoint",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_clearTurnPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_AnimCard_AnimCard_setHitTestCenterSizeScale(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimCard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimCard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AnimCard_AnimCard_setHitTestCenterSizeScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.AnimCard:setHitTestCenterSizeScale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_setHitTestCenterSizeScale'", nullptr);
            return 0;
        }
        cobj->setHitTestCenterSizeScale(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimCard:setHitTestCenterSizeScale",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_setHitTestCenterSizeScale'.",&tolua_err);
#endif

    return 0;
}
int lua_AnimCard_AnimCard_setNeedDepthTest(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimCard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimCard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AnimCard_AnimCard_setNeedDepthTest'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.AnimCard:setNeedDepthTest");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_setNeedDepthTest'", nullptr);
            return 0;
        }
        cobj->setNeedDepthTest(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimCard:setNeedDepthTest",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_setNeedDepthTest'.",&tolua_err);
#endif

    return 0;
}
int lua_AnimCard_AnimCard_setHitTestEdgeSizeScale(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimCard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimCard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AnimCard_AnimCard_setHitTestEdgeSizeScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.AnimCard:setHitTestEdgeSizeScale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_setHitTestEdgeSizeScale'", nullptr);
            return 0;
        }
        cobj->setHitTestEdgeSizeScale(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimCard:setHitTestEdgeSizeScale",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_setHitTestEdgeSizeScale'.",&tolua_err);
#endif

    return 0;
}
int lua_AnimCard_AnimCard_isAutoTurnning(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimCard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimCard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AnimCard_AnimCard_isAutoTurnning'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_isAutoTurnning'", nullptr);
            return 0;
        }
        bool ret = cobj->isAutoTurnning();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimCard:isAutoTurnning",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_isAutoTurnning'.",&tolua_err);
#endif

    return 0;
}
int lua_AnimCard_AnimCard_setTurnPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimCard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimCard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AnimCard_AnimCard_setTurnPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.AnimCard:setTurnPoint");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.AnimCard:setTurnPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_setTurnPoint'", nullptr);
            return 0;
        }
        cobj->setTurnPoint(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimCard:setTurnPoint",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_setTurnPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_AnimCard_AnimCard_setRoundRadius(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimCard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimCard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AnimCard_AnimCard_setRoundRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.AnimCard:setRoundRadius");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_setRoundRadius'", nullptr);
            return 0;
        }
        cobj->setRoundRadius(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimCard:setRoundRadius",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_setRoundRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_AnimCard_AnimCard_setAutoTurnSpeed(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimCard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimCard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AnimCard_AnimCard_setAutoTurnSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.AnimCard:setAutoTurnSpeed");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_setAutoTurnSpeed'", nullptr);
            return 0;
        }
        cobj->setAutoTurnSpeed(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimCard:setAutoTurnSpeed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_setAutoTurnSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_AnimCard_AnimCard_getHitTestCenterSizeScale(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimCard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimCard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AnimCard_AnimCard_getHitTestCenterSizeScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_getHitTestCenterSizeScale'", nullptr);
            return 0;
        }
        double ret = cobj->getHitTestCenterSizeScale();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimCard:getHitTestCenterSizeScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_getHitTestCenterSizeScale'.",&tolua_err);
#endif

    return 0;
}
int lua_AnimCard_AnimCard_setAutoTurnOver(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimCard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimCard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AnimCard_AnimCard_setAutoTurnOver'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.AnimCard:setAutoTurnOver");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_setAutoTurnOver'", nullptr);
            return 0;
        }
        cobj->setAutoTurnOver(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimCard:setAutoTurnOver",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_setAutoTurnOver'.",&tolua_err);
#endif

    return 0;
}

static int lua_AnimCard_AnimCard_addActionTweenCallfunc(lua_State* L)
{
	if (nullptr == L)
		return 0;

	int argc = 0;
	AnimCard* self = nullptr;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "cc.AnimCard", 0, &tolua_err)) goto tolua_lerror;
#endif

	self = static_cast<AnimCard*>(tolua_tousertype(L, 1, 0));

#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L, "invalid 'self' in function 'lua_AnimCard_AnimCard_addActionTweenCallfunc'\n", NULL);
		return 0;
	}
#endif

	argc = lua_gettop(L) - 1;

	if (1 == argc)
	{
#if COCOS2D_DEBUG >= 1
		if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err))
		{
			goto tolua_lerror;
		}
#endif

		LUA_FUNCTION handler = (toluafix_ref_function(L, 2, 0));

		self->addActionTweenCallfunc([=](cocos2d::Ref* ref, float value, const std::string& key){
			LuaStack* stack = LuaEngine::getInstance()->getLuaStack();

			stack->pushObject(ref, "cc.Ref");
			stack->pushFloat(value);
			stack->pushString(key.c_str());

			stack->executeFunctionByHandler(handler, 3);
			stack->clean();
		});

		ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
		return 0;
	}

	luaL_error(L, "'addActionTweenCallfunc' function of Widget has wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(L, "#ferror in function 'addActionTweenCallfunc'.", &tolua_err);
	return 0;
#endif
}

int lua_AnimCard_AnimCard_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.AnimCard",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Texture2D* arg0;
        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_create'", nullptr);
            return 0;
        }
        cocos2d::AnimCard* ret = cocos2d::AnimCard::create(arg0);
        object_to_luaval<cocos2d::AnimCard>(tolua_S, "cc.AnimCard",(cocos2d::AnimCard*)ret);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Texture2D* arg0;
        cocos2d::Texture2D* arg1;
        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0);
        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 3, "cc.Texture2D",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AnimCard_AnimCard_create'", nullptr);
            return 0;
        }
        cocos2d::AnimCard* ret = cocos2d::AnimCard::create(arg0, arg1);
        object_to_luaval<cocos2d::AnimCard>(tolua_S, "cc.AnimCard",(cocos2d::AnimCard*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AnimCard:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AnimCard_AnimCard_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_AnimCard_AnimCard_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AnimCard)");
    return 0;
}

int lua_register_AnimCard_AnimCard(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.AnimCard");
    tolua_cclass(tolua_S,"AnimCard","cc.AnimCard","ccui.Widget",nullptr);

    tolua_beginmodule(tolua_S,"AnimCard");
        tolua_function(tolua_S,"getHitTEstEdgeSizeScale",lua_AnimCard_AnimCard_getHitTEstEdgeSizeScale);
        tolua_function(tolua_S,"setAutoFixDistance",lua_AnimCard_AnimCard_setAutoFixDistance);
        tolua_function(tolua_S,"clearTurnPoint",lua_AnimCard_AnimCard_clearTurnPoint);
        tolua_function(tolua_S,"setHitTestCenterSizeScale",lua_AnimCard_AnimCard_setHitTestCenterSizeScale);
        tolua_function(tolua_S,"setNeedDepthTest",lua_AnimCard_AnimCard_setNeedDepthTest);
        tolua_function(tolua_S,"setHitTestEdgeSizeScale",lua_AnimCard_AnimCard_setHitTestEdgeSizeScale);
        tolua_function(tolua_S,"isAutoTurnning",lua_AnimCard_AnimCard_isAutoTurnning);
        tolua_function(tolua_S,"setTurnPoint",lua_AnimCard_AnimCard_setTurnPoint);
        tolua_function(tolua_S,"setRoundRadius",lua_AnimCard_AnimCard_setRoundRadius);
        tolua_function(tolua_S,"setAutoTurnSpeed",lua_AnimCard_AnimCard_setAutoTurnSpeed);
        tolua_function(tolua_S,"getHitTestCenterSizeScale",lua_AnimCard_AnimCard_getHitTestCenterSizeScale);
        tolua_function(tolua_S,"setAutoTurnOver",lua_AnimCard_AnimCard_setAutoTurnOver);
		tolua_function(tolua_S,"addActionTweenCallfunc",lua_AnimCard_AnimCard_addActionTweenCallfunc);
        tolua_function(tolua_S,"create", lua_AnimCard_AnimCard_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::AnimCard).name();
    g_luaType[typeName] = "cc.AnimCard";
    g_typeCast["AnimCard"] = "cc.AnimCard";
    return 1;
}
TOLUA_API int register_all_AnimCard(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_AnimCard_AnimCard(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

