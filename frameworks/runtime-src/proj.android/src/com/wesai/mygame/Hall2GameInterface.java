package com.wesai.mygame;

import android.app.Activity;
import android.util.Log;
import android.widget.Toast;

import com.wesai.games.joint.sdk.WSGameSDKApplication;
import com.wesai.games.joint.sdk.IWSApiGameHallToGamesAdapter;
import com.wesai.games.joint.sdk.IWSApiGamesToGameHall;

public class Hall2GameInterface extends IWSApiGameHallToGamesAdapter {

	Activity instance;
	static IWSApiGamesToGameHall boImpl;
	public static String pushStr;
    public static String locationStr;

	@Override
	public boolean isCloseActivity(Activity arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	public static IWSApiGamesToGameHall getBo() {
		return boImpl;
	}

	@Override
	public void onCreateStartGame(Activity activity, IWSApiGamesToGameHall bo)
			throws Exception {
		// TODO Auto-generated method stub
		instance = activity;
		boImpl = bo;
		System.load(WSGameSDKApplication.getGameApplicationInstance()
				.getGameSoFilePath(bo.doQueryGameId(), "libcocos2dlua.so"));
		Toast.makeText(instance, "userId = " + bo.doQueryWesaiUid(),
				Toast.LENGTH_SHORT).show();
	}

	@Override
	public boolean sendMsgToGame(int type, int resultType, String msg,
			String dataJson) {
		// TODO Auto-generated method stub
		String data = "Event:" + type + ",result:" + resultType + ",msg:" + msg
				+ ",jsonData:" + dataJson;
		String event = "";
		if (type == 20103) {
			event = "HallPushUserInfo";
		} else if (type == 20107) {
			event = "HallPushPayResult";
		}
		Log.d("MyGame", "sendMsgToGame: "+ data);
		Utils.postMsg2Cocos(event, data);
		return false;
	}
 
	@Override
	public void onGameDestroy(Activity arg0) throws Exception {
		// TODO Auto-generated method stub
	}

	@Override
	public void onGamePause(Activity arg0) throws Exception {
		// TODO Auto-generated method stub

	}

	@Override
	public void onGameResume(Activity arg0) throws Exception {
		// TODO Auto-generated method stub

	}

	@Override
	public void onGameStart(Activity arg0) throws Exception {
		// TODO Auto-generated method stub

	}

	@Override
	public void onGameStop(Activity arg0) throws Exception {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean quitGame(Activity arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
    public boolean isOpenLocation(Activity mActivity) {
        return true;
    }

	@Override
    public void onLocationChanged(String jsonData) {
        locationStr = jsonData;
        Log.d("MyGame", "onLocationChanged: "+jsonData);
        Utils.postMsg2Cocos("HallPushLocationChanged", jsonData);
    }

    @Override
    public void onPushMsg(String jsonData) {
        super.onPushMsg(jsonData);
        pushStr = jsonData;
        Log.d("MyGame", "onPushMsg: "+jsonData);
        Utils.postMsg2Cocos("HallPushNotification", jsonData);
    }
}
