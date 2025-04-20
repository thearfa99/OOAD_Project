# OOAD_Project: Hospital Management System

## Problem Definition:
Modern hospitals struggle with inefficient, manual workflows across patient care, resource management, and billing. Key challenges include:
 - Fragmented Processes: Paper-based registration, appointment scheduling, and billing lead to delays and errors.
 - Poor Resource Coordination: Doctors’ schedules, bed availability, and medical inventory are not tracked in real time.
 - Billing Complexity: Handling insurance claims, dynamic pricing, and payment modes manually increases errors.
 - Data Silos: Patient records, prescriptions, and reports lack centralized access, impacting care quality.

## Project Synopsis:
We propose a web-based Hospital Management System (HMS) to automate workflows, enhance patient care, and optimize resource utilization.
Key Features
 - Patient Management: 
    - Self-registration portal with digital profiles.
    - Real-time appointment booking and SMS/email reminders.
 - Doctor & Staff Coordination:
    - Schedule management and digital prescription generation.
    - Access to centralized patient histories.
 - Billing & Insurance:
    - Automated invoicing with support for insurance/self-pay strategies.
 - Inventory Tracking:
    - Real-time monitoring of medicines, equipment, and beds.
 - Reporting:
    - Dashboards for administrators to analyze patient flow and revenue.

## Technical Scope:
- Architecture: MVC (Spring Boot for backend, Thymeleaf/JavaFX frontend).
- Database: MySQL for data persistence (patient records, appointments).
- Design Patterns: Factory (user creation), Observer (appointment alerts), Strategy (billing), Singleton (DB config).
- Security: Role-based access control (Spring Security) and HIPAA-compliant encryption.
