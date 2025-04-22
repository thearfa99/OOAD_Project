#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include <algorithm>

/*==============================
Hospital Management System
Design Patterns Implementation:
- Singleton
- Abstract Factory
- Observer
- Command
- Template Method
==================================*/

// Forward declarations
class Person;
class Hospital;

//******************** SINGLETON PATTERN ********************

// Abstract Product-A: Abstract Factory Pattern
// Singleton Class: Singleton Pattern
// Command Class 1: Command Pattern
class RadiologicalTest {
protected:
    RadiologicalTest() = default;
    RadiologicalTest(const RadiologicalTest&) = delete;
    RadiologicalTest& operator=(const RadiologicalTest&) = delete;
    
    static std::unique_ptr<RadiologicalTest> instance;
    static std::mutex mutex;

public:
    static RadiologicalTest* getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!instance) {
            instance.reset(new RadiologicalTest());
        }
        return instance.get();
    }
    
    virtual ~RadiologicalTest() = default;
    virtual void perform(const std::string& patientName) const {
        std::cout << "Generic radiological test for " << patientName << std::endl;
    }
};

std::mutex RadiologicalTest::mutex;
std::unique_ptr<RadiologicalTest> RadiologicalTest::instance = nullptr;

//******************** COMMAND PATTERN ********************

// Abstract Product-B: Abstract Factory Pattern
// Command Class 2: Command Pattern
class LabTest {
public:
    virtual ~LabTest() = default;
    virtual void perform(const std::string& patientName) const {
        std::cout << "Generic lab test for " << patientName << std::endl;
    }
};

// Concrete Product-A1: Abstract Factory Pattern
// Concrete Command Class 1: Command Pattern
class XRAY : public RadiologicalTest {
public:
    void perform(const std::string& patientName) const override {
        std::cout << "XRAY test for " << patientName << " is being done." << std::endl;
    }
};

// Concrete Product-A2: Abstract Factory Pattern
// Concrete Command Class 2: Command Pattern
class EKG : public RadiologicalTest {
public:
    void perform(const std::string& patientName) const override {
        std::cout << "EKG test for " << patientName << " is being done." << std::endl;
    }
};

// Concrete Product-B1: Abstract Factory Pattern
// Concrete Command Class 3: Command Pattern
class Cholesterol : public LabTest {
public:
    void perform(const std::string& patientName) const override {
        std::cout << "Cholesterol test for " << patientName << " is being done." << std::endl;
    }
};

// Concrete Product-B2: Abstract Factory Pattern
// Concrete Command Class 4: Command Pattern
class Thyroid : public LabTest {
public:
    void perform(const std::string& patientName) const override {
        std::cout << "Thyroid test for " << patientName << " is being done." << std::endl;
    }
};

//******************** OBSERVER PATTERN ********************

// Abstract Subject: Observer Pattern
class Drug {
private:
    std::vector<Person*> patients;
    std::string sideEffect;
    std::string drugName;
    
public:
    Drug(const std::string& name, const std::string& effect)
        : drugName(name), sideEffect(effect) {}
    
    virtual ~Drug() = default;
    
    void attach(Person* person);
    void detach(Person* person);
    void notifyObservers();
    
    void setSideEffect(const std::string& effect) {
        sideEffect = effect;
        notifyObservers();
    }
    
    std::string getSideEffect() const { return sideEffect; }
    std::string getDrugName() const { return drugName; }
};

// Concrete Subject: Observer Pattern
class Pill : public Drug {
public:
    Pill(const std::string& drugName, const std::string& sideEffect)
        : Drug(drugName, sideEffect) {}
};

//******************** PERSON CLASSES ********************

// Observer: Observer Pattern
class Person {
protected:
    std::string name;
    
public:
    Person(const std::string& name) : name(name) {}
    virtual ~Person() = default;
    
    std::string getName() const { return name; }
    
    // Virtual methods to be implemented by subclasses
    virtual void update(Drug* drug) {}
    virtual void prescribeMed(Person* person, Drug* drug) {}
    virtual void setDepartment(Hospital* dep) {}
    virtual void conductTest(Hospital* dep, Person* patient) {}
    virtual Hospital* getDepartment() { return nullptr; }
    virtual void setEmail(const std::string& email) {}
    virtual void setTelephone(const std::string& telephone) {}
    virtual std::string getEmail() const { return ""; }
    virtual std::string getTelephone() const { return ""; }
};

// ConcreteObserver: Observer Pattern
class Patient : public Person {
private:
    Drug* observedDrug = nullptr;
    std::string email;
    std::string telephone;
    
public:
    Patient(const std::string& name) : Person(name) {}
    
