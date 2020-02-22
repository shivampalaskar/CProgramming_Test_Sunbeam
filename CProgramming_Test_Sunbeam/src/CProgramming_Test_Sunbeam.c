/*
 ============================================================================
 Name        : CProgramming_Test_Sunbeam.c
 Author      : Shivam Palaskar
 Version     :
 Copyright   : Your copyright notice
 Description : Time sheet Application
 ============================================================================
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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


void displayMainMenu(){
	int choice;
	while (1) {
		printf("\nMAIN MENU\n");
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
		printf("\nADMIN MENU\n");
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
			approveEntry();
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
		printf("\nSTAFF MENU\n");
		fflush(stdin);
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
			listPendingEntryWithModuleName();
			break;
		case 6 :
			listApprovedEntryWithModuleName();
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
	printf("5. List pending Entries With Staff And Module\n");
	printf("6. List approved entries With Staff And Module\n");
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
		printf("===================");
		printf("\nCourse List: \n");
		while (fgets(courseName, 6, fp) != NULL)
			printf("%s", courseName);
		fclose(fp);
		printf("===================");
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
	fflush(stdin);
	scanf("%s", staff.name);
	printf("Email : ");
	fflush(stdin);
	scanf("%s", staff.email);
	printf("Mobile No. :");
	scanf("%s", staff.mobile);
}

void displayModuleDetails() {
	FILE *fp;
	fp = fopen("module.db", "rb");
	printf("===================\n");
	if (fp != NULL) {
		while (fread(&module, sizeof(module), 1, fp) != '\0')
			printModuleDetails();
		fclose(fp);
		printf("===================");
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
		printf("===================\n");
		while (fread(&module, sizeof(module), 1, fp) != '\0') {
			if (strncmp(module.name, name, 1) == 0
					&& strcasecmp(module.course, course) == 0) {
				printModuleDetails();
				flag = 1;
				//break;
			}
		}
		if (flag == 0)
			printf("Module Not Found\n");
		fclose(fp);
		printf("===================");
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

void changeStatus(struct Entry *ptr){
	ptr->duration=entry.duration;
	ptr->id=entry.id;
	ptr->module_id=entry.module_id;
	ptr->staff_id=entry.staff_id;
	ptr->start_time=entry.start_time;
	ptr->work_date=entry.work_date;
	ptr->status=1;
}

void approveEntry() {
	FILE *fp;
	fp = fopen("entries.db", "rb+");
	struct Entry entryCpy;
	if (fp != NULL) {
		int workId, flag = 0;
		printf("Enter Work ID : ");
		scanf("%d", &workId);
		while (fread(&entry, sizeof(entry), 1, fp) != '\0') {
			if (entry.id == workId) {
				printf("Entry Found :\n");
				changeStatus(&entryCpy);
				fseek(fp, -sizeof(entryCpy), SEEK_CUR);
				fwrite(&entryCpy, sizeof(entry), 1, fp);
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			printf("Entry Not Found\n");
		else
			printf("Entry Approved Successfully");
		fclose(fp);
	} else
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
	MODULECAT *p1 = (MODULECAT*) s1, *p2 = (MODULECAT*) s2;
	double diff = strcmp(p1->name, p2->name);
	return diff;
}

void modulesPerCourse(){
	char course[6];
	printf("\nEnter Course Name (Complete) : ");
	scanf("%s", course);
	printf("===================\n");
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
			printf("\nModule ID : %d\n", moduleArr[i].id);
			printf("Module Name : %s\n", moduleArr[i].name);
			printf("Course : %s\n", moduleArr[i].course);
			printf("Duration : %d\n", moduleArr[i].duration);
		}
		printf("===================");
	}else
		printf("Error In File Opening");

}

void listPendingEntries() {
	FILE *fp;
	fp = fopen("entries.db", "rb");
	int flag =0;
	printf("===================\n");
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
		printf("===================");
	} else
		printf("Error In File Opening");
}

void listApprovedEntries() {
	FILE *fp;
	fp = fopen("entries.db", "rb");
	int flag = 0;
	printf("===================\n");
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
		printf("===================");
	} else
		printf("Error In File Opening");
}

void printfStaff(int staff_id){
	FILE *fp_staff;
	fp_staff = fopen("staff.db", "rb");
	if (fp_staff != NULL) {
		while (fread(&staff, sizeof(staff), 1, fp_staff) != '\0') {
			if (staff.id == staff_id) {
				printf("Staff ID : %d\n", staff.id);
				printf("Staff Name : %s\n", staff.name);
			}
		}

	} else
		printf("Error In File Opening");
}

void printfModule(int module_id) {
	FILE *fp_module;
	fp_module = fopen("module.db", "rb");
	if (fp_module != NULL) {
		while (fread(&module, sizeof(module), 1, fp_module) != '\0') {
			if (module.id == module_id) {
				printf("Module Name : %s\n", module.name);
			}
		}
	} else
		printf("Error In File Opening");
}

void listPendingEntryWithModuleName() {
	int staff_id;
	printf("\nEnter Staff Id : ");
	scanf("%d",&staff_id);
	FILE *fp_workEntry,*fp_module,*fp_staff;
	int flag = 0;
	fp_workEntry = fopen("entries.db", "rb");
	printf("===================\n");
	if (fp_workEntry != NULL) {
		while (fread(&entry, sizeof(entry), 1, fp_workEntry) != '\0') {
			if (entry.status == 0 && entry.staff_id==staff_id) {
				printf("\nStatus : Pending\n");
				printfStaff(entry.staff_id);
				printfModule(entry.module_id);
				flag = 1;
			}
		}
		if (flag == 0) {
			printf("No Pending Entries\n");
		}
		fclose(fp_workEntry);
		printf("===================");
	} else
		printf("Error In File Opening");
}

void listApprovedEntryWithModuleName() {
	int staff_id;
	printf("\nEnter Staff Id : ");
	scanf("%d", &staff_id);
	FILE *fp_workEntry, *fp_module, *fp_staff;
	int flag = 0;
	fp_workEntry = fopen("entries.db", "rb");
	printf("===================\n");
	if (fp_workEntry != NULL) {
		while (fread(&entry, sizeof(entry), 1, fp_workEntry) != '\0') {
			if (entry.status == 1 && entry.staff_id==staff_id) {
				printf("\nStatus : Approved\n");
				printfStaff(entry.staff_id);
				printfModule(entry.module_id);
				flag = 1;
			}
		}
		if (flag == 0) {
			printf("Pending Entries\n");
		}
		fclose(fp_workEntry);
		printf("===================");
	} else
		printf("Error In File Opening");
}

int cmpfunc1(const void * s1, const void * s2) {
	MODULECAT *p1 = (MODULECAT*) s1, *p2 = (MODULECAT*) s2;
	int diff = p1->duration - p2->duration;
	return diff;
}

void modulesPerCategory() {
	char course[6];
	printf("Enter Course Name (Complete) : ");
	scanf("%s", course);
	printf("===================\n");
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
			printf("\nModule ID : %d\n", moduleArr[i].id);
			printf("Module Name : %s\n", moduleArr[i].name);
			printf("Course : %s\n", moduleArr[i].course);
			printf("Duration : %d\n", moduleArr[i].duration);
		}
		printf("===================");
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
	printf("\nModule ID : %d\n", module.id);
	printf("Module Name : %s\n", module.name);
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
    printf("Date : In DD/MM/YYYY format only :");
    scanf("%d / %d / %d",&entry.work_date.day,&entry.work_date.month,&entry.work_date.year);
	printf("Time : ");
	printf("Hour : ");
	scanf("%d", &entry.start_time.hours);
	printf("Mins : ");
	scanf("%d", &entry.start_time.mins);
	printf("Secs : ");
	scanf("%d", &entry.start_time.seconds);
	fflush(stdin);

    /*printf("Time : In HH-MM-SS format only");
    scanf("%d / %d / %d",&entry.start_time.hours,&entry.start_time.mins,&entry.start_time.seconds);*/
}

void printWorkEntryDetails(){
	printf("\nStatus : %d\n",entry.status);
	printf("Id : %d\n",entry.id);
	printf("Staff ID : %d\n",entry.staff_id);
	printf("Module ID : %d\n",entry.module_id);
	printf("Duration : %d\n",entry.duration);
	printf("Date : %d/%d/%d\n",entry.work_date.day,entry.work_date.month,entry.work_date.year);
	printf("Time : %d/%d/%d\n",entry.start_time.hours,entry.start_time.mins,entry.start_time.seconds);
}

int main (void){
	displayMyDetails();
	displayMainMenu();
	return 0;
}
