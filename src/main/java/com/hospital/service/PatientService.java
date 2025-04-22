package com.hospital.service;

import com.hospital.model.Patient;
import com.hospital.repository.PatientRepository;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class PatientService {
    private final PatientRepository repo;

    public PatientService(PatientRepository repo) {
        this.repo = repo;
    }

    public List<Patient> getAllPatients() {
        return repo.findAll();
    }

    public void savePatient(Patient patient) {
        repo.save(patient);
    }
}