    void setEmail(const std::string& email) override { this->email = email; }
    void setTelephone(const std::string& telephone) override { this->telephone = telephone; }
    
    std::string getEmail() const override { return email; }
    std::string getTelephone() const override { return telephone; }
    
    void update(Drug* drug) override {
        observedDrug = drug;
        std::cout << "\nNotification for " << name << ":" << std::endl;
        std::cout << "Due to the side effect change of " << drug->getDrugName()
                 << " to " << drug->getSideEffect() << std::endl;
        std::cout << "Notification sent to: " << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "Phone: " << telephone << std::endl;
    }
};

//******************** ABSTRACT FACTORY PATTERN ********************

// Abstract Factory Class: Abstract Factory Pattern
// Abstract Class: Template Method Pattern
class Hospital {
private:
    // Template Method components
    void insertPersonalInfo(Person* person) {
        std::string email, phone;
        std::cout << "\nPERSONAL DEMOGRAPHIC INFORMATION" << std::endl;
        std::cout << "Insert the following contact information:" << std::endl;
        std::cout << "E-mail: ";
        std::cin >> email;
        std::cout << "Telephone: ";
        std::cin >> phone;
        person->setEmail(email);
        person->setTelephone(phone);
        std::cout << std::endl;
    }
    
    virtual void insuranceInfo(Person* person) {
        std::cout << "Generic insurance information" << std::endl;
    }
    
    virtual void medicalHistory(Person* person) {
        std::cout << "Generic medical history" << std::endl;
    }
    
    virtual void consentForm(Person* person) {
        std::cout << "Generic consent form" << std::endl;
    }

protected:
    std::vector<Hospital*> departments;

public:
    virtual ~Hospital() = default;
    
    // Template Method
    void createPatient(Person* person) {
        insertPersonalInfo(person);
        insuranceInfo(person);
        medicalHistory(person);
        consentForm(person);
    }
    
    virtual void hireDoctor(Person* doctor) {}
    
    void addDepartment(Hospital* department) {
        departments.push_back(department);
    }
    
    // Factory methods
    virtual std::unique_ptr<RadiologicalTest> createRadiologicalTest(Person* patient) {
        return nullptr;
    }
    
    virtual std::unique_ptr<LabTest> createLabTest(Person* patient) {
        return nullptr;
    }
};

//******************** CONCRETE FACTORIES ********************

// Concrete Factory Class 1: Abstract Factory Pattern
// Concrete Class 1: Template Method Pattern
// Receiver Class 1: Command Pattern
class Cardiology : public Hospital {
private:
    void insuranceInfo(Person* person) override {
        std::cout << "INSURANCE MESSAGE" << std::endl;
        std::cout << "Cardiology department accepts only government insurance." << std::endl << std::endl;
    }
    
    void medicalHistory(Person* person) override {
        int choice;
        std::cout << "MEDICAL HISTORY" << std::endl;
        std::cout << "Have you ever had cardiac problems before?" << std::endl;
        std::cout << "1 for YES, 0 for NO: ";
        std::cin >> choice;
        std::cout << "Processing..." << std::endl << std::endl;
    }
    
    void consentForm(Person* person) override {
        int choice;
        std::cout << "CONSENT FORM" << std::endl;
        std::cout << "I have been informed about the conditions and risks relevant to my treatment under CARDIOLOGY department." << std::endl;
        std::cout << "I understood and I'm willing to take the risks (PRESS 1)" << std::endl;
        std::cout << "I understood and I don't want to take the risk (PRESS 0)" << std::endl;
        std::cin >> choice;
        if (choice == 0) {
            std::cout << "Treatment declined. Exiting registration." << std::endl;
            exit(0);
        }
        std::cout << std::endl;
    }
    
public:
    void hireDoctor(Person* doctor) override {
        doctor->setDepartment(this);
    }
    
    std::unique_ptr<RadiologicalTest> createRadiologicalTest(Person* patient) override {
        auto test = std::make_unique<EKG>();
        test->perform(patient->getName());
        return test;
    }
    
    std::unique_ptr<LabTest> createLabTest(Person* patient) override {
        auto test = std::make_unique<Cholesterol>();
        test->perform(patient->getName());
        return test;
    }
};

// Concrete Factory Class 2: Abstract Factory Pattern
// Concrete Class 2: Template Method Pattern
// Receiver Class 2: Command Pattern
class Endocrinology : public Hospital {
private:
    void insuranceInfo(Person* person) override {
        std::cout << "INSURANCE MESSAGE" << std::endl;
        std::cout << "Endocrinology department doesn't accept any insurance." << std::endl << std::endl;
    }
    
