#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100

struct Patient {
    int id;
    char name[50];
    char address[100];
    int age;
    char sex[10];
    char disease[100];
};

struct MedicalRecord {
    int recordId;
    int patientId;
    char patientName[50];
    char creationDate[20];
    char medicalHistory[500];
};

struct Patient patients[MAX_PATIENTS];
struct MedicalRecord records[MAX_PATIENTS];
int patientCount = 0;
int recordCount = 0;

void loadMedicalRecordFromFile() {
    FILE *file = fopen("medicalRecords.txt", "r");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read record data from the file
    while (fscanf(file, "%d,%d,%[^,],%[^,],%[^\n]\n", &records[recordCount].recordId,
                  &records[recordCount].patientId, records[recordCount].patientName,
                  records[recordCount].creationDate, records[recordCount].medicalHistory
                  ) == 5) {
        recordCount++;
    }

    fclose(file);
}

void loadPatientsFromFile() {
    FILE *file = fopen("patients.txt", "r");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read patient data from the file
    while (fscanf(file, "%d,%[^,],%[^,],%d,%[^,],%[^\n]\n", &patients[patientCount].id,
                  patients[patientCount].name, patients[patientCount].address,
                  &patients[patientCount].age, patients[patientCount].sex,
                  patients[patientCount].disease) == 6) {
        patientCount++;
    }

    fclose(file);
}

void savePatientsToFile() {
    FILE *file = fopen("patients.txt", "w");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Write patient data to the file
    for (int i = 0; i < patientCount; i++) {
        fprintf(file, "%d,%s,%s,%d,%s,%s\n", patients[i].id, patients[i].name, patients[i].address,
                patients[i].age, patients[i].sex, patients[i].disease);
    }

    fclose(file);
}

void saveMedicalRecordToFile() {
    FILE *file = fopen("medicalRecords.txt", "w");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Write patient data to the file
    for (int i = 0; i < recordCount; i++) {
        fprintf(file, "%d,%d,%s,%s,%s\n", records[i].recordId , records[i].patientId, records[i].patientName,
                records[i].creationDate, records[i].medicalHistory);
    }

    fclose(file);
}

void addPatient() {
    struct Patient patient;

    printf("Enter patient ID: ");
    scanf("%d", &patient.id);
    getchar();  // Consume newline character

    printf("Enter patient name: ");
    fgets(patient.name, sizeof(patient.name), stdin);
    patient.name[strcspn(patient.name, "\n")] = '\0';  // Remove newline character

    printf("Enter patient address: ");
    fgets(patient.address, sizeof(patient.address), stdin);
    patient.address[strcspn(patient.address, "\n")] = '\0';  // Remove newline character

    printf("Enter patient age: ");
    scanf("%d", &patient.age);
    getchar();  // Consume newline character

    printf("Enter patient sex: ");
    fgets(patient.sex, sizeof(patient.sex), stdin);
    patient.sex[strcspn(patient.sex, "\n")] = '\0';  // Remove newline character

    printf("Enter patient disease description: ");
    fgets(patient.disease, sizeof(patient.disease), stdin);
    patient.disease[strcspn(patient.disease, "\n")] = '\0';  // Remove newline character

    patients[patientCount++] = patient;

    printf("Patient added successfully.\n");
}
void addMedicalRecord() {
    struct MedicalRecord record;
    int id =0,idTrue=0;
    
    printf("Enter record ID: ");
    scanf("%d", &record.recordId);
    getchar();  // Consume newline character
    /*verif start*/
   do
   {
    printf("Enter patientID: ");
    scanf("%d", &id);
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id==id)
        {
            record.patientId=id;
            getchar(); // Consume newline character
            idTrue=1;
            printf("patient name %s add \n",patients[i].name);
            strcpy(record.patientName,patients[i].name);
        }
    }
   } while (idTrue != 1 );
    /*verif ends*/
   
    
   
    
    // Remove newline character

    printf("Enter Medical Record creationDate: ");
    fgets(record.creationDate, sizeof(record.creationDate), stdin);
    record.creationDate[strcspn(record.creationDate, "\n")] = '\0';  // Remove newline character

    printf("Enter Medical Record medicalHistory: ");
    fgets(record.medicalHistory, sizeof(record.medicalHistory), stdin);
    record.medicalHistory[strcspn(record.medicalHistory, "\n")] = '\0';  // Remove newline character

    

    records[recordCount++] = record;

    printf("medical record added successfully.\n");
}

