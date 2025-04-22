package com.hospital.util;

public class CreditCardPayment implements PaymentStrategy {
    public void processPayment(double amount) {
        System.out.println("Processing credit card payment of $" + amount);
    }
}
