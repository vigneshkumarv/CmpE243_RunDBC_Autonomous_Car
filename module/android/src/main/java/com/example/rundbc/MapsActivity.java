package com.example.rundbc;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Handler;
import android.support.annotation.WorkerThread;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

public class MapsActivity extends AppCompatActivity {
    private static final String TAG = "MapsActivity";
    private static final String STARTMSG ="CARON~";
    private static final String STOPMSG = "CAROFF~";
//~ADLG#
    private static final char START_PCK = '~';
    private static final char END_PCK = '#';
    TextView mylabel, connected;
    //EditText myText;
    Button btStart, btStop, btBack;
    BluetoothSocket mmSocket;
    BluetoothAdapter mBluetoothadapter;
    BluetoothDevice mmDevice;
    OutputStream mmOutputStream;
    InputStream mmInputStream;
    Thread workerThread;
    String DeviceAddress;
    TextView DeflectionAngle, DistancefromDestination;
    byte [] readBuffer;
    int readBufferPosition;

    String temp_string="";
    //Handler BluetoothIn;
    //final int handlerState = 0;
    private StringBuilder recDataString = new StringBuilder();
    volatile boolean stopWorker;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        Intent intent = getIntent();
        DeviceAddress = intent.getStringExtra(MainActivity.EXTRA_MESSAGE);
        mylabel = findViewById(R.id.connectstatus);
        connected = findViewById(R.id.connectedtohc05);
        //myText = findViewById(R.id.message);
        //btSend = findViewById(R.id.send);
        DeflectionAngle = findViewById(R.id.AngleDisplay);
        DistancefromDestination = findViewById(R.id.dfdDisplay);
        btStart = findViewById(R.id.startbtn);
        btStop = findViewById(R.id.stopbtn);
        btBack = findViewById(R.id.back);
        findBT();
        try {
            OpenBT();
        } catch (IOException e) {
            e.printStackTrace();
        }

       /* btSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //String msg= myText.getText().toString();//~10
                SendData(msg);
            }
        });*/

        btStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                SendData(STARTMSG);
                Log.d(TAG,"Start Button Clicked");
            }
        });

        btStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                SendData(STOPMSG);
                Log.d(TAG,"Stop Button Clicked");
            }
        });

        btBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try{
                    closeBT();
                }
                catch (IOException e){}

            }
        });

    }

    private void SendData(String msg) {
        try {
            mmOutputStream.write(msg.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
        mylabel.setText("Data Sent");
    }

    void findBT(){
        mBluetoothadapter = BluetoothAdapter.getDefaultAdapter();
        mmDevice = mBluetoothadapter.getRemoteDevice(DeviceAddress);
        connected.setText("Connected to " + mmDevice.getName());

    }
    void OpenBT() throws IOException{
        UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");//HC-05 Specific
        mmSocket = mmDevice.createInsecureRfcommSocketToServiceRecord(uuid);
        mmSocket.connect();
        Log.d(TAG,"Connected!");
        mmOutputStream = mmSocket.getOutputStream();
        mmInputStream = mmSocket.getInputStream();
        beginListenForData();
        mylabel.setText("Ready");

    }
    void beginListenForData(){
        final Handler handler = new Handler();
        final byte delimiter = '#'; //ASCII  code for a newline character

        stopWorker = false;
        readBufferPosition = 0;
        readBuffer = new byte[1024];

        workerThread = new Thread(new Runnable() {
            @Override
            public void run() {
                while(!Thread.currentThread().isInterrupted() && !stopWorker) {
                    try {
                        int bytesAvailable = mmInputStream.available();
                        if (bytesAvailable > 0) {                            //Making sure data is available
                            byte[] packetBytes = new byte[bytesAvailable];
                            mmInputStream.read(packetBytes);
                            for (int i = 0; i < bytesAvailable; i++) {
                                byte b = packetBytes[i];
                                if (b == START_PCK) {
                                    temp_string = "";
                                    temp_string = Character.toString((char) b);
                                } else if (b == END_PCK) {
                                    temp_string += Character.toString((char) b);
                                    parse_msg(temp_string);
                                    temp_string = "";
                                } else {
                                    temp_string += Character.toString((char) b);
                                }
                            }

                        }
                    }

                    catch (IOException ex) {
                        stopWorker = true;
                    }
                }
            }
        });
        workerThread.start();
    }
    void parse_msg(String str){
        Log.i("Parse_msg(): ",str);

       //DeflectionAngle.setText("Angle: "+str.substring(str.indexOf('A')+1, str.indexOf('D')));
       //DistancefromDestination.setText("Dist: "+str.substring(str.indexOf('D')+1,str.indexOf('L')));

    }
    void closeBT() throws IOException
    {
        stopWorker = true;
        mmOutputStream.close();
        mmInputStream.close();
        mmSocket.close();
        finish();
    }
}
