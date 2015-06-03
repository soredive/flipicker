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
    private Sensor gyroSensor = null;
    private Sensor rotationVectorSensor = null;
    // gyro sensor things


    //////////////// gyro sensor things ////////////////
    // was sensor on
    private boolean is_sensor_on;

    // check is fliped
    private boolean is_phone_flipped;

    // first state when start flipping
    private float[] first_saving = new float[3];
    private float[] first_saving_min = new float[3];
    private float[] first_saving_max = new float[3];
    private boolean is_first_check;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //Save activity instance
        _activiy = this;
        cocos_activity = this;
        is_first_check = true;
        //

        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);

        rotationVectorSensor = sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);
        gyroSensor = sensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
        //SensorManager.getOrientation();
    }

    @Override
    protected void onStart(){
        super.onStart();
    }

    @Override
    public void onSensorChanged(SensorEvent event){
        synchronized (this){
//            Log.d("Sensor", "onSensorChanged: " + event.sensor.getType() + ", x: " + event.values[0] + ", y: " + event.values[1] + ", z: " + event.values[2]);
//            if(event.sensor.getType() == Sensor.TYPE_GYROSCOPE){
//                Log.d("Gyro x: ", " "+event.values[0] + ", y: " + event.values[1] + ", z: " + event.values[2]);
//            }else
            if(event.sensor.getType() == Sensor.TYPE_ROTATION_VECTOR){
                if(is_first_check){
                    is_first_check = false;

                    float no1, no2, max, min;
                    for(int i = 0; i < 3; i++){
                        first_saving[i] = event.values[i];
                        no1 = first_saving[i] - 0.5f;
                        no2 = first_saving[i] + 0.5f;
                        if(no1>=1) no1 -= 1;
                        if(no1<=-1) no1 += 1;
                        if(no2>=1) no2 -= 1;
                        if(no2<=-1) no2 += 1;

                        if(no1>no2){
                            max = no1;
                            min = no2;
                        }else{
                            max = no2;
                            min = no1;
                        }
                        first_saving_max[i] = max;
                        first_saving_min[i] = min;
                    }
                }else{
                    boolean ok = false;
                    for(int i = 0; i < 2; i++){
                        if(event.values[i] <= first_saving_min[i] || event.values[i] >= first_saving_max[i]){
                            ok = true;
                        }
                    }
                    if(ok == true){
                        // ok flipped
                        callNativeCPPCall();
                    }
                }
                Log.d("Rotation x: ", " "+event.values[0] + ", y: " + event.values[1] + ", z: " + event.values[2]);
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



    // called from cpp to android to start sensor
    public static void calledByCppStartSensor(){
        cocos_activity.startFlipSensor();
    }
    public void startFlipSensor(){
        is_sensor_on = true;
        is_phone_flipped = false;
        // init sensor
        if(gyroSensor != null){
            sensorManager.registerListener(this, gyroSensor, SensorManager.SENSOR_DELAY_NORMAL);
        }
        if(rotationVectorSensor != null){
            sensorManager.registerListener(this, rotationVectorSensor, SensorManager.SENSOR_DELAY_NORMAL);
        }
    }




    // called from cpp to Android to stop sensor
    public static void calledByCppStopSensor(){
        cocos_activity.endFlipSensor();
    }
    public void endFlipSensor(){
        if(gyroSensor != null || rotationVectorSensor != null){
            sensorManager.unregisterListener(this);
        }
    }




    // call cpp from Android to go flip end scene!
    public void callNativeCPPCall(){
        callNativeFlipEvent();
        endFlipSensor();
    }
    public static native void callNativeFlipEvent();




    public static void alertJNI() {
        String tag = "JniTest";
        String message = "I've been called from C++";
        Log.d(tag, "Showing alert dialog: " + message);
    }
}