#ifndef _LFQ_HH_
#define _LFQ_HH_
#include"lfq-public.h"
class lfq {
private:
  lfq_ctx ctx;
  int max_consume_thread;
public:
  lfq(int max_consume_thread = 4):
    ctx()
  {
    lfq_init(&ctx, max_consume_thread);
  }
  ~lfq() {
    lfq_clean(&ctx);
  }
  void enqueue(void* item) {
    lfq_enqueue(&ctx, item);
  }
  void* dequeue() {
    return lfq_dequeue(&ctx);
  }
  void* dequeue(int tid) {
    return lfq_dequeue_tid(&ctx, tid);
  }

};
#endif //_LFQ_HH_