    void medicalHistory(Person* person) override {
        int choice;
        std::cout << "MEDICAL HISTORY" << std::endl;
        std::cout << "Have you ever received any kind of hormone treatment before?" << std::endl;
        std::cout << "1 for YES, 0 for NO: ";
        std::cin >> choice;
        std::cout << "Processing..." << std::endl << std::endl;
    }
    
    void consentForm(Person* person) override {
        int choice;
        std::cout << "CONSENT FORM" << std::endl;
        std::cout << "I have been informed about the conditions and risks relevant to my treatment under ENDOCRINOLOGY department." << std::endl;
        std::cout << "I understood and I'm willing to take the risks (PRESS 1)" << std::endl;
        std::cout << "I understood and I don't want to take the risk (PRESS 0)" << std::endl;
        std::cin >> choice;
        if (choice == 0) {
            std::cout << "Treatment declined. Exiting registration." << std::endl;
            exit(0);
        }
        std::cout << std::endl;
    }
    
public:
    void hireDoctor(Person* doctor) override {
        doctor->setDepartment(this);
    }
    
    std::unique_ptr<RadiologicalTest> createRadiologicalTest(Person* patient) override {
        auto test = std::make_unique<XRAY>();
        test->perform(patient->getName());
        return test;
    }
    
    std::unique_ptr<LabTest> createLabTest(Person* patient) override {
        auto test = std::make_unique<Thyroid>();
        test->perform(patient->getName());
        return test;
    }
};

// Concrete Factory Class 3: Abstract Factory Pattern
// Concrete Class 3: Template Method Pattern
// Receiver Class 3: Command Pattern
class Orthopedics : public Hospital {
private:
    void insuranceInfo(Person* person) override {
        std::cout << "INSURANCE MESSAGE" << std::endl;
        std::cout << "Orthopedics department accepts only private health insurance." << std::endl << std::endl;
    }
    
    void medicalHistory(Person* person) override {
        int choice;
        std::cout << "MEDICAL HISTORY" << std::endl;
        std::cout << "Have you ever had a broken limb before?" << std::endl;
        std::cout << "1 for YES, 0 for NO: ";
        std::cin >> choice;
        std::cout << "Processing..." << std::endl << std::endl;
    }
    
    void consentForm(Person* person) override {
        int choice;
        std::cout << "CONSENT FORM" << std::endl;
        std::cout << "I have been informed about the conditions and risks relevant to my treatment under ORTHOPEDICS department." << std::endl;
        std::cout << "I understood and I'm willing to take the risks (PRESS 1)" << std::endl;
        std::cout << "I understood and I don't want to take the risk (PRESS 0)" << std::endl;
        std::cin >> choice;
        if (choice == 0) {
            std::cout << "Treatment declined. Exiting registration." << std::endl;
            exit(0);
        }
        std::cout << std::endl;
    }
    
public:
    void hireDoctor(Person* doctor) override {
        doctor->setDepartment(this);
    }
    
    std::unique_ptr<RadiologicalTest> createRadiologicalTest(Person* patient) override {
        auto test = std::make_unique<XRAY>();
        test->perform(patient->getName());
        return test;
    }
    
    // Consistent API: implement lab test for Orthopedics
    std::unique_ptr<LabTest> createLabTest(Person* patient) override {
        auto test = std::make_unique<Cholesterol>();
        test->perform(patient->getName());
        return test;
    }
};

//******************** COMMAND PATTERN INVOKER ********************

// INVOKER CLASS: COMMAND PATTERN & OBJECT DELEGATION FOR ABSTRACT FACTORY
class LabAttendant {
public:
    void createTests(Hospital* department, Person* patient) {
        if (department) {
            department->createRadiologicalTest(patient);
            department->createLabTest(patient);
        } else {
            std::cout << "Error: Department not specified for testing." << std::endl;
        }
    }
};

//******************** DOCTOR CLASS ********************

// CLIENT FOR COMMAND PATTERN - INITIATES & CONTROLS TESTING PROCESS
class Doctor : public Person {
private:
    Hospital* department = nullptr;
    std::unique_ptr<LabAttendant> medicalTest = std::make_unique<LabAttendant>();
    
public:
    Doctor(const std::string& name) : Person(name) {}
    
    void setDepartment(Hospital* dep) override {
        department = dep;
    }
    
    Hospital* getDepartment() override {
        return department;
    }
    
    // Ordering Test Function
    void conductTest(Hospital* department, Person* patient) override {
        std::cout << name << " is ordering tests for " << patient->getName() << std::endl;
        medicalTest->createTests(department, patient);
    }
    
