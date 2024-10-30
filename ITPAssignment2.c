#include <stdio.h>
#include <string.h>

struct Student{
    int Student_id;
    char Name[50];
    char Faculty[50];
};

enum ExamType{WRITTEN=0, DIGITAL};

union ExamInfo{
    int duration;
    char software[50];
};

struct Exam{
    int Exam_id;
    enum ExamType Exam_type;
    union ExamInfo ExamInfo;
};

struct ExamGrade{
    int Exam_id;
    int Student_id;
    int Grade;
};

struct Student Students[1000];
struct Exam Exams[500];
struct ExamGrade ExamGrades[1000]; 
int numstudent=0;

FILE *fileout;
FILE *filein;

// Function for adding student
int ADD_STUDENT(char *str){
    char query[50];
    int student_id;
    char name[50];
    char faculty[50];
    sscanf(str, "%s %d %s %s", query, &student_id, name, faculty);

    // Validation of student existence 
    for(int i=0; i<1000; i++){
        if(Students[i].Student_id==student_id){
            fprintf(fileout, "Student: %d already exists\n", student_id);
            return 0;
        }
    }

    // Validation of student id
    if((student_id<1)||(student_id>999)){
        fprintf(fileout, "%s\n", "Invalid student id");
        return 0;
    }

    // Validation of student name
    if((strlen(name)<2)||(strlen(name)>19)){
        fprintf(fileout, "%s\n", "Invalid name");
        return 0;
    }
    for(int i=0; i<strlen(name);i++){
        if((i==0)&&((name[i]<65)||(name[i]>90))){
            fprintf(fileout, "%s\n", "Invalid name");
            return 0;
        }
        if((i!=0)&&((name[i]<97)||(name[i]>122))){
            fprintf(fileout, "%s\n", "Invalid name");
            return 0;
        }
    }

    // Validation of student faculty
    if((strlen(faculty)<5)||(strlen(faculty)>29)){
        fprintf(fileout, "%s\n", "Invalid faculty");
        return 0;
    }
    for(int i=0; i<strlen(faculty);i++){
        if((i==0)&&((faculty[i]<65)||(faculty[i]>90))){
            fprintf(fileout, "%s\n", "Invalid faculty");
            return 0;
        }
        if((i!=0)&&((faculty[i]<65)||(faculty[i]>122)||((faculty[i]<97)&&(faculty[i]>90)))){
            fprintf(fileout, "%s\n", "Invalid faculty");
            return 0;
        }
    }

    Students[numstudent].Student_id=student_id;
    strcpy(Students[numstudent].Name, name);
    strcpy(Students[numstudent].Faculty, faculty);

    fprintf(fileout, "Student: %d added\n", Students[numstudent].Student_id);
    numstudent+=1;
}

