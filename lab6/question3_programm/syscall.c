#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define SYS_hello 386

int main(){
long result = syscall(SYS_hello);

if(result==0){
	printf("sys_hello executed successfully.\n");
}
else{
	perror("sys_hello failed.\n");
}
return 0;
}
