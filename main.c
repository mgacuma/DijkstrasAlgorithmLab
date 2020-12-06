#include <stdio.h>
#include <stdlib.h>


int main() {

	printf("\t\tDijkstra's Algorithm\n\n");

	FILE* fptr;
	errno_t err;
	char buff[255];
	int arr[26][26];
	char root, target;

	int r = 0, c = 0, i, j, len, iroot, itarget;
	

	err = fopen_s(&fptr, "C:\\Users\\Miguel\\source\\repos\\DijkstraLab\\DijkstraLab\\input.txt", "r");
	
	
	if (err != 0) {
		printf("\nINPUT FILE NOT FOUND.\n");
		exit(1);
	}

	printf("\t\t| Routing Table |\n\n");
	
	fgets(buff, 255, fptr);
	printf("%s", buff);

	for (i = 0; i < 255; i++) {
		if (buff[i] != '\0') {
			switch (buff[i]) {
				case ' ': break;
				case '\t': break;
				case '\n': break;
				default: c++;
			}
		}
		else break;
	}
	r = c;
	len = c;

	//printf("\n\n[%d]\n\n", c); CHECK

	r = 0;
	c = 0;

	while (!feof(fptr)) {
		fgets(buff, 255, fptr);
		printf("%s", buff);

		for (i = 0; i < 255; i++) {
			if (buff[i] != '\0') {
				if (buff[i] >= '0' && buff[i] <= '9') {
					arr[r][c] = buff[i] - '0';
					c++;
					
				}
			}
			else break;
		}
		r++;
		c = 0;
	}


	i = 0;
	j = 0;

	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			if (arr[i][j] ==0) {
				arr[i][j] = 999;
			}
		}
	}

	printf("\n\n");
	/* CHECK ARRAY CONTENTS
	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			printf("[%d] ", arr[i][j]);
		}
		printf("\n");
	}
	*/

	r = 0;
	c = 0;

	while (1) {
		printf("\nEnter root vertex: \n");
		scanf_s("\n%c", &root);
		if (root - 'A' > len) {
			printf("\nINVALID VERTEX. TRY AGAIN.\n");
		}
		else break;
	}

	while (1) {
		printf("\nEnter target vertex: ");
		scanf_s("\n%c", &target);
		if (target - 'A' > len) {
			printf("\nINVALID VERTEX. TRY AGAIN.\n");
		}
		else break;
	}

	iroot = root - 'A';
	itarget = target - 'A';


	fclose(fptr);
	return 0;
}
