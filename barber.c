#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>

pthread_mutex_t cuttingHair;
sem_t barberS; 
sem_t customerS;
sem_t changeChairs;

int numberOfChairs;
int checkFinishLeave = 0;
int emptyChairs;
int kickedCustomer = 0;

time_t totalWaitingTime;

int numberOfCustomer;
int maxArrivalTime;
int max_haricut_duration ;
int haricut_repetion;

double* waitingTimeArray;

void *threadBarber(void *data);
void *threadCustomer(void *data);
void hairCut();
void *createCustomers();


struct thread_data_customer {
    int customerNumberr;
    int haircutRepetitionn;
    int maxArivalTimee;
    int maxHaircutDurationn;
};


void *threadBarber(void *data)
{    
    int endCheck = 0;
    
    while (1)
   // int k = 0;
   // while(k < totalHairCut)
    {
        sem_wait(&customerS);
        sem_wait(&changeChairs);

        emptyChairs++; 

        sem_post(&changeChairs);
        sem_post(&barberS);        
        pthread_mutex_lock(&cuttingHair);

        hairCut();    

        pthread_mutex_unlock(&cuttingHair);
        
        printf("Customer's cut is done!.\n");
	    
        endCheck++; 
        if (checkFinishLeave == numberOfCustomer){
            break;
        }
    }
    printf("Barber did it's jub. The barber shop will be closed!!\n");
    pthread_exit(NULL);    
}

void *threadCustomer(void *data)
{  
/*
         struct thread_data_customer *pthreadData = (struct thread_data_customer *)malloc(sizeof(struct thread_data_customer));
		 pthreadData->customerNumber = i;
		 pthreadData->haircutRepetition = haricut_repetion;
		 pthreadData->maxArivalTime = maxArrivalTime;
		 pthreadData->maxHaircutDuration = max_haricut_duration;

         */
    int customerNumber = *(int *)data;
    int repetition = 0;
    int repetition2;

    while(repetition < haricut_repetion){

   
    struct timeval startTime, stopTime;
     

    sem_wait(&changeChairs); 
    // printf("Customer %d is in the waiting segmenttt @@@@@@@@@@@@@@@@@@.\n", customerNumber);
    // Here, I searched and took some help from the internet for sem_wait and sem_posts
    if (emptyChairs >= 1)
    {
                
        emptyChairs--;

        printf(" %d. Customer is waiting to barber to cut.\n", customerNumber);
        printf("Number of Empty Chairs: %d\n", emptyChairs);
        
        gettimeofday(&startTime, NULL);

        sem_post(&customerS);
        sem_post(&changeChairs);         
        sem_wait(&barberS); 
        
        
        gettimeofday(&stopTime, NULL);
        
        double time = (double)(stopTime.tv_usec - startTime.tv_usec) / 1000000 + (double)(stopTime.tv_sec - startTime.tv_sec);
        waitingTimeArray[customerNumber] += time;
        
        totalWaitingTime += 1000 * time;
        printf("Barber cut %d. Customer's hair!!\n", customerNumber);     
        repetition++;   
    }
    else
    {
        sem_post(&changeChairs);
        kickedCustomer++;
        printf("Customer couldn't find a chair and left!!!.\n");
        break;
        
    }
}   
    checkFinishLeave++;
    pthread_exit(NULL);
}

void hairCut() {

    int haircutDuration = rand() % max_haricut_duration + 1; 

	haircutDuration = haircutDuration * 1000; 
    printf("Cutting is done and took time: %d ms\n", haircutDuration);
    usleep(haircutDuration);
}

void *createCustomers() {
    int tmp;   
    int custNumber = 0;
    int j = 0;
    for(j = 0; j < numberOfCustomer; j++){

        pthread_t customer_thread;
	
        pthread_create(&customer_thread, NULL, (void *)threadCustomer, &custNumber);  
	
        custNumber++;
            
        int waitArrive = rand() % maxArrivalTime + 1;
        printf("Wait arriving time the next customer: %d\n", waitArrive);
        usleep(waitArrive*1000);
    }
}

int main(int argc, char * argv[]) {	


    srand(time(NULL)); 

     numberOfCustomer = atoi(argv[1]);
     maxArrivalTime = atoi(argv[2]);
     max_haricut_duration = atoi(argv[3]);
     haricut_repetion = atoi(argv[4]);
     numberOfChairs = atoi(argv[5]);  

    waitingTimeArray = malloc(numberOfCustomer* sizeof(double));

    int t = 0;
    for(t = 0; t < numberOfCustomer; t++){
        waitingTimeArray[t] = 0.0;
    }

      

    pthread_t barberThread;
    pthread_t CustomerT;

    pthread_mutex_init(&cuttingHair, NULL);

    sem_init(&customerS, 0, 0);
    sem_init(&barberS, 0, 0);
    sem_init(&changeChairs, 0, 1);
    
    emptyChairs = numberOfChairs; 
    
    pthread_create(&barberThread, NULL, (void *)threadBarber, NULL);  
    pthread_create(&CustomerT, NULL, (void *)createCustomers, NULL);  
	
    pthread_join(barberThread, NULL);
    pthread_join(CustomerT, NULL);
    int r = 0;
    
    
    printf("\n");

    printf("The customer number who had to left before the total repitition time: %d\n", kickedCustomer);  
    double averageTimeW = totalWaitingTime / (double) (numberOfCustomer);
    printf("The average waiting time (leaving customer are counted as 0ms) is: %f ms.\n", averageTimeW);

    for(r = 1; r < numberOfCustomer+1; r++){
       printf("Customer %d has waiting time: %f ms\n", r, waitingTimeArray[r]*1000.0);
    }  	
}