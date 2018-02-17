---------------------------------------------------------------------------------------------
                            MEDICAL CLINIC SCHEDULING SERVICE
---------------------------------------------------------------------------------------------
This program is designed to provide patients with medical treatment according to their needs.

Doctors and patients are checked-in to the clinic:
 
    Doctor check-in:
        -Doctor supplies name, favorite room number, and specialty code
        -Assigns doctor to favorite room if the room is available
        -If the doctor's favorite room is not available, the doctor can check-in another time
    
    Patient check-in:
        -Patient supplies name, age, specialty code, and emergency indicator
        -If the patient is under 16, the patient is assigned to a pediatrition
        
        Otherwise:
        -Assigns patient to available room occupied by a doctor with the same specialty code
        -If no matching specialty doctor is available, assigns patient to least crowded
            matching specialty doctor waiting room
        -If no matching specialty doctor is in the clinic, patient is seen by a general 
            practitioner (GP) or added to the least crowded GP waiting room
        -If no GP is in the clinic, the patient is seen by any available doctor or added to
            the least crowded waiting room in the clinic
 
 
 Doctors and patients are checked-out of the clinic:
 
    Doctor check-out: 
        -Doctor supplies name, room number, and specialty code
        -Assumes doctor's current patient has been seen and they are auto checked-out
        -Patients in the corresponding waiting room are properly reassigned
        
    Patient check-out:
        -Patient supplies name, room number, and specialty code
        -Doctor is free to see next patient in waiting room if anyone is waiting
 
 Assumptions:
 
    -All patients are seen before they check-out
    -All patients eventually check-out
    -There are 100 exam rooms in the clinic, each with one waiting room
    -Everyone's specialty code is one of the following:
 
    1. PED - Pediatrics                        7.  PSY - Psychiatry
    2. GEN - General practice                  8.  NEU - Neurology
    3. INT - Internal medicine                 9.  ORT - Orthopedics
    4. CAR - Cardiology                        10. DET - Dermatology
    5. SUR - Surgeon                           11. OPT - Ophthalmology
    6. OBS - Obstetrics                        12. ENT - Ear, Nose, and Throat
