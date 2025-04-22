package com.hospital.util;

import com.hospital.model.Appointment;

public interface AppointmentObserver {
    void update(Appointment appointment);
}