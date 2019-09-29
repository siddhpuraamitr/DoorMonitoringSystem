package com.siddhpuraamit.doorstatus;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class MyListAdapter extends RecyclerView.Adapter<MyListAdapter.ViewHolder> {
    private ArrayList<DateNStatus>  listdata;

    // RecyclerView recyclerView;
    public MyListAdapter(ArrayList<DateNStatus> _listdata) {
        this.listdata = _listdata;
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        LayoutInflater layoutInflater = LayoutInflater.from(parent.getContext());
        View listItem = layoutInflater.inflate(R.layout.list_item, parent, false);
        ViewHolder viewHolder = new ViewHolder(listItem);
        return viewHolder;
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        final DateNStatus dateNStatus = listdata.get(position);
        holder.tvDate.setText(dateNStatus.getDate());
        holder.tvStatus.setText("Main door is "+ dateNStatus.getStatus());
        if(dateNStatus.getStatus().contains("open") || dateNStatus.getStatus().contains("Open")){
            holder.ivDoor.setImageResource(R.drawable.doors_open);
        }else{
            holder.ivDoor.setImageResource(R.drawable.door_close);
        }
        holder.linearLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Toast.makeText(view.getContext(), "click on item: " + dateNStatus.getDate() + "\n" + dateNStatus.getStatus(), Toast.LENGTH_LONG).show();
            }
        });
    }


    @Override
    public int getItemCount() {
        return listdata.size();
    }

    public static class ViewHolder extends RecyclerView.ViewHolder {
        public TextView tvDate;
        public TextView tvStatus;
        public ImageView ivDoor;
        public LinearLayout linearLayout;

        public ViewHolder(View itemView) {
            super(itemView);
            this.tvDate = (TextView) itemView.findViewById(R.id.tvDate);
            this.tvStatus = (TextView) itemView.findViewById(R.id.tvStatus);
            this.ivDoor = (ImageView)itemView.findViewById(R.id.ivDoor);
            linearLayout = (LinearLayout) itemView.findViewById(R.id.linearLayout);
        }
    }
}