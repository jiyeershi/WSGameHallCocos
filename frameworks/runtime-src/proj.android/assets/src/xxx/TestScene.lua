
local TestScene = class("TestScene", cc.Scene)
local json = require "cocos.cocos2d.json"

function TestScene:ctor( ... )
	-- self.super:ctor()
	local T_USERINFO = 10
	local T_CHARGE = 11
	local T_ACHIVEMENT = 12
	local T_END = 13


	local labUserInfo = ccui.Text:create("UserInfo", "fonts/arial.ttf", 60)
	self:addChild(labUserInfo)
	labUserInfo:setPosition(cc.p(50, 100))
	labUserInfo:setTouchEnabled(true)
	labUserInfo:setTag(T_USERINFO)
	labUserInfo:setAnchorPoint(cc.p(0, 0))
	print(display.width)
	print(display.height)

	if device.platform ~= "ios" then return end

	local OC2LuaCallBack = function (eventType, result, msg, jsonData)
		print(eventType, result, msg, jsonData)
	end

	local function onMenuPostClicked()
        local xhr = cc.XMLHttpRequest:new()
        xhr.responseType = cc.XMLHTTPREQUEST_RESPONSE_STRING
        xhr:open("POST", "http://game.test.api.wesai.com/intra/virtualMedal")
        local function onReadyStateChanged()
            if xhr.readyState == 4 and (xhr.status >= 200 and xhr.status < 207) then
                if not tolua.isnull(labelStatusCode) then
                    labelStatusCode:setString("Http Status Code:" .. xhr.statusText)
                else
                    print("ERROR: labelStatusCode is invalid!")
                end
                print(xhr.response)
            else
                print("xhr.readyState is:", xhr.readyState, "xhr.status is: ",xhr.status)
            end
            xhr:unregisterScriptHandler()
        end
        xhr:registerScriptHandler(onReadyStateChanged)
        local result, uId = luaoc.callStaticMethod("WSOCInteractionLua", "getWesaiUid")
        local result1, gameId = luaoc.callStaticMethod("WSOCInteractionLua", "getGameId")
        local sendData = string.format("user_id=%s&game_id=%s&medal_value=1", uId, gameId)
        print("sendData ", sendData)
        xhr:send(sendData)
        print("waiting...")
    end

	local onClickAchivement = function ( ... )
		print("==============onClickAchivement==============")
		onMenuPostClicked()
	end

	local onClickCharge = function ( ... )
		print("==============onClickCharge==============")
		local arg = {callBack = OC2LuaCallBack}  
		local result, version = luaoc.callStaticMethod("WSOCInteractionLua", "doPay", arg)
	end

	local onClickUserInfo = function ( ... )
		print("==============onClickUserInfo==============")
		local arg = {callBack = OC2LuaCallBack}  
		local result, value = luaoc.callStaticMethod("WSOCInteractionLua", "doQueryUserInfo", arg)
		print(result, value)
	end

	local onClickEnd = function ( ... )
		print("==============onClickEnd==============")
		local result, value = luaoc.callStaticMethod("WSOCInteractionLua", "stopGame")
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

	-- local labUserInfo = ccui.Text:create("UserInfo", "fonts/arial.ttf", 60)
	local labUserInfo = ccui.Button:create("userinfo.png.png", "userinfo.png.png")
	self:addChild(labUserInfo)
	labUserInfo:setPosition(cc.p(50, 100))
	labUserInfo:setTouchEnabled(true)
	labUserInfo:setTag(T_USERINFO)
	labUserInfo:addTouchEventListener(onlick)
	labUserInfo:setAnchorPoint(cc.p(0, 0))

	local labCharge = ccui.Text:create("Charge", "fonts/arial.ttf", 60)
	self:addChild(labCharge)
	labCharge:setPosition(cc.p(50, 220))
	labCharge:setTouchEnabled(true)
	labCharge:setTag(T_CHARGE)
	labCharge:addTouchEventListener(onlick)
	labCharge:setAnchorPoint(cc.p(0, 0))

	local labAddAchivementReq = ccui.Text:create("AddAchivementReq", "fonts/arial.ttf", 60)
	self:addChild(labAddAchivementReq)
	labAddAchivementReq:setPosition(cc.p(50, 320))
	labAddAchivementReq:setTouchEnabled(true)
	labAddAchivementReq:setTag(T_ACHIVEMENT)
	labAddAchivementReq:addTouchEventListener(onlick)
	labAddAchivementReq:setAnchorPoint(cc.p(0, 0))

	local labEnd = ccui.Text:create("end", "fonts/arial.ttf", 60)
	self:addChild(labEnd)
	labEnd:setPosition(cc.p(50, 420))
	labEnd:setTouchEnabled(true)
	labEnd:setTag(T_END)
	labEnd:addTouchEventListener(onlick)
	labEnd:setAnchorPoint(cc.p(0, 0))
end

return TestScene