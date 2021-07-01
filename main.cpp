#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define CSI "\033["
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ESC 27
#define ENTER 13
#define BKSP 8
#define TAB 9
#define RESET_COLOR CSI "0m"
#define GREEN_COLOR CSI "32m"
#define RED_COLOR CSI "31m"

struct Visitor {
    char ticketID[25];
    char lisence[25];
    char enter_time[25];
    char exit_time[25];
    struct Visitor* next;
    struct Visitor* left;
    struct Visitor* right;
};

struct Visitor* head = NULL;
struct Visitor* tail = NULL;
struct Visitor* root = NULL;

struct Visitor* createNewNode(char ticketID[], char lisence[], char enter_time[]) {
    struct Visitor* newNode = (struct Visitor*)malloc(sizeof(struct Visitor));
    strcpy(newNode->ticketID, ticketID);
    strcpy(newNode->lisence, lisence);
    strcpy(newNode->enter_time, enter_time);
    newNode->next = NULL;

    return newNode;
}

// LINKED LIST INSERT
void pushTail(char ticketID[], char lisence[], char enter_time[]) {
    struct Visitor* newNode = createNewNode(ticketID, lisence, enter_time);

	if (head == NULL)
	{
		head = tail = newNode;
	}
	else
	{
		tail -> next = newNode;
		tail = newNode;
	}
}

struct Visitor* popHead()
{
	if(head != NULL)
	{
		struct Visitor *temp=head;

		if(head == tail)
		{
			head = tail = NULL;
		}
		else
		{
			head = head -> next;
		}
		return temp;
	}
}

struct Visitor* popTail()
{
    if(head != NULL)
    {
        struct Visitor *temp = tail;

        if(head == tail)
        {
            head = tail = NULL;
        }
        else
        {
            struct Visitor* curr = head;
            while (curr->next != tail) {
                curr = curr->next;
            }
            tail = curr;
            curr->next = NULL;
        }
        return temp;
    }
}

// LINKED LIST DELETE
struct Visitor* popMid(char ticketID[])
{
    if(head != NULL)
    {
        if (strcmp(ticketID, head->ticketID) == 0) {
            popHead();
        }
        else if (strcmp(ticketID, tail->ticketID) == 0) {
            popTail();
        } else {
            struct Visitor* curr = head;
            while (strcmp(ticketID, curr->next->ticketID) != 0) {
                curr = curr->next;
                if (curr->next == NULL)
                    return NULL;
            }

            struct Visitor* temp = curr->next;
            curr->next = temp->next;

            return temp;
        }
    } else {
        return NULL;
    }
}

// BST INSERT
struct Visitor* pushHistory(struct Visitor* root, struct Visitor* node) {
    if(root == NULL){
        root = node;
    }
    else if(strcmp(node->ticketID, root->ticketID) < 0){
        root->left = pushHistory(root->left, node);
    }
    else if(strcmp(node->ticketID, root->ticketID) > 0){
        root->right = pushHistory(root->right, node);
    }

    return root;
}

// BST SEARCH
struct Visitor* search(struct Visitor* root, char ticketID[]){

    if(root == NULL) {
        return NULL;
    }
    else if(strcmp(root->ticketID, ticketID) == 0) {
        return root;
    }
    else if(strcmp(root->ticketID, ticketID) > 0) {
        return search(root->left, ticketID);
    }
    else if(strcmp(root->ticketID, ticketID) < 0) {
        return search(root->right, ticketID);
    }
}

void savePos() {
    printf(CSI "s");
}

void resetPos() {
    printf(CSI "u");
}

void setPos(int y, int x) {
    printf(CSI "%d;%dH", y, x);
}

void clear() {
    printf(CSI "H");
    printf(CSI "J");
}

int mCount = 0;
int cCount = 0;
char newTicket[25];