    // Diagnose Function - Attaching Observer to the Subject Notification Network
    void prescribeMed(Person* patient, Drug* drug) override {
        std::cout << name << " is prescribing " << drug->getDrugName()
                 << " to " << patient->getName() << std::endl;
        drug->attach(patient);
    }
};

//******************** DRUG OBSERVER IMPLEMENTATION ********************

void Drug::attach(Person* person) {
    // Avoid duplicate entries
    auto it = std::find_if(patients.begin(), patients.end(),
                          [person](Person* p) { return p->getName() == person->getName(); });
    
    if (it == patients.end()) {
        patients.push_back(person);
        std::cout << person->getName() << " is now being monitored for " << drugName << " side effects." << std::endl;
    }
}

void Drug::detach(Person* person) {
    auto it = std::find_if(patients.begin(), patients.end(),
                          [person](Person* p) { return p->getName() == person->getName(); });
    
    if (it != patients.end()) {
        patients.erase(it);
        std::cout << person->getName() << " is no longer being monitored for " << drugName << " side effects." << std::endl;
    }
}

void Drug::notifyObservers() {
    for (auto& patient : patients) {
        patient->update(this);
    }
}

//******************** MAIN FUNCTION ********************

int main() {
    // Creating Persons
    std::unique_ptr<Person> pat1 = std::make_unique<Patient>("Arfa");
    std::unique_ptr<Person> pat2 = std::make_unique<Patient>("Saabith");
    std::unique_ptr<Person> pat3 = std::make_unique<Patient>("Nevin");
    std::unique_ptr<Person> doc1 = std::make_unique<Doctor>("Dr. Omkar");
    std::unique_ptr<Person> doc2 = std::make_unique<Doctor>("Dr. Pavan");
    std::unique_ptr<Person> doc3 = std::make_unique<Doctor>("Dr. Ritwik");

    // Creating Medications
    std::unique_ptr<Drug> majezik = std::make_unique<Pill>("Majezik", "Dizziness");
    std::unique_ptr<Drug> aspirin = std::make_unique<Pill>("Aspirin", "Palpitations");
    std::unique_ptr<Drug> apranaxFort = std::make_unique<Pill>("Apranax Fort", "Heart Attack");

    // Creating Hospital & Departments
    std::unique_ptr<Hospital> acibadem = std::make_unique<Hospital>();
    std::unique_ptr<Hospital> cardiology = std::make_unique<Cardiology>();
    std::unique_ptr<Hospital> endocrinology = std::make_unique<Endocrinology>();
    std::unique_ptr<Hospital> orthopedics = std::make_unique<Orthopedics>();
    
    // Adding departments to main hospital
    acibadem->addDepartment(cardiology.get());
    acibadem->addDepartment(endocrinology.get());
    acibadem->addDepartment(orthopedics.get());

    // Setting doctors' departments
    cardiology->hireDoctor(doc1.get());
    endocrinology->hireDoctor(doc2.get());
    orthopedics->hireDoctor(doc3.get());

    // Registering patients in departments
    std::cout << "=== REGISTERING PATIENT 1 IN CARDIOLOGY ===" << std::endl;
    cardiology->createPatient(pat1.get());
    
    std::cout << "=== REGISTERING PATIENT 2 IN ENDOCRINOLOGY ===" << std::endl;
    endocrinology->createPatient(pat2.get());
    
    std::cout << "=== REGISTERING PATIENT 3 IN ORTHOPEDICS ===" << std::endl;
    orthopedics->createPatient(pat3.get());

    // Testing stage
    std::cout << "\n=== CONDUCTING MEDICAL TESTS ===" << std::endl;
    doc1->conductTest(doc1->getDepartment(), pat1.get());
    doc2->conductTest(doc2->getDepartment(), pat2.get());
    doc3->conductTest(doc3->getDepartment(), pat3.get());

    // Diagnose & Prescribing medication stage
    std::cout << "\n=== PRESCRIBING MEDICATIONS ===" << std::endl;
    doc1->prescribeMed(pat1.get(), aspirin.get());
    doc2->prescribeMed(pat2.get(), apranaxFort.get());
    doc3->prescribeMed(pat3.get(), majezik.get());

    // Changing side effect states to trigger observer notifications
    std::cout << "\n=== UPDATING MEDICATION SIDE EFFECTS ===" << std::endl;
    aspirin->setSideEffect("Severe Palpitations");
    apranaxFort->setSideEffect("Stroke");
    majezik->setSideEffect("Blurry Vision");

    return 0;
}
