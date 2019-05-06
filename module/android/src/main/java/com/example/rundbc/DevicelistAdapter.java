package com.example.rundbc;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class DevicelistAdapter extends ArrayAdapter<BluetoothDevice> {
    private LayoutInflater mLayoutInflator;
    private ArrayList<BluetoothDevice> mDevices;
    private int mViewResourceId;

    public DevicelistAdapter(Context context,int tvResourceID, ArrayList<BluetoothDevice> devices){
        super(context,tvResourceID,devices);
        this.mDevices = devices;
        mLayoutInflator = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        mViewResourceId = tvResourceID;
    }
    public View getView(int position, View convertView, ViewGroup parent){
        convertView = mLayoutInflator.inflate(mViewResourceId,null);

        BluetoothDevice device = mDevices.get(position);
        if(device!=null){
            TextView deviceName = convertView.findViewById(R.id.tvDeviceName);
            TextView deviceAddress = convertView.findViewById(R.id.tvDeviceAddress);

            if(deviceName!=null){
                deviceName.setText(device.getName());
            }
            if(deviceAddress!=null){
                deviceAddress.setText(device.getAddress());
            }

        }
        return convertView;
    }
}
