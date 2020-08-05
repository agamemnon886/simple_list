#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct list_s
{
	struct list_s *next; /* NULL for the last item in a list */
	int data;
}
list_t;

	/* Counts the number of items in a list.
	 */
int count_list_items(const list_t *head) {
	if(head == NULL) {
		return 0;
	}

	if (head->next != NULL) {
		return count_list_items(head->next) + 1;
	} else {
		return 1;
	}
}

    /* Inserts a new list item after the one specified as the argument.
	 */
int insert_next_to_list(list_t *item, int data) {
	int ret = -1;
	list_t *new = NULL;

	if(item == NULL) {
		fprintf(stderr, "%s, %d, Invalid argument\n", __func__, __LINE__);
		goto exit;
	}

	new = (list_t *)calloc(1, sizeof(list_t));
	if(new == NULL) {
		fprintf(stderr, "Failed to allocate memnory\n");
		goto exit;
	}

	list_t *tmp = item->next;
	new->next = tmp;
	new->data = data;
	item->next = new;

	ret = 0;

exit:

	return ret;
}

    /* Removes an item following the one specificed as the argument.
	 */
void remove_next_from_list(list_t *item) {
	if ((item != NULL) && (item->next != NULL)) {
		list_t *tmp = item->next;
		item->next = item->next->next;
		free(tmp);
	}
}

	/* Returns item data as text.
	 */
char *item_data(const list_t *list)
{
	char *buf = NULL;
	int len = 0;

	if(list == NULL) {
		fprintf(stderr, "NULL-item\n");
		goto exit;
	}

	len = snprintf(NULL, 0, "%d", list->data);

	buf = (char *)calloc(len + 1, sizeof(char));
	if(buf == NULL) {
		fprintf(stderr, "calloc() failed\n");
		goto exit;
	}

	snprintf(buf, len + 1, "%d", list->data);

exit:

	return buf;
}

int main()
{
	list_t *list = NULL;

	list = (list_t *)calloc(1, sizeof(list_t));

	list->data = 55;

	insert_next_to_list(list, 4);
	insert_next_to_list(list->next, 6);
	insert_next_to_list(list->next->next, 4389204);
	insert_next_to_list(list->next->next->next, 50);

	printf("count = %d\n", count_list_items(list));


	printf("\nPrint list:\n");
	for(list_t *tmp = list; tmp != NULL; tmp = tmp->next) {
		char *str = item_data(tmp);

		if(str != NULL) {
			printf("%s\n", str);
			free(str);
			str = NULL;
		}
	}

	printf("\n");

	remove_next_from_list(list->next);

	printf("count = %d\n", count_list_items(list));

	printf("\nPrint list:\n");
	for(list_t *tmp = list; tmp != NULL; tmp = tmp->next) {
		char *str = item_data(tmp);

		if(str != NULL) {
			printf("%s\n", str);
			free(str);
			str = NULL;
		}
	}

	printf("\n");

	list_t *tmp = list;
	while(tmp->next != NULL) {
		remove_next_from_list(tmp);
	}

	if(list != NULL) {
		free(list);
		list = NULL;
	}

	return 0;
}


