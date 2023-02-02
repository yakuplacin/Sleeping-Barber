This HomeWork is for the Abdullah Gül Üniversity (AGU) Operating Systems' HW3 - Sleeping Barber.
It is one of the solution to the Sleeping Barber problem with some parameters.

You just need to type to the terminal "make"

After make, you should type the examples.
"./barber 25 500 100 10 15"  


Sleeping Barber Problem: There is a barber shop with n chairs for waiting customers, one barber’s chair and one barber. If a customer enters to the store and there are no free chairs, the customer leaves. If a customer enters the store and the barber is sleeping, the customer wakes up the barber and gets a haircut. Otherwise, the customer enters the store and takes a seat and wait. If the barber finishes a haircut and there are waiting customers, the barber cuts the hair of the next customer. Otherwise, the barber goes to sleep in his chair. 

In this homework, you are supposed to write a program for the sleeping barber problem, which will implement a deadlock-free solution with maximum concurrency. The program should work for any number of customers (odd numbers, maximum 27). In the program, a thread will express a customer. These threads will be spawned by the main thread, which is not a customer. You need to use Pthreads, mutex and condition variables to synchronize. You can use monitor based solutions or semaphores that are deadlock free. The program will be named barber and will take the following arguments: barber <num_customer> <max_arrival_time> <max_haricut_duration> <haricut_repetion > <number_of_chairs>

For the arguments;
<num_customer> is the number of regular customers that the barber has. You need to have this many customer thread in your code 
<max_arrival_time> is the maximum time passes between each arrival of a specific customer.  
<max_haricut_duration> is the maximum time it takes to cut a customer hair. 
<haircut_repetition> represents how many times a customer will have a haircut. 
<number_of_chairs> is for the total chairs in the barber shop for customers.
Your program will stop when all customers have haircut_repetition times haircut. 

