package com.pebble_test;

import java.util.UUID;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Menu;
import android.widget.Toast;

import com.getpebble.android.kit.PebbleKit;
import com.getpebble.android.kit.util.PebbleDictionary;



public class MainActivity extends Activity {

	private final static UUID PEBBLE_APP_UUID = UUID.fromString("88c99af8-9512-4e23-b79e-ba437c788446");
	private PebbleKit.PebbleDataReceiver dataReceiver;
	private Handler mHandler;
	
	private final static int CMD_KEY = 0x00;
    private final static int CMD_SELECT = 0x00;
    private final static int CMD_UP = 0x01;
    private final static int CMD_DOWN = 0x02;
    private final static int CMD_MULTI_SELECT = 0x03;
    
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		mHandler = new Handler();
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	
	@Override
	protected void onResume()
	{
		super.onResume();
		
		dataReceiver = new PebbleKit.PebbleDataReceiver(PEBBLE_APP_UUID) {
            @Override
            public void receiveData(final Context context, final int transactionId, final PebbleDictionary data) {
                final int cmd = data.getUnsignedInteger(CMD_KEY).intValue();
            	//Log.i(getLocalClassName(), "Received value=" + data.getString(0xabbababe) + " for key: 0");
            	
            	
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        // All data received from the Pebble must be ACK'd, otherwise you'll hit time-outs in the
                        // watch-app which will cause the watch to feel "laggy" during periods of frequent
                        // communication.
                        PebbleKit.sendAckToPebble(context, transactionId);
                        Toast toast;
                        switch (cmd) {
                            // send SMS when the up button is pressed
                            case CMD_UP:
                            	Log.v(getLocalClassName(), "UP");
                            	toast = Toast.makeText(context, "UP", Toast.LENGTH_SHORT);
                            	toast.show();
                                break;
                            case CMD_DOWN:
                            	Log.v(getLocalClassName(), "DOWN");
                            	toast = Toast.makeText(context, "DOWN", Toast.LENGTH_SHORT);
                            	toast.show();
                            	break;
                            case CMD_SELECT:
                            	Log.v(getLocalClassName(), "SELECT");
                            	toast = Toast.makeText(context, "SELECT", Toast.LENGTH_SHORT);
                            	toast.show();
                            	break;
                            case CMD_MULTI_SELECT:
                            	Log.v(getLocalClassName(), "MULTISELECT");
                            	toast = Toast.makeText(context, "MULTISELECT", Toast.LENGTH_SHORT);
                            	toast.show();
                            	break;
                            default:
                                break;
                        }
                        
                    }
                    
                });
                
            }
        };
        PebbleKit.registerReceivedDataHandler(this, dataReceiver);
		
	}

	
}
