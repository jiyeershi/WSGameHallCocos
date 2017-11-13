
local TestScene = class("TestScene", cc.Scene)
local luaoc = require "cocos.cocos2d.luaoc"
local json = require "cocos.cocos2d.json"

local apiArr = {
	"http://game.test.api.wesai.com/intra/virtualMedal",
	"http://game-pre.api.wesai.com/intra/virtualMedal",
	"http://game.api.wesai.com/intra/virtualMedal",
}

function TestScene:ctor( ... )
	-- self.super:ctor()
	-- local OC2LuaCallBack = function (eventType, result, msg, jsonData)

    local labEvent = nil
    local labApi = nil
	local OC2LuaCallBack = function (jsonData)
		print(jsonData)
		labEvent:setString(jsonData)
	end

	 local function onMenuPostClicked()
        local xhr = cc.XMLHttpRequest:new()
        xhr.responseType = cc.XMLHTTPREQUEST_RESPONSE_STRING
        xhr:open("POST", apiArr[apiIndex])
        print("onMenuPostClicked apiArr[apiIndex]", apiArr[apiIndex])
        -- xhr:open("POST", "http://game-pre.api.wesai.com/intra/virtualMedal")
        -- xhr:open("POST", "http://game.api.wesai.com/intra/virtualMedal")
        local function onReadyStateChanged()
            if xhr.readyState == 4 and (xhr.status >= 200 and xhr.status < 207) then
                if not tolua.isnull(labelStatusCode) then
                    labelStatusCode:setString("Http Status Code:" .. xhr.statusText)
                else
                    print("ERROR: labelStatusCode is invalid!")
                end
                print(xhr.response)
                labEvent:setString(xhr.response)
            else
                print("xhr.readyState is:", xhr.readyState, "xhr.status is: ",xhr.status)
            end
            xhr:unregisterScriptHandler()
        end
		xhr:registerScriptHandler(onReadyStateChanged)
        local result, uId = luaoc.callStaticMethod("WSGameCenterInterface", "getWesaiUid")
        local result1, gameId = luaoc.callStaticMethod("WSGameCenterInterface", "getGameId")
        local sendData = string.format("user_id=%s&game_id=%s&medal_value=1", uId, gameId)
        print("sendData ", sendData)
        xhr:send(sendData)
        print("waiting...")
    end

	local onClickAchivement = function ( ... )
		print("==============onClickAchivement==============")
		-- local arg = {callBack = OC2LuaCallBack,iconUrl = "http://images2015.cnblogs.com/blog/784420/201602/784420-20160217161627003-1456997293.png"}  
		-- local result, version = luaoc.callStaticMethod("WSGameCenterInterface", "doShareImage", arg)
		onMenuPostClicked()
	end

	local onClickCharge = function ( ... )
		print("==============onClickCharge==============")
		local arg = {callBack = OC2LuaCallBack}  
		local result, version = luaoc.callStaticMethod("WSGameCenterInterface", "doPay", arg)
	end

	local onClickUserInfo = function ( ... )
		print("==============onClickUserInfo==============")
		local arg = {callBack = OC2LuaCallBack}  
		local result, value = luaoc.callStaticMethod("WSGameCenterInterface", "doQueryUserInfo", arg)
		print(result, value)
		labEvent:setString(value)
	end

	local onClickGetPushMsg = function ( ... )
		print("==============onClickGetPushMsg==============")
		local arg = {callBack = OC2LuaCallBack}  
		local result, value = luaoc.callStaticMethod("WSGameCenterInterface", "getPushInfo", arg)
		print(result, value)
		labEvent:setString(value)
	end

	local onClickGetLocationStr = function ( ... )
		print("==============onClickGetLocationStr==============")
		local arg = {callBack = OC2LuaCallBack}
		local result, value = luaoc.callStaticMethod("WSGameCenterInterface", "getLocationInfo", arg)
		print(result, value)
		labEvent:setString(value)
	end

	local onClickShare = function ( ... )
		print("==============onClickShare==============")
		local arg = {callBack = OC2LuaCallBack,
			title = "cocos-lua游戏 分享测试",
			content = "这是一条cocos-lua游戏 分享测试",
			iconUrl = "https://static.wesai.com/ticketv2-product_static/pc/img/v2/logov2.png?v=819c55576907f5d888b19dce8b33326d", 
			url = "https://www.wesai.com/",
		}  
		local result, value = luaoc.callStaticMethod("WSGameCenterInterface", "doShareImage", arg)
		print(result, value)
		labEvent:setString(value)
	end

	local onClickEnd = function ( ... )
		print("==============onClickEnd==============")
		local result, value = luaoc.callStaticMethod("WSGameCenterInterface", "stopGame")
		print(result, value)
	end 

	local size = cc.Director:getInstance():getWinSize()
	local lab2 = cc.LabelTTF:create("lua游戏", "fonts/arial.ttf", 30, cc.size(0,0), 0);
	lab2:setPosition(cc.p(0, size.height - 100))
	lab2:setAnchorPoint(cc.p(0,0.5))
	-- self:addChild(lab2)

    local root = cc.CSLoader:createNode("MainScene.csb")
    self:addChild(root)

    labApi = root:getChildByName("lab_api");
    labEvent = root:getChildByName("lab_event");
    local btn_changeApi = root:getChildByName("btn_changeApi")
    btn_changeApi:addTouchEventListener(function (pSender, event)
    	if event == 2 then
	    	apiIndex = (apiIndex+1) % 3
	    	labApi:setString(apiArr[apiIndex])
	    	print("click changeApi ...")
	    end
    end)

    local btn_charge = root:getChildByName("btn_charge")
    btn_charge:addTouchEventListener(function (pSender, event)
    	if event == 2 then
    		onClickCharge()
    		print("click charge ...")
    	end
    end)

    local btn_quary = root:getChildByName("btn_quary")
    btn_quary:addTouchEventListener(function (pSender, event)
    	if event == 2 then
    		onClickUserInfo()
    		print("click quary user info ...")
    	end
    end)

    local btn_addAchivement = root:getChildByName("btn_addAchivement")
    btn_addAchivement:addTouchEventListener(function (pSender, event)
    	if event == 2 then
    		onClickAchivement()
    		print("click  add Achivement user info ...")
    	end
    end)

    local btn_share = root:getChildByName("btn_share")
    btn_share:addTouchEventListener(function (pSender, event)
    	if event == 2 then
    		onClickShare()
    		print("click share ...")
    	end
    end)

    local btn_getLocation = root:getChildByName("btn_getLocation")
    btn_getLocation:addTouchEventListener(function (pSender, event)
    	if event == 2 then
    		onClickGetLocationStr()
    		print("click GetLocationStr ...")
    	end
    end)

    local btn_push = root:getChildByName("btn_push")
    btn_push:addTouchEventListener(function (pSender, event)
    	if event == 2 then
    		onClickGetPushMsg()
    		print("click GetPushMsg ...")
    	end
    end)

    local btn_quit = root:getChildByName("btn_quit")
    btn_quit:addTouchEventListener(function (pSender, event)
    	if event == 2 then
    		print("click end Game ...")
    		onClickEnd()
    	end
    end)

end

return TestScene