void searchePatientWithId() {
    int patientId;

    printf("Enter patient ID: ");
    scanf("%d", &patientId);

    int found = 0;

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == patientId) {
            printf("Patient Found!\n");
            printf("ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Address: %s\n", patients[i].address);
            printf("Age: %d\n", patients[i].age);
            printf("Sex: %s\n", patients[i].sex);
            printf("Disease Description: %s\n", patients[i].disease);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No patient found with ID: %d\n", patientId);
    }
}

void searchAndModifyRecord() {
     int recordMedicalId;
    int id =0,idTrue=0;

    printf("Enter record Medical ID: ");
    scanf("%d", &recordMedicalId);

    int found = 0;

    for (int i = 0; i < recordCount; i++) {
        if (records[i].recordId == recordMedicalId) {
            printf("record Id: %d\n", records[i].recordId);
            printf("patient Id: %d\n", records[i].patientId);
            printf("patient Name: %s\n", records[i].patientName);
            printf("creation Date: %s\n", records[i].creationDate);
            printf("medical History: %s\n", records[i].medicalHistory);
            found = 1;
            
                printf("Do you want to modify the patient's record? (1 for Yes, 0 for No): ");
                int modifyChoice;
                scanf("%d", &modifyChoice);

                if (modifyChoice == 1) {
                     do
                    {
                        printf("Enter patientID: ");
                        scanf("%d", &id);
                        for (int j = 0; j < patientCount; j++) {
                            if (patients[j].id==id)
                            {
                                records[i].patientId=id;
                                getchar(); // Consume newline character
                                idTrue=1;
                                printf("patient name %s add \n",patients[j].name);
                                strcpy(records[i].patientName,patients[j].name);
                            }
                        }
                    } while (idTrue != 1 );
                        /*verif ends*/

                        // Remove newline character

                        printf("Enter Medical Record creationDate: ");
                        fgets(records[i].creationDate, sizeof(records[i].creationDate), stdin);
                        records[i].creationDate[strcspn(records[i].creationDate, "\n")] = '\0';  // Remove newline character

                        printf("Enter Medical Record medicalHistory: ");
                        fgets(records[i].medicalHistory, sizeof(records[i].medicalHistory), stdin);
                        records[i].medicalHistory[strcspn(records[i].medicalHistory, "\n")] = '\0';  // Remove newline character

                        printf("medical record modified successfully.\n");
                                    }
                                    break;
                            }
                        }
    if (!found) {
        printf("No medical record found with ID: %d\n", recordMedicalId);
    }
}

void listPatientsAlphabetically() {
    struct Patient temp;

    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (strcmp(patients[j].name, patients[j + 1].name) > 0) {
                temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }

    printf("\n--- Patient List (Alphabetically) ---\n");

    for (int i = 0; i < patientCount; i++) {
        printf("ID: %d\n", patients[i].id);
        printf("Name: %s\n", patients[i].name);
        printf("Address: %s\n", patients[i].address);
        printf("Age: %d\n", patients[i].age);
        printf("Sex: %s\n", patients[i].sex);
        printf("Disease Description: %s\n", patients[i].disease);
        printf("--------------------\n");
    }
}

