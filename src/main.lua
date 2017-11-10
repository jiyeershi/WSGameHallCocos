
cc.FileUtils:getInstance():setPopupNotify(false)
CC_DISABLE_GLOBAL = false
require "config"
require "cocos.init"
-- local luaoc = require "cocos.cocos2d.luaoc"
local TestScene = require "TestScene"


print('-----gameid----rr2');
print('-----gameid----rr2');
print('-----gameid----rr2');

USERID = ""
GAMEID = ""

local function LGfunc()  
    print("callBack succeed")  
end
local function main()
print('-----gameid----rr2');
print('-----gameid----rr2');
print('-----gameid----rr2');
local size = cc.Director:getInstance():getWinSize();
  
     print('---111--size',size.height);

	local testScene = TestScene:create()
    cc.Director:getInstance():runWithScene(testScene)
    -- require("app.MyApp"):create():run()
 --    local arg1 = {callBack = LGfunc}  
	-- local arg2 = {types = 1,maxCount = 4,original = 1}  
	-- local result, version = luaoc.callStaticMethod("WSOCInteractionLua", "getUserInfo", arg1)
	-- print("============================")
	-- print(result,version)
	-- print("============================")

	-- local result, version = luaoc.callStaticMethod("WSOCInteractionLua", "getWeSaiUid")

	print("============================")
	print(result,version)
	print("============================")
end

function OC2LuaUserId(uid, gameId)
	print("uid = ", uid)
	print("gameId = ", gameId)
	USERID = uid
	GAMEID = gameId
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
