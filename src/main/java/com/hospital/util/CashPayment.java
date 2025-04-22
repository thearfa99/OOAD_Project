package com.hospital.util;

public class CashPayment implements PaymentStrategy {
    public void processPayment(double amount) {
        System.out.println("Processing cash payment of $" + amount);
    }
}
