#ifndef BBQUIC_HASH_H
#define BBQUIC_HASH_H

#ifdef __cplusplus
extern "C" {
#endif

struct BBquic_hash;

struct BBquic_hash_elem
{
    TAILQ_ENTRY(BBquic_hash_elem)
                    qhe_next_bucket,
                    qhe_next_all;
    const void     *qhe_key_data;
    void           *qhe_value;
    unsigned        qhe_key_len;
    unsigned        qhe_hash_val;
    enum {
        QHE_HASHED  = 1 << 0,
    }               qhe_flags;
};

struct BBquic_hash *
BBquic_hash_create (void);

struct BBquic_hash *
BBquic_hash_create_ext (int (*cmp)(const void *, const void *, size_t), unsigned (*hash)(const void *, size_t, unsigned seed));

void
BBquic_hash_destroy (struct BBquic_hash *);

struct BBquic_hash_elem *
BBquic_hash_insert (struct BBquic_hash *, const void *key, unsigned key_sz,
                                    void *value, struct BBquic_hash_elem *);

struct BBquic_hash_elem *
BBquic_hash_find (struct BBquic_hash *, const void *key, unsigned key_sz);

#define BBquic_hashelem_getdata(el) ((el)->qhe_value)

void
BBquic_hash_erase (struct BBquic_hash *, struct BBquic_hash_elem *);

void
BBquic_hash_reset_iter (struct BBquic_hash *);

struct BBquic_hash_elem *
BBquic_hash_first (struct BBquic_hash *);

struct BBquic_hash_elem *
BBquic_hash_next (struct BBquic_hash *);

unsigned
BBquic_hash_count (struct BBquic_hash *);

size_t
BBquic_hash_mem_used (const struct BBquic_hash *);

#ifdef __cplusplus
}
#endif
#endif