#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define LINESIZE 16

//use one command line argument
int main(int argc, char *argv[]) {
        if (argc < 2) {
                printf("Usage: diagonal <textstring>\n");
                return -1;
        }

	// create a file so that 20 rows of empty will appear with od -c command
        int fd = open("diagonal2.out", O_CREAT | O_WRONLY);
        printf("fd = %d\n", fd);
        char space = ' ';

        //0, 17, 34
	int save = 0;
	for(int j=2; j<=argc; j++) {
		int m = j-1;
		if (j % 2 == 0) {
			lseek(fd,save, SEEK_SET);
                        for(int line=0; line<LINESIZE; line++)
                                for(int column=0; column<LINESIZE; column++)
                                        write(fd, &space, 1);
		        int n = strlen(argv[m]);
		        for(int i=0, k=1; i<n; i++,k++) {
                		//save = save + ((LINESIZE+1)*i);
				lseek(fd,(((LINESIZE*1)+1)*i)+save, SEEK_SET);
                		write(fd, &argv[m][i], 1);
        		}
			//save += n;
			save += 16*16;
			
		}
		else {
			lseek(fd,save, SEEK_SET);
			for(int line=0; line<LINESIZE; line++)
                		for(int column=0; column<LINESIZE; column++)
                        		write(fd, &space, 1);
		        int n = strlen(argv[m]);
                        for(int i=0, k=1; i<n; i++,k++) {
				//save = save + ((LINESIZE-1)*i);
                      		lseek(fd,(((LINESIZE*1)-1)*k)+save, SEEK_SET);
                                write(fd, &argv[m][i], 1);
                        }
			//save += n;
			save += 16*16;
		}
	}

	close(fd);
}

