
cc.FileUtils:getInstance():setPopupNotify(false)

require "config"
require "cocos.init"

local TestScene = require "app.scenes.MainScene"

local function main()
    -- require("app.MyApp"):create():run()
    cc.FileUtils:getInstance():addSearchPath("res/")
	-- cc.Director:getInstance():setContentScaleFactor(640 / 320)

	display.loadSpriteFrames("image/player.plist", "image/player.pvr.ccz")
	audio.preloadMusic("sound/background.mp3") 
	audio.preloadSound("sound/button.wav")
	audio.preloadSound("sound/ground.mp3")
	audio.preloadSound("sound/heart.mp3")
	audio.preloadSound("sound/hit.mp3")

    local testScene = TestScene:create()
    cc.Director:getInstance():runWithScene(testScene)
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
