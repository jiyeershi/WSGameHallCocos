package com.wesai.mygame;

import android.util.*;
import com.wesai.mygame.Hall2GameInterface;
import com.wesai.games.joint.sdk.PayEntity;

public class Utils {
	public static native void postMsg2Cocos(String key,String value);
    
    public static void doQueryUserInfo() {
        Log.d("MyGame", "doQueryUserInfo ");
        Hall2GameInterface.getBo().doQueryUserInfo();
    }

    public static void doPay(String orderId, String cost, String description, String extralContent) {
        Log.d("MyGame", "doPay");
        Log.d("MyGame", "orderId: "+orderId+" cost: "+cost+" description: "+description+" extralContent: "+extralContent);
        PayEntity pay = new PayEntity();
        pay.setOrder_id(orderId);
        pay.setAmount(cost);
        pay.setDescription(description);
        pay.setExtra_content(extralContent);
        Hall2GameInterface.getBo().doPay(pay);
    }

    public static String doQueryWesaiUid(){
        Log.d("MyGame", "doQueryWesaiUid");
        return Hall2GameInterface.getBo().doQueryWesaiUid();
        // return "doQueryWesaiUid ok";
    }

    public static String doQueryGameId(){
        Log.d("MyGame", "doQueryGameId");
        return Hall2GameInterface.getBo().doQueryGameId();
        // return "doQueryGameId";
    }

    public  static void doShareRichText(String title, String content, String iconUrl, String h5Url){
        Log.d("MyGame", "doShareRichText" + "title = "+ title + "content = "+ content + "iconUrl = "+ iconUrl + " h5Url = " + h5Url);
        Hall2GameInterface.getBo().doShareRichText(title, content, iconUrl, h5Url);
    }

    public static String getLocationStr() {
        Log.d("MyGame", "getLocationStr");
        return Hall2GameInterface.locationStr;
        // return "Hall2GameInterface.locationStr";
    }

    public static String getPushStr() {
        Log.d("MyGame", "getPushStr");
        return Hall2GameInterface.pushStr;
        // return "Hall2GameInterface.pushStr";
    }
}