// Function for adding exam
int ADD_EXAM(char *str){
    static int numexam=0;

    char exam_info1[50];
    int exam_info;

    char query[50];
    int exam_id;
    char exam_type[50];
    char exam_info_general[50];
    sscanf(str, "%s %d %s %s", query, &exam_id, exam_type, exam_info_general);

    // Validation of exam existence
    for(int i=0; i<500; i++){
        if(Exams[i].Exam_id==exam_id){
            fprintf(fileout, "Exam: %d already exists\n", exam_id);
            return 0;
        }
    }

    // Validation of exam id
    if((exam_id<1)||(exam_id>499)){
        fprintf(fileout, "%s\n", "Invalid exam id");
        return 0;
    }

    // Validation of exam type
    for(int i=0; i<strlen(exam_type);i++){
        if((exam_type[i]<65)||(exam_type[i]>90)){
            fprintf(fileout, "%s\n", "Invalid exam type");
            return 0;
        }
    }

    if((strcmp("WRITTEN", exam_type)!=0)&&(strcmp("DIGITAL", exam_type)!=0)){
        fprintf(fileout, "%s\n", "Invalid exam type");
        return 0;
    }

    // Validation of exam duration
    if((strcmp("WRITTEN", exam_type)==0)){
        sscanf(exam_info_general, "%d", &exam_info);
        if((exam_info<40)||(exam_info>180)){
            fprintf(fileout, "%s\n", "Invalid duration");
            return 0;
        }
    }

    // Validation of exam software
    else if(strcmp("DIGITAL", exam_type)==0){
        sscanf(exam_info_general, "%s", exam_info1);
        if((strlen(exam_info1)<3)||(strlen(exam_info1)>19)){
            fprintf(fileout, "%s\n", "Invalid software");
            return 0;
        }
        for(int i=0; i<strlen(exam_info1);i++){
        if((i==0)&&((exam_info1[i]<65)||(exam_info1[i]>90))){
            fprintf(fileout, "%s\n", "Invalid software");
            return 0;
        }
        if((i!=0)&&((exam_info1[i]<65)||(exam_info1[i]>122)||((exam_info1[i]<97)&&(exam_info1[i]>90)))){
            fprintf(fileout, "%s\n", "Invalid software");
            return 0;
        }
        }
    }

    Exams[numexam].Exam_id=exam_id;
    if(strcmp("WRITTEN", exam_type)==0){
        Exams[numexam].ExamInfo.duration=exam_info;
        Exams[numexam].Exam_type=0;
    }
    else{
        strcpy(Exams[numexam].ExamInfo.software, exam_info1);
        Exams[numexam].Exam_type=1;
    }

    fprintf(fileout, "Exam: %d added\n", exam_id);
    numexam+=1;
}

// Function for adding grade
int ADD_GRADE(char *str){
    static int numgrade=0;
    int k=0;
    int n=0;

    char query[50];
    int exam_id;
    int student_id;
    int grade;
    sscanf(str, "%s %d %d %d", query, &exam_id, &student_id, &grade);

    // Validation of exam existence
    for(int i=0; i<500; i++){
        if(Exams[i].Exam_id==exam_id){
            k+=1;
        }
    }
    if(k==0){
        fprintf(fileout, "%s\n", "Exam not found");
            return 0;
    }

    // Validation of exam id
    if((exam_id<1)||(exam_id>499)){
        fprintf(fileout, "%s\n", "Invalid exam id");
        return 0;
    }
    
    //Validation of student existence
    for(int i=0; i<1000; i++){
        if(Students[i].Student_id==student_id){
            n+=1;
        }
    }
    if(n==0){
        fprintf(fileout, "%s\n", "Student not found");
            return 0;
    }

    // Validation of student id
    if((student_id<1)||(student_id>999)){
        fprintf(fileout, "%s\n", "Invalid student id");
        return 0;
    }

    // Validation of grade
    if((grade<0)||(grade>100)){
        fprintf(fileout, "%s\n", "Invalid grade");
        return 0;
    }

    ExamGrades[numgrade].Exam_id=exam_id;
    ExamGrades[numgrade].Student_id=student_id;
    ExamGrades[numgrade].Grade=grade;

    fprintf(fileout, "Grade %d added for the student: %d\n", grade, student_id);
    numgrade++;
}

