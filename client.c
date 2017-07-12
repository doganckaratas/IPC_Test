#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {
	int qhandler;
	key_t k = ftok("/var", 'c');
	if(k != -1) {
		qhandler = msgget(k,0644 | IPC_CREAT);
		if(qhandler != -1) { 
			char gelen[256];
			strcpy(gelen,argv[1]);	
			size_t length;
			if((length = strlen(gelen)) > 0) {
				if(gelen[length - 1] == '\n') {
					gelen[length - 1] = 0;
					length--;
				}
				if(msgsnd(qhandler,&gelen,length,0) == -1) {
					perror("msgsnd()");
					return -1;
				}
			}
		} else {
			perror("msgget()");
			return 2;
		}
		
		if(msgctl(qhandler,0,NULL) == -1) {
			perror("msgctl()");
			return 3;
		}
	} else {
		perror("ftok()");
		return 1;
	}
	return 0;
}