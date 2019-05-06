package com.example.rundbc;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity  {
    private static final String TAG = "MainActivity";
    private static final int REQUEST_ENABLE_BT = 1;
    public static final String EXTRA_MESSAGE = "com.example.rundbc.MESSAGE";

    BluetoothAdapter mBluetoothAdapter;
    TextView BluetoothStatus;
    ImageView BTIstatus;
    Button discoverdevices;

    BluetoothDevice mydevice;

    // Create a BroadcastReceiver for ACTION_FOUND
    private final BroadcastReceiver mBroadcastReceiver1 = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            //when discovery finds a device
            if (action.equals(mBluetoothAdapter.ACTION_STATE_CHANGED)){
                final int state = intent.getIntExtra(BluetoothAdapter.EXTRA_STATE,mBluetoothAdapter.ERROR);
                switch(state){
                    case BluetoothAdapter.STATE_OFF: //State off = 10
                        Log.d(TAG, "OnReceive: STATE OFF");
                        break;
                    case BluetoothAdapter.STATE_TURNING_OFF: //State turning off = 13
                        Log.d(TAG,"mBroadcastReceiver1: STATE TURNING OFF");
                        break;
                    case BluetoothAdapter.STATE_ON: //State ON = 12
                        Log.d(TAG,"MBroadcastReceiver1: STATE ON");
                        break;
                    case BluetoothAdapter.STATE_TURNING_ON: //State on = 11
                        Log.d(TAG,"MBroadcastReceiver1: STATE ON");
                        break;
                }
            }
        }
    };

    //BroadcastReceiver3
    private final BroadcastReceiver mBroadcastReceiver3 = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            Log.d(TAG, "OnReceive: Action_Found");

            if (action.equals(BluetoothDevice.ACTION_FOUND)) {
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);

                Log.d(TAG, "onReceiver:" + device.getName() + " : " + device.getAddress());
                if(device.getName()!= null) {
                    if (device.getName().equals("HC-05")) {
                        showToast("Connecting...");
                        mydevice = device;
                        searchnconnect();
                    }
                }

            }
        }

    };

        @Override
        protected void onDestroy() {
            Log.d(TAG, "OnDestroy: Called");
            super.onDestroy();
            unregisterReceiver(mBroadcastReceiver1);
            unregisterReceiver(mBroadcastReceiver3);
        }


        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_main);

            Button monoffBtn = findViewById(R.id.onoffBtn);
            BluetoothStatus = findViewById(R.id.BluetoothStatusTV);
            BTIstatus = findViewById(R.id.BluetoothIv);
            discoverdevices = findViewById(R.id.FindunpairedDevices);
            discoverdevices.setEnabled(false);

            mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

            checkBTStatus();
            checkOnOffstatus();
            monoffBtn.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    Log.d(TAG, "Enable/Disable Bluetooth");
                    enableDisableBT();
                }
            });
            discoverdevices.setOnClickListener(discoverdevicesOnClickListener);
            registerReceiver(mBroadcastReceiver3, new IntentFilter(BluetoothDevice.ACTION_FOUND));

        }

        public void checkOnOffstatus() {
            if (mBluetoothAdapter.isEnabled()) {
                BTIstatus.setImageResource(R.drawable.ic_action_on);
            } else {
                BTIstatus.setImageResource(R.drawable.ic_action_off);
            }

        }

        public void checkBTStatus() {
            if (mBluetoothAdapter == null) {
                BluetoothStatus.setText("Bluetooth is not Available");
                Log.d(TAG, "enableDisableBT: Bluetooth not available");
            } else {
                BluetoothStatus.setText("Bluetooth is Available");
                Log.d(TAG, "enableDisableBT: Bluetooth is Available");
            }
        }

        public void enableDisableBT() {
            if (!mBluetoothAdapter.isEnabled()) {
                Log.d(TAG, "Enabling Bluetooth");
                showToast("Turning On Bluetooth");
                //Intent enableBTIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                BTIstatus.setImageResource(R.drawable.ic_action_on);
                mBluetoothAdapter.enable();
                discoverdevices.setEnabled(true);
                //startActivity(enableBTIntent);

                IntentFilter BTIntent = new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED);
                registerReceiver(mBroadcastReceiver1, BTIntent);

            }
            if (mBluetoothAdapter.isEnabled()) {
                Log.d(TAG, "Disabling Bluetooth");
                showToast("Turning Off Bluetooth");
                mBluetoothAdapter.disable();
                discoverdevices.setEnabled(false);
                BTIstatus.setImageResource(R.drawable.ic_action_off);

                IntentFilter BTIntent = new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED);
                registerReceiver(mBroadcastReceiver1, BTIntent);
            }
        }

        private Button.OnClickListener discoverdevicesOnClickListener = new Button.OnClickListener() {

            @Override
            public void onClick(View view) {
                mBluetoothAdapter.startDiscovery();
            }
        };
        private void searchnconnect(){

            mBluetoothAdapter.cancelDiscovery();

            String device_details = mydevice.getAddress();
            String deviceaddress = device_details.substring(device_details.length()-17);
            Log.d("DEVICE ADDRESS: ",deviceaddress);
            Intent intent = new Intent(MainActivity.this, MapsActivity.class);
            intent.putExtra(EXTRA_MESSAGE,deviceaddress);
            startActivity(intent);

        }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        if(requestCode == REQUEST_ENABLE_BT){
            checkBTStatus();
        }
    }

        private void showToast(String msg) {
            Toast.makeText(this, msg, Toast.LENGTH_SHORT).show();
        }
    }



