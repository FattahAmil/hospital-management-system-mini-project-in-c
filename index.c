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

struct prescription {
    int id;
    char date[10];
    char name[50];
    char address[100];
    int age;
    char sex[10];
    char disease[100];
    char med[1000];
    char test[100];
};

struct MedicalRecord {
    int recordId;
    int patientId;
    char patientName[50];
    char creationDate[20];
    char medicalHistory[500];
};

struct Doctor{
    int id;
    char name[50];
    int phno;
    char sex[10];
    char specializtion[100];
};

struct Admin{
    int id;
    char name[50];
    int phno;
    char sex[10];
    char profession[100];
};

struct Patient patients[MAX_PATIENTS];
struct MedicalRecord records[MAX_PATIENTS];
struct prescription presc[MAX_PATIENTS];
struct Doctor doc[MAX_PATIENTS];
struct Admin admin[MAX_PATIENTS];

int patientCount = 0;
int recordCount = 0;
int prescount = 0;
int doccount = 0;
int admcount = 0;

/*Files used :
1. C:\Users\\Desktop\\medicalRecords.txt
2. C:\\Users\\Desktop\\patients.txt
3. dotxt
4. C:\\Users\\adm.txt
5. C:\\Usersa\\prescriptions.txt
*/
void listMedicalRecords() {


    printf("\n--- Patient List ---\n");

    for (int i = 0; i < recordCount; i++) {

            printf("Record Id: %d\n", records[i].recordId);
            printf("Patient Id: %d\n", records[i].patientId);
            printf("Name: %s\n", records[i].patientName);
            printf("Creation Date: %s\n", records[i].creationDate);
            printf("Medical History: %s\n", records[i].medicalHistory);

        printf("--------------------\n");
    }
}

void loadMedicalRecordFromFile() {
    FILE *file = fopen("C:\\Users\\Desktop\\medicalRecords.txt", "r");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read record data from the file
    while (fscanf(file, "%d,%d,%[^,],%[^,],%[^\n]\n", &records[recordCount].recordId,
                  &records[recordCount].patientId, records[recordCount].patientName,
                  records[recordCount].creationDate, records[recordCount].medicalHistory
                  ) == 5)
                /*== 5: This is the condition that checks if fscanf successfully read all 5 expected values from the file.
                 If it successfully reads all 5 values, the condition will be true (equal to 5).*/
                {
                    recordCount++;
                }
                printf("%d\n",recordCount);

    fclose(file);
    listMedicalRecords();
}

void listPatientRecords() {


    printf("\n--- Patient List ---\n");

    for (int i = 0; i < patientCount; i++) {

            printf("Id: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Address: %s\n", patients[i].address);
            printf("Age: %d\n", patients[i].age);
            printf("Sex: %s\n", patients[i].sex);
            printf("Disease: %s\n", patients[i].disease);

        printf("--------------------\n");
    }
}

void loadPatientsFromFile() {
    FILE *file = fopen("C:\\Users\\Desktop\\patients.txt", "r");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read patient data from the file
    while (fscanf(file, "%d,%[^,],%[^,],%d,%[^,],%[^\n]\n", &patients[patientCount].id,
                  &patients[patientCount].name, &patients[patientCount].address,
                  &patients[patientCount].age, &patients[patientCount].sex,
                  &patients[patientCount].disease) == 6) {
        patientCount++;
    }
    printf("%d\n",patientCount);

    fclose(file);
    listPatientRecords();
}

