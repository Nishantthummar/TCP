#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	int shm_id, ret_val;
	void *memory = NULL;
	char *p;
	const int msize = 0x6400;

	shm_id = shmget(IPC_PRIVATE, msize, IP_CREATE | IPC_EXCL | S_IRUSR | S_IWUSR);
	
	if (shm_id <0 ) {
		printf("\nFailed to create segment");
		shm_id = shmget(IPC_PRIVATE, msize, IP_CREATE | IPC_EXCL | S_IRUSR | S_IWUSR);

	}
	printf("\nCreating segment successfully with id is %d", shm_id);
	
	memory = shmat(shm_id, NULL, 0);