char* generateTicket(char type[]) {
    if (strcmp(type, "car") != 0) {
        if (mCount < 10) {
            sprintf(newTicket, "MT000%d", mCount);
        }
        else if (mCount < 100) {
            sprintf(newTicket, "MT00%d", mCount);
        }
        else if (mCount < 1000) {
            sprintf(newTicket, "MT0%d", mCount);
        }
        else if (mCount < 10000) {
            sprintf(newTicket, "MT%d", mCount);
        }
    } else {
        if (cCount < 10) {
            sprintf(newTicket, "CT000%d", cCount);
        }
        else if (cCount < 100) {
            sprintf(newTicket, "CT00%d", cCount);
        }
        else if (cCount < 1000) {
            sprintf(newTicket, "CT0%d", cCount);
        }
        else if (cCount < 10000) {
            sprintf(newTicket, "CT%d", cCount);
        }
    }
    return newTicket;
}

char* currentTimeToStr() {
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char* time = asctime(timeinfo);
    return ctime(&rawtime);
}

void displayTime() {
    char time[25];
    strcpy(time, currentTimeToStr());
    sscanf(time, "%[^\n]", time);
    char waktu[7][25];
    int i = 0;

    char* tok = strtok(time, " ");
    while (tok != NULL) {
        strcpy(waktu[i], tok);
        i++;
        tok = strtok(NULL, " ");
    }

    printf("%s | %s - %s - %s | %s", waktu[0], waktu[1], waktu[2], waktu[4], waktu[3]);
}

int getMonth(char month_str[]) {
    if (strcmp(month_str, "Jan") == 0) {
        return 1;
    }
    if (strcmp(month_str, "Feb") == 0) {
        return 2;
    }
    if (strcmp(month_str, "Mar") == 0) {
        return 3;
    }
    if (strcmp(month_str, "Apr") == 0) {
        return 4;
    }
    if (strcmp(month_str, "May") == 0) {
        return 5;
    }
    if (strcmp(month_str, "Jun") == 0) {
        return 6;
    }
    if (strcmp(month_str, "Jul") == 0) {
        return 7;
    }
    if (strcmp(month_str, "Aug") == 0) {
        return 8;
    }
    if (strcmp(month_str, "Sep") == 0) {
        return 9;
    }
    if (strcmp(month_str, "Oct") == 0) {
        return 10;
    }
    if (strcmp(month_str, "Nov") == 0) {
        return 11;
    }
    if (strcmp(month_str, "Dec") == 0) {
        return 12;
    }
}

int getCost(char T[], char exit_time[], char ticketID[]) {
    time_t result = 0;

    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
    char temp[25], month_str[25];

    sscanf(T, "%[^ ] %[^ ] %2d %2d:%2d:%2d %4d", temp, month_str, &day, &hour, &min, &sec, &year);
    month = getMonth(month_str);
    struct tm breakdown = {0};
    breakdown.tm_year = year - 1900;
    breakdown.tm_mon = month - 1;
    breakdown.tm_mday = day;
    breakdown.tm_hour = hour;
    breakdown.tm_min = min;
    breakdown.tm_sec = sec;

    result = mktime(&breakdown);

    time_t now = 0;

    sscanf(exit_time, "%[^ ] %[^ ] %2d %2d:%2d:%2d %4d", temp, month_str, &day, &hour, &min, &sec, &year);
    month = getMonth(month_str);
    struct tm breakdown2 = {0};
    breakdown2.tm_year = year - 1900;
    breakdown2.tm_mon = month - 1;
    breakdown2.tm_mday = day;
    breakdown2.tm_hour = hour;
    breakdown2.tm_min = min;
    breakdown2.tm_sec = sec;

    now = mktime(&breakdown2);

    double gap = difftime(now, result);
    double times = gap/5;
    int price = 0, up1 = 0;

    do {
        times--;
        if (up1 == 0) {
            price += (ticketID[0] == 'C' ? 5000 : 2000);
            up1 = 1;
            continue;
        }
        price += (ticketID[0] == 'C' ? 3000 : 1000);
    } while (times > 0);

    return price;
}

