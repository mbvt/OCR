# include <errno.h>
# include <stdio.h>
# include <string.h>
# include "queue.h"

void queue_init(struct queue *queue){
	queue->size = 0;
}

int queue_is_empty(struct queue *queue){
	return queue->size == 0;
}

void queue_push(struct queue *queue, void *elm){
	errno = 0;
	struct list *list = malloc(sizeof(struct list));
	if(errno)
	{
		printf("an error: %s\n", strerror(errno));
    return;
	}
	if(list)
	{
		list->data = elm;
		if(queue->size){
			list->next = queue->store->next;
			queue->store->next = list;
		}
		else
			list->next = list;
		queue->store = list;
		queue->size++;
	}
}

void* queue_pop(struct queue *queue){
	if(queue->size==0)
		return NULL;
	struct list *list = queue->store->next;
	queue->size--;
	queue->store->next =list->next;
	void *t = list->data;
	free(list);
	return t;
}
