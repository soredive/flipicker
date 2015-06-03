//
//  JniBridge.cpp
//  Flipicker
//
//  Created by BomSok Kim on 2015. 6. 2..
//
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


#include <cocos2d.h>
#include "JniBridge.h"
#include "TypeTextScene.h"

////// for jni start
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#include <stdlib.h>
#include <android/log.h>
#include <string>

#define COCOS2D_DEBUG 1
////// for jni end

using namespace cocos2d;

extern "C" {
    
    
    
    
    
    /////////////////////// FROM ANDROID TO CPP /////////////////////////////
    // functions which is called from adnroid placed in here.
    // function name is pakage name , classs name , method name
    void Java_org_cocos2dx_cpp_AppActivity_callNativeFlipEvent(){
        auto ins = TypeText::RefTypeText;
        ins->TransToPick(1);
    }
    
    
    
    
    
    /////////////////////// FROM CPP TO ANDROID /////////////////////////////
    // functions which is call android method in here.
    void CallToJavaStartSensor(){
        JniMethodInfo t;
        
        if(JniHelper::getStaticMethodInfo(t,
            "org/cocos2dx/cpp/AppActivity",
            "calledByCppStartSensor",
            "()V"
           )){
            t.env->CallStaticVoidMethod(t.classID,t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
        
    }
    void CallToJavaStopSensor(){
        
    }
}



/////////// jin test
//cocos2d::JniMethodInfo methodInfo;
//
//if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "alertJNI", "()V")) {
//    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
//    methodInfo.env->DeleteLocalRef(methodInfo.classID);
//}
/////////// jin test







#endif