void payment(int cost, char ticketID[], char exit_time[]) {
    clear();
    int x = 50, y = 6;
    int pay, changes;
    setPos(2, 4);
    printf("BILL");

    setPos(2, 87);
    displayTime();

    setPos(y, x);
    printf("BINUS PARKING");

    setPos(y+3, x-35);
    printf("------------------------------------------------------------------------------------");
    for (int i=0; i<11; i++) {
        setPos(y+4+i, x-35);
        printf("|                                                                                  |");
    }
    setPos(y+15, x-35);
    printf("------------------------------------------------------------------------------------");

    setPos(y+5, x);
    printf("PAY:");
    setPos(y+6, x);
    printf(">> Rp.");
    scanf("%d", &pay);

    setPos(y+8, x);
    printf("RETURN:");
    setPos(y+9, x);
    printf(">> Rp.%d", pay-cost);

    getch();

    setPos(y+13, x);
    printf(GREEN_COLOR "PAYMENT SUCCESS" RESET_COLOR);
    getch();
    struct Visitor* temp = popMid(ticketID);
    strcpy(temp->exit_time, exit_time);
    temp->left = NULL;
    temp->right = NULL;
    if (root == NULL) {
        root = pushHistory(root, temp);
    } else {
        pushHistory(root, temp);
    }

    FILE* file = fopen("parked.txt", "w");
    struct Visitor* curr = head;
    while (curr != NULL) {
        fprintf(file, "%s;%s;%s\n", curr->ticketID, curr->lisence, curr->enter_time);
        curr = curr->next;
    }
    fclose(file);

    file = fopen("history.txt", "a");
    fprintf(file, "%s;%s;%s;%s\n", temp->ticketID, temp->lisence, temp->enter_time, temp->exit_time);

    fclose(file);
}

void billTicket(char enter_time[], char lisence[], char ticketID[], char exit_time[]) {
    clear();
    int x = 50, y = 6;
    setPos(2, 4);
    printf("BILL");

    setPos(2, 87);
    displayTime();

    setPos(y, x);
    printf("BINUS PARKING");
    setPos(y+3, x-35);
    printf("------------------------------------------------------------------------------------");
    for (int i=0; i<11; i++) {
        setPos(y+4+i, x-35);
        printf("|                                                                                  |");
    }
    setPos(y+5, x-2);
    printf("TICKET ID: %s", ticketID);

    setPos(y+7, x-2);
    printf("LICENSE PLATE: %s", lisence);


    setPos(y+9, x-2);
    printf("TIME");
    setPos(y+10, x-2);
    printf(">> ");
    printf("IN : %s", enter_time);
    setPos(y+11, x-2);
    printf(">> ");
    printf("OUT: %s", exit_time);

    setPos(y+13, x-2);
    printf("COST: Rp.%d", getCost(enter_time, exit_time, ticketID));

    setPos(y+15, x-35);
    printf("------------------------------------------------------------------------------------");

    getch();
    payment(getCost(enter_time, exit_time, ticketID), ticketID, exit_time);
}

struct Visitor* ticketValidation(char lisence[], char ticketID[]) {
    if (head) {
        struct Visitor* curr = head;
        while (curr != NULL) {
            if (strcmp(curr->lisence, lisence) == 0 && strcmp(curr->ticketID, ticketID) == 0) {
                return curr;
            }
            curr = curr->next;
        }
    }
    return NULL;
}

void exitTicketMenu() {
    char lisence[25], ticketID[25], exit_time[25], c;
    clear();
    int x = 50, y = 6, i = 0;

    setPos(2, 4);
    printf("EXIT TICKET");

    resetPos();
    setPos(2, 87);
    displayTime();

    setPos(y, x);
    printf("BINUS PARKING");
    for (int i=0; i<11; i++) {
        setPos(y+4+i, x-35);
        printf("|                                                                                  |");
    }
    setPos(y+3, x-35);
    printf("------------------------------------------------------------------------------------");
    setPos(y+15, x-35);
    printf("------------------------------------------------------------------------------------");
    setPos(y+16, x-6);
    printf("Press ESC key to go back");
    setPos(y+5, x);
    printf("LICENSE PLATE: ");
    setPos(y+6, x);
    printf(">> ");

    setPos(y+8, x);
    printf("TICKET ID: ");
    setPos(y+9, x);
    printf(">> ");

    setPos(y+6, x+3);
    while (1) {
        c = getch();
        if (c == ENTER) {
            lisence[i] = '\0';
            break;
        }
        else if (c == ESC) {
            return;
        }
        else if (c == ' ') {
            continue;
        }
        else if (c == BKSP) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            lisence[i] = c;
            i++;
            printf("%c", c);
        }
    }

    i = 0;
    setPos(y+9, x+3);
    while (1) {
        c = getch();
        if (c == ENTER) {
            ticketID[i] = '\0';
            break;
        }
        else if (c == ESC) {
            return;
        }
        else if (c == ' ') {
            continue;
        }
        else if (c == BKSP) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            ticketID[i] = c;
            i++;
            printf("%c", c);
        }
    }
    strcpy(lisence, strupr(lisence));
    strcpy(ticketID, strupr(ticketID));

    if (ticketValidation(lisence, ticketID) == NULL) {
        setPos(y+13, x-13);
        printf(RED_COLOR "TICKET IS INVALID OR LISENCE DOESN'T MATCH!\n" RESET_COLOR);
        getch();
        return;
    }

    strcpy(exit_time, currentTimeToStr());
    sscanf(exit_time, "%[^\n]", exit_time);

    billTicket(ticketValidation(lisence, ticketID)->enter_time, lisence, ticketID, exit_time);
}

