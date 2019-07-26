#ifndef __LFQ_PUBLIC_H__
#define __LFQ_PUBLIC_H__
extern "C" {
struct lfq_node{
	void * data;
	union {
		struct lfq_node * volatile next;
		struct lfq_node * volatile free_next;
	};
	volatile int can_free;
};

struct lfq_ctx{
	alignas(64)	volatile struct lfq_node  * volatile head;
	int volatile count;
	volatile struct lfq_node * * HP;
	volatile int * tid_map;
	int volatile is_freeing;
	volatile struct lfq_node * volatile fph; // free pool head
	volatile struct lfq_node * volatile fpt; // free pool tail
	int MAXHPSIZE;

	alignas(64) volatile struct lfq_node  * volatile tail;  // in another cache line to avoid contention
};

int lfq_init(struct lfq_ctx *ctx, int max_consume_thread);
int lfq_clean(struct lfq_ctx *ctx);
long lfg_count_freelist(const struct lfq_ctx *ctx);

int lfq_enqueue(struct lfq_ctx *ctx, void * data);
void * lfq_dequeue_tid(struct lfq_ctx *ctx, int tid );
void * lfq_dequeue(struct lfq_ctx *ctx );
}
#endif