// Function for changing exam information
int UPDATE_EXAM(char *str){
    char exam_info1[50];
    int exam_info;

    char query[50];
    int exam_id;
    char exam_type[50];
    char exam_info_general[50];
    sscanf(str, "%s %d %s %s", query, &exam_id, exam_type, exam_info_general);

    // Validation of exam type
    for(int i=0; i<strlen(exam_type);i++){
        if((exam_type[i]<65)||(exam_type[i]>90)){
            fprintf(fileout, "%s\n", "Invalid exam type");
            return 0;
        }
    }

    if((strcmp("WRITTEN", exam_type)!=0)&&(strcmp("DIGITAL", exam_type)!=0)){
        fprintf(fileout, "%s\n", "Invalid exam type");
        return 0;
    }

    // Validation of exam duration
    if((strcmp("WRITTEN", exam_type)==0)){
        int exam_info;
        sscanf(exam_info_general, "%d", &exam_info);
        if((exam_info<40)||(exam_info>180)){
            fprintf(fileout, "%s\n", "Invalid duration");
            return 0;
        }
    }

    // Validation of exam software
    else if(strcmp("DIGITAL", exam_type)==0){
        char exam_info1[50];
        sscanf(exam_info_general, "%s", exam_info1);
        if((strlen(exam_info1)<3)||(strlen(exam_info1)>19)){
            fprintf(fileout, "%s\n", "Invalid software");
            return 0;
        }
        for(int i=0; i<strlen(exam_info1);i++){
        if((i==0)&&((exam_info1[i]<65)||(exam_info1[i]>90))){
            fprintf(fileout, "%s\n", "Invalid software");
            return 0;
        }
        if((i!=0)&&((exam_info1[i]<65)||(exam_info1[i]>122)||((exam_info1[i]<97)&&(exam_info1[i]>90)))){
            fprintf(fileout, "%s\n", "Invalid software");
            return 0;
        }
        }
    }

    for(int i=0; i<500; i++){
        if(Exams[i].Exam_id=exam_id){
            if(strcmp("WRITTEN", exam_type)==0){
                    Exams[i].ExamInfo.duration=exam_info;
                    Exams[i].Exam_type=0;
                }
                else{
                    strcpy(Exams[i].ExamInfo.software, exam_info1);
                    Exams[i].Exam_type=1;
                }
        }
    }

    fprintf(fileout, "Exam: %d updated\n", exam_id);
}

// Function for changing grade
int UPDATE_GRADE(char *str){
    char query[50];
    int exam_id;
    int student_id;
    int grade;
    sscanf(str, "%s %d %d %d", query, &exam_id, &student_id, &grade);

    // Validation of grade
    if((grade<0)||(grade>100)){
        fprintf(fileout, "%s\n", "Invalid grade");
        return 0;
    }

    for(int i=0; i<1000; i++){
        if(ExamGrades[i].Exam_id==exam_id){
            ExamGrades[i].Grade=grade;
        }
    }

    fprintf(fileout, "Grade %d updated for the student: %d\n", grade, student_id);
}

// Function for finding information about student
int SEARCH_STUDENT(char *str){
    char query[50];
    int student_id;
    sscanf(str, "%s %d", query, &student_id);

    int n=0;

    // Validation of student existence
    for(int i=0; i<1000; i++){
        if(Students[i].Student_id==student_id){
            n+=1;
        }
    }
    if(n==0){
        fprintf(fileout, "%s\n", "Student not found");
            return 0;
    }

    // Validation of student id
    if((student_id<1)||(student_id>999)){
        fprintf(fileout, "%s\n", "Invalid student id");
        return 0;
    }

    for(int i=0; i<1000; i++){
        if(Students[i].Student_id==student_id){
            fprintf(fileout, "ID: %d, Name: %s, Faculty: %s\n", student_id, Students[i].Name, Students[i].Faculty);
        }
    }
}