int checkLisenceExistence(char lisence[]) {
    struct Visitor* curr = head;
    while (curr != NULL) {
        if (strcmp(curr->lisence, lisence) == 0) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

void carNewTicket() {
    clear();
    int x = 50, y = 6, i = 0;
    char ticketID[25], lisence[25], enter_time[25], c;
    strcpy(enter_time, currentTimeToStr());
    setPos(2, 4);
    printf("ENTRANCE TICKET");

    resetPos();
    setPos(2, 87);
    displayTime();

    setPos(y, x);
    printf("BINUS PARKING");

    setPos(y+3, x-35);
    printf("------------------------------------------------------------------------------------");
    for (int i=0; i<11; i++) {
        setPos(y+4+i, x-35);
        printf("|                                                                                  |");
    }

    setPos(y+5, x-6);
    printf("TIME: %s", enter_time);

    setPos(y+7, x-6);
    char car[] = "car";
    strcpy(ticketID, generateTicket(car));
    printf("TICKET ID: %s", ticketID);
    setPos(y+15, x-35);
    printf("------------------------------------------------------------------------------------");
    setPos(y+16, x-6);
    printf("Press ESC key to go back");

    setPos(y+9, x-6);
    printf("LISENCE PLATE:");
    setPos(y+10, x-6);
    printf(">> ");
    while (1) {
        c = getch();
        if (c == ENTER) {
            lisence[i] = '\0';
            break;
        }
        else if (c == ESC) {
            return;
        }
        else if (c == ' ') {
            continue;
        }
        else if (c == BKSP) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            lisence[i] = c;
            i++;
            printf("%c", c);
        }
    }
    strcpy(lisence, strupr(lisence));

    if (strcmp(lisence, "") == 0) {
        setPos(y+13, x-6);
        printf(RED_COLOR "INPUT LISENCE CAN'T BE EMPTY!" RESET_COLOR);
    }
    else if (checkLisenceExistence(lisence)) {
        setPos(y+13, x-6);
        printf(RED_COLOR "LISENCE PLATE ALREADY EXIST!" RESET_COLOR);
    } else {
        sscanf(enter_time, "%[^\n]", enter_time);
        pushTail(ticketID, lisence, enter_time);

        FILE* file = fopen("parked.txt", "a");
        fprintf(file, "%s;%s;%s\n", ticketID, lisence, enter_time);
        fclose(file);
        setPos(y+13, x-6);
        printf(GREEN_COLOR "NEW TICKET HAS BEEN CREATED!" RESET_COLOR);
        cCount++;
    }

    getch();
}

void motorNewTicket() {
    clear();
    int x = 50, y = 6, i = 0;
    char ticketID[25], lisence[25], enter_time[25], c;
    strcpy(enter_time, currentTimeToStr());
    setPos(2, 4);
    printf("ENTRANCE TICKET");

    resetPos();
    setPos(2, 87);
    displayTime();

    setPos(y, x);
    printf("BINUS PARKING");

    setPos(y+3, x-35);
    printf("------------------------------------------------------------------------------------");
    for (int i=0; i<11; i++) {
        setPos(y+4+i, x-35);
        printf("|                                                                                  |");
    }

    setPos(y+5, x-6);
    printf("TIME: %s", enter_time);
	
    setPos(y+7, x-6);
    char motorcyle[] = "motorcycle";
    strcpy(ticketID, generateTicket(motorcyle));
    printf("TICKET ID: %s", ticketID);
    setPos(y+15, x-35);
    printf("------------------------------------------------------------------------------------");
    setPos(y+16, x-6);
    printf("Press ESC key to go back");

    setPos(y+9, x-6);
    printf("LISENCE PLATE:");
    setPos(y+10, x-6);
    printf(">> ");
    while (1) {
        c = getch();
        if (c == ENTER) {
            lisence[i] = '\0';
            break;
        }
        else if (c == ESC) {
            return;
        }
        else if (c == ' ') {
            continue;
        }
        else if (c == BKSP) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            lisence[i] = c;
            i++;
            printf("%c", c);
        }
    }
    strcpy(lisence, strupr(lisence));

    if (strcmp(lisence, "") == 0) {
        setPos(y+13, x-6);
        printf(RED_COLOR "INPUT LISENCE CAN'T BE EMPTY!" RESET_COLOR);
    }
    else if (checkLisenceExistence(lisence)) {
        setPos(y+13, x-6);
        printf(RED_COLOR "LISENCE PLATE ALREADY EXIST!" RESET_COLOR);
    } else {
        sscanf(enter_time, "%[^\n]", enter_time);
        pushTail(ticketID, lisence, enter_time);

        FILE* file = fopen("parked.txt", "a");
        fprintf(file, "%s;%s;%s\n", ticketID, lisence, enter_time);
        fclose(file);
        setPos(y+13, x-6);
        printf(GREEN_COLOR "NEW TICKET HAS BEEN CREATED!" RESET_COLOR);
        mCount++;
    }

    getch();
}

