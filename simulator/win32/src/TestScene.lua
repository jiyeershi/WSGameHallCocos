
local TestScene = class("TestScene", cc.Scene)
local luaoc --= require "cocos.cocos2d.luaoc"
local json = require "cocos.cocos2d.json"

local apiArr = {
	"http://game.test.api.wesai.com/intra/virtualMedal",
	"http://game-pre.api.wesai.com/intra/virtualMedal",
	"http://game.api.wesai.com/intra/virtualMedal",
}

function TestScene:ctor( ... )
	-- self.super:ctor()
	local T_USERINFO = 10
	local T_CHARGE = 11
	local T_ACHIVEMENT = 12
	local T_END = 13

	local labEvent = nil
	local apiIndex = 1

	-- local OC2LuaCallBack = function (eventType, result, msg, jsonData)
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
		local result, value = luaoc.callStaticMethod("WSGameCenterInterface", "getLocationStr", arg)
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

	local onlick = function ( pSender, event )
		local tag = pSender:getTag()
		print("event = ", event)
		if event == 0 then 
			pSender:setScale(0.8)
		else
			pSender:setScale(1.0)
		print("touch tag = ", tag)
		if tag == T_USERINFO then
			onClickUserInfo()
		elseif tag == T_CHARGE then
			onClickCharge()
		elseif tag == T_ACHIVEMENT then
			onClickAchivement()
		elseif tag == T_END then
			onClickEnd()
		end
	end
end
     






	local size = cc.Director:getInstance():getWinSize()
	local lab2 = cc.LabelTTF:create("lua游戏", "fonts/arial.ttf", 30, cc.size(0,0), 0);
	lab2:setPosition(cc.p(280, size.height - 100))
	lab2:setAnchorPoint(cc.p(0,0.5))
	self:addChild(lab2)

    local root = cc.CSLoader:createNode("MainScene.csb")
    self:addChild(root)

    local labApi = root:getChildByName("lab_api");
    local labEvent = root:getChildByName("lab_event");
    local btn_changeApi = root:getChildByName("btn_changeApi")
    btn_changeApi:addTouchEventListener(function (pSender, event)
    	apiIndex = (apiIndex+1) % 3
    	labApi:setString(apiArr[apiIndex])
    	print("click event = ", event)
    end)

    local btn_charge = root:getChildByName("btn_charge")
    btn_charge:addTouchEventListener(function (pSender, event)
    	onClickCharge()
    end)

    local btn_quary = root:getChildByName("btn_quary")
    btn_quary:addTouchEventListener(function (pSender, event)
    	onClickUserInfo()
    end)

    local btn_addAchivement = root:getChildByName("btn_addAchivement")
    btn_addAchivement:addTouchEventListener(function (pSender, event)
    	onClickAchivement()
    end)

    local btn_share = root:getChildByName("btn_share")
    btn_share:addTouchEventListener(function (pSender, event)
    	onClickShare()
    end)

    local btn_getLocation = root:getChildByName("btn_getLocation")
    btn_getLocation:addTouchEventListener(function (pSender, event)
    	onClickGetLocationStr()
    end)

    local btn_push = root:getChildByName("btn_push")
    btn_push:addTouchEventListener(function (pSender, event)
    	onClickGetPushMsg()
    end)

    local btn_quit = root:getChildByName("btn_quit")
    btn_quit:addTouchEventListener(function (pSender, event)
    	onClickEnd()
    end)

end

return TestScene