void savePatientsToFile() {
    FILE *file = fopen("C:\\Users\\Desktop\\patients.txt", "a");

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
    FILE *file = fopen("C:\\Users\\Desktop\\medicalRecords.txt", "a");

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
    savePatientsToFile();
}
void addMedicalRecord() {
    struct MedicalRecord record;
    int id=0,idTrue=0;

    FILE *file = fopen("C:\\Users\\Desktop\\patients.txt", "r");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // read patient data to the file
    while (fscanf(file, "%d,%[^,],%[^,],%d,%[^,],%[^\n]\n", &patients[patientCount].id,
                  &patients[patientCount].name, &patients[patientCount].address,
                  &patients[patientCount].age, &patients[patientCount].sex,
                  &patients[patientCount].disease) == 6) {
        patientCount++;
    }

    fclose(file);

    printf("Enter record ID: ");
    scanf("%d", &record.recordId);
    getchar();  // Consume newline character
    /*verif start*/
   do
   {
    printf("Enter patientID: ");
    scanf("%d", &id);
    for (int i = 0; i <= patientCount; i++) {
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
    saveMedicalRecordToFile();
}

void saveDocToFile() {
    FILE *file = fopen("C:\\Users\\Desktop\\doc.txt", "a");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Write doctor's data to the file
    for (int i = 0; i < doccount; i++) {
        fprintf(file, "%d,%s,%d,%s,%s\n", doc[i].id, doc[i].name, doc[i].phno,
                doc[i].specializtion, doc[i].sex);
    }

    fclose(file);
}

void addDoc() {
    struct Doctor docs;

    printf("Enter Doctor's ID: ");
    scanf("%d", &docs.id);
    getchar();  // Consume newline character

    printf("Enter Doctor's name: ");
    fgets(docs.name, sizeof(docs.name), stdin);
    docs.name[strcspn(docs.name, "\n")] = '\0';  // Remove newline character

    printf("Enter Doctor's Phone number : ");
    scanf("%d", &docs.phno);
    getchar();  // Consume newline character

    printf("Enter Doctor's specialization : ");
    fgets(docs.specializtion, sizeof(docs.specializtion), stdin);
    docs.specializtion[strcspn(docs.specializtion, "\n")] = '\0';  // Remove newline character

    printf("Enter Doctor's sex: ");
    fgets(docs.sex, sizeof(docs.sex), stdin);
    docs.sex[strcspn(docs.sex, "\n")] = '\0';  // Remove newline character

    doc[doccount++] = docs;

    printf("Doctor added successfully.\n");
    saveDocToFile();
}

void saveadmToFile() {
    FILE *file = fopen("C:\\Users\\Desktop\\adm.txt", "a");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Write Admin's data to the file
    for (int i = 0; i < admcount; i++) {
        fprintf(file, "%d,%s,%d,%s,%s\n", admin[i].id, admin[i].name, admin[i].phno,admin[i].sex,admin[i].profession);
    }
    fclose(file);
}

void addAdmin() {
    struct Admin adm;

    printf("Enter Admin's ID: ");
    scanf("%d", &adm.id);
    getchar();  // Consume newline character

    printf("Enter Admin's name: ");
    fgets(adm.name, sizeof(adm.name), stdin);
    adm.name[strcspn(adm.name, "\n")] = '\0';  // Remove newline character

    printf("Enter Admin's Phone number : ");
    scanf("%d", &adm.phno);
    getchar();  // Consume newline character

    printf("Enter Admin's sex: ");
    fgets(adm.sex, sizeof(adm.sex), stdin);
    adm.sex[strcspn(adm.sex, "\n")] = '\0';  // Remove newline character

    printf("Enter Admin's profession : ");
    fgets(adm.profession, sizeof(adm.profession), stdin);
    adm.profession[strcspn(adm.profession, "\n")] = '\0';  // Remove newline character

    admin[admcount++] = adm;

    printf("Admin added successfully.\n");
    saveadmToFile();
}

int search(int opt,int p_id) {

    //SCREEN 3
    for(int i = 0;i<=100;i++)
            printf("*");
        printf("\n");
        for(int i = 0; i<=64;i++)
        {
            printf(" ");
            if(i==31)
                printf("---- HOSPITAL MANAGEMENT SYSTEM ----");
        }
        printf("\n");


    int found = 0;
    switch (opt)
    {
    case 1:;
        FILE *file1 = fopen("C:\\Users\\Desktop\\patients.txt", "r");

        if (file1 == NULL) {
            printf("Failed to open the file.\n");
        }

        // Read patient data from the file
        while (fscanf(file1, "%d,%[^,],%[^,],%d,%[^,],%[^\n]\n", &patients[patientCount].id,
                    &patients[patientCount].name, &patients[patientCount].address,
                    &patients[patientCount].age, &patients[patientCount].sex,
                    &patients[patientCount].disease) == 6) {
            patientCount++;
        }
        fclose(file1);

        for (int i = 0; i <= patientCount; i++) {
        if (patients[i].id == p_id) {
            for(int i = 0; i<=86;i++)
            {
                printf(" ");
                if(i==43)
                    printf("P A T I E N T");
            }
            printf("\n");
            for(int i = 0;i<=100;i++)
                printf("*");
            printf("\n");

            printf("ID: %d\t\t\t\t\t\t", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Address: %s\t\t\t\t", patients[i].address);
            printf("Age: %d\t\t", patients[i].age);
            printf("Sex: %s\n", patients[i].sex);
            printf("Disease Description: %s\n", patients[i].disease);
            found = 1;
            break;
        }
        }

        if (!found) {
            printf("No Patient found with ID: %d\n", p_id);
            return found;
        }
        break;
     case 2:;

        FILE *file2 = fopen("C:\\Users\\Desktop\\doc.txt", "r");

        if (file2 == NULL) {
            printf("Failed to open the file.\n");
        }

        // Read doc data from the file
        while (fscanf(file2, "%d,%[^,],%d,%[^,],%[^\n]\n", &doc[doccount].id,
                    &doc[doccount].name, &doc[doccount].phno,
                    &doc[doccount].sex,
                    &doc[doccount].specializtion) == 5) {
            doccount++;
        }
        fclose(file2);

        for (int i = 0; i <= doccount; i++) {
        if (doc[i].id == p_id) {
            for(int i = 0; i<=88;i++)
            {
                printf(" ");
                if(i==44)
                    printf("D O C T O R");
            }
            printf("\n");
            for(int i = 0;i<=100;i++)
                printf("*");
            printf("\n");

            printf("ID: %d\t\t\t\t\t\t", doc[i].id);
            printf("Name: %s\n", doc[i].name);
            printf("Ph. no. : %d\t\t\t\t", doc[i].phno);
            printf("Sex: %s\n", doc[i].sex);
            printf("Specialization: %s\n", doc[i].specializtion);
            found = 1;
            break;
        }
        }

        if (!found) {
            printf("No Doctor found with ID: %d\n",p_id);
            break;
        }
        break;
     case 3:;
        FILE *file3 = fopen("C:\\Users\\Desktop\\adm.txt", "r");

        if (file3 == NULL) {
            printf("Failed to open the file.\n");
        }

        // Read patient data from the file
        while (fscanf(file3, "%d,%[^,],%d,%[^,],%[^,],%[^\n]\n", &admin[admcount].id,
                    &admin[admcount].name, &admin[admcount].phno,
                    &admin[admcount].sex,
                    &admin[admcount].profession) == 5) {
            admcount++;
        }
        fclose(file3);

        for (int i = 0; i <= admcount; i++) {
        if (admin[i].id == p_id) {
            for(int i = 0; i<=90;i++)
            {
                printf(" ");
                if(i==45)
                    printf("A D M I N");
            }
            printf("\n");
            for(int i = 0;i<=100;i++)
                printf("*");
            printf("\n");

            printf("ID: %d\t\t\t\t\t\t", admin[i].id);
            printf("Name: %s\n", admin[i].name);
            printf("Ph. no. : %d\t\t\t\t", admin[i].phno);
            printf("Sex: %s\n", admin[i].sex);
            printf("Profession: %s\n", admin[i].profession);
            found = 1;
            break;
        }
        }

        if (found==0) {
            printf("No Admin found with ID: %d\n", p_id);
            break;
        }
        break;
    default:
        break;
    }
    return found;
}
void med_his()
{
    FILE *file = fopen("C:\\Users\\Desktop\\medicalRecords.txt", "r");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read record data from the file
    while (fscanf(file, "%d,%d,%[^,],%[^,],%[^\n]\n", &records[recordCount].recordId,
                    &records[recordCount].patientId, &records[recordCount].patientName,
                    &records[recordCount].creationDate, &records[recordCount].medicalHistory) == 5)
                {
                    recordCount++;
                }

    fclose(file);

    int recordMedicalId;
    printf("Enter record Medical ID: ");
    scanf("%d", &recordMedicalId);
    for(int i = 0; i<recordCount;i++)
    {
    if (records[i].recordId == recordMedicalId) {
            printf("medical History: %s\n", records[i].medicalHistory);
    }
}
}
void gen_prescription()
{
    struct prescription pres;

    printf("Enter patient ID: ");
    scanf("%d", &pres.id);
    getchar();  // Consume newline character

    printf("Enter date(dd/mm/yy): ");
    fgets(pres.date, sizeof(pres.date), stdin);
    pres.date[strcspn(pres.date, "\n")] = '\0';  // Remove newline character

    printf("Enter patient name: ");
    fgets(pres.name, sizeof(pres.name), stdin);
    pres.name[strcspn(pres.name, "\n")] = '\0';  // Remove newline character

    printf("Enter patient address: ");
    fgets(pres.address, sizeof(pres.address), stdin);
    pres.address[strcspn(pres.address, "\n")] = '\0';  // Remove newline character

    printf("Enter patient age: ");
    scanf("%d", &pres.age);
    getchar();  // Consume newline character

    printf("Enter patient sex: ");
    fgets(pres.sex, sizeof(pres.sex), stdin);
    pres.sex[strcspn(pres.sex, "\n")] = '\0';  // Remove newline character

    printf("Enter patient disease description: ");
    fgets(pres.disease, sizeof(pres.disease), stdin);
    pres.disease[strcspn(pres.disease, "\n")] = '\0';  // Remove newline character

    printf("What is the suggested medication?\n");
    fgets(pres.med, sizeof(pres.med), stdin);
    pres.med[strcspn(pres.med, "\n")] = '\0';

    printf("What is the suggested lab test?\n");
    fgets(pres.test, sizeof(pres.test), stdin);
    pres.test[strcspn(pres.test, "\n")] = '\0';

    presc[prescount++] = pres;

    FILE *file = fopen("C:\\Users\\Desktop\\prescriptions.txt", "a");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    for (int i = 0; i < prescount; i++) {
        fprintf(file, "%d,%s,%s,%s,%d,%s,%s,%s,%s,\n", presc[i].id , presc[i].date , presc[i].name, presc[i].address,
                presc[i].age, presc[i].sex, presc[i].disease, presc[i].med, presc[i].test);
    }

    fclose(file);
}

void show_prescription()
{
    struct prescription pres;

    for(int i = 0; i<=66;i++)
    {
        printf(" ");
        if(i==33)
            printf("---- P R E S C R I P T I O N ----");
    }
    printf("\n");
    FILE *file = fopen("C:\\Users\\Desktop\\prescriptions.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^\n],\n", &presc[prescount].id ,
                        &presc[prescount].date , &presc[prescount].name, &presc[prescount].address,
                        &presc[prescount].age, &presc[prescount].sex, &presc[prescount].disease,
                        &presc[prescount].med, &presc[prescount].test) == 9) {
                    prescount++;
                    }

    int patient_Id;
    printf("Enter your patient ID: ");
    scanf("%d", &patient_Id);
    for(int i = 0; i<=prescount;i++)
    {
        if (presc[i].id == patient_Id) {
            printf("Patient Id: %d\n", presc[i].id);
            printf("Date : %s\n",presc[i].date);
            printf("Name: %s\n", presc[i].name);
            printf("Address: %s\n", presc[i].address);
            printf("Age : %d\n", presc[i].age);
            printf("Sex: %s\n", presc[i].sex);
            printf("Disease : %s\n", presc[i].disease);
            printf("Suggested Medication : %s\n",presc[i].med);
            printf("Lab Tests suggested : %s\n",presc[i].test);
        }
    }
    fclose(file);
    printf("--------------------\n");

}

void searchAndModifyRecord() {
    int recordMedicalId;
    int id =0,idTrue=0;

    printf("Enter record Medical ID: ");
    scanf("%d", &recordMedicalId);

    int found = 0;
    FILE *file1 = fopen("C:\\Users\\Desktop\\medicalRecords.txt", "a+");

    if (file1 == NULL) {
        printf("Failed to open the file.\n");
    }

        // Read patient data from the file
        while (fscanf(file1, "%d,%d,%[^,],%[^,],%[^\n]\n", &records[recordCount].recordId,
                    &records[recordCount].patientId, &records[recordCount].patientName,
                    &records[recordCount].creationDate, &records[recordCount].medicalHistory) == 5)
                    {recordCount++;}
        fclose(file1);

    for (int i = 0; i <= recordCount; i++) {
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
                        FILE *file = fopen("C:\\Users\\Desktop\\patients.txt", "r");

                        if (file == NULL) {
                            printf("Failed to open the file.\n");
                            return;
                        }

                        // read patient data to the file
                        while (fscanf(file, "%d,%[^,],%[^,],%d,%[^,],%[^\n]\n", &patients[patientCount].id,
                                    &patients[patientCount].name, &patients[patientCount].address,
                                    &patients[patientCount].age, &patients[patientCount].sex,
                                    &patients[patientCount].disease) == 6) {
                            patientCount++;
                        }

                        fclose(file);
                        printf("Enter patientID: ");
                        scanf("%d", &id);
                        for (int j = 0; j <= patientCount; j++) {
                            if (patients[j].id==id)
                            {
                                records[i].patientId=id;
                                getchar(); // Consume newline character
                                idTrue=1;
                                strcpy(records[i].patientName,patients[j].name);
                            }
                        }
                    } while (idTrue != 1 );
                        /*verify ends*/

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

void deletePatient() {
    int patientId;
    printf("Enter patient ID: ");
    scanf("%d", &patientId);

    int found = 0;

    FILE *file = fopen("C:\\Users\\Desktop\\patients.txt", "a+");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read patient data from the file
    while (fscanf(file, "%d,%[^,],%[^,],%d,%[^,],%[^\n]\n", &patients[patientCount].id,
                  &patients[patientCount].name, &patients[patientCount].address,
                  &patients[patientCount].age, &patients[patientCount].sex,
                  &patients[patientCount].disease) == 6) {
        patientCount++;
    }

    fclose(file);

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

    FILE *file1 = fopen("C:\\Users\\Desktop\\medicalRecords.txt", "a+");

    if (file1 == NULL) {
        printf("Failed to open the file.\n");
    }

        // Read patient data from the file
        while (fscanf(file1, "%d,%d,%[^,],%[^,],%[^\n]\n", &records[recordCount].recordId,
                    &records[recordCount].patientId, &records[recordCount].patientName,
                    &records[recordCount].creationDate, &records[recordCount].medicalHistory) == 5)
                    {recordCount++;}
        fclose(file1);

    for (int i = 0; i < recordCount; i++) {
        if (records[i].recordId == medicalRecordId) {
            found = 1;

            printf("medical Record Found!\n");
            printf("record Id: %d\n", records[i].recordId);
            printf("patient Id: %d\n", records[i].patientId);
            printf("patient Name: %s\n", records[i].patientName);
            printf("creation Date: %s\n", records[i].creationDate);
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

/*LIST OF FUNCTIONS
1.loadMedicalRecordFromFile()
2.loadPatientsFromFile()
3.savePatientsToFile()
4.saveMedicalRecordToFile()
5.addPatient()
6.addMedicalRecord()
7.addDoc()
8.saveDocToFile()
9.addAdmin()
10.saveadmToFile()
11.search(int opt,int p_id)
12.med_his()
13.gen_prescription()
14.show_prescription()
15.searchAndModifyRecord()
16.listPatientsAlphabetically()
17.listMedicalRecords()
18.deletePatient()
19.deleteMedicalRecord()
20.listPatientRecords()
*/

int main()
{
    //SCREEN 1
    for(int i = 0;i<=100;i++)
        printf("*");
    printf("\n");
    for(int i = 0; i<=64;i++)
    {
        printf(" ");
        if(i==31)
            printf("---- HOSPITAL MANAGEMENT SYSTEM ----");
    }
    printf("\n");
    for(int i = 0; i<=86;i++)
    {
        printf(" ");
        if(i==43)
            printf("W E L C O M E");
    }
    printf("\n");
    for(int i = 0;i<=100;i++)
        printf("*");
    printf("\n");
    for(int i = 0; i<=80;i++)
    {
        printf(" ");
        if(i==43)
            printf("WHO  ARE  YOU ?");
    }
    printf("\n");
    for(int i = 0; i<=76;i++)
    {
        printf(" ");
        if(i==38)
            printf("Enter that serial number");
    }
    printf("\n");

    int opt1,opt2;
    for(int i = 0; i<=72;i++)
    {
        printf(" ");
        if(i==22)
            printf("1.PATIENT\t\t2.DOCTOR\t\t3.ADMIN");
    }
    printf("\n");
    scanf("%d",&opt1);
    for(int i = 0;i<=100;i++)
        printf("*");
    printf("\n\n\n\n\n");

    //SCREEN 2

    for(int i = 0;i<=100;i++)
        printf("*");
    printf("\n");
    for(int i = 0; i<=64;i++)
    {
        printf(" ");
        if(i==31)
            printf("---- HOSPITAL MANAGEMENT SYSTEM ----");
    }
    for(int i = 0; i<=93;i++)
    {
        printf(" ");
        if(i==46)
            printf("LOG IN");
    }
    printf("\n");
    for(int i = 0;i<=100;i++)
        printf("*");
    printf("\n");
    int personal_id,id,opt3;
    printf("Enter the you personal id : ");
    scanf("%d",&personal_id);
    do
    {
        switch (opt1)
        {
        case 1:
            if(search(opt1,personal_id) == 0)
                break;
            else
                {
                    printf("Which task do you wish to perform ?\n");
                    printf("1. Show Medical History\n2. Show the latest prescription\n(Enter 0 to exit)\n");
                    scanf("%d",&opt2);
                    switch (opt2)
                    {
                    case 1:
                        med_his();
                        break;
                    case 2:
                        show_prescription();
                        break;
                    default:
                        break;
                    }
                }
            break;
        case 2:
            if(search(opt1,personal_id) == 0)
                break;
            else
                {
                    printf("Which task do you wish to perform ?\n");
                    printf("1.Add a new patient\n");
                    printf("2.Search a patient using id\n");
                    printf("3.Delete patient's details\n");
                    printf("4.See details of all the patients\n");
                    printf("5.Generate Prescription\n");
                    printf("6.Show Medical History of a patient\n");
                    printf("(Enter 0 to exit)\n");
                    scanf("%d",&opt2);
                    switch (opt2)
                    {
                    case 1:
                        addPatient();
                        break;
                    case 2:
                        printf("Enter the Id : ");
                        scanf("%d",&id);
                        search(1,id);
                        break;
                    case 3:
                        deletePatient();
                        break;
                    case 4:
                        loadPatientsFromFile();
                        break;
                    case 5:
                        gen_prescription();
                        break;
                    case 6:
                        med_his();
                        break;
                    default:
                        break;
                    }
                }
            break;
        case 3:
            if(search(opt1,personal_id) == 0)
                break;
            else
                {
                    printf("Which task do you wish to perform ?\n");
                    printf("1.Search a person using id\n");
                    printf("2.List all patients\n");
                    printf("3.Add a new medical record\n");
                    printf("4.See medical records of all the patients\n");
                    printf("5.Delete a medical record\n");
                    printf("6.Search and Modify patient's record\n");
                    printf("7.Add a Doctor\n");
                    printf("8.Add an Admin person\n");
                    printf("(Enter 0 to exit)\n");
                    scanf("%d",&opt2);
                    switch (opt2)
                    {
                    case 1:
                        printf("Whom do you wish to search :\n1.Patient\t2.Doctor\t3.Admin\n");
                        scanf("%d",&opt3);
                        printf("Enter the Id : ");
                        scanf("%d",&id);
                        search(opt3,id);
                        break;
                    case 2:
                        loadPatientsFromFile();
                        break;
                    case 3:
                        addMedicalRecord();
                        break;
                    case 4:
                        loadMedicalRecordFromFile();
                        break;
                    case 5:
                        deleteMedicalRecord();
                        break;
                    case 6:
                        searchAndModifyRecord();
                        break;
                    case 7:
                        addDoc();
                        break;
                    case 8:
                        addAdmin();
                        break;
                    default:
                        break;
                    }
                }
            break;
        default:
            break;
        }

        for(int i = 0;i<=100;i++)
        printf("*");
        printf("\n\n\n\n\n");
    }while(opt2!=0);

    for(int i = 0;i<=100;i++)
        printf("*");
    printf("\n");
}
