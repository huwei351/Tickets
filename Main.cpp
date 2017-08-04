#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>

#include "Algorithm.h"

enum {
    PRE_MSG_SSQ = 1,
    PRE_MSG_DLT,
    PRE_QUIT = 99
};

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
    float num_weight = 0.5;
    float wuxing_weight = 0.5;
    Algorithm *ai = new Algorithm();
    ai->getCurNumAndWuxingWeight(num_weight, wuxing_weight);

    do {
        printf("\nResult Predict MsgID Menu:\n");
        printf("    %d  => Enter SSQ Submenu\n", 1);
        printf("    %d  => Enter DLT Submenu \n", 2);
        printf("    %d  => Quit Program\n", 99);
        choice = app_get_choice("Select action");

        switch(choice) {
            case PRE_MSG_SSQ: {
                    printf("\nSSQ Predict Submenu:\n");
                    printf("    %d  => Predict Latest SSQ Result\n", 1);
                    printf("    %d  => Compare Actual Result with Predict Result\n", 2);
                    printf("    %d  => Set Default num/wuxing Weight\n", 3);
                    printf("    %d  => Quit Program\n", PRE_QUIT);
                    ssq_index = app_get_choice("Select Function");

                    switch(ssq_index) {
                        case 1: {
                                printf("\nPleaes Slelect SSQ Predict Result Display Numbers:\n");
                                printf("    %d  => 5 Results\n", 5);
                                printf("    %d  => 10 Results\n", 10);
                                printf("    %d  => 20 Results\n", 20);
                                printf("    %d  => 50 Results\n", 50);
                                printf("    %d  => Quit Program\n", PRE_QUIT);
                                int choice = app_get_choice("Select Numbers");
                                ai->updateDatabase();
                                ai->getMaxProbabilityPredictResult(choice);
                            }
                            break;

                        case 2: {
                            }
                            break;

                        case 3: {
                                printf("\nSet Num/Wuxing Weight (default: 0.5-0.5)\n");
                                printf("Current Weight Num-Wuxing: %0.3f-%0.3f, Please Select:\n", num_weight, wuxing_weight);
                                printf("    %d  => Num-Wuxing: 0.4-0.6\n", 1);
                                printf("    %d  => Num-Wuxing: 0.3-0.7\n", 2);
                                printf("    %d  => Num-Wuxing: 0.2-0.8\n", 3);
                                printf("    %d  => Num-Wuxing: 0.1-0.9\n", 4);
                                printf("    %d  => Type Other Choices\n", 5);
                                printf("    %d  => Reset To Default (0.5-0.5)\n", 6);
                                printf("    %d  => Quit Program\n", PRE_QUIT);
                                int choice = app_get_choice("Select Numbers");

                                if(choice == 1) {
                                    ai->setNumAndWuxingWeight(0.4, 0.6);
                                } else if(choice == 2) {
                                    ai->setNumAndWuxingWeight(0.3, 0.7);
                                } else if(choice == 3) {
                                    ai->setNumAndWuxingWeight(0.2, 0.8);
                                } else if(choice == 4) {
                                    ai->setNumAndWuxingWeight(0.1, 0.9);
                                } else if(choice == 5) {
                                    //TODO
                                } else if(choice == 6) {
                                    ai->setNumAndWuxingWeight(0.5, 0.5);
                                } else if(choice == PRE_QUIT) {
                                    break;
                                } else {
                                    printf("Unknown choice\n");
                                }
                            }
                            break;

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
                    printf("\nDLT Predict Submenu:\n");
                    printf("	%d	=> Predict Latest DLT Result\n", 1);
                    printf("	%d	=> Compare Actual Result with Predict Result\n", 2);
                    printf("	%d	=> Quit Program\n", PRE_QUIT);
                    dlt_index = app_get_choice("Select Function");

                    switch(dlt_index) {
                        case 1: {
                            }

                        case 2: {
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

