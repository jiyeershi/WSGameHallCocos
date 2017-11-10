
local TestScene = class("TestScene", cc.Scene)
local luaoc = require "cocos.cocos2d.luaoc"

GameInfo = {}
GameInfo.uId = ""
GameInfo.gameId = ""

function TestScene:ctor( ... )
	local T_USERINFO = 10
	local T_CHARGE = 11
	local T_ACHIVEMENT = 12
	local T_END = 13

	local onClickAchivement = function ( ... )
		print("onClickAchivement")
	end

	local onClickCharge = function ( ... )
		print("onClickCharge")
		local payCallBack = function ( result )
			print(result)
		end
		local arg = {callBack = payCallBack}  
		local result, version = luaoc.callStaticMethod("WSOCInteractionLua", "doPay", arg)
	end

	local onClickUserInfo = function ( ... )
		print("onClickUserInfo")
		local getUserInfoCallBack = function ( userInfo )
			print(userInfo)
		end
		local arg = {uid = USERID, callBack = getUserInfoCallBack}  
		local result, value = luaoc.callStaticMethod("WSOCInteractionLua", "getUserInfo", arg)
		print(result, value)
	end

	local onClickEnd = function ( ... )
		print("onClickEnd")
	end

	local onlick = function ( pSender, event )
		local tag = pSender:getTag()
		print("event = ", event)
		if event == 0 then 
			pSender:setScale(0.8)
		else
			pSender:setScale(1.0)
		end
		print("touch tag = ", tag)
		if tag == T_USERINFO then
			onClickUserInfo()
		elseif tag == T_CHARGE then
			onClickCharge()
		elseif tag == T_ACHIVEMENT then
			onClickAchivement()
		elseif tag == 12 then
			onClickEnd()
		end
	end

	local labUserInfo = ccui.Text:create("UserInfo", "fonts/arial.ttf", 40)
	self:addChild(labUserInfo)
	labUserInfo:setPosition(cc.p(0, 220))
	labUserInfo:setTouchEnabled(true)
	labUserInfo:setTag(T_USERINFO)
	labUserInfo:addTouchEventListener(onlick)
	labUserInfo:setAnchorPoint(cc.p(0, 0))

	local labCharge = ccui.Text:create("Charge", "fonts/arial.ttf", 40)
	self:addChild(labCharge)
	labCharge:setPosition(cc.p(0, 320))
	labCharge:setTouchEnabled(true)
	labCharge:setTag(T_CHARGE)
	labCharge:addTouchEventListener(onlick)
	labCharge:setAnchorPoint(cc.p(0, 0))

	local labAddAchivementReq = ccui.Text:create("AddAchivementReq", "fonts/arial.ttf", 40)
	self:addChild(labAddAchivementReq)
	labAddAchivementReq:setPosition(cc.p(0, 420))
	labAddAchivementReq:setTouchEnabled(true)
	labAddAchivementReq:setTag(T_ACHIVEMENT)
	labAddAchivementReq:addTouchEventListener(onlick)
	labAddAchivementReq:setAnchorPoint(cc.p(0, 0))

	local labEnd = ccui.Text:create("end", "fonts/arial.ttf", 40)
	self:addChild(labEnd)
	labEnd:setPosition(cc.p(0, 520))
	labEnd:setTouchEnabled(true)
	labEnd:setTag(T_END)
	labEnd:addTouchEventListener(onlick)
	labEnd:setAnchorPoint(cc.p(0, 0))
end

return TestScene