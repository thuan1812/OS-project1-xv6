#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void newProcess(int p[2]) {
	int prime;
	int n;
	close(p[1]);
	read(p[0], &prime, 4);
	printf("prime %d\n", prime);

	if (read(p[0], &n, 4)) {
		int newp[2];
		pipe(newp);
		if (n % prime != 0) write(newp[1], &n, 4);

		while(read(p[0], &n, 4)){
			if(n % prime != 0) write(newp[1], &n, 4);
		}
		close(p[0]);
	
		if (fork() == 0) {
			newProcess(newp);
		} 
		else {
			close(newp[0]);
			close(newp[1]);
			wait(0);
		}
	}
	exit(0);
}

int main(int argc, char const *argv[])
{
	int p[2];
	pipe(p);
	if (fork() == 0) {
		newProcess(p);
	}
	else {
		close(p[0]);
		for(int i = 2; i <= 35; i++) {
			write(p[1], &i, 4);
		}
		close(p[1]);
		wait(0);
		exit(0);
	}
	return 0;
}