void showEntranceTicketMenu(int choose) {
    int x = 50, y = 6;
    setPos(2, 4);
    printf("ENTRANCE TICKET");

    resetPos();
    setPos(2, 87);
    displayTime();

    setPos(y, x);
    printf("BINUS PARKING");
    setPos(y+3, x-35);
    printf("------------------------------------------------------------------------------------");
    setPos(y+4, x-35);
    printf("|                                                                                  |");

    setPos(y+5, x-35);
    if (choose == 1) {
        printf("|                              -> CAR                                              |");
    } else {
        printf("|                                 CAR                                              |");
    }

    setPos(y+6, x-35);
    if (choose == 2) {
        printf("|                              -> MOTORCYCLE                                       |");
    } else {
        printf("|                                 MOTORCYCLE                                       |");
    }

    setPos(y+7, x-35);
    if (choose == 3) {
        printf("|                              -> BACK                                             |");
    } else {
        printf("|                                 BACK                                             |");
    }
    for(int i=0; i<8; i++) {
        setPos(y+8+i, x-35);
        printf("|                                                                                  |");
    }
    setPos(y+15, x-35);
    printf("------------------------------------------------------------------------------------");
    setPos(y+16, x-15);
    printf("Press ARROW UP or ARROW DOWN key to change option");
}

void entranceTicketMenu() {
    int choose = 1;
    char move;
    do {
        clear();
        showEntranceTicketMenu(choose);
        move = getch();

        switch (move) {
            case ARROW_UP:
                choose--;
                break;
            case ARROW_DOWN:
                choose++;
                break;
        }

        if (choose < 1)
            choose = 1;
        if (choose > 3)
            choose = 3;
        if (move == ENTER) {
            if (choose == 1) {
                carNewTicket();
            }
            else if (choose == 2) {
                motorNewTicket();
            }
            else if (choose == 3) {
                break;
            }
        }
    } while (1);
}

