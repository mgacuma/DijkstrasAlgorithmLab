#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main() {

	printf("\t\tDijkstra's Algorithm\n\n");

	FILE* fptr;
	errno_t err;

	int arr[26][26];
	char buff[255];
	char visited[26];
	int distances[26];
	char prevnode[26];
	char root, target, prev, curr;

	int r = 0, c = 0, A = 65, i, j, k, len, iroot, itarget, adder, min, next;
	
	for (i = 0; i < 26; i++) {
		visited[i] = ' ';
	}

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
			if (arr[i][j] == 0) {
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

	//MAIN LOOP SOLVER
	while (1) {

		for (i = 0; i < 26; i++) {
			visited[i] = ' ';
			distances[i] = 999;
			prevnode[i] = ' ';
		}

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

		iroot = root - A;
		itarget = target - A;

		//////////////////////////////////////////////////////////////

		curr = root;
		adder = 0;
		bool here = false, ihere = false;

		for (j = 0; j < len; j++) {								//	MAIN DIJKSTRA LOOP

			for (i = 0; i < len; i++) {								//Update old values
				if (arr[curr - A][i] + adder < distances[i]) {
					distances[i] = arr[curr - A][i] + adder;
					prevnode[i] = curr;
				}
			}

			printf("\n");
			for (i = 0; i < len; i++) {
				if (A + i == root) {
					printf("N/A\t");
				}
				else printf("%d\t", distances[i]);
			}

			/////////////////////find next values

			printf("\nCURRENT NODE: %c\n", curr);
			visited[j] = curr;
			prev = curr;
			char temp;
			int itemp = 0;
			min = 999;

			for (i = 0; i < len; i++) {
				here = false;
				if (distances[i] < min) {
					for (k = 0; k < len; k++) {
						if (visited[k] == A + i) {
							here = true;
							break;
						}
					}
					if (!here) {
						min = distances[i];
						itemp = i;
					}
				}  
				
			}

			curr = A + itemp;
			adder = distances[itemp];


			printf("\nCURRENT NODE: %c\n", curr);
			printf("\nADDER: %d\n", adder);
		}


		printf("\nShortest path from vertex %c to vertex %c: %d\n", root, target, distances[target-A]);

		printf("\nShortest path to each vertex: \n");
		char ctemp = 'A';
		for (i = 0; i < len; i++) {
			
			printf("%c\t", ctemp);
			ctemp = ctemp + 1;
		}
		printf("\n");
		for (i = 0; i < len; i++) {
			if (A + i == root) {
				printf("N/A\t");
			}
			else printf("%d\t", distances[i]);
		}
		printf("\n");
		for (i = 0; i < len; i++) {
			printf("%c\t", prevnode[i]);
		}
		printf("\n");
		for (i = 0; i < len; i++) {
			printf("%c\t", visited[i]);
		}
	}



	fclose(fptr);
	return 0;
}
