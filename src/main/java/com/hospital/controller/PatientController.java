package com.hospital.controller;

import com.hospital.model.Patient;
import com.hospital.service.PatientService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

@Controller
@RequestMapping("/patients")
public class PatientController {
    private final PatientService service;

    public PatientController(PatientService service) {
        this.service = service;
    }

    @GetMapping
    public String listPatients(Model model) {
        model.addAttribute("patients", service.getAllPatients());
        return "patients";
    }

    @PostMapping
    public String addPatient(@ModelAttribute Patient patient) {
        service.savePatient(patient);
        return "redirect:/patients";
    }
}