void parkedVehicleData() {
    clear();
    int x = 50, y = 6;
    setPos(2, 4);
    int i = 5;
    printf("PARKED VEHICLE");

    resetPos();
    setPos(2, 87);
    displayTime();

    setPos(y, x);
    printf("BINUS PARKING");
    setPos(y+2, x-27);
    printf("=====================================================================\n");
    setPos(y+3, x-27);
    printf("| %-9s | %-13s | %-10s | %-24s |\n", "TICKET ID", "LISENCE PLATE", "VEHICLE", "ENTRY TIME");
    setPos(y+4, x-27);
    printf("=====================================================================\n");
    if (head == NULL) {
        setPos(y+i, x-27);
        printf("|                             NO DATA                               |\n");
        i++;
    } else {
        struct Visitor* curr = head;
        while (curr != NULL) {
            setPos(y+i, x-27);
            if (curr->ticketID[0] == 'C') {
                printf("| %-9s | %-13s | %-10s | %-24s |\n", curr->ticketID, curr->lisence, "Car", curr->enter_time);
            } else {
                printf("| %-9s | %-13s | %-10s | %-24s |\n", curr->ticketID, curr->lisence, "Motorcycle", curr->enter_time);
            }
            curr = curr->next;
            i++;
        }
    }
    setPos(y+i, x-27);
    printf("=====================================================================\n");
    setPos(y+i+2, x-6);
    printf("Press any key to go back . . .");

    getch();
}

void searchData(char ticketID[]) {
    clear();
    int x = 50, y = 6, i = 0;
    char c;
    setPos(2, 4);
    printf("PARKING HISTORY");

    resetPos();
    setPos(2, 87);
    displayTime();

    setPos(y, x);
    printf("BINUS PARKING");
    setPos(y+2, x-38);
    printf("================================================================================================\n");
    setPos(y+3, x-38);
    printf("| %-9s | %-13s | %-10s | %-24s | %-24s |\n", "TICKET ID", "LISENCE PLATE", "VEHICLE", "ENTRY TIME", "EXIT TIME");
    setPos(y+4, x-38);
    printf("================================================================================================\n");
    setPos(y+5, x-38);
    if (search(root, ticketID) == NULL) {
        printf("|                                          NO DATA                                             |\n");
    } else {
        struct Visitor* node = search(root, ticketID);
        if (node->ticketID[0] == 'C') {
            printf("| %-9s | %-13s | %-10s | %-24s | %-24s |\n", node->ticketID, node->lisence, "Car", node->enter_time, node->exit_time);
        } else {
            printf("| %-9s | %-13s | %-10s | %-24s | %-24s |\n", node->ticketID, node->lisence, "Motorcycle", node->enter_time, node->exit_time);
        }
    }
    setPos(y+6, x-38);
    printf("================================================================================================\n");
    setPos(y+8, x-6);
    printf("Press Any Key to Continue . . .");
    getch();
}

int countHistory = 5;

void printHistory(struct Visitor* root) {
    if(!root)
        return;

    printHistory(root->left);
    setPos(6+countHistory, 12);
    if (root->ticketID[0] == 'C') {
        printf("| %-9s | %-13s | %-10s | %-24s | %-24s |\n", root->ticketID, root->lisence, "Car", root->enter_time, root->exit_time);
    } else {
        printf("| %-9s | %-13s | %-10s | %-24s | %-24s |\n", root->ticketID, root->lisence, "Motorcycle", root->enter_time, root->exit_time);
    }
    countHistory++;
    printHistory(root->right);
}

void parkingHistoryData() {
    clear();
    countHistory = 5;
    int x = 50, y = 6, i = 0;
    char ticketID[25], c;
    setPos(2, 4);
    printf("PARKING HISTORY");

    resetPos();
    setPos(2, 87);
    displayTime();

    setPos(y, x);
    printf("BINUS PARKING");
    setPos(y+2, x-38);
    printf("================================================================================================\n");
    setPos(y+3, x-38);
    printf("| %-9s | %-13s | %-10s | %-24s | %-24s |\n", "TICKET ID", "LISENCE PLATE", "VEHICLE", "ENTRY TIME", "EXIT TIME");
    setPos(y+4, x-38);
    printf("================================================================================================\n");
    if (root == NULL) {
        setPos(y+countHistory, x-38);
        printf("|                                          NO DATA                                             |\n");
        countHistory++;
    } else {
        printHistory(root);
    }
    setPos(y+countHistory, x-38);
    printf("================================================================================================\n");
    setPos(y+countHistory+5, x-6);
    printf("Press ESC key to go back");
    setPos(y+countHistory+2, x-6);
    printf("SEARCH FOR SPESIFIC DATA");
    setPos(y+countHistory+3, x-6);
    printf("TICKET ID: ");
    while (1) {
        c = getch();
        if (c == ENTER) {
            ticketID[i] = '\0';
            break;
        }
        else if (c == ESC) {
            return;
        }
        else if (c == BKSP) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            ticketID[i] = c;
            i++;
            printf("%c", c);
        }
    }
    searchData(ticketID);
}

