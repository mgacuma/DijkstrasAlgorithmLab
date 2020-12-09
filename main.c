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
	
	//Initialize visited array
	for (i = 0; i < 26; i++) {
		visited[i] = ' ';
	}

	//Open File
	err = fopen_s(&fptr, "C:\\Users\\Miguel\\source\\repos\\DijkstraLab\\DijkstraLab\\input.txt", "r");
	if (err != 0) {
		printf("\nINPUT FILE NOT FOUND.\n");
		exit(1);
	}

	//Read file and display cost matrix
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
	len = c;


	r = 0;
	c = 0;

	//Fill distances array with values
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

	//Change missing array values to infinity
	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			if (arr[i][j] == 0) {
				arr[i][j] = 999;
			}
		}
	}

	printf("\n\n");

	r = 0;
	c = 0;

	//MAIN LOOP 
	while (1) {

		//Clear Data
		for (i = 0; i < 26; i++) {
			visited[i] = ' ';
			distances[i] = 999;
			prevnode[i] = ' ';
		}

		//User Input Root Node
		while (1) {
			printf("\nEnter root vertex: \n");
			scanf_s("\n%c", &root);
			if (root - 'A' > len) {
				printf("\nINVALID VERTEX. TRY AGAIN.\n");
			}
			else break;
		}

		//User Input Target Node
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

		//Algorithm Start
		curr = root;
		adder = 0;
		bool here = false, ihere = false;

		//	MAIN DIJKSTRA LOOP
		for (j = 0; j < len; j++) {
			
			//Update old values
			for (i = 0; i < len; i++) {								
				if (arr[curr - A][i] + adder < distances[i]) {
					distances[i] = arr[curr - A][i] + adder;
					prevnode[i] = curr;
				}
			}

			//Find next values
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

			//Update Adder and current node for next loop iteration
			curr = A + itemp;
			adder = distances[itemp];
		}

		//Display Results
		printf("\nShortest path from vertex %c to vertex %c: %d\n\nPath routing: \n", root, target, distances[target-A]);
		
		curr = target;
		while (curr != root) {
			printf("%c\t<\t", curr);
			curr = prevnode[curr - A];
		}
		printf("%c\n", root);


		printf("\nShortest path to each vertex from root %c: \n", root);
		
		curr = 'A';
		for (i = 0; i < len; i++) {
			
			printf("%c\t", curr);
			curr = curr + 1;
		}
		printf("\n");
		for (i = 0; i < len; i++) {
			if (A + i == root) {
				printf("N/A\t");
			}
			else printf("%d\t", distances[i]);
		}

		printf("\n");
	}



	fclose(fptr);
	return 0;
}
