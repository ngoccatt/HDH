#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>       //needed for wait;

struct Node{
    char num[80];
    struct Node* next;
    int length;
};

struct Node* head = NULL;
struct Node* tail = NULL;

void addList(char* data) {
    //data nhan vao co dang xxxxx\n\0. strlen() dem ca \n, thanh ra du
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->length = strlen(data);
    if (data[temp->length-1] == '\n') {
        data[temp->length-1] = '\0';
        temp->length--;
    }
    strcpy(temp->num, data);
    temp->next=NULL;

    if (tail == NULL) {
        tail = temp;
        head = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

int countNumberDivisibleBy2(){
	struct Node* scan = head;
	int count = 0;
	while (scan != NULL) {
		if ((scan->num[scan->length - 1] - '0') % 2 == 0) count++;
		scan = scan->next;
	}
	return count;
}

int countNumberDivisibleBy5(){
	struct Node* scan = head;
	int count = 0;
	while (scan != NULL) {
		if ((scan->num[scan->length - 1] - '0') % 5 == 0) count++;
		scan = scan->next;
	}
	return count;
}

int countNumberDivisibleBy3() {
	struct Node* scan = head;
	int count = 0;
	int sum = 0;
	while (scan != NULL) {
		sum = 0;
		for (int i = 0; i < scan->length; i++) {
			sum += (scan->num[i] - '0');
		}
		if (sum % 3 == 0) count++;
		scan = scan->next;
	}
	return count;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("NO FILE IMPORTED\n");
        return -1;
    } 
    FILE* fptr;
	fptr = fopen(argv[1], "r");
	char data[80];
	if (fptr == NULL) {
		printf("Can't open file!\n"); 
		return -1;
	}
	
	while (!feof(fptr)) {
		fgets(data, 80, fptr);
        //printf("%s\n", data);
		addList(data);
	}
    //printf("Hi, I'm parent process. My process pid is %d", getpid());
	struct Node* scan = head;
    //print list
	// while (scan != NULL) {
	// 	printf("%s with length %d\n", scan->num, scan->length);
	// 	scan = scan->next;
	// }
	
    pid_t child1 = fork();
    if (child1 > 0)     //this is parent process
    {
        pid_t child2 = fork();
        if (child2 > 0) //this is parent process
        {
            pid_t child3 = fork();
            if (child3 > 0) //this is also parent process 
            {
                //waitpid can help parent wait for a specific child to 
                //terminate. in case using -1, it wait for abitrary child (act the
                //same as wait(&status))
                int status;
                pid_t pid;
                //make the process sleep so that we can check
                //using pstree -p parentpid
                //sleep(10);
                while ((pid=wait(&status))!=-1) {
                    //printf("Process %d terminated\n",pid);
                }
                //sleep(100);
            } else {   //child process 3
                //printf("We have %d number that's divisible by 5\n", countNumberDivisibleBy5());
                printf("%d\n", countNumberDivisibleBy5());
            }
        } else { //child process 2
            //printf("We have %d number that's divisible by 3\n", countNumberDivisibleBy3());
            printf("%d\n", countNumberDivisibleBy3());
        }
    } else {    //child process 1
        //printf("We have %d number that's divisible by 2\n", countNumberDivisibleBy2());
        printf("%d\n", countNumberDivisibleBy2());
    }
	
	fclose(fptr);

	return 0;
}