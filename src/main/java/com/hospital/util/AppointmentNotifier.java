package com.hospital.util;

import com.hospital.model.Appointment;
import java.util.*;

public class AppointmentNotifier {
    private final List<AppointmentObserver> observers = new ArrayList<>();

    public void addObserver(AppointmentObserver observer) {
        observers.add(observer);
    }

    public void notifyObservers(Appointment appointment) {
        for (AppointmentObserver observer : observers) {
            observer.update(appointment);
        }
    }
}