void listMedicalRecords() {
    

    printf("\n--- Patient List ---\n");

    for (int i = 0; i < recordCount; i++) {
        
            printf("record Id: %d\n", records[i].recordId);
            printf("patient Id: %d\n", records[i].patientId);
            printf("patient Name: %s\n", records[i].patientName);
            printf("creation Date: %s\n", records[i].creationDate);
            printf("medical History: %s\n", records[i].medicalHistory);
     
        printf("--------------------\n");
    }
}


void deletePatient() {
    int patientId;
    printf("Enter patient ID: ");
    scanf("%d", &patientId);

    int found = 0;

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == patientId) {
            found = 1;

            printf("Patient Found!\n");
            printf("ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Address: %s\n", patients[i].address);
            printf("Age: %d\n", patients[i].age);
            printf("Sex: %s\n", patients[i].sex);
            printf("Disease Description: %s\n", patients[i].disease);

            printf("Are you sure you want to delete this patient? (1 for Yes, 0 for No): ");
            int deleteChoice;
            scanf("%d", &deleteChoice);

            if (deleteChoice == 1) {
                for (int j = i; j < patientCount - 1; j++) {
                    patients[j] = patients[j + 1];
                }
                patientCount--;

                printf("Patient deleted successfully.\n");
            } else {
                printf("Deletion cancelled.\n");
            }

            break;
        }
    }

    if (!found) {
        printf("No patient found with ID: %d\n", patientId);
    }
}

void deleteMedicalRecord() {
    int medicalRecordId;
    printf("Enter medical record ID: ");
    scanf("%d", &medicalRecordId);

    int found = 0;

    for (int i = 0; i < recordCount; i++) {
        if (records[i].recordId == medicalRecordId) {
            found = 1;

            printf("medical Record Found!\n");
            printf("record Id: %d\n", records[i].recordId);
            printf("patient Id: %s\n", records[i].patientId);
            printf("patient Name: %s\n", records[i].patientName);
            printf("creation Date: %d\n", records[i].creationDate);
            printf("medical History: %s\n", records[i].medicalHistory);
           

            printf("Are you sure you want to delete this patient? (1 for Yes, 0 for No): ");
            int deleteChoice;
            scanf("%d", &deleteChoice);

            if (deleteChoice == 1) {
                for (int j = i; j < recordCount - 1; j++) {
                    records[j] = records[j + 1];
                }
                recordCount--;

                printf("Medical Records deleted successfully.\n");
            } else {
                printf("Deletion cancelled.\n");
            }

            break;
        }
    }

    if (!found) {
        printf("No patient found with ID: %d\n", medicalRecordId);
    }
}

int main() {
    int choice;

    // Load patient data from the file
    loadPatientsFromFile();
    loadMedicalRecordFromFile();
    do {
        printf("\n--- Hospital Management System ---\n");
        printf("1. Add a new patient\n");
        printf("2. searche Patient With Id\n");
        printf("3. Search and modify a patient record\n");
        printf("4. List patients alphabetically\n");
        printf("5. Delete a patient\n");
        printf("6. Save patients to file\n");
        printf("7. Save medical record to file\n");
        printf("8. Add a new medical record \n");
        printf("9. load Medical Record From File\n");
        printf("10. load Patients From File \n");
        printf("11. Delete a medical record\n");
        printf("12. List all medical record\n");
        printf("13. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                searchePatientWithId();
                break;
            case 3:
                searchAndModifyRecord();
                break;
            case 4:
                listPatientsAlphabetically();
                break;
            case 5:
                deletePatient();
                break;
            case 6:
                savePatientsToFile();
                break;
            case 7:
                saveMedicalRecordToFile();
                break;
            case 8:
                addMedicalRecord();
                break;
            case 9:
                loadMedicalRecordFromFile();
                break;
            case 10:
                loadPatientsFromFile();
                break;
            case 11:
                deleteMedicalRecord();
                break;    
            case 12:
                listMedicalRecords();
                break; 
            case 13:
                printf("Exiting the program.\n");
                break; 
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 13);

    return 0;
}
