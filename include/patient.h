#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>

// forward dec
class VisualizeTaskManager;

/**
 * @class Patient
 * @brief Represents a patient with details such as name, age, address, ID, symptoms, and gender.
 */
class Patient {
private:
    std::string description; ///< The name of the patient.
    std::string gender; ///< The gender of the patient.
    int age; ///< The age of the patient.

public:
    friend class VisualizeTaskManager;
    /**
     * @brief Constructor to initialize a Patient object with all details.
     * @param description The name of the patient.
     * @param age The age of the patient.
     * @param gender The gender of the patient.
     */
    Patient(std::string description, int age, std::string gender) :
    description(description), age(age),gender(gender) {}
    Patient() = default;

    /**
     * @brief Destructor for the Patient object.
     */
    ~Patient() = default;

    std::string getDescription() const;

    std::string getGender() const;

    int getAge() const;
    void setDescription(const std::string& description);
    void setGender(const std::string& gender);
    void setAge(int age);
};

std::string Patient::getDescription() const {
    return description;
}

std::string Patient::getGender() const {
    return gender;
}

int Patient::getAge() const {
    return age;
}

void Patient::setDescription(const std::string& description)
{
    this->description = description;
}

void Patient::setGender(const std::string& gender)
{
    this->gender = gender;
}
void Patient::setAge(int age)
{
    this->age = age;
}

#endif // PATIENT_H
