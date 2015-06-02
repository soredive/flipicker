/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

// for gyro sensor
import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorListener;
import android.hardware.SensorManager;
import android.app.AlertDialog;
import android.os.Bundle;
import android.util.Log;
// for gyro sensor

public class AppActivity extends Cocos2dxActivity implements SensorEventListener {
    public static Activity _activiy;

    public static AppActivity cocos_activity;

    // gyro sensor things
    private SensorManager sensorManager = null;
    private Sensor orientationSensor = null;
    private Sensor accelermeterSensor = null;
    // gyro sensor things

    // check is fliped
    private boolean is_phone_flipped;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //Save activity instance
        _activiy = this;
        cocos_activity = this;

        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);

        accelermeterSensor = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        orientationSensor = sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION);
        // DEPRECATED
        //SensorManager.getOrientation();
    }

    @Override
    protected void onStart(){
        super.onStart();

        startFlipSensor();

        // test
        callNativeCPPCall();
        //test
    }

    @Override
    public void onSensorChanged(SensorEvent event){
        synchronized (this){
            Log.d("Sensor", "onSensorChanged: " + event.sensor.getType()
                    + ", x: " + event.values[0] + ", y: " + event.values[1] + ", z: " + event.values[2]);
            if(event.sensor.getType() == Sensor.TYPE_ACCELEROMETER){
                Log.d("Accel x: ", " "+event.values[0] + ", y: " + event.values[1] + ", z: " + event.values[2]);
            }else if(event.sensor.getType() == Sensor.TYPE_ORIENTATION){
                Log.d("Orientation x: ", " "+event.values[0] + ", y: " + event.values[1] + ", z: " + event.values[2]);
                /**
                 * float headingAngle = values[0];
                 float pitchAngle = values[1];
                 float rollAngle = values[2];
                 */
            }
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy){

    }

    @Override
    protected void onStop(){
        endFlipSensor();

        super.onStop();
    }

    @Override
    protected void onDestroy(){
        endFlipSensor();

        super.onDestroy();
    }

    public void startFlipSensor(){
        is_phone_flipped = false;

        // init sensor
        if(accelermeterSensor != null){
            sensorManager.registerListener(this, accelermeterSensor, SensorManager.SENSOR_DELAY_NORMAL);
        }
        if(orientationSensor != null){
            sensorManager.registerListener(this, orientationSensor, SensorManager.SENSOR_DELAY_NORMAL);
        }
    }

    public void endFlipSensor(){
        if(accelermeterSensor != null || orientationSensor != null){
            sensorManager.unregisterListener(this);
        }
    }

    public static void calledByCppStartSensor(){
        cocos_activity.startFlipSensor();

        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
        Log.d("*******************", "start sensor");
    }

    public static void calledByCppStopSensor(){
        cocos_activity.endFlipSensor();
    }

    public void callNativeCPPCall(){
        String a = "Yes, It's pure Java!";

        callNativeFlipEvent();
    }

    public static native void callNativeFlipEvent();


    public static void alertJNI() {
        String tag = "JniTest";
        String message = "I've been called from C++";
        Log.d(tag, "Showing alert dialog: " + message);
    }
}