// Function for finding information about grade
int SEARCH_GRADE(char *str){
    char query[50];
    int exam_id;
    int student_id;
    sscanf(str, "%s %d %d", query, &exam_id, &student_id);

    // Validation of exam existence
    int k=0;
    for(int i=0; i<500; i++){
        if(Exams[i].Exam_id==exam_id){
            k+=1;
        }
    }
    if(k==0){
        fprintf(fileout, "%s\n", "Exam not found");
            return 0;
    }

    // Validation of exam id
    if((exam_id<1)||(exam_id>499)){
        fprintf(fileout, "%s\n", "Invalid exam id");
        return 0;
    }

    // Validation of student existence
    int n=0;
    for(int i=0; i<1000; i++){
        if(Students[i].Student_id==student_id){
            n+=1;
        }
    }
    if(n==0){
        fprintf(fileout, "%s\n", "Student not found");
            return 0;
    }

    // Validation of student id
    if((student_id<1)||(student_id>999)){
        fprintf(fileout, "%s\n", "Invalid student id");
        return 0;
    }

    int g, s, e;
    for(int i=0; i<1000; i++){
        if((ExamGrades[i].Exam_id==exam_id)&&(ExamGrades[i].Student_id==student_id)){
            g=i;
        }
    }
    for(int i=0; i<1000; i++){
        if(Students[i].Student_id==student_id){
            s=i;
        }
    }
    for(int i=0; i<500; i++){
        if(Exams[i].Exam_id==exam_id){
            e=i;
        }
    }

    if(Exams[e].Exam_type==0){
        fprintf(fileout, "Exam: %d, Student: %d, Name: %s, Grade: %d, Type: WRITTEN, Info: %d\n", exam_id, student_id, Students[s].Name, ExamGrades[g].Grade, Exams[e].ExamInfo.duration);
    }
    else{
        fprintf(fileout, "Exam: %d, Student: %d, Name: %s, Grade: %d, Type: DIGITAL, Info: %s\n", exam_id, student_id, Students[s].Name, ExamGrades[g].Grade, Exams[e].ExamInfo.software);
    }
}

// Function for deleting information about student 
int DELETE_STUDENT(char *str){
    char query[50];
    int student_id;
    sscanf(str, "%s %d", query, &student_id);

    for(int i=0; i<1000; i++){
        if(Students[i].Student_id==student_id){
            Students[i].Student_id=0;
        }
    }
    for(int i=0; i<1000; i++){
        if(ExamGrades[i].Student_id==student_id){
            ExamGrades[i].Student_id=0;
        }
    }

    fprintf(fileout, "Student: %d deleted\n", student_id);
}

// Function for finding and printing information about all existing students
void LIST_ALL_STUDENTS(){
    for(int i=0; i<1000; i++){
        if(Students[i].Student_id!=0){
            fprintf(fileout, "ID: %d, Name: %s, Faculty: %s\n", Students[i].Student_id, Students[i].Name, Students[i].Faculty);
        }
    }
}

// Helping function for other function calling
void strconv(char *str){

    char add_student[]="ADD_STUDENT";
    char add_exam[]="ADD_EXAM";
    char add_grade[]="ADD_GRADE";
    char update_exam[]="UPDATE_EXAM";
    char update_grade[]="UPDATE_GRADE";
    char search_student[]="SEARCH_STUDENT";
    char search_grade[]="SEARCH_GRADE";
    char delete_student[]="DELETE_STUDENT";
    char list_all_students[]="LIST_ALL_STUDENTS";
    char end[]="END";

    if(strstr(str, add_student)){
        ADD_STUDENT(str);
    }
    else if(strstr(str, add_exam)){
        ADD_EXAM(str);
    }
    else if(strstr(str, add_grade)){
        ADD_GRADE(str);
    }
    else if(strstr(str, update_exam)){
        UPDATE_EXAM(str);
    }
    else if(strstr(str, update_grade)){
        UPDATE_GRADE(str);
    }
    else if(strstr(str, search_student)){
        SEARCH_STUDENT(str);
    }
    else if(strstr(str, search_grade)){
        SEARCH_GRADE(str);
    }
    else if(strstr(str, delete_student)){
        DELETE_STUDENT(str);
    }
    else if(strstr(str, list_all_students)){
        LIST_ALL_STUDENTS();
    }
    else if(strstr(str, list_all_students)){
        LIST_ALL_STUDENTS();
    }
}

int main(){
    filein = fopen("input.txt", "r");

    fileout = fopen("output.txt", "w");

    char line[200];
    
    // Reading file line by line
    while((fgets(line, 200, filein))!=NULL){
        line[strcspn(line, "\n" )] = '\0';
        if(strcmp("END", line)==0){
            return 0;
        }
        else{
            strconv(line);
        }
    }

    fclose(filein);
    fclose(fileout);

    return 0;
}