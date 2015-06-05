//
//  JniBridge.h
//  Flipicker
//
//  Created by BomSok Kim on 2015. 6. 2..
//
//

#ifndef __Flipicker__JniBridge__
#define __Flipicker__JniBridge__

#include <stdio.h>

extern "C"
{
    void Java_org_cocos2dx_cpp_AppActivity_callNativeFlipEvent();
    
    void CallToJavaStartSensor();
    
    void CallToJavaStopSensor();
}

#endif /* defined(__Flipicker__JniBridge__) */
