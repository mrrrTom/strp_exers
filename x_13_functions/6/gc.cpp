#include "gc.hpp"

/* ========================================================================== */
/*  mini_gc_malloc                                                            */
/* ========================================================================== */
static header* add_heap(size_t req_size)
{
    void *p;
    header *align_p;

    if (gc_heaps_used >= HEAP_LIMIT) {
        fputs("OutOfMemory Error", stderr);
        abort();
    }

    if (req_size < TINY_HEAP_SIZE)
        req_size = TINY_HEAP_SIZE;

    if((p = sbrk(req_size + PTRSIZE + HEADER_SIZE)) == (void *)-1)
        return NULL;

    /* address alignment */
    align_p = gc_heaps[gc_heaps_used].slot = (header*)ALIGN((size_t)p, PTRSIZE);
    req_size = gc_heaps[gc_heaps_used].size = req_size;
    align_p->size = req_size;
    align_p->next_free = align_p;
    gc_heaps_used++;

    return align_p;
}

static header* grow(size_t req_size)
{
    header* cp, *up;

    if (!(cp = add_heap(req_size)))
        return NULL;

    up = (header*) cp;
    mini_gc_free((void *)(up+1));
    return free_list;
}

void* mini_gc_malloc(size_t req_size)
{
    header* p, *prevp;
    size_t do_gc = 0;

    req_size = ALIGN(req_size, PTRSIZE);

    if (req_size <= 0) {
        return NULL;
    }
    if ((prevp = free_list) == NULL) {
        if (!(p = add_heap(TINY_HEAP_SIZE))) {
            return NULL;
        }
        prevp = free_list = p;
    }
    for (p = prevp->next_free; ; prevp = p, p = p->next_free) {
        if (p->size >= req_size) {
            if (p->size == req_size)
                /* just fit */
                prevp->next_free = p->next_free;
            else {
                /* too big */
                p->size -= (req_size + HEADER_SIZE);
                p = NEXT_HEADER(p);
                p->size = req_size;
            }
            free_list = prevp;
            FL_SET(p, FL_ALLOC);
            return (void *)(p+1);
        }
        if (p == free_list) {
            if (!do_gc) {
                garbage_collect();
                do_gc = 1;
            }
            else if ((p = grow(req_size)) == NULL)
                return NULL;
        }
    }
}

void mini_gc_free(void *ptr)
{
    header* target, *hit;

    target = (header*)ptr - 1;

    /* search join point of target to free_list */
    for (hit = free_list; !(target > hit && target < hit->next_free); hit = hit->next_free)
        /* heap end? And hit(search)? */
        if (hit >= hit->next_free &&
            (target > hit || target < hit->next_free))
            break;

    if (NEXT_HEADER(target) == hit->next_free) {
        /* merge */
        target->size += (hit->next_free->size + HEADER_SIZE);
        target->next_free = hit->next_free->next_free;
    }
    else {
        /* join next free block */
        target->next_free = hit->next_free;
    }
    if (NEXT_HEADER(hit) == target) {
        /* merge */
        hit->size += (target->size + HEADER_SIZE);
        hit->next_free = target->next_free;
    }
    else {
        /* join before free block */
        hit->next_free = target;
    }
    free_list = hit;
    target->flags = 0;
}




/* ========================================================================== */
/*  mini_gc                                                                   */
/* ========================================================================== */


static gc_heap* is_pointer_to_heap(void *ptr)
{
    size_t i;

    if (hit_cache &&
        ((void *)hit_cache->slot) <= ptr &&
        (size_t)ptr < (((size_t)hit_cache->slot) + hit_cache->size))
        return hit_cache;

    for (i = 0; i < gc_heaps_used;  i++) {
        if ((((void *)gc_heaps[i].slot) <= ptr) &&
            ((size_t)ptr < (((size_t)gc_heaps[i].slot) + gc_heaps[i].size))) {
            hit_cache = &gc_heaps[i];
            return &gc_heaps[i];
        }
    }
    return NULL;
}

static header* get_header(gc_heap *gh, void *ptr)
{
    header* p, *pend, *pnext;

    pend = (header*)(((size_t)gh->slot) + gh->size);
    for (p = gh->slot; p < pend; p = pnext) {
        pnext = NEXT_HEADER(p);
        if ((void *)(p+1) <= ptr && ptr < (void *)pnext) {
            return p;
        }
    }
    return NULL;
}

void gc_init(void)
{
    long dummy;

    /* referenced bdw-gc mark_rts.c */
    dummy = 42;

    /* check stack grow */
    stack_start = ((void *)&dummy);
}

static void set_stack_end(void)
{
    void *tmp;
    long dummy;

    /* referenced bdw-gc mark_rts.c */
    dummy = 42;

    stack_end = (void *)&dummy;
}

static void gc_mark_range(void *start, void *end);

static void gc_mark(void* ptr)
{
    gc_heap* gh;
    header *hdr;

    /* mark check */
    if (!(gh = is_pointer_to_heap(ptr))) return;
    if (!(hdr = get_header(gh, ptr))) return;
    if (!FL_TEST(hdr, FL_ALLOC)) return;
    if (FL_TEST(hdr, FL_MARK)) return;

    /* marking */
    FL_SET(hdr, FL_MARK);
    //DEBUG(printf("mark ptr : %p, header : %p\n", ptr, hdr));

    /* mark children */
    gc_mark_range((void *)(hdr+1), (void *)NEXT_HEADER(hdr));
}

static void gc_mark_range(void *start, void *end)
{
    char* p;

    for (p = reinterpret_cast<char*>(start); p < end; p++) {
        gc_mark(*(void **)p);
    }
}

static void gc_mark_register(void)
{
    jmp_buf env;
    size_t i;

    setjmp(env);
    for (i = 0; i < sizeof(env); i++) {
        gc_mark(((void **)env)[i]);
    }
}

static void gc_mark_stack(void)
{
    set_stack_end();
    if (stack_start > stack_end) {
        gc_mark_range(stack_end, stack_start);
    }
    else {
        gc_mark_range(stack_start, stack_end);
    }
}

static void gc_sweep(void)
{
    size_t i;
    header *p, *pend, *pnext;

    for (i = 0; i < gc_heaps_used; i++) {
        pend = (header*)(((size_t)gc_heaps[i].slot) + gc_heaps[i].size);
        for (p = gc_heaps[i].slot; p < pend; p = NEXT_HEADER(p)) {
            if (FL_TEST(p, FL_ALLOC)) {
                if (FL_TEST(p, FL_MARK)) {
                    //DEBUG(printf("mark unset : %p\n", p));
                    FL_UNSET(p, FL_MARK);
                }
                else {
                    mini_gc_free(p+1);
                }
            }
        }
    }
}

void add_roots(void * start, void * end)
{
    void *tmp;
    if (start > end) {
        tmp = start;
        start = end;
        end = tmp;
    }
    root_ranges[root_ranges_used].start = start;
    root_ranges[root_ranges_used].end = end;
    root_ranges_used++;

    if (root_ranges_used >= ROOT_RANGES_LIMIT) {
        fputs("Root OverFlow", stderr);
        abort();
    }
}

void garbage_collect(void)
{
    size_t i;

    /* marking machine context */
    gc_mark_register();
    gc_mark_stack();

    /* marking roots */
    for (i = 0; i < root_ranges_used; i++) {
        gc_mark_range(root_ranges[i].start, root_ranges[i].end);
    }

    /* sweeping */
    gc_sweep();
}
