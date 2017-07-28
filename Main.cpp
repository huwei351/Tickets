#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>

#include "Algorithm.h"

enum {
    PRE_MSG_SSQ = 1,
    PRE_MSG_DLT,
    PRE_MSG_SSQ_UPDATE,
    PRE_MSG_SSQ_PREDICT,
    PRE_MSG_SSQ_REPORT,
    PRE_MSG_DLT_UPDATE,
    PRE_MSG_DLT_PREDICT,
    PRE_MSG_DLT_REPORT,
    PRE_QUIT = 99
};

void pre_display_main_menu(void)
{
    printf("\nResult Predict MsgID Menu:\n");
    printf("    %d  => Enter SSQ Submenu\n", PRE_MSG_SSQ);
    printf("    %d  => Enter DLT Submenu \n", PRE_MSG_DLT);
    printf("    %d  => Quit Program\n", PRE_QUIT);
}

void pre_display_ssq_submenu(void)
{
    printf("\nSSQ Predict Submenu:\n");
    printf("    %d  => Update SSQ Result Database\n", PRE_MSG_SSQ_UPDATE);
    printf("    %d  => Predict Latest SSQ Result\n", PRE_MSG_SSQ_PREDICT);
    printf("    %d  => Compare Actual Result with Predict Result\n", PRE_MSG_SSQ_REPORT);
    printf("    %d  => Quit Program\n", PRE_QUIT);
}

void pre_display_dlt_submenu(void)
{
    printf("\nDLT Predict Submenu:\n");
    printf("    %d  => Update DLT Result Database\n", PRE_MSG_DLT_UPDATE);
    printf("    %d  => Predict Latest DLT Result\n", PRE_MSG_DLT_PREDICT);
    printf("    %d  => Compare Actual Result with Predict Result\n", PRE_MSG_DLT_REPORT);
    printf("    %d  => Quit Program\n", PRE_QUIT);
}

int app_get_choice(const char *querystring)
{
    int neg, value, c, base;
    int count = 0;
    base = 10;
    neg = 1;
    printf("%s => ", querystring);
    value = 0;

    do {
        c = getchar();

        if((count == 0) && (c == '\n')) {
            return -1;
        }

        count ++;

        if((c >= '0') && (c <= '9')) {
            value = (value * base) + (c - '0');
        } else if((c >= 'a') && (c <= 'f')) {
            value = (value * base) + (c - 'a' + 10);
        } else if((c >= 'A') && (c <= 'F')) {
            value = (value * base) + (c - 'A' + 10);
        } else if(c == '-') {
            neg *= -1;
        } else if(c == 'x') {
            base = 16;
        }
    } while((c != EOF) && (c != '\n'));

    return value * neg;
}

int32_t main(int32_t argc, char *argv[])
{
    int choice;
    int ssq_index;
    int dlt_index;
    Algorithm *ai = new Algorithm();

    do {
        pre_display_main_menu();
        choice = app_get_choice("Select action");

        switch(choice) {
            case PRE_MSG_SSQ: {
                    pre_display_ssq_submenu();
                    ssq_index = app_get_choice("Select Function");

                    switch(ssq_index) {
                        case PRE_MSG_SSQ_UPDATE: {
                                bool success = ai->updateDatabase();

                                if(!success)
                                { printf("updatae database fail!\n"); }
                            }
                            break;

                        case PRE_MSG_SSQ_PREDICT: {
                                printf("\nPleaes Slelect SSQ Predict Result Display Numbers:\n");
                                printf("    %d  => 5 Results\n", 5);
                                printf("    %d  => 10 Results\n", 10);
                                printf("    %d  => 20 Results\n", 20);
                                printf("    %d  => 50 Results\n", 50);
                                printf("    %d  => Quit Program\n", PRE_QUIT);
                                int choice = app_get_choice("Select Numbers");
                                ai->getMaxProbabilityPredictResult(choice);
                            }
                            break;

                        case PRE_MSG_SSQ_REPORT: {
                            }

                        case PRE_QUIT: {
                                printf("Quit SSQ Submenu\n");
                                break;
                            }

                        default:
                            printf("Unknown choice:%d", ssq_index);
                            break;
                    }

                    break;
                }

            case PRE_MSG_DLT: {
                    pre_display_dlt_submenu();
                    dlt_index = app_get_choice("Select Function");

                    switch(dlt_index) {
                        case PRE_MSG_DLT_UPDATE: {
                            }

                        case PRE_MSG_DLT_PREDICT: {
                            }

                        case PRE_MSG_DLT_REPORT: {
                            }

                        case PRE_QUIT: {
                                printf("Quit DLT Submenu\n");
                                break;
                            }

                        default:
                            printf("Unknown choice:%d", dlt_index);
                            break;
                    }

                    break;
                }
                break;

            case PRE_QUIT:
                printf("main: Bye Bye\n");
                break;

            default:
                printf("Unknown choice:%d", choice);
                break;
        }
    } while(choice != PRE_QUIT);  /* While user don't exit application */

    delete ai;
    printf(" Result Predict Program is quiting...\n");
    return 0;
}

