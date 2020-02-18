/*
 ============================================================================
 Name        : CProgramming_Test_Sunbeam.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void displayMyDetails();
void displayMainMenu();
void registerStaff();
void printfStaffDetails();
void printModuleDetails();
void getStaffDetails();
void getModuleDetails();
void staffMenu();
void adminMenu();
int staffMenuList();
int adminMenuList();
void displayCourseList();
void addCourse();
void addModule();
void displayStaffDetails();
void displayModuleDetails();
void findModuleByNameAndCourse();
void editModuleByID();
void deleteModuleById();
void modulesPerCourse();
void modulesPerCategory();
void workEntry();
void getWorkEntryData();
void getWorkEntryDetails();
void listPendingEntries();
void printWorkEntryDetails();
void approveEntry();
void listApprovedEntries();
void listPendingEntriesWithModuleName();


struct Staff {
	int id;
	char name[20], email[20], mobile[11];
}staff;

struct Module{
	int id,duration;
	char name[20],course[6];
}module;

struct Date {
	int day, month, year;
};

struct Time {
	int hours, mins, seconds;
};

struct Entry{
	int id,staff_id,module_id,duration;
	int status;
	struct Date work_date;


	struct Time start_time;
}entry;

int main (void){
	displayMyDetails();
	displayMainMenu();
	return 0;
}

void displayMainMenu(){
	int choice;
	while (1) {
		printf("MAIN MENU\n");
		printf("0. Exit\n");
		printf("1. Register Staff\n");
		printf("2. Staff\n");
		printf("3. Admin\n");
		printf(" Enter Choice : ");
		scanf("%d", &choice);
		switch (choice) {
		case 0:
			exit(0);
			break;
		case 1:
			registerStaff();
			break;
		case 2:
			staffMenu();
			break;
		case 3:
			adminMenu();
			break;
		}
	}

}

void adminMenu() {
	int choice;
	while(1){
		printf("ADMIN MENU\n");
	choice = adminMenuList();
		switch (choice) {
		case 0:
			displayMainMenu();
			break;
		case 1:
			displayCourseList();
			break;
		case 2:
			addCourse();
			break;
		case 3:
			displayModuleDetails();
			break;
		case 4:
			findModuleByNameAndCourse();
			break;
		case 5:
			editModuleByID();
			break;
		case 6:
			deleteModuleById();
			break;
		case 7:
			listPendingEntries();
			break;
		case 8:
			listApprovedEntries();
			break;
		case 9:
			break;
		case 10:
			addModule();
			break;
		}
	}
}

void staffMenu() {
	int choice;
	while(1){
		printf("STAFF MENU\n");
	choice = staffMenuList();
		switch (choice) {
		case 0:
			displayMainMenu();
			break;
		case 1:
			displayCourseList();
			break;
		case 2:
			modulesPerCourse();
			break;
		case 3:
			modulesPerCategory();
			break;
		case 4:
			workEntry();
			break;
		case 5:
			break;
		}
	}
}

int adminMenuList(){
	int choice;
	printf("0. Exit\n");
	printf("1. List Courses\n");
	printf("2. Add Course\n");
	printf("3. List all modules\n");
	printf("4. Find modules by course and name\n");
	printf("5. Edit modules\n");
	printf("6. Delete module\n");
	printf("7. List pending entries\n");
	printf("8. List approved entries\n");
	printf("9. Approve entry\n");
	printf("10. Add module\n");
	printf("Enter choice : ");
	scanf("%d",&choice);
	return choice;
}

int staffMenuList(){
	int choice;
	printf("0. Exit\n");
	printf("1. List Courses\n");
	printf("2. Modules per Course(Sorted by name)\n");
	printf("3. Modules Per Category(Sorted By Duration\n");
	printf("4. Work Entry\n");
	printf("5. List pending Entries\n");
	printf("6. List approved entries\n");
	printf(" Enter Choice : ");
	scanf("%d",&choice);
	return choice;
}

void addCourse() {
	FILE *fp;
	fp = fopen("courses.txt", "a");
	if (fp != NULL) {
		char courseName[6];
		printf("Enter Course name : ");
		scanf("%s", courseName);
		fputs(courseName, fp);
		printf("Course Added Successfully");
		fclose(fp);
		// To add New line character
		fp = fopen("courses.txt", "a");
		fputs("\n", fp);
		fclose(fp);
	}else
		printf("Error In File Opening");
}

void addModule() {
	FILE *fp;
	fp = fopen("module.db", "ab");
	if (fp != NULL) {
		getModuleDetails();
		fwrite(&module, sizeof(module), 1, fp);
		fclose(fp);
		printf("\n\n");
		//displayModuleDetails();
	} else
		printf("Error In File Opening");
}

void displayCourseList() {
	FILE *fp;
	fp = fopen("courses.txt", "r");
	if (fp != NULL) {
		char courseName[6];
		printf("Course List: \n");
		while (fgets(courseName, 6, fp) != NULL)
			printf("%s", courseName);
		fclose(fp);
	} else
		printf("Error In File Opening");
}

void displayMyDetails(){
	printf("Student Name : Shivam Palaskar\n");
	printf("Roll Number : 36106\n");
	printf("Center Name : SunBeam\n");
	printf("Course Name : PG-DAC\n");
	printf("Group Name : NULL\n");
	printf("Mission Statement : I will NEVER QUIT\n\n");
}


void registerStaff() {
	FILE *fp;
	fp = fopen("staff.db", "ab");
	if (fp != NULL) {
		getStaffDetails();
		fwrite(&staff, sizeof(staff), 1, fp);
		fclose(fp);
		//displayStaffDetails();
	} else
		printf("Error In File Opening");
}

void displayStaffDetails() {
	FILE *fp;
	fp = fopen("staff.db", "rb");
	if (fp != NULL) {
		while (fread(&staff, sizeof(staff), 1, fp) != '\0')
			printfStaffDetails();
		fclose(fp);
	}else
		printf("Error In File Opening");

}

void getStaffDetails() {
	fflush(stdin);
	printf("Enter Staff Details\n");
	printf("Id : ");
	scanf("%d", &staff.id);
	printf("Name : ");
	scanf("%s", staff.name);
	printf("Email : ");
	scanf("%s", staff.email);
	printf("Mobile No. :");
	scanf("%s", staff.mobile);
}

void displayModuleDetails() {
	FILE *fp;
	fp = fopen("module.db", "rb");
	if (fp != NULL) {
		while (fread(&module, sizeof(module), 1, fp) != '\0')
			printModuleDetails();
		fclose(fp);
	}else
		printf("Error In File Opening");
}

void findModuleByNameAndCourse() {
	FILE *fp;
	fp = fopen("module.db", "rb");
	if (fp != NULL) {
		char name[20], course[6];
		int flag = 0;
		printf("Enter Course Name (Complete) : ");
		scanf("%s", course);
		printf("Enter Module Name (Can be Partial) : ");
		scanf("%s", name);
		while (fread(&module, sizeof(module), 1, fp) != '\0') {
			if (strncmp(module.name, name, 2) == 0
					&& strcasecmp(module.course, course) == 0) {
				printf("Module Found :\n");
				printModuleDetails();
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			printf("Module Not Found\n");
		fclose(fp);
	}else
		printf("Error In File Opening");
}

void editModuleByID(){
	FILE *fp;
	fp = fopen("module.db", "rb+");
	if (fp != NULL) {
		int id, flag = 0;
		printf("Enter Module ID : ");
		scanf("%d", &id);
		while (fread(&module, sizeof(module), 1, fp) != '\0') {
			if (module.id == id) {
				printf("Module Found :\n");
				getModuleDetails();
				fseek(fp, -sizeof(module), SEEK_CUR);
				fwrite(&module, sizeof(module), 1, fp);
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			printf("Module Not Found\n");
		else
			printf("\nModule Modified Successfully");
		fclose(fp);
	}else
		printf("Error In File Opening");

}

void deleteModuleById() {
	FILE *fp;
	fp = fopen("module.db", "rb+");
	if (fp != NULL) {
		int id, flag = 0;
		printf("Enter Module ID : ");
		scanf("%d", &id);
		FILE *ft = fopen("TempModuleFile.dat", "wb");

		while (fread(&module, sizeof(module), 1, fp)) {
			if (module.id != id) {
				fwrite(&module, sizeof(module), 1, ft);
			}
			if (module.id == id)
				flag = 1;
		}
		fclose(fp);
		fclose(ft);
		remove("module.db");
		rename("TempModuleFile.dat", "module.db");
		if (flag == 1)
			printf("Module is deleted Successful");
		else
			printf("\nNo such Module is present");
	}else
		printf("Error In File Opening");

}

typedef struct ModuleCat{
		int id,duration;
		char name[20],course[6];
	}MODULECAT;

int cmpfunc(const void * s1, const void * s2) {
	int l = *((MODULECAT *)s1)->name;
	int r = *((MODULECAT *)s2)->name;
	return (l - r);
}

void modulesPerCourse(){
	char course[6];
	printf("Enter Course Name (Complete) : ");
	scanf("%s", course);

	FILE *fp;
	fp = fopen("module.db", "rb");
	if (fp != NULL) {
		int flag = 0, index = 0, len = 0;

		while (fread(&module, sizeof(module), 1, fp) != '\0') {
			if (strcasecmp(module.course, course) == 0)
				len++;
		}
		rewind(fp);
		MODULECAT moduleArr[len];

		while (fread(&module, sizeof(module), 1, fp) != '\0') {
			if (strcasecmp(module.course, course) == 0) {
				moduleArr[index].id = module.id;
				strcpy(moduleArr[index].name, module.name);
				strcpy(moduleArr[index].course, module.course);
				moduleArr[index].duration = module.duration;
				index++;
				flag = 1;
			}
		}
		if (flag == 0)
			printf("Module Not Found\n");
		fclose(fp);
		int len1 = sizeof(moduleArr) / sizeof(moduleArr[0]);
		qsort(moduleArr, len1, sizeof(MODULECAT), cmpfunc);

		for (int i = 0; i < len; i++) {
			printf("ID : %d\n", moduleArr[i].id);
			printf("Name : %s\n", moduleArr[i].name);
			printf("Course : %s\n", moduleArr[i].course);
			printf("Duration : %d\n", moduleArr[i].duration);
		}
	}else
		printf("Error In File Opening");

}

int cmpfunc1(const void * s1, const void * s2) {
	int l = ((MODULECAT *)s1)->duration;
	int r = ((MODULECAT *)s2)->duration;
	return (l - r);
}

void modulesPerCategory() {
	char course[6];
	printf("Enter Course Name (Complete) : ");
	scanf("%s", course);

	FILE *fp;
	fp = fopen("module.db", "rb");
	if (fp != NULL) {
		int flag = 0, index = 0, len = 0;

		while (fread(&module, sizeof(module), 1, fp) != '\0') {
			if (strcasecmp(module.course, course) == 0)
				len++;
		}
		rewind(fp);
		MODULECAT moduleArr[len];

		while (fread(&module, sizeof(module), 1, fp) != '\0') {
			if (strcasecmp(module.course, course) == 0) {
				moduleArr[index].id = module.id;
				strcpy(moduleArr[index].name, module.name);
				strcpy(moduleArr[index].course, module.course);
				moduleArr[index].duration = module.duration;
				index++;
				flag = 1;
			}
		}
		if (flag == 0)
			printf("Module Not Found\n");
		fclose(fp);
		int len1 = sizeof(moduleArr) / sizeof(moduleArr[0]);
		qsort(moduleArr, len1, sizeof(MODULECAT), cmpfunc1);

		for (int i = 0; i < len; i++) {
			printf("ID : %d\n", moduleArr[i].id);
			printf("Name : %s\n", moduleArr[i].name);
			printf("Course : %s\n", moduleArr[i].course);
			printf("Duration : %d\n", moduleArr[i].duration);
		}
	}else
		printf("Error In File Opening");

}

void getModuleDetails(){
	fflush(stdin);
	printf("Enter Module Details\n");
	printf("ID : ");
	scanf("%d",&module.id);
	printf("Name : ");
	scanf("%s",module.name);
	printf("Course : ");
	scanf("%s",module.course);
	printf("Duration : ");
	scanf("%d",&module.duration);
}

void printfStaffDetails(){
	printf("ID : %d\n",staff.id);
	printf("name : %s\n",staff.name);
	printf("email : %s\n",staff.email);
	printf("mobile : %s\n",staff.mobile);
}

void printModuleDetails() {
	printf("ID : %d\n", module.id);
	printf("Name : %s\n", module.name);
	printf("Course : %s\n", module.course);
	printf("Duration : %d\n", module.duration);
}

void workEntry(){
	getWorkEntryData();
}

void getWorkEntryData(){
	FILE *fp;
	fp = fopen("entries.db", "ab");
	if (fp != NULL) {
		getWorkEntryDetails();
		fwrite(&entry, sizeof(entry), 1, fp);
		fclose(fp);
	} else
		printf("Error In File Opening");
}

void getWorkEntryDetails() {
	entry.status=0;
	fflush(stdin);
	printf("Enter Work Entry Details\n");
	printf("ID : ");
	scanf("%d", &entry.id);
	printf("Staff ID : ");
	scanf("%d", &entry.staff_id);
	printf("Module ID : ");
	scanf("%d", &entry.module_id);
	printf("Duration : ");
    scanf("%d", &entry.duration);
    printf("Date : In DD/MM/YYY format only");
    scanf("%d / %d / %d",&entry.work_date.day,&entry.work_date.month,&entry.work_date.year);
    printf("Time : In HH-MM-SS format only");
    scanf("%d / %d / %d",&entry.start_time.hours,&entry.start_time.mins,&entry.start_time.seconds);
}

void listPendingEntries() {
	FILE *fp;
	fp = fopen("entries.db", "rb");
	int flag =0;
	if (fp != NULL) {
		while(fread(&entry, sizeof(entry), 1, fp)!='\0'){
			if(entry.status==0){
				printWorkEntryDetails();
				flag =1;
			}
		}
		if(flag==0){
			printf("No Pending Entries\n");
		}
		fclose(fp);
	} else
		printf("Error In File Opening");
}

void listApprovedEntries() {
	FILE *fp;
	fp = fopen("entries.db", "rb");
	int flag = 0;
	if (fp != NULL) {
		while (fread(&entry, sizeof(entry), 1, fp) != '\0') {
			if (entry.status == 1) {
				printWorkEntryDetails();
				flag = 1;
			}
		}
		if (flag == 0) {
			printf("No Pending Entries\n");
		}
		fclose(fp);
	} else
		printf("Error In File Opening");
}

/*void approveEntry(){
	FILE *fp;
	fp = fopen("entries.db", "ab+");
	int flag = 0,id;
	printf("Enter Entry ID : ");
	scanf("%d",&id);
	if (fp != NULL) {
		while (fread(&entry, sizeof(entry), 1, fp) != '\0') {
			if (entry.id == id) {
				fseek(fp,-1, SEEK_CUR);
				entry.status=1;
				flag = 1;
			}
		}
		if (flag == 0) {
			printf("No Pending Entries\n");
		}else
			printf("Approved\n");
		fclose(fp);
	} else
		printf("Error In File Opening");
}*/

void printWorkEntryDetails(){
	printf("Id : %d\n",entry.id);
	printf("Staff ID : %d\n",entry.staff_id);
	printf("Module ID : %d\n",entry.module_id);
	printf("Duration : %d\n",entry.duration);
	printf("Date : %d/%d/%d\n",entry.work_date.day,entry.work_date.month,entry.work_date.year);
	printf("Time : %d/%d/%d\n",entry.start_time.hours,entry.start_time.mins,entry.start_time.seconds);
}

/*void listPendingEntriesWithModuleName() {
	FILE *fp,fp2;
	fp = fopen("entries.db", "rb");
	fp2 = fopen("module.db", "rb");
	int flag = 0;
	if (fp != NULL) {
		while (fread(&entry, sizeof(entry), 1, fp) != '\0') {
			if (entry.status == 0) {
				printWorkEntryDetails();
				while (fread(&module, sizeof(module), 1, fp2) != '\0'){
					if(module.id==entry.module_id)
						printf("Module Id : %d",module.id);
				}
				flag = 1;
			}
		}
		if (flag == 0) {
			printf("No Pending Entries\n");
		}
		fclose(fp);
	} else
		printf("Error In File Opening");
}*/