void showDataParkingMenu(int choose) {
    clear();
    int x = 50, y = 6;
    setPos(2, 4);
    printf("OPERATOR MENU");

    resetPos();
    setPos(2, 87);
    displayTime();

    setPos(y, x);
    printf("BINUS PARKING");

    setPos(y+3, x-35);
    printf("------------------------------------------------------------------------------------");
    setPos(y+4, x-35);
    printf("|                                                                                  |");
    setPos(y+5, x-35);
    if (choose == 1) {
        printf("|                              -> PARKED VEHICLE                                   |");
    } else {
        printf("|                                 PARKED VEHICLE                                   |");
    }

    setPos(y+6, x-35);
    if (choose == 2) {
        printf("|                              -> PARKING HISTORY                                  |");
    } else {
        printf("|                                 PARKING HISTORY                                  |");
    }

    setPos(y+7, x-35);
    if (choose == 3) {
        printf("|                              -> BACK                                             |");
    } else {
        printf("|                                 BACK                                             |");
    }

    setPos(y+8, x-35);
    printf("|                                                                                  |");

    setPos(y+9, x-35);
    printf("|                                                                                  |");
    for(int i=0; i<5; i++) {
        setPos(y+10+i, x-35);
        printf("|                                                                                  |");
    }
    setPos(y+15, x-35);
    printf("------------------------------------------------------------------------------------");
    setPos(y+16, x-15);
    printf("Press ARROW UP or ARROW DOWN key to change option");
}

void dataParkingMenu() {
    int choose = 1;
    char move;
    do {
        clear();
        showDataParkingMenu(choose);
        move = getch();

        switch (move) {
            case ARROW_UP:
                choose--;
                break;
            case ARROW_DOWN:
                choose++;
                break;
        }

        if (choose < 1)
            choose = 1;
        if (choose > 3)
            choose = 3;
        if (move == ENTER) {
            switch (choose) {
                case 1:
                    parkedVehicleData();
                    break;
                case 2:
                    parkingHistoryData();
                    break;
            }
        }
    } while (choose != 3 || move != ENTER);
}

void showOperatorMenu(int choose) {
    int x = 50, y = 6;
    setPos(2, 4);
    printf("OPERATOR MENU");

    resetPos();
    setPos(2, 87);
    displayTime();

    setPos(y, x);
    printf("BINUS PARKING");

    setPos(y+3, x-35);
    printf("------------------------------------------------------------------------------------");
    setPos(y+4, x-35);
    printf("|                                                                                  |");
    setPos(y+5, x-35);
    if (choose == 1) {
        printf("|                              -> ENTRANCE TICKET                                  |");
    } else {
        printf("|                                 ENTRANCE TICKET                                  |");
    }

    setPos(y+6, x-35);
    if (choose == 2) {
        printf("|                              -> EXIT TICKET                                      |");
    } else {
        printf("|                                 EXIT TICKET                                      |");
    }

    setPos(y+7, x-35);
    if (choose == 3) {
        printf("|                              -> PARKING DATA                                     |");
    } else {
        printf("|                                 PARKING DATA                                     |");
    }
    setPos(y+8, x-35);
    if (choose == 4) {
        printf("|                              -> EXIT                                             |");
    } else {
        printf("|                                 EXIT                                             |");
    }

    setPos(y+9, x-35);
    printf("|                                                                                  |");
    for(int i=0; i<5; i++) {
        setPos(y+10+i, x-35);
        printf("|                                                                                  |");
    }
    setPos(y+15, x-35);
    printf("------------------------------------------------------------------------------------");
    setPos(y+16, x-15);
    printf("Press ARROW UP or ARROW DOWN key to change option");
}

