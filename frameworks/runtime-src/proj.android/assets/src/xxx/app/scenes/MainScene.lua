
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()

    audio.playMusic("sound/background.mp3", true)

    display.newSprite("image/main.jpg")
        :setPosition(display.cx, display.cy)
        :addTo(self)
    
    local title = display.newSprite("image/title.png")
        :setPosition(display.cx / 2 * 3, display.cy)
        :addTo(self)

    local sequence = transition.sequence({
        cc.MoveTo:create(0.5, cc.p(display.cx, display.cy)),
        cc.FadeOut:create(0.2),
        cc.DelayTime:create(0.5),
        cc.FadeIn:create(0.3),
    })

    local start = ccui.Button:create("image/start1.png", "image/start2.png")
    start:setPosition( display.cx / 2, display.cy )
    start:addTo(self)
    start:addClickEventListener(function()
            print("start")
            audio.playSound("sound/button.wav")
            -- app:enterScene()
            local scene = require("app.scenes.GameScene"):create()
            display.runScene(scene, nil, "SLIDEINT", 1.0)
        end)

    local move1 = cc.MoveBy:create(0.5, cc.p(0, 10))
    local move2 = cc.MoveBy:create(0.5, cc.p(0, -10))
    local SequenceAction = cc.Sequence:create( move1, move2 )
    transition.execute(start, cc.RepeatForever:create( SequenceAction ))
end

function MainScene:onEnter()
end

function MainScene:onExit()
end

return MainScene
