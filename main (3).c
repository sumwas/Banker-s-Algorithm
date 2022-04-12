#include <stdio.h>
#include <stdlib.h>

// Declare dynamic arrays/vectors and global variables
int *resource = NULL;
int *available = NULL;
int *maximum = NULL;
int *allocated = NULL;
int *need = NULL;

int num_processes;
int num_resources;

//*********************************************************
void print_resource_vector() {
	// declare local variables 
	printf("\nResources:\n");
	// for loop: print each resource index 
	for (int j = 0; j<num_resources; j++){
	    printf("\tr%d", j);
	}
	printf("\n");
	// for loop: print number of total units of each resource index 
	for (int j = 0; j<num_resources; j++){
	    printf("\t%d", resource[j]);
	}
	return;
}

//*********************************************************
void print_available_vector() {
    printf("\n");
	// declare local variables 
	printf("\nAvailable:\n");
	// for loop: print each resource index 
	for (int j = 0; j<num_resources; j++){
	    printf("\tr%d", j);
	}
	printf("\n");
	// for loop: print number of total units of each resource index 
	for (int j = 0; j<num_resources; j++){
	    printf("\t%d", available[j]);
	}
	return;
}


//*************************************************************
void print_maxclaim_array() { 
    printf("\n");
	// declare local variables 
		printf("\nMaximum:\n");
	// for loop: print each resource index 
	for (int j = 0; j<num_resources; j++){
	    printf("\tr%d", j);
	}
	//printf("\n");
	// for each process:
	for (int i = 0; i<num_processes; i++){
	    printf("\np%d", i);
	    for (int j = 0; j<num_resources; j++){
	        printf("\t%d", maximum[(i*num_resources)+j]);
	    }
	    //printf("\n");
	}
		// for each resource: 
			// print maximum number of units each process may request from each resource 
	return;
}


//*************************************************************
void print_allocated_array() { 
	 printf("\n");
	// declare local variables 
		printf("\nAllocated:\n");
	// for loop: print each resource index 
	for (int j = 0; j<num_resources; j++){
	    printf("\tr%d", j);
	}
	//printf("\n");
	// for each process:
	for (int i = 0; i<num_processes; i++){
	    printf("\np%d", i);
	    for (int j = 0; j<num_resources; j++){
	        printf("\t%d", allocated[(i*num_resources)+j]);
	    }
	    //printf("\n");
	}
		// for each resource: 
			// print number of units each process is allocated from each resource 
	return;
}

//*************************************************************
void print_need_array() { 
	 printf("\n");
	// declare local variables 
		printf("\nNeed:\n");
	// for loop: print each resource index 
	for (int j = 0; j<num_resources; j++){
	    printf("\tr%d", j);
	}
	//printf("\n");
	// for each process:
	for (int i = 0; i<num_processes; i++){
	    printf("\np%d", i);
	    for (int j = 0; j<num_resources; j++){
	        printf("\t%d", need[(i*num_resources)+j]);
	    }
	    //printf("\n");
	}
		// for each resource: 
			// print number of units each process needs from each resource 
	return;
}

//**************************************************************
void option1() {
	// declare local variables 
	int units;
	
	// prompt for number of processes and number of resources 
	printf("Enter number of processes: ");
	scanf("%d", &num_processes);
	printf("Enter number of resources: ");
	scanf("%d", &num_resources);
	
	// allocate memory for vectors and arrays: resource, available, max_claim, allocated, need 
	resource = (int *)malloc(num_resources * sizeof(int));
	available = (int *)malloc(num_resources * sizeof(int));
	maximum = (int *)malloc(num_processes * num_resources * sizeof(int));
	allocated = (int *)malloc(num_processes * num_resources * sizeof(int));
	need = (int *)malloc(num_processes * num_resources * sizeof(int));
	
	// for each resource, prompt for number of units, set resource and available vectors indices
	printf("Enter number of units for resources (r0 to r%d): " , num_resources-1);
	for (int j = 0; j<num_resources; j++){
	    scanf("%d", &units);
	    resource[j] = units;
	    available[j] = units;
	}
	
	// for each process, for each resource, prompt for maximum number of units requested by process, update maxclaim and need arrays
	for(int i = 0; i<num_processes; i++){
	    printf("Enter maximum units process %i will request from each resource (r0 to r%d): " , i , num_resources-1);
	    for(int j = 0; j<num_resources; j++){
	        scanf("%d", &units);
	        maximum[(i*num_resources)+j] = units;
	        need[(i*num_resources)+j] = units;
	    }
	}
	// for each process, for each resource, prompt for number of resource units allocated to process 
	for(int i = 0; i<num_processes; i++){
	    printf("Enter number of units of each resource (r0 to r%i) allocated to process p%d: " , num_resources-1, i);
	    for(int j = 0; j<num_resources; j++){
	        scanf("%d", &units);
	        allocated[(i*num_resources)+j] = units;
	        need[(i*num_resources)+j] -= units;
	        available[j] -= units;
	    }
	}
	// print resource vector, available vector, maxclaim array, allocated array, need array 
	print_resource_vector();
	print_available_vector();
	print_maxclaim_array();
	print_allocated_array();
	print_need_array();
	printf("\n");
	return;
}


