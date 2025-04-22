# Problem Statement & Synopsis
## Problem Definition:
Modern hospitals struggle with disconnected departmental workflows and inefficient patient care coordination. Key challenges include:
- Department Isolation: Specialized departments operate independently without unified patient management.
- Test Management Complexity: Radiological and laboratory tests lack standardized ordering processes.
- Medication Monitoring: No systematic tracking of medication side effects and patient notifications.
- Inconsistent Patient Registration: Each department follows different intake procedures.

## Project Synopsis:
We've implemented a C++ Hospital Management System (HMS) that demonstrates advanced object-oriented design principles and patterns to streamline interdepartmental operations.
Key Features
- Unified Hospital Structure:
Central hospital entity with specialized departments (Cardiology, Endocrinology, Orthopedics).
Consistent patient registration across all departments using template methods.
- Doctor Assignment and Test Management:
Doctors affiliated with specific departments can order standardized tests.
Lab attendant execution of department-appropriate radiological and laboratory tests.
Medication Management and Monitoring:
Prescription tracking with automatic patient notification.
Real-time updates when medication side effects change.
- Patient Communication:
Multi-channel notifications (email, telephone) for critical medication updates.

##Technical Implementation:
Design Patterns:
- Singleton Pattern: Ensures single instance of radiological test services.
- Abstract Factory Pattern: Standardizes test creation across departments.
- Observer Pattern: Notifies patients about medication side effect changes.
- Command Pattern: Decouples test requests from execution.
- Template Method Pattern: Enforces consistent patient registration across departments.
