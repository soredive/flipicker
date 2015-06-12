//
//  iOSHelper.mm
//

#include "iOSHelper.h"
//--
#import "AppController.h"

void iOSHelper::showAlert()
{
    AppController* appController = (AppController*)[UIApplication sharedApplication].delegate;
    [appController showAlert];
}