//******************************************************************
void option2() {

	// declare local variables, including vector to indicate if process is safely processed and "num_done" count
	int num_done = 0;
	int *done = (int *)calloc(num_processes , sizeof(int));
	int less_than_or_equal = 1;
	int at_least_one = 1;
	
	// while not all processes are processed
	while ((num_done < num_processes) && (at_least_one == 1) ) {//2nd part of while
	    at_least_one = 0;
		// for each process  
		for (int i = 0; i<num_processes; i++){
		    less_than_or_equal = 1;
			// if process has not been processed yet 
			if (done[i] == 0){
				// print message comparing need vector with available vector
				printf("\ncomparing: < ");
				for(int j = 0; j<num_resources; j++){
				    printf("%d ",need[(i*num_resources)+j]);
				} //for j
				printf("> <= < ");
				for(int j = 0; j<num_resources; j++){
				    printf("%d ",available[j]);
				} //for j
				printf("> : ");
				// for each resource 
				for(int j = 0; j<num_resources; j++){
					// check for safe processing by comparing process' need vector to available vector 
					less_than_or_equal &= need[(i*num_resources)+j] <= available[j]; 
				} //for
	      		// if every resource is available 
	      		if (less_than_or_equal == 1){
					// print message that process can be processed
					printf("Yes --> p%d can be processed", i);
					done[i] = 1;
					at_least_one = 1;
					// update number of available units of resource 
					// for each resource 
					for (int j = 0; j<num_resources; j++){
						// free all resources allocated to process 
						available[j] +=  allocated[(i*num_resources)+j];
						allocated[(i*num_resources)+j] = 0;
						// increment number of sequenced processes 
					} // for j
					num_done++;
	      		}
				// else print message that process cannot be processed
				else {
				    printf("No --> p%d could not be processed", i);
				}
			}// if (done ==0)
		} // for j
	} // while
	
	//if (no process was processed in the final round of the for-loop)
	if (num_done < num_processes){
		// print message of deadlock among processes not processed	
		printf("\nDeadlock among processes: ");
		for (int i = 0; i< num_processes; i++){
		    if (done[i]==0){
		        printf("p%d ", i);
		    } //if
		} //for
		printf("\n");
	} //if
	return;
}


//******************************************************************
void option3() {
	// check if vectors/array are not NULL--if so, free each vector/array 	);
	if (resource != NULL){
	    free(resource);
	    free(available);
	    free(maximum);
	    free(allocated);
	    free(need);
	}
	return;
}


//*************************************************************
int main() {
	   /* declare local vars */
    int choice = 0;
    /* while user has not chosen to quit */
    while (choice != 3) {
        /* print menu of options */
        printf("\nBanker's Algorithm \n------------------\n1) Enter parameters \n2) Determine safe sequence  \n3) Quit program  \n");
        /* prompt for menu selection */
        printf("\nEnter selection: ");
        scanf("%d" , &choice);
        
        /* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */
        if (choice == 1){
            option1();
        }
        else if (choice == 2){
            option2();
        }
        else if (choice == 3){
            option3();
        }
        else {
            printf("Invalid Option\n");
        }
        
} /* while loop */
	 return 1; // indicates success 
} // end of procedure 



