#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priorityqueue.h"

struct cashiers{
    int time;
    int available;
    int time_spent_working;
    double time_spent_working_percentage;
};

typedef struct cashiers Cashiers;

double RandomNumber()
{
    return ((rand()%100) / 100.0);
}

Cashiers AssignCashiers(Cashiers *cash, int cashier_amount, int cashier_service_time)
{
    for(int i = 0; i < cashier_amount; ++i){
        cash[i].available = 1;
        cash[i].time = 0;
        cash[i].time_spent_working = 0;
        cash[i].time_spent_working_percentage = 0;
    }

    return *cash;
}


int NewCustomer(double new_customer_probability)
{
    double RNG = RandomNumber() + new_customer_probability;
    if(RNG >= 1){
        return 1;
    }
    return 0;
}

double AverageWaitingTime(Queue *waiting_times)
{
    double average = 0;
    int sum = 0, queue_size = SizeOfQueue(waiting_times);

    if(queue_size != 0){
        while(SizeOfQueue(waiting_times) != 0){
            sum += popOut(waiting_times);
        }
        return average = ((double)sum / queue_size);
    }
    return 0;
}

void PrintSectionLines()
{
    printf("******************************************************\n");
}

void PrintResults(int customers_serviced, int customers_unserviced, int biggest_queue_size, int longest_waiting_time, Queue *waiting_times)
{
    printf("Aptarnauti klientai:        %d\n", customers_serviced);
    printf("Neaptarnauti zmones:        %d\n", customers_unserviced);
    printf("Didziausias eiles skaicius: %d\n", biggest_queue_size);
    printf("Ilgiausias lauktas laikas:  %d min\n", longest_waiting_time);
    printf("Vidutinis kliento laukimas: %.2lf min\n", AverageWaitingTime(waiting_times));
    PrintSectionLines();
}

void WholeDaysWork(int working_hours, int cashier_amount, int cashier_service_time, double new_customer_probability)
{
    Queue *customer_queue = createQueue();
    Queue *waiting_times = createQueue();
    Cashiers* cash = (Cashiers*)malloc(cashier_amount * sizeof(Cashiers));

    new_customer_probability = new_customer_probability / 100;
    int counter, size_of_queue = 0, customers_serviced = 0;
    int longest_waiting_time = 0, biggest_queue_size = 0, customers_unserviced, temporary;

    AssignCashiers(cash,cashier_amount,cashier_service_time);
    PrintSectionLines();
    printf("PRADINIAI DUOMENYS:\nDarbo laikas: %d min\nKasininkes: %d \nAptarnavimo laikas: %d min\nTikimybe kad ateis klientas: %.2lf\n",working_hours, cashier_amount, cashier_service_time, new_customer_probability);
    PrintSectionLines();

    for(int current_time = 1; current_time <= working_hours; ++current_time){
        // Check the availability of cashiers
        for(int j = 0; j < cashier_amount; ++j){
            // Counts the time cashier spends working
            if(cash[j].available == 0){
                cash[j].time_spent_working++;
            }
            
            if(cash[j].available == 0 && cash[j].time == current_time){
                customers_serviced++;
                cash[j].available = 1;
                cash[j].time = 0;
            }
        }

        // Check if there are any customers in the queue
        if(IsEmpty(customer_queue) == 0){
            // If the queue is not empty, check if there are any available cashiers
            for(int h = 0; h < cashier_amount; ++h){
                // If a cashier is available, then the customer will be serviced
                if(cash[h].available == 1){
                    cash[h].available = 0;
                    cash[h].time = current_time + cashier_service_time;
                    temporary = popOut(customer_queue);

                    // Queue that keeps track of all the times customers had to wait before being serviced
                    insert(waiting_times, (current_time - temporary), 1);

                    if( (current_time - temporary) >= longest_waiting_time){
                        longest_waiting_time = current_time - temporary;
                    }
                    size_of_queue--;
                    break;
                }
            }
        }

        // Check if a new customer comes in
        if(NewCustomer(new_customer_probability)){
            counter = 0;
            // Check if there are available cashiers
            for(int i = 0; i < cashier_amount; ++i){
                // If a cashier is available, then the customer will be serviced
                if(cash[i].available == 1){
                    // This cashier becomes unavailable while he/she services the customer
                    cash[i].available = 0;
                    cash[i].time = current_time + cashier_service_time;
                    break;
                }else{ 
                    counter++;
                }
            }

            // If true, that means there were no available cashiers at that time
            if(counter == cashier_amount){
                // The customer has to wait in a queue
                size_of_queue++;
                insert(customer_queue, current_time, 1);
            }
        }

        if(size_of_queue >= biggest_queue_size){
            biggest_queue_size = size_of_queue;
        }

    }
    customers_unserviced = customer_queue->size;



    PrintResults(customers_serviced,customers_unserviced,biggest_queue_size,longest_waiting_time,waiting_times);
    
    for(int i = 0; i < cashier_amount; ++i){
        cash[i].time_spent_working_percentage = (cash[i].time_spent_working * 100.0)/working_hours;
        printf("Kasininke nr. %d, buvo uzimta %.2lf %% viso darbo laiko\n", i+1, cash[i].time_spent_working_percentage);
    }
    PrintSectionLines();

    free(cash);
    clearQueue(customer_queue);
    clearQueue(waiting_times);
}

int main()
{
    srand(time(NULL));
    int cashier_amount, cashier_services_time;
    double new_customer_probability;
    int working_hours;

    FILE *data_file = fopen("duom.txt", "r");
    fscanf(data_file, "%d", &working_hours);
    fscanf(data_file, "%d", &cashier_amount);
    fscanf(data_file, "%d", &cashier_services_time);
    fscanf(data_file, "%lf", &new_customer_probability);

    fclose(data_file);

    WholeDaysWork(working_hours,cashier_amount,cashier_services_time,new_customer_probability);
    return 0;
}
