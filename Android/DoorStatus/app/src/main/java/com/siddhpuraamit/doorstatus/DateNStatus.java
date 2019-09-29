package com.siddhpuraamit.doorstatus;

public class DateNStatus {
    private String date;
    private String status;

    public DateNStatus(){
        super();
    }

    public DateNStatus(String _date, String _status){
        date = _date;
        status = _status;
    }


    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}
