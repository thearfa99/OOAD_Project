package com.hospital.util;

public class ReportFactory {
    public static Report createReport(String type) {
        if ("patient".equalsIgnoreCase(type)) {
            return new PatientReport();
        }
        throw new IllegalArgumentException("Invalid report type");
    }
}
