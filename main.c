#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	char *name;
	int weight;
	int value;
} item_info;

void loot(item_info **items, int entries, int capacity) {
	int arr[entries + 1][capacity + 1];
	for (int i = 0; i <= entries; i++) {
		for (int w = 0; w <= capacity; w++) arr[i][w] = 0;
	}
	for (int i = 1; i <= entries; i++) {
		for (int w = 0; w <= capacity; w++) {
			if (items[i - 1]->weight <= w) arr[i][w] = fmax(arr[i - 1][w], arr[i - 1][w - items[i - 1]->weight] + items[i - 1]->value);
			else arr[i][w] = arr[i - 1][w];
		}
	}
	int max_value = arr[entries][capacity];
	int fin_val = max_value;
	int fin_wt = 0, count = 0;
	item_info *selected[entries];
	int w = capacity;
	for (int i = entries; i > 0 && max_value > 0; i--) {
		if (max_value != arr[i - 1][w]) {
			selected[count++] = items[i - 1];
			fin_wt += items[i - 1]->weight;
			max_value -= items[i - 1]->value;
			w -= items[i - 1]->weight;
		}
	}
	for (int i = count - 1; i >= 0; i--) printf("%s, %d, %d\n", selected[i]->name, selected[i]->weight, selected[i]->value);
	printf("final weight: %d\nfinal value: %d\n", fin_wt, fin_val);
}

int main() {
	item_info **items = malloc(128 * sizeof(item_info*));
	char *wt = calloc(5, sizeof(char));
	fscanf(stdin, "%s", wt);
	int weight = atoi(wt);
	char *buf = malloc(128 * sizeof(char));
	int index = 0, outer = 0, count = -1;
	char c;
	while ((c = fgetc(stdin))) {
		if (c == ';' || c == EOF || c == '\n') {
			buf[index++] = '\0';
			index = 0;
			if (count > -1) {
				switch (count % 3) {
					case 0:
						items[outer] = malloc(sizeof(item_info));
						items[outer]->name = malloc((strlen(buf) + 1) * sizeof(char));
						strcpy(items[outer]->name, buf);
						break;
					case 1:
						items[outer]->weight = atoi(buf);
						break;
					case 2:
						items[outer]->value = atoi(buf);
						outer++;
						break;
				}
			}
			count++;
			if (c == EOF) break;
		} else buf[index++] = c;
	}
	loot(items, count / 3, weight);
}