void operatorMenu() {
    int choose = 1;
    char move;
    do {
        clear();
        showOperatorMenu(choose);
        move = getch();

        switch (move) {
            case ARROW_UP:
                choose--;
                break;
            case ARROW_DOWN:
                choose++;
                break;
        }

        if (choose < 1)
            choose = 1;
        if (choose > 4)
            choose = 4;
        if (move == ENTER) {
            switch (choose) {
                case 1:
                    entranceTicketMenu();
                    break;
                case 2:
                    exitTicketMenu();
                    break;
                case 3:
                    dataParkingMenu();
                    break;
            }
        }
    } while (choose != 4 || move != ENTER);
}

void loginMenu() {
    do {
        clear();
        int x = 50, y = 6;
        setPos(2, 4);
        printf("LOGIN PAGE");

        resetPos();
        setPos(2, 87);
        displayTime();


        setPos(y, x-3);
        printf("Welcome to BINUS PARKING");

        setPos(y+3, x-35);
        printf("------------------------------------------------------------------------------------");

        for (int i=0; i<11; i++) {
            setPos(y+4+i, x-35);
            printf("|                                                                                  |");
        }
        setPos(y+15, x-35);
        printf("------------------------------------------------------------------------------------");
        setPos(y+16, x-4);
        printf("Press ESC key to go back");

        setPos(y+5, x-7);
        printf("Username : ");
        setPos(y+6, x-7);
        printf("Password : ");

        char uname[25], pass[25], c;
        setPos(y+5, x+4);
        int i = 0;
        while (1) {
            c = getch();
            if (c == ENTER) {
                uname[i] = '\0';
                break;
            }
            else if (c == ESC) {
                clear();
                return;
            }
            else if (c == BKSP) {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            } else {
                uname[i] = c;
                i++;
                printf("%c", c);
            }
        }
        setPos(y+6, x+4);
        i = 0;
        while (1) {
            c = getch();
            if (c == ENTER) {
                pass[i] = '\0';
                break;
            }
            else if (c == BKSP) {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            } else {
                pass[i] = c;
                i++;
                printf("*");
            }
        }

        if (strcmp(uname, "admin") != 0 || strcmp(pass, "admin") != 0) {
            setPos(y+13, x-7);
            printf(RED_COLOR "USERNAME OR PASSWORD IS INVALID!\n" RESET_COLOR);
            getch();
            continue;
        }

        break;
    } while (1);

    operatorMenu();
    clear();
}

void loadData() {
    FILE* file = fopen("parked.txt", "r");

    if (file == NULL) {
        file = fopen("parked.txt", "w");
        fclose(file);
    } else {
        while (1) {
            char ticketID[25], lisence[25], enter_time[25];
            int a = fscanf(file, "%[^;];%[^;];%[^\n]", ticketID, lisence, enter_time);
            fgetc(file);

            if (a == EOF)
                break;

            if (ticketID[0] == 'C') {
                cCount++;
            } else {
                mCount++;
            }
            pushTail(ticketID, lisence, enter_time);
        }
        fclose(file);
    }
    file = fopen("history.txt", "r");

    if (file == NULL) {
        file = fopen("history.txt", "w");
        fclose(file);
    } else {
        while (1) {
            char ticketID[25], lisence[25], enter_time[25], exit_time[25];
            int a = fscanf(file, "%[^;];%[^;];%[^;];%[^\n]", ticketID, lisence, enter_time, exit_time);
            fgetc(file);

            if (a == EOF)
                break;

            struct Visitor* node = (struct Visitor*)malloc(sizeof(struct Visitor));
            strcpy(node->ticketID, ticketID);
            strcpy(node->lisence, lisence);
            strcpy(node->enter_time, enter_time);
            strcpy(node->exit_time, exit_time);
            node->left = NULL;
            node->right = NULL;
            if (root == NULL) {
                root = pushHistory(root, node);
            } else {
                pushHistory(root, node);
            }


            if (ticketID[0] == 'C') {
                cCount++;
            } else {
                mCount++;
            }
        }
        fclose(file);
    }
}

int main() {

    loadData();
    system("cls");
    loginMenu();

    return 0;
}
