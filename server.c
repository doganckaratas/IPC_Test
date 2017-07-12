#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

int main() {
while(1) {
	int qhandler;
	key_t k = ftok("/var", 'c');
	if(k != -1) {
		qhandler = msgget(k,0644 | IPC_CREAT);
		if(qhandler != -1) { 
			char gelen[256] = "";
				msgrcv(qhandler,&gelen,sizeof(gelen),0,0);
				printf("%s\n",gelen);
		} else {
			perror("msgget()");
			return -1;
		}
	} else {
		perror("ftok()");
		return -3;
	}
	}
	return 0;
}